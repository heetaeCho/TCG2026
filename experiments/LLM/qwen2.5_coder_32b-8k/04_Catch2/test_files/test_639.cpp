#include <gtest/gtest.h>

#include "catch_random_number_generator.hpp"



using namespace Catch;



// Test Fixture for SimplePcg32

class SimplePcg32Test_639 : public ::testing::Test {

protected:

    SimplePcg32 rng;

};



// Test normal operation of the seed function

TEST_F(SimplePcg32Test_639, SeedSetsStateCorrectly_639) {

    result_type initialSeed = 42;

    rng.seed(initialSeed);

    // Since we cannot access m_state directly, we rely on observable behavior.

    // We can check if the sequence of numbers generated changes with different seeds.

    result_type firstNumber = rng();

    rng.seed(84);

    result_type secondNumber = rng();

    EXPECT_NE(firstNumber, secondNumber);

}



// Test boundary conditions for the seed function

TEST_F(SimplePcg32Test_639, SeedWithMaxValue_639) {

    rng.seed(std::numeric_limits<result_type>::max());

    // Again, we rely on observable behavior.

    result_type number = rng();

    EXPECT_GE(number, SimplePcg32::min());

    EXPECT_LE(number, SimplePcg32::max());

}



// Test boundary conditions for the seed function

TEST_F(SimplePcg32Test_639, SeedWithZero_639) {

    rng.seed(0);

    result_type number = rng();

    EXPECT_GE(number, SimplePcg32::min());

    EXPECT_LE(number, SimplePcg32::max());

}



// Test the min and max static functions

TEST_F(SimplePcg32Test_639, MinAndMaxReturnCorrectValues_639) {

    result_type minValue = SimplePcg32::min();

    result_type maxValue = SimplePcg32::max();

    EXPECT_LE(minValue, maxValue);

}



// Test the operator() function for normal operation

TEST_F(SimplePcg32Test_639, OperatorGeneratesNumberInRange_639) {

    rng.seed(10);

    result_type number = rng();

    EXPECT_GE(number, SimplePcg32::min());

    EXPECT_LE(number, SimplePcg32::max());

}



// Test the discard function for normal operation

TEST_F(SimplePcg32Test_639, DiscardAdvancesState_639) {

    rng.seed(10);

    result_type firstNumber = rng();

    rng.discard(10);

    result_type secondNumber = rng();

    EXPECT_NE(firstNumber, secondNumber);

}



// Test the discard function with zero skips

TEST_F(SimplePcg32Test_639, DiscardWithZeroSkips_639) {

    rng.seed(10);

    result_type firstNumber = rng();

    rng.discard(0);

    result_type secondNumber = rng();

    EXPECT_EQ(firstNumber, secondNumber);

}



// Test the operator== function for normal operation

TEST_F(SimplePcg32Test_639, OperatorEqualSameSeed_639) {

    SimplePcg32 rng1;

    SimplePcg32 rng2;

    rng1.seed(5);

    rng2.seed(5);

    EXPECT_TRUE(rng1 == rng2);

}



// Test the operator!= function for normal operation

TEST_F(SimplePcg32Test_639, OperatorNotEqualDifferentSeeds_639) {

    SimplePcg32 rng1;

    SimplePcg32 rng2;

    rng1.seed(5);

    rng2.seed(10);

    EXPECT_TRUE(rng1 != rng2);

}
