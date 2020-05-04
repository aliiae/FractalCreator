#ifndef FRACTALCREATOR_INCLUDE_CREATOR_H
#define FRACTALCREATOR_INCLUDE_CREATOR_H

#include "utils.h"
#include <string>
#include <utility>

class Creator {
public:
  explicit Creator(std::string ImagePath, int Width, int Height,
                   int MaxIterations)
      : image_path_(std::move(ImagePath)), width_(Width), height_(Height),
        max_iterations_(MaxIterations){};
  Creator()
      : image_path_("output.ppm"), width_(1200), height_(1200),
        max_iterations_(30){};
  int getHeight() const;
  void setHeight(int Height);
  void draw(int SelectedTypeNumber);
  int getWidth() const;
  void setWidth(int Width);
  [[nodiscard]] const std::string &getImagePath() const;

  void setImagePath(const std::string &ImagePath);

private:
  int width_;
  int height_;
  std::string image_path_;
  int max_iterations_;
  utils::RGB toRgb(int Iterations) const;
};

#endif // FRACTALCREATOR_INCLUDE_CREATOR_H
