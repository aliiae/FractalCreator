#ifndef FRACTALCREATOR_INCLUDE_AREA_H
#define FRACTALCREATOR_INCLUDE_AREA_H

template <typename T> class Area {
public:
  [[maybe_unused]] Area(T XMin, T XMax, T YMin, T YMax)
      : x_min(XMin), x_max(XMax), y_min(YMin), y_max(YMax){};

  T width() { return (x_max - x_min); }
  T height() { return (y_max - y_min); }

  T getXMin() const { return x_min; }
  T getYMin() const { return y_min; }
  void setYMax(T YMax) { y_max = YMax; }

private:
  T x_min, x_max, y_min, y_max;
};

#endif // FRACTALCREATOR_INCLUDE_AREA_H
