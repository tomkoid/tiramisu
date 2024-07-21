#include "textures.h"
#include "utils.h"
#include "collision.h"
#include <format>
#include <raylib.h>
#include <string>
#include <vector>

std::vector<Texture2D> set_ui_direction(std::string *msg, float &accel_x,
                                        float &accel_y) {
  std::vector<std::string> direction;
  std::vector<Texture2D> ui_arrow_textures;

  if (accel_x > 0) {
    direction.push_back("forwards");
    ui_arrow_textures.push_back(*load_direction_texture(Direction::forward));
  }
  if (accel_x < 0) {
    direction.push_back("backwards");
    ui_arrow_textures.push_back(*load_direction_texture(Direction::backward));
  }
  if (accel_y < 0) {
    direction.push_back("upwards");
    ui_arrow_textures.push_back(*load_direction_texture(Direction::upward));
  }
  if (accel_y > 0) {
    direction.push_back("downwards");
    ui_arrow_textures.push_back(*load_direction_texture(Direction::downward));
  }

  *msg = std::format("== {} ==", utils::join<std::vector<std::string>>(
                                     ", ", direction.begin(), direction.end()));

  return ui_arrow_textures;
}

