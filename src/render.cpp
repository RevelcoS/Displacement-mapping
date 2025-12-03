#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <glm/glm.hpp>

#include "render.h"
#include "utils.h"
#include "objects.h"
#include "triangle.h"

const int width = 1024;
const int height = 1024;
const int channels = 3;

const char filename[32] = "out.bmp";

namespace render {

    std::vector<uint8_t> image;

}

// Interface functions
namespace render {

    void init() {

        render::image.resize(width * height * channels);

    }

    Color get_color(glm::ivec2 coord);
    void render() {

        for (int i = 0; i < height; i++) {

            for (int j = 0; j < width; j++) {

                glm::ivec2 coord(j, i);
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

// Base raycast functions
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
        glm::vec3 direction = glm::normalize(glm::vec3( ray.x, ray.y, -1.0f ));
        glm::vec3 origin(0.0f);

        // Raycast
        Color color = render::raycast(origin, direction);

        return color;

    }

    Color raycast(glm::vec3 origin, glm::vec3 direction) {

        const Triangle triangle = {

            glm::vec3(30.0f, 28.0f, -1.0f),
            glm::vec3(-21.0f, 20.0f, -1.0f),
            glm::vec3(-30.0f, -40.0f, -1.0f)

            // glm::vec3(0.0f, 1.0f, -1.0f),
            // glm::vec3(-1.0f, -1.0f, -1.0f),
            // glm::vec3(1.0f, -1.0f, -1.0f)

        };

        HitInfo info = TriangleIntersect(triangle, origin, direction); 

        return utils::color2hex(info.color);

    }

}
