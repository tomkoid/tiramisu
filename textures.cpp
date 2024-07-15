#include "textures.hpp"
#include "collision.hpp"
#include "globals.hpp"
#include <raylib.h>

Texture2D get_direction_texture(Image image) {
  ImageColorBrightness(&image, 100);
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);

  return texture;
}

void preload_direction_textures() {
  farrow = get_direction_texture(
      LoadImageSvg("assets/arrow-forward.svg", DIR_ARROW_SIZE, DIR_ARROW_SIZE));

  barrow = get_direction_texture(LoadImageSvg("assets/arrow-backward.svg",
                                              DIR_ARROW_SIZE, DIR_ARROW_SIZE));
  uarrow = get_direction_texture(
      LoadImageSvg("assets/arrow-upward.svg", DIR_ARROW_SIZE, DIR_ARROW_SIZE));
  darrow = get_direction_texture(LoadImageSvg("assets/arrow-downward.svg",
                                              DIR_ARROW_SIZE, DIR_ARROW_SIZE));
}

Texture2D *load_direction_texture(Direction dir) {
  switch (dir) {
  case Direction::forward:
    return &farrow;
  case Direction::backward:
    return &barrow;
  case Direction::upward:
    return &uarrow;
  case Direction::downward:
    return &darrow;
  }
}
