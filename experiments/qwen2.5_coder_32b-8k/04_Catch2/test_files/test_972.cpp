#include <gtest/gtest.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Matchers;



// Test Fixture for ApproxMatcher

class ApproxMatcherTest_972 : public ::testing::Test {

protected:

    std::vector<double> comparator;

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher;



    void SetUp() override {

        comparator = {1.0, 2.0, 3.0};

        matcher = ApproxMatcher<double>(comparator);

    }

};



// Test normal operation

TEST_F(ApproxMatcherTest_972, Match_NormalOperation_972) {

    std::vector<double> test_vector = {1.0, 2.0, 3.0};

    EXPECT_TRUE(matcher.match(test_vector));

}



// Test boundary conditions with slight difference within epsilon

TEST_F(ApproxMatcherTest_972, Match_BoundaryConditionsWithinEpsilon_972) {

    matcher.epsilon(0.1);

    std::vector<double> test_vector = {1.05, 2.05, 3.05};

    EXPECT_TRUE(matcher.match(test_vector));

}



// Test boundary conditions with slight difference outside epsilon

TEST_F(ApproxMatcherTest_972, Match_BoundaryConditionsWithoutEpsilon_972) {

    matcher.epsilon(0.01);

    std::vector<double> test_vector = {1.05, 2.05, 3.05};

    EXPECT_FALSE(matcher.match(test_vector));

}



// Test exceptional or error cases with different vector sizes

TEST_F(ApproxMatcherTest_972, Match_ExceptionalCaseDifferentSizes_972) {

    std::vector<double> test_vector = {1.0, 2.0};

    EXPECT_FALSE(matcher.match(test_vector));

}



// Test setting margin and verifying its effect

TEST_F(ApproxMatcherTest_972, SetMargin_VerifyEffect_972) {

    matcher.margin(0.5);

    std::vector<double> test_vector = {1.6, 2.6, 3.6};

    EXPECT_TRUE(matcher.match(test_vector));

}



// Test setting scale and verifying its effect

TEST_F(ApproxMatcherTest_972, SetScale_VerifyEffect_972) {

    matcher.scale(0.5);

    std::vector<double> test_vector = {0.5, 1.0, 1.5};

    EXPECT_TRUE(matcher.match(test_vector));

}



// Test setting epsilon and verifying its effect

TEST_F(ApproxMatcherTest_972, SetEpsilon_VerifyEffect_972) {

    matcher.epsilon(0.05);

    std::vector<double> test_vector = {1.02, 2.02, 3.02};

    EXPECT_TRUE(matcher.match(test_vector));

}



// Test custom ApproxMatcher creation

TEST_F(ApproxMatcherTest_972, CustomApproxMatcherCreation_972) {

    auto custom_matcher = ApproxMatcher<double>::custom();

    std::vector<double> test_vector = {1.0, 2.0, 3.0};

    EXPECT_TRUE(custom_matcher.match(test_vector));

}
