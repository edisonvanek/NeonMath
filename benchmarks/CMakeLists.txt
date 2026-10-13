include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.8.4
)

FetchContent_MakeAvailable(benchmark)

add_executable(NeonMathBenchmarks benchmark_math.cpp)
target_link_libraries(NeonMathBenchmarks PRIVATE NeonMath benchmark::benchmark)
