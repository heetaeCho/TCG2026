// random_integer_generator_tests_349.cpp
#include <gtest/gtest.h>
#include <vector>
#include <cstdint>

// Include the header under test
// Adjust the include path if your project structure differs.
#include "catch2/generators/catch_generators_random.hpp"

using Catch::Generators::RandomIntegerGenerator;

class RandomIntegerGeneratorTest_349 : public ::testing::Test {
protected:
    // Helper: collect N observable outputs without assuming internal mechanics.
    template <typename Int>
    static std::vector<Int> CollectN(RandomIntegerGenerator<Int>& gen, size_t N) {
        std::vector<Int> out;
        out.reserve(N);
        if (N == 0) return out;

        // First observed value (without advancing)
        out.push_back(gen.get());

        // Subsequent values: advance then observe
        for (size_t i = 1; i < N; ++i) {
            // We only assert true for a reasonable number of steps (no assumption of finiteness).
            ASSERT_TRUE(gen.next());
            out.push_back(gen.get());
        }
        return out;
    }
};

// --- Normal operation: get() returns value within [a, b] right after construction.
TEST_F(RandomIntegerGeneratorTest_349, GetWithinBoundsAfterConstruction_349) {
    const int a = -5, b = 7;
    const std::uint32_t seed = 123u;

    RandomIntegerGenerator<int> gen(a, b, seed);
    int first = gen.get();
    EXPECT_LE(first, b);
    EXPECT_GE(first, a);
}

// --- Normal operation: repeated next() keeps values within [a, b].
TEST_F(RandomIntegerGeneratorTest_349, NextKeepsValuesWithinBounds_349) {
    const int a = 10, b = 20;
    const std::uint32_t seed = 42u;

    RandomIntegerGenerator<int> gen(a, b, seed);

    // Check a few steps without assuming distribution specifics.
    const int steps = 100;
    for (int i = 0; i < steps; ++i) {
        int v = gen.get();
        EXPECT_GE(v, a);
        EXPECT_LE(v, b);
        ASSERT_TRUE(gen.next()); // Expect to be able to advance for many steps
    }
}

// --- Determinism: same seed + same bounds -> identical observable sequences.
TEST_F(RandomIntegerGeneratorTest_349, SameSeedProducesSameSequence_349) {
    const int a = 0, b = 100;
    const std::uint32_t seed = 20250828u;

    RandomIntegerGenerator<int> gen1(a, b, seed);
    RandomIntegerGenerator<int> gen2(a, b, seed);

    constexpr size_t N = 64;
    auto s1 = CollectN(gen1, N);
    auto s2 = CollectN(gen2, N);

    ASSERT_EQ(s1.size(), s2.size());
    for (size_t i = 0; i < s1.size(); ++i) {
        EXPECT_EQ(s1[i], s2[i]) << "Mismatch at index " << i;
    }
}

// --- Non-advancing get(): calling get() repeatedly without next() should not move the sequence.
TEST_F(RandomIntegerGeneratorTest_349, GetDoesNotAdvanceSequence_349) {
    const int a = -100, b = 100;
    const std::uint32_t seed = 777u;

    RandomIntegerGenerator<int> gen(a, b, seed);
    int v1 = gen.get();
    int v2 = gen.get();
    int v3 = gen.get();

    // All should be identical because we never called next()
    EXPECT_EQ(v1, v2);
    EXPECT_EQ(v2, v3);

    // After advancing once, value can change (but must still be in range).
    ASSERT_TRUE(gen.next());
    int v_after = gen.get();
    EXPECT_GE(v_after, a);
    EXPECT_LE(v_after, b);
    // We do not *require* change (to avoid flakiness), but it's allowed.
}

// --- Boundary condition: a == b -> generator must always yield that single value.
TEST_F(RandomIntegerGeneratorTest_349, EqualBoundsAlwaysYieldThatValue_349) {
    const int a = 5, b = 5; // equal bounds
    const std::uint32_t seed = 1u;

    RandomIntegerGenerator<int> gen(a, b, seed);

    constexpr int checks = 32;
    for (int i = 0; i < checks; ++i) {
        EXPECT_EQ(gen.get(), a);
        ASSERT_TRUE(gen.next()); // Should remain advanceable
    }
}

// --- Interface contract: next() returns true across multiple steps (no finite length assumed).
TEST_F(RandomIntegerGeneratorTest_349, NextReturnsTrueForManySteps_349) {
    const int a = 0, b = 10;
    const std::uint32_t seed = 9u;

    RandomIntegerGenerator<int> gen(a, b, seed);

    // Reasonable number of iterations to validate the observable contract.
    for (int i = 0; i < 256; ++i) {
        ASSERT_TRUE(gen.next());
    }
}
