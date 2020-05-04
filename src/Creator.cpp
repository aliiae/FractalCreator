#include "Creator.h"
#include "Area.h"
#include "Fractal.h"
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

void Creator::draw(int SelectedTypeNumber) {
  std::unique_ptr<FractalType> SelectedFractalType;
  switch (SelectedTypeNumber) {
  case 2: {
    SelectedFractalType = std::make_unique<BurningShip>(max_iterations_);
    break;
  }
  default:
    SelectedFractalType = std::make_unique<MandelbrotSet>(max_iterations_);
  }

  std::cout << "Generating a " << SelectedFractalType->getName()
            << " fractal with max " << max_iterations_ << " iterations";
  Fractal NewFractal = Fractal(std::move(SelectedFractalType), max_iterations_);
  clock_t Start = clock();
  Area<int> Screen(0, width_, 0, height_);
  Image Colors(width_, height_);
  for (int Ix = 0; Ix < Screen.width(); ++Ix)
    for (int Iy = 0; Iy < Screen.height(); ++Iy) {
      int Iterations =
          NewFractal.getIterations(utils::Coordinate{Iy, Ix}, Screen, Colors);
      Colors(Ix, Iy) = double(Iterations) / double(max_iterations_);
    }
  clock_t Stop = clock();
  std::cout << " (" << (double(Stop - Start) / CLOCKS_PER_SEC) << " seconds)"
			<< "\n";
  std::cout << "Saving to " << image_path_;
  Start = clock();
  Colors.save(image_path_);
  Stop = clock();
  std::cout << " (" << (double(Stop - Start) / CLOCKS_PER_SEC) << " seconds)"
            << "\n";
}
