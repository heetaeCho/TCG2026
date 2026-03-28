#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_random_number_generator.hpp"



using namespace Catch;



class SimplePcg32Test : public ::testing::Test {

protected:

    SimplePcg32 rng;

};



TEST_F(SimplePcg32Test_640, DefaultConstructorInitializesWithDefaultSeed_640) {

    // Since we cannot directly verify the internal state, we rely on observable behavior.

    // We can check if two default-constructed instances produce the same sequence.

    SimplePcg32 rng1;

    EXPECT_EQ(rng(), rng1());

}



TEST_F(SimplePcg32Test_640, SeedConstructorInitializesWithProvidedSeed_640) {

    // Similar to the default constructor test, we check if two instances with the same seed produce the same sequence.

    uint64_t seed = 12345;

    SimplePcg32 rng1(seed);

    SimplePcg32 rng2(seed);

    EXPECT_EQ(rng1(), rng2());

}



TEST_F(SimplePcg32Test_640, SeedFunctionReinitializesWithNewSeed_640) {

    uint64_t seed1 = 12345;

    uint64_t seed2 = 67890;

    rng.seed(seed1);

    SimplePcg32 rng1(seed1);

    EXPECT_EQ(rng(), rng1());

    rng.seed(seed2);

    SimplePcg32 rng2(seed2);

    EXPECT_EQ(rng(), rng2());

}



TEST_F(SimplePcg32Test_640, DiscardSkipsCorrectNumberOfValues_640) {

    // We can check if discarding a certain number of values results in the generator skipping that many.

    uint64_t skip = 10;

    SimplePcg32 rng1;

    for (uint64_t i = 0; i < skip; ++i) {

        rng1();

    }

    rng.discard(skip);

    EXPECT_EQ(rng(), rng1());

}



TEST_F(SimplePcg32Test_640, DiscardWithZeroSkipsNoValues_640) {

    // Discarding zero values should not change the state.

    SimplePcg32 rng1 = rng;

    rng.discard(0);

    EXPECT_EQ(rng(), rng1());

}



TEST_F(SimplePcg32Test_640, OperatorEqualityComparesStateCorrectly_640) {

    // Two instances with the same seed should be equal.

    uint64_t seed = 12345;

    SimplePcg32 rng1(seed);

    EXPECT_EQ(rng1, rng);



    // Two instances with different seeds should not be equal.

    rng.seed(67890);

    EXPECT_NE(rng, rng1);

}



TEST_F(SimplePcg32Test_640, OperatorInequalityComparesStateCorrectly_640) {

    // Two instances with the same seed should not be unequal.

    uint64_t seed = 12345;

    SimplePcg32 rng1(seed);

    EXPECT_FALSE(rng1 != rng);



    // Two instances with different seeds should be unequal.

    rng.seed(67890);

    EXPECT_NE(rng, rng1);

}



TEST_F(SimplePcg32Test_640, MinFunctionReturnsCorrectMinimumValue_640) {

    // The minimum value of the generator can be compared against a known constant.

    EXPECT_EQ(SimplePcg32::min(), 0u);

}



TEST_F(SimplePcg32Test_640, MaxFunctionReturnsCorrectMaximumValue_640) {

    // The maximum value of the generator can be compared against a known constant.

    EXPECT_EQ(SimplePcg32::max(), UINT32_MAX);

}
