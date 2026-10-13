#pragma once

#include <cmath>

#include <NeonMath/Constants.h>
#include <NeonMath/Math/MathUtils.h>
#include <NeonMath/Types.h>

namespace ne {

struct Vec2 {
    f32 x{};
    f32 y{};

    constexpr Vec2() noexcept = default;
    constexpr Vec2(f32 vx, f32 vy) noexcept : x(vx), y(vy) {}

    constexpr bool operator==(const Vec2& other) const noexcept = default;
    constexpr bool operator!=(const Vec2& other) const noexcept = default;

    constexpr Vec2 operator+() const noexcept { return *this; }
    constexpr Vec2 operator-() const noexcept { return Vec2(-x, -y); }

    constexpr Vec2 operator+(const Vec2& other) const noexcept {
        return Vec2(x + other.x, y + other.y);
    }

    constexpr Vec2 operator-(const Vec2& other) const noexcept {
        return Vec2(x - other.x, y - other.y);
    }

    constexpr Vec2 operator*(f32 scalar) const noexcept {
        return Vec2(x * scalar, y * scalar);
    }

    constexpr Vec2 operator/(f32 scalar) const noexcept {
        if (scalar == 0.0f) {
            return Vec2(0.0f, 0.0f);
        }
        return Vec2(x / scalar, y / scalar);
    }

    constexpr Vec2& operator+=(const Vec2& other) noexcept { x += other.x; y += other.y; return *this; }
    constexpr Vec2& operator-=(const Vec2& other) noexcept { x -= other.x; y -= other.y; return *this; }
    constexpr Vec2& operator*=(f32 scalar) noexcept { x *= scalar; y *= scalar; return *this; }
    constexpr Vec2& operator/=(f32 scalar) noexcept {
        if (scalar != 0.0f) {
            x /= scalar;
            y /= scalar;
        }
        return *this;
    }

    friend constexpr Vec2 operator*(f32 scalar, const Vec2& vector) noexcept {
        return vector * scalar;
    }

    [[nodiscard]] constexpr f32 dot(const Vec2& other) const noexcept {
        return x * other.x + y * other.y;
    }

    [[nodiscard]] constexpr f32 lengthSquared() const noexcept {
        return dot(*this);
    }

    [[nodiscard]] constexpr f32 length() const noexcept {
        return std::sqrt(lengthSquared());
    }

    [[nodiscard]] constexpr bool tryNormalize(Vec2& out) const noexcept {
        const f32 len = length();
        if (!std::isfinite(len) || len <= Epsilon) {
            out = Vec2(0.0f, 0.0f);
            return false;
        }
        out = *this / len;
        return true;
    }

    [[nodiscard]] constexpr Vec2 normalized() const noexcept {
        Vec2 out(0.0f, 0.0f);
        if (!tryNormalize(out)) {
            return out;
        }
        return out;
    }

    [[nodiscard]] constexpr f32 cross(const Vec2& other) const noexcept {
        return x * other.y - y * other.x;
    }

    [[nodiscard]] constexpr bool isFinite() const noexcept {
        return std::isfinite(x) && std::isfinite(y);
    }

    [[nodiscard]] constexpr Vec2 lerp(const Vec2& target, f32 t) const noexcept {
        return Vec2(ne::lerp(x, target.x, t), ne::lerp(y, target.y, t));
    }

    static constexpr Vec2 Zero() noexcept { return Vec2(0.0f, 0.0f); }
    static constexpr Vec2 One() noexcept { return Vec2(1.0f, 1.0f); }
};

} // namespace ne
