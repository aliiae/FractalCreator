#include <Creator.h>

#include <future>

Creator::Creator(int width, int height, int max_iterations,
                 std::shared_ptr<Fractal> fractal)
    : width_(width),
      height_(height),
      max_iterations_(max_iterations),
      fractal_(std::move(fractal)) {
  future_rows_.resize(height_);
  pixels_.resize(width_ * height_ * 4, 0);
}

/**
 * Calculate Bernstein polynomials mapping an integer to a continuous RGB space.
 * A modified version of
 * https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11
 */
utils::RGB Creator::ToRgb(double t) {
  return utils::RGB{
      static_cast<unsigned char>((8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255)),
      static_cast<unsigned char>((15 * (1 - t) * (1 - t) * t * t * 255)),
      static_cast<unsigned char>((9 * (1 - t) * t * t * t * 255))};
}

double Creator::ConvertX(int col) const {
  return col * fractal_->GetArea().GetWidth() / width_ +
         fractal_->GetArea().GetXMin();
}

double Creator::ConvertY(int row) const {
  return row * fractal_->GetArea().GetHeight() / height_ +
         fractal_->GetArea().GetYMin();
}
std::vector<unsigned char> &Creator::GetPixels() {
  auto get_row = [=](int row) {
    std::vector<utils::RGB> result(width_);
    double imaginary_part = ConvertY(row);
    for (int col = 0; col < width_; col++) {
      double real_part = ConvertX(col);
      const std::complex<double> &z =
          std::complex<double>{real_part, imaginary_part};
      int iterations = fractal_->GetIterations(z);
      if (iterations == max_iterations_) {
        result[col] = utils::RGB{0, 0, 0};
      } else {
        double scaled_iterations =
            double(iterations) / double(fractal_->GetMaxIterations());
        result[col] = ToRgb(scaled_iterations);
      }
    }
    return result;
  };

  for (int row = 0; row < height_; row++) {
    future_rows_[row] = std::async(get_row, row);
  }

  for (int row = 0; row < height_; row++) {
    auto rgb_row = std::move(future_rows_[row].get());
    for (int col = 0; col < width_; col++) {
      int offset = 4 * (row * width_ + col);
      pixels_[offset] = 255;
      pixels_[offset + 1] = rgb_row[col].blue;
      pixels_[offset + 2] = rgb_row[col].green;
      pixels_[offset + 3] = rgb_row[col].red;
    }
  }
  return pixels_;
}
