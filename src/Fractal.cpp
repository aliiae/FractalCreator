#include <Fractal.h>
#include <utils.h>

int Fractal::GetMaxIterations() const { return max_iterations_; }
int Fractal::GetIterations(std::complex<double> c) {
  std::complex<double> z = c;
  for (int iteration = 0; iteration < max_iterations_; ++iteration) {
    if (abs(z) >= 2.0) {
      return iteration;
    }
    z = CalculateRecurrence(z, c);
  }
  return max_iterations_;
}

/**
 * Formats the area as (left, right, top, bottom) coordinates to display to the
 * user.
 */
std::string Fractal::GetZoomAreaString() {
  Area<double> a = GetArea();
  return "(" + utils::FormatDouble(a.GetXMin()) + "," +
         utils::FormatDouble(a.GetXMax()) + "," +
         utils::FormatDouble(a.GetYMin()) + "," +
         utils::FormatDouble(a.GetYMax()) + ")";
}

Fractal::Fractal(int max_iterations) : max_iterations_(max_iterations) {}