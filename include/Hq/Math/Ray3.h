#include "MathTypes.h"

namespace hq
{
namespace math
{
    //////////////////////////// Ray3 ///////////////////////////////////////////////

    Vec3  pointOnRay(const Ray3& r, float distance);
    void  pointOnRay(const Ray3& r, float distance, Vec3& dst);
    float distance(const Vec3& point, const Ray3& r);
    bool  intersects(const Plane& p, const Ray3& r);
    bool  intersects(const Box3& b, const Ray3& r);
    bool  intersects(const Sphere& s, const Ray3& r);
    bool  intersects(const Frustum& f, const Ray3& r);
}
}
