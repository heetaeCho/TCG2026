// File: tests/test_uniform_integer_distribution_1057.cpp

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include "Catch2/src/catch2/internal/catch_uniform_integer_distribution.hpp"

using Catch::uniform_integer_distribution;

// Simple URBG stub: external collaborator with deterministic outputs.
// It satisfies the UniformRandomBitGenerator requirements the distro expects.
struct StubGen {
    using result_type = uint32_t;

    explicit StubGen(std::initializer_list<result_type> seq)
        : data(seq), idx(0) {
        // Ensure there is at least one element to return
        if (data.size() == 0) {
            data.push_back(0u);
        }
    }

    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

    result_type operator()() {
        const result_type out = data[idx];
        idx = (idx + 1) % data.size();
        return out;
    }

    std::vector<result_type> data;
    size_t idx;
};

class UniformIntegerDistributionTest_1057 : public ::testing::Test {};

//
// Constructors & accessors
//
TEST_F(UniformIntegerDistributionTest_1057, AccessorsReturnCtorBounds_1057) {
    // Positive-only range
    uniform_integer_distribution<int> dist1(10, 25);
    EXPECT_EQ(dist1.a(), 10);
    EXPECT_EQ(dist1.b(), 25);

    // Negative-only range
    uniform_integer_distribution<int> dist2(-8, -3);
    EXPECT_EQ(dist2.a(), -8);
    EXPECT_EQ(dist2.b(), -3);

    // Mixed-sign range
    uniform_integer_distribution<int> dist3(-5, 7);
    EXPECT_EQ(dist3.a(), -5);
    EXPECT_EQ(dist3.b(), 7);
}

//
// Boundary: a == b must always yield that single value
//
TEST_F(UniformIntegerDistributionTest_1057, SingleValueRangeAlwaysReturnsBound_1057) {
    uniform_integer_distribution<int> dist(42, 42);
    StubGen gen{0u, std::numeric_limits<uint32_t>::max(), 123456789u, 1u};

    for (int i = 0; i < 20; ++i) {
        int v = dist(gen);
        EXPECT_EQ(v, 42) << "All draws must equal the single bound when a == b";
    }
}

//
// Observable behavior: all draws lie within [a, b] for various ranges
//
TEST_F(UniformIntegerDistributionTest_1057, DrawsStayWithinBounds_PositiveRange_1057) {
    uniform_integer_distribution<int> dist(10, 15);
    // Cycle through representative raw values across the URBG domain
    StubGen gen{
        0u,
        std::numeric_limits<uint32_t>::max(),
        std::numeric_limits<uint32_t>::max() / 2u,
        1u,
        (std::numeric_limits<uint32_t>::max() / 3u),
        (std::numeric_limits<uint32_t>::max() * 2u / 3u)
    };

    for (int i = 0; i < 60; ++i) {
        int v = dist(gen);
        EXPECT_LE(10, v);
        EXPECT_LE(v, 15);
    }
}

TEST_F(UniformIntegerDistributionTest_1057, DrawsStayWithinBounds_NegativeRange_1057) {
    uniform_integer_distribution<int> dist(-7, -3);
    StubGen gen{
        0u,
        std::numeric_limits<uint32_t>::max(),
        std::numeric_limits<uint32_t>::max() / 2u,
        123u,
        9999999u
    };

    for (int i = 0; i < 50; ++i) {
        int v = dist(gen);
        EXPECT_LE(-7, v);
        EXPECT_LE(v, -3);
    }
}

TEST_F(UniformIntegerDistributionTest_1057, DrawsStayWithinBounds_MixedSignRange_1057) {
    uniform_integer_distribution<int> dist(-5, 5);
    StubGen gen{
        0u,
        std::numeric_limits<uint32_t>::max(),
        1u,
        std::numeric_limits<uint32_t>::max() / 2u,
        (std::numeric_limits<uint32_t>::max() / 4u),
        (std::numeric_limits<uint32_t>::max() * 3u / 4u)
    };

    for (int i = 0; i < 60; ++i) {
        int v = dist(gen);
        EXPECT_LE(-5, v);
        EXPECT_LE(v, 5);
    }
}

//
// Type coverage: works for wider integer types
//
TEST_F(UniformIntegerDistributionTest_1057, SupportsDifferentIntegerTypes_1057) {
    // int64_t range crossing zero
    uniform_integer_distribution<long long> d1(-10000000000LL, 10000000000LL);
    StubGen gen{0u, 1u, std::numeric_limits<uint32_t>::max()};
    for (int i = 0; i < 30; ++i) {
        long long v = d1(gen);
        EXPECT_LE(-10000000000LL, v);
        EXPECT_LE(v, 10000000000LL);
    }

    // uint32_t positive range
    uniform_integer_distribution<uint32_t> d2(100u, 200u);
    for (int i = 0; i < 20; ++i) {
        uint32_t v = d2(gen);
        EXPECT_LE(100u, v);
        EXPECT_LE(v, 200u);
    }
}

//
// Error/exceptional case (observable via assert): a > b
// Only check in debug builds where assert is active.
//
#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
TEST_F(UniformIntegerDistributionTest_1057, DebugAssertsWhenALargerThanB_1057) {
    // Using a lambda to avoid unused-variable warnings in optimized builds.
    EXPECT_DEATH(
        []{
            volatile int a = 5;
            volatile int b = 4;
            uniform_integer_distribution<int> d(a, b);
            (void)d;
        }(),
        ""); // We don't assert on a specific message.
}
#endif
