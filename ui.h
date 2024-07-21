#ifndef UI_H_
#define UI_H_

#include <raylib.h>
#include <string>
#include <vector>
std::vector<Texture2D> set_ui_direction(std::string *msg, float &accel_x,
                                        float &accel_y);
#endif // !UI_H_
