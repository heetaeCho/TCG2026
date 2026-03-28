#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



TEST(WithinAbsMatcherTest_205, MatchesValueWithinMargin_205) {

    WithinAbsMatcher matcher = WithinAbs(10.0, 0.5);

    EXPECT_TRUE(matcher.match(9.7));

}



TEST(WithinAbsMatcherTest_205, DoesNotMatchValueOutsideMargin_205) {

    WithinAbsMatcher matcher = WithinAbs(10.0, 0.5);

    EXPECT_FALSE(matcher.match(10.6));

}



TEST(WithinAbsMatcherTest_205, MatchesExactTargetValue_205) {

    WithinAbsMatcher matcher = WithinAbs(10.0, 0.5);

    EXPECT_TRUE(matcher.match(10.0));

}



TEST(WithinAbsMatcherTest_205, HandlesNegativeValuesCorrectly_205) {

    WithinAbsMatcher matcher = WithinAbs(-10.0, 0.5);

    EXPECT_TRUE(matcher.match(-9.7));

}



TEST(WithinAbsMatcherTest_205, MatchesValueOnLowerBoundary_205) {

    WithinAbsMatcher matcher = WithinAbs(10.0, 0.5);

    EXPECT_TRUE(matcher.match(9.5));

}



TEST(WithinAbsMatcherTest_205, MatchesValueOnUpperBoundary_205) {

    WithinAbsMatcher matcher = WithinAbs(10.0, 0.5);

    EXPECT_TRUE(matcher.match(10.5));

}



TEST(WithinAbsMatcherTest_205, ZeroMarginMatchesExactValueOnly_205) {

    WithinAbsMatcher matcher = WithinAbs(10.0, 0.0);

    EXPECT_TRUE(matcher.match(10.0));

    EXPECT_FALSE(matcher.match(9.999999));

}
