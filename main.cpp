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

void get_bg_text(std::string *msg, int &accel_x, int &accel_y) {
  std::vector<std::string> direction;

  if (accel_x > 0) {
    direction.push_back("forwards");
  }
  if (accel_x < 0) {
    direction.push_back("backwards");
  }
  if (accel_y < 0) {
    direction.push_back("upwards");
  }
  if (accel_y > 0) {
    direction.push_back("downwards");
  }

  *msg = std::format("== {} ==", join<std::vector<std::string>>(
                                     ", ", direction.begin(), direction.end()));
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

  while (!WindowShouldClose()) {
    BeginDrawing();

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
    get_bg_text(&msg, accel_x, accel_y);

    const unsigned int text_len = TextLength(msg.c_str()) * FONT_SIZE;
    DrawText(msg.c_str(), ((SCREEN_WIDTH / 2) - (text_len / 4)),
             SCREEN_HEIGHT / 2, FONT_SIZE, {88, 91, 112, 255});

    ballPosition.x += accel_x;
    ballPosition.y += accel_y;
  }

  CloseWindow();

  return 0;
}
