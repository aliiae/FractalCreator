#ifndef FRACTALCREATOR_INCLUDE_IMAGE_H
#define FRACTALCREATOR_INCLUDE_IMAGE_H

#include "utils.h"
#include <vector>

class Image {
public:
  Image(int Width, int Height);
  int getWidth() const;
  void setWeight(int Weight);
  int getHeight() const;
  void setHeight(int Height);
  double &operator()(int X, int Y);
  double operator()(int X, int Y) const;
  int getBytesPerPixel() const;
  void setBytesPerPixel(int BytesPerPixel);
  void save(const std::string &FilePath);

private:
  int width_;
  int height_;
  int bytesPerPixel_{3};
  std::vector<double> data_;
  static utils::RGB toRgb(double &ValuePercentage);
  int convertIndexTo1D(int &X, int &Y) const;
};

#endif // FRACTALCREATOR_INCLUDE_IMAGE_H
