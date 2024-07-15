#include "collision.hpp"
#include "framerate.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <format>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

int lastRand = 0;

enum Direction { forward, backward, upward, downward };

Texture2D farrow;
Texture2D barrow;
Texture2D uarrow;
Texture2D darrow;

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

int main(int argc, char **argv) {
  if (argc != 1) {
    std::cout << argv[0] << "takes no arguments.\n";
    return 1;
  }

  int framerate = get_framerate();
  std::string msg = "== first, frame ==";
  float accel_x = 4.0;
  float accel_y = 4.0;

  Vector2 ballPosition = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tiramisu");
  SetTargetFPS(framerate);

  std::cout << "preloading textures.." << std::endl;
  preload_direction_textures();
  std::cout << "preload done." << std::endl;

  screenWidth = SCREEN_HEIGHT;
  screenHeight = SCREEN_HEIGHT;

  while (!WindowShouldClose()) {
    if (GetScreenWidth() != screenWidth) {
      int tmpFramerate = get_framerate();
      if (tmpFramerate != framerate) {
        SetTargetFPS(tmpFramerate);
        framerate = tmpFramerate;
      }
    }

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    BeginDrawing();

    if (IsKeyDown(KEY_RIGHT))
      accel_x = std::abs(accel_x);
    if (IsKeyDown(KEY_LEFT))
      accel_x = -std::abs(accel_x);
    if (IsKeyDown(KEY_UP))
      accel_y = -std::abs(accel_y);
    if (IsKeyDown(KEY_DOWN))
      accel_y = std::abs(accel_y);

    ClearBackground({30, 30, 46, 255});

    DrawCircleV(ballPosition, CIRCLE_RAD, {203, 166, 247, 255});

    EndDrawing();

    collision(&ballPosition, accel_x, accel_y);
    std::vector<Texture2D> arrows = set_ui_direction(&msg, accel_x, accel_y);

    int widget_offset = 20;
    int widget_gap = 60;
    for (unsigned long i = 0; i < arrows.size(); i++) {
      DrawTexture(arrows[i], widget_offset + widget_gap * i, 10,
                  {137, 180, 250, 255});
    }

    // directions at center
    const unsigned int text_len = TextLength(msg.c_str()) * FONT_SIZE;
    DrawText(msg.c_str(), ((screenWidth / 2) - (text_len / 4)),
             screenHeight / 2, FONT_SIZE, {88, 91, 112, 255});

    const unsigned int speed_len = TextLength(std::to_string(accel_y).c_str()) +
                                   TextLength("Acceleration Z: ") * FONT_SIZE;
    DrawText(std::format("Acceleration X: {}", accel_x).c_str(),
             screenWidth - speed_len - widget_offset, screenHeight - FONT_SIZE,
             FONT_SIZE, {88, 91, 112, 255});
    DrawText(std::format("Acceleration Y: {}", accel_y).c_str(),
             screenWidth - speed_len - widget_offset,
             screenHeight - FONT_SIZE * 2, FONT_SIZE, {88, 91, 112, 255});

    ballPosition.x += accel_x;
    ballPosition.y += accel_y;
  }

  CloseWindow();

  return 0;
}
