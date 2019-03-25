#include <iostream>

#include "Database.hh"
#include "Statistics.hh"


int main(int argc, char **argv)
{
  system("clear");

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
  
  // [DEBUG] end of program
  // return 1;
    
  std::cout << "\nStart testu arytmetyki zespolonej: " << argv[1] << std::endl;
  std::cout << std::endl;

  getchar();

  Expression   expression;

  while (GetNextQuestion(&base,&expression)) {
    
    int attempts = 3;
    int failed = 0;
    
    Complex pattern{0,0};
    Complex answer{0,0};

    system("clear");

    if(!Solve(expression, pattern)){
      getchar();
      continue;
      }

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
    getchar();
    getchar();
  }
  
  system("clear");

  std::cout << std::endl;
  std::cout << " Koniec testu" << std::endl;
  std::cout << std::endl;

  points.showResults();
}
