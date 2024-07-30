#ifndef UTILS_H
#define UTILS_H

#include <climits>
#include <numeric>
#include <string>
#include <vector>

namespace utils {
template <class T>
std::string join(std::string delimiter,
                 typename T::iterator begin,
                 typename T::iterator end) {
  if (begin == end) {
    return std::string();
  }
  if (std::next(begin) == end) {
    return std::string(*begin);
  }
  return std::accumulate(
      std::next(begin), end, *begin,
      [delimiter](const std::string a, const std::string b) -> std::string {
        return a + delimiter + b;
      });
}
int maxAt(std::vector<int>& vector_name);
int getFramerate();
double roundUp(double value, int decimal_places);
}  // namespace utils

#endif  // !UTILS_H
