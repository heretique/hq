#include "MathTypes.h"

namespace hq
{
namespace math
{
    //////////////////////// Triangle //////////////////////////

    Vec3 barycenter(const Vec3& a, const Vec3& b, const Vec3& c);
    void barycenter(const Vec3& a, const Vec3& b, const Vec3& c, Vec3& dst);
    Vec3 barycenter(const Triangle& t);
    void barycenter(const Triangle& t, Vec3& dst);
    Vec3 barycentricCoord(const Vec3& p, const Vec3& a, const Vec3& b, const Vec3& c);
    void barycentricCoord(const Vec3& p, const Vec3& a, const Vec3& b, const Vec3& c, Vec3& dst);
    Vec3 barycentricCoord(const Vec3& p, const Triangle& t);
    void barycentricCoord(const Vec3& p, const Triangle& t, Vec3& dst);
}
}
