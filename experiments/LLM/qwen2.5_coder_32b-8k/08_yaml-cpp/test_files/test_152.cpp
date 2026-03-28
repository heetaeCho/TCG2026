#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



class ChompTest_152 : public ::testing::Test {

protected:

    const RegEx& chomp_regex = Chomp();

};



TEST_F(ChompTest_152, MatchesValidChompIndicator_152) {

    EXPECT_TRUE(chomp_regex.Matches('+'));

    EXPECT_TRUE(chomp_regex.Matches('-'));

    EXPECT_TRUE(chomp_regex.Matches(' '));

}



TEST_F(ChompTest_152, MatchesValidDigit_152) {

    for (char ch = '0'; ch <= '9'; ++ch) {

        EXPECT_TRUE(chomp_regex.Matches(ch));

    }

}



TEST_F(ChompTest_152, MatchesCombinationOfChompIndicatorAndDigit_152) {

    EXPECT_TRUE(chomp_regex.Matches("+1"));

    EXPECT_TRUE(chomp_regex.Matches("1+"));

    EXPECT_TRUE(chomp_regex.Matches("-0"));

    EXPECT_TRUE(chomp_regex.Matches("0-"));

}



TEST_F(ChompTest_152, DoesNotMatchInvalidCharacter_152) {

    for (char ch = 'A'; ch <= 'Z'; ++ch) {

        EXPECT_FALSE(chomp_regex.Matches(ch));

    }

    for (char ch = 'a'; ch <= 'z'; ++ch) {

        EXPECT_FALSE(chomp_regex.Matches(ch));

    }

    EXPECT_FALSE(chomp_regex.Matches('$'));

    EXPECT_FALSE(chomp_regex.Matches('@'));

}



TEST_F(ChompTest_152, MatchesEmptyString_152) {

    EXPECT_FALSE(chomp_regex.Matches(""));

}



TEST_F(ChompTest_152, MatchesLongerInvalidString_152) {

    EXPECT_FALSE(chomp_regex.Matches("abc"));

    EXPECT_FALSE(chomp_regex.Matches("1234"));

    EXPECT_FALSE(chomp_regex.Matches("+-"));

}
