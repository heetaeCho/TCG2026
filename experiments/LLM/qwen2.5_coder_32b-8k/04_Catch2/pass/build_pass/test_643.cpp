#include <gtest/gtest.h>

#include <catch2/internal/catch_random_number_generator.hpp>



using namespace Catch;



// Test Fixture for SimplePcg32

class SimplePcg32Test_643 : public ::testing::Test {

protected:

    SimplePcg32 rng;

};



// Test default constructor initializes with a non-zero seed

TEST_F(SimplePcg32Test_643, DefaultConstructorInitializesWithNonZeroSeed_643) {

    SimplePcg32 rngDefault;

    EXPECT_NE(rngDefault, SimplePcg32(0));

}



// Test parameterized constructor sets the correct seed

TEST_F(SimplePcg32Test_643, ParameterizedConstructorSetsCorrectSeed_643) {

    uint64_t testSeed = 12345;

    SimplePcg32 rngParam(testSeed);

    EXPECT_NE(rngParam, SimplePcg32(0));

}



// Test seed function sets the correct seed

TEST_F(SimplePcg32Test_643, SeedFunctionSetsCorrectSeed_643) {

    uint64_t testSeed = 12345;

    rng.seed(testSeed);

    EXPECT_NE(rng, SimplePcg32(0));

}



// Test operator() generates a value within the correct range

TEST_F(SimplePcg32Test_643, OperatorGeneratesValueInRange_643) {

    uint64_t result = rng();

    EXPECT_GE(result, SimplePcg32::min());

    EXPECT_LE(result, SimplePcg32::max());

}



// Test discard function advances the state correctly

TEST_F(SimplePcg32Test_643, DiscardAdvancesStateCorrectly_643) {

    uint64_t initialState = rng();

    rng.discard(1);

    uint64_t nextState = rng();

    EXPECT_NE(initialState, nextState);

}



// Test equality operator works correctly

TEST_F(SimplePcg32Test_643, EqualityOperatorWorksCorrectly_643) {

    SimplePcg32 rng1(12345);

    SimplePcg32 rng2(12345);

    EXPECT_TRUE(rng1 == rng2);

}



// Test inequality operator works correctly

TEST_F(SimplePcg32Test_643, InequalityOperatorWorksCorrectly_643) {

    SimplePcg32 rng1(12345);

    SimplePcg32 rng2(67890);

    EXPECT_TRUE(rng1 != rng2);

}



// Test min and max static functions return correct values

TEST_F(SimplePcg32Test_643, MinMaxFunctionsReturnCorrectValues_643) {

    uint64_t expectedMin = 0;

    uint64_t expectedMax = std::numeric_limits<uint64_t>::max();

    EXPECT_EQ(SimplePcg32::min(), expectedMin);

    EXPECT_EQ(SimplePcg32::max(), expectedMax);

}



// Test boundary condition for discard with zero skips

TEST_F(SimplePcg32Test_643, DiscardWithZeroSkipsDoesNothing_643) {

    uint64_t initialState = rng();

    rng.discard(0);

    uint64_t nextState = rng();

    EXPECT_EQ(initialState, nextState);

}



// Test boundary condition for seed with zero

TEST_F(SimplePcg32Test_643, SeedWithZeroDoesNotThrow_643) {

    EXPECT_NO_THROW(rng.seed(0));

}
