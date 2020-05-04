#ifndef FRACTALCREATOR_INCLUDE_FRACTAL_H
#define FRACTALCREATOR_INCLUDE_FRACTAL_H

#include "Area.h"
#include "FractalType.h"
#include "Image.h"
#include "utils.h"
#include <complex>
#include <memory>

class Fractal {
public:
  Fractal(std::unique_ptr<FractalType> Type, int NumberOfIterations)
      : type_(std::move(Type)), max_iterations_(NumberOfIterations) {}
  int getMaxIterations() const;
  void setMaxIterations(int NumberOfIterations);
  int getIterations(utils::Coordinate Coord, Area<int> &Screen, Image &Colors);
  void zoom(double WindowRatio, Area<double> NewArea);

private:
  std::unique_ptr<FractalType> type_;
  int max_iterations_;
  std::complex<double> scale(Area<int> &Screen, utils::Coordinate Coord);
};

#endif // FRACTALCREATOR_INCLUDE_FRACTAL_H
