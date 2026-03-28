#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



class AnyTrueMatcherTest_192 : public ::testing::Test {

protected:

    AnyTrueMatcher matcher;

};



TEST_F(AnyTrueMatcherTest_192, Describe_ReturnsCorrectDescription_192) {

    EXPECT_EQ(matcher.describe(), "contains at least one true");

}



TEST_F(AnyTrueMatcherTest_192, Match_EmptyContainer_ReturnsFalse_192) {

    std::vector<bool> empty;

    EXPECT_FALSE(matcher.match(empty));

}



TEST_F(AnyTrueMatcherTest_192, Match_AllFalse_ReturnsFalse_192) {

    std::vector<bool> all_false = {false, false, false};

    EXPECT_FALSE(matcher.match(all_false));

}



TEST_F(AnyTrueMatcherTest_192, Match_SomeTrue_ReturnsTrue_192) {

    std::vector<bool> some_true = {false, true, false};

    EXPECT_TRUE(matcher.match(some_true));

}



TEST_F(AnyTrueMatcherTest_192, Match_AllTrue_ReturnsTrue_192) {

    std::vector<bool> all_true = {true, true, true};

    EXPECT_TRUE(matcher.match(all_true));

}



TEST_F(AnyTrueMatcherTest_192, Match_SingleFalse_ReturnsFalse_192) {

    std::vector<bool> single_false = {false};

    EXPECT_FALSE(matcher.match(single_false));

}



TEST_F(AnyTrueMatcherTest_192, Match_SingleTrue_ReturnsTrue_192) {

    std::vector<bool> single_true = {true};

    EXPECT_TRUE(matcher.match(single_true));

}
