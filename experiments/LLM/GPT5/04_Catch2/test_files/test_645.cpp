// File: tests/shared_rng_tests_645.cpp

#include <gtest/gtest.h>

// Headers under test
#include "catch2/internal/catch_context.cpp"                 // provides Catch::sharedRng()
#include "catch2/internal/catch_random_number_generator.hpp" // provides Catch::SimplePcg32

using Catch::sharedRng;
using Catch::SimplePcg32;

// A small helper fixture just for grouping; not required for state management.
class SharedRngTest_645 : public ::testing::Test {};

// [Behavior] sharedRng returns the same instance every time (singleton semantics).
TEST_F(SharedRngTest_645, ReturnsSameInstance_645) {
    SimplePcg32& a = sharedRng();
    SimplePcg32& b = sharedRng();
    EXPECT_EQ(&a, &b) << "sharedRng must return a reference to a single static instance";
}

// [Behavior] Seeding should reset the sequence deterministically for the same seed.
// This test avoids assuming exact values; it only checks that reseeding to the same seed
// reproduces the same *next* output.
TEST_F(SharedRngTest_645, ReseedingResetsNextOutput_645) {
    auto& rng = sharedRng();

    rng.seed(999u);
    auto first = rng(); // next value after seed=999

    rng.seed(999u);
    auto second = rng(); // should match the previous "first" if seeding resets sequence

    EXPECT_EQ(first, second) << "Reseeding to the same value should reproduce the same next output";
}

// [Behavior] Discard should advance the sequence equivalently to drawing and discarding values.
// We confirm by comparing:
//   v2 = rng(); rng();        (two draws)
//   rng.seed(S); rng.discard(1); v2_expected = rng();
// and asserting v2 == v2_expected.
TEST_F(SharedRngTest_645, DiscardAdvancesSequence_645) {
    auto& rng = sharedRng();

    // Establish two-step progression
    rng.seed(123u);
    (void)rng();                  // v1 (discarded)
    auto v2 = rng();              // keep for comparison

    // Now reproduce v2 using discard
    rng.seed(123u);
    rng.discard(1);               // skip v1
    auto v2_expected = rng();     // should match the earlier v2

    EXPECT_EQ(v2, v2_expected) << "discard(1) should advance the sequence by one draw";
}

// [Behavior] Generated values must lie within [min(), max()] as exposed by the interface.
TEST_F(SharedRngTest_645, GeneratedValuesWithinBounds_645) {
    auto& rng = sharedRng();

    rng.seed(2025u);
    auto val = rng();

    auto lo = SimplePcg32::min();
    auto hi = SimplePcg32::max();

    // Using ASSERTs first to avoid undefined comparisons if bounds were inverted.
    ASSERT_LE(lo, hi) << "min() should not exceed max()";
    EXPECT_GE(val, lo);
    EXPECT_LE(val, hi);
}

// [Behavior] Equality/inequality operators are reflexive for the same object reference.
// We do not assert anything about internal state—just that comparing an object to itself
// yields equality and not-inequality via the public operators.
TEST_F(SharedRngTest_645, EqualityIsReflexiveForSameObject_645) {
    auto& rng = sharedRng();
    // The header exposes operator==/!= taking two const SimplePcg32&.
    EXPECT_TRUE(operator==(rng, rng));
    EXPECT_FALSE(operator!=(rng, rng));
}
