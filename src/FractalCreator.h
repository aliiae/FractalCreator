#ifndef FRACTALCREATOR_SRC_FRACTALCREATOR_H
#define FRACTALCREATOR_SRC_FRACTALCREATOR_H
#include <complex>
#include "Area.h"
#include "utils.h"

class FractalCreator {
public:
  explicit FractalCreator(int NumberOfIterations) : max_iterations(NumberOfIterations) {}
  int getMaxIterations() const;
  void setMaxIterations(int NumberOfIterations);
  std::vector<int> iterate(Area<int> &Screen, Area<double> &FractalArea);

private:
  int max_iterations;
  std::complex<double> scale(Area<int> &Screen, Area<double> &FractalArea, std::complex<double> Constant);
  void getNumberOfIterations(Area<int> &Screen, Area<double> &FractalArea, std::vector<int> &Colors);
  int escape(std::complex<double> Constant);
  static std::complex<double> getValue(std::complex<double> Z, std::complex<double> C);
};

#endif //FRACTALCREATOR_SRC_FRACTALCREATOR_H
