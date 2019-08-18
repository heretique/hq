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

    const Vec2& Vec2::Zero()
    {
        static Vec2 zero;
        return zero;
    }

    const Vec2& Vec2::One()
    {
        static Vec2 one(1.f);
        return one;
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

    const Vec3& Vec3::Zero()
    {
        static Vec3 zero;
        return zero;
    }

    const Vec3& Vec3::One()
    {
        static Vec3 one(1.f);
        return one;
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

    const Vec4& Vec4::Zero()
    {
        static Vec4 zero;
        return zero;
    }

    const Vec4& Vec4::One()
    {
        static Vec4 one(1.f);
        return one;
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

    const Mat3x3& Mat3x3::Identity()
    {
        static Mat3x3 identity;
        identity.data[0] = identity.data[4] = identity.data[8] = 1.f;
        return identity;
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

    const Mat4x4& Mat4x4::Identity()
    {
        static Mat4x4 identity;
        identity.data[0] = identity.data[5] = identity.data[10] = identity.data[15] = 1.f;
        return identity;
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
