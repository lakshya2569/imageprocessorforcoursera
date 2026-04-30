#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <string>

unsigned char* loadImage(
    const std::string& filename,
    int& width,
    int& height,
    int& channels
);

void saveImage(
    const std::string& filename,
    unsigned char* data,
    int width,
    int height,
    int channels
);

#endif