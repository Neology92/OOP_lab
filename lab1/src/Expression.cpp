#include <iostream>

#include "Expression.hh"


/*!
 * Oblicza wyrażenie złożone z dwóch liczb zespolonych i symbolu operacji.
 * Argumenty:
 *    expr - wyrażenie liczb zespolonych,
 * Zwraca:
 *    Wynik - jako liczbę zespoloną.
 */
Complex Solve(Expression  expr)
{
    Complex result{0,0};

    switch (expr.op)
    {
        case kAddition: 
            result = expr.arg1 + expr.arg2;
          break;

        case kSubtraction:
            result = expr.arg1 - expr.arg2;
          break;
        
        case kMultiplication:
            result = expr.arg1 * expr.arg2;
          break;

        case kDivision:
            result = expr.arg1 / expr.arg2;
          break;

        default:
            std::cerr << "Error: Unknown operator in expression!" << std::endl;
          break;
    }

    return result;
}


/*!
 * Pozwala wypisać dziłanie na liczbach zespolonych.
 * Argumenty:
 *    arg1 - strumień wyjścia,
 *    arg2 - wyrażenie.
 * Zwraca:
 *    strumień z wyrażeniem.
 */
std::ostream& operator<<(std::ostream& stream, Expression& expression)
{
  stream << expression.arg1;

  switch (expression.op)
  {
    case kAddition:
      stream << " + ";
      break;

    case kSubtraction:
      stream << " - ";
      break;
    
    case kMultiplication:
      stream << " * ";
      break;

    case kDivision:
      stream << " / ";
      break;

    default:
        std::cerr << "Error: Wrong operation symbol in expression!";
        stream.clear();
        return stream;
      break;
  }

  stream << expression.arg2;

  return stream;
}