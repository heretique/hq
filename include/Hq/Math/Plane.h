#include "MathTypes.h"

namespace hq
{
namespace math
{
    ///////////////////////// Plane //////////////////////////////

    float distance(const Vec3& point, const Plane& plane);
    Plane normalize(const Plane& p);
    void  normalize(const Plane& p, Plane& dst);
    void  normalize(Plane& p);
    bool  intersects(const Plane& p, const Ray3& r);
    bool  intersects(const Plane& p1, const Plane& p2);
    bool  intersects(const Plane& p, const Box3& b);
    bool  intersects(const Plane& p, const Sphere& s);
    bool  intersects(const Plane& p, const Frustum& f);

    bool  intersection(const Plane& p1, const Plane& p2, const Plane& p3, Vec3& dst);
    bool  intersection(const Plane& p1, const Plane& p2, Ray3& dst);
    // out distance from sphere center
    bool intersection(const Plane& p, const Sphere& s, float& distance);
    bool intersection(const Plane& p, const Box3& b, uint8_t& count, Vec3* dst);
    bool intersection(const Plane& p, const Frustum& f, uint8_t& count, Vec3* dst);

    Vec3  projectPoint(const Plane& plane, const Vec3& point);
    void  projectPoint(const Plane& plane, const Vec3& point, Vec3& dst);
    Plane transform(const Plane& plane, const Mat4x4& tr);
    void  transform(const Plane& plane, const Mat4x4& tr, Plane& dst);
    void  transform(Plane& plane, const Mat4x4& tr);

    /// Returns 1 if the point is on the front side of the plane (same side as the normal),
    /// -1 if on the back side or 0 if point is in plane
    int side(const Vec3& point, const Plane& plane);
    /// Returns 1 if the box is on the front side of the plane (same side as the normal),
    /// -1 if on the back side, or 0 if box center is in plane
    int side(const Box3& b, const Plane& p);
    /// Returns 1 if the sphere is on the front side of the plane (same side as the normal),
    /// -1 if on the back side or 0 if sphere center is in plane
    int side(const Sphere& s, const Plane& p);
}
}
