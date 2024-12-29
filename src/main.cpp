#include <raylib.h>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "collision.h"
#include "globals.h"
#include "src/controls/volume.h"
#include "src/ui/volume.h"
#include "textures.h"
#include "ui.h"
#include "ui/acceleration.h"
#include "ui/bounces.h"
#include "ui/center_directions.h"
#include "ui/volume.h"
#include "utils.h"

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

int main(int argc, char** argv) {
  if (argc != 1) {
    std::cout << argv[0] << "takes no arguments.\n";
    return 1;
  }

  int framerate    = utils::getFramerate();
  std::string msg  = "== first, frame ==";
  float accel_x    = 4.0;
  float accel_y    = 4.0;
  int wall_bounces = 0;

  Vector2 ballPosition = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};

  InitAudioDevice();
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tiramisu");
  SetTargetFPS(framerate);

  std::cout << "preloading textures.." << std::endl;
  preload_direction_textures();

  Wave bounceSoundWave = LoadWave("assets/bounce.wav");
  Sound bounceSound    = LoadSoundFromWave(bounceSoundWave);
  std::cout << "preload done." << std::endl;

  screenWidth  = SCREEN_HEIGHT;
  screenHeight = SCREEN_HEIGHT;

  bool showVolume = false;
  std::chrono::steady_clock::time_point showVolumeTimeDone;
  while (!WindowShouldClose()) {
    int screenWidthTmp  = GetScreenWidth();
    int screenHeightTmp = GetScreenHeight();

    if (screenWidthTmp != screenWidth) {
      int tmpFramerate = utils::getFramerate();
      if (tmpFramerate != framerate) {
        SetTargetFPS(tmpFramerate);
        framerate = tmpFramerate;
      }
    }

    if (screenWidthTmp != screenWidth || screenHeightTmp != screenHeight) {
      SetWindowSize(screenWidthTmp, screenHeightTmp);
      screenWidth  = screenWidthTmp;
      screenHeight = screenHeightTmp;
    }

    BeginDrawing();

    // direction control
    if (IsKeyPressed(KEY_RIGHT))
      accel_x = std::abs(accel_x);
    if (IsKeyPressed(KEY_LEFT))
      accel_x = -std::abs(accel_x);
    if (IsKeyPressed(KEY_UP))
      accel_y = -std::abs(accel_y);
    if (IsKeyPressed(KEY_DOWN))
      accel_y = std::abs(accel_y);

    // volume control
    controls::handleVolumeControls(showVolume, showVolumeTimeDone);

    ClearBackground({30, 30, 46, 255});

    DrawCircleV(ballPosition, CIRCLE_RAD, {203, 166, 247, 255});

    EndDrawing();

    bool collided                 = collision(&ballPosition, wall_bounces, accel_x, accel_y);
    std::vector<Texture2D> arrows = set_ui_direction(&msg, accel_x, accel_y);

    int i = 0;
    for (Texture2D arrow : arrows) {
      DrawTexture(arrow, widget_offset + widget_gap * i, 10, {137, 180, 250, 255});
      i++;
    }

    // directions at center
    ui::drawCenterDirections(msg);

    // acceleration controls
    ui::drawAccelerationControls(accel_x, accel_y);

    // draw bounces
    ui::drawBounces(wall_bounces);

    if (showVolume && std::chrono::steady_clock::now() < showVolumeTimeDone) {
      ui::drawVolume();
    } else {
      showVolume = false;
    }

    if (collided) {
      accel_x = increment_speed(accel_x, 0.001);
      accel_y = increment_speed(accel_y, 0.001);

      if (IsAudioDeviceReady()) {
        PlaySound(bounceSound);
      }
    }

    ballPosition.x += accel_x * ((float)BASE_REFRESHRATE / GetFPS());
    ballPosition.y += accel_y * ((float)BASE_REFRESHRATE / GetFPS());
  }

  UnloadSound(bounceSound);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}
