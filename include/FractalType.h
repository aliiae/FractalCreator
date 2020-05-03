#ifndef FRACTALCREATOR_INCLUDE_FRACTALTYPE_H
#define FRACTALCREATOR_INCLUDE_FRACTALTYPE_H

#include "Area.h"
#include <complex>

enum FractalName { MANDELBROT_SET, BURNING_SHIP };

class FractalType {
public:
  FractalType(int MaxIterations) : max_iterations_(MaxIterations){};
  virtual ~FractalType() {}
  virtual Area<double> getFractalArea() = 0;
  virtual std::complex<double> calculateRecurrence(std::complex<double> Z,
                                                   std::complex<double> C) = 0;
  virtual FractalName getName() = 0;

private:
  int max_iterations_;
};

class MandelbrotSet : public FractalType {
public:
  using FractalType::FractalType;
  Area<double> getFractalArea() override;
  std::complex<double> calculateRecurrence(std::complex<double> Z,
                                           std::complex<double> C) override;
  FractalName getName() override;

private:
  Area<double> fractal_area_{-2.5, 1, -1, 1};
};

class BurningShip : public FractalType {
public:
  using FractalType::FractalType;
  Area<double> getFractalArea() override;
  std::complex<double> calculateRecurrence(std::complex<double> Z,
                                           std::complex<double> C) override;
  FractalName getName() override;

private:
  Area<double> fractal_area_{-2.5, 1.5, -2.5, 1.5};
};

#endif // FRACTALCREATOR_INCLUDE_FRACTALTYPE_H
