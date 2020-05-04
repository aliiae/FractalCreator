#ifndef FRACTALCREATOR_INCLUDE_IMAGE_H
#define FRACTALCREATOR_INCLUDE_IMAGE_H

#include "utils.h"
#include <complex>
#include <vector>

class Image {
public:
  Image(int Width, int Height);
  int getWidth() const;
  int getHeight() const;
  utils::RGB &operator()(int X, int Y);
  utils::RGB operator()(int X, int Y) const;
  void save(const std::string &FilePath);

private:
  int width_;
  int height_;
  int bytesPerPixel_{3};
  std::vector<utils::RGB> data_;
  int convert2DIndexTo1D(int &X, int &Y) const;
};

#endif // FRACTALCREATOR_INCLUDE_IMAGE_H
