#include <cmath>
#include <limits>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <NeonMath/NeonMath.h>

using namespace ne;

TEST_CASE("Vec2 constructors and default values") {
    Vec2 a;
    REQUIRE(a.x == 0.0f);
    REQUIRE(a.y == 0.0f);

    Vec2 b(1.0f, 2.0f);
    REQUIRE(b == Vec2(1.0f, 2.0f));
    REQUIRE(b != Vec2(2.0f, 1.0f));
}

TEST_CASE("Vec2 arithmetic and dot product") {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(3.0f, 4.0f);

    Vec2 sum = a + b;
    REQUIRE(sum == Vec2(4.0f, 6.0f));

    Vec2 diff = a - b;
    REQUIRE(diff == Vec2(-2.0f, -2.0f));

    Vec2 neg = -a;
    REQUIRE(neg == Vec2(-1.0f, -2.0f));

    REQUIRE(a.dot(b) == 11.0f);
    REQUIRE(a.lengthSquared() == 5.0f);
    REQUIRE(approx(a.length()).margin(1.0e-5f) == std::sqrt(5.0f));
    REQUIRE(a.cross(b) == -2.0f);
}

TEST_CASE("Vec2 scale, division and safe normalization") {
    Vec2 a(4.0f, 0.0f);

    REQUIRE((a * 2.0f) == Vec2(8.0f, 0.0f));
    REQUIRE((a / 2.0f) == Vec2(2.0f, 0.0f));

    Vec2 normalized = a.normalized();
    REQUIRE(normalized == Vec2(1.0f, 0.0f));

    Vec2 zero(0.0f, 0.0f);
    Vec2 out(0.0f, 0.0f);

    REQUIRE_FALSE(zero.tryNormalize(out));
    REQUIRE(out == Vec2(0.0f, 0.0f));
    REQUIRE(zero.normalized() == Vec2(0.0f, 0.0f));
}

TEST_CASE("Vec3 constructors, arithmetic and cross product") {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);

    REQUIRE(a + b == Vec3(5.0f, 7.0f, 9.0f));
    REQUIRE(a - b == Vec3(-3.0f, -3.0f, -3.0f));
    REQUIRE(-a == Vec3(-1.0f, -2.0f, -3.0f));
    REQUIRE(a.dot(b) == 32.0f);
    REQUIRE(a.lengthSquared() == 14.0f);

    auto c = a.cross(b);
    REQUIRE(c == Vec3(-3.0f, 6.0f, -3.0f));
    REQUIRE(c.length() > 0.0f);
}

TEST_CASE("Vec3 normalization and finite checks") {
    Vec3 a(0.0f, 3.0f, 4.0f);
    Vec3 n = a.normalized();

    REQUIRE(n == Vec3(0.0f, 0.6f, 0.8f));

    Vec3 zero(0.0f, 0.0f, 0.0f);
    Vec3 out(0.0f, 0.0f, 0.0f);

    REQUIRE_FALSE(zero.tryNormalize(out));
    REQUIRE(out == Vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(zero.normalized() == Vec3(0.0f, 0.0f, 0.0f));

    Vec3 nanVec(std::numeric_limits<f32>::quiet_NaN(), 1.0f, 1.0f);
    Vec3 infVec(1.0f, std::numeric_limits<f32>::infinity(), 1.0f);

    REQUIRE_FALSE(nanVec.isFinite());
    REQUIRE_FALSE(infVec.isFinite());
}

TEST_CASE("Vec4 arithmetic and normalization") {
    Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);

    REQUIRE(a + b == Vec4(6.0f, 8.0f, 10.0f, 12.0f));
    REQUIRE(a - b == Vec4(-4.0f, -4.0f, -4.0f, -4.0f));
    REQUIRE(a.dot(b) == 70.0f);

    Vec4 c = a * 0.5f;
    REQUIRE(c == Vec4(0.5f, 1.0f, 1.5f, 2.0f));

    Vec4 z(0.0f, 0.0f, 0.0f, 0.0f);
    Vec4 nz(0.0f, 0.0f, 0.0f, 0.0f);
    REQUIRE_FALSE(z.tryNormalize(nz));
    REQUIRE(nz == Vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

TEST_CASE("MathUtils radians/degrees and clamp") {
    REQUIRE(approx(radians(180.0f)).margin(1.0e-5f) == Pi);
    REQUIRE(approx(degrees(Pi)).margin(1.0e-5f) == 180.0f);

    REQUIRE(clamp(5.0f, 1.0f, 4.0f) == 4.0f);
    REQUIRE(clamp(-10.0f, -5.0f, 5.0f) == -5.0f);
    REQUIRE(saturate(0.5f) == 0.5f);
    REQUIRE(saturate(-1.0f) == 0.0f);
    REQUIRE(saturate(2.0f) == 1.0f);
}

TEST_CASE("Lerp and nearlyEqual") {
    REQUIRE(lerp(1.0f, 3.0f, 0.5f) == 2.0f);
    REQUIRE(lerp(Vec2(0.0f, 0.0f), Vec2(10.0f, 10.0f), 0.5f) == Vec2(5.0f, 5.0f));

    REQUIRE(nearlyEqual(1.0f, 1.0f + 1.0e-7f));
    REQUIRE_FALSE(nearlyEqual(1.0f, 2.0f, 0.01f));
}

TEST_CASE("NaN and infinite value behavior") {
    Vec3 a(std::numeric_limits<f32>::quiet_NaN(), 0.0f, 0.0f);
    Vec3 b(1.0f, std::numeric_limits<f32>::infinity(), 0.0f);

    REQUIRE_FALSE(a.isFinite());
    REQUIRE_FALSE(b.isFinite());

    REQUIRE_FALSE(std::isfinite(a.length()));
    REQUIRE_FALSE(std::isfinite(b.length()));
}

TEST_CASE("Zero division contract") {
    Vec3 z(0.0f, 0.0f, 0.0f);
    Vec3 q = z / 0.0f;
    REQUIRE(q == Vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(z.length() == 0.0f);
}

TEST_CASE("Vec2 and Vec3 lerp") {
    Vec2 v2a(0.0f, 0.0f);
    Vec2 v2b(10.0f, 10.0f);
    Vec2 v2l = v2a.lerp(v2b, 0.25f);
    REQUIRE(v2l == Vec2(2.5f, 2.5f));

    Vec3 v3a(0.0f, 0.0f, 0.0f);
    Vec3 v3b(10.0f, 20.0f, 30.0f);
    Vec3 v3l = v3a.lerp(v3b, 0.5f);
    REQUIRE(v3l == Vec3(5.0f, 10.0f, 15.0f));
}
