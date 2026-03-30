#include <gtest/gtest.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Matchers;



class ApproxMatcherTest_974 : public ::testing::Test {

protected:

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double> matcher = ApproxMatcher<double>(comparator);

};



TEST_F(ApproxMatcherTest_974, MatchWithDefaultTolerance_974) {

    std::vector<double> testVector = {1.0, 2.0, 3.0};

    EXPECT_TRUE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_974, MatchWithSmallDifferenceWithinEpsilon_974) {

    std::vector<double> testVector = {1.001, 2.001, 3.001};

    EXPECT_TRUE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_974, MatchWithLargeDifferenceOutsideEpsilon_974) {

    std::vector<double> testVector = {1.1, 2.1, 3.1};

    EXPECT_FALSE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_974, SetNewScaleAffectsMatching_974) {

    matcher.scale(0.5);

    std::vector<double> testVector = {1.5, 2.5, 3.5};

    EXPECT_TRUE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_974, SetNewEpsilonAffectsMatching_974) {

    matcher.epsilon(0.01);

    std::vector<double> testVector = {1.02, 2.02, 3.02};

    EXPECT_TRUE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_974, SetNewMarginAffectsMatching_974) {

    matcher.margin(0.1);

    std::vector<double> testVector = {1.1, 2.1, 3.1};

    EXPECT_TRUE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_974, DescribeReturnsExpectedString_974) {

    std::string description = matcher.describe();

    EXPECT_EQ(description, "is approximately {1, 2, 3}");

}
