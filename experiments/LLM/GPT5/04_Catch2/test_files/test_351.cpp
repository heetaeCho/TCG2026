// File: random_integer_generator_tests_351.cpp

#include <gtest/gtest.h>

// Include the interface under test
// Adjust include path to match your project layout.
#include "catch2/generators/catch_generators_random.hpp"

using Catch::Generators::GeneratorWrapper;

namespace {

// Helper: take N observable values from a generator strictly via its interface.
template <typename T>
std::vector<T> TakeN(GeneratorWrapper<T>& gen, size_t n) {
    std::vector<T> out;
    out.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        out.push_back(gen.get());
        // We don't assert on the return value of next(); we just exercise it as an observable step.
        // The generator may be conceptually infinite; we keep iterations bounded here.
        (void)gen.next();
    }
    return out;
}

} // namespace

// ---------- Normal operation ----------

TEST(RandomIntegerGeneratorTest_351, ValuesWithinRange_Int_351) {
    const int a = 1, b = 6;
    auto gen = Catch::Generators::random<int>(a, b);

    // Sample several times; each observed value must be within [a, b].
    constexpr size_t kSamples = 200;
    for (size_t i = 0; i < kSamples; ++i) {
        int v = gen.get();
        EXPECT_GE(v, a);
        EXPECT_LE(v, b);
        (void)gen.next();
    }
}

TEST(RandomIntegerGeneratorTest_351, ValuesWithinRange_Unsigned_351) {
    const unsigned a = 0u, b = 3u;
    auto gen = Catch::Generators::random<unsigned>(a, b);

    constexpr size_t kSamples = 100;
    for (size_t i = 0; i < kSamples; ++i) {
        unsigned v = gen.get();
        EXPECT_GE(v, a);
        EXPECT_LE(v, b);
        (void)gen.next();
    }
}

// ---------- Boundary conditions ----------

TEST(RandomIntegerGeneratorTest_351, ClosedInterval_IncludesNegativeBounds_351) {
    const long long a = -10;
    const long long b = -1;
    auto gen = Catch::Generators::random<long long>(a, b);

    constexpr size_t kSamples = 128;
    for (size_t i = 0; i < kSamples; ++i) {
        long long v = gen.get();
        EXPECT_GE(v, a);
        EXPECT_LE(v, b);
        (void)gen.next();
    }
}

TEST(RandomIntegerGeneratorTest_351, DegenerateInterval_aEqualsb_351) {
    const int a = 42;
    auto gen = Catch::Generators::random<int>(a, a);

    // All observed values must be exactly 'a'
    constexpr size_t kSamples = 16;
    for (size_t i = 0; i < kSamples; ++i) {
        EXPECT_EQ(gen.get(), a);
        (void)gen.next();
    }
}

TEST(RandomIntegerGeneratorTest_351, WideButSafeRange_351) {
    // Use a wide range without risking overflow in client assertions.
    const int a = std::numeric_limits<int>::min() / 2;
    const int b = std::numeric_limits<int>::max() / 2;
    auto gen = Catch::Generators::random<int>(a, b);

    constexpr size_t kSamples = 64;
    for (size_t i = 0; i < kSamples; ++i) {
        int v = gen.get();
        EXPECT_GE(v, a);
        EXPECT_LE(v, b);
        (void)gen.next();
    }
}

// ---------- Exceptional / error cases (observable via interface) ----------

TEST(RandomIntegerGeneratorTest_351, ThrowsWhenMinGreaterThanMax_351) {
    // Construction should report an error observably (by throwing) when a > b.
    // We don't assume a specific exception type here.
    EXPECT_ANY_THROW({
        auto bad = Catch::Generators::random<int>(5, 1);
        (void)bad;
    });
}

// ---------- Type coverage (still via interface) ----------

TEST(RandomIntegerGeneratorTest_351, WorksWithDifferentIntegralTypes_351) {
    // Signed short
    {
        short a = static_cast<short>(-3);
        short b = static_cast<short>(2);
        auto gen = Catch::Generators::random<short>(a, b);
        auto sample = gen.get();
        EXPECT_GE(sample, a);
        EXPECT_LE(sample, b);
    }
    // Unsigned long long
    {
        unsigned long long a = 100ULL, b = 1000ULL;
        auto gen = Catch::Generators::random<unsigned long long>(a, b);
        auto sample = gen.get();
        EXPECT_GE(sample, a);
        EXPECT_LE(sample, b);
    }
}

// ---------- Basic progression (observable interaction via next()) ----------

TEST(RandomIntegerGeneratorTest_351, NextProgressesSequence_351) {
    const int a = 10, b = 20;
    auto gen = Catch::Generators::random<int>(a, b);

    // Take a small sequence and verify each value remains within [a, b].
    // We do NOT assert on uniqueness or randomness—only on observable bounds.
    auto values = TakeN(gen, 8);
    for (int v : values) {
        EXPECT_GE(v, a);
        EXPECT_LE(v, b);
    }
}
