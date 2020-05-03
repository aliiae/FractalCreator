#ifndef FRACTALCREATOR_INCLUDE_BURNINGSHIPFRACTAL_H
#define FRACTALCREATOR_INCLUDE_BURNINGSHIPFRACTAL_H

#include "Fractal.h"

class BurningShipFractal : public Fractal {
public:
  using Fractal::Fractal;
  void setFractalArea(const Area<double> &FractalArea) override;
  Area<double> getFractalArea() override;

private:
  std::complex<double> calculateRecurrence(std::complex<double> Z,
                                           std::complex<double> C) override;
  Area<double> fractal_area_{-2.5, 1.5, -2.5, 1.5};
};

#endif // FRACTALCREATOR_INCLUDE_BURNINGSHIPFRACTAL_H
