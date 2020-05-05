#include "MandelbrotSet.h"
#include <complex>

std::complex<double> MandelbrotSet::calculateRecurrence(std::complex<double> Z, std::complex<double> C) {
  for (int Power = 1; Power < order_; Power++) {
	Z *= Z;
  }
  return Z + C;
}
Area<double> MandelbrotSet::getZoomArea() { return zoom_area_; }
void MandelbrotSet::setZoomArea(Area<double> &FractalArea) {
  zoom_area_ = FractalArea;
}
std::string MandelbrotSet::getName() { return name_; }

