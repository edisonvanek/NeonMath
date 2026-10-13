#pragma once

#include <cmath>

#include <NeonMath/Constants.h>
#include <NeonMath/Math/MathUtils.h>
#include <NeonMath/Types.h>

namespace ne {

struct Vec4 {
    f32 x{};
    f32 y{};
    f32 z{};
    f32 w{};

    constexpr Vec4() noexcept = default;
    constexpr Vec4(f32 vx, f32 vy, f32 vz, f32 vw) noexcept : x(vx), y(vy), z(vz), w(vw) {}

    constexpr bool operator==(const Vec4& other) const noexcept = default;
    constexpr bool operator!=(const Vec4& other) const noexcept = default;

    constexpr Vec4 operator+() const noexcept { return *this; }
    constexpr Vec4 operator-() const noexcept { return Vec4(-x, -y, -z, -w); }

    constexpr Vec4 operator+(const Vec4& other) const noexcept {
        return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    constexpr Vec4 operator-(const Vec4& other) const noexcept {
        return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    constexpr Vec4 operator*(f32 scalar) const noexcept {
        return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    constexpr Vec4 operator/(f32 scalar) const noexcept {
        if (scalar == 0.0f) {
            return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
        }
        return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    constexpr Vec4& operator+=(const Vec4& other) noexcept { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
    constexpr Vec4& operator-=(const Vec4& other) noexcept { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
    constexpr Vec4& operator*=(f32 scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
    constexpr Vec4& operator/=(f32 scalar) noexcept {
        if (scalar != 0.0f) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
        }
        return *this;
    }

    friend constexpr Vec4 operator*(f32 scalar, const Vec4& vector) noexcept {
        return vector * scalar;
    }

    [[nodiscard]] constexpr f32 dot(const Vec4& other) const noexcept {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    [[nodiscard]] constexpr f32 lengthSquared() const noexcept {
        return dot(*this);
    }

    [[nodiscard]] constexpr f32 length() const noexcept {
        return std::sqrt(lengthSquared());
    }

    [[nodiscard]] constexpr bool tryNormalize(Vec4& out) const noexcept {
        const f32 len = length();
        if (!std::isfinite(len) || len <= Epsilon) {
            out = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
            return false;
        }
        out = *this / len;
        return true;
    }

    [[nodiscard]] constexpr Vec4 normalized() const noexcept {
        Vec4 out(0.0f, 0.0f, 0.0f, 0.0f);
        if (!tryNormalize(out)) {
            return out;
        }
        return out;
    }

    [[nodiscard]] constexpr bool isFinite() const noexcept {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w);
    }

    [[nodiscard]] constexpr Vec4 lerp(const Vec4& target, f32 t) const noexcept {
        return Vec4(ne::lerp(x, target.x, t), ne::lerp(y, target.y, t), ne::lerp(z, target.z, t), ne::lerp(w, target.w, t));
    }

    static constexpr Vec4 Zero() noexcept { return Vec4(0.0f, 0.0f, 0.0f, 0.0f); }
    static constexpr Vec4 One() noexcept { return Vec4(1.0f, 1.0f, 1.0f, 1.0f); }
};

} // namespace ne
