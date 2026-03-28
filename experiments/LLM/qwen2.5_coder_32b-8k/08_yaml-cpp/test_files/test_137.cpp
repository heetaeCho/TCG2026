#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/exp.h"



using namespace YAML::Exp;



TEST(AmpersandRegExTest_137, MatchesAmpersandCharacter_137) {

    const auto& ampersandRegex = Ampersand();

    EXPECT_TRUE(ampersandRegex.Matches('&'));

}



TEST(AmpersandRegExTest_137, DoesNotMatchNonAmpersandCharacters_137) {

    const auto& ampersandRegex = Ampersand();

    EXPECT_FALSE(ampersandRegex.Matches('a'));

    EXPECT_FALSE(ampersandRegex.Matches('1'));

    EXPECT_FALSE(ampersandRegex.Matches(' '));

}



TEST(AmpersandRegExTest_137, MatchesAmpersandInString_137) {

    const auto& ampersandRegex = Ampersand();

    EXPECT_TRUE(ampersandRegex.Matches("&"));

    EXPECT_TRUE(ampersandRegex.Matches("abc&def"));

}



TEST(AmpersandRegExTest_137, DoesNotMatchStringsLackingAmpersand_137) {

    const auto& ampersandRegex = Ampersand();

    EXPECT_FALSE(ampersandRegex.Matches(""));

    EXPECT_FALSE(ampersandRegex.Matches("abcdef"));

}



TEST(AmpersandRegExTest_137, MatchFunctionReturnsOneForAmpersand_137) {

    const auto& ampersandRegex = Ampersand();

    EXPECT_EQ(ampersandRegex.Match("&"), 1);

}



TEST(AmpersandRegExTest_137, MatchFunctionReturnsZeroForNonAmpersandCharacters_137) {

    const auto& ampersandRegex = Ampersand();

    EXPECT_EQ(ampersandRegex.Match("a"), 0);

    EXPECT_EQ(ampersandRegex.Match("1"), 0);

}



TEST(AmpersandRegExTest_137, MatchFunctionReturnsOneForAmpersandInString_137) {

    const auto& ampersandRegex = Ampersand();

    EXPECT_EQ(ampersandRegex.Match("abc&def"), 1);

}



TEST(AmpersandRegExTest_137, MatchFunctionReturnsZeroForStringsLackingAmpersand_137) {

    const auto& ampersandRegex = Ampersand();

    EXPECT_EQ(ampersandRegex.Match(""), 0);

    EXPECT_EQ(ampersandRegex.Match("abcdef"), 0);

}
