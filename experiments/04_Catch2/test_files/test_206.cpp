#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



TEST(WithinRelMatcherTest_206, NormalOperation_206) {

    WithinRelMatcher matcher = WithinRel(1.0, 0.1);

    EXPECT_TRUE(matcher.match(1.05));

    EXPECT_FALSE(matcher.match(1.15));

}



TEST(WithinRelMatcherTest_206, BoundaryConditions_206) {

    WithinRelMatcher matcher = WithinRel(1.0, 0.1);

    EXPECT_TRUE(matcher.match(1.1));   // Upper boundary

    EXPECT_TRUE(matcher.match(0.9));   // Lower boundary

    EXPECT_FALSE(matcher.match(1.1001)); // Slightly above upper boundary

    EXPECT_FALSE(matcher.match(0.8999)); // Slightly below lower boundary

}



TEST(WithinRelMatcherTest_206, ZeroTarget_206) {

    WithinRelMatcher matcher = WithinRel(0.0, 0.1);

    EXPECT_TRUE(matcher.match(0.1));

    EXPECT_TRUE(matcher.match(-0.1));

    EXPECT_FALSE(matcher.match(0.1001));

    EXPECT_FALSE(matcher.match(-0.1001));

}



TEST(WithinRelMatcherTest_206, NegativeTarget_206) {

    WithinRelMatcher matcher = WithinRel(-1.0, 0.1);

    EXPECT_TRUE(matcher.match(-1.05));

    EXPECT_FALSE(matcher.match(-1.15));

    EXPECT_TRUE(matcher.match(-0.9));   // Lower boundary

    EXPECT_TRUE(matcher.match(-1.1));   // Upper boundary

}



TEST(WithinRelMatcherTest_206, ZeroEpsilon_206) {

    WithinRelMatcher matcher = WithinRel(1.0, 0.0);

    EXPECT_TRUE(matcher.match(1.0));

    EXPECT_FALSE(matcher.match(1.0001));

    EXPECT_FALSE(matcher.match(0.9999));

}



TEST(WithinRelMatcherTest_206, LargeEpsilon_206) {

    WithinRelMatcher matcher = WithinRel(1.0, 1.0);

    EXPECT_TRUE(matcher.match(2.0));   // Upper boundary

    EXPECT_TRUE(matcher.match(0.0));   // Lower boundary

}



TEST(WithinRelMatcherTest_206, NegativeEpsilon_206) {

    WithinRelMatcher matcher = WithinRel(1.0, -0.1);

    EXPECT_THROW(WithinRelMatcher(-1.0, -0.1), std::invalid_argument); // Negative epsilon should be invalid

}
