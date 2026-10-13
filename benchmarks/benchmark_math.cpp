#include <benchmark/benchmark.h>

#include <NeonMath/NeonMath.h>

static void BM_Vec3Add(benchmark::State& state) {
    ne::Vec3 a(1.0f, 2.0f, 3.0f);
    ne::Vec3 b(4.0f, 5.0f, 6.0f);

    for (auto _ : state) {
        auto c = a + b;
        benchmark::DoNotOptimize(c);
    }
}

static void BM_Vec3Dot(benchmark::State& state) {
    ne::Vec3 a(1.0f, 2.0f, 3.0f);
    ne::Vec3 b(4.0f, 5.0f, 6.0f);

    for (auto _ : state) {
        auto d = a.dot(b);
        benchmark::DoNotOptimize(d);
    }
}

static void BM_Vec3Normalize(benchmark::State& state) {
    ne::Vec3 a(3.0f, 4.0f, 12.0f);

    for (auto _ : state) {
        auto n = a.normalized();
        benchmark::DoNotOptimize(n);
    }
}

BENCHMARK(BM_Vec3Add);
BENCHMARK(BM_Vec3Dot);
BENCHMARK(BM_Vec3Normalize);

BENCHMARK_MAIN();
