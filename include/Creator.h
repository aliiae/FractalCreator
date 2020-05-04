#ifndef FRACTALCREATOR_INCLUDE_CREATOR_H
#define FRACTALCREATOR_INCLUDE_CREATOR_H

#include "Fractal.h"
#include "utils.h"
#include <string>
#include <utility>

class Creator {
public:
  explicit Creator(std::string ImagePath, int Width, int Height,
                   int MaxIterations, std::unique_ptr<Fractal> Fractal)
      : image_path_(std::move(ImagePath)), width_(Width), height_(Height),
        max_iterations_(MaxIterations), fractal_(std::move(Fractal)){};
  Creator()
      : image_path_("output.ppm"), width_(1200), height_(1200),
        max_iterations_(30){};
  int getHeight() const;
  void setHeight(int Height);
  int getWidth() const;
  void setWidth(int Width);
  const std::unique_ptr<Fractal> &getFractal() const;
  void draw();

private:
  int width_;
  int height_;
  std::string image_path_;
  int max_iterations_;
  std::unique_ptr<Fractal> fractal_;
  [[nodiscard]] utils::RGB toRgb(int Iterations) const;
  double convertX(int Col) const;
  double convertY(int Row) const;
};

#endif // FRACTALCREATOR_INCLUDE_CREATOR_H
