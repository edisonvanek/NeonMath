function(neonmath_configure_platform)
    set(NEONMATH_TARGET_PLATFORM "NATIVE" PARENT_SCOPE)

    if(NEONMATH_PLATFORM STREQUAL "NATIVE")
        if(WIN32)
            set(NEONMATH_TARGET_PLATFORM "WINDOWS" PARENT_SCOPE)
        elseif(APPLE)
            if(CMAKE_SYSTEM_NAME STREQUAL "iOS" OR CMAKE_OSX_SYSROOT MATCHES "iPhone")
                set(NEONMATH_TARGET_PLATFORM "IOS" PARENT_SCOPE)
            else()
                set(NEONMATH_TARGET_PLATFORM "MACOS" PARENT_SCOPE)
            endif()
        elseif(ANDROID)
            set(NEONMATH_TARGET_PLATFORM "ANDROID" PARENT_SCOPE)
        elseif(EMSCRIPTEN)
            set(NEONMATH_TARGET_PLATFORM "WEB" PARENT_SCOPE)
        elseif(UNIX)
            set(NEONMATH_TARGET_PLATFORM "LINUX" PARENT_SCOPE)
        else()
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=NATIVE could not determine a supported host platform. "
                "Please set NEONMATH_PLATFORM explicitly to WINDOWS, LINUX, MACOS, ANDROID, IOS, or WEB."
            )
        endif()
    else()
        set(NEONMATH_TARGET_PLATFORM "${NEONMATH_PLATFORM}" PARENT_SCOPE)
    endif()

    if(NEONMATH_TARGET_PLATFORM STREQUAL "WINDOWS")
        if(NOT CMAKE_SYSTEM_NAME STREQUAL "" AND NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=WINDOWS is incompatible with the active toolchain/system: "
                "CMAKE_SYSTEM_NAME='${CMAKE_SYSTEM_NAME}'. Use a Windows toolchain and build directory."
            )
        endif()
        if(NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC|Clang|GNU")
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=WINDOWS requires a Windows-compatible C++ toolchain; "
                "detected '${CMAKE_CXX_COMPILER_ID}'."
            )
        endif()
    elseif(NEONMATH_TARGET_PLATFORM STREQUAL "LINUX")
        if(NOT CMAKE_SYSTEM_NAME STREQUAL "" AND NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=LINUX is incompatible with the active toolchain/system: "
                "CMAKE_SYSTEM_NAME='${CMAKE_SYSTEM_NAME}'. Use a Linux toolchain."
            )
        endif()
        if(NOT UNIX OR APPLE)
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=LINUX requires a Linux target environment. "
                "Currently detected CMAKE_SYSTEM_NAME='${CMAKE_SYSTEM_NAME}'."
            )
        endif()
    elseif(NEONMATH_TARGET_PLATFORM STREQUAL "MACOS")
        if(NOT APPLE)
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=MACOS requires an Apple toolchain and macOS target. "
                "Detected CMAKE_SYSTEM_NAME='${CMAKE_SYSTEM_NAME}'."
            )
        endif()
        if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=MACOS is incompatible with iOS. "
                "For iOS, use NEONMATH_PLATFORM=IOS and an Apple iOS toolchain."
            )
        endif()
    elseif(NEONMATH_TARGET_PLATFORM STREQUAL "ANDROID")
        if(NOT ANDROID)
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=ANDROID requires an Android toolchain. "
                "Set CMAKE_TOOLCHAIN_FILE to the Android NDK toolchain and ensure ANDROID_NDK is configured."
            )
        endif()
        if(NOT DEFINED ANDROID_NDK)
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=ANDROID requires Android NDK configuration. "
                "Use the Android NDK toolchain file and set ANDROID_ABI / ANDROID_PLATFORM."
            )
        endif()
    elseif(NEONMATH_TARGET_PLATFORM STREQUAL "IOS")
        if(NOT APPLE)
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=IOS requires an Apple toolchain. "
                "Detected CMAKE_SYSTEM_NAME='${CMAKE_SYSTEM_NAME}'."
            )
        endif()
        if(NOT CMAKE_SYSTEM_NAME STREQUAL "iOS")
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=IOS requires iOS target configuration."
            )
        endif()
    elseif(NEONMATH_TARGET_PLATFORM STREQUAL "WEB")
        if(NOT EMSCRIPTEN)
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=WEB requires an Emscripten toolchain. "
                "Use emcmake or configure with an Emscripten compiler."
            )
        endif()
        if(NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
            message(FATAL_ERROR
                "NEONMATH_PLATFORM=WEB is incompatible with CMAKE_SYSTEM_NAME='${CMAKE_SYSTEM_NAME}'. "
                "Use the Emscripten toolchain."
            )
        endif()
    else()
        message(FATAL_ERROR
            "Unsupported NEONMATH_PLATFORM='${NEONMATH_PLATFORM}'. "
            "Allowed values: NATIVE, WINDOWS, LINUX, MACOS, ANDROID, IOS, WEB."
        )
    endif()

    message(STATUS "NeonMath target platform configured to: ${NEONMATH_TARGET_PLATFORM}")
endfunction()
