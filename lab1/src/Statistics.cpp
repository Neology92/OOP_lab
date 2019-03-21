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
        std::cout << "\033[1;32mDobrze!\033[0m" << std::endl;
    }else{
        Points::badAnswer();
        std::cout << "\033[1;31mZla odpowiedz.\033[0m Prawidlowy wynik: "<< pattern << std::endl;
    }
}
void Points::showResults(){
    std::cout << "Ilosc dobrych odpowiedzi: " << count << std::endl;
    std::cout << "Ilosc zlych odpowiedzi: " << pool-count << std::endl;
    std::cout << "Wynik procentowy: " << (float)(100*count/pool) << "%"<< std::endl;
}

