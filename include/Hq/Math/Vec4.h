#include "MathTypes.h"

namespace hq
{
namespace math
{
    //////////////////////// Vec4 //////////////////////////

    bool isZero(const Vec4& v);
    bool isOne(const Vec4& v);
    Vec4 operator-(const Vec4& v);
    Vec4 operator +(const Vec4& lhs, const Vec4& rhs);
    void add(const Vec4& lhs, const Vec4& rhs, Vec4& dst);
    Vec4 operator -(const Vec4& lhs, const Vec4& rhs);
    void sub(const Vec4& lhs, const Vec4& rhs, Vec4& dst);
    Vec4 operator *(const Vec4& lhs, const Vec4& rhs);
    void mul(const Vec4& lhs, const Vec4& rhs, Vec4& dst);
    Vec4 operator /(const Vec4& lhs, const Vec4& rhs);
    void div(const Vec4& lhs, const Vec4& rhs, Vec4& dst);

    float angle(const Vec4& v1, const Vec4& v2);
    Vec4  clamp(const Vec4& v, const Vec4& min, const Vec4& max);
    void  clamp(const Vec4& v, const Vec4& min, const Vec4& max, Vec4& dst);
    void  clamp(Vec4& v, const Vec4& min, const Vec4& max);
    float dot(const Vec4& v1, const Vec4& v2);
    float length(const Vec4& v);
    float lengthSquared(const Vec4& v);
    float distance(const Vec4& v1, const Vec4& v2);
    float distanceSquared(const Vec4& v1, const Vec4& v2);
    Vec4  normalize(const Vec4& v);
    void  normalize(const Vec4& v, Vec4& dst);
    void  normalize(Vec4& v);
    Vec4  scale(const Vec4& v, float scale);
    void  scale(const Vec4& v, float scale, Vec4& dst);
    void  scale(Vec4& v, float scale);

    float maxComponent(const Vec4& v);
    float minComponent(const Vec4& v);
    float meanComponent(const Vec4& v);
}
}
