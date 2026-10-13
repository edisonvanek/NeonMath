include(FetchContent)

option(NEONMATH_FETCH_CATCH2 "Fetch Catch2 for NeonMath tests" ON)

if(NEONMATH_FETCH_CATCH2)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.6.0
    )
    FetchContent_MakeAvailable(Catch2)
endif()

add_executable(NeonMathTests test_math.cpp)
target_link_libraries(NeonMathTests PRIVATE NeonMath Catch2::Catch2WithMain)

add_test(NAME NeonMathTests COMMAND NeonMathTests)
