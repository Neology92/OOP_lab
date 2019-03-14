#include <iostream>

#include "Statistics.hh"

/*!
* Plik zawiera definicje metod zawartych w klasie Points
*/

Points::Points(){
    count = 0;
    pool = 0;
}
void Points::goodAnswer(){
    pool++;
    count++;
}
void Points::badAnswer(){
    pool++;
}
void Points::check(Complex pattern, Complex answer){
    if(pattern == answer){
        Points::goodAnswer();
        std::cout << "Dobrze!" << std::endl;
    }else{
        Points::badAnswer();
        std::cout << "Zla odpowiedz. Prawidlowy wynik: "<< pattern << std::endl;
    }
}
void Points::showResults(){
    std::cout << "Ilosc dobrych odpowiedzi: " << count << std::endl;
    std::cout << "Ilosc zlych odpowiedzi: " << pool-count << std::endl;
    std::cout << "Wynik procentowy: " << (float)(100*count/pool) << "%"<< std::endl;
}