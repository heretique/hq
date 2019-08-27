#include "catch.hpp"
#include "Hq/Math/Math.h"

using namespace hq::math;

TEST_CASE("Base math functions", "[base math]")
{
    {
        float f1 = 0.000001f;
        float f2 = 0.000003f;
        float f3 = 0.000002f;
        REQUIRE(!equal(f1, f2, kEpsilon));
        REQUIRE(equal(f1, f3, kEpsilon));
    }

    REQUIRE(equal(std::sin(kPi), hq::math::sin(kPi), kEpsilon));
    REQUIRE(equal(std::sin(kPiHalf), hq::math::sin(kPiHalf), kEpsilon));
    REQUIRE(equal(std::sin(1.5f), hq::math::sin(1.5f), kEpsilon));
    REQUIRE(equal(std::cos(kPi), hq::math::cos(kPi), kEpsilon));
    REQUIRE(equal(std::cos(kPiHalf), hq::math::cos(kPiHalf), kEpsilon));
    REQUIRE(equal(std::cos(1.5f), hq::math::cos(1.5f), kEpsilon));
    REQUIRE(equal(std::sinh(kPi), hq::math::sinh(kPi), kEpsilon));
    REQUIRE(equal(std::sinh(kPiHalf), hq::math::sinh(kPiHalf), kEpsilon));
    REQUIRE(equal(std::sinh(1.5f), hq::math::sinh(1.5f), kEpsilon));
    REQUIRE(equal(std::cosh(kPi), hq::math::cosh(kPi), kEpsilon));
    REQUIRE(equal(std::cosh(kPiHalf), hq::math::cosh(kPiHalf), kEpsilon));
    REQUIRE(equal(std::cosh(1.5f), hq::math::cosh(1.5f), kEpsilon));
}

TEST_CASE("Testing math vectors functions", "[math vectors]")
{
    REQUIRE(isZero(Vec2::Zero));
    REQUIRE(isZero(Vec3::Zero));
    REQUIRE(isOne(Vec2::One));
    REQUIRE(isOne(Vec3::One));

    {
        Vec2 v      = Vec2::One;
        Vec2 minusV = -v;
        REQUIRE((equal(minusV.x, -1.f, kEpsilon) && equal(minusV.y, -1.f, kEpsilon)));
    }

    {
        Vec3 v      = Vec3::One;
        Vec3 minusV = -v;
        REQUIRE((equal(minusV.x, -1.f, kEpsilon) &&  //
                 equal(minusV.y, -1.f, kEpsilon) &&  //
                 equal(minusV.z, -1.f, kEpsilon)));
    }
}
