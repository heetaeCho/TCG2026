#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Matchers;

using ::testing::ElementsAre;



TEST(ApproxMatcherTest_970, Match_ReturnsTrueForEqualVectors_970) {

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    std::vector<double> testVector = {1.0, 2.0, 3.0};



    EXPECT_TRUE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsFalseForDifferentVectors_970) {

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    std::vector<double> testVector = {1.1, 2.1, 3.1};



    EXPECT_FALSE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsTrueForApproximateValuesWithinEpsilon_970) {

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    matcher.epsilon(0.1);

    std::vector<double> testVector = {1.05, 2.05, 3.05};



    EXPECT_TRUE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsFalseForApproximateValuesOutsideEpsilon_970) {

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    matcher.epsilon(0.05);

    std::vector<double> testVector = {1.1, 2.1, 3.1};



    EXPECT_FALSE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsTrueForApproximateValuesWithinMargin_970) {

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    matcher.margin(0.1);

    std::vector<double> testVector = {1.05, 2.05, 3.05};



    EXPECT_TRUE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsFalseForApproximateValuesOutsideMargin_970) {

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    matcher.margin(0.05);

    std::vector<double> testVector = {1.1, 2.1, 3.1};



    EXPECT_FALSE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsTrueForApproximateValuesWithinScale_970) {

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    matcher.scale(0.1);

    std::vector<double> testVector = {1.1, 2.2, 3.3};



    EXPECT_TRUE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsFalseForApproximateValuesOutsideScale_970) {

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    matcher.scale(0.05);

    std::vector<double> testVector = {1.6, 3.2, 4.8};



    EXPECT_FALSE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsFalseForDifferentSizeVectors_970) {

    std::vector<double> comparator = {1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    std::vector<double> testVector = {1.0, 2.0};



    EXPECT_FALSE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsTrueForEmptyVectors_970) {

    std::vector<double> comparator;

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    std::vector<double> testVector;



    EXPECT_TRUE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsTrueForSingleElementVectors_970) {

    std::vector<double> comparator = {1.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    std::vector<double> testVector = {1.0};



    EXPECT_TRUE(matcher.match(testVector));

}



TEST(ApproxMatcherTest_970, Match_ReturnsFalseForSingleElementVectorsDifferentValues_970) {

    std::vector<double> comparator = {1.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> matcher(comparator);

    std::vector<double> testVector = {2.0};



    EXPECT_FALSE(matcher.match(testVector));

}
