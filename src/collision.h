#pragma once

#include <raylib.h>
bool collision(Vector2* ballPosition, int& wall_bounces, float& accel_x, float& accel_y);

enum Direction {
  forward,
  backward,
  upward,
  downward
};
