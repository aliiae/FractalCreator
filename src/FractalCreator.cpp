#include <iostream>
#include <vector>
#include "complex"
#include "FractalCreator.h"
#include "Area.h"

using Complex = std::complex<double>;

Complex FractalCreator::getValue(Complex Z, Complex C) {
  return Complex{abs(Z.real()*Z.real() - Z.imag()*Z.imag() + C.real()),
				 abs(2*Z.real()*Z.imag() + C.imag())};
}

int FractalCreator::getMaxIterations() const {
  return max_iterations;
}
void FractalCreator::setMaxIterations(int NumberOfIterations) {
  max_iterations = NumberOfIterations;
}

// Check if a point is in the set or escapes to infinity, return the number if iterations
int FractalCreator::escape(Complex Constant) {
  Complex Z(0);
  int Iteration = 0;
  while (abs(Z) < 2.0 && Iteration < max_iterations) {
	Z = getValue(Z, Constant);
	Iteration++;
  }
  return Iteration;
}

// Loop over each pixel from our image and check if the points associated with this pixel escape to infinity
void FractalCreator::getNumberOfIterations(Area<int> &Screen, Area<double> &FractalArea, std::vector<int> &Colors) {
  int K = 0, Progress = -1;
  for (int I = Screen.getYMin(); I < Screen.getYMax(); ++I) {
	for (int J = Screen.getXMin(); J < Screen.getXMax(); ++J) {
	  Complex C((double)J, (double)I);
	  C = scale(Screen, FractalArea, C);
	  Colors[K] = escape(C);
	  K++;
	}
	if (Progress < (int)(I*100.0/Screen.getYMax())) {
	  Progress = (int)(I*100.0/Screen.getYMax());
	  std::cout << Progress << "%" << std::endl;
	}
  }
}

// Convert a pixel coordinate to the complex domain
Complex FractalCreator::scale(Area<int> &Screen, Area<double> &FractalArea, Complex Constant) {
  return Complex(Constant.real()/(double)Screen.width()*FractalArea.width() + FractalArea.getXMin(),
				 Constant.imag()/(double)Screen.height()*FractalArea.height() + FractalArea.getXMin());
}

std::vector<int> FractalCreator::iterate(Area<int> &Screen, Area<double> &FractalArea) {
  auto Start = std::chrono::steady_clock::now();
  std::vector<int> Colors(Screen.size());
  getNumberOfIterations(Screen, FractalArea, Colors);
  auto End = std::chrono::steady_clock::now();
  std::cout << "Time to generate = " << std::chrono::duration<double, std::milli>(End - Start).count()
			<< " [ms]" << std::endl;
  return Colors;
}
