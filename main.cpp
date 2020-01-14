#include "CalcList.hpp"
#include <iostream>


int main() {
  CalcList calculator;
  int choice;
  int input;
  bool running = true;

  #ifdef __linux__ 
    system("clear");
  #elif  __APPLE__ 
    system("clear");
  #elif _WIN32
    system("CLS");
  #else
  #endif

  while(running) {

    std::cout << "\nAvailable operations are:\n" << std::endl;

    std::cout << "(1) Addition" << std::endl;
    std::cout << "(2) Subtraction" << std::endl;
    std::cout << "(3) Multiplication" << std::endl;
    std::cout << "(4) Division" << std::endl;
    std::cout << "(5) Remove Last Operation" << std::endl;
    std::cout << "(6) Quit the program\n" << std::endl;

    std::cout << "The calculator's current total is: " << calculator.total() << std::endl;

    std::cin >> choice;
    std::cin.ignore();

    switch(choice) {
      case 1:
        std::cout << "Enter the number you would like to add: ";
        std::cin >> input;
        calculator.newOperation(ADDITION, input);
        break;

      case 2:
        std::cout << "Enter the number you would like to subtract: ";
        std::cin >> input;
        calculator.newOperation(SUBTRACTION, input);
        break;
        
      case 3:
        std::cout << "Enter the number you would like to multiply by: ";
        std::cin >> input;
        calculator.newOperation(MULTIPLICATION, input);
        break;
      
      case 4:
        std::cout << "Enter the number you would like to divide by: ";
        std::cin >> input;

        try {
          calculator.newOperation(DIVISION, input);
        }
        catch(const std::invalid_argument& e) {
          std::cout << "\nCannot divide by 0.\n" << std::endl;
        }
        break;

      case 5:
        try{
          calculator.removeLastOperation();
        }
        catch(const std::invalid_argument& e) {
          std::cout << "\nNo operations to remove.\n" << std::endl;
        }
        break;

      case 6:
        running = false;
        break;
      
      default:
        std::cout << "\nInvalid choice...\n" << std::endl;
    }
  }

  return 0;
}