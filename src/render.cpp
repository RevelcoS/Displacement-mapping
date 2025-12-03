#include "render.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

const int width = 1024;
const int height = 1024;
const int channels = 3;

const char filename[32] = "out.bmp";

namespace render {

    std::vector<uint8_t> image;

}

namespace render {

    void init() {

        render::image.resize(width * height * channels);

    }

    void render() {

        for (int i = 0; i < height; i++) {

            for (int j = 0; j < width; j++) {

                int offset = (i * width + j) * channels;
                render::image[offset + 0] = 255.0 * i / (height - 1);
                render::image[offset + 1] = 255.0 * j / (width - 1);
                render::image[offset + 2] = 255.0 * (width - j - 1) / (width - 1);

            }

        }


    }

    void save() {

        stbi_write_bmp(filename, width, height, channels, render::image.data());

    }

}
