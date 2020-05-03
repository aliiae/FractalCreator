#ifndef FRACTALCREATOR_INCLUDE_FRACTAL_H
#define FRACTALCREATOR_INCLUDE_FRACTAL_H

#include "Area.h"
#include "Image.h"
#include "utils.h"
#include <complex>
#include <memory>

class Fractal {
public:
  explicit Fractal(int NumberOfIterations)
      : max_iterations_(NumberOfIterations) {}
  int getMaxIterations() const;
  void setMaxIterations(int NumberOfIterations);
  int getIterations(utils::Coordinate Coord, Area<int> &Screen, Image &Colors);

private:
  virtual std::complex<double> calculateRecurrence(std::complex<double> Z,
                                                   std::complex<double> C) = 0;
  virtual Area<double> getFractalArea() = 0;
  virtual void setFractalArea(const Area<double> &FractalArea) = 0;
  int max_iterations_;
  std::complex<double> scale(Area<int> &Screen, utils::Coordinate Coord);
};

#endif // FRACTALCREATOR_INCLUDE_FRACTAL_H
