#include "Hq/Math/Math.h"
#include <cassert>
#include <cstring>

namespace hq
{
namespace math
{
    //////////// Vec2 ///////////

    constexpr Vec2::Vec2()
        : x(0.f)
        , y(0.f)
    {
    }

    constexpr Vec2::Vec2(float a)
        : x(a)
        , y(a)
    {
    }

    Vec2::Vec2(const float* data)
    {
        assert(data);
        x = data[0];
        y = data[1];
    }

    constexpr Vec2::Vec2(float x, float y)
        : x(x)
        , y(y)
    {
    }

    float& Vec2::operator[](size_t i)
    {
        assert(i < 2);
        return data[i];
    }

    const float& Vec2::operator[](size_t i) const
    {
        assert(i < 2);
        return data[i];
    }

    const Vec2 Vec2::Zero(0.f);
    const Vec2 Vec2::One(1.f);

    bool isZero(const Vec2& v)
    {
        return v.x == 0.f && v.y == 0.f;
    }

    bool isOne(const Vec2& v)
    {
        return v.x == 1.f && v.y == 1.f;
    }

    Vec2 operator-(const Vec2& v)
    {
        return Vec2(-v.x, -v.y);
    }

    Vec2 add(const Vec2& lhs, const Vec2& rhs)
    {
        return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    void add(const Vec2& lhs, const Vec2& rhs, Vec2& dst)
    {
        dst.x = lhs.x + rhs.x;
        dst.y = lhs.y + rhs.y;
    }

    Vec2 sub(const Vec2& lhs, const Vec2& rhs)
    {
        return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    void sub(const Vec2& lhs, const Vec2& rhs, Vec2& dst)
    {
        dst.x = lhs.x - rhs.x;
        dst.y = lhs.y - rhs.y;
    }

    Vec2 mul(const Vec2& lhs, const Vec2& rhs)
    {
        return Vec2(lhs.x * rhs.x, lhs.y * rhs.y);
    }

    void mul(const Vec2& lhs, const Vec2& rhs, Vec2& dst)
    {
        dst.x = lhs.x * rhs.x;
        dst.y = lhs.y * rhs.y;
    }

    Vec2 div(const Vec2& lhs, const Vec2& rhs)
    {
        return Vec2(lhs.x / rhs.x, lhs.y / rhs.y);
    }

    void div(const Vec2& lhs, const Vec2& rhs, Vec2& dst)
    {
        dst.x = lhs.x / rhs.x;
        dst.y = lhs.y / rhs.y;
    }

    float angle(const Vec2& v1, const Vec2& v2)
    {
        float dz = v1.x * v2.y - v1.y * v2.x;
        return atan2(abs(dz) + kFloatSmall, dot(v1, v2));
    }

    Vec2 clamp(const Vec2& v, const Vec2& min, const Vec2& max)
    {
        return {clamp(v.x, min.x, max.x),  //
                clamp(v.y, min.y, max.y)};
    }

    void clamp(const Vec2& v, const Vec2& min, const Vec2& max, Vec2& dst)
    {
        dst.x = clamp(v.x, min.x, max.x);
        dst.y = clamp(v.y, min.y, max.y);
    }

    void clampSelf(Vec2& v, const Vec2& min, const Vec2& max)
    {
        clamp(v, min, max, v);
    }

    float dot(const Vec2& v1, const Vec2& v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    float length(const Vec2& v)
    {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    float lengthSquared(const Vec2& v)
    {
        return v.x * v.x + v.y * v.y;
    }

    float distance(const Vec2& v1, const Vec2& v2)
    {
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;

        return sqrt(dx * dx + dy * dy);
    }

    float distanceSquared(const Vec2& v1, const Vec2& v2)
    {
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;

        return (dx * dx + dy * dy);
    }

    Vec2 normalize(const Vec2& v)
    {
        const float invLen = 1.0f / length(v);
        const Vec2  result = scale(v, invLen);
        return result;
    }

    void normalize(const Vec2& v, Vec2& dst)
    {
        const float invLen = 1.0f / length(v);
        scale(v, invLen, dst);
    }

    void normalizeSelf(Vec2& v)
    {
        const float invLen = 1.0f / length(v);
        scale(v, invLen, v);
    }

    Vec2 scale(const Vec2& v, float scale)
    {
        return {v.x * scale, v.y * scale};
    }

    void scale(const Vec2& v, float scale, Vec2& dst)
    {
        dst.x = v.x * scale;
        dst.y = v.y * scale;
    }

    void scaleSelf(Vec2& v, float scale)
    {
        v.x = v.x * scale;
        v.y = v.y * scale;
    }

    Vec2 rotate(const Vec2& v, const Vec2& point, float angle)
    {
        Vec2 result;
        rotate(v, point, angle, result);
        return result;
    }

    void rotate(const Vec2& v, const Vec2& point, float angle, Vec2& dst)
    {
        float sinAngle = sin(angle);
        float cosAngle = cos(angle);

        if (isZero(point))
        {
            float tempX = v.x * cosAngle - v.y * sinAngle;
            dst.y       = v.y * cosAngle + v.x * sinAngle;
            dst.x       = tempX;
        }
        else
        {
            float tempX = v.x - point.x;
            float tempY = v.y - point.y;

            dst.x = tempX * cosAngle - tempY * sinAngle + point.x;
            dst.y = tempY * cosAngle + tempX * sinAngle + point.y;
        }
    }

    void rotateSelf(Vec2& v, const Vec2& point, float angle)
    {
        rotate(v, point, angle, v);
    }

    ////////////// Vec3 /////////////

    constexpr Vec3::Vec3()
        : x(0.f)
        , y(0.f)
        , z(0.f)
    {
    }

    constexpr Vec3::Vec3(float a)
        : x(a)
        , y(a)
        , z(a)
    {
    }

    Vec3::Vec3(const float* data)
    {
        assert(data);
        x = data[0];
        y = data[1];
        z = data[2];
    }

    Vec3::Vec3(const Vec2& v, float a)
        : x(v.x)
        , y(v.y)
        , z(a)
    {
    }

    constexpr Vec3::Vec3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    float& Vec3::operator[](size_t i)
    {
        assert(i < 3);
        return data[i];
    }

    const float& Vec3::operator[](size_t i) const
    {
        assert(i < 3);
        return data[i];
    }

    const Vec3 Vec3::Zero(0.f);
    const Vec3 Vec3::One(1.f);

    bool isZero(const Vec3& v)
    {
        return v.x == 0.f && v.y == 0.f && v.z == 0.f;
    }

    bool isOne(const Vec3& v)
    {
        return v.x == 1.f && v.y == 1.f && v.z == 0.f;
    }

    Vec3 operator-(const Vec3& v)
    {
        return {-v.x, -v.y, -v.z};
    }

    Vec3 add(const Vec3& lhs, const Vec3& rhs)
    {
        return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
    }

    void add(const Vec3& lhs, const Vec3& rhs, Vec3& dst)
    {
        dst.x = lhs.x + rhs.x;
        dst.y = lhs.y + rhs.y;
        dst.z = lhs.z + rhs.z;
    }

    Vec3 sub(const Vec3& lhs, const Vec3& rhs)
    {
        return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    }

    void sub(const Vec3& lhs, const Vec3& rhs, Vec3& dst)
    {
        dst.x = lhs.x - rhs.x;
        dst.y = lhs.y - rhs.y;
        dst.z = lhs.z - rhs.z;
    }

    Vec3 mul(const Vec3& lhs, const Vec3& rhs)
    {
        return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
    }

    void mul(const Vec3& lhs, const Vec3& rhs, Vec3& dst)
    {
        dst.x = lhs.x * rhs.x;
        dst.y = lhs.y * rhs.y;
        dst.z = lhs.z * rhs.z;
    }

    Vec3 div(const Vec3& lhs, const Vec3& rhs)
    {
        return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
    }

    void div(const Vec3& lhs, const Vec3& rhs, Vec3& dst)
    {
        dst.x = lhs.x / rhs.x;
        dst.y = lhs.y / rhs.y;
        dst.z = lhs.z / rhs.z;
    }

    float angle(const Vec3& v1, const Vec3& v2)
    {
        float dx = v1.y * v2.z - v1.z * v2.y;
        float dy = v1.z * v2.x - v1.x * v2.z;
        float dz = v1.x * v2.y - v1.y * v2.x;

        return atan2(sqrt(dx * dx + dy * dy + dz * dz) + kFloatSmall, dot(v1, v2));
    }

    Vec3 clamp(const Vec3& v, const Vec3& min, const Vec3& max)
    {
        return {clamp(v.x, min.x, max.x),  //
                clamp(v.y, min.y, max.y),  //
                clamp(v.z, min.z, max.z)};
    }

    void clamp(const Vec3& v, const Vec3& min, const Vec3& max, Vec3& dst)
    {
        dst.x = clamp(v.x, min.x, max.x);
        dst.y = clamp(v.y, min.y, max.y);
        dst.z = clamp(v.z, min.z, max.z);
    }

    void clampSelf(Vec3& v, const Vec3& min, const Vec3& max)
    {
        clamp(v, min, max, v);
    }

    Vec3 cross(const Vec3& v1, const Vec3& v2)
    {
        return {
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x,
        };
    }

    void cross(const Vec3& v1, const Vec3& v2, Vec3& dst)
    {
        dst.x = v1.y * v2.z - v1.z * v2.y;
        dst.y = v1.z * v2.x - v1.x * v2.z;
        dst.z = v1.x * v2.y - v1.y * v2.x;
    }

    float dot(const Vec3& v1, const Vec3& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    float length(const Vec3& v)
    {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    float lengthSquared(const Vec3& v)
    {
        return (v.x * v.x + v.y * v.y + v.z * v.z);
    }

    float distance(const Vec3& v1, const Vec3& v2)
    {
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;
        float dz = v2.z - v1.z;

        return sqrt(dx * dx + dy * dy + dz * dz);
    }

    float distanceSquared(const Vec3& v1, const Vec3& v2)
    {
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;
        float dz = v2.z - v1.z;

        return (dx * dx + dy * dy + dz * dz);
    }

    Vec3 normalize(const Vec3& v)
    {
        const float invLen = 1.0f / length(v);
        const Vec3  result = scale(v, invLen);
        return result;
    }

    void normalize(const Vec3& v, Vec3& dst)
    {
        const float invLen = 1.0f / length(v);
        scale(v, invLen, dst);
    }

    void normalizeSelf(Vec3& v)
    {
        const float invLen = 1.0f / length(v);
        scale(v, invLen, v);
    }

    Vec3 scale(const Vec3& v, float scale)
    {
        return {v.x * scale, v.y * scale, v.z * scale};
    }

    void scale(const Vec3& v, float scale, Vec3& dst)
    {
        dst.x = v.x * scale;
        dst.y = v.y * scale;
        dst.z = v.z * scale;
    }

    void scaleSelf(Vec3& v, float scale)
    {
        v.x = v.x * scale;
        v.y = v.y * scale;
        v.z = v.z * scale;
    }

    ////////////// Vec4 //////////////

    constexpr Vec4::Vec4()
        : x(0.f)
        , y(0.f)
        , z(0.f)
        , w(0.f)
    {
    }

    constexpr Vec4::Vec4(float a)
        : x(a)
        , y(a)
        , z(a)
        , w(a)
    {
    }

    Vec4::Vec4(const float* data)
    {
        assert(data);
        x = data[0];
        y = data[1];
        z = data[2];
        w = data[3];
    }

    Vec4::Vec4(const Vec2& v, float a)
        : x(v.x)
        , y(v.y)
        , z(a)
        , w(a)
    {
    }

    Vec4::Vec4(const Vec2& v, float a, float b)
        : x(v.x)
        , y(v.y)
        , z(a)
        , w(b)
    {
    }

    Vec4::Vec4(const Vec3& v, float a)
        : x(v.x)
        , y(v.y)
        , z(v.z)
        , w(a)
    {
    }

    constexpr Vec4::Vec4(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    float& Vec4::operator[](size_t i)
    {
        assert(i < 4);
        return data[i];
    }

    const float& Vec4::operator[](size_t i) const
    {
        assert(i < 4);
        return data[i];
    }

    const Vec4 Vec4::Zero(0.f);
    const Vec4 Vec4::One(1.f);

    bool isZero(const Vec4& v)
    {
        return v.x == 0.f && v.y == 0.f && v.z == 0.f && v.w == 0.f;
    }

    bool isOne(const Vec4& v)
    {
        return v.x == 1.f && v.y == 1.f && v.z == 1.f && v.w == 1.f;
    }

    Vec4 operator-(const Vec4& v)
    {
        return {-v.x, -v.y, -v.z, -v.w};
    }

    Vec4 add(const Vec4& lhs, const Vec4& rhs)
    {
        return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
    }

    void add(const Vec4& lhs, const Vec4& rhs, Vec4& dst)
    {
        dst.x = lhs.x + rhs.x;
        dst.y = lhs.y + rhs.y;
        dst.z = lhs.z + rhs.z;
        dst.w = lhs.w + rhs.w;
    }

    Vec4 sub(const Vec4& lhs, const Vec4& rhs)
    {
        return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w};
    }

    void sub(const Vec4& lhs, const Vec4& rhs, Vec4& dst)
    {
        dst.x = lhs.x - rhs.x;
        dst.y = lhs.y - rhs.y;
        dst.z = lhs.z - rhs.z;
        dst.w = lhs.w - rhs.w;
    }

    Vec4 mul(const Vec4& lhs, const Vec4& rhs)
    {
        return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w};
    }

    void mul(const Vec4& lhs, const Vec4& rhs, Vec4& dst)
    {
        dst.x = lhs.x * rhs.x;
        dst.y = lhs.y * rhs.y;
        dst.z = lhs.z * rhs.z;
        dst.w = lhs.w * rhs.w;
    }

    Vec4 div(const Vec4& lhs, const Vec4& rhs)
    {
        return {lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w};
    }

    void div(const Vec4& lhs, const Vec4& rhs, Vec4& dst)
    {
        dst.x = lhs.x / rhs.x;
        dst.y = lhs.y / rhs.y;
        dst.z = lhs.z / rhs.z;
        dst.w = lhs.w / rhs.w;
    }

    float angle(const Vec4& v1, const Vec4& v2)
    {
        float dx = v1.w * v2.x - v1.x * v2.w - v1.y * v2.z + v1.z * v2.y;
        float dy = v1.w * v2.y - v1.y * v2.w - v1.z * v2.x + v1.x * v2.z;
        float dz = v1.w * v2.z - v1.z * v2.w - v1.x * v2.y + v1.y * v2.x;

        return atan2(sqrt(dx * dx + dy * dy + dz * dz) + kFloatSmall, dot(v1, v2));
    }

    Vec4 clamp(const Vec4& v, const Vec4& min, const Vec4& max)
    {
        return {clamp(v.x, min.x, max.x),  //
                clamp(v.y, min.y, max.y),  //
                clamp(v.z, min.z, max.z),  //
                clamp(v.w, min.w, max.w)};
    }

    void clamp(const Vec4& v, const Vec4& min, const Vec4& max, Vec4& dst)
    {
        dst.x = clamp(v.x, min.x, max.x);
        dst.y = clamp(v.y, min.y, max.y);
        dst.z = clamp(v.z, min.z, max.z);
        dst.w = clamp(v.w, min.w, max.w);
    }

    void clampSelf(Vec4& v, const Vec4& min, const Vec4& max)
    {
        clamp(v, min, max, v);
    }

    float dot(const Vec4& v1, const Vec4& v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    float length(const Vec4& v)
    {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    float lengthSquared(const Vec4& v)
    {
        return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    float distance(const Vec4& v1, const Vec4& v2)
    {
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;
        float dz = v2.z - v1.z;
        float dw = v2.w - v1.w;

        return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
    }

    float distanceSquared(const Vec4& v1, const Vec4& v2)
    {
        float dx = v2.x - v1.x;
        float dy = v2.y - v1.y;
        float dz = v2.z - v1.z;
        float dw = v2.w - v1.w;

        return (dx * dx + dy * dy + dz * dz + dw * dw);
    }

    Vec4 normalize(const Vec4& v)
    {
        const float invLen = 1.0f / length(v);
        const Vec4  result = scale(v, invLen);
        return result;
    }

    void normalize(const Vec4& v, Vec4& dst)
    {
        const float invLen = 1.0f / length(v);
        scale(v, invLen, dst);
    }

    void normalizeSelf(Vec4& v)
    {
        const float invLen = 1.0f / length(v);
        scale(v, invLen, v);
    }

    Vec4 scale(const Vec4& v, float scale)
    {
        return {v.x * scale,  //
                v.y * scale,  //
                v.z * scale,  //
                v.w * scale};
    }

    void scale(const Vec4& v, float scale, Vec4& dst)
    {
        dst.x = v.x * scale;
        dst.y = v.y * scale;
        dst.z = v.z * scale;
        dst.w = v.w * scale;
    }

    void scaleSelf(Vec4& v, float scale)
    {
        v.x = v.x * scale;
        v.y = v.y * scale;
        v.z = v.z * scale;
        v.w = v.w * scale;
    }

    ////////////////// Rect /////////////////////

    constexpr Rect::Rect()
        : x(0.f)
        , y(0.f)
        , width(0.f)
        , height(0.f)
    {
    }

    constexpr Rect::Rect(float width, float height)
        : x(0.f)
        , y(0.f)
        , width(width)
        , height(height)
    {
    }

    constexpr Rect::Rect(float x, float y, float width, float height)
        : x(x)
        , y(y)
        , width(width)
        , height(height)
    {
    }

    Rect::Rect(const Vec2& topLeft, const Vec2& size)
        : topLeft(topLeft)
        , size(size)
    {
    }

    ///////////////// Plane /////////////////////////////

    constexpr Plane::Plane()
        : normal()
        , distance(0.f)
    {
    }

    Plane::Plane(const Vec3& normal, float distance)
        : normal(normal)
        , distance(distance)
    {
    }

    constexpr Plane::Plane(float normalX, float normalY, float normalZ, float distance)
        : normal(normalX, normalY, normalZ)
        , distance(distance)
    {
    }

    ///////////////// Mat3x3 //////////////////////////
    Mat3x3::Mat3x3()
    {
        memset(data, 0, sizeof(data));
    }

    Mat3x3::Mat3x3(const float* data)
    {
        memcpy(this->data, data, sizeof(this->data));
    }

    Mat3x3::Mat3x3(const Vec3& c1, const Vec3& c2, const Vec3 c3)
    {
        this->c1 = c1;
        this->c2 = c2;
        this->c3 = c3;
    }

    constexpr Mat3x3::Mat3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32,
                             float m33)
        : m11(m11)
        , m12(m12)
        , m13(m13)
        , m21(m21)
        , m22(m22)
        , m23(m23)
        , m31(m31)
        , m32(m32)
        , m33(m33)
    {
    }

    const Mat3x3& Mat3x3::IdentiT()
    {
        static Mat3x3 identiT;
        identiT.data[0] = identiT.data[4] = identiT.data[8] = 1.f;
        return identiT;
    }

    ///////////////////// Mat4x4 //////////////////////

    Mat4x4::Mat4x4()
    {
        memset(data, 0, sizeof(data));
    }

    Mat4x4::Mat4x4(const float* data)
    {
        memcpy(this->data, data, sizeof(this->data));
    }

    Mat4x4::Mat4x4(const Mat3x3& rotation, const Vec3& scale, const Vec3& translation) {}

    Mat4x4::Mat4x4(const Quat& rotation, const Vec3& scale, const Vec3& translation) {}

    Mat4x4::Mat4x4(const Vec4& c1, const Vec4& c2, const Vec4& c3, const Vec4& c4)
    {
        this->c1 = c1;
        this->c2 = c2;
        this->c3 = c3;
        this->c4 = c4;
    }

    const Mat4x4& Mat4x4::IdentiT()
    {
        static Mat4x4 identiT;
        identiT.data[0] = identiT.data[5] = identiT.data[10] = identiT.data[15] = 1.f;
        return identiT;
    }

    ///////////////// Quat /////////////////////////////

    constexpr Quat::Quat()
        : x(0.f)
        , y(0.f)
        , z(0.f)
        , w(0.f)
    {
    }

    constexpr Quat::Quat(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    Quat::Quat(const Vec3& axis, float angle) {}

    Quat::Quat(const Mat3x3& rotation) {}

    Quat::Quat(const Mat4x4& m) {}

    /////////////////////////// Ray2 ///////////////////////////////

    Ray2::Ray2(const Vec2& origin, const Vec2& direction)
        : origin(origin)
        , direction(direction)
    {
    }

    ////////////////////////// Ray3 ////////////////////////////////

    Ray3::Ray3(const Vec3& origin, const Vec3& direction)
        : origin(origin)
        , direction(direction)
    {
    }

    //////////////////////////// Box2 /////////////////////////////

    Box2::Box2(const Vec2& min, const Vec2& max)
        : min(min)
        , max(max)
    {
    }

    Vec2 Box2::center() const
    {
        Vec2 result;
        add(min, max, result);
        scale(result, 0.5f, result);
        return result;
    }

    Vec2 Box2::extent() const
    {
        Vec2 result;
        sub(max, min, result);
        scale(result, 0.5f, result);
        return result;
    }

    ////////////////////////// Box3 ///////////////////////////////

    Box3::Box3(const Vec3& min, const Vec3& max)
        : min(min)
        , max(max)
    {
    }

    Vec3 Box3::center() const
    {
        Vec3 result;
        add(min, max, result);
        scale(result, 0.5f, result);
        return result;
    }

    Vec3 Box3::extent() const
    {
        Vec3 result;
        sub(max, min, result);
        scale(result, 0.5f, result);
        return result;
    }

    ///////////////////////// Circle ///////////////////////////////

    constexpr Circle::Circle()
        : center(0.f)
        , radius(0.f)
    {
    }

    Circle::Circle(const Vec2& center, float radius)
        : center(center)
        , radius(radius)
    {
    }

    constexpr Circle::Circle(float xcenter, float ycenter, float radius)
        : center(xcenter, ycenter)
        , radius(radius)
    {
    }

    ///////////////////////// Sphere ////////////////////////////////

    constexpr Sphere::Sphere()
        : center(0.f)
        , radius(0.f)
    {
    }

    Sphere::Sphere(const Vec3& center, float radius)
        : center(center)
        , radius(radius)
    {
    }

    constexpr Sphere::Sphere(float xcenter, float ycenter, float zcenter, float radius)
        : center(xcenter, ycenter, zcenter)
        , radius(radius)
    {
    }

}
}
