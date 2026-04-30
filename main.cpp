#include <iostream>
#include <filesystem>
#include <vector>
#include <cuda_runtime.h>

#include "image_utils.h"
#include "image_kernels.h"

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cout <<
        "Usage:\n"
        "./image_processor input_folder output_folder\n";
        return 1;
    }

    std::string inputFolder = argv[1];
    std::string outputFolder = argv[2];

    fs::create_directories(outputFolder);

    for (auto& entry :
         fs::directory_iterator(inputFolder))
    {
        std::string file =
            entry.path().string();

        int width, height, channels;

        unsigned char* hostInput =
            loadImage(file,
                      width,
                      height,
                      channels);

        if (!hostInput)
        {
            std::cout <<
            "Failed to load: "
            << file << "\n";
            continue;
        }

        size_t rgbSize =
            width * height * channels;

        size_t graySize =
            width * height;

        unsigned char *d_input,
                      *d_gray,
                      *d_sobel;

        cudaMalloc(&d_input,
                   rgbSize);

        cudaMalloc(&d_gray,
                   graySize);

        cudaMalloc(&d_sobel,
                   graySize);

        cudaMemcpy(
            d_input,
            hostInput,
            rgbSize,
            cudaMemcpyHostToDevice);

        runGrayscale(
            d_input,
            d_gray,
            width,
            height,
            channels);

        runSobel(
            d_gray,
            d_sobel,
            width,
            height);

        std::vector<unsigned char>
            result(graySize);

        cudaMemcpy(
            result.data(),
            d_sobel,
            graySize,
            cudaMemcpyDeviceToHost);

        std::string outFile =
            outputFolder +
            "/processed_" +
            entry.path().filename().string();

        saveImage(
            outFile,
            result.data(),
            width,
            height,
            1);

        cudaFree(d_input);
        cudaFree(d_gray);
        cudaFree(d_sobel);

        stbi_image_free(hostInput);

        std::cout <<
        "Processed: "
        << file << "\n";
    }

    std::cout <<
    "All images processed.\n";

    return 0;
}