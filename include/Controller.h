#ifndef FRACTALCREATOR_INCLUDE_CONTROLLER_H
#define FRACTALCREATOR_INCLUDE_CONTROLLER_H
#include <SDL_keycode.h>
#include <SDL_events.h>
#include <Fractal.h>
#include <memory>
#include <utility>

class Controller {
public:
  Controller(std::shared_ptr<Fractal> Fractal) : fractal_(std::move(Fractal)) {};
  bool changeZoom(SDL_Event &Event) {
	bool PositionChanged{true};
	auto NewArea = fractal_->getArea();
	double Delta = 0.1;
	double WidthDelta = NewArea.getWidth() * Delta;
	double HeightDelta = NewArea.getHeight() * Delta;
	switch (Event.key.keysym.sym) {
	case SDLK_w:
	case SDLK_UP: {
	  NewArea.setYMin(NewArea.getYMin() - WidthDelta);
	  NewArea.setYMax(NewArea.getYMax() - WidthDelta);
	  fractal_->setArea(NewArea);
	  break;
	}
	case SDLK_s:
	case SDLK_DOWN: {
	  NewArea.setYMin(NewArea.getYMin() + HeightDelta);
	  NewArea.setYMax(NewArea.getYMax() + HeightDelta);
	  fractal_->setArea(NewArea);
	  break;
	}
	case SDLK_a:
	case SDLK_LEFT: {
	  NewArea.setXMin(NewArea.getXMin() - WidthDelta);
	  NewArea.setXMax(NewArea.getXMax() - WidthDelta);
	  fractal_->setArea(NewArea);
	  break;
	}
	case SDLK_d:
	case SDLK_RIGHT: {
	  NewArea.setXMin(NewArea.getXMin() + WidthDelta);
	  NewArea.setXMax(NewArea.getXMax() + WidthDelta);
	  fractal_->setArea(NewArea);
	  break;
	}
	case SDLK_KP_EQUALS:
	case SDLK_KP_PLUS:
	case SDLK_EQUALS:
	case SDLK_PLUS: {
	  NewArea.setXMin(NewArea.getXMin() + WidthDelta);
	  NewArea.setXMax(NewArea.getXMax() - WidthDelta);
	  NewArea.setYMin(NewArea.getYMin() + HeightDelta);
	  NewArea.setYMax(NewArea.getYMax() - HeightDelta);
	  fractal_->setArea(NewArea);
	  break;
	}
	case SDLK_MINUS:
	case SDLK_KP_MINUS: {
	  NewArea.setXMin(NewArea.getXMin() - WidthDelta);
	  NewArea.setXMax(NewArea.getXMax() + WidthDelta);
	  NewArea.setYMin(NewArea.getYMin() - HeightDelta);
	  NewArea.setYMax(NewArea.getYMax() + HeightDelta);
	  fractal_->setArea(NewArea);
	  break;
	}
	default: {
	  PositionChanged = false;
	}
	}
	return PositionChanged;
  };

private:
  std::shared_ptr<Fractal> fractal_;
};
#endif //FRACTALCREATOR_INCLUDE_CONTROLLER_H
