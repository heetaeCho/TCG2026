// File: tests/random_integer_generator_test.cpp

#include <gtest/gtest.h>

// Include the class under test from your codebase.
// Adjust the include path if your project structure differs.
#include "catch2/generators/catch_generators_random.hpp"

#include <climits>
#include <vector>

using Catch::Generators::RandomIntegerGenerator;

class RandomIntegerGeneratorTest_350 : public ::testing::Test {
protected:
    // Helper to pull N values from a generator via next()+get()
    static std::vector<int> CollectN(RandomIntegerGenerator<int>& gen, size_t n) {
        std::vector<int> out;
        out.reserve(n);
        for (size_t i = 0; i < n; ++i) {
            ASSERT_TRUE(gen.next());           // Observable contract from provided next() body
            out.push_back(gen.get());         // Observable: get() returns current value
        }
        return out;
    }
};

// [Normal] next() always returns true and get() is within [a, b]
TEST_F(RandomIntegerGeneratorTest_350, NextReturnsTrueAndValuesWithinBounds_350) {
    const int a = 5;
    const int b = 17;
    const uint32_t seed = 12345u;

    RandomIntegerGenerator<int> gen(a, b, seed);

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(gen.next());      // From the given implementation, next() returns true
        int v = gen.get();
        EXPECT_LE(a, v);
        EXPECT_LE(v, b);
    }
}

// [Boundary] a == b yields that single value every time
TEST_F(RandomIntegerGeneratorTest_350, SingleValueRangeAlwaysYieldsBound_350) {
    const int bound = 42;
    const uint32_t seed = 999u;

    RandomIntegerGenerator<int> gen(bound, bound, seed);

    for (int i = 0; i < 50; ++i) {
        ASSERT_TRUE(gen.next());
        EXPECT_EQ(bound, gen.get());
    }
}

// [Normal/Determinism] Same seed and bounds produce identical observable sequences
TEST_F(RandomIntegerGeneratorTest_350, SameSeedProducesIdenticalSequence_350) {
    const int a = -10;
    const int b = 10;
    const uint32_t seed = 777u;

    RandomIntegerGenerator<int> gen1(a, b, seed);
    RandomIntegerGenerator<int> gen2(a, b, seed);

    // Compare first 200 numbers
    for (int i = 0; i < 200; ++i) {
        ASSERT_TRUE(gen1.next());
        ASSERT_TRUE(gen2.next());
        EXPECT_EQ(gen1.get(), gen2.get());
    }
}

// [Boundary] Large (extreme) bounds keep values in range
TEST_F(RandomIntegerGeneratorTest_350, ValuesStayWithinExtremeIntRange_350) {
    const int a = INT_MIN;
    const int b = INT_MAX;
    const uint32_t seed = 13579u;

    RandomIntegerGenerator<int> gen(a, b, seed);

    // Pull a handful of values and assert they are within full int range
    for (int i = 0; i < 20; ++i) {
        ASSERT_TRUE(gen.next());
        int v = gen.get();
        // These are tautologically true for int, but assert the observable contract explicitly
        EXPECT_LE(a, v);
        EXPECT_LE(v, b);
    }
}

// [API/Reference] get() returns a const reference to the current value; without advancing,
// repeated get() calls should reference the same stored value.
TEST_F(RandomIntegerGeneratorTest_350, GetReferenceStableWithoutAdvance_350) {
    const int a = 0;
    const int b = 100;
    const uint32_t seed = 424242u;

    RandomIntegerGenerator<int> gen(a, b, seed);

    ASSERT_TRUE(gen.next());
    // Take the address of the referenced value and ensure it is stable if we don't advance.
    auto const* addr1 = &gen.get();
    int val1 = gen.get();

    // Multiple reads without calling next() should keep the same address and value.
    auto const* addr2 = &gen.get();
    int val2 = gen.get();

    EXPECT_EQ(addr1, addr2);
    EXPECT_EQ(val1, val2);
}

// [Smoke/Progress] Multiple next() calls keep succeeding and values keep updating observably
TEST_F(RandomIntegerGeneratorTest_350, MultipleAdvancesSucceedAndProduceSequence_350) {
    const int a = 1;
    const int b = 3;
    const uint32_t seed = 2024u;

    RandomIntegerGenerator<int> gen(a, b, seed);

    // Collect a small sequence; verify all in range and at least one change occurs
    int changes = 0;
    ASSERT_TRUE(gen.next());
    int prev = gen.get();
    EXPECT_LE(a, prev);
    EXPECT_LE(prev, b);

    for (int i = 0; i < 50; ++i) {
        ASSERT_TRUE(gen.next());
        int cur = gen.get();
        EXPECT_LE(a, cur);
        EXPECT_LE(cur, b);
        if (cur != prev) { ++changes; }
        prev = cur;
    }
    // In a small range there can be repeats, but across 51 draws we expect some variation.
    // This doesn't assume a specific RNG algorithm—just that the generator progresses.
    EXPECT_GT(changes, 0);
}
