#include "MathTypes.h"

namespace hq
{
namespace math
{
    ///////////////////// Frustum ////////////////////////////////////////

    void getCorners(const Frustum& f, Vec3* dst);
    void getNearCorners(const Frustum& f, Vec3* dst);
    void getFarCorners(const Frustum& f, Vec3* dst);
    bool intersects(const Vec3& point, const Frustum& f);
    bool intersects(const Sphere& s, const Frustum& f);
    bool intersects(const Box3& b, const Frustum& f);
    bool intersects(const Plane& p, const Frustum& f);
    bool intersects(const Ray3& r, const Frustum& f);
}
}
