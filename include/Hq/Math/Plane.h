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
    bool  intersects(const Ray3& ray, const Plane& plane);
    bool  intersects(const Plane& p1, const Plane& p2);
    bool  intersects(const Box3& b, const Plane& p);
    bool  intersects(const Sphere& s, const Plane& p);
    bool  intersects(const Frustum& f, const Plane& p);
    bool  intersection(const Plane& p1, const Plane& p2, const Plane& p3, Vec3& dst);
    bool  intersection(const Plane& p1, const Plane& p2, Ray3& dst);
    // out distance from sphere center
    bool intersection(const Sphere& s, const Plane& p, float& distance);
    bool intersection(const Box3& b, const Plane& p, uint8_t& count, Vec3* dst);
    bool intersection(const Frustum& f, const Plane& p, uint8_t& count, Vec3* dst);

    Vec3  projectPoint(const Vec3& point, const Plane& plane);
    void  projectPoint(const Vec3& point, const Plane& plane, Vec3& dst);
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
