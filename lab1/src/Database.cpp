#include <iostream>
#include <cstring>
#include <cassert>

#include "Database.hh"

using namespace std;

/*
 * Tablica, ktora jest widoczna tylko w tym module.
 * Zawiera ona tresc latwego testu.
 */
static Expression  easy_test[] =
  { {{2,1}, kAddition, {1,2}},
    {{1,0}, kSubtraction, {0,1}},
    {{3,0}, kMultiplication, {0,3}},
    {{4,8}, kDivision, {1,0}},
  };

/*
 * Analogicznie zdefiniuj test "trudne"
 *
 */
static Expression  hard_test[] =
  { {{ 1.1, 5.5}, kMultiplication, { 2.3, 4.1}},
    {{ 2, 2},     kDivision,       { 2,-1}},
    {{ 4.3,-1.1}, kMultiplication, { 7.2, 2.4}},
    {{-1.5, 6.0}, kDivision,       {-5.0,-1.2}},
  };


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
void SetTest(Database *database_ptr, Expression *test_array_ptr, unsigned int number_of_questions)
{
  database_ptr->test_array_ptr = test_array_ptr;
  database_ptr->number_of_questions = number_of_questions;
  database_ptr->question_index = 0;
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
bool Init( Database  *database_ptr, const char*  test_name )
{
  if (!strcmp(test_name,"latwy")) {
    SetTest(database_ptr,easy_test,sizeof(easy_test)/sizeof(Expression));
    return true;
  }
  else if (!strcmp(test_name,"trudny")) {
    SetTest(database_ptr,hard_test,sizeof(hard_test)/sizeof(Expression));
    return true;
  }

  cerr << "Otwarcie testu '" << test_name << "' nie powiodlo sie." << endl;
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
bool GetNextQuestion( Database  *database_ptr,  Expression *expression_ptr )
{
  if (database_ptr->question_index >= database_ptr->number_of_questions) return false;

  *expression_ptr = database_ptr->test_array_ptr[database_ptr->question_index];
  ++database_ptr->question_index;
  return true;
}
