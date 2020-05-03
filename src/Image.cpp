#include "Image.h"
#include <cmath>
#include <complex>
#include <fstream>
#include <iostream>

Image::Image(int Width, int Height)
    : width_(Width), height_(Height), data_(Height * Width) {}

int Image::getWidth() const { return width_; }
void Image::setWeight(int Weight) { width_ = Weight; }
int Image::getHeight() const { return height_; }
void Image::setHeight(int Height) { height_ = Height; }
int Image::getBytesPerPixel() const { return bytesPerPixel_; }
void Image::setBytesPerPixel(int BytesPerPixel) {
  bytesPerPixel_ = BytesPerPixel;
}
int Image::convert2DIndexTo1D(int &X, int &Y) const { return X * width_ + Y; }

utils::RGB Image::toRgb(double &ValuePercentage) {
  return utils::RGB{(int)(9 * (1 - ValuePercentage) * ValuePercentage *
                          ValuePercentage * ValuePercentage * 255),
                    (int)(15 * (1 - ValuePercentage) * (1 - ValuePercentage) *
                          ValuePercentage * ValuePercentage * 255),
                    (int)(8.5 * (1 - ValuePercentage) * (1 - ValuePercentage) *
                          (1 - ValuePercentage * ValuePercentage * 255))};
}

void Image::save(const std::string &FilePath) {
  std::ofstream Output(FilePath, std::ios::binary);
  utils::RGB Pixel{};
  if (Output.is_open()) {
    Output << "P" << bytesPerPixel_ << std::endl
           << width_ << " " << height_ << std::endl
           << " 255" << std::endl;
    for (int Ix = 0; Ix < width_; ++Ix)
      for (int Iy = 0; Iy < height_; ++Iy) {
        Pixel = Image::toRgb(data_[convert2DIndexTo1D(Ix, Iy)]);
        Output << Pixel.red << " " << Pixel.green << " " << Pixel.blue
               << std::endl;
      }
    Output.close();
  } else {
    std::cerr << "Could not open the file " << FilePath;
  }
}

/**
 * Overloaded operators to get and set 2D indices into the underlying 1D matrix,
 * e.g. ImageObject(1,1) = 1;
 */
double Image::operator()(int X, int Y) const {
  return data_[convert2DIndexTo1D(X, Y)];
}
double &Image::operator()(int X, int Y) {
  return data_[convert2DIndexTo1D(X, Y)];
}
