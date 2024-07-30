#include <raylib.h>
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

int getFramerate() {
  std::vector<int> refreshRates;
  for (int i = 0; i < GetMonitorCount(); i++) {
    refreshRates.push_back(GetMonitorRefreshRate(i));
  }

  return utils::maxAt(refreshRates);
}
}  // namespace utils
