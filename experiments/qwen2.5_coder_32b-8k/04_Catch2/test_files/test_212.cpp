#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



class IsNaNMatcherTest : public ::testing::Test {

protected:

    IsNaNMatcher matcher;

};



TEST_F(IsNaNMatcherTest_212, MatchesNanValue_212) {

    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::quiet_NaN()));

}



TEST_F(IsNaNMatcherTest_212, DoesNotMatchNonNanValue_212) {

    EXPECT_FALSE(matcher.match(0.0));

}



TEST_F(IsNaNMatcherTest_212, MatchesSignalingNanValue_212) {

    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::signaling_NaN()));

}



TEST_F(IsNaNMatcherTest_212, DoesNotMatchInfinity_212) {

    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::infinity()));

}
