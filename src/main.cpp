#include "Creator.h"
#include <iostream>
#include <BurningShip.h>
#include <MandelbrotSet.h>
#include <map>

int main() {
  const int MaxIterations = 256;
  const int ImageWidth = 1000;
  const int ImageHeight = 1000;
  const std::string OutputPath = "output.ppm";
  char DefaultChoice = 'M';

  std::map<char, std::function<std::unique_ptr<Fractal>()>> InputLetterMap =
	  {
		  {DefaultChoice, [MaxIterations]() { return std::make_unique<MandelbrotSet>(MaxIterations); }},
		  {'B', [MaxIterations]() { return std::make_unique<BurningShip>(MaxIterations); }}
	  };

  std::string SelectedTypeLetter;
  int SelectedOrder;
  std::unique_ptr<Fractal> SelectedFractal;
  std::cout << "Please choose the fractal type [M,B]:"
			<< "\n"
			<< "1. [M]andelbrot Set (default)"
			<< "\n"
			<< "2. [B]urning Ship" << std::endl;
  std::cin >> SelectedTypeLetter;
  if (InputLetterMap.find(SelectedTypeLetter.at(0)) != InputLetterMap.end()) {
	SelectedFractal = InputLetterMap[SelectedTypeLetter.at(0)]();
  } else {
	std::cout << "Setting the fractal type to the default value " << DefaultChoice
			  << std::endl;
	SelectedFractal = InputLetterMap[DefaultChoice]();
  }

  std::cout << "Please choose the fractal order (default 2):" << std::endl;
  std::cin >> SelectedOrder;
  if (SelectedOrder <= 0) {
	std::cout << "Setting the order to the default value 2" << std::endl;
	SelectedOrder = 2;
  }
  SelectedFractal->setOrder(SelectedOrder);
  Creator FractalCreator = Creator(OutputPath, ImageWidth, ImageHeight,
								   MaxIterations, std::move(SelectedFractal));
  FractalCreator.draw();
  return 0;
}