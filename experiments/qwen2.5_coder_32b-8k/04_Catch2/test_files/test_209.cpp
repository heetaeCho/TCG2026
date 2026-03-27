#include <gtest/gtest.h>

#include <catch2/matchers/catch_matchers_floating_point.hpp>



using namespace Catch::Matchers;



// Fixture class for TEST_ID 209

class WithinRelMatcherTest_209 : public ::testing::Test {

protected:

    // Setup code, if needed, can go here

};



TEST_F(WithinRelMatcherTest_209, MatchesEqualValues_209) {

    float target = 1.0f;

    WithinRelMatcher matcher = WithinRel(target);

    EXPECT_TRUE(matcher.match(target));

}



TEST_F(WithinRelMatcherTest_209, MatchesWithinTolerance_209) {

    float target = 1.0f;

    WithinRelMatcher matcher = WithinRel(target);

    float value_within_tolerance = target + (std::numeric_limits<float>::epsilon() * 50);

    EXPECT_TRUE(matcher.match(value_within_tolerance));

}



TEST_F(WithinRelMatcherTest_209, DoesNotMatchOutsideTolerance_209) {

    float target = 1.0f;

    WithinRelMatcher matcher = WithinRel(target);

    float value_outside_tolerance = target + (std::numeric_limits<float>::epsilon() * 200);

    EXPECT_FALSE(matcher.match(value_outside_tolerance));

}



TEST_F(WithinRelMatcherTest_209, MatchesNegativeValuesWithinTolerance_209) {

    float target = -1.0f;

    WithinRelMatcher matcher = WithinRel(target);

    float value_within_tolerance = target - (std::numeric_limits<float>::epsilon() * 50);

    EXPECT_TRUE(matcher.match(value_within_tolerance));

}



TEST_F(WithinRelMatcherTest_209, MatchesZeroValue_209) {

    float target = 0.0f;

    WithinRelMatcher matcher = WithinRel(target);

    EXPECT_TRUE(matcher.match(0.0f + (std::numeric_limits<float>::epsilon() * 50)));

}



TEST_F(WithinRelMatcherTest_209, MatchesVerySmallValues_209) {

    float target = std::numeric_limits<float>::min();

    WithinRelMatcher matcher = WithinRel(target);

    EXPECT_TRUE(matcher.match(std::nextafterf(target, 1.0f)));

}



TEST_F(WithinRelMatcherTest_209, MatchesLargeValues_209) {

    float target = std::numeric_limits<float>::max();

    WithinRelMatcher matcher = WithinRel(target);

    EXPECT_TRUE(matcher.match(std::prevafterf(target, 0.0f)));

}
