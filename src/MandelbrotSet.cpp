#include "MandelbrotSet.h"
#include <complex>

std::complex<double> MandelbrotSet::calculateRecurrence(std::complex<double> Z, std::complex<double> C) {
  return Z * Z + C;
}
Area<double> MandelbrotSet::getArea() { return zoom_area_; }
void MandelbrotSet::setArea(Area<double> &FractalArea) {
  zoom_area_ = FractalArea;
}
std::string MandelbrotSet::getName() { return name_; }

