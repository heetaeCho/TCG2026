#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_string.hpp"



using namespace Catch::Matchers;



class StringEqualsMatcherTest : public ::testing::Test {

protected:

    CasedString casedStr;

    StringEqualsMatcher matcher;



    void SetUp() override {

        casedStr = CasedString("test", CaseSensitive::Yes);

        matcher = StringEqualsMatcher(casedStr);

    }

};



TEST_F(StringEqualsMatcherTest_219, MatchReturnsTrueForEqualStrings_219) {

    EXPECT_TRUE(matcher.match("test"));

}



TEST_F(StringEqualsMatcherTest_219, MatchReturnsFalseForDifferentStrings_219) {

    EXPECT_FALSE(matcher.match("different"));

}



TEST_F(StringEqualsMatcherTest_219, MatchIsCaseSensitive_219) {

    EXPECT_FALSE(matcher.match("TEST"));

}



TEST_F(StringEqualsMatcherTest_219, BoundaryConditionEmptyStringMatch_219) {

    CasedString emptyCasedStr("", CaseSensitive::Yes);

    StringEqualsMatcher emptyMatcher(emptyCasedStr);

    EXPECT_TRUE(emptyMatcher.match(""));

}



TEST_F(StringEqualsMatcherTest_219, BoundaryConditionLongStringMatch_219) {

    std::string longStr(1000, 'a');

    CasedString longCasedStr(longStr, CaseSensitive::Yes);

    StringEqualsMatcher longMatcher(longCasedStr);

    EXPECT_TRUE(longMatcher.match(longStr));

}



TEST_F(StringEqualsMatcherTest_219, BoundaryConditionLongStringMismatch_219) {

    std::string longStr(1000, 'a');

    CasedString longCasedStr(longStr, CaseSensitive::Yes);

    StringEqualsMatcher longMatcher(longCasedStr);

    EXPECT_FALSE(longMatcher.match(std::string(1000, 'b')));

}
