#ifndef TEXTURES_H
#define TEXTURES_H

#include "collision.hpp"
#include <raylib.h>
inline Texture2D farrow;
inline Texture2D barrow;
inline Texture2D uarrow;
inline Texture2D darrow;

Texture2D get_direction_texture(Image image);
void preload_direction_textures();
Texture2D *load_direction_texture(Direction dir);

#endif // !TEXTURES_H
