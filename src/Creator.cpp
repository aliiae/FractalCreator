#include "Creator.h"
#include <memory>

Creator::Creator(int Width, int Height, int MaxIterations, std::shared_ptr<Fractal> Fractal)
	: width_(Width), height_(Height),
	  max_iterations_(MaxIterations), fractal_(std::move(Fractal)) {
  rows_.resize(height_);
  future_rows_.resize(height_);
  pixels_.resize(width_ * height_ * 4, 0);
}

/**
 * Calculate Bernstein polynomials mapping an integer to a continuous RGB space.
 * A modified version of
 * https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11: r(t) = 8.5 *
 * (1 - t)**3 * t; g(t) = 15 * (1 - t)**2 * t**2; b(t) = 9 * (1 - t) * t**3
 */
utils::RGB Creator::toRgb(double T) {
  return utils::RGB{(int)(8.5 * (1 - T) * (1 - T) * (1 - T) * T * 255),
					(int)(15 * (1 - T) * (1 - T) * T * T * 255),
					(int)(9 * (1 - T) * T * T * T * 255)};
}

double Creator::convertX(int Col) const {
  return Col * fractal_->getArea().getWidth() / width_ + fractal_->getArea().getXMin();
}

double Creator::convertY(int Row) const {
  return Row * fractal_->getArea().getHeight() / height_ + fractal_->getArea().getYMin();
}
std::vector<unsigned char> &Creator::getPixels() {
  auto GetRow = [=](int Row) {
	std::vector<utils::RGB> Result(width_);
	double ImaginaryPart = convertY(Row);
	for (int Col = 0; Col < width_; Col++) {
	  double RealPart = convertX(Col);
	  int Iterations = fractal_->getIterations(
		  std::complex<double>{RealPart, ImaginaryPart});
	  double ScaledIterations =
		  double(Iterations) / double(fractal_->getMaxIterations());
	  Result[Col] = toRgb(ScaledIterations);
	}
	return Result;
  };

  for (int Row = 0; Row < height_; Row++) {
	future_rows_[Row] = std::async(GetRow, Row);
  }

  for (int Row = 0; Row < height_; Row++) {
	rows_[Row] = std::move(future_rows_[Row].get());
	for (int Col = 0; Col < width_; Col++) {
	  int Offset = 4 * (Row * width_ + Col);
	  pixels_[Offset] = 255;
	  pixels_[Offset + 1] = rows_[Row][Col].blue;
	  pixels_[Offset + 2] = rows_[Row][Col].green;
	  pixels_[Offset + 3] = rows_[Row][Col].red;
	}
  }
  return pixels_;
}
