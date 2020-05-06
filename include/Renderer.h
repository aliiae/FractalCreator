#ifndef FRACTALCREATOR_INCLUDE_RENDERER_H_
#define FRACTALCREATOR_INCLUDE_RENDERER_H_
#include <Creator.h>
#include <SDL.h>

#include <iostream>
#include <utility>
#include <vector>

class Renderer {
 public:
  Renderer(const std::size_t width, const std::size_t height);
  ~Renderer();
  Renderer(Renderer &other) = delete;
  Renderer &operator=(const Renderer &other) = delete;
  Renderer(Renderer &&other) noexcept;
  Renderer &operator=(Renderer &&other) noexcept;

  void Render(std::vector<unsigned char> &pixels);
  void UpdateWindowTitle(const std::string &title);

 private:
  int pitch_;
  SDL_Texture *texture_;
  SDL_Window *sdl_window_;
  SDL_Renderer *sdl_renderer_;
  int *pixels_pointer_{nullptr};
  void ClearScreen() const;
  unsigned long pixels_size_;
  const std::size_t width_{};
  const std::size_t height_{};
  void UpdateTexture(const std::vector<unsigned char> &pixels);
};
#endif  // FRACTALCREATOR_INCLUDE_RENDERER_H_
