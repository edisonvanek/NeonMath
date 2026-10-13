#pragma once

#include <cmath>
#include <limits>
#include <type_traits>

#include <NeonMath/Constants.h>
#include <NeonMath/Types.h>

namespace ne {

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <Numeric T>
constexpr T radians(T degreesValue) noexcept {
    return degreesValue * static_cast<T>(Pi / 180.0);
}

template <Numeric T>
constexpr T degrees(T radiansValue) noexcept {
    return radiansValue * static_cast<T>(180.0 / Pi);
}

template <Numeric T>
constexpr T clamp(T value, T minValue, T maxValue) noexcept {
    if (value < minValue) {
        return minValue;
    }
    if (value > maxValue) {
        return maxValue;
    }
    return value;
}

template <Numeric T>
constexpr T saturate(T value) noexcept {
    return clamp(value, static_cast<T>(0), static_cast<T>(1));
}

template <Numeric T>
constexpr T lerp(T a, T b, T t) noexcept {
    return a + (b - a) * t;
}

template <Numeric T>
constexpr bool nearlyEqual(T a, T b, T epsilon = static_cast<T>(1.0e-6)) noexcept {
    const T diff = std::abs(a - b);
    return diff <= epsilon;
}

} // namespace ne
