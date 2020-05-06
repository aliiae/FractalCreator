#ifndef FRACTALCREATOR_INCLUDE_UTILS_H
#define FRACTALCREATOR_INCLUDE_UTILS_H
#include <string>

namespace utils {
struct RGB {
  int red;
  int green;
  int blue;
};
std::string formatDouble(double Double);
} // namespace utils
#endif // FRACTALCREATOR_INCLUDE_UTILS_H