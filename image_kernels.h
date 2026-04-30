#ifndef IMAGE_KERNELS_H
#define IMAGE_KERNELS_H

#include <cuda_runtime.h>

void runGrayscale(
    unsigned char* input,
    unsigned char* output,
    int width,
    int height,
    int channels
);

void runSobel(
    unsigned char* input,
    unsigned char* output,
    int width,
    int height
);

#endif