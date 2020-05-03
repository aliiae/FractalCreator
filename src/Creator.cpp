#include "Creator.h"
#include "Area.h"
#include "BurningShipFractal.h"
#include "Fractal.h"
#include "MandelbrotSetFractal.h"
#include <iostream>
#include <memory>

int Creator::getWidth() const { return width_; }
void Creator::setWidth(float Width) { width_ = Width; }
int Creator::getHeight() const { return height_; }
void Creator::setHeight(float Height) { height_ = Height; }
const std::string &Creator::getImagePath() const { return image_path_; }
void Creator::setImagePath(const std::string &ImagePath) {
  image_path_ = ImagePath;
}

void Creator::draw() {
  Area<int> Screen(0, width_, 0, height_);
  std::cout << "Generating a fractal with max " << max_iterations_
            << " iterations";
  clock_t Start = clock();
  Image Colors(width_, height_);
  auto Fractal = BurningShipFractal(max_iterations_);
//    auto Fractal = MandelbrotSetFractal(max_iterations_);
  for (int Ix = 0; Ix < Screen.width(); ++Ix)
    for (int Iy = 0; Iy < Screen.height(); ++Iy) {
      int Iterations =
          Fractal.getIterations(utils::Coordinate{Iy, Ix}, Screen, Colors);
      Colors(Ix, Iy) = double(Iterations) / double(max_iterations_);
    }
  clock_t Stop = clock();
  std::cout << " (" << (double(Stop - Start) / CLOCKS_PER_SEC) << " seconds)"
            << std::endl;
  std::cout << "Saving to " << image_path_;
  Start = clock();
  Colors.save(image_path_);
  Stop = clock();
  std::cout << " (" << (double(Stop - Start) / CLOCKS_PER_SEC) << " seconds)"
            << std::endl;
}
