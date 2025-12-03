#include <cmath>

#include <glm/glm.hpp>

#include "objects.h"
#include "utils.h"

namespace utils {

    inline uint8_t component2hex(float from) {

        return (uint8_t)std::round(glm::clamp(from * 255.0f, 0.0f, 255.0f));

    }

    Color color2hex(glm::vec3 from) {

        Color to;
        to.r = component2hex(from.r);
        to.g = component2hex(from.g);
        to.b = component2hex(from.b);
        
        return to;

    }

}
