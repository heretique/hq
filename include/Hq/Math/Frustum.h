#include "MathTypes.h"

namespace hq
{
namespace math
{
    ///////////////////// Frustum ////////////////////////////////////////

    void getCorners(const Frustum& f, Vec3* dst);
    void getNearCorners(const Frustum& f, Vec3* dst);
    void getFarCorners(const Frustum& f, Vec3* dst);
    bool intersects(const Frustum& f, const Vec3& point);
    bool intersects(const Frustum& f, const Sphere& s);
    bool intersects(const Frustum& f, const Box3& b);
    bool intersects(const Frustum& f, const Plane& p);
    bool intersects(const Frustum& f, const Ray3& r);
}
}
