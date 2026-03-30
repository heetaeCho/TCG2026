#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch;

using namespace Catch::Matchers;



class ApproxMatcherTest_971 : public ::testing::Test {

protected:

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double> matcher;



    ApproxMatcherTest_971() : matcher(comparator) {}

};



TEST_F(ApproxMatcherTest_971, Match_ReturnsTrueForApproxEqualVectors_971) {

    std::vector<double> testVector = {1.001, 2.001, 3.001};

    EXPECT_TRUE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_971, Match_ReturnsFalseForNonApproxEqualVectors_971) {

    std::vector<double> testVector = {1.1, 2.1, 3.1};

    EXPECT_FALSE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_971, Describe_ReturnsCorrectDescription_971) {

    EXPECT_EQ(matcher.describe(), "is approx: is approximately (1, 2, 3)");

}



TEST_F(ApproxMatcherTest_971, Epsilon_SettingChangesEpsilonValue_971) {

    matcher.epsilon(0.05);

    std::vector<double> testVector = {1.06, 2.06, 3.06};

    EXPECT_FALSE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_971, Margin_SettingChangesMarginValue_971) {

    matcher.margin(0.5);

    std::vector<double> testVector = {1.6, 2.6, 3.6};

    EXPECT_TRUE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_971, Scale_SettingChangesScaleValue_971) {

    matcher.scale(0.5);

    std::vector<double> testVector = {0.5, 1.0, 1.5};

    EXPECT_TRUE(matcher.match(testVector));

}



TEST_F(ApproxMatcherTest_971, Match_BoundaryConditionsWithZeros_971) {

    ApproxMatcher<double> zeroMatcher({0.0, 0.0, 0.0});

    std::vector<double> testVector = {1e-12, 1e-12, 1e-12};

    EXPECT_TRUE(zeroMatcher.match(testVector));

}



TEST_F(ApproxMatcherTest_971, Match_BoundaryConditionsWithLargeNumbers_971) {

    ApproxMatcher<double> largeMatcher({1e9, 1e9, 1e9});

    std::vector<double> testVector = {1.001e9, 1.001e9, 1.001e9};

    EXPECT_TRUE(largeMatcher.match(testVector));

}



TEST_F(ApproxMatcherTest_971, Match_ExceptionalCaseWithNaN_971) {

    std::vector<double> testVector = {std::numeric_limits<double>::quiet_NaN(), 2.0, 3.0};

    EXPECT_FALSE(matcher.match(testVector));

}
