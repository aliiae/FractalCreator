#include "Renderer.h"
Renderer::Renderer(std::size_t Width, std::size_t Height)
	: width_(Width), height_(Height), pixels_size_{Width * Height * 4}, pitch_{int(Height) * 4} {
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
  texture_ = SDL_CreateTexture(sdl_renderer_, SDL_PIXELFORMAT_RGBA8888,
							   SDL_TEXTUREACCESS_STREAMING, Width, Height);
}
Renderer::~Renderer() {
  SDL_DestroyTexture(texture_);
  SDL_DestroyWindow(sdl_window_);
  SDL_Quit();
  pixels_pointer_ = NULL;
}
void Renderer::render(std::vector<unsigned char> &Pixels) {
  clearScreen();
  pixels_pointer_ = NULL;
  SDL_LockTexture(texture_, NULL, (void **)&pixels_pointer_, &pitch_);
  std::memcpy(pixels_pointer_, &Pixels[0], pixels_size_);
  SDL_UnlockTexture(texture_);
  pixels_pointer_ = NULL;

  SDL_RenderCopy(sdl_renderer_, texture_, NULL, NULL);
  SDL_RenderPresent(sdl_renderer_);
}
void Renderer::updateWindowTitle(Area<double> ZoomArea) {
  std::string Title{"Fractal Creator " + ZoomArea.toString()};
  SDL_SetWindowTitle(sdl_window_, Title.c_str());
}
void Renderer::clearScreen() const {
  SDL_SetRenderDrawColor(sdl_renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(sdl_renderer_);
}
