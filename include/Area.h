#ifndef FRACTALCREATOR_INCLUDE_AREA_H_
#define FRACTALCREATOR_INCLUDE_AREA_H_

template <typename T>
class Area {
 public:
  [[maybe_unused]] Area(T x_min, T x_max, T y_min, T y_max)
      : x_min_(x_min), x_max_(x_max), y_min_(y_min), y_max_(y_max){};

  T GetWidth() { return (x_max_ - x_min_); }
  T GetHeight() { return (y_max_ - y_min_); }

  T GetXMin() const { return x_min_; }
  T GetYMin() const { return y_min_; }
  void SetYMax(T y_max) { y_max_ = y_max; }
  void SetXMin(T x_min) { x_min_ = x_min; }
  T GetXMax() const { return x_max_; }
  void SetXMax(T x_max) { x_max_ = x_max; }
  void SetYMin(T y_min) { y_min_ = y_min; }
  T GetYMax() const { return y_max_; }

 private:
  T x_min_, x_max_, y_min_, y_max_;
};

#endif  // FRACTALCREATOR_INCLUDE_AREA_H_
