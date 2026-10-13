# NeonMath

NeonMath is a lightweight, dependency-free C++20 math library designed for game-engine and graphics workloads. It provides a stable public API for 2D/3D/4D vector math, scalar utilities, and constants without requiring engine-specific dependencies.

The library is intentionally header-first and platform-neutral. It is designed for:
- C++20 consumers
- Windows, Linux, macOS, Android, iOS, and WebAssembly
- engine integration without hard dependencies on platform SDKs
- future SIMD backends behind a stable API

## Project structure

```text
NeonMath/
├── CMakeLists.txt
├── CMakePresets.json
├── README.md
├── LICENSE
├── .gitignore
├── include/
│   └── NeonMath/
│       ├── NeonMath.h
│       ├── Config.h
│       ├── Types.h
│       ├── Constants.h
│       └── Math/
│           ├── Vec2.h
│           ├── Vec3.h
│           ├── Vec4.h
│           └── MathUtils.h
├── src/
│   └── NeonMath.cpp
├── tests/
│   ├── CMakeLists.txt
│   └── test_math.cpp
├── benchmarks/
│   ├── CMakeLists.txt
│   └── benchmark_math.cpp
├── cmake/
│   └── NeonMathPlatform.cmake
└── build/
```

## Requirements

- CMake 3.25+
- C++20 compiler
- MSVC, Clang, or GCC for native builds
- Android NDK for Android
- Apple toolchain and SDK for iOS/macOS
- Emscripten for WebAssembly

## Platform selection

The project exposes a single CMake cache variable:

```bash
-DNEONMATH_PLATFORM=<NATIVE|WINDOWS|LINUX|MACOS|ANDROID|IOS|WEB>
```

Important:
- `NATIVE` auto-detects the current host platform.
- `WINDOWS`, `LINUX`, `MACOS`, `ANDROID`, `IOS`, and `WEB` define the target platform contract.
- The platform selection is separate from the active toolchain/compiler.
- Use a fresh build directory whenever the toolchain or SDK changes.

Examples:

```bash
cmake -S . -B build/windows -DNEONMATH_PLATFORM=WINDOWS
cmake -S . -B build/linux -DNEONMATH_PLATFORM=LINUX
cmake -S . -B build/macos -DNEONMATH_PLATFORM=MACOS

cmake -S . -B build/android \
  -DNEONMATH_PLATFORM=ANDROID \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_PLATFORM=android-24

cmake -S . -B build/ios \
  -DNEONMATH_PLATFORM=IOS \
  -DCMAKE_SYSTEM_NAME=iOS \
  -DCMAKE_OSX_ARCHITECTURES=arm64

emcmake cmake -S . -B build/web -DNEONMATH_PLATFORM=WEB
```

## Build and test

Native Linux example:

```bash
cmake -S . -B build/linux -DNEONMATH_PLATFORM=LINUX -DNEONMATH_BUILD_TESTS=ON
cmake --build build/linux --config Release
ctest --test-dir build/linux --output-on-failure
```

Windows example:

```powershell
cmake -S . -B build\windows -DNEONMATH_PLATFORM=WINDOWS -DNEONMATH_BUILD_TESTS=ON
cmake --build build\windows --config Release
ctest --test-dir build\windows --output-on-failure
```

When testing availability is limited, the library still builds without external dependencies. Catch2 is fetched only when `NEONMATH_BUILD_TESTS=ON`.

## Benchmarks

Benchmarks are disabled by default. Enable them with:

```bash
cmake -S . -B build/benchmarks -DNEONMATH_BUILD_BENCHMARKS=ON
cmake --build build/benchmarks --config Release
./build/benchmarks/NeonMathBenchmarks
```

## Consumer integration example

```cmake
cmake_minimum_required(VERSION 3.25)
project(MyApp LANGUAGES CXX)

add_executable(MyApp main.cpp)
find_package(NeonMath CONFIG REQUIRED)
target_link_libraries(MyApp PRIVATE NeonMath::NeonMath)
```

Or if you are building as part of the same source tree:

```cmake
add_subdirectory(NeonMath)
add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE NeonMath::NeonMath)
```

## Basic usage

```cpp
#include <NeonMath/NeonMath.h>

int main() {
    ne::Vec3 a(1.0f, 2.0f, 3.0f);
    ne::Vec3 b(0.0f, 1.0f, 4.0f);

    ne::Vec3 c = a + b;
    float dot = a.dot(b);
    float length = c.length();

    ne::Vec3 n = c.normalized();
    ne::Vec3 cross = a.cross(b);

    ne::Vec2 v2(3.0f, 4.0f);
    ne::Vec2 n2 = v2.normalized();
    float l2 = n2.length();

    ne::Vec4 q(1.0f, 2.0f, 3.0f, 4.0f);
    ne::Vec4 q2 = q * 0.5f;

    float deg = ne::degrees(ne::Pi);
    float rad = ne::radians(180.0f);

    return (dot > 0.0f && length > 0.0f && q2.x >= 0.0f && rad > 0.0f) ? 0 : 1;
}
```

## Current limitations and future work

- No automatic SIMD selection is implemented yet.
- Header-first API is intentionally minimal and stable.
- Static library variant is optional and not required for the core math API.
- Cross-platform presets are documented but not all toolchains/SDKs are guaranteed to be installed in every developer environment.
- Future work includes:
  - platform-specific SIMD backends
  - more math primitives
  - matrix math
  - quaternion support
  - more rigorous benchmark and profiling coverage

## License

This project is distributed under the MIT License. See LICENSE for details.
