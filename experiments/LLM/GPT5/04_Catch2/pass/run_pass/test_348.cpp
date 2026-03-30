// random_floating_generator_test_348.cpp
#include <gtest/gtest.h>

// Include the header under test (path from the prompt)
#include "Catch2/src/catch2/generators/catch_generators_random.hpp"

using Catch::Generators::RandomFloatingGenerator;

// A tiny helper to collect a finite sequence without assuming infinite next().
template <typename Float>
static std::vector<Float> CollectSequence(RandomFloatingGenerator<Float>& gen, size_t max_count) {
    std::vector<Float> out;
    if (max_count == 0) return out;
    out.push_back(gen.get());
    for (size_t i = 1; i < max_count; ++i) {
        if (!gen.next()) break;
        out.push_back(gen.get());
    }
    return out;
}

class RandomFloatingGeneratorTest_348 : public ::testing::Test {};

// --- Normal operation: initial value is within [a, b] and subsequent values remain in range.
TEST_F(RandomFloatingGeneratorTest_348, ValuesStayWithinRange_348) {
    const double a = -3.5;
    const double b = 7.25;
    const uint32_t seed = 123456u;

    RandomFloatingGenerator<double> gen(a, b, seed);

    auto val0 = gen.get();
    EXPECT_GE(val0, std::min(a, b));
    EXPECT_LE(val0, std::max(a, b));

    // Advance a handful of times; each observed value must remain within range.
    for (int i = 0; i < 50; ++i) {
        // If next() ever reports no further values, stop — do not assume infinite length.
        if (i > 0 && !gen.next()) break;
        const double v = gen.get();
        EXPECT_GE(v, std::min(a, b));
        EXPECT_LE(v, std::max(a, b));
    }
}

// --- Boundary: zero-width range [a, a] must always yield 'a' (the only in-range value).
TEST_F(RandomFloatingGeneratorTest_348, ZeroWidthRange_AlwaysEqualsBound_348) {
    const float a = 2.0f;
    const uint32_t seed = 777u;

    RandomFloatingGenerator<float> gen(a, a, seed);

    // First value
    EXPECT_FLOAT_EQ(gen.get(), a);

    // A few steps; regardless of next() returning true/false, any produced values must equal a.
    for (int i = 0; i < 10; ++i) {
        if (i > 0 && !gen.next()) break;
        EXPECT_FLOAT_EQ(gen.get(), a);
    }
}

// --- Normal/negative ranges: supports ranges crossing zero (no assumptions about distribution).
TEST_F(RandomFloatingGeneratorTest_348, RangeCrossingZero_ValuesWithinBounds_348) {
    const long double lo = -10.0L;
    const long double hi = 0.5L;
    const uint32_t seed = 42u;

    RandomFloatingGenerator<long double> gen(lo, hi, seed);

    for (int i = 0; i < 25; ++i) {
        if (i > 0 && !gen.next()) break;
        const long double v = gen.get();
        EXPECT_LE(v, std::max(lo, hi));
        EXPECT_GE(v, std::min(lo, hi));
    }
}

// --- Determinism: same (a, b, seed) should produce the same observable sequence.
TEST_F(RandomFloatingGeneratorTest_348, SameSeedProducesSameSequence_348) {
    const double a = 0.0;
    const double b = 1.0;
    const uint32_t seed = 2024u;

    RandomFloatingGenerator<double> g1(a, b, seed);
    RandomFloatingGenerator<double> g2(a, b, seed);

    // Collect up to N values from each (stop early if next() returns false).
    constexpr size_t N = 64;
    auto s1 = CollectSequence(g1, N);
    auto s2 = CollectSequence(g2, N);

    ASSERT_EQ(s1.size(), s2.size());
    for (size_t i = 0; i < s1.size(); ++i) {
        // Use EXPECT_DOUBLE_EQ for bitwise-close equality on doubles.
        EXPECT_DOUBLE_EQ(s1[i], s2[i]) << "Mismatch at index " << i;
    }
}

// --- Type/overload check for long double: get() returns a const reference and value is in range.
TEST_F(RandomFloatingGeneratorTest_348, LongDoubleGetReturnsConstRefWithinRange_348) {
    const long double a = 1.25L;
    const long double b = 9.75L;
    const uint32_t seed = 11u;

    RandomFloatingGenerator<long double> gen(a, b, seed);

    // Verify the type is a const reference at compile time.
    static_assert(std::is_same<decltype(gen.get()), long double const&>::value,
                  "get() must return const reference to long double for the specialization");

    const long double& ref = gen.get();
    EXPECT_GE(ref, std::min(a, b));
    EXPECT_LE(ref, std::max(a, b));

    // After advancing (if possible), the reference value should still be within bounds.
    if (gen.next()) {
        const long double& ref2 = gen.get();
        EXPECT_GE(ref2, std::min(a, b));
        EXPECT_LE(ref2, std::max(a, b));
    }
}
