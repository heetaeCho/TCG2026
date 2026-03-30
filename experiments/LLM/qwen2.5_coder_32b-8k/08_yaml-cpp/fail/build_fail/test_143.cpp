#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



TEST_F(PlainScalarTest_143, MatchesValidPlainScalars_143) {

    EXPECT_TRUE(PlainScalar().Matches("valid"));

    EXPECT_TRUE(PlainScalar().Matches("plain_scalar123"));

    EXPECT_TRUE(PlainScalar().Matches("another_valid_plain_scalar"));

}



TEST_F(PlainScalarTest_143, MatchesEmptyString_143) {

    EXPECT_FALSE(PlainScalar().Matches(""));

}



TEST_F(PlainScalarTest_143, DoesNotMatchStringsContainingForbiddenCharacters_143) {

    EXPECT_FALSE(PlainScalar().Matches("forbidden,char"));

    EXPECT_FALSE(PlainScalar().Matches("[brackets]"));

    EXPECT_FALSE(PlainScalar().Matches("{curly}"));

    EXPECT_FALSE(PlainScalar().Matches("#hash"));

    EXPECT_FALSE(PlainScalar().Matches("&ampersand"));

    EXPECT_FALSE(PlainScalar().Matches("*asterisk"));

    EXPECT_FALSE(PlainScalar().Matches("!exclamation"));

    EXPECT_FALSE(PlainScalar().Matches("|pipe"));

    EXPECT_FALSE(PlainScalar().Matches("'>single_quote'"));

    EXPECT_FALSE(PlainScalar().Matches("\"double_quote\""));

    EXPECT_FALSE(PlainScalar().Matches("%percent"));

    EXPECT_FALSE(PlainScalar().Matches("@at"));

    EXPECT_FALSE(PlainScalar().Matches("`backtick`"));

}



TEST_F(PlainScalarTest_143, DoesNotMatchStringsStartingWithDashColon_143) {

    EXPECT_FALSE(PlainScalar().Matches("-:"));

    EXPECT_FALSE(PlainScalar().Matches("-: followed_by_text"));

}



TEST_F(PlainScalarTest_143, MatchesStringsStartingWithDashColonFollowedByNonBlankOrBreak_143) {

    EXPECT_TRUE(PlainScalar().Matches("-:a"));

    EXPECT_TRUE(PlainScalar().Matches("-:123"));

}



TEST_F(PlainScalarTest_143, MatchesStringsStartingWithDashColonFollowedByBlank_143) {

    EXPECT_FALSE(PlainScalar().Matches("-: "));

}



TEST_F(PlainScalarTest_143, MatchesStringsStartingWithDashColonFollowedByBreak_143) {

    EXPECT_FALSE(PlainScalar().Matches("-:\n"));

}
