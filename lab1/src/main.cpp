#include <iostream>

#include "Database.hh"



int main(int argc, char **argv)
{

  if (argc < 2) {
    std::cout << std::endl;
    std::cout << " Brak opcji okreslajacej rodzaj testu." << std::endl;
    std::cout << " Dopuszczalne nazwy to:  latwy, trudny." << std::endl;
    std::cout << std::endl;
    return 1;
  }


  Database   base = { nullptr, 0, 0 };

  if (Init(&base,argv[1]) == false) {
    std::cerr << " Inicjalizacja testu nie powiodla sie." << std::endl;
    return 1;
  }


  
  std::cout << std::endl;
  std::cout << " Start testu arytmetyki zespolonej: " << argv[1] << std::endl;
  std::cout << std::endl;

  Expression   expression;
  
  while (GetNextQuestion(&base,&expression)) {
    Complex complex{0,0};
    
    std::cout << "Podaj wynik operacji: ";
    std::cout << expression << " = ";

    std::cin >> complex;
    std::cout << complex << std::endl;
  }

  
  std::cout << std::endl;
  std::cout << " Koniec testu" << std::endl;
  std::cout << std::endl;

}
