#pragma once

#include "Hq/Math/MathTypes.h"
#include <cstdint>

namespace hq
{
namespace math
{
    ///////////////////////// Basic Functions /////////////////////////
    // The following basic functions implementations are copied/inspired
    // from https://github.com/bkaradzic/bx

    constexpr float    kPi         = 3.1415926535897932384626433832795f;
    constexpr float    kPi2        = 6.2831853071795864769252867665590f;
    constexpr float    kInvPi      = 1.0f / kPi;
    constexpr float    kPiHalf     = 1.5707963267948966192313216916398f;
    constexpr float    kPiQuarter  = 0.7853981633974483096156608458199f;
    constexpr float    kSqrt2      = 1.4142135623730950488016887242097f;
    constexpr float    kLogNat10   = 2.3025850929940456840179914546844f;
    constexpr float    kInvLogNat2 = 1.4426950408889634073599246810019f;
    constexpr float    kLogNat2Hi  = 0.6931471805599453094172321214582f;
    constexpr float    kLogNat2Lo  = 1.90821492927058770002e-10f;
    constexpr float    kE          = 2.7182818284590452353602874713527f;
    constexpr float    kNearZero   = 1.0f / float(1 << 28);
    constexpr float    kFloatMin   = 1.175494e-38f;
    constexpr float    kFloatMax   = 3.402823e+38f;
    constexpr float    kFloatSmall = 1.0e-37f;
    extern const float kInfinity;

    template <typename T>
    inline constexpr T min(const T& a, const T& b)
    {
        return a < b ? a : b;
    }

    template <typename T>
    inline constexpr T max(const T& a, const T& b)
    {
        return a > b ? a : b;
    }

    template <typename T>
    inline constexpr T min(const T& a, const T& b, const T& c)
    {
        return min(min(a, b), c);
    }

    template <typename T>
    inline constexpr T max(const T& a, const T& b, const T& c)
    {
        return max(max(a, b), c);
    }

    template <typename T>
    inline constexpr T mid(const T& a, const T& b, const T& c)
    {
        return max(min(a, b), min(max(a, b), c));
    }

    template <typename T>
    inline constexpr T clamp(const T& a, const T& minVal, const T& maxVal)
    {
        return max(min(a, maxVal), minVal);
    }

    template <typename T>
    inline constexpr bool isPowerOf2(T a)
    {
        return a && !(a & (a - 1));
    }

    /// Returns converted the argument _deg to radians.
    float toRad(float deg);

    /// Returns converted the argument _rad to degrees.
    float toDeg(float rad);

    /// Reinterprets the bit pattern of a as uint32_t.
    uint32_t floatToBits(float a);

    /// Reinterprets the bit pattern of a as float.
    float bitsToFloat(uint32_t a);

    /// Reinterprets the bit pattern of a as uint64_t.
    uint64_t doubleToBits(double a);

    /// Reinterprets the bit pattern of a as double.
    double bitsToDouble(uint64_t a);

    /// Returns sortable floating point value.
    uint32_t floatFlip(uint32_t value);

    /// Returns true if _f is a number that is NaN.
    bool isNan(float f);

    /// Returns true if _f is a number that is NaN.
    bool isNan(double f);

    /// Returns true if _f is not infinite and is not a NaN.
    bool isFinite(float f);

    /// Returns true if _f is not infinite and is not a NaN.
    bool isFinite(double f);

    /// Returns true if _f is infinite and is not a NaN.
    bool isInfinite(float f);

    /// Returns true if _f is infinite and is not a NaN.
    bool isInfinite(double f);

    /// Returns the largest integer value not greater than _f.
    constexpr float floor(float f);

    /// Returns the smallest integer value not less than _f.
    constexpr float ceil(float f);

    /// Returns the nearest integer value to _f, rounding halfway cases away from zero,
    constexpr float round(float f);

    /// Returns linear interpolation between two values a and b.
    constexpr float lerp(float a, float b, float t);

    /// Returns the sign of a.
    constexpr float sign(float a);

    /// Returns the absolute of a.
    constexpr float abs(float a);

    /// Returns the square of a.
    constexpr float square(float a);

    /// Returns the cosine of the argument a.
    float sin(float a);

    /// Returns hyperbolic sine of the argument a.
    float sinh(float a);

    /// Returns radian angle between -pi/2 and +pi/2 whose sine is a.
    float asin(float a);

    /// Returns the cosine of the argument a.
    float cos(float a);

    /// Returns hyperbolic cosine of the argument a.
    float cosh(float a);

    /// Returns radian angle between 0 and pi whose cosine is a.
    float acos(float a);

    /// Returns the circular tangent of the radian argument a.
    float tan(float a);

    /// Returns hyperbolic tangent of the argument a.
    float tanh(float a);

    /// Returns radian angle between -pi/2 and +pi/2 whose tangent is a.
    float atan(float a);

    /// Retruns the inverse tangent of _y/_x.
    float atan2(float y, float x);

    /// Computes a raised to the b power.
    float pow(float a, float b);

    /// Returns the result of multiplying a by 2 raised to the power of the exponent.
    float ldexp(float a, int32_t b);

    /// Returns decomposed given floating point value a into a normalized fraction and
    /// an integral power of two.
    float frexp(float a, int32_t* outExp);

    /// Returns e (2.71828...) raised to the a power.
    float exp(float a);

    /// Returns 2 raised to the a power.
    float exp2(float a);

    /// Returns the base e (2.71828...) logarithm of a.
    float log(float a);

    /// Returns the base 2 logarithm of a.
    float log2(float a);

    /// Returns the square root of a.
    float sqrt(float a);

    /// Returns reciprocal square root of a.
    float rsqrt(float a);

    /// Returns the nearest integer not greater in magnitude than a.
    constexpr float trunc(float a);

    /// Returns the fractional (or decimal) part of a, which is greater than or equal to 0
    /// and less than 1.
    constexpr float fract(float a);

    /// Returns result of multipla and add (a * b + c).
    constexpr float mad(float a, float b, float c);

    /// Returns the floating-point remainder of the division operation a/b.
    float mod(float a, float b);

    constexpr bool equal(float a, float b, float epsilon);

    float wrap(float a, float wrap);

    constexpr float step(float edge, float a);

    constexpr float pulse(float a, float start, float end);

    constexpr float smoothStep(float a);

    constexpr float bias(float time, float bias);

    constexpr float gain(float time, float gain);

    float angleDiff(float a, float b);

    /// Returns shortest distance linear interpolation between two angles.
    float angleLerp(float a, float b, float _t);

    ///////////////////////// Vec2 /////////////////////////

    bool isZero(const Vec2& v);
    bool isOne(const Vec2& v);
    Vec2 operator-(const Vec2& v);
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
    void  clamp(const Vec2& v, const Vec2& min, const Vec2& max, Vec2& dst);
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
    Vec2  rotate(const Vec2& v, const Vec2& point, float angle);
    void  rotate(const Vec2& v, const Vec2& point, float angle, Vec2& dst);
    void  rotateSelf(Vec2& v, const Vec2& point, float angle);

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
    Vec3 div(const Vec3& lhs, const Vec3& rhs);
    void div(const Vec3& lhs, const Vec3& rhs, Vec3& dst);

    float angle(const Vec3& v1, const Vec3& v2);
    Vec3  clamp(const Vec3& v, const Vec3& min, const Vec3& max);
    void  clamp(const Vec3& v, const Vec3& min, const Vec3& max, Vec3& dst);
    void  clampSelf(Vec3& v, const Vec3& min, const Vec3& max);
    Vec3  cross(const Vec3& v1, const Vec3& v2);
    void  cross(const Vec3& v1, const Vec3& v2, Vec3& dst);
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

    //////////////////////// Vec4 //////////////////////////

    bool isZero(const Vec4& v);
    bool isOne(const Vec4& v);
    Vec4 operator-(const Vec4& v);
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
    void  clamp(const Vec4& v, const Vec4& min, const Vec4& max, Vec4& dst);
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

////////////// INLINES //////////////////////////////
namespace hq
{
namespace math
{
    inline constexpr uint32_t uint32_sra(uint32_t a, int32_t _sa)
    {
        return a >> _sa;
    }

    inline constexpr uint32_t uint32_neg(uint32_t a)
    {
        return -a;
    }

    inline constexpr uint32_t uint32_or(uint32_t a, uint32_t b)
    {
        return a | b;
    }

    inline constexpr uint32_t uint32_xor(uint32_t a, uint32_t b)
    {
        return a ^ b;
    }

    inline float toRad(float _deg)
    {
        return _deg * kPi / 180.0f;
    }

    inline float toDeg(float _rad)
    {
        return _rad * 180.0f / kPi;
    }

    inline uint32_t floatToBits(float a)
    {
        union {
            float    f;
            uint32_t ui;
        } u = {a};
        return u.ui;
    }

    inline float bitsToFloat(uint32_t a)
    {
        union {
            uint32_t ui;
            float    f;
        } u = {a};
        return u.f;
    }

    inline uint64_t doubleToBits(double a)
    {
        union {
            double   f;
            uint64_t ui;
        } u = {a};
        return u.ui;
    }

    inline double bitsToDouble(uint64_t a)
    {
        union {
            uint64_t ui;
            double   f;
        } u = {a};
        return u.f;
    }

    inline uint32_t floatFlip(uint32_t value)
    {
        // Reference(s):
        // - http://archive.fo/2012.12.08-212402/http://stereopsis.com/radix.html
        //
        const uint32_t tmp0   = uint32_sra(value, 31);
        const uint32_t tmp1   = uint32_neg(tmp0);
        const uint32_t mask   = uint32_or(tmp1, 0x80000000);
        const uint32_t result = uint32_xor(value, mask);
        return result;
    }

    inline bool isNan(float _f)
    {
        const uint32_t tmp = floatToBits(_f) & INT32_MAX;
        return tmp > UINT32_C(0x7f800000);
    }

    inline bool isNan(double _f)
    {
        const uint64_t tmp = doubleToBits(_f) & INT64_MAX;
        return tmp > UINT64_C(0x7ff0000000000000);
    }

    inline bool isFinite(float _f)
    {
        const uint32_t tmp = floatToBits(_f) & INT32_MAX;
        return tmp < UINT32_C(0x7f800000);
    }

    inline bool isFinite(double _f)
    {
        const uint64_t tmp = doubleToBits(_f) & INT64_MAX;
        return tmp < UINT64_C(0x7ff0000000000000);
    }

    inline bool isInfinite(float _f)
    {
        const uint32_t tmp = floatToBits(_f) & INT32_MAX;
        return tmp == UINT32_C(0x7f800000);
    }

    inline bool isInfinite(double _f)
    {
        const uint64_t tmp = doubleToBits(_f) & INT64_MAX;
        return tmp == UINT64_C(0x7ff0000000000000);
    }

    inline constexpr float floor(float a)
    {
        if (a < 0.0f)
        {
            const float fr     = fract(-a);
            const float result = -a - fr;

            return -(0.0f != fr ? result + 1.0f : result);
        }

        return a - fract(a);
    }

    inline constexpr float ceil(float a)
    {
        return -floor(-a);
    }

    inline constexpr float round(float _f)
    {
        return floor(_f + 0.5f);
    }

    inline constexpr float lerp(float a, float b, float _t)
    {
        return a + (b - a) * _t;
    }

    inline constexpr float sign(float a)
    {
        return a < 0.0f ? -1.0f : 1.0f;
    }

    inline constexpr float abs(float a)
    {
        return a < 0.0f ? -a : a;
    }

    inline constexpr float square(float a)
    {
        return a * a;
    }

    inline float sin(float a)
    {
        return cos(a - kPiHalf);
    }

    inline float sinh(float a)
    {
        return 0.5f * (exp(a) - exp(-a));
    }

    inline float asin(float a)
    {
        return kPiHalf - acos(a);
    }

    inline float cosh(float a)
    {
        return 0.5f * (exp(a) + exp(-a));
    }

    inline float tan(float a)
    {
        return sin(a) / cos(a);
    }

    inline float tanh(float a)
    {
        const float tmp0   = exp(2.0f * a);
        const float tmp1   = tmp0 - 1.0f;
        const float tmp2   = tmp0 + 1.0f;
        const float result = tmp1 / tmp2;

        return result;
    }

    inline float atan(float a)
    {
        return atan2(a, 1.0f);
    }

    inline float pow(float a, float b)
    {
        return exp(b * log(a));
    }

    inline float exp2(float a)
    {
        return pow(2.0f, a);
    }

    inline float log2(float a)
    {
        return log(a) * kInvLogNat2;
    }

    inline float rsqrtRef(float a)
    {
        return pow(a, -0.5f);
    }

    inline float sqrtRef(float a)
    {
        if (a < kNearZero)
        {
            return 0.0f;
        }

        return 1.0f / rsqrtRef(a);
    }

    //    inline float sqrtSimd(float a)
    //    {
    //        const simd128_t aa    = simd_splat(a);
    //        const simd128_t sqrta = simd_sqrt(aa);
    //        float           result;
    //        simd_stx(&result, sqrta);

    //        return result;
    //    }

    inline float sqrt(float a)
    {
        //#if BXcONFIG_SUPPORTS_SIMD
        //        return sqrtSimd(a);
        //#else
        return sqrtRef(a);
        //#endif  // BXcONFIG_SUPPORTS_SIMD
    }

    //    inline float rsqrtSimd(float a)
    //    {
    //        if (a < kNearZero)
    //        {
    //            return 0.0f;
    //        }

    //        const simd128_t aa     = simd_splat(a);
    //        const simd128_t rsqrta = simd_rsqrt_nr(aa);
    //        float           result;
    //        simd_stx(&result, rsqrta);

    //        return result;
    //    }

    inline float rsqrt(float a)
    {
        //#if BXcONFIG_SUPPORTS_SIMD
        //        return rsqrtSimd(a);
        //#else
        return rsqrtRef(a);
        //#endif  // BXcONFIG_SUPPORTS_SIMD
    }

    inline constexpr float trunc(float a)
    {
        return float(int(a));
    }

    inline constexpr float fract(float a)
    {
        return a - trunc(a);
    }

    inline constexpr float mad(float a, float b, float c)
    {
        return a * b + c;
    }

    inline float mod(float a, float b)
    {
        return a - b * floor(a / b);
    }

    inline constexpr bool equal(float a, float b, float epsilon)
    {
        // Reference(s):
        // - Floating-point tolerances revisited
        //   https://web.archive.org/web/20181103180318/http://realtimecollisiondetection.net/blog/?p=89
        //
        const float lhs = abs(a - b);
        const float rhs = epsilon * max(1.0f, abs(a), abs(b));
        return lhs <= rhs;
    }

    inline bool equal(const float* a, const float* b, uint32_t num, float epsilon)
    {
        bool result = equal(a[0], b[0], epsilon);
        for (uint32_t ii = 1; result && ii < num; ++ii)
        {
            result = equal(a[ii], b[ii], epsilon);
        }
        return result;
    }

    inline float wrap(float a, float wrap)
    {
        const float tmp0   = mod(a, wrap);
        const float result = tmp0 < 0.0f ? wrap + tmp0 : tmp0;
        return result;
    }

    inline constexpr float step(float _edge, float a)
    {
        return a < _edge ? 0.0f : 1.0f;
    }

    inline constexpr float pulse(float a, float start, float end)
    {
        return step(a, start) - step(a, end);
    }

    inline constexpr float smoothStep(float a)
    {
        return square(a) * (3.0f - 2.0f * a);
    }

    inline constexpr float bias(float time, float bias)
    {
        return time / (((1.0f / bias - 2.0f) * (1.0f - time)) + 1.0f);
    }

    inline constexpr float gain(float time, float gain)
    {
        // Reference(s):
        // - Bias And Gain Are Your Friend
        //   https://web.archive.org/web/20181126040535/https://blog.demofox.org/2012/09/24/bias-and-gain-are-your-friend/
        //   https://web.archive.org/web/20181126040558/http://demofox.org/biasgain.html
        //
        if (time < 0.5f)
        {
            return bias(time * 2.0f, gain) * 0.5f;
        }

        return bias(time * 2.0f - 1.0f, 1.0f - gain) * 0.5f + 0.5f;
    }

    inline float angleDiff(float a, float b)
    {
        const float dist = wrap(b - a, kPi2);
        return wrap(dist * 2.0f, kPi2) - dist;
    }

    inline float angleLerp(float a, float b, float _t)
    {
        return a + angleDiff(a, b) * _t;
    }

}
}
