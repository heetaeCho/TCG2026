// File: tests/random_integer_generator_tests_1060.cpp
#include <gtest/gtest.h>
#include <vector>
#include <cstdint>

// Include the header under test.
// Adjust the include path if your project layout differs.
#include "catch2/generators/catch_generators_random.hpp"

namespace {

using Catch::Generators::RandomIntegerGenerator;

// Simple alias to keep tests concise
template <typename Int>
using RIG = RandomIntegerGenerator<Int>;

class RandomIntegerGeneratorTest_1060 : public ::testing::Test {
protected:
    static constexpr std::uint32_t kSeed = 123456789u;
};

TEST_F(RandomIntegerGeneratorTest_1060, ConstructAndGetWithinRange_1060) {
    const int a = 1;
    const int b = 10;
    RIG<int> gen(a, b, kSeed);

    const int first = gen.get();
    EXPECT_GE(first, a);
    EXPECT_LE(first, b);
}

TEST_F(RandomIntegerGeneratorTest_1060, NextAdvancesAndStaysWithinRange_1060) {
    const int a = -50;
    const int b = 50;
    RIG<int> gen(a, b, kSeed);

    // After construction, get() is already initialized
    int prev = gen.get();
    EXPECT_GE(prev, a);
    EXPECT_LE(prev, b);

    // Call next() multiple times — should always return true and keep values in range
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(gen.next()) << "next() should indicate more values are available";
        const int v = gen.get();
        EXPECT_GE(v, a);
        EXPECT_LE(v, b);
    }
}

TEST_F(RandomIntegerGeneratorTest_1060, DeterministicWithSameSeed_1060) {
    const int a = 0;
    const int b = 1000;

    RIG<int> g1(a, b, kSeed);
    RIG<int> g2(a, b, kSeed);

    // Sequences from identical seeds and bounds should match value-for-value
    std::vector<int> seq1, seq2;
    seq1.reserve(64);
    seq2.reserve(64);

    // First value is established by constructor; record and then advance several times
    seq1.push_back(g1.get());
    seq2.push_back(g2.get());
    for (int i = 0; i < 63; ++i) {
        ASSERT_TRUE(g1.next());
        ASSERT_TRUE(g2.next());
        seq1.push_back(g1.get());
        seq2.push_back(g2.get());
    }

    EXPECT_EQ(seq1, seq2);
}

TEST_F(RandomIntegerGeneratorTest_1060, DegenerateRangeSingleValue_1060) {
    const int single = 42;
    RIG<int> gen(single, single, kSeed);

    // For a == b, the generator should always yield that single value
    for (int i = 0; i < 20; ++i) {
        const int v = gen.get();
        EXPECT_EQ(v, single);
        EXPECT_TRUE(gen.next()); // Random generator is conceptually unbounded
    }
}

TEST_F(RandomIntegerGeneratorTest_1060, WorksWithDifferentIntegerTypesAndNegativeRanges_1060) {
    // int64_t range with negatives
    const std::int64_t a = static_cast<std::int64_t>(-100000);
    const std::int64_t b = static_cast<std::int64_t>(-99900);

    RIG<std::int64_t> gen(a, b, kSeed);

    // Initial value is in range
    auto v = gen.get();
    EXPECT_GE(v, a);
    EXPECT_LE(v, b);

    // A few steps should remain in the same range
    for (int i = 0; i < 16; ++i) {
        EXPECT_TRUE(gen.next());
        v = gen.get();
        EXPECT_GE(v, a);
        EXPECT_LE(v, b);
    }
}

} // namespace
