#pragma once

#include <vector>
#include <fstream>
#include "Expression.hh"


/*
 * Modeluje pojecie bazy testu z zestawem pytan w tablicy
 * oraz informacji o maksymalnej ilosci pytan, jak
 * tez indeksem nastepnego pytania, ktore ma byc pobrane
 * z bazy.
 */
struct Database {
  unsigned int question_index;      /* Numer pytania, ktore ma byc pobrane jako nastepne */
  Expression *last_question;        /* Wskaźnik na ostatni element */
  std::vector<Expression> questions;
};


/*
* Wczytuje pytania z pliku.
*/
bool SetTest(Database &database_ptr, std::string &file_path);


/*
 * Inicjalizuje test powiazany z dana nazwa.
 */
bool Init( Database &database_ptr, const char *test_name );

/*
 * Udostepnia nastepne pytanie z bazy.
 */
bool GetNextQuestion( Database  *database_ptr,  Expression *expression_ptr );

