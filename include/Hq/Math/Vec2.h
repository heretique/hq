#include "MathTypes.h"

namespace hq
{
namespace math
{
    ///////////////////////// Vec2 /////////////////////////

    bool isZero(const Vec2& v);
    bool isOne(const Vec2& v);
    Vec2 operator-(const Vec2& v);
    Vec2 operator +(const Vec2& lhs, const Vec2& rhs);
    void add(const Vec2& lhs, const Vec2& rhs, Vec2& dst);
    Vec2 operator -(const Vec2& lhs, const Vec2& rhs);
    void sub(const Vec2& lhs, const Vec2& rhs, Vec2& dst);
    Vec2 operator *(const Vec2& lhs, const Vec2& rhs);
    void mul(const Vec2& lhs, const Vec2& rhs, Vec2& dst);
    Vec2 operator *(float f, const Vec2& v);
    Vec2 operator *(const Vec2& v, float f);
    void mul(float f, const Vec2& v, Vec2& dst);
    void mul(const Vec2& v, float f, Vec2& dst);
    Vec2 operator /(const Vec2& lhs, const Vec2& rhs);
    void div(const Vec2& lhs, const Vec2& rhs, Vec2& dst);

    float angle(const Vec2& v1, const Vec2& v2);
    Vec2  clamp(const Vec2& v, const Vec2& min, const Vec2& max);
    void  clamp(const Vec2& v, const Vec2& min, const Vec2& max, Vec2& dst);
    void  clamp(Vec2& v, const Vec2& min, const Vec2& max);
    float dot(const Vec2& v1, const Vec2& v2);
    float length(const Vec2& v);
    float lengthSquared(const Vec2& v);
    float distance(const Vec2& v1, const Vec2& v2);
    float distanceSquared(const Vec2& v1, const Vec2& v2);
    Vec2  normalize(const Vec2& v);
    void  normalize(const Vec2& v, Vec2& dst);
    void  normalize(Vec2& v);
    Vec2  scale(const Vec2& v, float scale);
    void  scale(const Vec2& v, float scale, Vec2& dst);
    void  scale(Vec2& v, float scale);
    Vec2  rotate(const Vec2& v, const Vec2& point, float angle);
    void  rotate(const Vec2& v, const Vec2& point, float angle, Vec2& dst);
    void  rotate(Vec2& v, const Vec2& point, float angle);

    Vec2 minVec(const Vec2& v1, const Vec2& v2);
    Vec2 maxVec(const Vec2& v1, const Vec2& v2);

    float maxComponent(const Vec2& v);
    float minComponent(const Vec2& v);
    float meanComponent(const Vec2& v);
}
}
