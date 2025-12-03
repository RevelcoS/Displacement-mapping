#pragma once

#include <stdint.h>

#include <vector>

namespace render {

    extern std::vector<uint8_t> image;

    void init();
    void render();
    void save();

}
