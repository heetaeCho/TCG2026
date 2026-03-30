#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



class RegExTest_118 : public ::testing::Test {

protected:

    const RegEx& blankRegex = Blank();

};



TEST_F(RegExTest_118, MatchesSpace_118) {

    EXPECT_TRUE(blankRegex.Matches(' '));

}



TEST_F(RegExTest_118, MatchesTab_118) {

    EXPECT_TRUE(blankRegex.Matches('\t'));

}



TEST_F(RegExTest_118, DoesNotMatchNonWhitespace_118) {

    EXPECT_FALSE(blankRegex.Matches('a'));

    EXPECT_FALSE(blankRegex.Matches('0'));

    EXPECT_FALSE(blankRegex.Matches('.'));

}



TEST_F(RegExTest_118, MatchesStringWithSpace_118) {

    EXPECT_TRUE(blankRegex.Matches(" "));

}



TEST_F(RegExTest_118, MatchesStringWithTab_118) {

    EXPECT_TRUE(blankRegex.Matches("\t"));

}



TEST_F(RegExTest_118, DoesNotMatchNonWhitespaceString_118) {

    EXPECT_FALSE(blankRegex.Matches("abc"));

    EXPECT_FALSE(blankRegex.Matches("123"));

    EXPECT_FALSE(blankRegex.Matches(".!@#"));

}



TEST_F(RegExTest_118, MatchReturnsLengthOfSpace_118) {

    EXPECT_EQ(blankRegex.Match(" "), 1);

}



TEST_F(RegExTest_118, MatchReturnsLengthOfTab_118) {

    EXPECT_EQ(blankRegex.Match("\t"), 1);

}



TEST_F(RegExTest_118, MatchReturnsZeroForNonWhitespace_118) {

    EXPECT_EQ(blankRegex.Match("a"), 0);

    EXPECT_EQ(blankRegex.Match("0"), 0);

    EXPECT_EQ(blankRegex.Match("."), 0);

}



TEST_F(RegExTest_118, MatchReturnsZeroForEmptyString_118) {

    EXPECT_EQ(blankRegex.Match(""), 0);

}
