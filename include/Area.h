#ifndef FRACTALCREATOR_INCLUDE_AREA_H
#define FRACTALCREATOR_INCLUDE_AREA_H

#include <string>

template<typename T> class Area {
public:
  [[maybe_unused]] Area(T XMin, T XMax, T YMin, T YMax)
	  : x_min(XMin), x_max(XMax), y_min(YMin), y_max(YMax) {};

  T width() { return (x_max - x_min); }
  T height() { return (y_max - y_min); }
  void setXMin(T XMin) {
	x_min = XMin;
  }
  void setXMax(T XMax) {
	x_max = XMax;
  }
  void setYMin(T YMin) {
	y_min = YMin;
  }
  T getXMin() const { return x_min; }
  T getXMax() const {
	return x_max;
  }
  T getYMax() const {
	return y_max;
  }
  T getYMin() const { return y_min; }
  void setYMax(T YMax) { y_max = YMax; }

private:
  T x_min, x_max, y_min, y_max;
};

#endif // FRACTALCREATOR_INCLUDE_AREA_H
