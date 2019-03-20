#include <iostream>
#include <sstream>

#include "Expression.hh"

  
/*!
 * Dzieli linię tekstu według podanego symbolu.
 * Argumenty:
 *    text - text do podzielenia,
 *    sliced[] - tablica, do której zostaną wpisane oddzielone frazy
 *    ch - symbol, według którego nastąpi podział
 * Założenia:
 *    Przekazana tablica musi musi być na tyle duża, aby pomieściła podzieloną frazę
 */
void slice(std::string &text, std::string sliced[], char ch)
{
    int i = 0;
    std::stringstream sstream;
    sstream << text;
    while(getline(sstream, sliced[i], ch))
    {
      i++;
    }
}
  
/*!
 * Oblicza wyrażenie złożone z dwóch liczb zespolonych i symbolu operacji.
 * Argumenty:
 *    expr - wyrażenie liczb zespolonych,
 *    solution - docelowy pojemnik do przekazania wyniku
 * Zwraca:
 *    Bool - czy udało się rozwiązać.
 */
bool Solve(Expression  expr, Complex &solution)
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
            return false;
          break;
    }

    solution = result;
    return true;
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