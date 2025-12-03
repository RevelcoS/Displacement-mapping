#pragma once

struct HitInfo {

    bool hit = false;
    float t = 0.0f;
    glm::vec3 color = glm::vec3(0.0f);

};

HitInfo TriangleIntersect(const Triangle &triangle,
        glm::vec3 origin, glm::vec3 direction);
