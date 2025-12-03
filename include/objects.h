#pragma once

#include <stdint.h>

struct Color {

    uint8_t r;
    uint8_t g;
    uint8_t b;

};

struct Triangle {

    glm::vec3 p0;
    glm::vec3 p1;
    glm::vec3 p2;

    // TODO: add triangle ID and texture map

};
