#include "Renderer.h"
Renderer::Renderer(std::size_t Width, std::size_t Height)
    : width_(Width),
      height_(Height), pixels_size_{Width * Height * 4}, pitch_{int(Height) *
                                                                4} {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  sdl_window_ =
      SDL_CreateWindow("Fractal Creator", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);
  if (sdl_window_ == nullptr) {
    std::cerr << "Window could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer_) {
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
  delete pixels_pointer_;
}
void Renderer::render(std::vector<unsigned char> &Pixels) {
  clearScreen();
  pixels_pointer_ = nullptr;
  SDL_LockTexture(texture_, nullptr, (void **)&pixels_pointer_, &pitch_);
  std::memcpy(pixels_pointer_, &Pixels[0], pixels_size_);
  SDL_UnlockTexture(texture_);
  pixels_pointer_ = nullptr;

  SDL_RenderCopy(sdl_renderer_, texture_, nullptr, nullptr);
  SDL_RenderPresent(sdl_renderer_);
}
void Renderer::updateWindowTitle(const std::string &Title) {
  SDL_SetWindowTitle(sdl_window_, Title.c_str());
}
void Renderer::clearScreen() const {
  SDL_SetRenderDrawColor(sdl_renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(sdl_renderer_);
}
Renderer &Renderer::operator=(Renderer &&Other) noexcept {
  if (&Other == this) {
    return *this;
  }
  std::swap(sdl_window_, Other.sdl_window_);
  std::swap(sdl_renderer_, Other.sdl_renderer_);
  std::swap(texture_, Other.texture_);
  std::swap(pixels_pointer_, Other.pixels_pointer_);
  return *this;
}
Renderer::Renderer(Renderer &&Other) noexcept
    : sdl_window_(std::exchange(Other.sdl_window_, nullptr)),
      sdl_renderer_(std::exchange(Other.sdl_renderer_, nullptr)),
      texture_(std::exchange(Other.texture_, nullptr)),
      pixels_pointer_(std::exchange(Other.pixels_pointer_, nullptr)),
      width_(Other.width_), height_(Other.height_),
      pixels_size_(Other.pixels_size_), pitch_(Other.pitch_) {}
