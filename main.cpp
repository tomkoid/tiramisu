#include "collision.h"
#include "framerate.h"
#include "globals.h"
#include "textures.h"
#include "ui.h"
#include <cstdlib>
#include <format>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

int lastRand = 0;

float increment_speed(float accel_var, float accel_adder) {
  if (accel_var > 0) {
    return accel_var + accel_adder;
  } else if (accel_var < 0) {
    return accel_var - accel_adder;
  } else {
    return accel_var;
  }
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
  int wall_bounces = 0;

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
    int screenWidthTmp = GetScreenWidth();
    int screenHeightTmp = GetScreenHeight();

    if (screenWidthTmp != screenWidth) {
      int tmpFramerate = get_framerate();
      if (tmpFramerate != framerate) {
        SetTargetFPS(tmpFramerate);
        framerate = tmpFramerate;
      }
    }

    if (screenWidthTmp != screenWidth || screenHeightTmp != screenHeight) {
      SetWindowSize(screenWidthTmp, screenHeightTmp);
      screenWidth = screenWidthTmp;
      screenHeight = screenHeightTmp;
    }

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

    bool collided = collision(&ballPosition, wall_bounces, accel_x, accel_y);
    std::vector<Texture2D> arrows = set_ui_direction(&msg, accel_x, accel_y);

    int widget_offset = 20;
    int widget_gap = 60;
    int i = 0;
    for (Texture2D arrow : arrows) {
      DrawTexture(arrow, widget_offset + widget_gap * i, 10,
                  {137, 180, 250, 255});
      i++;
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

    // draw bounces
    DrawText(std::to_string(wall_bounces).c_str(),
             screenWidth -
                 TextLength(std::to_string(wall_bounces).c_str()) * FONT_SIZE -
                 widget_offset,
             0 + FONT_SIZE, FONT_SIZE * 2, WHITE);

    if (collided) {
      accel_x = increment_speed(accel_x, 0.001);
      accel_y = increment_speed(accel_y, 0.001);
    }

    ballPosition.x += accel_x * ((float)BASE_REFRESHRATE/GetFPS());
    ballPosition.y += accel_y * ((float)BASE_REFRESHRATE/GetFPS());
  }

  CloseWindow();

  return 0;
}
