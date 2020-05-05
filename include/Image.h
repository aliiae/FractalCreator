#ifndef FRACTALCREATOR_INCLUDE_IMAGE_H
#define FRACTALCREATOR_INCLUDE_IMAGE_H

#include "utils.h"
#include <complex>
#include <vector>

class Image {
public:
  Image(int Width, int Height, std::vector<std::vector<utils::RGB>> &Colours);
  void save(const std::string &FilePath);

private:
  int width_;
  int height_;
  int bytesPerPixel_{3};
  std::vector<std::vector<utils::RGB>> colours_;
};

#endif // FRACTALCREATOR_INCLUDE_IMAGE_H
