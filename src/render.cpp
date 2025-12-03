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

    Color get_color(glm::ivec2 coord);
    void render() {

        for (int i = 0; i < height; i++) {

            for (int j = 0; j < width; j++) {

                glm::ivec2 coord(i, j);
                Color color = render::get_color(coord);

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

    Color raycast(glm::vec3 origin, glm::vec3 direction);
    Color get_color(glm::ivec2 coord) {

        const float aspect_ratio = (float)width / height;
        const float camera_width = 100.0f;
        const float camera_height = camera_width / aspect_ratio;

        // Camera top left and bottom right position
        const glm::vec2 s1( -camera_width / 2,  camera_height / 2);
        const glm::vec2 s2(  camera_width / 2, -camera_height / 2);

        // Screen space uv coords
        const glm::vec2 pixel_size(1.0f / width, 1.0f / height);
        glm::vec2 uv = (glm::vec2(coord) + 0.5f) * pixel_size;

        // World space ray coords
        glm::vec2 ray = glm::mix(s1, s2, uv);
    
        // Ray origin and direction
        glm::vec3 direction( ray.x, ray.y, -1.0f );
        glm::vec3 origin(0.0f);

        // Raycast
        Color color = render::raycast(origin, direction);

        return color;

    }

    Color raycast(glm::vec3 origin, glm::vec3 direction) {

        glm::vec3 color(0.15f, 0.32f, 1.0f);
        return utils::color2hex(color);

    }

}
