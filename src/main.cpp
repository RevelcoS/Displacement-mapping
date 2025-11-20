#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include <vector>

// #include <glm/glm.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

// const glm::uvec2 dimensions = { 1024, 1024 };
const int width = 1024;
const int height = 1024;
const int channels = 3;

const char filename[32] = "out.bmp";

int main() {

    std::vector<uint8_t> image(width * height * channels);
    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            int offset = (i * width + j) * channels;
            image[offset + 0] = 255.0 * i / (height - 1);
            image[offset + 1] = 255.0 * j / (width - 1);
            image[offset + 2] = 255.0 * (width - j - 1) / (width - 1);

        }

    }

    stbi_write_bmp(filename, width, height, channels, image.data());

    return 0;

}
