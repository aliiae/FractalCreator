#include <sstream>
#include <utils.h>

std::string utils::formatDouble(double Double) {
  std::stringstream Stream;
  Stream.setf(std::ios::fixed);
  Stream.precision(1);
  Stream << Double;
  return Stream.str();
}
