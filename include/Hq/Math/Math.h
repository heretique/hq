#pragma once

#include "Hq/Math/MathTypes.h"

namespace hq
{
namespace math
{
    ///////////////////////// Vec2 /////////////////////////

    Vec2 operator-(const Vec2& v);
    Vec2 operator!(const Vec2& v);
    Vec2 add(const Vec2& lhs, const Vec2& rhs);
    void add(const Vec2& lhs, const Vec2& rhs, Vec2& dst);
    Vec2 sub(const Vec2& lhs, const Vec2& rhs);
    void sub(const Vec2& lhs, const Vec2& rhs, Vec2& dst);
    Vec2 mul(const Vec2& lhs, const Vec2& rhs);
    void mul(const Vec2& lhs, const Vec2& rhs, Vec2& dst);
    Vec2 div(const Vec2& lhs, const Vec2& rhs);
    void div(const Vec2& lhs, const Vec2& rhs, Vec2& dst);

    float angle(const Vec2& v1, const Vec2& v2);
    Vec2  clamp(const Vec2& v, const Vec2& min, const Vec2& max);
    Vec2  clamp(const Vec2& v, const Vec2& min, const Vec2& max, Vec2& dst);
    void  clampSelf(Vec2& v, const Vec2& min, const Vec2& max);
    float dot(const Vec2& v1, const Vec2& v2);
    float length(const Vec2& v);
    float lengthSquared(const Vec2& v);
    float distance(const Vec2& v1, const Vec2& v2);
    float distanceSquared(const Vec2& v1, const Vec2& v2);
    Vec2  normalize(const Vec2& v);
    void  normalize(const Vec2& v, Vec2& dst);
    void  normalizeSelf(Vec2& v);
    Vec2  scale(const Vec2& v, float scale);
    void  scale(const Vec2& v, float scale, Vec2& dst);
    void  scaleSelf(Vec2& v, float scale);
    Vec2  rotate(const Vec2& v, float angle);
    void  rotate(const Vec2& v, float angle, Vec2& dst);
    void  rotateSelf(Vec2& v, float angle);

    //////////////////////// Vec3 //////////////////////////

    Vec3 operator-(const Vec3& v);
    Vec3 operator!(const Vec3& v);
    Vec3 add(const Vec3& lhs, const Vec3& rhs);
    void add(const Vec3& lhs, const Vec3& rhs, Vec3& dst);
    Vec3 sub(const Vec3& lhs, const Vec3& rhs);
    void sub(const Vec3& lhs, const Vec3& rhs, Vec3& dst);
    Vec3 mul(const Vec3& lhs, const Vec3& rhs);
    void mul(const Vec3& lhs, const Vec3& rhs, Vec3& dst);
    Vec3 div(const Vec3& lhs, const Vec3& rhs);
    void div(const Vec3& lhs, const Vec3& rhs, Vec3& dst);

    float angle(const Vec3& v1, const Vec3& v2);
    Vec3  clamp(const Vec3& v, const Vec3& min, const Vec3& max);
    Vec3  clamp(const Vec3& v, const Vec3& min, const Vec3& max, Vec3& dst);
    void  clampSelf(Vec3& v, const Vec3& min, const Vec3& max);
    Vec3  cross(const Vec3& v1, const Vec3& v2);
    Vec3  cross(const Vec3& v1, const Vec3& v2, Vec3& dst);
    float dot(const Vec3& v1, const Vec3& v2);
    float length(const Vec3& v);
    float lengthSquared(const Vec3& v);
    float distance(const Vec3& v1, const Vec3& v2);
    float distanceSquared(const Vec3& v1, const Vec3& v2);
    Vec3  normalize(const Vec3& v);
    void  normalize(const Vec3& v, Vec3& dst);
    void  normalizeSelf(Vec3& v);
    Vec3  scale(const Vec3& v, float scale);
    void  scale(const Vec3& v, float scale, Vec3& dst);
    void  scaleSelf(Vec3& v, float scale);
    Vec3  rotate(const Vec3& v, float angle);
    void  rotate(const Vec3& v, float angle, Vec3& dst);
    void  rotateSelf(Vec3& v, float angle);

    //////////////////////// Vec4 //////////////////////////

    Vec4 operator-(const Vec4& v);
    Vec4 operator!(const Vec4& v);
    Vec4 add(const Vec4& lhs, const Vec4& rhs);
    void add(const Vec4& lhs, const Vec4& rhs, Vec4& dst);
    Vec4 sub(const Vec4& lhs, const Vec4& rhs);
    void sub(const Vec4& lhs, const Vec4& rhs, Vec4& dst);
    Vec4 mul(const Vec4& lhs, const Vec4& rhs);
    void mul(const Vec4& lhs, const Vec4& rhs, Vec4& dst);
    Vec4 div(const Vec4& lhs, const Vec4& rhs);
    void div(const Vec4& lhs, const Vec4& rhs, Vec4& dst);

    float angle(const Vec4& v1, const Vec4& v2);
    Vec4  clamp(const Vec4& v, const Vec4& min, const Vec4& max);
    Vec4  clamp(const Vec4& v, const Vec4& min, const Vec4& max, Vec4& dst);
    void  clampSelf(Vec4& v, const Vec4& min, const Vec4& max);
    float dot(const Vec4& v1, const Vec4& v2);
    float length(const Vec4& v);
    float lengthSquared(const Vec4& v);
    float distance(const Vec4& v1, const Vec4& v2);
    float distanceSquared(const Vec4& v1, const Vec4& v2);
    Vec4  normalize(const Vec4& v);
    void  normalize(const Vec4& v, Vec4& dst);
    void  normalizeSelf(Vec4& v);
    Vec4  scale(const Vec4& v, float scale);
    void  scale(const Vec4& v, float scale, Vec4& dst);
    void  scaleSelf(Vec4& v, float scale);
}
}
