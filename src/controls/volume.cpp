#include <raylib.h>
#include <chrono>
#include <iostream>

#include "../utils.h"

void toggleShowVolume(bool& showVolume, std::chrono::time_point<std::chrono::steady_clock>& showVolumeTimeDone) {
  showVolume         = true;
  showVolumeTimeDone = std::chrono::steady_clock::now() + std::chrono::seconds(1);
}

namespace controls {
  void handleVolumeControls(bool& showVolume, std::chrono::time_point<std::chrono::steady_clock>& showVolumeTimeDone) {
    bool changedVol = false;

    if (IsKeyPressed(KEY_MINUS)) {
      toggleShowVolume(showVolume, showVolumeTimeDone);

      if (utils::roundUp(GetMasterVolume(), 3) <= 0.1) {
        changedVol = true;
        SetMasterVolume(0.0);
      } else {
        double targetVol = utils::roundUp(GetMasterVolume() - 0.1, 3);
        changedVol       = true;
        SetMasterVolume(targetVol);
      }
    }
    if (IsKeyPressed(KEY_EQUAL)) {
      toggleShowVolume(showVolume, showVolumeTimeDone);

      if (GetMasterVolume() + 0.1 <= 1.0) {
        double targetVol = utils::roundUp(GetMasterVolume() + 0.1, 3);
        changedVol       = true;
        SetMasterVolume(targetVol);
      }
    }

    if (changedVol) {
      std::cout << "VOLUME: changed to " << GetMasterVolume() * 100 << "%" << std::endl;
    }
  }
} // namespace controls
