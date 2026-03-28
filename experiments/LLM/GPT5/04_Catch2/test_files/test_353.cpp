// File: random_floating_generator_test_353.cpp

#include <gtest/gtest.h>

#include <vector>
#include <limits>
#include <type_traits>

// Include the headers from the provided interface
// (adjust include paths to match your project layout)
#include "catch2/generators/catch_generators_random.hpp"

using Catch::Generators::RandomFloatingGenerator;

namespace {

// A small helper that pulls N values from a generator via next()+get().
template <typename T>
std::vector<T> PullValues(RandomFloatingGenerator<T>& gen, size_t n) {
    std::vector<T> out;
    out.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        // Observable behavior: next() should return whether it advanced.
        // We only assert "true" for a small fixed number of pulls so we don't
        // make assumptions about potential finiteness.
        ASSERT_TRUE(gen.next());
        out.push_back(gen.get());
    }
    return out;
}

} // namespace

// ========================
// Tests for float / double
// ========================

TEST(RandomFloatingGeneratorTest_353, FloatValuesStayWithinRange_353) {
    const float a = 0.0f;
    const float b = 1.0f;
    RandomFloatingGenerator<float> gen(a, b, /*seed*/123u);

    auto values = PullValues(gen, /*n*/100);
    for (float v : values) {
        EXPECT_GE(v, std::min(a, b));
        EXPECT_LE(v, std::max(a, b));
    }
}

TEST(RandomFloatingGeneratorTest_353, FloatDeterministicWithSameSeed_353) {
    const float a = -5.0f;
    const float b = 5.0f;
    constexpr uint32_t seed = 987654321u;

    RandomFloatingGenerator<float> gen1(a, b, seed);
    RandomFloatingGenerator<float> gen2(a, b, seed);

    // Pull a handful of values and ensure sequences match exactly.
    auto v1 = PullValues(gen1, /*n*/20);
    auto v2 = PullValues(gen2, /*n*/20);

    ASSERT_EQ(v1.size(), v2.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]);
    }
}

// =======================================
// Tests for the long double specialization
// =======================================

TEST(RandomFloatingGeneratorTest_353, LongDoubleValuesStayWithinRange_353) {
    const long double a = -1.25L;
    const long double b = 2.75L;
    RandomFloatingGenerator<long double> gen(a, b, /*seed*/42u);

    auto values = PullValues(gen, /*n*/64);
    for (long double v : values) {
        EXPECT_GE(v, std::min(a, b));
        EXPECT_LE(v, std::max(a, b));
    }
}

TEST(RandomFloatingGeneratorTest_353, LongDoubleDeterministicWithSameSeed_353) {
    const long double a = 10.0L;
    const long double b = 20.0L;
    constexpr uint32_t seed = 123456u;

    RandomFloatingGenerator<long double> gen1(a, b, seed);
    RandomFloatingGenerator<long double> gen2(a, b, seed);

    auto v1 = PullValues(gen1, /*n*/25);
    auto v2 = PullValues(gen2, /*n*/25);

    ASSERT_EQ(v1.size(), v2.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]);
    }
}

TEST(RandomFloatingGeneratorTest_353, LongDoubleConstantWhenBoundsEqual_353) {
    const long double c = 7.5L;
    RandomFloatingGenerator<long double> gen(c, c, /*seed*/1u);

    auto values = PullValues(gen, /*n*/10);
    for (long double v : values) {
        // Observable: when constructed with identical bounds, results are that bound.
        EXPECT_EQ(v, c);
    }
}

TEST(RandomFloatingGeneratorTest_353, LongDoubleNextReturnsTrueForMultipleAdvances_353) {
    RandomFloatingGenerator<long double> gen(0.0L, 1.0L, /*seed*/7u);

    // We only assert a handful of steps to avoid assumptions about infinity.
    for (int i = 0; i < 5; ++i) {
        EXPECT_TRUE(gen.next());
    }
}

TEST(RandomFloatingGeneratorTest_353, LongDoubleGetReturnsLastGeneratedValue_353) {
    RandomFloatingGenerator<long double> gen(-3.0L, 3.0L, /*seed*/9u);

    ASSERT_TRUE(gen.next());
    const long double first = gen.get();
    // Calling get() repeatedly without next() should not change the observed value.
    EXPECT_EQ(gen.get(), first);
    EXPECT_EQ(gen.get(), first);

    ASSERT_TRUE(gen.next());
    const long double second = gen.get();
    // After advancing, get() should now reflect the new current value.
    EXPECT_NE(second, first);
    EXPECT_EQ(gen.get(), second);
}
