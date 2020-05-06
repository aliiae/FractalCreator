#ifndef FRACTALCREATOR_INCLUDE_FRACTAL_H
#define FRACTALCREATOR_INCLUDE_FRACTAL_H

#include "Area.h"
#include <complex>

class Fractal {
  friend class Creator;

public:
  explicit Fractal(int MaxIterations);
  virtual ~Fractal() = default;

  virtual Area<double> getArea() = 0;
  virtual void setArea(Area<double> &NewArea) = 0;
  std::string getZoomAreaString();
  virtual std::complex<double> calculateRecurrence(std::complex<double> Z,
                                                   std::complex<double> C) = 0;
  virtual std::string getName() = 0;

  int getIterations(std::complex<double> C);
  int getMaxIterations() const;

protected:
  int max_iterations_;
};

#endif // FRACTALCREATOR_INCLUDE_FRACTAL_H
