#ifndef FRACTALCREATOR_INCLUDE_AREA_H
#define FRACTALCREATOR_INCLUDE_AREA_H
#include <string>

template<typename T> class Area {
public:
  [[maybe_unused]] Area(T XMin, T XMax, T YMin, T YMax)
	  : x_min_(XMin), x_max_(XMax), y_min_(YMin), y_max_(YMax) {};

  T width() { return (x_max_ - x_min_); }
  T height() { return (y_max_ - y_min_); }

  T getXMin() const { return x_min_; }
  T getYMin() const { return y_min_; }
  void setYMax(T YMax) { y_max_ = YMax; }
  void setXMin(T XMin) {
	x_min_ = XMin;
  }
  T getXMax() const {
	return x_max_;
  }
  void setXMax(T XMax) {
	x_max_ = XMax;
  }
  void setYMin(T YMin) {
	y_min_ = YMin;
  }
  T getYMax() const {
	return y_max_;
  }
  std::string toString() {
//    TODO:
	return "(" + std::to_string(x_min_) + "," + std::to_string(x_max_) + "," + std::to_string(y_min_) + " " + std::to_string(y_max_) + ")";
  }

private:
  T x_min_, x_max_, y_min_, y_max_;
};

#endif // FRACTALCREATOR_INCLUDE_AREA_H
