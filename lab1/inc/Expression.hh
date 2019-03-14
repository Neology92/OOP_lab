#pragma once

#include "Complex.hh"

/*!
 * Modeluje zbior operatorow arytmetycznych.
 */
enum Operator { kAddition, kSubtraction, kMultiplication, kDivision };


/*!
 * Modeluje pojecie dwuargumentowego wyrazenia zespolonego
 */
struct Expression {
  Complex   arg1;   // Pierwszy argument wyrazenia arytmetycznego
  Operator  op;     // Opertor wyrazenia arytmetycznego
  Complex   arg2;   // Drugi argument wyrazenia arytmetycznego
};


Complex Solve(Expression  expr);


// Przeciążenie operatora strumienia wyjścia
std::ostream& operator<<(std::ostream& stream, Expression& expression);