#include <iostream>

#include "Database.hh"
#include "Statistics.hh"


int main(int argc, char **argv)
{

  if (argc < 2) {
    std::cout << std::endl;
    std::cout << " Brak opcji okreslajacej rodzaj testu." << std::endl;
    std::cout << " Dopuszczalne nazwy to:  latwy, trudny." << std::endl;
    std::cout << std::endl;
    return 1;
  }


  Database   base = { 0, nullptr };

  if (Init(base,argv[1]) == false) {
    std::cerr << " Inicjalizacja testu nie powiodla sie." << std::endl;
    return 1;
  }

  Points points;  // Deklaracja obiektu podliczającego punkty użytkownika
  
  std::cout << std::endl;
  std::cout << " Start testu arytmetyki zespolonej: " << argv[1] << std::endl;
  std::cout << std::endl;

  Expression   expression;
  
  while (GetNextQuestion(&base,&expression)) {
    
    int attempts = 3;
    int failed = 0;
    
    Complex pattern{0,0};
    Complex answer{0,0};

    if(!Solve(expression, pattern))
      continue;

    std::cout << "Podaj wynik operacji: ";
    std::cout << expression << " = ";

    do{
      failed = 0;
      std::cin >> answer;
      attempts--;

      if(std::cin.fail())
      {
        failed = 1;
        std::cerr << "Error: Wrong format! Write again." << std::endl;
      }
      std::cin.clear();

    }while(failed && attempts);

    points.check(pattern, answer);
  }
  
  std::cout << std::endl;
  std::cout << " Koniec testu" << std::endl;
  std::cout << std::endl;

  points.showResults();

}
