#include <Renderer.h>
#include <Controller.h>
#include "Creator.h"

std::shared_ptr<Fractal> selectFractal(std::string &SelectedTypeLetter, int MaxIterations) {
  int SelectedOrder;
  std::shared_ptr<Fractal> SelectedFractal;
  std::cout << "Please choose the fractal type [M,B]:"
			<< "\n"
			<< "1. [M]andelbrot Set (default)"
			<< "\n"
			<< "2. [B]urning Ship" << std::endl;
  std::cin >> SelectedTypeLetter;
  if (SelectedTypeLetter.at(0)!='B') {
	if (SelectedTypeLetter.at(0)!='M') {
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
  return SelectedFractal;
}

int main() {
  const int MaxIterations = 512;
  const int ImageWidth = 640;
  const int ImageHeight = 640;

  std::string SelectedTypeLetter;
  std::shared_ptr<Fractal> SelectedFractal = selectFractal(SelectedTypeLetter, MaxIterations);
  Creator FractalCreator = Creator( ImageWidth, ImageHeight,
								   MaxIterations, SelectedFractal);
  Renderer Renderer(ImageWidth, ImageHeight);
  Controller Controller(SelectedFractal);

  std::vector<unsigned char> NewPixels = FractalCreator.getPixels();
  Renderer.render(NewPixels);
  Renderer.updateWindowTitle(SelectedFractal->getArea());

  bool Running{true};
  SDL_Event Event;
  while (Running) {
	while (SDL_PollEvent(&Event)) {
	  if (Event.type==SDL_QUIT) {
		Running = false;
		break;
	  } else if (Event.type==SDL_KEYDOWN) {
		if (Controller.changeZoom(Event)) {
		  NewPixels = FractalCreator.getPixels();
		  Renderer.render(NewPixels);
		  Renderer.updateWindowTitle(SelectedFractal->getArea());
		}
	  }
	}
  }
  return 0;
}