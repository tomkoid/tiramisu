#include "textures.h"
#include <raylib.h>
#include <cstddef>
#include <string>
#include <cstring>
#include "collision.h"
#include "globals.h"

#define NANOSVG_IMPLEMENTATION // Expands implementation
#include "../libs/nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "../libs/nanosvgrast.h"

Image LoadImageSVG(const char* fileName, int width, int height) {
  Image image = {0, 0, 0, 0, 0};

  std::string fileExtension = GetFileExtension(fileName);
  if (fileExtension == ".svg" || fileExtension == ".SVG") {
    int dataSize            = 0;
    unsigned char* fileData = LoadFileData(fileName, &dataSize);

    if (fileData != nullptr) {
      // Ensure file data ends with a null terminator
      if (dataSize > 0 && fileData[dataSize - 1] != '\0') {
        fileData           = static_cast<unsigned char*>(RL_REALLOC(fileData, dataSize + 1));
        fileData[dataSize] = '\0';
        dataSize += 1;
      }

      // Validate the file data as valid SVG content
      if (std::strncmp(reinterpret_cast<const char*>(fileData), "<svg", 4) == 0) {
        NSVGimage* svgImage = nsvgParse(reinterpret_cast<char*>(fileData), "px", 96.0f);
        if (svgImage != nullptr) {
          // Adjust width and height if necessary
          if (width == 0)
            width = static_cast<int>(svgImage->width);
          if (height == 0)
            height = static_cast<int>(svgImage->height);

          // Calculate the scale for rendering
          float scaleWidth  = static_cast<float>(width) / svgImage->width;
          float scaleHeight = static_cast<float>(height) / svgImage->height;
          float scale       = std::min(scaleWidth, scaleHeight);

          // Center the image if necessary
          int offsetX = (scaleHeight > scaleWidth) ? 0 : (width - static_cast<int>(svgImage->width * scale)) / 2;
          int offsetY = (scaleHeight > scaleWidth) ? (height - static_cast<int>(svgImage->height * scale)) / 2 : 0;

          // Allocate memory for the rasterized image
          auto imgData = static_cast<unsigned char*>(RL_MALLOC(width * height * 4));

          // Rasterize the SVG
          NSVGrasterizer* rasterizer = nsvgCreateRasterizer();
          nsvgRasterize(rasterizer, svgImage, offsetX, offsetY, scale, imgData, width, height, width * 4);

          // Populate the Image struct
          image.data    = imgData;
          image.width   = width;
          image.height  = height;
          image.mipmaps = 1;
          image.format  = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

          // Clean up resources
          nsvgDelete(svgImage);
          nsvgDeleteRasterizer(rasterizer);
        }
      }
      UnloadFileData(fileData);
    }
  }

  return image;
}

Texture2D get_direction_texture(Image image) {
  ImageColorBrightness(&image, 100);
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);

  return texture;
}

Image load_svg(const char* path) {
  return LoadImageSVG(path, DIR_ARROW_SIZE, DIR_ARROW_SIZE);
}

void preload_direction_textures() {
  farrow = get_direction_texture(load_svg("assets/arrow-forward.svg"));

  barrow = get_direction_texture(load_svg("assets/arrow-backward.svg"));
  uarrow = get_direction_texture(load_svg("assets/arrow-upward.svg"));
  darrow = get_direction_texture(load_svg("assets/arrow-downward.svg"));
}

Texture2D* load_direction_texture(Direction dir) {
  switch (dir) {
    case Direction::forward: return &farrow;
    case Direction::backward: return &barrow;
    case Direction::upward: return &uarrow;
    case Direction::downward: return &darrow;
  }

  return NULL;
}
