#include "Creator.h"
#include <Image.h>
#include <JobManager.h>
#include <iostream>

using Clock = std::chrono::system_clock;
using Seconds = std::chrono::duration<double>;

/**
 * Calculate Bernstein polynomials mapping an integer to a continuous RGB space.
 * A modified version of
 * https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11: r(t) = 8.5 *
 * (1 - t)**3 * t; g(t) = 15 * (1 - t)**2 * t**2; b(t) = 9 * (1 - t) * t**3
 */
utils::RGB Creator::toRgb(double T) const {
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
  auto JobFunction = [&](int RowIndex) { fillOneRow(RowIndex); };
  JobManager Manager = JobManager(4, height_, JobFunction);
  Manager.compute();
  Seconds ElapsedSeconds = Clock::now() - Start;
  std::cout << " (" << ElapsedSeconds.count() << " seconds)" << std::endl;
  std::cout << "Saving to " << image_path_;
  std::cout.flush();
  Start = Clock::now();
  image_->save(image_path_);
  ElapsedSeconds = Clock::now() - Start;
  std::cout << " (" << ElapsedSeconds.count() << " seconds)" << std::endl;
}
/**
 * Process a single row of a fractal (i.e. calculate all pixels of a Y-axis).
 */
void Creator::fillOneRow(int RowIndex) {
  double ImaginaryPart = convertRowIndexToImaginary(RowIndex);
  for (int ColIndex = 0; ColIndex < image_->getWidth(); ++ColIndex) {
    double RealPart = convertColIndexToReal(ColIndex);
    std::complex<double> C = std::complex<double>{RealPart, ImaginaryPart};
    int Iterations = fractal_->getIterations(C);
    double ScaledIterations =
        double(Iterations) / double(fractal_->getMaxIterations());
    (*image_)(RowIndex, ColIndex) = toRgb(ScaledIterations);
  }
}
double Creator::convertRowIndexToImaginary(int Row) const {
  return fractal_->getZoomArea().getYMin() +
         Row / (double)image_->getHeight() * fractal_->getZoomArea().height();
}
double Creator::convertColIndexToReal(int Col) const {
  return fractal_->getZoomArea().getXMin() +
         Col / (double)image_->getWidth() * fractal_->getZoomArea().width();
}
