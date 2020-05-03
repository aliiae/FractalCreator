#include "Fractal.h"
#include "complex"

int Fractal::getMaxIterations() const { return max_iterations_; }
void Fractal::setMaxIterations(int NumberOfIterations) {
  max_iterations_ = NumberOfIterations;
}

/**
 * Convert a pixel coordinate to the complex domain.
 */
std::complex<double> Fractal::scale(Area<int> &Screen,
                                    utils::Coordinate Coord) {
  return std::complex<double>(
      this->getFractalArea().getXMin() +
          Coord.x / (Screen.width() - 1.0) * this->getFractalArea().width(),
      this->getFractalArea().getYMin() +
          Coord.y / (Screen.height() - 1.0) * this->getFractalArea().height());
}

/**
 * Counts the number of iterations of the recurrence relation at the given point
 * until convergence or max iterations.
 */
int Fractal::getIterations(utils::Coordinate Coord, Area<int> &Screen,
                           Image &Colors) {
  std::complex<double> C = scale(Screen, Coord);
  std::complex<double> Z = 0;
  int Iterations = 0;
  while (Iterations < max_iterations_ && abs(Z) < 2.0) {
    Z = this->calculateRecurrence(Z, C);
    Iterations++;
  }
  return Iterations;
}