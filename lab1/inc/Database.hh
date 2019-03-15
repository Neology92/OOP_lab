#pragma once


#include "Expression.hh"


/*
 * Modeluje pojecie bazy testu z zestawem pytan w tablicy
 * oraz informacji o maksymalnej ilosci pytan, jak
 * tez indeksem nastepnego pytania, ktore ma byc pobrane
 * z bazy.
 */
struct Database {
  Expression   *test_array_ptr;     /* Wskaznik na tablice zawierajaca pytania testu */
  unsigned int number_of_questions; /* Ilosc wszystkich pytan */
  unsigned int question_index;      /* Numer pytania, ktore ma byc pobrane jako nastepne */
};


/*
* Ustawia test
*/
void SetTest(Database *database_ptr, Expression *test_array_ptr, unsigned int number_of_questions);


/*
 * Inicjalizuje test powiazany z dana nazwa.
 */
bool Init( Database  *database_ptr, const char*  test_name );

/*
 * Udostepnia nastepne pytanie z bazy.
 */
bool GetNextQuestion( Database  *database_ptr,  Expression *expression_ptr );

