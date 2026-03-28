#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



class WithinAbsMatcherTest_197 : public ::testing::Test {

protected:

    double target = 5.0;

    double margin = 0.1;

    WithinAbsMatcher matcher{target, margin};

};



TEST_F(WithinAbsMatcherTest_197, MatchWithinMargin_197) {

    EXPECT_TRUE(matcher.match(target + margin));

    EXPECT_TRUE(matcher.match(target - margin));

}



TEST_F(WithinAbsMatcherTest_197, MatchOnTarget_197) {

    EXPECT_TRUE(matcher.match(target));

}



TEST_F(WithinAbsMatcherTest_197, MatchOutsideMargin_197) {

    EXPECT_FALSE(matcher.match(target + margin * 2));

    EXPECT_FALSE(matcher.match(target - margin * 2));

}



TEST_F(WithinAbsMatcherTest_197, DescribeMatch_197) {

    std::string description = matcher.describe();

    EXPECT_EQ(description, "is within " + std::to_string(margin) + " of " + std::to_string(target));

}
