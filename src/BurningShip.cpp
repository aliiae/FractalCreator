#include <BurningShip.h>

std::complex<double> BurningShip::calculateRecurrence(std::complex<double> Z,
                                                      std::complex<double> C) {
  Z = abs(Z.real()) + ImaginaryOne * abs(Z.imag());
  return Z * Z + C;
}
Area<double> BurningShip::getArea() { return zoom_area_; }
void BurningShip::setArea(Area<double> &FractalArea) {
  zoom_area_ = FractalArea;
}
std::string BurningShip::getName() { return name_; }
const std::complex<double> &BurningShip::ImaginaryOne{0, 1.0};
