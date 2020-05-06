#include <BurningShip.h>
#include <Controller.h>
#include <Creator.h>
#include <MandelbrotSet.h>
#include <Renderer.h>
#include <iostream>
#include <map>

std::shared_ptr<Fractal> selectFractalType(int MaxIterations);
bool escapeWasPressed(const SDL_Event &Event);

std::string getTitle(std::shared_ptr<Fractal> &SelectedFractal);
int main() {
  const int MaxIterations = 256;
  const int Width = 640;
  const int Height = 640;

  std::shared_ptr<Fractal> SelectedFractal = selectFractalType(MaxIterations);
  Creator FractalCreator =
      Creator(Width, Height, MaxIterations, SelectedFractal);
  Renderer Renderer(Width, Height);
  Controller Controller(SelectedFractal);

  std::vector<unsigned char> NewPixels = FractalCreator.getPixels();
  Renderer.render(NewPixels);
  Renderer.updateWindowTitle(getTitle(SelectedFractal));

  bool Running{true};
  SDL_Event Event;
  while (Running) {
    while (SDL_PollEvent(&Event)) {
      if (escapeWasPressed(Event)) {
        Running = false;
        break;
      } else if (Event.type == SDL_KEYDOWN) {
        if (Controller.changeZoom(Event)) {
          NewPixels = FractalCreator.getPixels();
          Renderer.render(NewPixels);
          Renderer.updateWindowTitle(getTitle(SelectedFractal));
        }
      }
    }
  }
  return 0;
}
std::string getTitle(std::shared_ptr<Fractal> &SelectedFractal) {
  const std::string &Title =
      SelectedFractal->getName() + " " + SelectedFractal->getZoomAreaString();
  return Title;
}

bool escapeWasPressed(const SDL_Event &Event) {
  return Event.type == SDL_QUIT ||
         (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE);
}
std::shared_ptr<Fractal> selectFractalType(const int MaxIterations) {
  char DefaultChoice = 'M';
  std::string SelectedTypeLetter;
  std::__1::map<char, std::function<std::shared_ptr<Fractal>()>>
      InputLetterMap = {{DefaultChoice,
                         [MaxIterations]() {
                           return std::make_shared<MandelbrotSet>(
                               MaxIterations);
                         }},
                        {'B', [MaxIterations]() {
                           return std::make_shared<BurningShip>(MaxIterations);
                         }}};
  std::__1::unique_ptr<Fractal> SelectedFractal;
  std::cout
      << "Please choose the fractal type you would like to explore (default "
      << DefaultChoice << "):\n"
      << "1. [M]andelbrot Set\n"
      << "2. [B]urning Ship" << std::endl;
  std::cin >> SelectedTypeLetter;
  if (InputLetterMap.find(SelectedTypeLetter.at(0)) != InputLetterMap.end()) {
    return InputLetterMap[SelectedTypeLetter.at(0)]();
  }
  std::cout << "Setting the fractal type to the default value " << DefaultChoice
            << std::endl;
  return InputLetterMap[DefaultChoice]();
}
