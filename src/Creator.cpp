#include "Creator.h"
#include "Fractal.h"
#include <Image.h>
#include <iostream>
#include <memory>

using Clock = std::chrono::system_clock;
using Seconds = std::chrono::duration<double>;

int Creator::getWidth() const { return width_; }
void Creator::setWidth(int Width) { width_ = Width; }
int Creator::getHeight() const { return height_; }
void Creator::setHeight(int Height) { height_ = Height; }

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

void Creator::draw() {
  std::cout << "Generating a " << fractal_->getName() << " fractal of order "
            << fractal_->getOrder() << " with max " << max_iterations_
            << " iterations";
  std::cout.flush();
  auto Start = Clock::now();
  Image Colors(width_, height_);
  for (int Row = 0; Row < height_; ++Row) {
    double ImaginaryPart = convertY(Row);
    for (int Col = 0; Col < width_; ++Col) {
      double RealPart = convertX(Col);
      std::complex<double> C = std::complex<double>{RealPart, ImaginaryPart};
      int Iterations = fractal_->getIterations(C);
      Colors(Row, Col) = toRgb(Iterations);
    }
  }
  Seconds ElapsedSeconds = Clock::now() - Start;
  std::cout << " (" << ElapsedSeconds.count() << " seconds)" << std::endl;

  std::cout << "Saving to " << image_path_;
  std::cout.flush();
  Start = Clock::now();
  Colors.save(image_path_);
  ElapsedSeconds = Clock::now() - Start;
  std::cout << " (" << ElapsedSeconds.count() << " seconds)" << std::endl;
}
double Creator::convertY(int Row) const {
  return fractal_->getZoomArea().getYMin() +
         Row / (double)height_ * fractal_->getZoomArea().height();
}
double Creator::convertX(int Col) const {
  return fractal_->getZoomArea().getXMin() +
         Col / (double)width_ * fractal_->getZoomArea().width();
}
const std::unique_ptr<Fractal> &Creator::getFractal() const { return fractal_; }