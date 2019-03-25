#include <iostream>
#include <sstream>
#include <assert.h>

#include "Expression.hh"
#include "Complex.hh"


/*!
 * Tworzy sprzężenie liczby zespolonej
 * Argumenty:
 *    complex - liczba zespolona,
 * Zwraca:
 *    Sprzężenie liczby zespolonej.
 */
Complex conjugate(Complex complex)
{
  complex.im = -complex.im;

  return complex;
}

/*!
 * Tworzy moduł liczby zespolonej
 * Argumenty:
 *    complex - liczba zespolona,
 * Zwraca:
 *    Moduł liczby zespolonej.
 */
Complex modulus(Complex complex)
{
  Complex con = conjugate(complex);
  Complex mod;

  mod = complex * con;

  return mod;
}


/*!
 * Realizuje dodanie dwoch liczb zespolonych.
 * Argumenty:
 *    arg1 - pierwszy skladnik dodawania,
 *    arg2 - drugi skladnik dodawania.
 * Zwraca:
 *    Sume dwoch skladnikow przekazanych jako parametry.
 */
Complex  operator + (Complex  arg1,  Complex  arg2)
{
  Complex  result;

  result.re = arg1.re + arg2.re;
  result.im = arg1.im + arg2.im;
  return result;
}

/*!
 * Realizuje odejmowanie dwoch liczb zespolonych.
 * Argumenty:
 *    arg1 - pierwszy skladnik odejmowania,
 *    arg2 - drugi skladnik odejmowanie.
 * Zwraca:
 *    Roznice dwoch skladnikow przekazanych jako parametry.
 */
Complex  operator - (Complex  arg1,  Complex  arg2)
{
  Complex  result;

  result.re = arg1.re - arg2.re;
  result.im = arg1.im - arg2.im;
  return result;
}

/*!
 * Realizuje mnozenia dwoch liczb zespolonych.
 * Argumenty:
 *    arg1 - pierwszy skladnik mnozenia,
 *    arg2 - drugi skladnik mnozenia.
 * Zwraca:
 *    Iloczyn dwoch skladnikow przekazanych jako parametry.
 */
Complex  operator * (Complex  arg1,  Complex  arg2)
{
  Complex  result{0,0};

  result.re = arg1.re * arg2.re;
  result.im = arg1.re * arg2.im;
  result.re -= arg1.im * arg2.im;
  result.im += arg1.im * arg2.re;

  return result;
}

/*!
 * Realizuje dzielenia dwoch liczb zespolonych.
 * Argumenty:
 *    arg1 - pierwszy skladnik dzielenia,
 *    arg2 - drugi skladnik dzielenia.
 * Zwraca:
 *    Iloraz dwoch skladnikow przekazanych jako parametry.
 */
Complex  operator / (Complex  arg1,  Complex  arg2)
{
  Complex  result;

    if(!(arg2.re + arg2.im))
    {
      std::cerr << "Error: Division by zero occured!" << std::endl;
      assert(arg2.re+arg2.im);
    }

    Complex numerator = arg1 * conjugate(arg2);
    Complex denominator = modulus(arg2);

    if(denominator.re == 0)
    {
      std::cerr << "Error: Denominator is equal 0! Cannot divide!" << std::endl;
      assert(denominator.re);
    }

    result.re = numerator.re / denominator.re;
    result.im = numerator.im / denominator.re;

  return result;
}

bool operator == (Complex  arg1,  Complex  arg2)
{
  if(arg1.im == arg2.im && arg1.re == arg2.re)
    return true;
  else
    return false;
}



/*!
 * Pozwala wypisać liczbę zespoloną.
 * Argumenty:
 *    arg1 - strumień wyjścia,
 *    arg2 - liczba zespolona.
 * Zwraca:
 *    strumień z liczbą zespoloną.
 */
std::ostream& operator<<(std::ostream& stream, Complex& complex)
{
  if(!(complex.re || complex.im)){
    stream << "(" << 0 << ")";    // Jeśli całość jest równa zerom to wypisz po prostu 0
    return stream;
  }
 
  stream << "(";  // Otwórz zapis nawiasem
  if(complex.re) {
    stream << complex.re; // Wypisz część rzeczywistą
    
    if(complex.im > 0)    // Dopisz +, jeśli potrzebny
      stream << "+"; 
  }  

  if(complex.im)
  {
    if(complex.im != 1)
      stream << complex.im;
    
    stream << "i";   // Dopisz część urojoną
  }
  stream << ")";


  return stream;
}


/*!
 * Pozwala pobrać od użytkownika liczbę zespoloną.
 * Argumenty:
 *    arg1 - strumień wejścia,
 *    arg2 - liczba zespolona.
 * Zwraca:
 *    strumień z liczbą zespoloną.
 * 
 * Założenia:
 *    Użytkownik nie może wprowadzić (Nieprzeidywalne zachowanie):
 *    - spacji wewnątrz wyrażenia
 *    - pustych nawiasów
 */
std::istream& operator>>(std::istream& stream, Complex& complex)
{
    // Flagi i liczba prób
    bool failed = 0;

    std::string data; // Pojemnik na dane
    stream >> data;
    int data_len = data.length();  // Długość wyrażenia
    
    std::string numbers[10]; // Pojemnik na wyciągnięte liczby
    int num_i=0;         // Iterator dla numbers

    if(data_len < 3)
    {
      stream.setstate(std::ios::failbit);
      return stream;
    }

    // Filtrowanie danych i wyciągnięcie liczb
    // =========================================
    for(int i=1; i<data_len-1; i++)
    {
        failed = checkIfCorrectChar(data, data_len, i, numbers, num_i);

        if(failed){      
          stream.setstate(std::ios::failbit);
          return stream;
        }
    }// for
    
    // Jeśli etap filtrowania przeszedł pomyślnie
    // ========================================================
    // tablica numbers - przechowuje w tym momencie liczby podane przez użytkownika
    //                   nieposegregowane: rzeczywiste i urojone(z literką "i").
    // num_i - liczba... liczb
      for(int i=0; i <= num_i; i++){

        int numbers_len = numbers[i].length();

        if(numbers[i][0] == 'i' || (numbers[i][0] == '+' && numbers[i][1] == 'i'))
        {
          complex.im += 1;
        }
        else if (numbers[i][0] == '-' && numbers[i][1] == 'i') 
        {
          complex.im -= 1;
        }
        else if(numbers[i][numbers_len-1] == 'i')
        {
          complex.im += std::stof(numbers[i]);
        }
        else
        {
          complex.re += std::stof(numbers[i]);
        }
      }// for
  
  return stream;
}

bool checkIfCorrectChar(std::string data, int &data_len, int &i, std::string numbers[], int &num_i)
{
  bool failed = 0;
          // Najpierw sprawdźmy nawiasy
        if(data[0] != '(' || data[data_len-1] != ')')
        {
          failed = 1;
        }
        else
        {
          switch (data[i])
          {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'i':
                numbers[num_i] += data[i];
              break;

            case '+':
            case '-': // - i + ocznaczają nową liczbę - chyba, że pierwsza nie została jeszcze podana
                if(numbers[0].length() > 0)
                  if(++num_i >= 9)
                  {
                    std::cerr << "Error: Too long expression!" << std::endl; 
                    failed = 1; 
                  }
                numbers[num_i] += data[i];
              break;

            case '.': // Kropka musi być poprzedzona, bądź mieć po sobie cyfrę
                if((data[i-1] >= '0' && data[i-1] <= '9')
                || (data[i+1] >= '0' && data[i+1] <= '9'))
                {
                  numbers[num_i] += data[i];
                }
                else
                {
                  failed = 1;
                }
              break;
              
            default:
              failed = 1;
          }// switch
        }// else
    return failed;
}