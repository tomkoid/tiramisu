#include <raylib.h>
#include <string>
#include "src/globals.h"

namespace ui {
  void drawBounces(int wall_bounces) {
    DrawText(std::to_string(wall_bounces).c_str(), screenWidth - TextLength(std::to_string(wall_bounces).c_str()) * FONT_SIZE - widget_offset, 0 + FONT_SIZE, FONT_SIZE * 2, WHITE);
  }
} // namespace ui
