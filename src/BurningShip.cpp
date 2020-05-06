#include <BurningShip.h>

std::complex<double> BurningShip::CalculateRecurrence(std::complex<double> z,
                                                      std::complex<double> c) {
  z = abs(z.real()) + imaginary_one_ * abs(z.imag());
  return z * z + c;
}
Area<double> BurningShip::GetArea() { return zoom_area_; }
void BurningShip::SetArea(Area<double> &fractal_area) {
  zoom_area_ = fractal_area;
}
std::string BurningShip::GetName() { return name_; }
const std::complex<double> &BurningShip::imaginary_one_{0, 1.0};
