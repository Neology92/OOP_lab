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


/*!
* Modeluje pojęcie wyniku użytkownika
*/
class Points
{
  private:
    int count;          // Zdobyte punkty
    int pool;           // Pula punktów
    
    void goodAnswer();    // Dodaje punkt zaliczony
    void badAnswer();     // Dodaje punkt niezaliczony
    
  public:
    Points();                                 // Konstruktor
    void check(Complex c1, Complex c2);       // Sprawdza czy zaliczyć punkt
    void showResults();                       // Pokazuje wyniki na standardowe wyjście  
};


Complex Solve(Expression  expr);


// Przeciążenie operatora strumienia wyjścia
std::ostream& operator<<(std::ostream& stream, Expression& expression);