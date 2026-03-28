#include <gtest/gtest.h>

#include "exp.h"

#include "regex_yaml.h"



class RegExTest_122 : public ::testing::Test {

protected:

    YAML::RegEx alphaRegex = YAML::Exp::Alpha();

};



TEST_F(RegExTest_122, AlphaMatchesLowerCaseLetter_122) {

    EXPECT_TRUE(alphaRegex.Matches('a'));

}



TEST_F(RegExTest_122, AlphaMatchesUpperCaseLetter_122) {

    EXPECT_TRUE(alphaRegex.Matches('Z'));

}



TEST_F(RegExTest_122, AlphaDoesNotMatchDigit_122) {

    EXPECT_FALSE(alphaRegex.Matches('5'));

}



TEST_F(RegExTest_122, AlphaDoesNotMatchSpecialCharacter_122) {

    EXPECT_FALSE(alphaRegex.Matches('#'));

}



TEST_F(RegExTest_122, AlphaMatchesStringWithLowerCaseLetter_122) {

    EXPECT_TRUE(alphaRegex.Matches("abc"));

}



TEST_F(RegExTest_122, AlphaMatchesStringWithUpperCaseLetter_122) {

    EXPECT_TRUE(alphaRegex.Matches("XYZ"));

}



TEST_F(RegExTest_122, AlphaDoesNotMatchStringWithDigit_122) {

    EXPECT_FALSE(alphaRegex.Matches("abc123"));

}



TEST_F(RegExTest_122, AlphaDoesNotMatchStringWithSpecialCharacter_122) {

    EXPECT_FALSE(alphaRegex.Matches("abc#def"));

}



TEST_F(RegExTest_122, AlphaMatchesEmptyString_ReturnsFalse_122) {

    EXPECT_FALSE(alphaRegex.Matches(""));

}
