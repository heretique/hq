#include "MathTypes.h"

namespace hq
{
namespace math
{
    //////////////////////////// Ray3 ///////////////////////////////////////////////

    Vec3  pointOnRay(const Ray3& r, float distance);
    void  pointOnRay(const Ray3& r, float distance, Vec3& dst);
    float distance(const Vec3& point, const Ray3& r);

    bool  intersects(const Ray3& r, const Plane& p);
    bool  intersects(const Ray3& r, const Box3& b);
    bool  intersects(const Ray3& r, const Sphere& s);
    bool  intersects(const Ray3& r, const Frustum& f);

    bool intersection(const Ray3& r, const Box3& b, float& distance);
}
}
