#include "Creator.h"
#include "FractalType.h"
#include <iostream>

int main() {
  int SelectedTypeNumber;
  while (SelectedTypeNumber <= 0 || SelectedTypeNumber > 2) {
    std::cout << "Please enter the number of fractal type:" << std::endl
              << "1. Mandelbrot set [default]" << std::endl
              << "2. Burning ship" << std::endl;
    std::cin >> SelectedTypeNumber;
  }
  Creator("output.ppm", 1000, 1000, 255).draw(SelectedTypeNumber);
  return 0;
}