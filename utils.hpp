#ifndef UTILS_H
#define UTILS_H

#include <numeric>
#include <string>

namespace utils {
template <class T>
std::string join(std::string delimiter, typename T::iterator begin,
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
} // namespace utils

#endif // !UTILS_H
