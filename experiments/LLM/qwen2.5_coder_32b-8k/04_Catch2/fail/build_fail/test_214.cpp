#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch2/matchers/catch_matchers_predicate.hpp"



using namespace Catch::Matchers;

using ::testing::Eq;



// Mock predicate function for testing

bool mockPredicate(int value) {

    return value > 0;

}



class PredicateMatcherTest_214 : public ::testing::Test {

protected:

    void SetUp() override {

        positiveMatcher = std::make_unique<PredicateMatcher<int>>(mockPredicate, "is positive");

    }



    std::unique_ptr<PredicateMatcher<int>> positiveMatcher;

};



TEST_F(PredicateMatcherTest_214, DescribeReturnsCorrectDescription_214) {

    EXPECT_EQ(positiveMatcher->describe(), "is positive");

}



TEST_F(PredicateMatcherTest_214, MatchPositiveNumberReturnsTrue_214) {

    EXPECT_TRUE(positiveMatcher->match(5));

}



TEST_F(PredicateMatcherTest_214, MatchZeroReturnsFalse_214) {

    EXPECT_FALSE(positiveMatcher->match(0));

}



TEST_F(PredicateMatcherTest_214, MatchNegativeNumberReturnsFalse_214) {

    EXPECT_FALSE(positiveMatcher->match(-5));

}
