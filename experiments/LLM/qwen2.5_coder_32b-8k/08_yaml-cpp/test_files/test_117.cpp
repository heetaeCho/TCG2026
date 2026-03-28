#include "gtest/gtest.h"

#include "./TestProjects/yaml-cpp/src/exp.h"



namespace YAML {

class Stream {};

}



using namespace YAML::Exp;



TEST(TabRegExTest_117, MatchesSingleTabCharacter_117) {

    const RegEx& tabRegex = Tab();

    EXPECT_TRUE(tabRegex.Matches('\t'));

}



TEST(TabRegExTest_117, DoesNotMatchNonTabCharacters_117) {

    const RegEx& tabRegex = Tab();

    EXPECT_FALSE(tabRegex.Matches('a'));

    EXPECT_FALSE(tabRegex.Matches(' '));

    EXPECT_FALSE(tabRegex.Matches('\n'));

    EXPECT_FALSE(tabRegex.Matches('\r'));

}



TEST(TabRegExTest_117, MatchesStringWithSingleTab_117) {

    const RegEx& tabRegex = Tab();

    EXPECT_TRUE(tabRegex.Matches("\t"));

}



TEST(TabRegExTest_117, DoesNotMatchEmptyString_117) {

    const RegEx& tabRegex = Tab();

    EXPECT_FALSE(tabRegex.Matches(""));

}



TEST(TabRegExTest_117, DoesNotMatchStringWithoutTab_117) {

    const RegEx& tabRegex = Tab();

    EXPECT_FALSE(tabRegex.Matches("abc"));

    EXPECT_FALSE(tabRegex.Matches("a b c"));

}



TEST(TabRegExTest_117, MatchesSubstringWithTab_117) {

    const RegEx& tabRegex = Tab();

    EXPECT_TRUE(tabRegex.Matches("abc\txyz"));

}



TEST(TabRegExTest_117, MatchReturnsCorrectPositionForSingleTab_117) {

    const RegEx& tabRegex = Tab();

    EXPECT_EQ(0, tabRegex.Match("\t"));

}



TEST(TabRegExTest_117, MatchReturnsNegativeForNoMatch_117) {

    const RegEx& tabRegex = Tab();

    EXPECT_LT(tabRegex.Match("abc"), 0);

}



TEST(TabRegExTest_117, MatchReturnsCorrectPositionInSubstring_117) {

    const RegEx& tabRegex = Tab();

    EXPECT_EQ(3, tabRegex.Match("abc\txyz"));

}
