#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



class RegExTest : public ::testing::Test {

protected:

    const RegEx& digitRegex = Digit();

};



TEST_F(RegExTest_121, MatchesDigitCharacter_121) {

    EXPECT_TRUE(digitRegex.Matches('0'));

    EXPECT_TRUE(digitRegex.Matches('5'));

    EXPECT_TRUE(digitRegex.Matches('9'));

}



TEST_F(RegExTest_121, DoesNotMatchNonDigitCharacter_121) {

    EXPECT_FALSE(digitRegex.Matches('a'));

    EXPECT_FALSE(digitRegex.Matches('-'));

    EXPECT_FALSE(digitRegex.Matches(' '));

}



TEST_F(RegExTest_121, MatchesDigitString_121) {

    EXPECT_TRUE(digitRegex.Matches("0"));

    EXPECT_TRUE(digitRegex.Matches("5"));

    EXPECT_TRUE(digitRegex.Matches("9"));

}



TEST_F(RegExTest_121, DoesNotMatchNonDigitString_121) {

    EXPECT_FALSE(digitRegex.Matches("a"));

    EXPECT_FALSE(digitRegex.Matches("-"));

    EXPECT_FALSE(digitRegex.Matches(" "));

}



TEST_F(RegExTest_121, MatchReturnsCorrectLengthForDigit_121) {

    EXPECT_EQ(digitRegex.Match("0"), 1);

    EXPECT_EQ(digitRegex.Match("5"), 1);

    EXPECT_EQ(digitRegex.Match("9"), 1);

}



TEST_F(RegExTest_121, MatchReturnsZeroForNonDigit_121) {

    EXPECT_EQ(digitRegex.Match("a"), 0);

    EXPECT_EQ(digitRegex.Match("-"), 0);

    EXPECT_EQ(digitRegex.Match(" "), 0);

}
