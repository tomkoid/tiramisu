#ifndef COLLISION_H
#define COLLISION_H

#include <raylib.h>
void collision(Vector2 *ballPosition, float &accel_x, float &accel_y);

enum Direction { forward, backward, upward, downward };

#endif
