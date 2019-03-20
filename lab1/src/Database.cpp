#include <iostream>
#include <cstring>
#include <cassert>
#include <sstream>

#include "Database.hh"

using namespace std;

// /*
//  * Tablica, ktora jest widoczna tylko w tym module.
//  * Zawiera ona tresc latwego testu.
//  */
// static Expression  easy_test[] =
//   { 
//     {{2,1}, kAddition, {1,2}},
//     {{1,0}, kSubtraction, {0,1}},
//     {{3,0}, kMultiplication, {0,3}},
//     {{4,8}, kDivision, {1,0}},
//   };

// /*
//  * Analogicznie zdefiniuj test "trudne"
//  *
//  */
// static Expression  hard_test[] =
//   { 
//     {{ 4.3,-1.1}, kMultiplication, { 2, 1.5}},
//     {{ 2, 2},     kDivision,       { 2,-1}},
//     {{ 1.1, 5.5}, kMultiplication, { 2.3, 4.1}},
//     {{-1.5, 6.0}, kDivision,       {-0.5,-1.5}},
//   };


/*
 * W bazie testu ustawia wybrany test jako biezacy test i indeks pytania
 * ustawia na pierwsze z nich.
 * Parametry:
 *    database_ptr        - wskaznik na zmienna reprezentujaca baze testu,
 *    test_array_ptr      - wskaznik na tablice zawierajaca wyrazenia arytmetyczne
 *                          bedace przedmiotem testu,
 *    number_of_questions - ilosc pytan w tablicy.
 *   
 * Warunki wstepne:
 *      - Parametr database_ptr nie moze byc pustym wskaznikiem. Musi zawierac adres
 *        zmiennej reprezentujacej baze testu, ktora wczesniej zostal poprawnie
 *        zainicjalizowany poprzez wywolanie funkcji Init.
 *      - Parametr test_array_ptr zawiera wskaznik na istniejaca tablice.
 *      - Parametr number_of_questions zawiera wartosc, ktora nie przekracza ilosci elementow
 *        w tablicy dostepnej poprzez test_array_ptr.
 */
bool SetTest(Database &database, std::string file_path)
{
  std::ifstream file;
  file.open(file_path, ios::in);

  if(!file.good()){
    return false;
  }

  // Plik został poprawnie otworzony
  // ===============================


  while(!file.eof())
  {
    std::string line;
    std::string expr[3];
    std::stringstream sstream;

    getline(file, line);

    slice(line, expr, ' ');

    Complex comp1{0,0};
    Operator op;
    Complex comp2{0,0};

    sstream.clear();
    sstream << expr[0];
    sstream >> comp1;

    const char *ch = expr[1].c_str(); // Konwersja na char
                                      // switch nie honoruje typu string
    switch(ch[0])
    {
      case '+':
          op = kAddition;
        break;

      case '-':
          op = kSubtraction;
        break;

      case '*':
          op = kMultiplication;
        break;

      case '/':
          op = kDivision;
        break;

      default:
        op = kIncorrect;
    }

    sstream.clear();
    sstream << expr[2];
    sstream >> comp2;


    std::cout << comp1 << " " << op << " " << comp2 << std::endl;

    database.questions.push_back({comp1, op, comp2});
  
  }


  if(!database.questions.empty())
    database.last_question = &database.questions.back();

  file.close();
  return true;
}




/*
 * Inicjalizuje test kojarzac zmienna dostepna poprzez wskaznik database_ptr
 * z dana tablica wyrazen, ktora reprezentuje jeden z dwoch dopuszczalnych 
 * testow.
 * Parametry:
 *    database_ptr - wskaznik na zmienna reprezentujaca baze testu.
 *    test_name  - wskaznik na napis wybranego typu testu.
 *
 * Warunki wstepne:
 *      - Parametr database_ptr nie moze byc pustym wskaznikiem. Musi zawierac adres
 *        zmiennej reprezentujacej baze testu, ktora wczesniej zostal poprawnie
 *        zainicjalizowany poprzez wywolanie funkcji Init.
 *      - Parametr test_name musi wskazywac na jedna z nazw tzn. "latwe" lub "trudne".
 *       
 * Zwraca:
 *       true - gdy operacja sie powiedzie i test zostanie poprawnie
 *              zainicjalizowany,
 *       false - w przypadku przeciwnym.
 */
bool Init( Database &database, const char *test_name)
{
  if (!strcmp(test_name,"latwy")) {
    if(SetTest(database, "./dat/easyTest.dat"))
      return true;
  }
  else if (!strcmp(test_name,"trudny")) {
    if(SetTest(database, "./dat/hardTest.dat"))
      return true;
  }

    std::cerr << "Error: couldn't open test: " << test_name << std::endl;
    return false;
}



/*!
 * Funkcja udostepnia nastepne pytania o ile jest odpowiednia ich ilosc.
 * Parametry:
 *       database_ptr   - wskaznik na zmienna reprezentujaca baze testu.
 *       expression_ptr - wskaznik na zmienna, do ktorej zostanie wpisane
 *                        kolejne wyrazenie z bazy testu.
 *
 * Warunki wstepne:
 *      - Parametr database_ptr nie moze byc pustym wskaznikiem. Musi zawierac adres
 *        zmiennej reprezentujacej baze testu, ktora wczesniej zostal poprawnie
 *        zainicjalizowany poprzez wywolanie funkcji Init.
 *      - Parametr expression_ptr nie moze byc pustym wskaznikiem. Musi wskazywac na
 *        istniejaca zmienna.
 *
 * Zwraca:
 *       true - gdy operacja sie powiedzie i parametrowi *expression_ptr zostanie
 *              przypisane nowe wyrazenie zespolone z bazy,
 *       false - w przypadku przeciwnym.
 */
bool GetNextQuestion( Database  *database,  Expression *expression_ptr )
{
  if (&(database->questions[database->question_index]) == database->last_question) return false;

  *expression_ptr = database->questions[database->question_index];
  ++database->question_index;
  return true;
}
