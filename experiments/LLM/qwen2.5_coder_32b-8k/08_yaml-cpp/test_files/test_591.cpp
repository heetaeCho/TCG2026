#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"



class IsNegativeInfinityTest : public ::testing::Test {

protected:

    using namespace YAML::conversion;

};



TEST_F(IsNegativeInfinityTest_NormalOperation_591, ReturnsTrueForValidNegativeInfinityStrings_591) {

    EXPECT_TRUE(IsNegativeInfinity("-.inf"));

    EXPECT_TRUE(IsNegativeInfinity("-.Inf"));

    EXPECT_TRUE(IsNegativeInfinity("-.INF"));

}



TEST_F(IsNegativeInfinityTest_BoundaryConditions_591, ReturnsFalseForEmptyString_591) {

    EXPECT_FALSE(IsNegativeInfinity(""));

}



TEST_F(IsNegativeInfinityTest_BoundaryConditions_591, ReturnsFalseForSingleCharacterStrings_591) {

    EXPECT_FALSE(IsNegativeInfinity("-"));

    EXPECT_FALSE(IsNegativeInfinity("i"));

    EXPECT_FALSE(IsNegativeInfinity("."));

    EXPECT_FALSE(IsNegativeInfinity("f"));

    EXPECT_FALSE(IsNegativeInfinity("n"));

}



TEST_F(IsNegativeInfinityTest_ExceptionalCases_591, ReturnsFalseForSimilarButDifferentStrings_591) {

    EXPECT_FALSE(IsNegativeInfinity("-inf"));

    EXPECT_FALSE(IsNegativeInfinity("-Inf"));

    EXPECT_FALSE(IsNegativeInfinity("-INF"));

    EXPECT_FALSE(IsNegativeInfinity(".inf"));

    EXPECT_FALSE(IsNegativeInfinity(".Inf"));

    EXPECT_FALSE(IsNegativeInfinity(".INF"));

}



TEST_F(IsNegativeInfinityTest_ExceptionalCases_591, ReturnsFalseForArbitraryStrings_591) {

    EXPECT_FALSE(IsNegativeInfinity("random_string"));

    EXPECT_FALSE(IsNegativeInfinity("12345"));

    EXPECT_FALSE(IsNegativeInfinity("!@#$%"));

}
