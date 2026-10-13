cmake_minimum_required(VERSION 3.25)

project(NeonMath
    VERSION 0.1.0
    DESCRIPTION "Cross-platform C++20 math library for game engines"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/NeonMathPlatform.cmake)

set(NEONMATH_PLATFORM "NATIVE"
    CACHE STRING
    "Target platform selection for NeonMath. Use NATIVE to auto-detect the host platform."
)
set_property(CACHE NEONMATH_PLATFORM PROPERTY STRINGS
    NATIVE
    WINDOWS
    LINUX
    MACOS
    ANDROID
    IOS
    WEB
)

neonmath_configure_platform()

option(NEONMATH_BUILD_TESTS "Build NeonMath tests" OFF)
option(NEONMATH_BUILD_BENCHMARKS "Build NeonMath benchmarks" OFF)
option(NEONMATH_BUILD_STATIC_LIB "Build an optional static library variant" OFF)

add_library(NeonMath INTERFACE)
add_library(NeonMath::NeonMath ALIAS NeonMath)

target_include_directories(NeonMath
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(NeonMath
    INTERFACE
        cxx_std_20
)

if(NEONMATH_TARGET_PLATFORM STREQUAL "WINDOWS")
    target_compile_definitions(NeonMath INTERFACE NEONMATH_PLATFORM_WINDOWS=1)
elseif(NEONMATH_TARGET_PLATFORM STREQUAL "LINUX")
    target_compile_definitions(NeonMath INTERFACE NEONMATH_PLATFORM_LINUX=1)
elseif(NEONMATH_TARGET_PLATFORM STREQUAL "MACOS")
    target_compile_definitions(NeonMath INTERFACE NEONMATH_PLATFORM_MACOS=1)
elseif(NEONMATH_TARGET_PLATFORM STREQUAL "ANDROID")
    target_compile_definitions(NeonMath INTERFACE NEONMATH_PLATFORM_ANDROID=1)
elseif(NEONMATH_TARGET_PLATFORM STREQUAL "IOS")
    target_compile_definitions(NeonMath INTERFACE NEONMATH_PLATFORM_IOS=1)
elseif(NEONMATH_TARGET_PLATFORM STREQUAL "WEB")
    target_compile_definitions(NeonMath INTERFACE NEONMATH_PLATFORM_WEB=1)
endif()

if(NEONMATH_BUILD_STATIC_LIB)
    add_library(NeonMathStatic STATIC src/NeonMath.cpp)
    add_library(NeonMath::NeonMathStatic ALIAS NeonMathStatic)
    target_link_libraries(NeonMathStatic PUBLIC NeonMath)
    target_compile_features(NeonMathStatic PUBLIC cxx_std_20)
endif()

if(NEONMATH_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(NEONMATH_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()
