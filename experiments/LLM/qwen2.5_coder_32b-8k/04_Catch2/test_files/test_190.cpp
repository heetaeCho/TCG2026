#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



class NoneTrueMatcherTest_190 : public ::testing::Test {

protected:

    NoneTrueMatcher matcher;

};



TEST_F(NoneTrueMatcherTest_190, Describe_ReturnsCorrectDescription_190) {

    EXPECT_EQ(matcher.describe(), "contains no true");

}



TEST_F(NoneTrueMatcherTest_190, Match_EmptyContainer_ReturnsTrue_190) {

    std::vector<bool> emptyVector;

    EXPECT_TRUE(matcher.match(emptyVector));

}



TEST_F(NoneTrueMatcherTest_190, Match_AllFalseValues_ReturnsTrue_190) {

    std::vector<bool> falseVector = {false, false, false};

    EXPECT_TRUE(matcher.match(falseVector));

}



TEST_F(NoneTrueMatcherTest_190, Match_ContainsOneTrueValue_ReturnsFalse_190) {

    std::vector<bool> mixedVector = {false, true, false};

    EXPECT_FALSE(matcher.match(mixedVector));

}



TEST_F(NoneTrueMatcherTest_190, Match_AllTrueValues_ReturnsFalse_190) {

    std::vector<bool> trueVector = {true, true, true};

    EXPECT_FALSE(matcher.match(trueVector));

}
