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

    constexpr float kPi             = 3.1415926535897932384626433832795f;
    constexpr float kPi2            = 6.2831853071795864769252867665590f;
    constexpr float kInvPi          = 1.0f / kPi;
    constexpr float kPiHalf         = 1.5707963267948966192313216916398f;
    constexpr float kPiQuarter      = 0.7853981633974483096156608458199f;
    constexpr float kSqrt2          = 1.4142135623730950488016887242097f;
    constexpr float kLogNat10       = 2.3025850929940456840179914546844f;
    constexpr float kInvLogNat2     = 1.4426950408889634073599246810019f;
    constexpr float kLogNat2Hi      = 0.6931471805599453094172321214582f;
    constexpr float kLogNat2Lo      = 1.90821492927058770002e-10f;
    constexpr float kE              = 2.7182818284590452353602874713527f;
    constexpr float kNearZero       = 1.0f / float(1 << 28);
    constexpr float kFloatMin       = 1.175494e-38f;
    constexpr float kFloatMax       = 3.402823e+38f;
    constexpr float kFloatSmall     = 1.0e-37f;
    constexpr float kFloatTolerance = 2e-37f;
    constexpr float kEpsilon        = 1e-6f;
    constexpr float kDegToRad       = (kPi / 180.0f);
    constexpr float kRadToDeg       = (180.0f / kPi);

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

    //////////////////////////////////////// INLINES //////////////////////////////

    inline constexpr uint32_t uint32_li(uint32_t _a)
    {
        return _a;
    }

    inline constexpr uint32_t uint32_dec(uint32_t _a)
    {
        return _a - 1;
    }

    inline constexpr uint32_t uint32_inc(uint32_t _a)
    {
        return _a + 1;
    }

    inline constexpr uint32_t uint32_not(uint32_t _a)
    {
        return ~_a;
    }

    inline constexpr uint32_t uint32_neg(uint32_t _a)
    {
        return -(int32_t)_a;
    }

    inline constexpr uint32_t uint32_ext(uint32_t _a)
    {
        return ((int32_t)_a) >> 31;
    }

    inline constexpr uint32_t uint32_and(uint32_t _a, uint32_t _b)
    {
        return _a & _b;
    }

    inline constexpr uint32_t uint32_andc(uint32_t _a, uint32_t _b)
    {
        return _a & ~_b;
    }

    inline constexpr uint32_t uint32_xor(uint32_t _a, uint32_t _b)
    {
        return _a ^ _b;
    }

    inline constexpr uint32_t uint32_xorl(uint32_t _a, uint32_t _b)
    {
        return !_a != !_b;
    }

    inline constexpr uint32_t uint32_or(uint32_t _a, uint32_t _b)
    {
        return _a | _b;
    }

    inline constexpr uint32_t uint32_orc(uint32_t _a, uint32_t _b)
    {
        return _a | ~_b;
    }

    inline constexpr uint32_t uint32_sll(uint32_t _a, int32_t _sa)
    {
        return _a << _sa;
    }

    inline constexpr uint32_t uint32_srl(uint32_t _a, int32_t _sa)
    {
        return _a >> _sa;
    }

    inline constexpr uint32_t uint32_sra(uint32_t _a, int32_t _sa)
    {
        return ((int32_t)_a) >> _sa;
    }

    inline constexpr uint32_t uint32_rol(uint32_t _a, int32_t _sa)
    {
        return (_a << _sa) | (_a >> (32 - _sa));
    }

    inline constexpr uint32_t uint32_ror(uint32_t _a, int32_t _sa)
    {
        return (_a >> _sa) | (_a << (32 - _sa));
    }

    inline constexpr uint32_t uint32_add(uint32_t _a, uint32_t _b)
    {
        return _a + _b;
    }

    inline constexpr uint32_t uint32_iadd(uint32_t _a, uint32_t _b)
    {
        return int32_t(_a) + int32_t(_b);
    }

    inline constexpr uint32_t uint32_sub(uint32_t _a, uint32_t _b)
    {
        return _a - _b;
    }

    inline constexpr uint32_t uint32_isub(uint32_t _a, uint32_t _b)
    {
        return int32_t(_a) - int32_t(_b);
    }

    inline constexpr uint32_t uint32_mul(uint32_t _a, uint32_t _b)
    {
        return _a * _b;
    }

    inline constexpr uint32_t uint32_div(uint32_t _a, uint32_t _b)
    {
        return _a / _b;
    }

    inline constexpr uint32_t uint32_mod(uint32_t _a, uint32_t _b)
    {
        return _a % _b;
    }

    inline constexpr uint32_t uint32_cmpeq(uint32_t _a, uint32_t _b)
    {
        return -(_a == _b);
    }

    inline constexpr uint32_t uint32_cmpneq(uint32_t _a, uint32_t _b)
    {
        return -(_a != _b);
    }

    inline constexpr uint32_t uint32_cmplt(uint32_t _a, uint32_t _b)
    {
        return -(_a < _b);
    }

    inline constexpr uint32_t uint32_cmple(uint32_t _a, uint32_t _b)
    {
        return -(_a <= _b);
    }

    inline constexpr uint32_t uint32_cmpgt(uint32_t _a, uint32_t _b)
    {
        return -(_a > _b);
    }

    inline constexpr uint32_t uint32_cmpge(uint32_t _a, uint32_t _b)
    {
        return -(_a >= _b);
    }

    inline constexpr uint32_t uint32_setnz(uint32_t _a)
    {
        return -!!_a;
    }

    inline constexpr uint32_t uint32_satadd(uint32_t _a, uint32_t _b)
    {
        const uint32_t add    = uint32_add(_a, _b);
        const uint32_t lt     = uint32_cmplt(add, _a);
        const uint32_t result = uint32_or(add, lt);

        return result;
    }

    inline constexpr uint32_t uint32_satsub(uint32_t _a, uint32_t _b)
    {
        const uint32_t sub    = uint32_sub(_a, _b);
        const uint32_t le     = uint32_cmple(sub, _a);
        const uint32_t result = uint32_and(sub, le);

        return result;
    }

    inline constexpr uint32_t uint32_satmul(uint32_t _a, uint32_t _b)
    {
        const uint64_t mul    = (uint64_t)_a * (uint64_t)_b;
        const uint32_t hi     = mul >> 32;
        const uint32_t nz     = uint32_setnz(hi);
        const uint32_t result = uint32_or(uint32_t(mul), nz);

        return result;
    }

    inline constexpr uint32_t uint32_sels(uint32_t test, uint32_t _a, uint32_t _b)
    {
        const uint32_t mask   = uint32_ext(test);
        const uint32_t sel_a  = uint32_and(_a, mask);
        const uint32_t sel_b  = uint32_andc(_b, mask);
        const uint32_t result = uint32_or(sel_a, sel_b);

        return (result);
    }

    inline constexpr uint32_t uint32_selb(uint32_t _mask, uint32_t _a, uint32_t _b)
    {
        const uint32_t sel_a  = uint32_and(_a, _mask);
        const uint32_t sel_b  = uint32_andc(_b, _mask);
        const uint32_t result = uint32_or(sel_a, sel_b);

        return (result);
    }

    inline constexpr uint32_t uint32_imin(uint32_t _a, uint32_t _b)
    {
        const uint32_t a_sub_b = uint32_sub(_a, _b);
        const uint32_t result  = uint32_sels(a_sub_b, _a, _b);

        return result;
    }

    inline constexpr uint32_t uint32_imax(uint32_t _a, uint32_t _b)
    {
        const uint32_t b_sub_a = uint32_sub(_b, _a);
        const uint32_t result  = uint32_sels(b_sub_a, _a, _b);

        return result;
    }

    inline constexpr uint32_t uint32_min(uint32_t _a, uint32_t _b)
    {
        return _a > _b ? _b : _a;
    }

    inline constexpr uint32_t uint32_min(uint32_t _a, uint32_t _b, uint32_t _c)
    {
        return uint32_min(_a, uint32_min(_b, _c));
    }

    inline constexpr uint32_t uint32_max(uint32_t _a, uint32_t _b)
    {
        return _a > _b ? _a : _b;
    }

    inline constexpr uint32_t uint32_max(uint32_t _a, uint32_t _b, uint32_t _c)
    {
        return uint32_max(_a, uint32_max(_b, _c));
    }

    inline constexpr uint32_t uint32_clamp(uint32_t _a, uint32_t _min, uint32_t _max)
    {
        const uint32_t tmp    = uint32_max(_a, _min);
        const uint32_t result = uint32_min(tmp, _max);

        return result;
    }

    inline constexpr uint32_t uint32_iclamp(uint32_t _a, uint32_t _min, uint32_t _max)
    {
        const uint32_t tmp    = uint32_imax(_a, _min);
        const uint32_t result = uint32_imin(tmp, _max);

        return result;
    }

    inline constexpr uint32_t uint32_incwrap(uint32_t _val, uint32_t _min, uint32_t _max)
    {
        const uint32_t inc          = uint32_inc(_val);
        const uint32_t max_diff     = uint32_sub(_max, _val);
        const uint32_t neg_max_diff = uint32_neg(max_diff);
        const uint32_t max_or       = uint32_or(max_diff, neg_max_diff);
        const uint32_t max_diff_nz  = uint32_ext(max_or);
        const uint32_t result       = uint32_selb(max_diff_nz, inc, _min);

        return result;
    }

    inline constexpr uint32_t uint32_decwrap(uint32_t _val, uint32_t _min, uint32_t _max)
    {
        const uint32_t dec          = uint32_dec(_val);
        const uint32_t min_diff     = uint32_sub(_min, _val);
        const uint32_t neg_min_diff = uint32_neg(min_diff);
        const uint32_t min_or       = uint32_or(min_diff, neg_min_diff);
        const uint32_t min_diff_nz  = uint32_ext(min_or);
        const uint32_t result       = uint32_selb(min_diff_nz, dec, _max);

        return result;
    }

    inline constexpr uint32_t uint32_cntbits(uint32_t _val)
    {
        const uint32_t tmp0   = uint32_srl(_val, 1);
        const uint32_t tmp1   = uint32_and(tmp0, 0x55555555);
        const uint32_t tmp2   = uint32_sub(_val, tmp1);
        const uint32_t tmp3   = uint32_and(tmp2, 0xc30c30c3);
        const uint32_t tmp4   = uint32_srl(tmp2, 2);
        const uint32_t tmp5   = uint32_and(tmp4, 0xc30c30c3);
        const uint32_t tmp6   = uint32_srl(tmp2, 4);
        const uint32_t tmp7   = uint32_and(tmp6, 0xc30c30c3);
        const uint32_t tmp8   = uint32_add(tmp3, tmp5);
        const uint32_t tmp9   = uint32_add(tmp7, tmp8);
        const uint32_t tmpA   = uint32_srl(tmp9, 6);
        const uint32_t tmpB   = uint32_add(tmp9, tmpA);
        const uint32_t tmpC   = uint32_srl(tmpB, 12);
        const uint32_t tmpD   = uint32_srl(tmpB, 24);
        const uint32_t tmpE   = uint32_add(tmpB, tmpC);
        const uint32_t tmpF   = uint32_add(tmpD, tmpE);
        const uint32_t result = uint32_and(tmpF, 0x3f);

        return result;
    }

    inline constexpr uint32_t uint32_cntlz(uint32_t _val)
    {
        const uint32_t tmp0   = uint32_srl(_val, 1);
        const uint32_t tmp1   = uint32_or(tmp0, _val);
        const uint32_t tmp2   = uint32_srl(tmp1, 2);
        const uint32_t tmp3   = uint32_or(tmp2, tmp1);
        const uint32_t tmp4   = uint32_srl(tmp3, 4);
        const uint32_t tmp5   = uint32_or(tmp4, tmp3);
        const uint32_t tmp6   = uint32_srl(tmp5, 8);
        const uint32_t tmp7   = uint32_or(tmp6, tmp5);
        const uint32_t tmp8   = uint32_srl(tmp7, 16);
        const uint32_t tmp9   = uint32_or(tmp8, tmp7);
        const uint32_t tmpA   = uint32_not(tmp9);
        const uint32_t result = uint32_cntbits(tmpA);

        return result;
    }

    inline constexpr uint32_t uint32_cnttz(uint32_t _val)
    {
        const uint32_t tmp0   = uint32_not(_val);
        const uint32_t tmp1   = uint32_dec(_val);
        const uint32_t tmp2   = uint32_and(tmp0, tmp1);
        const uint32_t result = uint32_cntbits(tmp2);

        return result;
    }

    inline constexpr uint32_t uint32_part1by1(uint32_t _a)
    {
        // shuffle:
        // ---- ---- ---- ---- fedc ba98 7654 3210
        // to:
        // -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0

        const uint32_t val = uint32_and(_a, 0xffff);

        const uint32_t tmp0 = uint32_sll(val, 8);
        const uint32_t tmp1 = uint32_xor(val, tmp0);
        const uint32_t tmp2 = uint32_and(tmp1, 0x00ff00ff);

        const uint32_t tmp3 = uint32_sll(tmp2, 4);
        const uint32_t tmp4 = uint32_xor(tmp2, tmp3);
        const uint32_t tmp5 = uint32_and(tmp4, 0x0f0f0f0f);

        const uint32_t tmp6 = uint32_sll(tmp5, 2);
        const uint32_t tmp7 = uint32_xor(tmp5, tmp6);
        const uint32_t tmp8 = uint32_and(tmp7, 0x33333333);

        const uint32_t tmp9   = uint32_sll(tmp8, 1);
        const uint32_t tmpA   = uint32_xor(tmp8, tmp9);
        const uint32_t result = uint32_and(tmpA, 0x55555555);

        return result;
    }

    inline constexpr uint32_t uint32_part1by2(uint32_t _a)
    {
        // shuffle:
        // ---- ---- ---- ---- ---- --98 7654 3210
        // to:
        // ---- 9--8 --7- -6-- 5--4 --3- -2-- 1--0

        const uint32_t val = uint32_and(_a, 0x3ff);

        const uint32_t tmp0 = uint32_sll(val, 16);
        const uint32_t tmp1 = uint32_xor(val, tmp0);
        const uint32_t tmp2 = uint32_and(tmp1, 0xff0000ff);

        const uint32_t tmp3 = uint32_sll(tmp2, 8);
        const uint32_t tmp4 = uint32_xor(tmp2, tmp3);
        const uint32_t tmp5 = uint32_and(tmp4, 0x0300f00f);

        const uint32_t tmp6 = uint32_sll(tmp5, 4);
        const uint32_t tmp7 = uint32_xor(tmp5, tmp6);
        const uint32_t tmp8 = uint32_and(tmp7, 0x030c30c3);

        const uint32_t tmp9   = uint32_sll(tmp8, 2);
        const uint32_t tmpA   = uint32_xor(tmp8, tmp9);
        const uint32_t result = uint32_and(tmpA, 0x09249249);

        return result;
    }

    inline constexpr uint32_t uint32_testpow2(uint32_t _a)
    {
        const uint32_t tmp0   = uint32_dec(_a);
        const uint32_t tmp1   = uint32_xor(_a, tmp0);
        const uint32_t tmp2   = uint32_srl(tmp1, 1);
        const uint32_t result = uint32_cmpeq(tmp2, tmp0);

        return result;
    }

    inline constexpr uint32_t uint32_nextpow2(uint32_t _a)
    {
        const uint32_t tmp0   = uint32_dec(_a);
        const uint32_t tmp1   = uint32_srl(tmp0, 1);
        const uint32_t tmp2   = uint32_or(tmp0, tmp1);
        const uint32_t tmp3   = uint32_srl(tmp2, 2);
        const uint32_t tmp4   = uint32_or(tmp2, tmp3);
        const uint32_t tmp5   = uint32_srl(tmp4, 4);
        const uint32_t tmp6   = uint32_or(tmp4, tmp5);
        const uint32_t tmp7   = uint32_srl(tmp6, 8);
        const uint32_t tmp8   = uint32_or(tmp6, tmp7);
        const uint32_t tmp9   = uint32_srl(tmp8, 16);
        const uint32_t tmpA   = uint32_or(tmp8, tmp9);
        const uint32_t result = uint32_inc(tmpA);

        return result;
    }

    inline constexpr uint32_t uint64_cntbits(uint64_t _val)
    {
        const uint32_t lo = uint32_t(_val & UINT32_MAX);
        const uint32_t hi = uint32_t(_val >> 32);

        const uint32_t total = uint32_cntbits(lo) + uint32_cntbits(hi);
        return total;
    }

    inline constexpr uint32_t uint64_cntlz(uint64_t _val)
    {
        return _val & UINT64_C(0xffffffff00000000) ? uint32_cntlz(uint32_t(_val >> 32))
                                                   : uint32_cntlz(uint32_t(_val)) + 32;
    }

    inline constexpr uint32_t uint64_cnttz(uint64_t _val)
    {
        return _val & UINT64_C(0xffffffff) ? uint32_cnttz(uint32_t(_val)) : uint32_cnttz(uint32_t(_val >> 32)) + 32;
    }

    inline constexpr uint64_t uint64_sll(uint64_t _a, int32_t _sa)
    {
        return _a << _sa;
    }

    inline constexpr uint64_t uint64_srl(uint64_t _a, int32_t _sa)
    {
        return _a >> _sa;
    }

    inline constexpr uint64_t uint64_sra(uint64_t _a, int32_t _sa)
    {
        return ((int64_t)_a) >> _sa;
    }

    inline constexpr uint64_t uint64_rol(uint64_t _a, int32_t _sa)
    {
        return (_a << _sa) | (_a >> (64 - _sa));
    }

    inline constexpr uint64_t uint64_ror(uint64_t _a, int32_t _sa)
    {
        return (_a >> _sa) | (_a << (64 - _sa));
    }

    inline constexpr uint64_t uint64_add(uint64_t _a, uint64_t _b)
    {
        return _a + _b;
    }

    inline constexpr uint64_t uint64_sub(uint64_t _a, uint64_t _b)
    {
        return _a - _b;
    }

    inline constexpr uint64_t uint64_mul(uint64_t _a, uint64_t _b)
    {
        return _a * _b;
    }

    inline constexpr uint32_t uint32_gcd(uint32_t _a, uint32_t _b)
    {
        do
        {
            const uint32_t tmp = uint32_mod(_a, _b);
            _a                 = _b;
            _b                 = tmp;
        } while (_b);

        return _a;
    }

    inline constexpr uint32_t uint32_lcm(uint32_t _a, uint32_t _b)
    {
        return _a * (_b / uint32_gcd(_a, _b));
    }

    inline constexpr uint32_t strideAlign(uint32_t _offset, uint32_t _stride)
    {
        const uint32_t mod    = uint32_mod(_offset, _stride);
        const uint32_t add    = uint32_sub(_stride, mod);
        const uint32_t mask   = uint32_cmpeq(mod, 0);
        const uint32_t tmp    = uint32_selb(mask, 0, add);
        const uint32_t result = uint32_add(_offset, tmp);

        return result;
    }

    template <uint32_t Min>
    inline constexpr uint32_t strideAlign(uint32_t _offset, uint32_t _stride)
    {
        const uint32_t align  = uint32_lcm(Min, _stride);
        const uint32_t mod    = uint32_mod(_offset, align);
        const uint32_t mask   = uint32_cmpeq(mod, 0);
        const uint32_t tmp0   = uint32_selb(mask, 0, align);
        const uint32_t tmp1   = uint32_add(_offset, tmp0);
        const uint32_t result = uint32_sub(tmp1, mod);

        return result;
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
