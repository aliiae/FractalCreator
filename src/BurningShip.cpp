#include <BurningShip.h>

#include <complex>

std::complex<double> BurningShip::CalculateRecurrence(std::complex<double> z,
                                                      std::complex<double> c) {
  z = std::complex<double>{abs(z.real()), 0} +
      std::complex<double>{0, abs(z.imag())};
  return z * z + c;
}
Area<double> BurningShip::GetArea() { return zoom_area_; }
void BurningShip::SetArea(Area<double> &fractal_area) {
  zoom_area_ = fractal_area;
}
std::string BurningShip::GetName() { return name_; }
