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
	bool ZoomChanged{true};
	auto ZoomArea = fractal_->getZoomArea();
	double WidthDelta = ZoomArea.width() * 0.1;
	double HeightDelta = ZoomArea.height() * 0.1;
	switch (Event.key.keysym.sym) {
	case SDLK_w:
	case SDLK_UP: {
	  ZoomArea.setYMin(ZoomArea.getYMin() - WidthDelta);
	  ZoomArea.setYMax(ZoomArea.getYMax() - WidthDelta);
	  fractal_->setZoomArea(ZoomArea);
	  break;
	}
	case SDLK_s:
	case SDLK_DOWN: {
	  ZoomArea.setYMin(ZoomArea.getYMin() + HeightDelta);
	  ZoomArea.setYMax(ZoomArea.getYMax() + HeightDelta);
	  fractal_->setZoomArea(ZoomArea);
	  break;
	}
	case SDLK_a:
	case SDLK_LEFT: {
	  ZoomArea.setXMin(ZoomArea.getXMin() - WidthDelta);
	  ZoomArea.setXMax(ZoomArea.getXMax() - WidthDelta);
	  fractal_->setZoomArea(ZoomArea);
	  break;
	}
	case SDLK_d:
	case SDLK_RIGHT: {
	  ZoomArea.setXMin(ZoomArea.getXMin() + WidthDelta);
	  ZoomArea.setXMax(ZoomArea.getXMax() + WidthDelta);
	  fractal_->setZoomArea(ZoomArea);
	  break;
	}
	case SDLK_KP_EQUALS:
	case SDLK_KP_PLUS:
	case SDLK_EQUALS:
	case SDLK_PLUS: {
	  ZoomArea.setXMin(ZoomArea.getXMin() + WidthDelta);
	  ZoomArea.setXMax(ZoomArea.getXMax() - WidthDelta);
	  ZoomArea.setYMax(ZoomArea.getYMax() + HeightDelta);
	  ZoomArea.setYMin(ZoomArea.getYMin() - HeightDelta);
	  fractal_->setZoomArea(ZoomArea);
	  break;
	}
	case SDLK_MINUS:
	case SDLK_KP_MINUS: {
	  ZoomArea.setXMin(ZoomArea.getXMin() - WidthDelta);
	  ZoomArea.setXMax(ZoomArea.getXMax() + WidthDelta);
	  ZoomArea.setYMax(ZoomArea.getYMax() - HeightDelta);
	  ZoomArea.setYMin(ZoomArea.getYMin() + HeightDelta);
	  fractal_->setZoomArea(ZoomArea);
	  break;
	}
	default: {
	  ZoomChanged = false;
	}
	}
	return ZoomChanged;
  };

private:
  std::shared_ptr<Fractal> fractal_;
};
#endif //FRACTALCREATOR_INCLUDE_CONTROLLER_H
