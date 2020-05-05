#include "Image.h"
#include <fstream>
#include <iostream>

Image::Image(int Width, int Height,
             std::vector<std::vector<utils::RGB>> &Colours)
    : width_(Width), height_(Height), colours_(Colours) {}

void Image::save(const std::string &FilePath) {
  std::ofstream Output(FilePath, std::ios::binary);
  if (Output.is_open()) {
    Output << "P" << bytesPerPixel_ << "\n"
           << width_ << " " << height_ << "\n"
           << "255"
           << "\n";
    for (int Row = 0; Row < height_; ++Row) {
      for (int Col = 0; Col < width_; ++Col) {
        auto &Pixel = colours_[Row][Col];
        Output << Pixel.red << " " << Pixel.green << " " << Pixel.blue << "\n";
      }
    }
    Output.close();
  } else {
    std::cerr << "Could not open the file " << FilePath;
  }
}