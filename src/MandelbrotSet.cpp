#include <MandelbrotSet.h>

std::complex<double> MandelbrotSet::CalculateRecurrence(
    std::complex<double> z, std::complex<double> c) {
  return z * z + c;
}
Area<double> MandelbrotSet::GetArea() { return zoom_area_; }
void MandelbrotSet::SetArea(Area<double> &fractal_area) {
  zoom_area_ = fractal_area;
}
std::string MandelbrotSet::GetName() { return name_; }
