#pragma once

#include <cmath>

#include <NeonMath/Constants.h>
#include <NeonMath/Math/MathUtils.h>
#include <NeonMath/Types.h>

namespace ne {

struct Vec3 {
    f32 x{};
    f32 y{};
    f32 z{};

    constexpr Vec3() noexcept = default;
    constexpr Vec3(f32 vx, f32 vy, f32 vz) noexcept : x(vx), y(vy), z(vz) {}

    constexpr bool operator==(const Vec3& other) const noexcept = default;
    constexpr bool operator!=(const Vec3& other) const noexcept = default;

    constexpr Vec3 operator+() const noexcept { return *this; }
    constexpr Vec3 operator-() const noexcept { return Vec3(-x, -y, -z); }

    constexpr Vec3 operator+(const Vec3& other) const noexcept {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    constexpr Vec3 operator-(const Vec3& other) const noexcept {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    constexpr Vec3 operator*(f32 scalar) const noexcept {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    constexpr Vec3 operator/(f32 scalar) const noexcept {
        if (scalar == 0.0f) {
            return Vec3(0.0f, 0.0f, 0.0f);
        }
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    constexpr Vec3& operator+=(const Vec3& other) noexcept { x += other.x; y += other.y; z += other.z; return *this; }
    constexpr Vec3& operator-=(const Vec3& other) noexcept { x -= other.x; y -= other.y; z -= other.z; return *this; }
    constexpr Vec3& operator*=(f32 scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; return *this; }
    constexpr Vec3& operator/=(f32 scalar) noexcept {
        if (scalar != 0.0f) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
        }
        return *this;
    }

    friend constexpr Vec3 operator*(f32 scalar, const Vec3& vector) noexcept {
        return vector * scalar;
    }

    [[nodiscard]] constexpr f32 dot(const Vec3& other) const noexcept {
        return x * other.x + y * other.y + z * other.z;
    }

    [[nodiscard]] constexpr f32 lengthSquared() const noexcept {
        return dot(*this);
    }

    [[nodiscard]] constexpr f32 length() const noexcept {
        return std::sqrt(lengthSquared());
    }

    [[nodiscard]] constexpr bool tryNormalize(Vec3& out) const noexcept {
        const f32 len = length();
        if (!std::isfinite(len) || len <= Epsilon) {
            out = Vec3(0.0f, 0.0f, 0.0f);
            return false;
        }
        out = *this / len;
        return true;
    }

    [[nodiscard]] constexpr Vec3 normalized() const noexcept {
        Vec3 out(0.0f, 0.0f, 0.0f);
        if (!tryNormalize(out)) {
            return out;
        }
        return out;
    }

    [[nodiscard]] constexpr Vec3 cross(const Vec3& other) const noexcept {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    [[nodiscard]] constexpr bool isFinite() const noexcept {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }

    [[nodiscard]] constexpr Vec3 lerp(const Vec3& target, f32 t) const noexcept {
        return Vec3(ne::lerp(x, target.x, t), ne::lerp(y, target.y, t), ne::lerp(z, target.z, t));
    }

    static constexpr Vec3 Zero() noexcept { return Vec3(0.0f, 0.0f, 0.0f); }
    static constexpr Vec3 One() noexcept { return Vec3(1.0f, 1.0f, 1.0f); }
};

} // namespace ne
