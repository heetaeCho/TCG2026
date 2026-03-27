#include <gtest/gtest.h>

#include "exp.h"

#include "regex_yaml.h"



class RegExTest_119 : public ::testing::Test {

protected:

    YAML::Exp::RegEx breakRegex;



    void SetUp() override {

        breakRegex = YAML::Exp::Break();

    }

};



TEST_F(RegExTest_119, MatchesNewLineCharacter_119) {

    EXPECT_TRUE(breakRegex.Matches('\n'));

}



TEST_F(RegExTest_119, MatchesCarriageReturnNewLine_119) {

    EXPECT_TRUE(breakRegex.Matches("\r\n"));

}



TEST_F(RegExTest_119, MatchesCarriageReturn_119) {

    EXPECT_TRUE(breakRegex.Matches('\r'));

}



TEST_F(RegExTest_119, DoesNotMatchOtherCharacters_119) {

    EXPECT_FALSE(breakRegex.Matches('a'));

    EXPECT_FALSE(breakRegex.Matches(' '));

    EXPECT_FALSE(breakRegex.Matches('\t'));

}



TEST_F(RegExTest_119, MatchesStringWithNewLine_119) {

    EXPECT_TRUE(breakRegex.Matches("\nabc"));

}



TEST_F(RegExTest_119, MatchesStringWithCarriageReturnNewLine_119) {

    EXPECT_TRUE(breakRegex.Matches("\r\nabc"));

}



TEST_F(RegExTest_119, MatchesStringWithCarriageReturn_119) {

    EXPECT_TRUE(breakRegex.Matches("\rabcd"));

}



TEST_F(RegExTest_119, DoesNotMatchEmptyString_119) {

    EXPECT_FALSE(breakRegex.Matches(""));

}



TEST_F(RegExTest_119, MatchReturnsCorrectIndexForNewLine_119) {

    EXPECT_EQ(breakRegex.Match("abc\ndef"), 3);

}



TEST_F(RegExTest_119, MatchReturnsCorrectIndexForCarriageReturnNewLine_119) {

    EXPECT_EQ(breakRegex.Match("abc\r\ndef"), 3);

}



TEST_F(RegExTest_119, MatchReturnsCorrectIndexForCarriageReturn_119) {

    EXPECT_EQ(breakRegex.Match("abc\rcdef"), 3);

}



TEST_F(RegExTest_119, MatchReturnsNegativeOneForNoMatch_119) {

    EXPECT_EQ(breakRegex.Match("abcdef"), -1);

}
