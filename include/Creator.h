#ifndef FRACTALCREATOR_INCLUDE_CREATOR_H
#define FRACTALCREATOR_INCLUDE_CREATOR_H

#include "Fractal.h"
#include "utils.h"
#include "Controller.h"
#include "Renderer.h"
#include <future>
#include <string>
#include <utility>
#include <vector>

class Creator {
public:
  Creator(int Width, int Height, int MaxIterations,
          std::shared_ptr<Fractal> Fractal);
  std::vector<unsigned char> &getPixels();
private:
  int width_;
  int height_;
  int max_iterations_;
  static utils::RGB toRgb(double T);
  std::shared_ptr<Fractal> fractal_;
  std::vector<unsigned char> pixels_;
  [[nodiscard]] double convertY(int Row) const;
  [[nodiscard]] double convertX(int Col) const;
  std::vector<std::future<std::vector<utils::RGB>>> future_rows_;
};

#endif // FRACTALCREATOR_INCLUDE_CREATOR_H
