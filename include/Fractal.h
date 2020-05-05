#ifndef FRACTALCREATOR_INCLUDE_FRACTAL_H
#define FRACTALCREATOR_INCLUDE_FRACTAL_H

#include "Area.h"
#include <complex>

class Fractal {
  friend class Creator;

public:
  explicit Fractal(int MaxIterations) : max_iterations_(MaxIterations){};
  virtual ~Fractal() = default;
  virtual Area<double> getZoomArea() = 0;
  virtual void setZoomArea(Area<double> &NewArea) = 0;
  virtual std::complex<double> calculateRecurrence(std::complex<double> Z,
                                                   std::complex<double> C) = 0;
  virtual std::string getName() = 0;
  [[maybe_unused]] void zoom(double WindowRatio, Area<double> NewArea);
  int getIterations(std::complex<double> C);
  void setOrder(int Order);
  int getOrder() const;
  int getMaxIterations() const;

protected:
  int order_;
  int max_iterations_;
};

#endif // FRACTALCREATOR_INCLUDE_FRACTAL_H
