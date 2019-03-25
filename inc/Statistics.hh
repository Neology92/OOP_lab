#pragma once

#include "Complex.hh"

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