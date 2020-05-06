#ifndef FRACTALCREATOR_INCLUDE_RENDERER_H
#define FRACTALCREATOR_INCLUDE_RENDERER_H
#include <Creator.h>
#include <SDL.h>
#include <iostream>
#include <utility>
#include <vector>

class Renderer {
public:
  Renderer(const std::size_t Width, const std::size_t Height);
  ~Renderer();
  Renderer(Renderer &Other) = delete;
  Renderer &operator=(const Renderer &Other) = delete;
  Renderer(Renderer &&Other) noexcept;
  Renderer &operator=(Renderer &&Other) noexcept;

  void render(std::vector<unsigned char> &Pixels);
  void updateWindowTitle(const std::string &Title);

private:
  int pitch_;
  SDL_Texture *texture_;
  SDL_Window *sdl_window_;
  SDL_Renderer *sdl_renderer_;
  int *pixels_pointer_{nullptr};
  void clearScreen() const;
  unsigned long pixels_size_;
  const std::size_t width_{};
  const std::size_t height_{};
};
#endif // FRACTALCREATOR_INCLUDE_RENDERER_H
