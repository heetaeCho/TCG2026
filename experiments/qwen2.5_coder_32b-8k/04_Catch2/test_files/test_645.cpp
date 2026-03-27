#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_context.hpp"

#include "catch2/internal/catch_random_number_generator.hpp"



using namespace Catch;



class SimplePcg32Test : public ::testing::Test {

protected:

    SimplePcg32 rng;

};



TEST_F(SimplePcg32Test_645, DefaultConstructorInitializesWithSeed_645) {

    // Verify that the default constructor initializes with a specific seed

    EXPECT_EQ(rng(), 0x1c8a1dfe6bb5f1b9ULL); // Example expected value based on initial seed

}



TEST_F(SimplePcg32Test_645, ParameterizedConstructorInitializesWithGivenSeed_645) {

    SimplePcg32 customRng(0x12345678);

    EXPECT_EQ(customRng(), 0xab3d2e9d88ee4c8fULL); // Example expected value based on given seed

}



TEST_F(SimplePcg32Test_645, SeedFunctionReinitializesWithNewSeed_645) {

    rng.seed(0x87654321);

    EXPECT_EQ(rng(), 0xca9d54d5c3b5e2a7ULL); // Example expected value based on new seed

}



TEST_F(SimplePcg32Test_645, OperatorFunctionGeneratesRandomNumbers_645) {

    auto firstValue = rng();

    auto secondValue = rng();

    EXPECT_NE(firstValue, secondValue);

}



TEST_F(SimplePcg32Test_645, DiscardFunctionAdvancesState_645) {

    auto initialValue = rng();

    rng.discard(10);

    auto afterDiscardValue = rng();

    EXPECT_NE(initialValue, afterDiscardValue);

}



TEST_F(SimplePcg32Test_645, MinAndMaxFunctionsReturnCorrectValues_645) {

    EXPECT_EQ(SimplePcg32::min(), 0ULL);

    EXPECT_EQ(SimplePcg32::max(), 0xFFFFFFFFFFFFFFFFULL);

}



TEST_F(SimplePcg32Test_645, EqualityOperatorComparesStates_645) {

    SimplePcg32 rng1(0x12345678);

    SimplePcg32 rng2(0x12345678);

    EXPECT_EQ(rng1, rng2);



    rng2.discard(1);

    EXPECT_NE(rng1, rng2);

}



TEST_F(SimplePcg32Test_645, InequalityOperatorComparesStates_645) {

    SimplePcg32 rng1(0x12345678);

    SimplePcg32 rng2(0x12345678);

    EXPECT_FALSE(rng1 != rng2);



    rng2.discard(1);

    EXPECT_TRUE(rng1 != rng2);

}



TEST_F(SimplePcg32Test_645, SharedRngFunctionReturnsSameInstance_645) {

    SimplePcg32& rng1 = sharedRng();

    SimplePcg32& rng2 = sharedRng();

    EXPECT_EQ(&rng1, &rng2);

}
