#ifndef FRACTALCREATOR_INCLUDE_CREATOR_H
#define FRACTALCREATOR_INCLUDE_CREATOR_H

#include "Fractal.h"
#include "utils.h"
#include <future>
#include <string>
#include <utility>
#include <vector>

class Creator {
public:
  Creator(std::string ImagePath, int Width, int Height, int MaxIterations,
          std::unique_ptr<Fractal> Fractal)
      : image_path_(std::move(ImagePath)), width_(Width), height_(Height),
        max_iterations_(MaxIterations), fractal_(std::move(Fractal)) {
    rows_.resize(height_);
    future_rows_.resize(height_);
  };
  void draw();

private:
  int width_;
  int height_;
  int max_iterations_;
  std::string image_path_;
  std::unique_ptr<Fractal> fractal_;
  std::vector<std::future<std::vector<utils::RGB>>> future_rows_;
  std::vector<std::vector<utils::RGB>> rows_;
  static utils::RGB toRgb(double T);
  [[nodiscard]] double convertY(int Row) const;
  [[nodiscard]] double convertX(int Col) const;
};

#endif // FRACTALCREATOR_INCLUDE_CREATOR_H
