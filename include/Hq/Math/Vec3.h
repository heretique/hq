#include "MathTypes.h"

namespace hq
{
namespace math
{
    //////////////////////// Vec3 //////////////////////////

    bool isZero(const Vec3& v);
    bool isOne(const Vec3& v);
    Vec3 operator-(const Vec3& v);
    Vec3 add(const Vec3& lhs, const Vec3& rhs);
    void add(const Vec3& lhs, const Vec3& rhs, Vec3& dst);
    Vec3 sub(const Vec3& lhs, const Vec3& rhs);
    void sub(const Vec3& lhs, const Vec3& rhs, Vec3& dst);
    Vec3 mul(const Vec3& lhs, const Vec3& rhs);
    void mul(const Vec3& lhs, const Vec3& rhs, Vec3& dst);
    Vec3 mul(float f, const Vec3& v);
    Vec3 mul(const Vec3& v, float f);
    void mul(float f, const Vec3& v, Vec3& dst);
    void mul(const Vec3& v, float f, Vec3& dst);
    Vec3 div(const Vec3& lhs, const Vec3& rhs);
    void div(const Vec3& lhs, const Vec3& rhs, Vec3& dst);

    float angle(const Vec3& v1, const Vec3& v2);
    Vec3  clamp(const Vec3& v, const Vec3& min, const Vec3& max);
    void  clamp(const Vec3& v, const Vec3& min, const Vec3& max, Vec3& dst);
    void  clamp(Vec3& v, const Vec3& min, const Vec3& max);
    Vec3  cross(const Vec3& v1, const Vec3& v2);
    void  cross(const Vec3& v1, const Vec3& v2, Vec3& dst);
    float dot(const Vec3& v1, const Vec3& v2);
    float length(const Vec3& v);
    float lengthSquared(const Vec3& v);
    float distance(const Vec3& v1, const Vec3& v2);
    float distanceSquared(const Vec3& v1, const Vec3& v2);
    Vec3  normalize(const Vec3& v);
    void  normalize(const Vec3& v, Vec3& dst);
    void  normalize(Vec3& v);
    Vec3  scale(const Vec3& v, float scale);
    void  scale(const Vec3& v, float scale, Vec3& dst);
    void  scale(Vec3& v, float scale);
}
}
