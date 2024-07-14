#include "framerate.hpp"
#include <cstdlib>
#include <format>
#include <iostream>
#include <numeric>
#include <raylib.h>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define FONT_SIZE 20
#define CIRCLE_RAD 10
#define DIR_ARROW_SIZE 50

int lastRand = 0;

template <class T>
std::string join(std::string delimiter, typename T::iterator begin,
                 typename T::iterator end) {

  if (begin == end) {
    return std::string();
  }
  if (std::next(begin) == end) {
    return std::string(*begin);
  }
  return std::accumulate(
      std::next(begin), end, *begin,
      [delimiter](const std::string a, const std::string b) -> std::string {
        return a + delimiter + b;
      });
}

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

std::vector<Texture2D> set_ui_direction(std::string *msg, int &accel_x,
                                        int &accel_y) {
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

  *msg = std::format("== {} ==", join<std::vector<std::string>>(
                                     ", ", direction.begin(), direction.end()));

  return ui_arrow_textures;
}

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

int main(int argc, char **argv) {
  if (argc != 1) {
    std::cout << argv[0] << "takes no arguments.\n";
    return 1;
  }

  int framerate = get_framerate();
  std::string msg = "== first, frame ==";
  int accel_x = 4;
  int accel_y = 4;

  Vector2 ballPosition = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tiramisu");
  SetTargetFPS(framerate);

  std::cout << "preloading textures.." << std::endl;
  preload_direction_textures();
  std::cout << "preload done." << std::endl;

  while (!WindowShouldClose()) {
    BeginDrawing();

    /*DrawTexture(arrow_backwards_text, 0, 0, WHITE);*/
    /*ImageDrawPixel(&arrow_backwards, 0, 0, RAYWHITE);*/

    if (IsKeyDown(KEY_RIGHT))
      accel_x = abs(accel_x);
    if (IsKeyDown(KEY_LEFT))
      accel_x = -abs(accel_x);
    if (IsKeyDown(KEY_UP))
      accel_y = -abs(accel_y);
    if (IsKeyDown(KEY_DOWN))
      accel_y = abs(accel_y);

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

    const unsigned int text_len = TextLength(msg.c_str()) * FONT_SIZE;
    DrawText(msg.c_str(), ((SCREEN_WIDTH / 2) - (text_len / 4)),
             SCREEN_HEIGHT / 2, FONT_SIZE, {88, 91, 112, 255});

    ballPosition.x += accel_x;
    ballPosition.y += accel_y;
  }

  CloseWindow();

  return 0;
}
