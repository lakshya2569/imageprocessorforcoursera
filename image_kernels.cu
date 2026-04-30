#include "image_kernels.h"
#include <math.h>

__global__
void grayscaleKernel(
    unsigned char* input,
    unsigned char* output,
    int width,
    int height,
    int channels)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= width || y >= height) return;

    int idx = (y * width + x) * channels;

    unsigned char r = input[idx];
    unsigned char g = input[idx + 1];
    unsigned char b = input[idx + 2];

    output[y * width + x] =
        (unsigned char)(0.299f * r +
                        0.587f * g +
                        0.114f * b);
}

__global__
void sobelKernel(
    unsigned char* input,
    unsigned char* output,
    int width,
    int height)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x <= 0 || y <= 0 ||
        x >= width - 1 ||
        y >= height - 1)
        return;

    int gx =
        -input[(y - 1) * width + (x - 1)] +
         input[(y - 1) * width + (x + 1)] +
        -2 * input[y * width + (x - 1)] +
         2 * input[y * width + (x + 1)] +
        -input[(y + 1) * width + (x - 1)] +
         input[(y + 1) * width + (x + 1)];

    int gy =
        -input[(y - 1) * width + (x - 1)] -
         2 * input[(y - 1) * width + x] -
         input[(y - 1) * width + (x + 1)] +
         input[(y + 1) * width + (x - 1)] +
         2 * input[(y + 1) * width + x] +
         input[(y + 1) * width + (x + 1)];

    int mag = sqrtf(gx * gx + gy * gy);

    if (mag > 255) mag = 255;

    output[y * width + x] =
        (unsigned char)mag;
}

void runGrayscale(
    unsigned char* input,
    unsigned char* output,
    int width,
    int height,
    int channels)
{
    dim3 block(16,16);
    dim3 grid(
        (width + 15)/16,
        (height + 15)/16);

    grayscaleKernel<<<grid,block>>>(
        input,
        output,
        width,
        height,
        channels);
}

void runSobel(
    unsigned char* input,
    unsigned char* output,
    int width,
    int height)
{
    dim3 block(16,16);
    dim3 grid(
        (width + 15)/16,
        (height + 15)/16);

    sobelKernel<<<grid,block>>>(
        input,
        output,
        width,
        height);
}