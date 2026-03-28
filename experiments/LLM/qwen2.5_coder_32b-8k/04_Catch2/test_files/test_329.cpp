#include <gtest/gtest.h>

#include "catch_random_number_generator.hpp"



using namespace Catch;



TEST_F(SimplePcg32Test_329, DefaultConstructorInitializesWithSeed_329) {

    SimplePcg32 rng;

    // No direct way to verify internal state, but we can check if it generates a number

    EXPECT_GE(rng(), 0);

    EXPECT_LE(rng(), SimplePcg32::max());

}



TEST_F(SimplePcg32Test_329, SeedConstructorInitializesWithGivenSeed_329) {

    result_type seed = 12345;

    SimplePcg32 rng(seed);

    // No direct way to verify internal state, but we can check if it generates a number

    EXPECT_GE(rng(), 0);

    EXPECT_LE(rng(), SimplePcg32::max());

}



TEST_F(SimplePcg32Test_329, SeedFunctionResetsWithNewSeed_329) {

    SimplePcg32 rng;

    result_type initial = rng();

    rng.seed(54321);

    result_type after_seed = rng();

    EXPECT_NE(initial, after_seed); // Assuming new seed leads to different sequence

}



TEST_F(SimplePcg32Test_329, DiscardFunctionAdvancesSequence_329) {

    SimplePcg32 rng;

    result_type first = rng();

    rng.discard(10);

    result_type after_discard = rng();

    EXPECT_NE(first, after_discard); // Assuming discard advances the sequence

}



TEST_F(SimplePcg32Test_329, OperatorGeneratesWithinRange_329) {

    SimplePcg32 rng;

    for (int i = 0; i < 100; ++i) {

        result_type value = rng();

        EXPECT_GE(value, SimplePcg32::min());

        EXPECT_LE(value, SimplePcg32::max());

    }

}



TEST_F(SimplePcg32Test_329, MinAndMaxAreStaticConstants_329) {

    // Verify that min and max are static constants

    EXPECT_EQ(SimplePcg32::min(), 0);

    EXPECT_EQ(SimplePcg32::max(), static_cast<result_type>(-1));

}



TEST_F(SimplePcg32Test_329, EqualityOperatorComparesStates_329) {

    SimplePcg32 rng1(12345);

    SimplePcg32 rng2(12345);

    SimplePcg32 rng3(67890);



    EXPECT_TRUE(rng1 == rng2);  // Same seed, should be equal

    EXPECT_FALSE(rng1 == rng3); // Different seeds, should not be equal

}



TEST_F(SimplePcg32Test_329, InequalityOperatorComparesStates_329) {

    SimplePcg32 rng1(12345);

    SimplePcg32 rng2(12345);

    SimplePcg32 rng3(67890);



    EXPECT_FALSE(rng1 != rng2); // Same seed, should be equal

    EXPECT_TRUE(rng1 != rng3);  // Different seeds, should not be equal

}
