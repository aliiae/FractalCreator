#ifndef FRACTALCREATOR_INCLUDE_CREATOR_H
#define FRACTALCREATOR_INCLUDE_CREATOR_H

#include "Fractal.h"
#include "Image.h"
#include "utils.h"
#include <string>
#include <utility>

class Creator {
public:
  explicit Creator(std::string ImagePath, int Width, int Height,
                   int MaxIterations, std::shared_ptr<Fractal> Fractal)
      : image_path_(ImagePath), width_(Width), height_(Height),
        max_iterations_(MaxIterations), fractal_(Fractal) {
    image_ = std::make_shared<Image>(Width, Height);
  };
  void draw();
  void fillOneRow(int RowIndex);

private:
  int width_;
  int height_;
  int max_iterations_;
  std::shared_ptr<Image> image_;
  std::string image_path_;
  std::shared_ptr<Fractal> fractal_;
  double convertRowIndexToImaginary(int Row) const;
  double convertColIndexToReal(int Col) const;
  utils::RGB toRgb(double T) const;
};

#endif // FRACTALCREATOR_INCLUDE_CREATOR_H
