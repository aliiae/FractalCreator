#ifndef FRACTALCREATOR_SRC_AREA_H
#define FRACTALCREATOR_SRC_AREA_H

template<typename T>
class Area {
public:
  Area(T XMin, T XMax, T YMin, T YMax) : x_min(XMin), x_max(XMax), y_min(YMin), y_max(YMax) {};

  T size() {
	return (width()*height());
  }
  T width() {
	return (x_max - x_min);
  }
  T height() {
	return (y_max - y_min);
  }

  T getXMin() const {
	return x_min;
  }
  void setXMin(T XMin) {
	x_min = XMin;
  }
  T getXMax() const {
	return x_max;
  }
  void setXMax(T XMax) {
	x_max = XMax;
  }
  T getYMin() const {
	return y_min;
  }
  void setYMin(T YMin) {
	y_min = YMin;
  }
  T getYMax() const {
	return y_max;
  }
  void setYMax(T YMax) {
	y_max = YMax;
  }

private:
  T x_min, x_max, y_min, y_max;
};

#endif //FRACTALCREATOR_SRC_AREA_H
