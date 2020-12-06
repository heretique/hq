#include "MathTypes.h"

namespace hq
{
namespace math
{
    ///////////////////////// Vec2 /////////////////////////

    bool isZero(const Vec2& v);
    bool isOne(const Vec2& v);
    Vec2 operator-(const Vec2& v);
    Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
    void add(const Vec2& lhs, const Vec2& rhs, Vec2& dst);
    Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
    void sub(const Vec2& lhs, const Vec2& rhs, Vec2& dst);
    Vec2 operator*(const Vec2& lhs, const Vec2& rhs);
    void mul(const Vec2& lhs, const Vec2& rhs, Vec2& dst);
    Vec2 operator*(float f, const Vec2& v);
    Vec2 operator*(const Vec2& v, float f);
    void mul(float f, const Vec2& v, Vec2& dst);
    void mul(const Vec2& v, float f, Vec2& dst);
    Vec2 operator/(const Vec2& lhs, const Vec2& rhs);
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

    // int variant
    bool  isZero(const Vec2i& v);
    bool  isOne(const Vec2i& v);
    Vec2i operator-(const Vec2i& v);
    Vec2i operator+(const Vec2i& lhs, const Vec2i& rhs);
    void  add(const Vec2i& lhs, const Vec2i& rhs, Vec2i& dst);
    Vec2i operator-(const Vec2i& lhs, const Vec2i& rhs);
    void  sub(const Vec2i& lhs, const Vec2i& rhs, Vec2i& dst);
    Vec2i operator*(const Vec2i& lhs, const Vec2i& rhs);
    void  mul(const Vec2i& lhs, const Vec2i& rhs, Vec2i& dst);
    Vec2i operator*(int f, const Vec2i& v);
    Vec2i operator*(const Vec2i& v, int f);
    void  mul(int f, const Vec2i& v, Vec2i& dst);
    void  mul(const Vec2i& v, int f, Vec2i& dst);
    Vec2i operator/(const Vec2i& lhs, const Vec2i& rhs);
    Vec2i operator/(const Vec2i& lhs, int v);
    void  div(const Vec2i& lhs, const Vec2i& rhs, Vec2i& dst);

    Vec2i clamp(const Vec2i& v, const Vec2i& min, const Vec2i& max);
    void  clamp(const Vec2i& v, const Vec2i& min, const Vec2i& max, Vec2i& dst);
    void  clamp(Vec2i& v, const Vec2i& min, const Vec2i& max);

    Vec2i minVec(const Vec2i& v1, const Vec2i& v2);
    Vec2i maxVec(const Vec2i& v1, const Vec2i& v2);

    int maxComponent(const Vec2i& v);
    int minComponent(const Vec2i& v);
    int meanComponent(const Vec2i& v);
}
}
