#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <glm/glm.hpp>

#include "render.h"
#include "objects.h"
#include "utils.h"

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

    Color raycast(glm::vec3 origin, glm::vec3 direction);

    void render() {

        for (int i = 0; i < height; i++) {

            for (int j = 0; j < width; j++) {

                glm::vec3 origin(0.0f);
                glm::vec3 direction(1.0f);
                Color color = render::raycast(origin, direction);

                int offset = (i * width + j) * channels;
                render::image[offset + 0] = color.r; 
                render::image[offset + 1] = color.g;
                render::image[offset + 2] = color.b; 

            }

        }


    }

    void save() {

        stbi_write_bmp(filename, width, height, channels, render::image.data());

    }

}


namespace render {

    Color raycast(glm::vec3 origin, glm::vec3 direction) {

        glm::vec3 color(0.15f, 0.32f, 1.0f);
        return utils::color2hex(color);

    }

}
