// SimplePcg32_tests_642.cpp
#include <gtest/gtest.h>
#include <cstdint>
#include "catch2/internal/catch_random_number_generator.hpp"

using Catch::SimplePcg32;

class SimplePcg32Test_642 : public ::testing::Test {};

// --- Equality & inequality basics ---

TEST_F(SimplePcg32Test_642, DefaultConstructedEnginesAreEqual_642) {
    SimplePcg32 a;            // default seed per interface
    SimplePcg32 b;            // same default seed
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST_F(SimplePcg32Test_642, SameExplicitSeedProducesEqualEngines_642) {
    SimplePcg32 a;
    SimplePcg32 b;
    a.seed(123u);
    b.seed(123u);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST_F(SimplePcg32Test_642, DifferentSeedsProduceNonEqualEngines_642) {
    SimplePcg32 a;
    SimplePcg32 b;
    a.seed(123u);
    b.seed(456u);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}

TEST_F(SimplePcg32Test_642, AdvancingOneEngineBreaksEquality_642) {
    SimplePcg32 a;
    SimplePcg32 b;
    a.seed(42u);
    b.seed(42u);
    (void)a();                // advance state of one engine
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}

// --- discard() behavior via observable equivalence ---

TEST_F(SimplePcg32Test_642, DiscardZeroKeepsStateUnchanged_642) {
    SimplePcg32 a;
    SimplePcg32 b;
    a.seed(999u);
    b.seed(999u);
    a.discard(0);             // no-op skip
    EXPECT_TRUE(a == b);
}

TEST_F(SimplePcg32Test_642, DiscardMatchesRepeatedCalls_642) {
    SimplePcg32 a;
    SimplePcg32 b;
    a.seed(2024u);
    b.seed(2024u);

    constexpr uint64_t kSkip = 5;
    a.discard(kSkip);

    // Advance b by kSkip draws
    for (uint64_t i = 0; i < kSkip; ++i) {
        (void)b();
    }
    // After skipping/advancing equally, engines should be in the same state
    EXPECT_TRUE(a == b);
}

TEST_F(SimplePcg32Test_642, LargeDiscardStillDeterministicAndComparable_642) {
    SimplePcg32 a;
    SimplePcg32 b;
    a.seed(7u);
    b.seed(7u);

    constexpr uint64_t kSkip = 10000; // reasonably large but quick
    a.discard(kSkip);
    for (uint64_t i = 0; i < kSkip; ++i) {
        (void)b();
    }
    EXPECT_TRUE(a == b);
}

// --- Bounds & consistency ---

TEST_F(SimplePcg32Test_642, GeneratedValuesLieWithinMinMaxInclusive_642) {
    SimplePcg32 rng;
    rng.seed(314159u);

    // Use the engine's own result_type and min()/max()
    using result_t = decltype(rng());
    const result_t lo = SimplePcg32::min();
    const result_t hi = SimplePcg32::max();

    // Sample a bunch of times to verify bounds
    for (int i = 0; i < 1000; ++i) {
        result_t v = rng();
        EXPECT_LE(v, hi);
        EXPECT_GE(v, lo);
    }
}

TEST_F(SimplePcg32Test_642, ReseedingRestoresDeterministicState_642) {
    SimplePcg32 a;
    SimplePcg32 b;

    a.seed(111u);
    (void)a();                // disturb state
    a.seed(222u);             // reseed to a new, known state

    b.seed(222u);             // fresh engine with the same seed
    EXPECT_TRUE(a == b);      // states should now match again
}

TEST_F(SimplePcg32Test_642, InequalityIsLogicalNegationOfEquality_642) {
    SimplePcg32 a;
    SimplePcg32 b;

    a.seed(1u);
    b.seed(1u);
    EXPECT_EQ(a == b, !(a != b));

    (void)a(); // change a
    EXPECT_EQ(a == b, !(a != b));

    b.seed(2u); // change b via reseed
    EXPECT_EQ(a == b, !(a != b));
}
