#ifndef FRACTALCREATOR_SRC_GRAPHICS_H
#define FRACTALCREATOR_SRC_GRAPHICS_H

#include <utility>
#include <string>
#include "utils.h"

class Graphics {
public:
  explicit Graphics(std::string ImagePath, float Width, float Height, int MaxIterations)
	  : image_path_(std::move(ImagePath)), width_(Width), height_(Height), max_iterations_(MaxIterations) {};
  Graphics() : image_path_("output.ppm"), width_(1200), height_(1200), max_iterations_(30) {};
  Graphics(int MaxIterations)
	  : image_path_("output.ppm"), width_(1200), height_(1200), max_iterations_(MaxIterations) {};
  explicit Graphics(std::string ImagePath)
	  : image_path_(std::move(ImagePath)), width_(1200), height_(1200), max_iterations_(30) {};
  float getHeight() const;
  void setHeight(float Height);
  void draw();
  float getWidth() const;
  void setWidth(float Width);
  const std::string &getImagePath() const;
  void setImagePath(const std::string &ImagePath);

private:
  float width_;
  float height_;
  std::string image_path_;
  int max_iterations_;
public:
  std::tuple<int, int, int> getRgbSmooth(int Value) const;
};

#endif //FRACTALCREATOR_SRC_GRAPHICS_H
