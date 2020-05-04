#include "Creator.h"
#include "Area.h"
#include "Fractal.h"
#include <iostream>
#include <memory>

using Clock = std::chrono::system_clock;
using Seconds = std::chrono::duration<double>;

int Creator::getWidth() const { return width_; }
void Creator::setWidth(int Width) { width_ = Width; }
int Creator::getHeight() const { return height_; }
void Creator::setHeight(int Height) { height_ = Height; }
const std::string &Creator::getImagePath() const { return image_path_; }
void Creator::setImagePath(const std::string &ImagePath) {
  image_path_ = ImagePath;
}

/**
 * Calculate Bernstein polynomials mapping an integer to a continuous RGB space.
 * A modified version of
 * https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11: r(t) = 8.5 *
 * (1 - t)**3 * t; g(t) = 15 * (1 - t)**2 * t**2; b(t) = 9 * (1 - t) * t**3
 */
utils::RGB Creator::toRgb(int Iterations) const {
  double T = double(Iterations) / double(max_iterations_);
  return utils::RGB{(int)(8.5 * (1 - T) * (1 - T) * (1 - T) * T * 255),
					(int)(15 * (1 - T) * (1 - T) * T * T * 255),
					(int)(9 * (1 - T) * T * T * T * 255)};
}
void Creator::draw(std::string SelectedTypeChar, int SelectedOrder) {
  std::unique_ptr<FractalType> SelectedFractalType;
  if (SelectedTypeChar.at(0)=='B') {
	SelectedFractalType =
		std::make_unique<BurningShip>(max_iterations_, SelectedOrder);
  } else {
	SelectedFractalType =
		std::make_unique<MandelbrotSet>(max_iterations_, SelectedOrder);
  }
  std::cout << "Generating a " << SelectedFractalType->getName()
			<< " fractal of order " << SelectedOrder << " with max "
			<< max_iterations_ << " iterations";
  std::cout.flush();
  auto Start = Clock::now();
  Area<int> Screen(0, width_, 0, height_);
  Image Colors(width_, height_);
  Fractal NewFractal = Fractal(std::move(SelectedFractalType), max_iterations_);
  for (int Row = 0; Row < Screen.height(); ++Row)
	for (int Col = 0; Col < Screen.width(); ++Col) {
	  int Iterations =
		  NewFractal.getIterations(utils::Coordinate{Col, Row}, Screen, Colors);
	  Colors(Row, Col) = toRgb(Iterations);
	}
  Seconds ElapsedSeconds = Clock::now() - Start;
  std::cout << " (" << ElapsedSeconds.count() << " seconds)"
			<< "\n";

  std::cout << "Saving to " << image_path_;
  std::cout.flush();
  Start = Clock::now();
  Colors.save(image_path_);
  ElapsedSeconds = Clock::now() - Start;
  std::cout << " (" << ElapsedSeconds.count() << " seconds)"
			<< "\n";
}
