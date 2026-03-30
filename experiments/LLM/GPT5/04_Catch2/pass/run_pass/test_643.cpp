// simple_pcg32_operator_neq_tests_643.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_random_number_generator.hpp"

// All tests must end with _643 per requirement.

TEST(SimplePcg32Test_643, DefaultConstructorsAreEqualInitially_643) {
    Catch::SimplePcg32 a;
    Catch::SimplePcg32 b;

    // Two default-constructed generators should start in the same state.
    ASSERT_FALSE(a != b);
}

TEST(SimplePcg32Test_643, DifferentSeedsProduceNotEqual_643) {
    Catch::SimplePcg32 a;
    Catch::SimplePcg32 b;

    a.seed(123u);
    b.seed(456u);

    EXPECT_TRUE(a != b);
}

TEST(SimplePcg32Test_643, SameSeedSameAdvancesRemainEqual_643) {
    Catch::SimplePcg32 a;
    Catch::SimplePcg32 b;

    const uint32_t seed = 0xCAFEBABEu;
    a.seed(seed);
    b.seed(seed);

    // Advance both identically using operator() and discard.
    (void)a(); (void)b();
    a.discard(10);
    b.discard(10);

    ASSERT_FALSE(a != b); // i.e., equal
}

TEST(SimplePcg32Test_643, AdvancingOneStepMakesNotEqual_643) {
    Catch::SimplePcg32 a;
    Catch::SimplePcg32 b;

    a.seed(777u);
    b.seed(777u);

    // Advance only 'a' by one step.
    (void)a();

    EXPECT_TRUE(a != b);
}

TEST(SimplePcg32Test_643, DiscardZeroDoesNotChangeState_643) {
    Catch::SimplePcg32 a;
    Catch::SimplePcg32 b;

    a.seed(42u);
    b.seed(42u);

    // Discarding zero steps should leave state unchanged.
    a.discard(0);
    b.discard(0);

    ASSERT_FALSE(a != b);
}

TEST(SimplePcg32Test_643, MatchingDiscardsResynchronizeStates_643) {
    Catch::SimplePcg32 a;
    Catch::SimplePcg32 b;

    a.seed(99u);
    b.seed(99u);

    // Desynchronize: advance 'a' by one call.
    (void)a();
    ASSERT_TRUE(a != b);

    // Resynchronize by discarding one step on 'b'.
    b.discard(1);

    ASSERT_FALSE(a != b);
}

TEST(SimplePcg32Test_643, LargeSkipKeepsContractObservable_643) {
    Catch::SimplePcg32 a;
    Catch::SimplePcg32 b;

    a.seed(1u);
    b.seed(1u);

    // Apply a large but valid skip to one, then the same to the other.
    const uint64_t bigSkip = 1ULL << 20; // Large number of steps
    a.discard(bigSkip);

    EXPECT_TRUE(a != b);   // States must differ after advancing only 'a'.

    b.discard(bigSkip);

    // After applying the same advancement to 'b', states should match again.
    ASSERT_FALSE(a != b);
}
