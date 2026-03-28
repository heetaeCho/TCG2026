#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



class WithinRelMatcherTest : public ::testing::Test {

protected:

    WithinRelMatcher matcher;

    

    WithinRelMatcherTest() : matcher(1.0, 0.1) {}

};



TEST_F(WithinRelMatcherTest_201, Match_EqualValues_201) {

    EXPECT_TRUE(matcher.match(1.0));

}



TEST_F(WithinRelMatcherTest_201, Match_WithinRelativeMargin_201) {

    EXPECT_TRUE(matcher.match(1.1));

    EXPECT_TRUE(matcher.match(0.9));

}



TEST_F(WithinRelMatcherTest_201, Match_OutsideRelativeMargin_201) {

    EXPECT_FALSE(matcher.match(1.2));

    EXPECT_FALSE(matcher.match(0.8));

}



TEST_F(WithinRelMatcherTest_201, Match_ZeroTargetAndMatchee_201) {

    WithinRelMatcher zeroMatcher(0.0, 0.1);

    EXPECT_TRUE(zeroMatcher.match(0.0));

}



TEST_F(WithinRelMatcherTest_201, Match_ZeroEpsilon_201) {

    WithinRelMatcher zeroEpsilonMatcher(1.0, 0.0);

    EXPECT_TRUE(zeroEpsilonMatcher.match(1.0));

    EXPECT_FALSE(zeroEpsilonMatcher.match(1.1));

}



TEST_F(WithinRelMatcherTest_201, Match_NegativeValues_201) {

    WithinRelMatcher negativeMatcher(-1.0, 0.1);

    EXPECT_TRUE(negativeMatcher.match(-1.1));

    EXPECT_TRUE(negativeMatcher.match(-0.9));

}



TEST_F(WithinRelMatcherTest_201, Match_LargeEpsilon_201) {

    WithinRelMatcher largeEpsilonMatcher(1.0, 1.0);

    EXPECT_TRUE(largeEpsilonMatcher.match(2.0));

    EXPECT_TRUE(largeEpsilonMatcher.match(0.0));

}



TEST_F(WithinRelMatcherTest_201, Match_LargeValues_201) {

    WithinRelMatcher largeValueMatcher(1000.0, 0.1);

    EXPECT_TRUE(largeValueMatcher.match(1100.0));

    EXPECT_TRUE(largeValueMatcher.match(900.0));

}
