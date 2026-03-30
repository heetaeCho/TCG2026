#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"



using namespace Catch::Matchers;



class AnyTrueMatcherTest_184 : public ::testing::Test {

protected:

    AnyTrueMatcher matcher;

};



TEST_F(AnyTrueMatcherTest_184, Match_ReturnsFalseForEmptyRange_184) {

    std::vector<bool> emptyRange;

    EXPECT_FALSE(matcher.match(emptyRange));

}



TEST_F(AnyTrueMatcherTest_184, Match_ReturnsFalseForAllFalseValues_184) {

    std::vector<bool> allFalse = {false, false, false};

    EXPECT_FALSE(matcher.match(allFalse));

}



TEST_F(AnyTrueMatcherTest_184, Match_ReturnsTrueForSingleTrueValue_184) {

    std::vector<bool> singleTrue = {true};

    EXPECT_TRUE(matcher.match(singleTrue));

}



TEST_F(AnyTrueMatcherTest_184, Match_ReturnsTrueForMultipleValuesWithOneTrue_184) {

    std::vector<bool> mixedValues = {false, true, false};

    EXPECT_TRUE(matcher.match(mixedValues));

}



TEST_F(AnyTrueMatcherTest_184, Match_ReturnsTrueForAllTrueValues_184) {

    std::vector<bool> allTrue = {true, true, true};

    EXPECT_TRUE(matcher.match(allTrue));

}
