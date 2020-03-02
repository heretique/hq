#include "MathTypes.h"

namespace hq
{
namespace math
{
    /////////////////////////// Sphere ////////////////////////////////////////////

    bool intersects(const Sphere& s1, const Sphere& s2);
    bool intersects(const Sphere& s, const Box3& b);
    bool intersects(const Sphere& s, const Frustum& f);
    bool intersects(const Sphere& s, const Plane& p);
    bool intersects(const Sphere& s, const Ray3& r);
}
}
