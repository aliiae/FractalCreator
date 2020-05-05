#include "Image.h"
#include <fstream>
#include <iostream>

Image::Image(int Width, int Height)
    : width_(Width), height_(Height), data_(Height * Width) {}
int Image::getWidth() const { return width_; }
int Image::getHeight() const { return height_; }
int Image::convert2DIndexTo1D(int &X, int &Y) const { return X * height_ + Y; }

void Image::save(const std::string &FilePath) {
  std::ofstream Output(FilePath, std::ios::binary);
  utils::RGB Pixel{};
  if (Output.is_open()) {
    Output << "P" << bytesPerPixel_ << "\n"
           << width_ << " " << height_ << "\n"
           << "255"
           << "\n";
    for (int Row = 0; Row < height_; ++Row)
      for (int Col = 0; Col < width_; ++Col) {
        Pixel = data_[convert2DIndexTo1D(Row, Col)];
        Output << Pixel.red << " " << Pixel.green << " " << Pixel.blue << "\n";
      }
    Output.close();
  } else {
    std::cerr << "Could not open the file " << FilePath;
  }
}

/**
 * Calculate Bernstein polynomials mapping an integer to a continuous RGB space.
 * A modified version of
 * https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11: r(t) = 8.5 *
 * (1 - t)**3 * t; g(t) = 15 * (1 - t)**2 * t**2; b(t) = 9 * (1 - t) * t**3
 */
utils::RGB Image::toRgb(double T) const {
  return utils::RGB{(int)(8.5 * (1 - T) * (1 - T) * (1 - T) * T * 255),
                    (int)(15 * (1 - T) * (1 - T) * T * T * 255),
                    (int)(9 * (1 - T) * T * T * T * 255)};
}

/**
 * Overloaded operators to get and set 2D indices into the underlying 1D matrix,
 * e.g. ImageObject(1,1) = 1;
 */
utils::RGB Image::operator()(int X, int Y) const {
  return data_[convert2DIndexTo1D(X, Y)];
}
utils::RGB &Image::operator()(int X, int Y) {
  return data_[convert2DIndexTo1D(X, Y)];
}
