#include <gtest/gtest.h>

#include "catch2/internal/catch_random_number_generator.hpp"



using namespace Catch;



TEST_F(SimplePcg32Test_1096, ConstructorWithSeed_GeneratesCorrectInstance_1096) {

    SimplePcg32 rng(42);

}



TEST_F(SimplePcg32Test_1096, DefaultConstructor_SetsDefaultSeed_1096) {

    SimplePcg32 rng;

}



TEST_F(SimplePcg32Test_1096, SeedFunction_ChangesSeedCorrectly_1096) {

    SimplePcg32 rng(42);

    rng.seed(84);

}



TEST_F(SimplePcg32Test_1096, DiscardFunction_SkipsGivenNumberOfValues_1096) {

    SimplePcg32 rng;

    rng.discard(100);

}



TEST_F(SimplePcg32Test_1096, OperatorParenthesis_ReturnsRandomValueWithinRange_1096) {

    SimplePcg32 rng;

    result_type value = rng();

    EXPECT_GE(value, SimplePcg32::min());

    EXPECT_LE(value, SimplePcg32::max());

}



TEST_F(SimplePcg32Test_1096, OperatorEquality_ReturnsTrueForSameSeed_1096) {

    SimplePcg32 rng1(42);

    SimplePcg32 rng2(42);

    EXPECT_TRUE(rng1 == rng2);

}



TEST_F(SimplePcg32Test_1096, OperatorEquality_ReturnsFalseForDifferentSeeds_1096) {

    SimplePcg32 rng1(42);

    SimplePcg32 rng2(84);

    EXPECT_FALSE(rng1 == rng2);

}



TEST_F(SimplePcg32Test_1096, OperatorInequality_ReturnsFalseForSameSeed_1096) {

    SimplePcg32 rng1(42);

    SimplePcg32 rng2(42);

    EXPECT_FALSE(rng1 != rng2);

}



TEST_F(SimplePcg32Test_1096, OperatorInequality_ReturnsTrueForDifferentSeeds_1096) {

    SimplePcg32 rng1(42);

    SimplePcg32 rng2(84);

    EXPECT_TRUE(rng1 != rng2);

}



TEST_F(SimplePcg32Test_1096, MinFunction_ReturnsCorrectMinimumValue_1096) {

    EXPECT_EQ(SimplePcg32::min(), 0u);

}



TEST_F(SimplePcg32Test_1096, MaxFunction_ReturnsCorrectMaximumValue_1096) {

    EXPECT_EQ(SimplePcg32::max(), 0xFFFFFFFFFFFFFFFFu);

}
