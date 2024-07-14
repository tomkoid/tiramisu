#include "globals.hpp"
#include <iostream>
#include <raylib.h>

void collision(Vector2 *ballPosition, int &accel_x, int &accel_y) {
  if (ballPosition->y + CIRCLE_RAD >= SCREEN_HEIGHT) {
    std::cout << "direction: reverse accel_y" << std::endl;
    accel_y = -accel_y;
  } else if (ballPosition->x + CIRCLE_RAD >= SCREEN_WIDTH) {
    std::cout << "direction: reverse accel_x" << std::endl;
    accel_x = -accel_x;
  } else if (ballPosition->y - CIRCLE_RAD <= 0) {
    std::cout << "direction: reverse accel_y" << std::endl;
    accel_y = -accel_y;
  } else if (ballPosition->x - CIRCLE_RAD <= 0) {
    std::cout << "direction: reverse accel_x" << std::endl;
    accel_x = -accel_x;
  }
}
