#ifndef FRACTALCREATOR_INCLUDE_RENDERER_H
#define FRACTALCREATOR_INCLUDE_RENDERER_H
#include <utility>
#include <vector>
#include <iostream>
#include "SDL.h"
#include "Creator.h"

class Renderer {
public:
  Renderer(const std::size_t Width, const std::size_t Height);
  ~Renderer();
  Renderer(Renderer &Other) = delete;
  void render(std::vector<unsigned char> &Pixels);
  void updateWindowTitle(const std::string& Title);

private:
  SDL_Window *sdl_window_;
  SDL_Renderer *sdl_renderer_;
  SDL_Texture *texture_;
  const std::size_t width_{};
  const std::size_t height_{};
  int *pixels_pointer_{NULL};
  unsigned long pixels_size_;
  int pitch_;

  void clearScreen() const;
};
#endif //FRACTALCREATOR_INCLUDE_RENDERER_H
