// SimplePcg32_discard_tests_640.cpp
#include <gtest/gtest.h>
#include <cstdint>
#include "catch2/internal/catch_random_number_generator.hpp"

using Catch::SimplePcg32;

class SimplePcg32Test_640 : public ::testing::Test {
protected:
    // Returns the value produced after skipping `skip` draws manually.
    // This never inspects internal state; it only uses the public operator().
    static auto ManualAdvanceThenDraw(SimplePcg32 rng, uint64_t skip) {
        for (uint64_t i = 0; i < skip; ++i) {
            (void)rng(); // advance and ignore
        }
        return rng(); // the next value after `skip` advances
    }
};

// Normal operation: discard(0) does not change the next output.
TEST_F(SimplePcg32Test_640, DiscardZero_NoChange_640) {
    SimplePcg32 a;                 // default-seeded RNG
    SimplePcg32 b;                 // same default seed

    b.discard(0);                  // no-op by contract
    auto a_first = a();
    auto b_first = b();

    EXPECT_EQ(a_first, b_first);
}

// Normal operation: discard(1) advances by exactly one draw.
TEST_F(SimplePcg32Test_640, DiscardOne_AdvancesByOne_640) {
    SimplePcg32 base;              // default seed
    SimplePcg32 with_discard = base;

    // Value expected after discarding one = second value from the base stream
    auto expected = ManualAdvanceThenDraw(base, /*skip=*/1);

    with_discard.discard(1);
    auto actual = with_discard();

    EXPECT_EQ(actual, expected);
}

// Boundary-ish: discard(k) matches k manual operator() calls for small k.
TEST_F(SimplePcg32Test_640, DiscardSmallK_MatchesManualAdvance_640) {
    SimplePcg32 base;
    SimplePcg32 with_discard = base;

    const uint64_t k = 5; // small multi-step advance
    auto expected = ManualAdvanceThenDraw(base, k);

    with_discard.discard(k);
    auto actual = with_discard();

    EXPECT_EQ(actual, expected);
}

// Larger skip: ensure discard(k) matches manual advance for larger k.
TEST_F(SimplePcg32Test_640, DiscardLargeK_MatchesManualAdvance_640) {
    SimplePcg32 base;
    SimplePcg32 with_discard = base;

    const uint64_t k = 1234; // reasonably large but still quick for a unit test
    auto expected = ManualAdvanceThenDraw(base, k);

    with_discard.discard(k);
    auto actual = with_discard();

    EXPECT_EQ(actual, expected);
}

// Composability: consecutive discards sum to the same effect as a single discard with the sum.
TEST_F(SimplePcg32Test_640, ConsecutiveDiscards_EqualsSingleDiscard_640) {
    SimplePcg32 a; // baseline
    SimplePcg32 b = a;

    const uint64_t k1 = 17;
    const uint64_t k2 = 29;

    // One-shot discard of k1 + k2
    a.discard(k1 + k2);
    auto one_shot_next = a();

    // Two-step discards of k1 then k2
    b.discard(k1);
    b.discard(k2);
    auto two_step_next = b();

    EXPECT_EQ(one_shot_next, two_step_next);
}

// Independence: discarding on one instance must not affect another instance with the same seed.
TEST_F(SimplePcg32Test_640, DiscardDoesNotAffectOtherInstances_640) {
    SimplePcg32 a; // both default seeded -> initially identical streams
    SimplePcg32 b;

    // Discard only on 'a'
    const uint64_t k = 42;
    a.discard(k);

    // Now compare the (k+1)-th value from 'b' with the next from 'a'
    auto expected_from_b = ManualAdvanceThenDraw(b, k);
    auto next_from_a     = a();

    EXPECT_EQ(next_from_a, expected_from_b);
}
