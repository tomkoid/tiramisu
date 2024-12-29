#pragma once
#include <raylib.h>
#include "collision.h"
inline Texture2D farrow;
inline Texture2D barrow;
inline Texture2D uarrow;
inline Texture2D darrow;

Texture2D get_direction_texture(Image image);
void preload_direction_textures();
Texture2D* load_direction_texture(Direction dir);
