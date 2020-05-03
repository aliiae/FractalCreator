#include "FractalType.h"

std::complex<double>
MandelbrotSet::calculateRecurrence(std::complex<double> Z,
                                   std::complex<double> C) {
  return Z * Z + C;
}
Area<double> MandelbrotSet::getFractalArea() { return fractal_area_; }
FractalName MandelbrotSet::getName() { return MANDELBROT_SET; }
std::complex<double> BurningShip::calculateRecurrence(std::complex<double> Z,
                                                      std::complex<double> C) {
  return std::complex<double>{
      abs(Z.real() * Z.real() - Z.imag() * Z.imag() + C.real()),
      abs(2 * Z.real() * Z.imag() + C.imag())};
}
Area<double> BurningShip::getFractalArea() { return fractal_area_; }
FractalName BurningShip::getName() { return BURNING_SHIP; }
