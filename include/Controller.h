#ifndef FRACTALCREATOR_INCLUDE_CONTROLLER_H
#define FRACTALCREATOR_INCLUDE_CONTROLLER_H
#include <Fractal.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <memory>
#include <utility>

class Controller {
public:
  explicit Controller(std::shared_ptr<Fractal> Fractal);
  bool changeZoom(SDL_Event &Event);

private:
  std::shared_ptr<Fractal> fractal_;
  void moveUp(Area<double> &NewArea, double WidthDelta) const;
  void moveDown(Area<double> &NewArea, double HeightDelta) const;
  void moveLeft(Area<double> &NewArea, double WidthDelta) const;
  void moveRight(Area<double> &NewArea, double WidthDelta) const;
  void zoomIn(Area<double> &NewArea, double WidthDelta,
              double HeightDelta) const;
  void zoomOut(Area<double> &NewArea, double WidthDelta,
               double HeightDelta) const;
};
#endif // FRACTALCREATOR_INCLUDE_CONTROLLER_H
