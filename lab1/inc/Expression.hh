#pragma once

#include "Complex.hh"


/*!
 * Dzieli text na fragmenty, według podanego znaku
 */
void slice(std::string &text, std::string sliced[], char ch);


/*!
 * Modeluje zbior operatorow arytmetycznych.
 */
enum Operator { kIncorrect=-1, kAddition, kSubtraction, kMultiplication, kDivision };


/*!
 * Modeluje pojecie dwuargumentowego wyrazenia zespolonego
 */
struct Expression {
  Complex   arg1;   // Pierwszy argument wyrazenia arytmetycznego
  Operator  op;     // Opertor wyrazenia arytmetycznego
  Complex   arg2;   // Drugi argument wyrazenia arytmetycznego
};


/*!
 * Oblicza wyrażene z liczb zespolonych
 */
bool Solve(Expression  expr, Complex &solution);


// Przeciążenie operatora strumienia wyjścia
std::ostream& operator<<(std::ostream& stream, Expression& expression);