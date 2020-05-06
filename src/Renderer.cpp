#include <Renderer.h>

#include <string>

Renderer::Renderer(std::size_t width, std::size_t height)
    : width_(width),
      height_(height),
      pixels_size_{width * height * 4},
      pitch_{int(height) * 4} {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  sdl_window_ =
      SDL_CreateWindow("Fractal Creator", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
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
                               SDL_TEXTUREACCESS_STREAMING, width, height);
}
Renderer::~Renderer() {
  SDL_DestroyTexture(texture_);
  SDL_DestroyWindow(sdl_window_);
  SDL_Quit();
  delete pixels_pointer_;
}
void Renderer::Render(std::vector<unsigned char> &pixels) {
  ClearScreen();
  UpdateTexture(pixels);
  SDL_RenderCopy(sdl_renderer_, texture_, nullptr, nullptr);
  SDL_RenderPresent(sdl_renderer_);
}
void Renderer::UpdateTexture(const std::vector<unsigned char> &pixels) {
  pixels_pointer_ = nullptr;
  SDL_LockTexture(texture_, nullptr, (void **)&pixels_pointer_, &pitch_);
  std::memcpy(pixels_pointer_, &pixels[0], pixels_size_);
  SDL_UnlockTexture(texture_);
  pixels_pointer_ = nullptr;
}
void Renderer::UpdateWindowTitle(const std::string &title) {
  SDL_SetWindowTitle(sdl_window_, title.c_str());
}
void Renderer::ClearScreen() const {
  SDL_SetRenderDrawColor(sdl_renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(sdl_renderer_);
}
Renderer &Renderer::operator=(Renderer &&other) noexcept {
  if (&other == this) {
    return *this;
  }
  std::swap(sdl_window_, other.sdl_window_);
  std::swap(sdl_renderer_, other.sdl_renderer_);
  std::swap(texture_, other.texture_);
  std::swap(pixels_pointer_, other.pixels_pointer_);
  return *this;
}
Renderer::Renderer(Renderer &&other) noexcept
    : sdl_window_(std::exchange(other.sdl_window_, nullptr)),
      sdl_renderer_(std::exchange(other.sdl_renderer_, nullptr)),
      texture_(std::exchange(other.texture_, nullptr)),
      pixels_pointer_(std::exchange(other.pixels_pointer_, nullptr)),
      width_(other.width_),
      height_(other.height_),
      pixels_size_(other.pixels_size_),
      pitch_(other.pitch_) {}
