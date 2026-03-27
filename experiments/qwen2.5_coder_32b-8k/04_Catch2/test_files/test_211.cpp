#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



class IsNaNMatcherTest : public ::testing::Test {

protected:

    IsNaNMatcher matcher;

};



TEST_F(IsNaNMatcherTest_211, Match_NaN_ReturnsTrue_211) {

    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::quiet_NaN()));

}



TEST_F(IsNaNMatcherTest_211, Match_PositiveInfinity_ReturnsFalse_211) {

    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::infinity()));

}



TEST_F(IsNaNMatcherTest_211, Match_NegativeInfinity_ReturnsFalse_211) {

    EXPECT_FALSE(matcher.match(-std::numeric_limits<double>::infinity()));

}



TEST_F(IsNaNMatcherTest_211, Match_Zero_ReturnsFalse_211) {

    EXPECT_FALSE(matcher.match(0.0));

}



TEST_F(IsNaNMatcherTest_211, Match_NormalNumber_ReturnsFalse_211) {

    EXPECT_FALSE(matcher.match(42.42));

}



TEST_F(IsNaNMatcherTest_211, Describe_ReturnsCorrectString_211) {

    EXPECT_EQ(matcher.describe(), "is NaN");

}
