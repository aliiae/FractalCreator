#include "Creator.h"
#include <iostream>

int main() {
  int SelectedTypeNumber{0};
  while (SelectedTypeNumber <= 0 || SelectedTypeNumber > 2) {
    std::cout << "Please enter the number of fractal type:"
              << "\n"
              << "1. Mandelbrot set [default]"
              << "\n"
              << "2. Burning ship"
              << "\n";
    std::cin >> SelectedTypeNumber;
  }
  Creator("output.ppm", 1000, 1000, 512).draw(SelectedTypeNumber);
  return 0;
}