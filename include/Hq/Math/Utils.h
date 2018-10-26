#pragma once

#include "AABB.h"
#include "Vector.h"

namespace hq
{
namespace math
{
#undef M_PI
#define M_PI (3.14159265358979f)

    Vector3f RandomInUnitSphere();
    Vector3f RandomInUnitDisk();
    Vector3f reflect(const math::Vector3f& v, const math::Vector3f& n);
    bool     refract(const math::Vector3f& v, const math::Vector3f& n, float niOverNt, math::Vector3f& refracted);
    AABBf    sphereBbox(const math::Vector3f& center, const float radius);
    AABBf    surroundingBbox(const math::AABBf& bbox1, const math::AABBf& bbox2);

}  // namespace math

}  // namespace hq
