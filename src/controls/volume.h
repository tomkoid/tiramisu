#ifndef VOLUME_H
#define VOLUME_H

#include <raylib.h>
#include <chrono>

namespace controls {
void handleVolumeControls(
    bool &showVolume,
    std::chrono::time_point<std::chrono::steady_clock> &showVolumeTimeDone);
}

#endif  // !VOLUME_H
