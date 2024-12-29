#include <raylib.h>
#include <string>
#include "src/globals.h"

namespace ui {
  void drawCenterDirections(std::string msg) {
    const unsigned int text_len = TextLength(msg.c_str()) * FONT_SIZE;
    DrawText(msg.c_str(), ((screenWidth / 2) - (text_len / 4)), screenHeight / 2, FONT_SIZE, {88, 91, 112, 255});
  }
} // namespace ui
