#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



TEST(IsNaNMatcherTest_210, Match_ReturnsTrueForNan_210) {

    IsNaNMatcher matcher;

    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::quiet_NaN()));

}



TEST(IsNaNMatcherTest_210, Match_ReturnsFalseForNonNan_210) {

    IsNaNMatcher matcher;

    EXPECT_FALSE(matcher.match(42.0));

}



TEST(IsNaNMatcherTest_210, Describe_ReturnsCorrectDescription_210) {

    IsNaNMatcher matcher;

    EXPECT_EQ(matcher.describe(), "is NaN");

}
