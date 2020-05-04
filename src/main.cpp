#include "Creator.h"
#include <iostream>

int main() {
  std::string SelectedTypeLetter;
  int SelectedOrder;
  std::cout << "Please enter the letter of selected fractal type [M,B]:"
            << "\n"
            << "1. [M]andelbrot Set (default)"
            << "\n"
            << "2. [B]urning Ship" << std::endl;
  std::cin >> SelectedTypeLetter;
  if (SelectedTypeLetter.at(0) != 'M' && SelectedTypeLetter.at(0) != 'B') {
    std::cout << "Setting the fractal type to the default value M" << std::endl;
	SelectedTypeLetter = "M";
  }
  std::cout << "Please enter the fractal order (default 2):" << std::endl;
  std::cin >> SelectedOrder;
  if (SelectedOrder <= 0) {
    std::cout << "Setting the order to the default value 2" << std::endl;
    SelectedOrder = 2;
  }
  Creator("output.ppm", 1000, 1000, 512).draw(SelectedTypeLetter, SelectedOrder);
  return 0;
}