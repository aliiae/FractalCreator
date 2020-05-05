#ifndef FRACTALCREATOR_INCLUDE_FRACTALROW_H
#define FRACTALCREATOR_INCLUDE_FRACTALROW_H

#include "Creator.h"
#include "Fractal.h"
#include "Image.h"
#include "utils.h"
#include <complex>
#include <vector>

class FractalRow {
public:
  FractalRow(std::shared_ptr<Fractal> Fractal) : fractal_(Fractal){};
  void setup(std::shared_ptr<Image> &Colors, int Y) {
    y_ = Y;
    image_ = Colors;
  };

  void run() {
    double ImaginaryPart = convertY(y_);
    for (int X = 0; X < image_->getWidth(); ++X) {
      double RealPart = convertX(X);
      std::complex<double> C = std::complex<double>{RealPart, ImaginaryPart};
      int Iterations = fractal_->getIterations(C);
      double ScaledIterations =
          double(Iterations) / double(fractal_->getMaxIterations());
      (*image_)(y_, X) = image_->toRgb(ScaledIterations);
    }
  }

private:
  int y_;
  std::shared_ptr<Fractal> fractal_;
  std::shared_ptr<Image> image_;

  double convertY(int Row) const {
    return fractal_->getZoomArea().getYMin() +
           Row / (double)image_->getHeight() * fractal_->getZoomArea().height();
  }
  double convertX(int Col) const {
    return fractal_->getZoomArea().getXMin() +
           Col / (double)image_->getWidth() * fractal_->getZoomArea().width();
  }
};

#endif // FRACTALCREATOR_INCLUDE_FRACTALROW_H
