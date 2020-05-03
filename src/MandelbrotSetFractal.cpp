#include "MandelbrotSetFractal.h"

std::complex<double>
MandelbrotSetFractal::calculateRecurrence(std::complex<double> Z,
                                          std::complex<double> C) {
  return Z * Z + C;
}
Area<double> MandelbrotSetFractal::getFractalArea() { return fractal_area_; }
void MandelbrotSetFractal::setFractalArea(const Area<double> &FractalArea) {
  fractal_area_ = FractalArea;
}
