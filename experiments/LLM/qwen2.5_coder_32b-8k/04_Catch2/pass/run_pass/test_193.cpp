#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_quantifiers.cpp"



using namespace Catch::Matchers;



// Test fixture for AnyTrueMatcher tests

class AnyTrueMatcherTest_193 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if necessary

};



TEST_F(AnyTrueMatcherTest_193, Match_EmptyContainer_ReturnsFalse_193) {

    std::vector<bool> emptyContainer;

    AnyTrueMatcher matcher = AnyTrue();

    EXPECT_FALSE(matcher.match(emptyContainer));

}



TEST_F(AnyTrueMatcherTest_193, Match_AllFalseValues_ReturnsFalse_193) {

    std::vector<bool> allFalse{false, false, false};

    AnyTrueMatcher matcher = AnyTrue();

    EXPECT_FALSE(matcher.match(allFalse));

}



TEST_F(AnyTrueMatcherTest_193, Match_OneTrueValue_ReturnsTrue_193) {

    std::vector<bool> oneTrue{false, true, false};

    AnyTrueMatcher matcher = AnyTrue();

    EXPECT_TRUE(matcher.match(oneTrue));

}



TEST_F(AnyTrueMatcherTest_193, Match_AllTrueValues_ReturnsTrue_193) {

    std::vector<bool> allTrue{true, true, true};

    AnyTrueMatcher matcher = AnyTrue();

    EXPECT_TRUE(matcher.match(allTrue));

}



TEST_F(AnyTrueMatcherTest_193, Match_MixedValues_ReturnsTrue_193) {

    std::vector<bool> mixedValues{false, true, false, true};

    AnyTrueMatcher matcher = AnyTrue();

    EXPECT_TRUE(matcher.match(mixedValues));

}
