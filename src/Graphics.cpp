#include "Graphics.h"
#include "FractalCreator.h"
#include "Area.h"
#include <iostream>
#include <fstream>
#include <vector>

float Graphics::getWidth() const {
  return width_;
}
void Graphics::setWidth(float Width) {
  width_ = Width;
}
float Graphics::getHeight() const {
  return height_;
}
void Graphics::setHeight(float Height) {
  height_ = Height;
}
const std::string &Graphics::getImagePath() const {
  return image_path_;
}
void Graphics::setImagePath(const std::string &ImagePath) {
  image_path_ = ImagePath;
}

std::tuple<int, int, int> Graphics::getRgbSmooth(int Value) const {
  // map value on the 0..1 interval
  double T = (double)Value/(double)max_iterations_;
  int R = (int)(9*(1 - T)*T*T*T*255);
  int G = (int)(15*(1 - T)*(1 - T)*T*T*255);
  int B = (int)(8.5*(1 - T)*(1 - T)*(1 - T)*T*255);
  return std::tuple<int, int, int>(R, G, B);
}

void Graphics::draw() {
  std::ofstream Image(image_path_);
  // Define the size of the image
  Area<int> Screen(0, width_, 0, height_);
  // The domain in which we test for points
  Area<double> FractalArea(-2.2, 1.2, -1.7, 1.7);
  auto Fractal = FractalCreator(max_iterations_);
  std::cout << "Drawing a fractal with " << max_iterations_ << " iterations" << std::endl;
  if (Image.is_open()) {
	Image << "P3\n" << width_ << " " << height_ << " 255\n";
	std::vector<int> Colors = Fractal.iterate(Screen, FractalArea);
	int K = 0;
	std::tuple<int, int, int> Rgb;
	for (int I = Screen.getYMin(); I < Screen.getYMax(); ++I) {
	  for (int J = Screen.getXMin(); J < Screen.getXMax(); ++J) {
		int Value = Colors[K];
		Rgb = getRgbSmooth(Value);
		Image << std::get<0>(Rgb) << ' ' << std::get<1>(Rgb) << ' ' << std::get<2>(Rgb) << std::endl;
		K++;
	  }
	}
	for (int &ColorValue: Colors) {
	  Image << ColorValue << ' ' << 0 << ' ' << 0 << std::endl;
	}
	Image.close();
	std::cout << "Saved to " << image_path_;
  } else
	std::cerr << "Could not open the file " << image_path_;
}
