#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



class WithinRelMatcherTest : public ::testing::Test {

protected:

    float target = 10.0f;

    float eps = 0.1f;

};



TEST_F(WithinRelMatcherTest_208, MatchEqualValue_208) {

    WithinRelMatcher matcher(target, eps);

    EXPECT_TRUE(matcher.match(target));

}



TEST_F(WithinRelMatcherTest_208, MatchWithinRange_208) {

    WithinRelMatcher matcher(target, eps);

    EXPECT_TRUE(matcher.match(target + target * eps));

    EXPECT_TRUE(matcher.match(target - target * eps));

}



TEST_F(WithinRelMatcherTest_208, NotMatchOutsideRange_208) {

    WithinRelMatcher matcher(target, eps);

    EXPECT_FALSE(matcher.match(target + target * (eps + 0.1f)));

    EXPECT_FALSE(matcher.match(target - target * (eps + 0.1f)));

}



TEST_F(WithinRelMatcherTest_208, MatchZeroTarget_208) {

    float zero_target = 0.0f;

    WithinRelMatcher matcher(zero_target, eps);

    EXPECT_TRUE(matcher.match(zero_target));

    EXPECT_TRUE(matcher.match(zero_target + eps)); // This might not be meaningful for relative error with zero

    EXPECT_TRUE(matcher.match(zero_target - eps)); // This might not be meaningful for relative error with zero

}



TEST_F(WithinRelMatcherTest_208, MatchLargeValue_208) {

    float large_target = 1e6f;

    WithinRelMatcher matcher(large_target, eps);

    EXPECT_TRUE(matcher.match(large_target + large_target * eps));

    EXPECT_TRUE(matcher.match(large_target - large_target * eps));

}



TEST_F(WithinRelMatcherTest_208, MatchSmallValue_208) {

    float small_target = 1e-6f;

    WithinRelMatcher matcher(small_target, eps);

    EXPECT_TRUE(matcher.match(small_target + small_target * eps));

    EXPECT_TRUE(matcher.match(small_target - small_target * eps));

}
