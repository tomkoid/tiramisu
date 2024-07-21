#include <climits>
#include <vector>

namespace utils {
int maxAt(std::vector<int> &vector_name) {
  int max = INT_MIN;
  for (auto val : vector_name) {
    if (max < val)
      max = val;
  }
  return max;
}
} // namespace utils
