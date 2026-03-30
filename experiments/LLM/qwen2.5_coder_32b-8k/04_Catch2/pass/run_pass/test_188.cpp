#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



class AllTrueMatcherTest_188 : public ::testing::Test {

protected:

    AllTrueMatcher allTrueMatcher;

};



TEST_F(AllTrueMatcherTest_188, DescribeReturnsCorrectString_188) {

    EXPECT_EQ(allTrueMatcher.describe(), "contains only true");

}



TEST_F(AllTrueMatcherTest_188, MatchAllTrue_ReturnsTrue_188) {

    std::vector<bool> allTrue = {true, true, true};

    EXPECT_TRUE(allTrueMatcher.match(allTrue));

}



TEST_F(AllTrueMatcherTest_188, MatchMixedValues_ReturnsFalse_188) {

    std::vector<bool> mixedValues = {true, false, true};

    EXPECT_FALSE(allTrueMatcher.match(mixedValues));

}



TEST_F(AllTrueMatcherTest_188, MatchAllFalse_ReturnsFalse_188) {

    std::vector<bool> allFalse = {false, false, false};

    EXPECT_FALSE(allTrueMatcher.match(allFalse));

}



TEST_F(AllTrueMatcherTest_188, MatchEmptyRange_ReturnsTrue_188) {

    std::vector<bool> empty;

    EXPECT_TRUE(allTrueMatcher.match(empty));

}
