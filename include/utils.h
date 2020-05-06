#ifndef FRACTALCREATOR_INCLUDE_UTILS_H_
#define FRACTALCREATOR_INCLUDE_UTILS_H_
#include <string>

namespace utils {
struct RGB {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};
std::string FormatDouble(double double_value);
}  // namespace utils

#endif  // FRACTALCREATOR_INCLUDE_UTILS_H_