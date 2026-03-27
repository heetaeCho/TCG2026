#include <gtest/gtest.h>

#include <catch2/matchers/catch_matchers_floating_point.hpp>



using namespace Catch::Matchers;



TEST_F(WithinRelMatcherTest_207, NormalOperation_207) {

    WithinRelMatcher matcher = WithinRel(1.0);

    EXPECT_TRUE(matcher.match(1.0 + std::numeric_limits<double>::epsilon() * 50));

    EXPECT_FALSE(matcher.match(1.0 + std::numeric_limits<double>::epsilon() * 150));

}



TEST_F(WithinRelMatcherTest_207, BoundaryConditions_207) {

    WithinRelMatcher matcher = WithinRel(1.0);

    EXPECT_TRUE(matcher.match(1.0 + std::numeric_limits<double>::epsilon() * 100));

    EXPECT_FALSE(matcher.match(1.0 + std::numeric_limits<double>::epsilon() * 101));

}



TEST_F(WithinRelMatcherTest_207, ZeroTarget_207) {

    WithinRelMatcher matcher = WithinRel(0.0);

    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::epsilon() * 50));

    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::epsilon() * 150));

}



TEST_F(WithinRelMatcherTest_207, LargeTarget_207) {

    WithinRelMatcher matcher = WithinRel(1e9);

    EXPECT_TRUE(matcher.match(1e9 + std::numeric_limits<double>::epsilon() * 50 * 1e9));

    EXPECT_FALSE(matcher.match(1e9 + std::numeric_limits<double>::epsilon() * 150 * 1e9));

}



TEST_F(WithinRelMatcherTest_207, NegativeTarget_207) {

    WithinRelMatcher matcher = WithinRel(-1.0);

    EXPECT_TRUE(matcher.match(-1.0 - std::numeric_limits<double>::epsilon() * 50));

    EXPECT_FALSE(matcher.match(-1.0 - std::numeric_limits<double>::epsilon() * 150));

}
