#include <utils.h>

#include <sstream>

/**
 * Formats the double with precision 1.
 */
std::string utils::FormatDouble(double double_value) {
  std::stringstream stream;
  stream.setf(std::ios::fixed);
  stream.precision(1);
  stream << double_value;
  return stream.str();
}
