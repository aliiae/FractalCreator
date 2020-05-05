#include "Creator.h"
#include <iostream>
#include <unordered_map>
const int MaxIterations = 256;
const int ImageWidth = 1000;
const int ImageHeight = 1000;

int main() {
  std::string SelectedTypeLetter;
  int SelectedOrder;
  std::shared_ptr<Fractal> SelectedFractal;
  std::cout << "Please choose the fractal type [M,B]:"
            << "\n"
            << "1. [M]andelbrot Set (default)"
            << "\n"
            << "2. [B]urning Ship" << std::endl;
  std::cin >> SelectedTypeLetter;
  if (SelectedTypeLetter.at(0) != 'B') {
    if (SelectedTypeLetter.at(0) != 'M') {
      std::cout << "Setting the fractal type to the default value M"
                << std::endl;
    }
    SelectedFractal = std::make_shared<MandelbrotSet>(MaxIterations);
  } else {
    SelectedFractal = std::make_shared<BurningShip>(MaxIterations);
  }
  std::cout << "Please choose the fractal order (default 2):" << std::endl;
  std::cin >> SelectedOrder;
  if (SelectedOrder <= 0) {
    std::cout << "Setting the order to the default value 2" << std::endl;
    SelectedOrder = 2;
  }
  SelectedFractal->setOrder(SelectedOrder);
  Creator FractalCreator = Creator("output.ppm", ImageWidth, ImageHeight,
                                   MaxIterations, SelectedFractal);
  FractalCreator.draw();
  return 0;
}