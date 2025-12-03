#include <glm/glm.hpp>

#include "objects.h"
#include "triangle.h"

glm::vec3 TriangleGetNormal(const Triangle &triangle) {

    glm::vec3 dp1 = triangle.p2 - triangle.p0;
    glm::vec3 dp2 = triangle.p1 - triangle.p0;
    return glm::normalize(glm::cross(dp1, dp2));

}

glm::vec2 TriangleGetBarycenticCoords(const Triangle &triangle,
        glm::vec3 position) {

    // p = u * p0 + v * p1 + (1 - u - v) * p2 <=>
    // dp = u * dp0 + v * dp1
    //
    // where
    // dp = p - p2
    // dp0 = p0 - p2
    // dp1 = p1 - p2

    glm::vec3 dp = position - triangle.p2;
    glm::vec3 dp0 = triangle.p0 - triangle.p2;
    glm::vec3 dp1 = triangle.p1 - triangle.p2;

    // Non-zero det, unless p0, p1 and p2 lie on one line
    float det = dp0.x * dp1.y - dp0.y * dp1.x;
    float u =   dp.x  * dp1.y - dp.y  * dp1.x;
    float v =   dp0.x * dp.y  - dp0.y * dp.x;

    return glm::vec2(u, v) / det;

}

HitInfo TriangleIntersect(const Triangle &triangle,
        glm::vec3 origin, glm::vec3 direction) {

    HitInfo info;

    // TODO: precompute normal
    glm::vec3 normal = TriangleGetNormal(triangle);
    glm::vec3 torigin = triangle.p0;

    glm::vec3 dp = origin - torigin;

    // Normal looks at me
    if (glm::dot(dp, normal) < 0)
        normal = -normal;

    // If I look away from the plane, then nothing to intersect
    if (glm::dot(direction, normal) > 0) {

        return info;

    }

    // Binsearch intersection with plane
    float t0 = 0.0f;
    float t1 = 1000.0f;
    glm::vec3 p = origin;

    const float eps = 1e-3f;

    while (t1 - t0 > eps) {

        float mid = (t0 + t1) / 2.0f;
        p = origin + mid * direction;
        dp = p - torigin;

        if (glm::dot(dp, normal) > 0)
            t0 = mid;
        else t1 = mid;

    }

    float t = (t0 + t1) / 2.0f;
    p = origin + t * direction;

    // Get barycentric coords
    glm::vec2 uv = TriangleGetBarycenticCoords(triangle, p);
    if (uv.x < 0 || uv.y < 0 || uv.x + uv.y > 1)
        return info;

    // Intersection...
    info.hit = true;
    info.t = t;
    info.color = glm::vec3(0.15f, 0.32f, 1.0f);

    return info;

}
