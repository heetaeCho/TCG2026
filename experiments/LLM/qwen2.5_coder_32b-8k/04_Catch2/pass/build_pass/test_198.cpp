#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



class WithinAbsMatcherTest_198 : public ::testing::Test {

protected:

    double target = 5.0;

    double margin = 0.1;

    WithinAbsMatcher matcher;



    WithinAbsMatcherTest_198() : matcher(target, margin) {}

};



TEST_F(WithinAbsMatcherTest_198, MatchWithinMargin_198) {

    EXPECT_TRUE(matcher.match(5.05));

}



TEST_F(WithinAbsMatcherTest_198, MatchOnTarget_198) {

    EXPECT_TRUE(matcher.match(5.0));

}



TEST_F(WithinAbsMatcherTest_198, MatchBelowMargin_198) {

    EXPECT_TRUE(matcher.match(4.95));

}



TEST_F(WithinAbsMatcherTest_198, NotMatchAboveMargin_198) {

    EXPECT_FALSE(matcher.match(5.11));

}



TEST_F(WithinAbsMatcherTest_198, NotMatchBelowMargin_198) {

    EXPECT_FALSE(matcher.match(4.89));

}



TEST_F(WithinAbsMatcherTest_198, DescribeCorrectly_198) {

    EXPECT_EQ("is within 0.1 of 5", matcher.describe());

}
