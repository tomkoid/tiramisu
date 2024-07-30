#include <raylib.h>
#include <iostream>
#include "globals.h"

const int RESET_OFFSET = 1;

// returns if collided
bool collision(Vector2* ballPosition,
               int& wall_bounces,
               float& accel_x,
               float& accel_y) {
  bool collided = false;

  // reverse direction
  if (ballPosition->y + CIRCLE_RAD >= screenHeight) {
    std::cout << "direction: reverse accel_y" << std::endl;
    ballPosition->y = screenHeight - CIRCLE_RAD - RESET_OFFSET;
    accel_y = -accel_y;
    wall_bounces++;
    collided = true;
  } else if (ballPosition->x + CIRCLE_RAD >= screenWidth) {
    std::cout << "direction: reverse accel_x" << std::endl;
    ballPosition->x = screenWidth - CIRCLE_RAD - RESET_OFFSET;
    accel_x = -accel_x;
    wall_bounces++;
    collided = true;
  } else if (ballPosition->y - CIRCLE_RAD <= 0) {
    std::cout << "direction: reverse accel_y" << std::endl;
    ballPosition->y = CIRCLE_RAD + RESET_OFFSET + 0;
    accel_y = -accel_y;
    wall_bounces++;
    collided = true;
  } else if (ballPosition->x - CIRCLE_RAD <= 0) {
    std::cout << "direction: reverse accel_x" << std::endl;
    ballPosition->x = CIRCLE_RAD + RESET_OFFSET + 0;
    accel_x = -accel_x;
    wall_bounces++;
    collided = true;
  }

  return collided;
}
