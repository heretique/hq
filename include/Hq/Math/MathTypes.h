#pragma once

namespace hq
{
namespace math
{
    struct Vec2
    {
        union {
            float data[2];
            struct
            {
                float x, y;
            };
            struct
            {
                float u, v;
            };
        };

        constexpr          Vec2();
        explicit constexpr Vec2(float a);
        explicit Vec2(const float* data);
        constexpr Vec2(float x, float y);

        float&       operator[](size_t i);
        const float& operator[](size_t i) const;

        static const Vec2 Zero;
        static const Vec2 One;

    private:
        operator bool();
    };

    struct Vec3
    {
        union {
            float data[3];
            struct
            {
                float x, y, z;
            };
            struct
            {
                float r, g, b;
            };
            Vec2 xy;
        };

        constexpr          Vec3();
        explicit constexpr Vec3(float a);
        explicit Vec3(const float* data);
        Vec3(const Vec2& v, float a);
        constexpr Vec3(float x, float y, float z);

        float&       operator[](size_t i);
        const float& operator[](size_t i) const;

        static const Vec3 Zero;
        static const Vec3 One;

    private:
        operator bool();
    };

    struct Vec4
    {
        union {
            float data[4];
            struct
            {
                float x, y, z, w;
            };
            struct
            {
                float r, g, b, a;
            };
            Vec2 xy;
            Vec3 xyz;
            Vec3 rgb;
        };

        constexpr Vec4();
        constexpr explicit Vec4(float a);
        explicit Vec4(const float* data);
        Vec4(const Vec2& v, float a);
        Vec4(const Vec2& v, float a, float b);
        Vec4(const Vec3& v, float a);
        constexpr Vec4(float x, float y, float z, float w);

        float&       operator[](size_t i);
        const float& operator[](size_t i) const;

        static const Vec4 Zero;
        static const Vec4 One;

    private:
        operator bool();
    };

    struct Rect
    {
        union {
            struct
            {
                float x, y, width, height;
            };
            struct
            {
                Vec2 topLeft, size;
            };
        };
        constexpr Rect();
        constexpr Rect(float width, float height);
        constexpr Rect(float x, float y, float width, float height);
        Rect(const Vec2& topLeft, const Vec2& size);
    };

    struct Plane
    {
        Vec3  normal;    // The normal vector of the Plane.
        float distance;  // The distance of the Plane along its normal from the origin.

        constexpr Plane();
        Plane(const Vec3& normal, float distance);
        constexpr Plane(float normalX, float normalY, float normalZ, float distance);
    };

    // column-major
    struct Mat3x3
    {
        union {
            float data[9];
            struct
            {
                float m11, m12, m13, m21, m22, m23, m31, m32, m33;
            };
            struct
            {
                Vec3 c1, c2, c3;
            };
        };
        Mat3x3();
        Mat3x3(const float* data);
        Mat3x3(const Vec3& c1, const Vec3& c2, const Vec3 c3);
        constexpr Mat3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32,
                         float m33);

        static const Mat3x3& IdentiT();
    };

    // forward define
    struct Quat;

    // column-major
    struct Mat4x4
    {
        union {
            float data[16];
            struct
            {
                float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
            };
            struct
            {
                Vec4 c1, c2, c3, c4;
            };
        };
        Mat4x4();
        Mat4x4(const float* data);
        Mat4x4(const Mat3x3& rotation, const Vec3& scale, const Vec3& translation);
        Mat4x4(const Quat& rotation, const Vec3& scale, const Vec3& translation);
        Mat4x4(const Vec4& c1, const Vec4& c2, const Vec4& c3, const Vec4& c4);

        static const Mat4x4& IdentiT();
    };

    struct Frustum
    {
        Plane  near;
        Plane  far;
        Plane  bottom;
        Plane  top;
        Plane  left;
        Plane  right;
        Mat4x4 matrix;
    };

    struct Quat
    {
        union {
            float data[4];
            struct
            {
                float x, y, z, w;
            };
        };

        constexpr Quat();
        constexpr Quat(float x, float y, float z, float w);
        Quat(const Vec3& axis, float angle);
        Quat(const Mat3x3& rotation);
        // Constructs a quaternion equal to the rotational part of the specified matrix.
        Quat(const Mat4x4& m);

        float&       operator[](size_t i);
        const float& operator[](size_t i) const;

    private:
        operator bool();
    };

    struct Ray2
    {
        Vec2 origin;
        Vec2 direction;

        constexpr Ray2() {}
        Ray2(const Vec2& origin, const Vec2& direction);
    };

    struct Ray3
    {
        Vec3 origin;
        Vec3 direction;

        constexpr Ray3() {}
        Ray3(const Vec3& origin, const Vec3& direction);
    };

    struct Box2
    {
        Vec2      min;
        Vec2      max;
        constexpr Box2() {}
        Box2(const Vec2& min, const Vec2& max);
        Vec2 center() const;
        Vec2 extent() const;
    };

    struct Box3
    {
        Vec3      min;
        Vec3      max;
        constexpr Box3() {}
        Box3(const Vec3& min, const Vec3& max);
        Vec3 center() const;
        Vec3 extent() const;
    };

    struct Circle
    {
        Vec2      center;
        float     radius;
        constexpr Circle();
        Circle(const Vec2& center, float radius);
        constexpr Circle(float xcenter, float ycenter, float radius);
    };

    struct Sphere
    {
        Vec3      center;
        float     radius;
        constexpr Sphere();
        Sphere(const Vec3& center, float radius);
        constexpr Sphere(float xcenter, float ycenter, float zcenter, float radius);
    };

}
}
