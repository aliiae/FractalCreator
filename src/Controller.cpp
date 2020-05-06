#include <Controller.h>
Controller::Controller(std::shared_ptr<Fractal> fractal)
    : fractal_(std::move(fractal)) {}
bool Controller::ChangeZoom(SDL_Event &event) {
  bool position_changed{true};
  auto area = fractal_->GetArea();
  double delta = 0.1;
  double width_delta = area.GetWidth() * delta;
  double height_delta = area.GetHeight() * delta;
  switch (event.key.keysym.sym) {
    case SDLK_w:
    case SDLK_UP: {
      MoveUp(area, width_delta);
      break;
    }
    case SDLK_s:
    case SDLK_DOWN: {
      MoveDown(area, height_delta);
      break;
    }
    case SDLK_a:
    case SDLK_LEFT: {
      MoveLeft(area, width_delta);
      break;
    }
    case SDLK_d:
    case SDLK_RIGHT: {
      MoveRight(area, width_delta);
      break;
    }
    case SDLK_KP_EQUALS:
    case SDLK_KP_PLUS:
    case SDLK_EQUALS:
    case SDLK_PLUS: {
      ZoomIn(area, width_delta, height_delta);
      break;
    }
    case SDLK_MINUS:
    case SDLK_KP_MINUS: {
      ZoomOut(area, width_delta, height_delta);
      break;
    }
    default: {
      position_changed = false;
    }
  }
  return position_changed;
}
void Controller::ZoomOut(Area<double> &new_area, double width_delta,
                         double height_delta) const {
  new_area.SetXMin(new_area.GetXMin() - width_delta);
  new_area.SetXMax(new_area.GetXMax() + width_delta);
  new_area.SetYMin(new_area.GetYMin() - height_delta);
  new_area.SetYMax(new_area.GetYMax() + height_delta);
  fractal_->SetArea(new_area);
}
void Controller::ZoomIn(Area<double> &new_area, double width_delta,
                        double height_delta) const {
  new_area.SetXMin(new_area.GetXMin() + width_delta);
  new_area.SetXMax(new_area.GetXMax() - width_delta);
  new_area.SetYMin(new_area.GetYMin() + height_delta);
  new_area.SetYMax(new_area.GetYMax() - height_delta);
  fractal_->SetArea(new_area);
}
void Controller::MoveRight(Area<double> &new_area, double width_delta) const {
  new_area.SetXMin(new_area.GetXMin() + width_delta);
  new_area.SetXMax(new_area.GetXMax() + width_delta);
  fractal_->SetArea(new_area);
}
void Controller::MoveLeft(Area<double> &new_area, double width_delta) const {
  new_area.SetXMin(new_area.GetXMin() - width_delta);
  new_area.SetXMax(new_area.GetXMax() - width_delta);
  fractal_->SetArea(new_area);
}
void Controller::MoveDown(Area<double> &new_area, double height_delta) const {
  new_area.SetYMin(new_area.GetYMin() + height_delta);
  new_area.SetYMax(new_area.GetYMax() + height_delta);
  fractal_->SetArea(new_area);
}
void Controller::MoveUp(Area<double> &new_area, double width_delta) const {
  new_area.SetYMin(new_area.GetYMin() - width_delta);
  new_area.SetYMax(new_area.GetYMax() - width_delta);
  fractal_->SetArea(new_area);
}
