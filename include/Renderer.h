#ifndef FRACTALCREATOR_INCLUDE_RENDERER_H
#define FRACTALCREATOR_INCLUDE_RENDERER_H
#include <utility>
#include <vector>
#include <iostream>
#include "SDL.h"
#include "Creator.h"

class Renderer {
public:
  Renderer(const std::size_t Width, const std::size_t Height)
	  : width_(Width), height_(Height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	  std::cerr << "SDL could not initialize.\n";
	  std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
	}
	sdl_window_ = SDL_CreateWindow("Fractal Creator", SDL_WINDOWPOS_CENTERED,
								   SDL_WINDOWPOS_CENTERED, Width,
								   Height, SDL_WINDOW_SHOWN);
	if (sdl_window_==nullptr) {
	  std::cerr << "Window could not be created.\n";
	  std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
	}
	sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
	if (nullptr==sdl_renderer_) {
	  std::cerr << "Renderer could not be created.\n";
	  std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
	}
	pixels_.resize(Width * Height * 4, 0);
	texture_ = SDL_CreateTexture(sdl_renderer_, SDL_PIXELFORMAT_RGBA8888,
								 SDL_TEXTUREACCESS_STATIC, Width, Height);
  };
  ~Renderer() {
	SDL_DestroyTexture(texture_);
	SDL_DestroyWindow(sdl_window_);
	SDL_Quit();
  };
  Renderer(Renderer &Other) = delete;

  void render(std::vector<unsigned char> &Pixels) {
	int Pitch{static_cast<int>(width_ * 4)};
	SDL_SetRenderDrawColor( sdl_renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE );
	SDL_RenderClear( sdl_renderer_ );
	SDL_UpdateTexture(texture_, NULL, &Pixels[0], Pitch);
	SDL_RenderCopy(sdl_renderer_, texture_, NULL, NULL);
	SDL_RenderPresent(sdl_renderer_);
  };

  void updateWindowTitle(Area<double> ZoomArea) {
	std::string Title{"Fractal Creator " + ZoomArea.toString()};
	SDL_SetWindowTitle(sdl_window_, Title.c_str());
  };

private:
  SDL_Window *sdl_window_;
  SDL_Renderer *sdl_renderer_;
  SDL_Texture *texture_;

  const std::size_t width_{};
  const std::size_t height_{};
  std::vector<unsigned char> pixels_;
};
#endif //FRACTALCREATOR_INCLUDE_RENDERER_H
