#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include "catch2/matchers/catch_matchers.hpp"



using namespace Catch::Matchers;



class WithinAbsMatcherTest : public ::testing::Test {

protected:

    double target = 10.0;

    double margin = 0.5;

};



TEST_F(WithinAbsMatcherTest, MatchWithinMargin_1049) {

    WithinAbsMatcher matcher(target, margin);

    EXPECT_TRUE(matcher.match(10.3));

}



TEST_F(WithinAbsMatcherTest, MatchOnBoundary_1049) {

    WithinAbsMatcher matcher(target, margin);

    EXPECT_TRUE(matcher.match(9.5));

    EXPECT_TRUE(matcher.match(10.5));

}



TEST_F(WithinAbsMatcherTest, MatchOutsideMargin_1049) {

    WithinAbsMatcher matcher(target, margin);

    EXPECT_FALSE(matcher.match(9.4));

    EXPECT_FALSE(matcher.match(10.6));

}



TEST_F(WithinAbsMatcherTest, DescribeOutput_1049) {

    WithinAbsMatcher matcher(target, margin);

    std::string description = matcher.describe();

    EXPECT_EQ(description, "is within 0.5 of 10");

}



TEST_F(WithinAbsMatcherTest, NegativeMarginThrows_1049) {

    EXPECT_THROW(WithinAbsMatcher matcher(target, -0.1), Catch::EnforceException);

}
