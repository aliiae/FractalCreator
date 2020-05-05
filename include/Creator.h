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
  Creator(int Width, int Height, int MaxIterations,
          std::unique_ptr<Fractal> Fractal);;
  void draw();

private:
  int width_;
  int height_;
  int max_iterations_;
  std::unique_ptr<Fractal> fractal_;
  std::vector<std::future<std::vector<utils::RGB>>> future_rows_;
  std::vector<std::vector<utils::RGB>> rows_;
  static utils::RGB toRgb(double T);
  [[nodiscard]] double convertY(int Row) const;
  [[nodiscard]] double convertX(int Col) const;
};

#endif // FRACTALCREATOR_INCLUDE_CREATOR_H
