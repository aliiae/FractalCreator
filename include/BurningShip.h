#ifndef FRACTALCREATOR_INCLUDE_BURNINGSHIP_H
#define FRACTALCREATOR_INCLUDE_BURNINGSHIP_H

#include <Fractal.h>
class BurningShip : public Fractal {
public:
  using Fractal::Fractal;
  void setZoomArea(Area<double> &FractalArea) override;
  Area<double> getZoomArea() override;
  std::complex<double> calculateRecurrence(std::complex<double> Z,
										   std::complex<double> C) override;
  std::string getName() override;

private:
  Area<double> zoom_area_{-2.5, 1.5, -2.2, 1.2};
  static const std::complex<double> &ImaginaryOne;
  std::string name_{"Burning Ship"};
};

#endif //FRACTALCREATOR_INCLUDE_BURNINGSHIP_H
