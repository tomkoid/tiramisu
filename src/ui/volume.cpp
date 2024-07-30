#include <raylib.h>
#include <format>
#include "src/globals.h"

namespace ui {
void drawVolume() {
  DrawText(std::format("Volume: {:.0f} %", GetMasterVolume() * 100).c_str(), 10,
           10, FONT_SIZE, {88, 91, 112, 255});
}
}  // namespace ui
