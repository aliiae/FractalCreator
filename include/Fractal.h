#ifndef FRACTALCREATOR_INCLUDE_FRACTAL_H
#define FRACTALCREATOR_INCLUDE_FRACTAL_H

#include "Area.h"
#include <complex>

class Fractal {
  friend class Creator;

public:
  explicit Fractal(int MaxIterations);
  Fractal(int MaxIterations, int Order);
  virtual ~Fractal() = default;
  virtual Area<double> getArea() = 0;
  virtual void setArea(Area<double> &NewArea) = 0;
  virtual std::complex<double> calculateRecurrence(std::complex<double> Z,
                                                   std::complex<double> C) = 0;
  virtual std::string getName() = 0;

  int getIterations(std::complex<double> C);
  void setOrder(int Order);
  int getOrder() const;
  int getMaxIterations() const;

protected:
  int order_{};
  int max_iterations_;
};

class MandelbrotSet : public Fractal {
public:
  using Fractal::Fractal;
  void setArea(Area<double> &FractalArea) override;
  Area<double> getArea() override;
  std::complex<double> calculateRecurrence(std::complex<double> Z,
                                           std::complex<double> C) override;
  std::string getName() override;

private:
  Area<double> zoom_area_{-2.2, 1.2, -1.7, 1.7};
  std::string name_{"Mandelbrot Set"};
};

class BurningShip : public Fractal {
public:
  using Fractal::Fractal;
  void setArea(Area<double> &FractalArea) override;
  Area<double> getArea() override;
  std::complex<double> calculateRecurrence(std::complex<double> Z,
                                           std::complex<double> C) override;
  std::string getName() override;

private:
  Area<double> zoom_area_{-2.5, 1.5, -2.2, 1.2};
  static const std::complex<double> &ImaginaryOne;
  std::string name_{"Burning Ship"};
};

#endif // FRACTALCREATOR_INCLUDE_FRACTAL_H
