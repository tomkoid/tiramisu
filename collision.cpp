#include "globals.hpp"
#include <iostream>
#include <raylib.h>

const int RESET_OFFSET = 1;

void collision(Vector2 *ballPosition, int &wall_bounces, float &accel_x, float &accel_y) {
  // reverse direction
  if (ballPosition->y + CIRCLE_RAD >= screenHeight) {
    std::cout << "direction: reverse accel_y" << std::endl;
    ballPosition->y = screenHeight - CIRCLE_RAD - RESET_OFFSET;
    accel_y = -accel_y;
    wall_bounces++;
  } else if (ballPosition->x + CIRCLE_RAD >= screenWidth) {
    std::cout << "direction: reverse accel_x" << std::endl;
    ballPosition->x = screenWidth - CIRCLE_RAD - RESET_OFFSET;
    accel_x = -accel_x;
    wall_bounces++;
  } else if (ballPosition->y - CIRCLE_RAD <= 0) {
    std::cout << "direction: reverse accel_y" << std::endl;
    ballPosition->y = CIRCLE_RAD + RESET_OFFSET + 0;
    accel_y = -accel_y;
    wall_bounces++;
  } else if (ballPosition->x - CIRCLE_RAD <= 0) {
    std::cout << "direction: reverse accel_x" << std::endl;
    ballPosition->x = CIRCLE_RAD + RESET_OFFSET + 0;
    accel_x = -accel_x;
    wall_bounces++;
  }
}
