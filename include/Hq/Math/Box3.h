#include "MathTypes.h"

namespace hq
{
namespace math
{
    //////////////////////////// Box3 ///////////////////////////////////////////////

    void getCorners(const Box3& b, Vec3* dst);
    bool intersects(const Box3& b1, const Box3& b2);
    bool intersects(const Box3& b, const Sphere& s);
    bool intersects(const Box3& b, const Frustum& f);
    bool intersects(const Box3& b, const Ray3& r);

    bool intersection(const Box3& b, const Ray3& r, float& distance);

    void merge(const Box3& b, const Vec3& point, Box3& dst);
    void merge(Box3& b, const Vec3& point);
    void merge(const Box3& b, const Sphere& s, Box3& dst);
    void merge(Box3& b, const Sphere& s);
    void merge(const Box3& b, const Box3& box, Box3& dst);
    void merge(Box3& b, const Box3& box);
    void transform(const Box3& b, const Mat4x4& m, Box3& dst);
    void transform(Box3& b, const Mat4x4& m);
}
}
