#include "Hq/Math/Math.h"
#include "Hq/Math/Box2.h"
#include "Hq/Math/Box3.h"
#include "Hq/Math/Plane.h"
#include "Hq/Math/Quat.h"
#include "Hq/Math/Line3.h"
#include "Hq/Math/Line2.h"
#include "Hq/Math/Mat4x4.h"
#include "Hq/Math/Mat3x3.h"
#include "Hq/Math/Frustum.h"
#include "Hq/Math/Circle.h"
#include "Hq/Math/Rect.h"
#include "Hq/Math/Box3.h"
#include "Hq/Math/Box2.h"
#include "Hq/Math/Sphere.h"
#include "Hq/Math/Ray3.h"
#include "Hq/Math/Ray2.h"
#include "Hq/Math/Vec4.h"
#include "Hq/Math/Vec3.h"
#include "Hq/Math/Vec2.h"
#include "Hq/Math/Triangle.h"
#include "Hq/NotImplemented.h"
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdlib>

namespace hq
{
namespace math
{
    ////////////////////// Base functions ////////////////////////////////

    const float kInfinity = bitsToFloat(UINT32_C(0x7f800000));

    namespace
    {
        constexpr float kSinC2  = -0.16666667163372039794921875f;
        constexpr float kSinC4  = 8.333347737789154052734375e-3f;
        constexpr float kSinC6  = -1.9842604524455964565277099609375e-4f;
        constexpr float kSinC8  = 2.760012648650445044040679931640625e-6f;
        constexpr float kSinC10 = -2.50293279435709337121807038784027099609375e-8f;

        constexpr float kCosC2  = -0.5f;
        constexpr float kCosC4  = 4.166664183139801025390625e-2f;
        constexpr float kCosC6  = -1.388833043165504932403564453125e-3f;
        constexpr float kCosC8  = 2.47562347794882953166961669921875e-5f;
        constexpr float kCosC10 = -2.59630184018533327616751194000244140625e-7f;

    }  // namespace

    float cos(float _a)
    {
        const float   scaled = _a * 2.0f * kInvPi;
        const float   real   = floor(scaled);
        const float   xx     = _a - real * kPiHalf;
        const int32_t bits   = int32_t(real) & 3;

        float c0, c2, c4, c6, c8, c10;

        if (bits == 0 || bits == 2)
        {
            c0  = 1.0f;
            c2  = kCosC2;
            c4  = kCosC4;
            c6  = kCosC6;
            c8  = kCosC8;
            c10 = kCosC10;
        }
        else
        {
            c0  = xx;
            c2  = kSinC2;
            c4  = kSinC4;
            c6  = kSinC6;
            c8  = kSinC8;
            c10 = kSinC10;
        }

        const float xsq    = square(xx);
        const float tmp0   = mad(c10, xsq, c8);
        const float tmp1   = mad(tmp0, xsq, c6);
        const float tmp2   = mad(tmp1, xsq, c4);
        const float tmp3   = mad(tmp2, xsq, c2);
        const float tmp4   = mad(tmp3, xsq, 1.0);
        const float result = tmp4 * c0;

        return bits == 1 || bits == 2 ? -result : result;
    }

    namespace
    {
        constexpr float kAcosC0 = 1.5707288f;
        constexpr float kAcosC1 = -0.2121144f;
        constexpr float kAcosC2 = 0.0742610f;
        constexpr float kAcosC3 = -0.0187293f;

    }  // namespace

    float acos(float _a)
    {
        const float absa   = abs(_a);
        const float tmp0   = mad(kAcosC3, absa, kAcosC2);
        const float tmp1   = mad(tmp0, absa, kAcosC1);
        const float tmp2   = mad(tmp1, absa, kAcosC0);
        const float tmp3   = tmp2 * sqrt(1.0f - absa);
        const float negate = float(_a < 0.0f);
        const float tmp4   = tmp3 - 2.0f * negate * tmp3;
        const float result = negate * kPi + tmp4;

        return result;
    }

    namespace
    {
        constexpr float kAtan2C0 = -0.013480470f;
        constexpr float kAtan2C1 = 0.057477314f;
        constexpr float kAtan2C2 = -0.121239071f;
        constexpr float kAtan2C3 = 0.195635925f;
        constexpr float kAtan2C4 = -0.332994597f;
        constexpr float kAtan2C5 = 0.999995630f;

    }  // namespace

    float atan2(float _y, float _x)
    {
        const float ax     = abs(_x);
        const float ay     = abs(_y);
        const float maxaxy = max(ax, ay);
        const float minaxy = min(ax, ay);

        if (maxaxy == 0.0f)
        {
            return 0.0f * sign(_y);
        }

        const float mxy    = minaxy / maxaxy;
        const float mxysq  = square(mxy);
        const float tmp0   = mad(kAtan2C0, mxysq, kAtan2C1);
        const float tmp1   = mad(tmp0, mxysq, kAtan2C2);
        const float tmp2   = mad(tmp1, mxysq, kAtan2C3);
        const float tmp3   = mad(tmp2, mxysq, kAtan2C4);
        const float tmp4   = mad(tmp3, mxysq, kAtan2C5);
        const float tmp5   = tmp4 * mxy;
        const float tmp6   = ay > ax ? kPiHalf - tmp5 : tmp5;
        const float tmp7   = _x < 0.0f ? kPi - tmp6 : tmp6;
        const float result = sign(_y) * tmp7;

        return result;
    }

    float ldexp(float _a, int32_t _b)
    {
        const uint32_t ftob     = floatToBits(_a);
        const uint32_t masked   = uint32_and(ftob, UINT32_C(0xff800000));
        const uint32_t expsign0 = uint32_sra(masked, 23);
        const uint32_t tmp      = uint32_iadd(expsign0, _b);
        const uint32_t expsign1 = uint32_sll(tmp, 23);
        const uint32_t mantissa = uint32_and(ftob, UINT32_C(0x007fffff));
        const uint32_t bits     = uint32_or(mantissa, expsign1);
        const float    result   = bitsToFloat(bits);

        return result;
    }

    float frexp(float _a, int32_t* _outExp)
    {
        const uint32_t ftob    = floatToBits(_a);
        const uint32_t masked0 = uint32_and(ftob, UINT32_C(0x7f800000));
        const uint32_t exp0    = uint32_srl(masked0, 23);
        const uint32_t masked1 = uint32_and(ftob, UINT32_C(0x807fffff));
        const uint32_t bits    = uint32_or(masked1, UINT32_C(0x3f000000));
        const float    result  = bitsToFloat(bits);

        *_outExp = int32_t(exp0 - 0x7e);

        return result;
    }

    namespace
    {
        constexpr float kExpC0 = 1.66666666666666019037e-01f;
        constexpr float kExpC1 = -2.77777777770155933842e-03f;
        constexpr float kExpC2 = 6.61375632143793436117e-05f;
        constexpr float kExpC3 = -1.65339022054652515390e-06f;
        constexpr float kExpC4 = 4.13813679705723846039e-08f;

    }  // namespace

    float exp(float _a)
    {
        if (abs(_a) <= kNearZero)
        {
            return _a + 1.0f;
        }

        const float kk     = round(_a * kInvLogNat2);
        const float hi     = _a - kk * kLogNat2Hi;
        const float lo     = kk * kLogNat2Lo;
        const float hml    = hi - lo;
        const float hmlsq  = square(hml);
        const float tmp0   = mad(kExpC4, hmlsq, kExpC3);
        const float tmp1   = mad(tmp0, hmlsq, kExpC2);
        const float tmp2   = mad(tmp1, hmlsq, kExpC1);
        const float tmp3   = mad(tmp2, hmlsq, kExpC0);
        const float tmp4   = hml - hmlsq * tmp3;
        const float tmp5   = hml * tmp4 / (2.0f - tmp4);
        const float tmp6   = 1.0f - ((lo - tmp5) - hi);
        const float result = ldexp(tmp6, int32_t(kk));

        return result;
    }

    namespace
    {
        constexpr float kLogC0 = 6.666666666666735130e-01f;
        constexpr float kLogC1 = 3.999999999940941908e-01f;
        constexpr float kLogC2 = 2.857142874366239149e-01f;
        constexpr float kLogC3 = 2.222219843214978396e-01f;
        constexpr float kLogC4 = 1.818357216161805012e-01f;
        constexpr float kLogC5 = 1.531383769920937332e-01f;
        constexpr float kLogC6 = 1.479819860511658591e-01f;

    }  // namespace

    float log(float _a)
    {
        int32_t exp;
        float   ff = frexp(_a, &exp);
        if (ff < kSqrt2 * 0.5f)
        {
            ff *= 2.0f;
            --exp;
        }

        ff -= 1.0f;
        const float kk = float(exp);
        const float hi = kk * kLogNat2Hi;
        const float lo = kk * kLogNat2Lo;
        const float ss = ff / (2.0f + ff);
        const float s2 = square(ss);
        const float s4 = square(s2);

        const float tmp0 = mad(kLogC6, s4, kLogC4);
        const float tmp1 = mad(tmp0, s4, kLogC2);
        const float tmp2 = mad(tmp1, s4, kLogC0);
        const float t1   = s2 * tmp2;

        const float tmp3 = mad(kLogC5, s4, kLogC3);
        const float tmp4 = mad(tmp3, s4, kLogC1);
        const float t2   = s4 * tmp4;

        const float t12    = t1 + t2;
        const float hfsq   = 0.5f * square(ff);
        const float result = hi - ((hfsq - (ss * (hfsq + t12) + lo)) - ff);

        return result;
    }

    //////////// Vec2 ///////////

    Vec2::Vec2(const float* data)
    {
        assert(data);
        x = data[0];
        y = data[1];
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

    Vec2 mul(float f, const Vec2& v)
    {
        return Vec2(f * v.x, f * v.y);
    }

    Vec2 mul(const Vec2& v, float f)
    {
        return Vec2(f * v.x, f * v.y);
    }

    void mul(float f, const Vec2& v, Vec2& dst)
    {
        dst.x = f * v.x;
        dst.y = f * v.y;
    }

    void mul(const Vec2& v, float f, Vec2& dst)
    {
        dst.x = f * v.x;
        dst.y = f * v.y;
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

    void clamp(Vec2& v, const Vec2& min, const Vec2& max)
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

    void normalize(Vec2& v)
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

    void scale(Vec2& v, float scale)
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

    void rotate(Vec2& v, const Vec2& point, float angle)
    {
        rotate(v, point, angle, v);
    }

    ////////////// Vec3 /////////////

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
        return v.x == 1.f && v.y == 1.f && v.z == 1.f;
    }

    Vec3 operator-(const Vec3& v)
    {
        return {-v.x, -v.y, -v.z};
    }

    bool less(const Vec3& lhs, const Vec3& rhs)
    {
        return lhs.x < rhs.x || lhs.y < rhs.y || lhs.z < rhs.z;
    }

    bool greater(const Vec3& lhs, const Vec3& rhs)
    {
        return lhs.x > rhs.x || lhs.y > rhs.y || lhs.z > rhs.z;
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

    Vec3 mul(float f, const Vec3& v)
    {
        return Vec3(f * v.x, f * v.y, f * v.z);
    }

    Vec3 mul(const Vec3& v, float f)
    {
        return Vec3(f * v.x, f * v.y, f * v.z);
    }

    void mul(float f, const Vec3& v, Vec3& dst)
    {
        dst.x = f * v.x;
        dst.y = f * v.y;
        dst.z = f * v.z;
    }

    void mul(const Vec3& v, float f, Vec3& dst)
    {
        dst.x = f * v.x;
        dst.y = f * v.y;
        dst.z = f * v.z;
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

    void clamp(Vec3& v, const Vec3& min, const Vec3& max)
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

    void normalize(Vec3& v)
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

    void scale(Vec3& v, float scale)
    {
        v.x = v.x * scale;
        v.y = v.y * scale;
        v.z = v.z * scale;
    }

    ////////////// Vec4 //////////////

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

    void clamp(Vec4& v, const Vec4& min, const Vec4& max)
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

    void normalize(Vec4& v)
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

    void scale(Vec4& v, float scale)
    {
        v.x = v.x * scale;
        v.y = v.y * scale;
        v.z = v.z * scale;
        v.w = v.w * scale;
    }

    ////////////////////////////// Triangle ///////////////////////////////////

    Triangle::Triangle(const float* data)
    {
        assert(data);
        memcpy(points, data, sizeof(points));
    }

    void barycenter(const Triangle& t, Vec3& dst)
    {
        NOT_IMPLEMENTED;
    }

    Vec3 barycenter(const Triangle& t)
    {
        Vec3 b;
        barycenter(t, b);
        return b;
    }

    ////////////////// Rect /////////////////////

    Rect::Rect(const Vec2& topLeft, const Vec2& size)
        : x(topLeft.x)
        , y(topLeft.y)
        , width(size.x)
        , height(size.y)
    {
    }

    ///////////////// Plane /////////////////////////////

    Plane::Plane(const Vec3& normal, float distance)
        : normal(normal)
        , distance(distance)
    {
    }

    float distance(const Vec3& point, const Plane& plane)
    {
        return dot(plane.normal, point) + plane.distance;
    }

    Plane normalize(const Plane& p)
    {
        Plane result;
        normalize(p, result);
        return result;
    }

    void normalize(const Plane& p, Plane& dst)
    {
        dst.distance = p.distance;
        normalize(p.normal, dst.normal);
    }

    void normalize(Plane& p)
    {
        normalize(p, p);
    }

    // TODO: provide implementation for Plane functions
    bool intersects(const Ray3& ray, const Plane& plane)
    {
        NOT_IMPLEMENTED;
    }

    bool intersects(const Plane& p1, const Plane& p2)
    {
        NOT_IMPLEMENTED;
    }

    bool intersects(const Box3& b, const Plane& p)
    {
        NOT_IMPLEMENTED;
    }

    bool intersects(const Sphere& s, const Plane& p)
    {
        NOT_IMPLEMENTED;

        return false;
    }

    bool intersects(const Frustum& f, const Plane& p)
    {
        NOT_IMPLEMENTED;

        return false;
    }

    bool intersection(const Plane& p1, const Plane& p2, const Plane& p3, Vec3& dst)
    {
        NOT_IMPLEMENTED;

        return false;
    }

    bool intersection(const Plane& p1, const Plane& p2, Ray3& dst)
    {
        NOT_IMPLEMENTED;

        return false;
    }

    bool intersection(const Sphere& s, const Plane& p, float& distance)
    {
        NOT_IMPLEMENTED;

        return false;
    }

    bool intersection(const Box3& b, const Plane& p, uint8_t& count, Vec3* dst)
    {
        NOT_IMPLEMENTED;

        return false;
    }

    bool intersection(const Frustum& f, const Plane& p, uint8_t& count, Vec3* dst)
    {
        NOT_IMPLEMENTED;

        return false;
    }

    Vec3 projectPoint(const Vec3& point, const Plane& plane)
    {
        NOT_IMPLEMENTED;

        return Vec3::Zero;
    }

    void projectPoint(const Vec3& point, const Plane& plane, Vec3& dst)
    {
        NOT_IMPLEMENTED;
    }

    Plane transform(const Plane& plane, const Mat4x4& tr)
    {
        NOT_IMPLEMENTED;

        return Plane();
    }

    void transform(const Plane& plane, const Mat4x4& tr, Plane& dst)
    {
        NOT_IMPLEMENTED;
    }

    void transform(Plane& plane)
    {
        NOT_IMPLEMENTED;
    }

    int side(const Vec3& point, const Plane& plane)
    {
        float d = distance(point, plane);
        if (d == 0.f)
            return 0;
        else if (d > 0.f)
            return 1;
        else
            return -1;
    }

    int side(const Box3& b, const Plane& p)
    {
        return side(b.center(), p);
    }

    int side(const Sphere& s, const Plane& p)
    {
        return side(s.center, p);
    }

    ///////////////////////////////////// Mat3x3 ////////////////////////////////

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
        *reinterpret_cast<Vec3*>(data)     = c1;
        *reinterpret_cast<Vec3*>(data + 3) = c2;
        *reinterpret_cast<Vec3*>(data + 6) = c3;
    }

    const Mat3x3 Mat3x3::Identity = Mat3x3(Vec3(1.f, 0.f, 0.f),  //
                                           Vec3(0.f, 1.f, 0.f),  //
                                           Vec3(0.f, 0.f, 1.f));

    ///////////////////// Mat4x4 //////////////////////

    Mat4x4::Mat4x4()
    {
        memset(data, 0, sizeof(data));
    }

    Mat4x4::Mat4x4(const float* data)
    {
        memcpy(this->data, data, sizeof(this->data));
    }

    Mat4x4::Mat4x4(const Mat3x3& rotation, const Vec3& scale, const Vec3& translation)
    {
        memset(data, 0, sizeof(data));
        data[0]  = rotation.data[0] * scale.x;
        data[1]  = rotation.data[1];
        data[2]  = rotation.data[2];
        data[4]  = rotation.data[3];
        data[5]  = rotation.data[4] * scale.y;
        data[6]  = rotation.data[5];
        data[8]  = rotation.data[6];
        data[9]  = rotation.data[7];
        data[10] = rotation.data[8] * scale.z;
        data[12] = translation.x;
        data[13] = translation.y;
        data[14] = translation.z;
        data[15] = 1.f;
    }

    Mat4x4::Mat4x4(const Quat& q, const Vec3& s, const Vec3& t)
    {
        float x2 = q.x + q.x;
        float y2 = q.y + q.y;
        float z2 = q.z + q.z;

        float xx2 = q.x * x2;
        float yy2 = q.y * y2;
        float zz2 = q.z * z2;
        float xy2 = q.x * y2;
        float xz2 = q.x * z2;
        float yz2 = q.y * z2;
        float wx2 = q.w * x2;
        float wy2 = q.w * y2;
        float wz2 = q.w * z2;

        data[0] = (1.0f - yy2 - zz2) * s.x;
        data[1] = xy2 + wz2;
        data[2] = xz2 - wy2;
        data[3] = 0.0f;

        data[4] = xy2 - wz2;
        data[5] = (1.0f - xx2 - zz2) * s.y;
        data[6] = yz2 + wx2;
        data[7] = 0.0f;

        data[8]  = xz2 + wy2;
        data[9]  = yz2 - wx2;
        data[10] = (1.0f - xx2 - yy2) * s.z;
        data[11] = 0.0f;

        data[12] = t.x;
        data[13] = t.y;
        data[14] = t.z;
        data[15] = 1.0f;
    }

    Mat4x4::Mat4x4(const Vec4& c1, const Vec4& c2, const Vec4& c3, const Vec4& c4)
    {
        memcpy(data, &c1, sizeof(c1));
        memcpy(data + 4, &c2, sizeof(c2));
        memcpy(data + 8, &c3, sizeof(c3));
        memcpy(data + 12, &c4, sizeof(c4));
    }

    const Mat4x4 Mat4x4::Identity = Mat4x4(Vec4(1.f, 0.f, 0.f, 0.f),  //
                                           Vec4(0.f, 1.f, 0.f, 0.f),  //
                                           Vec4(0.f, 0.f, 1.f, 0.f),  //
                                           Vec4(0.f, 0.f, 0.f, 1.f));

    bool isIdentity(const Mat4x4& matrix)
    {
        return (memcmp(&matrix, &Mat4x4::Identity, sizeof(matrix.data)) == 0);
    }

    void setIdentity(Mat4x4& dst)
    {
        memcpy(dst.data, &Mat4x4::Identity, sizeof(dst.data));
    }

    void mul(const Mat4x4& matrix, float scalar, Mat4x4& dst)
    {
        float*       d = dst.data;
        const float* m = matrix.data;
        d[0]           = m[0] * scalar;
        d[1]           = m[1] * scalar;
        d[2]           = m[2] * scalar;
        d[3]           = m[3] * scalar;
        d[4]           = m[4] * scalar;
        d[5]           = m[5] * scalar;
        d[6]           = m[6] * scalar;
        d[7]           = m[7] * scalar;
        d[8]           = m[8] * scalar;
        d[9]           = m[9] * scalar;
        d[10]          = m[10] * scalar;
        d[11]          = m[11] * scalar;
        d[12]          = m[12] * scalar;
        d[13]          = m[13] * scalar;
        d[14]          = m[14] * scalar;
        d[15]          = m[15] * scalar;
    }

    void mul(const Mat4x4& lhs, const Mat4x4& rhs, Mat4x4& dst)
    {
        const float* m1 = lhs.data;
        const float* m2 = rhs.data;
        float*       d  = dst.data;

        d[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
        d[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
        d[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
        d[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

        d[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
        d[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
        d[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
        d[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

        d[8]  = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
        d[9]  = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
        d[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
        d[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

        d[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
        d[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
        d[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
        d[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
    }

    void mul(Mat4x4& lhs, const Mat4x4& rhs)
    {
        Mat4x4 tmp;
        mul(lhs, rhs, tmp);
        lhs = tmp;
    }

    void createLookAt(const Vec3& eyePosition, const Vec3& targetPosition, const Vec3& up, Mat4x4& dst)
    {
        createLookAt(eyePosition.x, eyePosition.y, eyePosition.z, targetPosition.x, targetPosition.y, targetPosition.z,
                     up.x, up.y, up.z, dst);
    }

    void createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ, float targetCenterX,
                      float targetCenterY, float targetCenterZ, float upX, float upY, float upZ, Mat4x4& dst)
    {
        Vec3 eye(eyePositionX, eyePositionY, eyePositionZ);
        Vec3 target(targetCenterX, targetCenterY, targetCenterZ);
        Vec3 up(upX, upY, upZ);
        normalize(up);

        Vec3 zaxis;
        sub(eye, target, zaxis);
        normalize(zaxis);

        Vec3 xaxis;
        cross(up, zaxis, xaxis);
        normalize(xaxis);

        Vec3 yaxis;
        cross(zaxis, xaxis, yaxis);
        normalize(yaxis);

        dst.data[0] = xaxis.x;
        dst.data[1] = yaxis.x;
        dst.data[2] = zaxis.x;
        dst.data[3] = 0.0f;

        dst.data[4] = xaxis.y;
        dst.data[5] = yaxis.y;
        dst.data[6] = zaxis.y;
        dst.data[7] = 0.0f;

        dst.data[8]  = xaxis.z;
        dst.data[9]  = yaxis.z;
        dst.data[10] = zaxis.z;
        dst.data[11] = 0.0f;

        dst.data[12] = -dot(xaxis, eye);
        dst.data[13] = -dot(yaxis, eye);
        dst.data[14] = -dot(zaxis, eye);
        dst.data[15] = 1.0f;
    }

    void createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane, Mat4x4& dst)
    {
        assert(zFarPlane != zNearPlane);

        float f_n   = 1.0f / (zFarPlane - zNearPlane);
        float theta = kDegToRad * fieldOfView * 0.5f;
        if (abs(mod(theta, kPiHalf)) < kEpsilon)
        {
            printf(
                "Invalid field of view value (%.4f) causes attempted calculation "
                "tan(%.4f), which is undefined.",
                fieldOfView, theta);
            abort();
        }
        float divisor = tan(theta);
        assert(divisor);
        float factor = 1.0f / divisor;

        memset(&dst, 0, sizeof(dst));

        assert(aspectRatio);
        dst.data[0]  = (1.0f / aspectRatio) * factor;
        dst.data[5]  = factor;
        dst.data[10] = (-(zFarPlane + zNearPlane)) * f_n;
        dst.data[11] = -1.0f;
        dst.data[14] = -2.0f * zFarPlane * zNearPlane * f_n;
    }

    void createOrthographic(float width, float height, float zNearPlane, float zFarPlane, Mat4x4& dst)
    {
        float halfWidth  = width / 2.0f;
        float halfHeight = height / 2.0f;
        createOrthographicOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNearPlane, zFarPlane, dst);
    }

    void createOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane,
                                     float zFarPlane, Mat4x4& dst)
    {
        assert(right != left);
        assert(top != bottom);
        assert(zFarPlane != zNearPlane);

        memset(&dst, 0, sizeof(dst));
        dst.data[0]  = 2 / (right - left);
        dst.data[5]  = 2 / (top - bottom);
        dst.data[12] = (left + right) / (left - right);
        dst.data[10] = 1 / (zNearPlane - zFarPlane);
        dst.data[13] = (top + bottom) / (bottom - top);
        dst.data[14] = zNearPlane / (zNearPlane - zFarPlane);
        dst.data[15] = 1;
    }

    void createBillboardHelper(const Vec3& objectPosition,
                               const Vec3& cameraPosition,
                               const Vec3& cameraUpVector,
                               const Vec3* cameraForwardVector,
                               Mat4x4&     dst)
    {
        Vec3 delta             = sub(cameraPosition, objectPosition);
        bool isSufficientDelta = lengthSquared(delta) > kEpsilon;

        setIdentity(dst);
        dst.data[3]  = objectPosition.x;
        dst.data[7]  = objectPosition.y;
        dst.data[11] = objectPosition.z;

        // As per the contracts for the 2 variants of createBillboard, we need
        // either a safe default or a sufficient distance between object and camera.
        if (cameraForwardVector || isSufficientDelta)
        {
            Vec3 target = isSufficientDelta ? cameraPosition : sub(objectPosition, *cameraForwardVector);

            // A billboard is the inverse of a lookAt rotation
            Mat4x4 lookAt;
            createLookAt(objectPosition, target, cameraUpVector, lookAt);
            dst.data[0]  = lookAt.data[0];
            dst.data[1]  = lookAt.data[4];
            dst.data[2]  = lookAt.data[8];
            dst.data[4]  = lookAt.data[1];
            dst.data[5]  = lookAt.data[5];
            dst.data[6]  = lookAt.data[9];
            dst.data[8]  = lookAt.data[2];
            dst.data[9]  = lookAt.data[6];
            dst.data[10] = lookAt.data[10];
        }
    }

    void createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition, const Vec3& cameraUpVector,
                         Mat4x4& dst)
    {
        createBillboardHelper(objectPosition, cameraPosition, cameraUpVector, nullptr, dst);
    }

    void createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition, const Vec3& cameraUpVector,
                         const Vec3& cameraForwardVector, Mat4x4& dst)
    {
        createBillboardHelper(objectPosition, cameraPosition, cameraUpVector, &cameraForwardVector, dst);
    }

    void createReflection(const Plane& plane, Mat4x4& dst)
    {
        Vec3  normal(plane.normal);
        float k = -2.0f * plane.distance;

        setIdentity(dst);

        dst.data[0] -= 2.0f * normal.x * normal.x;
        dst.data[5] -= 2.0f * normal.y * normal.y;
        dst.data[10] -= 2.0f * normal.z * normal.z;
        dst.data[1] = dst.data[4] = -2.0f * normal.x * normal.y;
        dst.data[2] = dst.data[8] = -2.0f * normal.x * normal.z;
        dst.data[6] = dst.data[9] = -2.0f * normal.y * normal.z;

        dst.data[3]  = k * normal.x;
        dst.data[7]  = k * normal.y;
        dst.data[11] = k * normal.z;
    }

    void createScale(const Vec3& scale, Mat4x4& dst)
    {
        setIdentity(dst);

        dst.data[0]  = scale.x;
        dst.data[5]  = scale.y;
        dst.data[10] = scale.z;
    }

    void createScale(float xScale, float yScale, float zScale, Mat4x4& dst)
    {
        setIdentity(dst);

        dst.data[0]  = xScale;
        dst.data[5]  = yScale;
        dst.data[10] = zScale;
    }

    void createRotation(const Quat& quat, Mat4x4& dst)
    {
        float x2 = quat.x + quat.x;
        float y2 = quat.y + quat.y;
        float z2 = quat.z + quat.z;

        float xx2 = quat.x * x2;
        float yy2 = quat.y * y2;
        float zz2 = quat.z * z2;
        float xy2 = quat.x * y2;
        float xz2 = quat.x * z2;
        float yz2 = quat.y * z2;
        float wx2 = quat.w * x2;
        float wy2 = quat.w * y2;
        float wz2 = quat.w * z2;

        dst.data[0] = 1.0f - yy2 - zz2;
        dst.data[1] = xy2 + wz2;
        dst.data[2] = xz2 - wy2;
        dst.data[3] = 0.0f;

        dst.data[4] = xy2 - wz2;
        dst.data[5] = 1.0f - xx2 - zz2;
        dst.data[6] = yz2 + wx2;
        dst.data[7] = 0.0f;

        dst.data[8]  = xz2 + wy2;
        dst.data[9]  = yz2 - wx2;
        dst.data[10] = 1.0f - xx2 - yy2;
        dst.data[11] = 0.0f;

        dst.data[12] = 0.0f;
        dst.data[13] = 0.0f;
        dst.data[14] = 0.0f;
        dst.data[15] = 1.0f;
    }

    void createRotation(const Vec3& axis, float angle, Mat4x4& dst)
    {
        float x = axis.x;
        float y = axis.y;
        float z = axis.z;

        // Make sure the input axis is normalized.
        float n = x * x + y * y + z * z;
        if (n != 1.0f)
        {
            // Not normalized.
            n = sqrt(n);
            // Prevent divide too close to zero.
            if (n > 0.000001f)
            {
                n = 1.0f / n;
                x *= n;
                y *= n;
                z *= n;
            }
        }

        float c = cos(angle);
        float s = sin(angle);

        float t   = 1.0f - c;
        float tx  = t * x;
        float ty  = t * y;
        float tz  = t * z;
        float txy = tx * y;
        float txz = tx * z;
        float tyz = ty * z;
        float sx  = s * x;
        float sy  = s * y;
        float sz  = s * z;

        dst.data[0] = c + tx * x;
        dst.data[1] = txy + sz;
        dst.data[2] = txz - sy;
        dst.data[3] = 0.0f;

        dst.data[4] = txy - sz;
        dst.data[5] = c + ty * y;
        dst.data[6] = tyz + sx;
        dst.data[7] = 0.0f;

        dst.data[8]  = txz + sy;
        dst.data[9]  = tyz - sx;
        dst.data[10] = c + tz * z;
        dst.data[11] = 0.0f;

        dst.data[12] = 0.0f;
        dst.data[13] = 0.0f;
        dst.data[14] = 0.0f;
        dst.data[15] = 1.0f;
    }

    void createRotationX(float angle, Mat4x4& dst)
    {
        setIdentity(dst);

        float c = cos(angle);
        float s = sin(angle);

        dst.data[5]  = c;
        dst.data[6]  = s;
        dst.data[9]  = -s;
        dst.data[10] = c;
    }

    void createRotationY(float angle, Mat4x4& dst)
    {
        setIdentity(dst);

        float c = cos(angle);
        float s = sin(angle);

        dst.data[0]  = c;
        dst.data[2]  = -s;
        dst.data[8]  = s;
        dst.data[10] = c;
    }

    void createRotationZ(float angle, Mat4x4& dst)
    {
        setIdentity(dst);

        float c = cos(angle);
        float s = sin(angle);

        dst.data[0] = c;
        dst.data[1] = s;
        dst.data[4] = -s;
        dst.data[5] = c;
    }

    void createFromEuler(float yaw, float pitch, float roll, Mat4x4& dst)
    {
        setIdentity(dst);

        rotateY(dst, yaw);
        rotateX(dst, pitch);
        rotateZ(dst, roll);
    }

    void createTranslation(const Vec3& translation, Mat4x4& dst)
    {
        setIdentity(dst);

        dst.data[12] = translation.x;
        dst.data[13] = translation.y;
        dst.data[14] = translation.z;
    }

    void createTranslation(float xTranslation, float yTranslation, float zTranslation, Mat4x4& dst)
    {
        setIdentity(dst);

        dst.data[12] = xTranslation;
        dst.data[13] = yTranslation;
        dst.data[14] = zTranslation;
    }

    void decompose(const Mat4x4& matrix, Quat& rotation, Vec3& scale, Vec3& translation)
    {
        // Extract the translation.
        translation.x = matrix.data[12];
        translation.y = matrix.data[13];
        translation.z = matrix.data[14];

        // Extract the scale.
        // This is simply the length of each axis (row/column) in the matrix.
        Vec3  xaxis(matrix.data[0], matrix.data[1], matrix.data[2]);
        float scaleX = length(xaxis);

        Vec3  yaxis(matrix.data[4], matrix.data[5], matrix.data[6]);
        float scaleY = length(yaxis);

        Vec3  zaxis(matrix.data[8], matrix.data[9], matrix.data[10]);
        float scaleZ = length(zaxis);

        // Determine if we have a negative scale (true if determinant is less than
        // zero).
        // In this case, we simply negate a single axis of the scale.
        float det = determinant(matrix);
        if (det < 0)
            scaleZ = -scaleZ;

        scale.x = scaleX;
        scale.y = scaleY;
        scale.z = scaleZ;

        // Scale too close to zero, can't decompose rotation.
        if (scaleX < kFloatTolerance || scaleY < kFloatTolerance || abs(scaleZ) < kFloatTolerance)
        {
            printf("Scale too close to zero, can't decompose rotation");
            abort();
        }

        float rn;

        // Factor the scale out of the matrix axes.
        rn = 1.0f / scaleX;
        xaxis.x *= rn;
        xaxis.y *= rn;
        xaxis.z *= rn;

        rn = 1.0f / scaleY;
        yaxis.x *= rn;
        yaxis.y *= rn;
        yaxis.z *= rn;

        rn = 1.0f / scaleZ;
        zaxis.x *= rn;
        zaxis.y *= rn;
        zaxis.z *= rn;

        // Now calculate the rotation from the resulting matrix (axes).
        float trace = xaxis.x + yaxis.y + zaxis.z + 1.0f;

        if (trace > 1.0f)
        {
            float s    = 0.5f / sqrt(trace);
            rotation.w = 0.25f / s;
            rotation.x = (yaxis.z - zaxis.y) * s;
            rotation.y = (zaxis.x - xaxis.z) * s;
            rotation.z = (xaxis.y - yaxis.x) * s;
        }
        else
        {
            // Note: since xaxis, yaxis, and zaxis are normalized,
            // we will never divide by zero in the code below.
            if (xaxis.x > yaxis.y && xaxis.x > zaxis.z)
            {
                float s    = 0.5f / sqrt(1.0f + xaxis.x - yaxis.y - zaxis.z);
                rotation.w = (yaxis.z - zaxis.y) * s;
                rotation.x = 0.25f / s;
                rotation.y = (yaxis.x + xaxis.y) * s;
                rotation.z = (zaxis.x + xaxis.z) * s;
            }
            else if (yaxis.y > zaxis.z)
            {
                float s    = 0.5f / sqrt(1.0f + yaxis.y - xaxis.x - zaxis.z);
                rotation.w = (zaxis.x - xaxis.z) * s;
                rotation.x = (yaxis.x + xaxis.y) * s;
                rotation.y = 0.25f / s;
                rotation.z = (zaxis.y + yaxis.z) * s;
            }
            else
            {
                float s    = 0.5f / sqrt(1.0f + zaxis.z - xaxis.x - yaxis.y);
                rotation.w = (xaxis.y - yaxis.x) * s;
                rotation.x = (zaxis.x + xaxis.z) * s;
                rotation.y = (zaxis.y + yaxis.z) * s;
                rotation.z = 0.25f / s;
            }
        }
    }

    float determinant(const Mat4x4& matrix)
    {
        const float* m  = matrix.data;
        float        a0 = m[0] * m[5] - m[1] * m[4];
        float        a1 = m[0] * m[6] - m[2] * m[4];
        float        a2 = m[0] * m[7] - m[3] * m[4];
        float        a3 = m[1] * m[6] - m[2] * m[5];
        float        a4 = m[1] * m[7] - m[3] * m[5];
        float        a5 = m[2] * m[7] - m[3] * m[6];
        float        b0 = m[8] * m[13] - m[9] * m[12];
        float        b1 = m[8] * m[14] - m[10] * m[12];
        float        b2 = m[8] * m[15] - m[11] * m[12];
        float        b3 = m[9] * m[14] - m[10] * m[13];
        float        b4 = m[9] * m[15] - m[11] * m[13];
        float        b5 = m[10] * m[15] - m[11] * m[14];

        // Calculate the determinant.
        return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
    }

    void getScale(const Mat4x4& matrix, Vec3& scale)
    {
        // Extract the scale.
        // This is simply the length of each axis (row/column) in the matrix.
        Vec3  xaxis(matrix.data[0], matrix.data[1], matrix.data[2]);
        float scaleX = length(xaxis);

        Vec3  yaxis(matrix.data[4], matrix.data[5], matrix.data[6]);
        float scaleY = length(yaxis);

        Vec3  zaxis(matrix.data[8], matrix.data[9], matrix.data[10]);
        float scaleZ = length(zaxis);

        // Determine if we have a negative scale (true if determinant is less than
        // zero).
        // In this case, we simply negate a single axis of the scale.
        float det = determinant(matrix);
        if (det < 0)
            scaleZ = -scaleZ;

        scale.x = scaleX;
        scale.y = scaleY;
        scale.z = scaleZ;
    }

    void getRotation(const Mat4x4& matrix, Quat& rotation)
    {
        // Extract the scale.
        // This is simply the length of each axis (row/column) in the matrix.
        Vec3  xaxis(matrix.data[0], matrix.data[1], matrix.data[2]);
        float scaleX = length(xaxis);

        Vec3  yaxis(matrix.data[4], matrix.data[5], matrix.data[6]);
        float scaleY = length(yaxis);

        Vec3  zaxis(matrix.data[8], matrix.data[9], matrix.data[10]);
        float scaleZ = length(zaxis);

        // Determine if we have a negative scale (true if determinant is less than
        // zero).
        // In this case, we simply negate a single axis of the scale.
        float det = determinant(matrix);
        if (det < 0)
            scaleZ = -scaleZ;

        // Scale too close to zero, can't decompose rotation.
        if (scaleX < kFloatTolerance || scaleY < kFloatTolerance || abs(scaleZ) < kFloatTolerance)
        {
            printf("Scale too close to zero, can't decompose rotation");
            abort();
        }

        float rn;

        // Factor the scale out of the matrix axes.
        rn = 1.0f / scaleX;
        xaxis.x *= rn;
        xaxis.y *= rn;
        xaxis.z *= rn;

        rn = 1.0f / scaleY;
        yaxis.x *= rn;
        yaxis.y *= rn;
        yaxis.z *= rn;

        rn = 1.0f / scaleZ;
        zaxis.x *= rn;
        zaxis.y *= rn;
        zaxis.z *= rn;

        // Now calculate the rotation from the resulting matrix (axes).
        float trace = xaxis.x + yaxis.y + zaxis.z + 1.0f;

        if (trace > 1.0f)
        {
            float s    = 0.5f / sqrt(trace);
            rotation.w = 0.25f / s;
            rotation.x = (yaxis.z - zaxis.y) * s;
            rotation.y = (zaxis.x - xaxis.z) * s;
            rotation.z = (xaxis.y - yaxis.x) * s;
        }
        else
        {
            // Note: since xaxis, yaxis, and zaxis are normalized,
            // we will never divide by zero in the code below.
            if (xaxis.x > yaxis.y && xaxis.x > zaxis.z)
            {
                float s    = 0.5f / sqrt(1.0f + xaxis.x - yaxis.y - zaxis.z);
                rotation.w = (yaxis.z - zaxis.y) * s;
                rotation.x = 0.25f / s;
                rotation.y = (yaxis.x + xaxis.y) * s;
                rotation.z = (zaxis.x + xaxis.z) * s;
            }
            else if (yaxis.y > zaxis.z)
            {
                float s    = 0.5f / sqrt(1.0f + yaxis.y - xaxis.x - zaxis.z);
                rotation.w = (zaxis.x - xaxis.z) * s;
                rotation.x = (yaxis.x + xaxis.y) * s;
                rotation.y = 0.25f / s;
                rotation.z = (zaxis.y + yaxis.z) * s;
            }
            else
            {
                float s    = 0.5f / sqrt(1.0f + zaxis.z - xaxis.x - yaxis.y);
                rotation.w = (xaxis.y - yaxis.x) * s;
                rotation.x = (zaxis.x + xaxis.z) * s;
                rotation.y = (zaxis.y + yaxis.z) * s;
                rotation.z = 0.25f / s;
            }
        }
    }

    void getTranslation(const Mat4x4& matrix, Vec3& translation)
    {
        // Extract the translation.
        translation.x = matrix.data[12];
        translation.y = matrix.data[13];
        translation.z = matrix.data[14];
    }

    void getUp(const Mat4x4& matrix, Vec3& dst)
    {
        dst.x = matrix.data[4];
        dst.y = matrix.data[5];
        dst.z = matrix.data[6];
    }

    void getRight(const Mat4x4& matrix, Vec3& dst)
    {
        dst.x = matrix.data[0];
        dst.y = matrix.data[1];
        dst.z = matrix.data[2];
    }

    void getForward(const Mat4x4& matrix, Vec3& dst)
    {
        dst.x = -matrix.data[8];
        dst.y = -matrix.data[9];
        dst.z = -matrix.data[10];
    }

    bool canInvert(const Mat4x4& matrix)
    {
        return determinant(matrix) > kFloatTolerance;
    }

    void invert(const Mat4x4& matrix, Mat4x4& dst)
    {
        const float* m  = matrix.data;
        float        a0 = m[0] * m[5] - m[1] * m[4];
        float        a1 = m[0] * m[6] - m[2] * m[4];
        float        a2 = m[0] * m[7] - m[3] * m[4];
        float        a3 = m[1] * m[6] - m[2] * m[5];
        float        a4 = m[1] * m[7] - m[3] * m[5];
        float        a5 = m[2] * m[7] - m[3] * m[6];
        float        b0 = m[8] * m[13] - m[9] * m[12];
        float        b1 = m[8] * m[14] - m[10] * m[12];
        float        b2 = m[8] * m[15] - m[11] * m[12];
        float        b3 = m[9] * m[14] - m[10] * m[13];
        float        b4 = m[9] * m[15] - m[11] * m[13];
        float        b5 = m[10] * m[15] - m[11] * m[14];

        // Calculate the determinant.
        float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
        // Close to zero, can't invert.
        if (abs(det) <= kFloatTolerance)
        {
            printf("Determinant close to zero, can't invert matrix");
            abort();
        }

        // Support the case where m == dst.
        Mat4x4 inverse;
        inverse.data[0] = m[5] * b5 - m[6] * b4 + m[7] * b3;
        inverse.data[1] = -m[1] * b5 + m[2] * b4 - m[3] * b3;
        inverse.data[2] = m[13] * a5 - m[14] * a4 + m[15] * a3;
        inverse.data[3] = -m[9] * a5 + m[10] * a4 - m[11] * a3;

        inverse.data[4] = -m[4] * b5 + m[6] * b2 - m[7] * b1;
        inverse.data[5] = m[0] * b5 - m[2] * b2 + m[3] * b1;
        inverse.data[6] = -m[12] * a5 + m[14] * a2 - m[15] * a1;
        inverse.data[7] = m[8] * a5 - m[10] * a2 + m[11] * a1;

        inverse.data[8]  = m[4] * b4 - m[5] * b2 + m[7] * b0;
        inverse.data[9]  = -m[0] * b4 + m[1] * b2 - m[3] * b0;
        inverse.data[10] = m[12] * a4 - m[13] * a2 + m[15] * a0;
        inverse.data[11] = -m[8] * a4 + m[9] * a2 - m[11] * a0;

        inverse.data[12] = -m[4] * b3 + m[5] * b1 - m[6] * b0;
        inverse.data[13] = m[0] * b3 - m[1] * b1 + m[2] * b0;
        inverse.data[14] = -m[12] * a3 + m[13] * a1 - m[14] * a0;
        inverse.data[15] = m[8] * a3 - m[9] * a1 + m[10] * a0;

        mul(inverse, 1.0f / det, dst);
    }

    void invert(Mat4x4& matrix)
    {
        invert(matrix, matrix);
    }

    void rotate(const Mat4x4& matrix, const Quat& rotation, Mat4x4& dst)
    {
        Mat4x4 r;
        createRotation(rotation, r);
        mul(matrix, r, dst);
    }

    void rotate(Mat4x4& matrix, const Quat& rotation)
    {
        Mat4x4 tmp;
        rotate(matrix, rotation, tmp);
        matrix = tmp;
    }

    void rotate(const Mat4x4& matrix, const Vec3& axis, float angle, Mat4x4& dst)
    {
        Mat4x4 r;
        createRotation(axis, angle, r);
        mul(matrix, r, dst);
    }

    void rotate(Mat4x4& matrix, const Vec3& axis, float angle)
    {
        Mat4x4 tmp;
        rotate(matrix, axis, angle, tmp);
        matrix = tmp;
    }

    void rotateX(const Mat4x4& matrix, float angle, Mat4x4& dst)
    {
        Mat4x4 r;
        createRotationX(angle, r);
        mul(matrix, r, dst);
    }

    void rotateX(Mat4x4& matrix, float angle)
    {
        Mat4x4 tmp;
        rotateX(matrix, angle, tmp);
        matrix = tmp;
    }

    void rotateY(const Mat4x4& matrix, float angle, Mat4x4& dst)
    {
        Mat4x4 r;
        createRotationY(angle, r);
        mul(matrix, r, dst);
    }

    void rotateY(Mat4x4& matrix, float angle)
    {
        Mat4x4 tmp;
        rotateY(matrix, angle, tmp);
        matrix = tmp;
    }

    void rotateZ(const Mat4x4& matrix, float angle, Mat4x4& dst)
    {
        Mat4x4 r;
        createRotationZ(angle, r);
        mul(matrix, r, dst);
    }

    void rotateZ(Mat4x4& matrix, float angle)
    {
        Mat4x4 tmp;
        rotateZ(matrix, angle, tmp);
        matrix = tmp;
    }

    void scale(const Mat4x4& matrix, float s, Mat4x4& dst)
    {
        scale(matrix, s, s, s, dst);
    }

    void scale(const Mat4x4& matrix, float scaleX, float scaleY, float scaleZ, Mat4x4& dst)
    {
        Mat4x4 s;
        createScale(scaleX, scaleY, scaleZ, s);
        mul(matrix, s, dst);
    }

    void scale(const Mat4x4& matrix, const Vec3& s, Mat4x4& dst)
    {
        scale(matrix, s.x, s.y, s.z, dst);
    }

    void scale(Mat4x4& matrix, float s)
    {
        Mat4x4 tmp;
        scale(matrix, s, tmp);
        matrix = tmp;
    }

    void scale(Mat4x4& matrix, float scaleX, float scaleY, float scaleZ)
    {
        Mat4x4 tmp;
        scale(matrix, scaleX, scaleY, scaleZ, tmp);
        matrix = tmp;
    }

    void scale(Mat4x4& matrix, const Vec3& s)
    {
        Mat4x4 tmp;
        scale(matrix, s, tmp);
        matrix = tmp;
    }

    void transform(const Vec4& vec, const Mat4x4& matrix, Vec3& dst)
    {
        const float* v = vec.data;
        const float* m = matrix.data;
        // Handle case where v == dst.
        float x = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + v[3] * m[12];
        float y = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + v[3] * m[13];
        float z = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3] * m[14];

        dst.data[0] = x;
        dst.data[1] = y;
        dst.data[2] = z;
    }

    void transformPoint(const Vec3& point, const Mat4x4& matrix, Vec3& dst)
    {
        transform(Vec4(point, 1.f), matrix, dst);
    }

    void transformPoint(Vec3& point, const Mat4x4& matrix)
    {
        transform(Vec4(point, 1.f), matrix, point);
    }

    void transform(const Vec3& vec, const Mat4x4& matrix, Vec3& dst)
    {
        transform(Vec4(vec, 0.f), matrix, dst);
    }

    void transform(Vec3& v, const Mat4x4& matrix)
    {
        transform(v, matrix, v);
    }

    void transform(const Vec4& vec, const Mat4x4& matrix, Vec4& dst)
    {
        const float* v = vec.data;
        const float* m = matrix.data;
        // Handle case where v == dst.
        float x = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + v[3] * m[12];
        float y = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + v[3] * m[13];
        float z = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3] * m[14];
        float w = v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + v[3] * m[15];

        dst.data[0] = x;
        dst.data[1] = y;
        dst.data[2] = z;
        dst.data[3] = w;
    }

    void transform(Vec4& v, const Mat4x4& matrix)
    {
        transform(v, matrix, v);
    }

    void translate(const Mat4x4& matrix, const Vec3& translation, Mat4x4& dst)
    {
        translate(matrix, translation.x, translation.y, translation.z, dst);
    }

    void translate(Mat4x4& matrix, const Vec3& translation)
    {
        Mat4x4 tmp;
        translate(matrix, translation, tmp);
        matrix = tmp;
    }

    void translate(const Mat4x4& matrix, float x, float y, float z, Mat4x4& dst)
    {
        Mat4x4 t;
        createTranslation(x, y, z, t);
        mul(matrix, t, dst);
    }

    void translate(Mat4x4& matrix, float x, float y, float z)
    {
        Mat4x4 tmp;
        translate(matrix, x, y, z, tmp);
        matrix = tmp;
    }

    void transpose(const Mat4x4& matrix, Mat4x4& dst)
    {
        const float* m     = matrix.data;
        float        t[16] = {m[0], m[4], m[8],  m[12], m[1], m[5], m[9],  m[13],
                       m[2], m[6], m[10], m[14], m[3], m[7], m[11], m[15]};
        memcpy(&dst, t, sizeof(dst));
    }

    void transpose(Mat4x4& matrix)
    {
        transpose(matrix, matrix);
    }

    //////////////////////////////////////////// FRUSTUM /////////////////////////////////////////////

    Frustum::Frustum() {}

    void updatePlanes(Frustum& f, const Mat4x4& matrix)
    {
        const float* m = matrix.data;
        f.near         = Plane(Vec3(m[3] + m[2], m[7] + m[6], m[11] + m[10]), m[15] + m[14]);
        f.far          = Plane(Vec3(m[3] - m[2], m[7] - m[6], m[11] - m[10]), m[15] - m[14]);
        f.bottom       = Plane(Vec3(m[3] + m[1], m[7] + m[5], m[11] + m[9]), m[15] + m[13]);
        f.top          = Plane(Vec3(m[3] - m[1], m[7] - m[5], m[11] - m[9]), m[15] - m[13]);
        f.left         = Plane(Vec3(m[3] + m[0], m[7] + m[4], m[11] + m[8]), m[15] + m[12]);
        f.right        = Plane(Vec3(m[3] - m[0], m[7] - m[4], m[11] - m[8]), m[15] - m[12]);
    }

    Frustum::Frustum(const Mat4x4& matrix)
        : matrix(matrix)
    {
        updatePlanes(*this, matrix);
    }

    void getCorners(const Frustum& f, Vec3* dst)
    {
        assert(dst);
        getNearCorners(f, dst);
        getFarCorners(f, dst + 4);
    }

    void getNearCorners(const Frustum& f, Vec3* dst)
    {
        assert(dst);
        intersection(f.near, f.left, f.top, *dst);
        intersection(f.near, f.left, f.bottom, *(dst + 1));
        intersection(f.near, f.right, f.bottom, *(dst + 2));
        intersection(f.near, f.right, f.top, *(dst + 3));
    }

    void getFarCorners(const Frustum& f, Vec3* dst)
    {
        assert(dst);
        intersection(f.far, f.right, f.top, *dst);
        intersection(f.far, f.right, f.bottom, *(dst + 1));
        intersection(f.far, f.left, f.bottom, *(dst + 2));
        intersection(f.far, f.left, f.top, *(dst + 3));
    }

    bool intersects(const Vec3& point, const Frustum& f)
    {
        if (distance(point, f.near) <= 0)
            return false;
        if (distance(point, f.far) <= 0)
            return false;
        if (distance(point, f.left) <= 0)
            return false;
        if (distance(point, f.right) <= 0)
            return false;
        if (distance(point, f.top) <= 0)
            return false;
        if (distance(point, f.bottom) <= 0)
            return false;

        return true;
    }

    bool intersects(const Sphere& s, const Frustum& f)
    {
        return intersects(f, s);
    }

    bool intersects(const Box3& b, const Frustum& f)
    {
        return intersects(f, b);
    }

    bool intersects(const Plane& p, const Frustum& f)
    {
        return intersects(f, p);
    }

    bool intersects(const Ray3& r, const Frustum& f)
    {
        return intersects(f, r);
    }

    ///////////////////////////////////////////// QUAT ///////////////////////////////////////////

    Quat::Quat(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
        normalize(*this);
    }

    Quat::Quat(const Vec3& axis, float angle)
    {
        createFromAxisAngle(axis, angle, *this);
    }

    Quat::Quat(const Mat3x3& rotation) {}

    Quat::Quat(const Mat4x4& m)
    {
        createFromRotationMatrix(m, *this);
    }

    const Quat Quat::Identity = Quat(0.f, 0.f, 0.f, 1.f);
    const Quat Quat::Zero     = Quat();

    bool isZero(const Quat& q)
    {
        return q.x == 0.0f && q.y == 0.0f && q.z == 0.0f && q.w == 0.0f;
    }

    bool isIdentity(const Quat& q)
    {
        return q.x == 0.0f && q.y == 0.0f && q.z == 0.0f && q.w == 1.0f;
    }

    Quat createFromEuler(float yaw, float pitch, float roll)
    {
        Quat result;
        pitch *= 0.5f;
        yaw *= 0.5f;
        roll *= 0.5f;

        float sinp = sin(pitch);
        float siny = sin(yaw);
        float sinr = sin(roll);
        float cosp = cos(pitch);
        float cosy = cos(yaw);
        float cosr = cos(roll);

        result.w = cosp * cosy * cosr + sinp * siny * sinr;
        result.x = sinp * cosy * cosr - cosp * siny * sinr;
        result.y = cosp * siny * cosr + sinp * cosy * sinr;
        result.z = cosp * cosy * sinr - sinp * siny * cosr;
        return result;
    }

    void createFromEuler(float yaw, float pitch, float roll, Quat& dst)
    {
        pitch *= 0.5f;
        yaw *= 0.5f;
        roll *= 0.5f;

        float sinp = sin(pitch);
        float siny = sin(yaw);
        float sinr = sin(roll);
        float cosp = cos(pitch);
        float cosy = cos(yaw);
        float cosr = cos(roll);

        dst.w = cosp * cosy * cosr + sinp * siny * sinr;
        dst.x = sinp * cosy * cosr - cosp * siny * sinr;
        dst.y = cosp * siny * cosr + sinp * cosy * sinr;
        dst.z = cosp * cosy * sinr - sinp * siny * cosr;
    }

    Quat createFromRotationMatrix(const Mat4x4& m)
    {
        Quat result;
        getRotation(m, result);
        return result;
    }

    void createFromRotationMatrix(const Mat4x4& m, Quat& dst)
    {
        getRotation(m, dst);
    }

    Quat createFromAxisAngle(const Vec3& axis, float angle)
    {
        Quat  result;
        float halfAngle    = angle * 0.5f;
        float sinHalfAngle = sinf(halfAngle);

        Vec3 normal(axis);
        normalize(normal);
        result.x = normal.x * sinHalfAngle;
        result.y = normal.y * sinHalfAngle;
        result.z = normal.z * sinHalfAngle;
        result.w = cosf(halfAngle);
        return result;
    }

    void createFromAxisAngle(const Vec3& axis, float angle, Quat& dst)
    {
        float halfAngle    = angle * 0.5f;
        float sinHalfAngle = sinf(halfAngle);

        Vec3 normal(axis);
        normalize(normal);
        dst.x = normal.x * sinHalfAngle;
        dst.y = normal.y * sinHalfAngle;
        dst.z = normal.z * sinHalfAngle;
        dst.w = cosf(halfAngle);
    }

    Quat conjugate(const Quat& q)
    {
        Quat result;
        conjugate(q, result);
        return result;
    }

    void conjugate(const Quat& q, Quat& dst)
    {
        dst.x = -q.x;
        dst.y = -q.y;
        dst.z = -q.z;
        dst.w = q.w;
    }

    void conjugate(Quat& q)
    {
        conjugate(q, q);
    }

    void toEuler(const Quat& q, float& yaw, float& pitch, float& roll)
    {
        pitch = atan2(2 * (q.w * q.x + q.y * q.z), 1 - 2 * (q.x * q.x + q.y * q.y));
        yaw   = asin(2 * (q.w * q.y - q.z * q.x));
        roll  = atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.y * q.y + q.z * q.z));
    }

    Quat invert(const Quat& q)
    {
        Quat result;
        invert(q, result);
        return result;
    }

    void invert(const Quat& q, Quat& dst)
    {
        float n = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
        if (n == 1.0f)
        {
            dst.x = -q.x;
            dst.y = -q.y;
            dst.z = -q.z;
            dst.w = q.w;
        }

        // Too close to zero.
        if (n < 0.000001f)
        {
            printf("Too close to zero");
            abort();
        }

        n     = 1.0f / n;
        dst.x = -q.x * n;
        dst.y = -q.y * n;
        dst.z = -q.z * n;
        dst.w = q.w * n;
    }

    void invert(Quat& q)
    {
        invert(q, q);
    }

    Quat mul(const Quat& q1, const Quat& q2)
    {
        Quat result;
        mul(q1, q2, result);
        return result;
    }

    void mul(const Quat& q1, const Quat& q2, Quat& dst)
    {
        float x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
        float y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
        float z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
        float w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;

        dst.x = x;
        dst.y = y;
        dst.z = z;
        dst.w = w;
    }

    Quat normalize(const Quat& q)
    {
        Quat result;
        normalize(q, result);
        return result;
    }

    void normalize(const Quat& q, Quat& dst)
    {
        float n = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

        // Already normalized.
        if (n == 1.0f)
            return;

        n = sqrt(n);
        // Too close to zero.
        if (n < 0.000001f)
            return;

        n     = 1.0f / n;
        dst.x = q.x * n;
        dst.y = q.y * n;
        dst.z = q.z * n;
        dst.w = q.w * n;
    }

    void normalize(Quat& q)
    {
        normalize(q, q);
    }

    Vec3 rotatePoint(const Vec3& point, const Quat& q)
    {
        Vec3 result;
        rotatePoint(point, q, result);
        return result;
    }

    void rotatePoint(const Vec3& point, const Quat& q, Vec3& dst)
    {
        Quat vecQuat;
        Quat resQuat;
        vecQuat.x = point.x;
        vecQuat.y = point.y;
        vecQuat.z = point.z;
        vecQuat.w = 0.0f;

        Quat conQuat;
        conjugate(q, conQuat);

        mul(vecQuat, conQuat, resQuat);
        mul(q, resQuat, resQuat);

        dst.x = resQuat.x;
        dst.y = resQuat.y;
        dst.z = resQuat.z;
    }

    float quatToAxisAngle(const Quat& q, Vec3& dst)
    {
        float angle;
        quatToAxisAngle(q, dst, angle);
        return angle;
    }

    void quatToAxisAngle(const Quat& q, Vec3& dst, float& angle)
    {
        Quat tmp;
        normalize(q, tmp);

        dst.x = tmp.x;
        dst.y = tmp.y;
        dst.z = tmp.z;
        angle = (2.0f * acos(q.w));
    }

    Quat lerp(const Quat& q1, const Quat& q2, float t)
    {
        Quat result;
        lerp(q1, q2, t, result);
        return result;
    }

    void lerp(const Quat& q1, const Quat& q2, float t, Quat& dst)
    {
        assert(!(t < 0.0f || t > 1.0f));

        if (t == 0.0f)
        {
            memcpy(&dst, &q1, sizeof(float) * 4);
            return;
        }
        else if (t == 1.0f)
        {
            memcpy(&dst, &q2, sizeof(float) * 4);
            return;
        }

        float t1 = 1.0f - t;

        dst.x = t1 * q1.x + t * q2.x;
        dst.y = t1 * q1.y + t * q2.y;
        dst.z = t1 * q1.z + t * q2.z;
        dst.w = t1 * q1.w + t * q2.w;
    }

    Quat slerp(const Quat& q1, const Quat& q2, float t)
    {
        Quat result;
        slerp(q1, q2, t, result);
        return result;
    }

    void slerp(const Quat& q1, const Quat& q2, float t, Quat& dst)
    {
        // Fast slerp implementation by kwhatmough:
        // It contains no division operations, no trig, no inverse trig
        // and no sqrt. Not only does this code tolerate small constraint
        // errors in the input quaternions, it actually corrects for them.
        assert(!(t < 0.0f || t > 1.0f));

        if (t == 0.0f)
        {
            dst.x = q1.x;
            dst.y = q1.y;
            dst.z = q1.z;
            dst.w = q1.w;
            return;
        }
        else if (t == 1.0f)
        {
            dst.x = q2.x;
            dst.y = q2.y;
            dst.z = q2.z;
            dst.w = q2.w;
            return;
        }

        if (equal(q1.x, q2.x, kEpsilon) &&  //
            equal(q1.y, q2.y, kEpsilon) &&  //
            equal(q1.z, q2.z, kEpsilon) &&  //
            equal(q1.w, q2.w, kEpsilon))
        {
            dst.x = q1.x;
            dst.y = q1.y;
            dst.z = q1.z;
            dst.w = q1.w;
            return;
        }

        float halfY, alpha, beta;
        float u, f1, f2a, f2b;
        float ratio1, ratio2;
        float halfSecHalfTheta, versHalfTheta;
        float sqNotU, sqU;

        float cosTheta = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;

        // As usual in all slerp implementations, we fold theta.
        alpha = cosTheta >= 0 ? 1.0f : -1.0f;
        halfY = 1.0f + alpha * cosTheta;

        // Here we bisect the interval, so we need to fold t as well.
        f2b = t - 0.5f;
        u   = f2b >= 0 ? f2b : -f2b;
        f2a = u - f2b;
        f2b += u;
        u += u;
        f1 = 1.0f - u;

        // One iteration of Newton to get 1-cos(theta / 2) to good accuracy.
        halfSecHalfTheta = 1.09f - (0.476537f - 0.0903321f * halfY) * halfY;
        halfSecHalfTheta *= 1.5f - halfY * halfSecHalfTheta * halfSecHalfTheta;
        versHalfTheta = 1.0f - halfY * halfSecHalfTheta;

        // Evaluate series expansions of the coefficients.
        sqNotU = f1 * f1;
        ratio2 = 0.0000440917108f * versHalfTheta;
        ratio1 = -0.00158730159f + (sqNotU - 16.0f) * ratio2;
        ratio1 = 0.0333333333f + ratio1 * (sqNotU - 9.0f) * versHalfTheta;
        ratio1 = -0.333333333f + ratio1 * (sqNotU - 4.0f) * versHalfTheta;
        ratio1 = 1.0f + ratio1 * (sqNotU - 1.0f) * versHalfTheta;

        sqU    = u * u;
        ratio2 = -0.00158730159f + (sqU - 16.0f) * ratio2;
        ratio2 = 0.0333333333f + ratio2 * (sqU - 9.0f) * versHalfTheta;
        ratio2 = -0.333333333f + ratio2 * (sqU - 4.0f) * versHalfTheta;
        ratio2 = 1.0f + ratio2 * (sqU - 1.0f) * versHalfTheta;

        // Perform the bisection and resolve the folding done earlier.
        f1 *= ratio1 * halfSecHalfTheta;
        f2a *= ratio2;
        f2b *= ratio2;
        alpha *= f1 + f2a;
        beta = f1 + f2b;

        // Apply final coefficients to a and b as usual.
        float w = alpha * q1.w + beta * q2.w;
        float x = alpha * q1.x + beta * q2.x;
        float y = alpha * q1.y + beta * q2.y;
        float z = alpha * q1.z + beta * q2.z;

        // This final adjustment to the quaternion's length corrects for
        // any small constraint error in the inputs q1 and q2 But as you
        // can see, it comes at the cost of 9 additional multiplication
        // operations. If this error-correcting feature is not required,
        // the following code may be removed.
        f1    = 1.5f - 0.5f * (w * w + x * x + y * y + z * z);
        dst.w = w * f1;
        dst.x = x * f1;
        dst.y = y * f1;
        dst.z = z * f1;
    }

    void slerpForSquad(const Quat& q1, const Quat& q2, float t, Quat& dst)
    {
        // cos(omega) = q1 * q2;
        // slerp(q1, q2, t) = (q1*sin((1-t)*omega) + q2*sin(t*omega))/sin(omega);
        // q1 = +- q2, slerp(q1,q2,t) = q1.
        // This is a straight-forward implementation of the formula of slerp. It does
        // not do any sign switching.
        float c = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

        if (abs(c) >= 1.0f)
        {
            dst.x = q1.x;
            dst.y = q1.y;
            dst.z = q1.z;
            dst.w = q1.w;
            return;
        }

        float omega = acos(c);
        float s     = sqrt(1.0f - c * c);
        if (abs(s) <= 0.00001f)
        {
            dst.x = q1.x;
            dst.y = q1.y;
            dst.z = q1.z;
            dst.w = q1.w;
            return;
        }

        float r1 = sin((1 - t) * omega) / s;
        float r2 = sin(t * omega) / s;
        dst.x    = (q1.x * r1 + q2.x * r2);
        dst.y    = (q1.y * r1 + q2.y * r2);
        dst.z    = (q1.z * r1 + q2.z * r2);
        dst.w    = (q1.w * r1 + q2.w * r2);
    }

    Quat squad(const Quat& q1, const Quat& q2, const Quat& s1, const Quat& s2, float t)
    {
        Quat result;
        squad(q1, q2, s1, s2, t, result);
        return result;
    }

    void squad(const Quat& q1, const Quat& q2, const Quat& s1, const Quat& s2, float t, Quat& dst)
    {
        assert(!(t < 0.0f || t > 1.0f));

        Quat dstQ(0.0f, 0.0f, 0.0f, 1.0f);
        Quat dstS(0.0f, 0.0f, 0.0f, 1.0f);

        slerpForSquad(q1, q2, t, dstQ);
        slerpForSquad(s1, s2, t, dstS);
        slerpForSquad(dstQ, dstS, 2.0f * t * (1.0f - t), dst);
    }

    /////////////////////////// Line2 //////////////////////////////

    Line2::Line2(const Vec2& p1, const Vec2& p2)
        : p1(p1)
        , p2(p2)
    {
    }

    /////////////////////////// Line3 ///////////////////////////////

    Line3::Line3(const Vec3& p1, const Vec3& p2)
        : p1(p1)
        , p2(p2)
    {
    }

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

    Vec3 pointOnRay(const Ray3& r, float distance)
    {
        return add(r.origin, mul(distance, r.direction));
    }

    void pointOnRay(const Ray3& r, float distance, Vec3& dst)
    {
        add(r.origin, mul(distance, r.direction), dst);
    }

    float distance(const Vec3& point, const Ray3& r)
    {
        NOT_IMPLEMENTED;

        return 0.f;
    }

    bool intersects(const Plane& p, const Ray3& r)
    {
        const Vec3& normal = p.normal;
        // If the origin of the ray is on the plane then the distance is zero.
        float alpha = (dot(normal, r.origin) + p.distance);
        if (abs(alpha) < kEpsilon)
        {
            return 0.0f;
        }

        float dotP = dot(normal, r.direction);

        // If the dot product of the plane's normal and this ray's direction is zero,
        // then the ray is parallel to the plane and does not intersect it.
        if (dotP == 0.0f)
        {
            return false;
        }

        // Calculate the distance along the ray's direction vector to the point where
        // the ray intersects the plane (if it is negative the plane is behind the
        // ray).
        float d = -alpha / dotP;
        if (d < 0.0f)
        {
            return false;
        }

        return true;
    }

    bool intersects(const Box3& b, const Ray3& r)
    {
        return intersects(r, b);
    }

    bool intersects(const Sphere& s, const Ray3& r)
    {
        return intersects(r, s);
    }

    bool intersects(const Frustum& f, const Ray3& r)
    {
        NOT_IMPLEMENTED;

        return false;
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

    void getCorners(const Box3& b, Vec3* dst)
    {
        assert(dst);

        // Near face, specified counter-clockwise looking towards the origin from the
        // positive z-axis.
        // Left-top-front.
        dst[0] = {b.min.x, b.max.y, b.max.z};
        // Left-bottom-front.
        dst[1] = {b.min.x, b.min.y, b.max.z};
        // Right-bottom-front.
        dst[2] = {b.max.x, b.min.y, b.max.z};
        // Right-top-front.
        dst[3] = {b.max.x, b.max.y, b.max.z};

        // Far face, specified counter-clockwise looking towards the origin from the
        // negative z-axis.
        // Right-top-back.
        dst[4] = {b.max.x, b.max.y, b.min.z};
        // Right-bottom-back.
        dst[5] = {b.max.x, b.min.y, b.min.z};
        // Left-bottom-back.
        dst[6] = {b.min.x, b.min.y, b.min.z};
        // Left-top-back.
        dst[7] = {b.min.x, b.max.y, b.min.z};
    }

    bool intersects(const Box3& b1, const Box3& b2)
    {
        return ((b1.min.x >= b2.min.x && b1.min.x <= b2.max.x) || (b2.min.x >= b1.min.x && b2.min.x <= b1.max.x)) &&
               ((b1.min.y >= b2.min.y && b1.min.y <= b2.max.y) || (b2.min.y >= b1.min.y && b2.min.y <= b1.max.y)) &&
               ((b1.min.z >= b2.min.z && b1.min.z <= b2.max.z) || (b2.min.z >= b1.min.z && b2.min.z <= b1.max.z));
    }

    bool intersects(const Sphere& s, const Box3& b)
    {
        return intersects(b, s);
    }

    bool intersects(const Frustum& f, const Box3& b)
    {
        NOT_IMPLEMENTED;

        return false;
    }

    bool intersects(const Ray3& r, const Box3& b)
    {
        NOT_IMPLEMENTED;

        return false;
    }

    void extend(const Box3& b, const Vec3& point, Box3& dst)
    {
        if (less(point, b.min))
            dst.min = point;
        else if (less(b.max, point))
            dst.max = point;
    }

    void extend(Box3& b, const Vec3& point)
    {
        extend(b, point, b);
    }

    void merge(const Box3& b, const Sphere& s, Box3& dst)
    {
        NOT_IMPLEMENTED;
    }

    void merge(Box3& b, const Sphere& s)
    {
        NOT_IMPLEMENTED;
    }

    void merge(const Box3& b, const Box3& box, Box3& dst)
    {
        NOT_IMPLEMENTED;
    }

    void merge(Box3& b, const Box3& box)
    {
        NOT_IMPLEMENTED;
    }

    void transform(const Box3& b, const Mat4x4& m, Box3& dst)
    {
        NOT_IMPLEMENTED;
    }

    void transform(Box3& b, const Mat4x4& m)
    {
        NOT_IMPLEMENTED;
    }

    ///////////////////////// Circle ///////////////////////////////

    Circle::Circle(const Vec2& center, float radius)
        : center(center)
        , radius(radius)
    {
    }

    ///////////////////////// Sphere ////////////////////////////////

    Sphere::Sphere(const Vec3& center, float radius)
        : center(center)
        , radius(radius)
    {
    }

    bool intersects(const Sphere& s1, const Sphere& s2)
    {
        // If the distance between the spheres' centers is less than or equal
        // to the sum of their radii, then the spheres intersect.
        return distance(s1.center, s2.center) <= (s1.radius + s2.radius);
    }

    bool intersects(const Box3& b, const Sphere& s)
    {
        // Determine what point is closest; if the distance to that
        // point is less than the radius, then this sphere intersects.
        float cpX = s.center.x;
        float cpY = s.center.y;
        float cpZ = s.center.z;

        const Vec3& boxMin = b.min;
        const Vec3& boxMax = b.max;
        // Closest x value.
        if (s.center.x < boxMin.x)
        {
            cpX = boxMin.x;
        }
        else if (s.center.x > boxMax.x)
        {
            cpX = boxMax.x;
        }

        // Closest y value.
        if (s.center.y < boxMin.y)
        {
            cpY = boxMin.y;
        }
        else if (s.center.y > boxMax.y)
        {
            cpY = boxMax.y;
        }

        // Closest z value.
        if (s.center.z < boxMin.z)
        {
            cpZ = boxMin.z;
        }
        else if (s.center.z > boxMax.z)
        {
            cpZ = boxMax.z;
        }

        // Find the distance to the closest point and see if it is less than or equal
        // to the radius.
        cpX -= s.center.x;
        cpY -= s.center.y;
        cpZ -= s.center.z;

        return sqrt(cpX * cpX + cpY * cpY + cpZ * cpZ) <= s.radius;
    }

    bool intersects(const Frustum& f, const Sphere& s)
    {
        // TODO: find a more faster way to test this
        return ((side(s, f.near) == 1 &&    //
                 side(s, f.far) == 1 &&     //
                 side(s, f.left) == 1 &&    //
                 side(s, f.right) == 1 &&   //
                 side(s, f.bottom) == 1 &&  //
                 side(s, f.top) == 1) ||    //
                intersects(f.near, s) ||    //
                intersects(f.far, s) ||     //
                intersects(f.left, s) ||    //
                intersects(f.right, s) ||   //
                intersects(f.bottom, s) ||  //
                intersects(f.top, s));
    }

    bool intersects(const Plane& p, const Sphere& s)
    {
        return abs(distance(s.center, p)) <= s.radius;
    }

    bool intersects(const Ray3& r, const Sphere& s)
    {
        return distance(s.center, r) <= s.radius;
    }
}
}
