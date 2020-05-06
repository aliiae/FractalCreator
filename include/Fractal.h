#ifndef FRACTALCREATOR_INCLUDE_FRACTAL_H_
#define FRACTALCREATOR_INCLUDE_FRACTAL_H_

#include <Area.h>

#include <complex>

class Fractal {
  friend class Creator;

 public:
  explicit Fractal(int max_iterations);
  virtual ~Fractal() = default;

  virtual Area<double> GetArea() = 0;
  virtual void SetArea(Area<double> &new_area) = 0;
  virtual std::complex<double> CalculateRecurrence(std::complex<double> z,
                                                   std::complex<double> c) = 0;
  virtual std::string GetName() = 0;

  int GetIterations(std::complex<double> c);
  std::string GetZoomAreaString();
  [[nodiscard]] int GetMaxIterations() const;

 protected:
  int max_iterations_;
};

#endif  // FRACTALCREATOR_INCLUDE_FRACTAL_H_
