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
  void zoom(double WindowRatio, Area<double> NewArea);
  int getIterations(std::complex<double> C);

protected:
  int max_iterations_;

public:
  int getOrder() const;

protected:
  int order_;

public:
  void setOrder(int Order);
};

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
  std::string name_{"Mandelbrot Set"};
};

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

#endif // FRACTALCREATOR_INCLUDE_FRACTAL_H
