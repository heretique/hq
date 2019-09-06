#include "MathTypes.h"

namespace hq
{
namespace math
{
    /////////////////////////// Sphere ////////////////////////////////////////////

    bool intersects(const Sphere& s1, const Sphere& s2);
    bool intersects(const Box3& b, const Sphere& s);
    bool intersects(const Frustum& f, const Sphere& s);
    bool intersects(const Plane& p, const Sphere& s);
    bool intersects(const Ray3& r, const Sphere& s);
}
}
