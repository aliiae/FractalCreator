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
	  type_->getFractalArea().getXMin() + Coord.x / (double)Screen.width() * type_->getFractalArea().width(),
	  type_->getFractalArea().getYMin() + Coord.y / (double)Screen.height() * type_->getFractalArea().height());
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
	Z = type_->calculateRecurrence(Z, C);
	Iterations++;
  }
  return Iterations;
}
void Fractal::zoom(double WindowRatio, Area<double> NewArea) {
  type_->zoom(WindowRatio, NewArea);
}
