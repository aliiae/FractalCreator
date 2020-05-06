#ifndef FRACTALCREATOR_INCLUDE_BURNINGSHIP_H_
#define FRACTALCREATOR_INCLUDE_BURNINGSHIP_H_

#include <Fractal.h>
class BurningShip : public Fractal {
 public:
  using Fractal::Fractal;
  void SetArea(Area<double> &fractal_area) override;
  Area<double> GetArea() override;
  std::complex<double> CalculateRecurrence(std::complex<double> z,
                                           std::complex<double> c) override;
  std::string GetName() override;

 private:
  Area<double> zoom_area_{-2.5, 1.5, -2.2, 1.2};
  std::string name_ = "Burning Ship";
};

#endif  // FRACTALCREATOR_INCLUDE_BURNINGSHIP_H_
