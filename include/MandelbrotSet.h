#ifndef FRACTALCREATOR_INCLUDE_MANDELBROTSET_H
#define FRACTALCREATOR_INCLUDE_MANDELBROTSET_H

#include "Fractal.h"

class MandelbrotSet : public Fractal {
public:
  using Fractal::Fractal;
  void setZoomArea(Area<double> &FractalArea) override;
  Area<double> getZoomArea() override;
  std::complex<double> calculateRecurrence(std::complex<double> Z,
										   std::complex<double> C) override;
  std::string getName() override;

private:
  Area<double> zoom_area_{-2.2, 1.2, -1.7, 1.7};
  std::string name_{"Mandelbrot_Set"};
};;

#endif //FRACTALCREATOR_INCLUDE_MANDELBROTSET_H
