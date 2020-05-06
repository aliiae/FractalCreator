#include <Renderer.h>
#include <Controller.h>
#include "Creator.h"
#include <iostream>
#include <BurningShip.h>
#include <MandelbrotSet.h>
#include <map>

std::shared_ptr<Fractal> selectFractalType(int MaxIterations);
int main() {
  const int MaxIterations = 256;
  const int ImageWidth = 800;
  const int ImageHeight = 800;

  std::shared_ptr<Fractal> SelectedFractal = selectFractalType(MaxIterations);
  Creator FractalCreator = Creator(ImageWidth, ImageHeight,
								   MaxIterations, SelectedFractal);
  Renderer Renderer(ImageWidth, ImageHeight);
  Controller Controller(SelectedFractal);
  const std::string &Title = SelectedFractal->getName() + " " + SelectedFractal->getZoomAreaString();

  std::vector<unsigned char> NewPixels = FractalCreator.getPixels();
  Renderer.render(NewPixels);
  Renderer.updateWindowTitle(Title);

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
		  Renderer.updateWindowTitle(Title);
		}
	  }
	}
  }
  return 0;
}

std::shared_ptr<Fractal> selectFractalType(const int MaxIterations) {
  char DefaultChoice = 'M';
  std::string SelectedTypeLetter;
  std::__1::map<char, std::function<std::shared_ptr<Fractal>()>> InputLetterMap =
	  {
		  {DefaultChoice, [MaxIterations]() { return std::make_shared<MandelbrotSet>(MaxIterations); }},
		  {'B', [MaxIterations]() { return std::make_shared<BurningShip>(MaxIterations); }}
	  };
  std::__1::unique_ptr<Fractal> SelectedFractal;
  std::cout << "Please choose the fractal type (default " << DefaultChoice << "):\n"
			<< "1. [M]andelbrot Set\n"
			<< "2. [B]urning Ship" << std::endl;
  std::cin >> SelectedTypeLetter;
  if (InputLetterMap.find(SelectedTypeLetter.at(0))!=InputLetterMap.end()) {
	return InputLetterMap[SelectedTypeLetter.at(0)]();
  }
  std::cout << "Setting the fractal type to the default value " << DefaultChoice
			<< std::endl;
  return InputLetterMap[DefaultChoice]();
}
