#include "Controller.h"
Controller::Controller(std::shared_ptr<Fractal> Fractal)
    : fractal_(std::move(Fractal)) {}
bool Controller::changeZoom(SDL_Event &Event) {
  bool PositionChanged{true};
  auto Area = fractal_->getArea();
  double Delta = 0.1;
  double WidthDelta = Area.getWidth() * Delta;
  double HeightDelta = Area.getHeight() * Delta;
  switch (Event.key.keysym.sym) {
  case SDLK_w:
  case SDLK_UP: {
    moveUp(Area, WidthDelta);
    break;
  }
  case SDLK_s:
  case SDLK_DOWN: {
    moveDown(Area, HeightDelta);
    break;
  }
  case SDLK_a:
  case SDLK_LEFT: {
    moveLeft(Area, WidthDelta);
    break;
  }
  case SDLK_d:
  case SDLK_RIGHT: {
    moveRight(Area, WidthDelta);
    break;
  }
  case SDLK_KP_EQUALS:
  case SDLK_KP_PLUS:
  case SDLK_EQUALS:
  case SDLK_PLUS: {
    zoomIn(Area, WidthDelta, HeightDelta);
    break;
  }
  case SDLK_MINUS:
  case SDLK_KP_MINUS: {
    zoomOut(Area, WidthDelta, HeightDelta);
    break;
  }
  default: {
    PositionChanged = false;
  }
  }
  return PositionChanged;
}
void Controller::zoomOut(Area<double> &NewArea, double WidthDelta,
                         double HeightDelta) const {
  NewArea.setXMin(NewArea.getXMin() - WidthDelta);
  NewArea.setXMax(NewArea.getXMax() + WidthDelta);
  NewArea.setYMin(NewArea.getYMin() - HeightDelta);
  NewArea.setYMax(NewArea.getYMax() + HeightDelta);
  fractal_->setArea(NewArea);
}
void Controller::zoomIn(Area<double> &NewArea, double WidthDelta,
                        double HeightDelta) const {
  NewArea.setXMin(NewArea.getXMin() + WidthDelta);
  NewArea.setXMax(NewArea.getXMax() - WidthDelta);
  NewArea.setYMin(NewArea.getYMin() + HeightDelta);
  NewArea.setYMax(NewArea.getYMax() - HeightDelta);
  fractal_->setArea(NewArea);
}
void Controller::moveRight(Area<double> &NewArea, double WidthDelta) const {
  NewArea.setXMin(NewArea.getXMin() + WidthDelta);
  NewArea.setXMax(NewArea.getXMax() + WidthDelta);
  fractal_->setArea(NewArea);
}
void Controller::moveLeft(Area<double> &NewArea, double WidthDelta) const {
  NewArea.setXMin(NewArea.getXMin() - WidthDelta);
  NewArea.setXMax(NewArea.getXMax() - WidthDelta);
  fractal_->setArea(NewArea);
}
void Controller::moveDown(Area<double> &NewArea, double HeightDelta) const {
  NewArea.setYMin(NewArea.getYMin() + HeightDelta);
  NewArea.setYMax(NewArea.getYMax() + HeightDelta);
  fractal_->setArea(NewArea);
}
void Controller::moveUp(Area<double> &NewArea, double WidthDelta) const {
  NewArea.setYMin(NewArea.getYMin() - WidthDelta);
  NewArea.setYMax(NewArea.getYMax() - WidthDelta);
  fractal_->setArea(NewArea);
}
