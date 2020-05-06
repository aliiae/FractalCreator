#include <BurningShip.h>
#include <Controller.h>
#include <Creator.h>
#include <MandelbrotSet.h>
#include <Renderer.h>

#include <iostream>
#include <map>

std::shared_ptr<Fractal> SelectFractalType(int max_iterations);
bool EscapeWasPressed(const SDL_Event &event);

std::string GetTitle(std::shared_ptr<Fractal> &selected_fractal);
int main() {
  const int kMaxIterations = 256;
  const int kWidth = 640;
  const int kHeight = 640;

  std::shared_ptr<Fractal> selected_fractal = SelectFractalType(kMaxIterations);
  Creator fractal_creator =
      Creator(kWidth, kHeight, kMaxIterations, selected_fractal);
  Renderer renderer(kWidth, kHeight);
  Controller controller(selected_fractal);

  std::vector<unsigned char> new_pixels = fractal_creator.GetPixels();
  renderer.Render(new_pixels);
  renderer.UpdateWindowTitle(GetTitle(selected_fractal));

  bool running{true};
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (EscapeWasPressed(event)) {
        running = false;
        break;
      } else if (event.type == SDL_KEYDOWN) {
        if (controller.ChangeZoom(event)) {
          new_pixels = fractal_creator.GetPixels();
          renderer.Render(new_pixels);
          renderer.UpdateWindowTitle(GetTitle(selected_fractal));
        }
      }
    }
  }
  return 0;
}
std::string GetTitle(std::shared_ptr<Fractal> &selected_fractal) {
  const std::string &title =
      selected_fractal->GetName() + " " + selected_fractal->GetZoomAreaString();
  return title;
}

bool EscapeWasPressed(const SDL_Event &event) {
  return event.type == SDL_QUIT ||
         (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE);
}
std::shared_ptr<Fractal> SelectFractalType(const int max_iterations) {
  char default_choice = 'M';
  std::string selected_type_letter;
  std::map<char, std::function<std::shared_ptr<Fractal>()>> input_letter_map = {
      {default_choice,
       [max_iterations]() {
         return std::make_shared<MandelbrotSet>(max_iterations);
       }},
      {'B', [max_iterations]() {
         return std::make_shared<BurningShip>(max_iterations);
       }}};
  std::unique_ptr<Fractal> selected_fractal;
  std::cout
      << "Please choose the fractal type you would like to explore (default "
      << default_choice << "):\n"
      << "1. [M]andelbrot Set\n"
      << "2. [B]urning Ship" << std::endl;
  std::cin >> selected_type_letter;
  if (input_letter_map.find(selected_type_letter.at(0)) !=
      input_letter_map.end()) {
    return input_letter_map[selected_type_letter.at(0)]();
  }
  std::cout << "Setting the fractal type to the default value "
            << default_choice << std::endl;
  return input_letter_map[default_choice]();
}
