#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "image_utils.h"

#include "../include/stb_image.h"
#include "../include/stb_image_write.h"

unsigned char* loadImage(
    const std::string& filename,
    int& width,
    int& height,
    int& channels)
{
    return stbi_load(
        filename.c_str(),
        &width,
        &height,
        &channels,
        0);
}

void saveImage(
    const std::string& filename,
    unsigned char* data,
    int width,
    int height,
    int channels)
{
    stbi_write_png(
        filename.c_str(),
        width,
        height,
        channels,
        data,
        width * channels);
}