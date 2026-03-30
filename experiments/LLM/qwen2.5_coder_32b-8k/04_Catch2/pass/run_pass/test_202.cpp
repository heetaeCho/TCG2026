#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include "catch2/internal/catch_reusable_string_stream.hpp"



using namespace Catch::Matchers;



class WithinRelMatcherTest_202 : public ::testing::Test {

protected:

    double target = 1.0;

    double epsilon = 0.1;

    WithinRelMatcher matcher;



    WithinRelMatcherTest_202() : matcher(target, epsilon) {}

};



TEST_F(WithinRelMatcherTest_202, MatchWithinRange_202) {

    EXPECT_TRUE(matcher.match(1.05));

}



TEST_F(WithinRelMatcherTest_202, MatchLowerBound_202) {

    EXPECT_TRUE(matcher.match(0.9));

}



TEST_F(WithinRelMatcherTest_202, MatchUpperBound_202) {

    EXPECT_TRUE(matcher.match(1.1));

}



TEST_F(WithinRelMatcherTest_202, MatchOutsideRangeLower_202) {

    EXPECT_FALSE(matcher.match(0.89));

}



TEST_F(WithinRelMatcherTest_202, MatchOutsideRangeUpper_202) {

    EXPECT_FALSE(matcher.match(1.11));

}



TEST_F(WithinRelMatcherTest_202, DescribeOutputCorrectly_202) {

    EXPECT_EQ(matcher.describe(), "and 1 are within 10% of each other");

}
