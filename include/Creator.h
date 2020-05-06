#ifndef FRACTALCREATOR_INCLUDE_CREATOR_H_
#define FRACTALCREATOR_INCLUDE_CREATOR_H_

#include <Controller.h>
#include <Fractal.h>
#include <Renderer.h>
#include <utils.h>

#include <future>
#include <string>
#include <utility>
#include <vector>

class Creator {
 public:
  Creator(int width, int height, int max_iterations,
          std::shared_ptr<Fractal> fractal);
  std::vector<unsigned char> &GetPixels();

 private:
  int width_;
  int height_;
  int max_iterations_;
  static utils::RGB ToRgb(double t);
  std::shared_ptr<Fractal> fractal_;
  std::vector<unsigned char> pixels_;
  [[nodiscard]] double ConvertY(int row) const;
  [[nodiscard]] double ConvertX(int col) const;
  std::vector<std::future<std::vector<utils::RGB>>> future_rows_;
};

#endif  // FRACTALCREATOR_INCLUDE_CREATOR_H_
