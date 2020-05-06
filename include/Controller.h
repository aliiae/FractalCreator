#ifndef FRACTALCREATOR_INCLUDE_CONTROLLER_H_
#define FRACTALCREATOR_INCLUDE_CONTROLLER_H_
#include <Fractal.h>
#include <SDL_events.h>
#include <SDL_keycode.h>

#include <memory>
#include <utility>

class Controller {
 public:
  explicit Controller(std::shared_ptr<Fractal> fractal);
  bool ChangeZoom(SDL_Event &event);

 private:
  std::shared_ptr<Fractal> fractal_;
  void MoveUp(Area<double> &new_area, double width_delta) const;
  void MoveDown(Area<double> &new_area, double height_delta) const;
  void MoveLeft(Area<double> &new_area, double width_delta) const;
  void MoveRight(Area<double> &new_area, double width_delta) const;
  void ZoomIn(Area<double> &new_area, double width_delta,
              double height_delta) const;
  void ZoomOut(Area<double> &new_area, double width_delta,
               double height_delta) const;
};
#endif  // FRACTALCREATOR_INCLUDE_CONTROLLER_H_
