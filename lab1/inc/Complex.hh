#pragma once


#include <iostream>

/*!
 *  Plik zawiera definicje struktury Complex oraz zapowiedzi
 *  przeciazen operatorow arytmetycznych dzialajacych na tej 
 *  strukturze.
 */


/*!
 * Modeluje pojecie liczby zespolonej
 */
struct  Complex {
  double   re;    /*! Pole repezentuje czesc rzeczywista. */
  double   im;    /*! Pole repezentuje czesc urojona. */
};

// Sprzężenie i moduł liczby zespolonej
Complex conjugate(Complex complex);
Complex modulus(Complex complex);

// Sprawdź kolejny znak pod kątem zapisu liczby zespolonej
bool checkIfCorrectChar();


Complex  operator + (Complex  arg1,  Complex  arg2);
Complex  operator - (Complex  arg1,  Complex  arg2);
Complex  operator * (Complex  arg1,  Complex  arg2);
Complex  operator / (Complex  arg1,  Complex  arg2);
bool     operator== (Complex  arg1,  Complex  arg2);


// Przeciazenie strumieni wejścia i wyjścia
std::ostream& operator<<(std::ostream& stream, Complex& complex);
std::istream& operator>>(std::istream& stream, Complex& complex);
