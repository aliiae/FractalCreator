#ifndef FRACTALCREATOR_INCLUDE_MANDELBROTSET_H_
#define FRACTALCREATOR_INCLUDE_MANDELBROTSET_H_

#include <Fractal.h>

class MandelbrotSet : public Fractal {
 public:
  using Fractal::Fractal;
  void SetArea(Area<double> &fractal_area) override;
  Area<double> GetArea() override;
  std::complex<double> CalculateRecurrence(std::complex<double> z,
                                           std::complex<double> c) override;
  std::string GetName() override;

 private:
  Area<double> zoom_area_{-2.2, 1.2, -1.7, 1.7};
  std::string name_ = "Mandelbrot Set";
};

#endif  // FRACTALCREATOR_INCLUDE_MANDELBROTSET_H_
