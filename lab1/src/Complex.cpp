#include <iostream>
#include <sstream>

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
      return {0,0};
    }

    Complex numerator = arg1 * conjugate(arg2);
    Complex denominator = modulus(arg2) * modulus(arg2);


    result.re = numerator.re / denominator.re;
    result.im = numerator.im / denominator.re;

  return result;
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
 */
std::istream& operator>>(std::istream& stream, Complex& complex)
{
  // Flagi i liczba prób
  //////////////////
  bool failed = 0;
  int attempts = 3;

  do
  {
    failed = 0;   
    attempts--; // Odejmij jedną próbę

    std::string data; // Pojemnik na dane
    stream >> data;
    int data_len = data.length();  // Długość wyrażenia
    
    std::string numbers[10]; // Pojemnik na wyciągnięte liczby
    int numbers_i=0;         // Iterator dla numbers

    ///////////////////////////////////////////
    // Filtrowanie danych i wyciągnięcie liczb
    ///////////////////////////////////////////
    for(int i=0; i<data_len; i++)
    {
      if(((data[i]>= '0' && data[i] <= '9') || data[i] == '-' || data[i] == '+' || data[i] == '.' || data[i] == 'i') && i > 0 && i < data_len-1 )
      {
        if((data[i] == '-' || data[i] == '+') && numbers[0].length() > 0)
        {
          if(++numbers_i >= 9)
          {
            std::cerr << "Error: Too long expression!" << std::endl; 
            failed = 1; 
          }
        }
          numbers[numbers_i] += data[i];
      }
      else
      {
        switch (data[i])
        {
          case '(':
            if(i != 0)
              failed = 1;
            break;
          
          case ')':
            if(i != data_len-1)
              failed = 1;
            break;

          default:
            failed = 1;
        }// switch
      }// else

      if(failed){      
        std::cerr << "Error: Wrong format!" << std::endl;
        i=data_len;
        data = "";
      }
    }// for
    
    // Jeśli etap filtrowania przeszedł pomyślnie
    //////////////////////////////////////////////
    // tablica numbers - przechowuje w tym momencie liczby podane przez użytkownika
    //                   nieposegregowane: rzeczywiste i urojone(z literką "i").
    // numbers_i - liczba... liczb
    if(!failed){
      for(int i=0; i <= numbers_i; i++){

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
    }// if

  }while(failed && attempts);
  
  return stream;
}