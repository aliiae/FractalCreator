#ifndef FRACTALCREATOR_INCLUDE_CREATOR_H
#define FRACTALCREATOR_INCLUDE_CREATOR_H

#include "Fractal.h"
#include "utils.h"
#include <string>
#include <utility>

class Creator {
public:
  explicit Creator(std::string ImagePath, int Width, int Height,
                   int MaxIterations, std::shared_ptr<Fractal> Fractal)
      : image_path_(ImagePath), width_(Width), height_(Height),
        max_iterations_(MaxIterations), fractal_(Fractal){};
  void draw();

private:
  int width_;
  int height_;
  int max_iterations_;
  std::string image_path_;
  std::shared_ptr<Fractal> fractal_;
};

#endif // FRACTALCREATOR_INCLUDE_CREATOR_H
