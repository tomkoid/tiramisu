#include <raylib.h>
#include <format>
#include <string>
#include "src/globals.h"

namespace ui {
void drawAccelerationControls(float &accel_x, float &accel_y) {
  const unsigned int speed_len = TextLength(std::to_string(accel_y).c_str()) +
                                 TextLength("Acceleration Z: ") * FONT_SIZE;
  DrawText(std::format("Acceleration X: {}", accel_x).c_str(),
           screenWidth - speed_len - widget_offset, screenHeight - FONT_SIZE,
           FONT_SIZE, {88, 91, 112, 255});
  DrawText(std::format("Acceleration Y: {}", accel_y).c_str(),
           screenWidth - speed_len - widget_offset,
           screenHeight - FONT_SIZE * 2, FONT_SIZE, {88, 91, 112, 255});
}
}  // namespace ui
