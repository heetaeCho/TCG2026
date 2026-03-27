#include <gtest/gtest.h>

#include "catch_random_number_generator.hpp"



using namespace Catch;



TEST_F(SimplePcg32Test_641, DefaultConstructorInitializesState_641) {

    SimplePcg32 rng;

    EXPECT_EQ(rng(), rng.min());

}



TEST_F(SimplePcg32Test_641, SeedConstructorSetsStateCorrectly_641) {

    uint64_t seed = 123456789;

    SimplePcg32 rng(seed);

    // Since we cannot inspect internal state, we check the first generated number

    EXPECT_NE(rng(), rng.min());

}



TEST_F(SimplePcg32Test_641, SeedMethodChangesState_641) {

    uint64_t seed = 987654321;

    SimplePcg32 rng(0);

    rng.seed(seed);

    // Since we cannot inspect internal state, we check the first generated number

    EXPECT_NE(rng(), rng.min());

}



TEST_F(SimplePcg32Test_641, DiscardSkipsCorrectNumberOfValues_641) {

    SimplePcg32 rng;

    uint64_t initial = rng();

    rng.discard(1);

    uint64_t afterDiscard = rng();

    EXPECT_NE(initial, afterDiscard);

}



TEST_F(SimplePcg32Test_641, MinMaxReturnCorrectValues_641) {

    SimplePcg32 rng;

    EXPECT_EQ(rng.min(), 0u);

    EXPECT_EQ(rng.max(), UINT32_MAX);

}



TEST_F(SimplePcg32Test_641, EqualityOperatorWorks_641) {

    SimplePcg32 rng1(12345);

    SimplePcg32 rng2(12345);

    SimplePcg32 rng3(54321);



    EXPECT_TRUE(rng1 == rng2);

    EXPECT_FALSE(rng1 == rng3);

}



TEST_F(SimplePcg32Test_641, InequalityOperatorWorks_641) {

    SimplePcg32 rng1(12345);

    SimplePcg32 rng2(12345);

    SimplePcg32 rng3(54321);



    EXPECT_FALSE(rng1 != rng2);

    EXPECT_TRUE(rng1 != rng3);

}



TEST_F(SimplePcg32Test_641, OperatorYieldsDifferentValuesOnConsecutiveCalls_641) {

    SimplePcg32 rng;

    uint32_t first = rng();

    uint32_t second = rng();

    EXPECT_NE(first, second);

}
