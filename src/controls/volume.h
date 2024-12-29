#pragma once

#include <raylib.h>
#include <chrono>

namespace controls {
  void handleVolumeControls(bool& showVolume, std::chrono::time_point<std::chrono::steady_clock>& showVolumeTimeDone);
}
