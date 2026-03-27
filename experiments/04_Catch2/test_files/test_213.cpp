#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_predicate.hpp"



using namespace Catch::Matchers;

using ::testing::Eq;



class PredicateMatcherTest_213 : public ::testing::Test {

protected:

    using TestPredicate = std::function<bool(int)>;

};



TEST_F(PredicateMatcherTest_213, Match_ReturnsTrueForMatchingItem_213) {

    TestPredicate always_true = [](int) { return true; };

    PredicateMatcher<int, TestPredicate> matcher(always_true, "Always True");



    EXPECT_TRUE(matcher.match(42));

}



TEST_F(PredicateMatcherTest_213, Match_ReturnsFalseForNonMatchingItem_213) {

    TestPredicate always_false = [](int) { return false; };

    PredicateMatcher<int, TestPredicate> matcher(always_false, "Always False");



    EXPECT_FALSE(matcher.match(42));

}



TEST_F(PredicateMatcherTest_213, Match_BoundaryConditionZero_213) {

    TestPredicate is_zero = [](int i) { return i == 0; };

    PredicateMatcher<int, TestPredicate> matcher(is_zero, "Is Zero");



    EXPECT_TRUE(matcher.match(0));

}



TEST_F(PredicateMatcherTest_213, Match_BoundaryConditionNegative_213) {

    TestPredicate is_negative = [](int i) { return i < 0; };

    PredicateMatcher<int, TestPredicate> matcher(is_negative, "Is Negative");



    EXPECT_TRUE(matcher.match(-1));

}



TEST_F(PredicateMatcherTest_213, Match_BoundaryConditionPositive_213) {

    TestPredicate is_positive = [](int i) { return i > 0; };

    PredicateMatcher<int, TestPredicate> matcher(is_positive, "Is Positive");



    EXPECT_TRUE(matcher.match(1));

}



TEST_F(PredicateMatcherTest_213, Describe_ReturnsProvidedDescription_213) {

    std::string description = "Custom Description";

    TestPredicate always_true = [](int) { return true; };

    PredicateMatcher<int, TestPredicate> matcher(always_true, description);



    EXPECT_EQ(matcher.describe(), description);

}
