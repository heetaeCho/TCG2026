#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_approx.hpp"

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Matchers;



// Test Fixture for ApproxMatcher tests

class ApproxMatcherTest_973 : public ::testing::Test {

protected:

    std::vector<double> comparator;

    ApproxMatcher<double> matcher;



    void SetUp() override {

        comparator = {1.0, 2.0, 3.0};

        matcher = ApproxMatcher<double>(comparator);

    }

};



// Test normal operation with default margin

TEST_F(ApproxMatcherTest_973, MatchWithDefaultMargin_973) {

    std::vector<double> testVector = {1.0, 2.0, 3.0};

    EXPECT_TRUE(matcher.match(testVector));

}



// Test normal operation with custom margin

TEST_F(ApproxMatcherTest_973, MatchWithCustomMargin_973) {

    matcher.margin(0.5);

    std::vector<double> testVector = {1.1, 2.1, 3.1};

    EXPECT_TRUE(matcher.match(testVector));

}



// Test boundary condition with margin

TEST_F(ApproxMatcherTest_973, MatchBoundaryConditionWithMargin_973) {

    matcher.margin(0.1);

    std::vector<double> testVector = {1.1, 2.1, 3.1};

    EXPECT_FALSE(matcher.match(testVector));

}



// Test exceptional case with mismatched vector sizes

TEST_F(ApproxMatcherTest_973, MatchWithMismatchedSize_973) {

    std::vector<double> testVector = {1.0, 2.0};

    EXPECT_FALSE(matcher.match(testVector));

}



// Test describe function for ApproxMatcher

TEST_F(ApproxMatcherTest_973, DescribeFunction_973) {

    std::string description = matcher.describe();

    EXPECT_EQ(description, "is approximately equal to {1.0, 2.0, 3.0}");

}



// Test custom margin setting and matching

TEST_F(ApproxMatcherTest_973, CustomMarginSetting_973) {

    matcher.margin(0.5);

    std::vector<double> testVector = {1.6, 2.6, 3.6};

    EXPECT_TRUE(matcher.match(testVector));

}



// Test custom epsilon setting and matching

TEST_F(ApproxMatcherTest_973, CustomEpsilonSetting_973) {

    matcher.epsilon(0.5);

    std::vector<double> testVector = {1.5, 2.5, 3.5};

    EXPECT_TRUE(matcher.match(testVector));

}



// Test custom scale setting and matching

TEST_F(ApproxMatcherTest_973, CustomScaleSetting_973) {

    matcher.scale(2.0);

    std::vector<double> testVector = {2.0, 4.0, 6.0};

    EXPECT_TRUE(matcher.match(testVector));

}
