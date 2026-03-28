#include <gtest/gtest.h>

#include "exp.h"

#include "regex_yaml.h"



class RegExTest_116 : public ::testing::Test {

protected:

    YAML::RegEx spaceRegex;

    YAML::RegEx rangeRegex;



    void SetUp() override {

        spaceRegex = YAML::Exp::Space();

        rangeRegex = YAML::RegEx('a', 'z');

    }

};



TEST_F(RegExTest_116, SpaceMatchesSingleSpace_116) {

    EXPECT_TRUE(spaceRegex.Matches(' '));

}



TEST_F(RegExTest_116, SpaceDoesNotMatchNonSpaceCharacters_116) {

    EXPECT_FALSE(spaceRegex.Matches('a'));

    EXPECT_FALSE(spaceRegex.Matches('\n'));

    EXPECT_FALSE(spaceRegex.Matches('\t'));

}



TEST_F(RegExTest_116, SpaceMatchesStringWithSingleSpace_116) {

    EXPECT_TRUE(spaceRegex.Matches(" "));

}



TEST_F(RegExTest_116, SpaceDoesNotMatchNonEmptyStrings_116) {

    EXPECT_FALSE(spaceRegex.Matches("a"));

    EXPECT_FALSE(spaceRegex.Matches("  "));

}



TEST_F(RegExTest_116, RangeMatchesCharactersInRange_116) {

    for (char ch = 'a'; ch <= 'z'; ++ch) {

        EXPECT_TRUE(rangeRegex.Matches(ch));

    }

}



TEST_F(RegExTest_116, RangeDoesNotMatchCharactersOutsideRange_116) {

    EXPECT_FALSE(rangeRegex.Matches('A'));

    EXPECT_FALSE(rangeRegex.Matches('Z'));

    EXPECT_FALSE(rangeRegex.Matches('0'));

    EXPECT_FALSE(rangeRegex.Matches('@'));

    EXPECT_FALSE(rangeRegex.Matches('{'));

}



TEST_F(RegExTest_116, RangeMatchesStringWithinRange_116) {

    EXPECT_TRUE(rangeRegex.Matches("abc"));

}



TEST_F(RegExTest_116, RangeDoesNotMatchStringsOutsideRange_116) {

    EXPECT_FALSE(rangeRegex.Matches("ABC"));

    EXPECT_FALSE(rangeRegex.Matches("abc123"));

    EXPECT_FALSE(rangeRegex.Matches("!@#"));

}



TEST_F(RegExTest_116, RangeMatchesEmptyStringReturnsFalse_116) {

    EXPECT_FALSE(rangeRegex.Matches(""));

}



TEST_F(RegExTest_116, SpaceMatchFunctionForSingleSpace_116) {

    EXPECT_EQ(spaceRegex.Match(" "), 1);

}



TEST_F(RegExTest_116, SpaceMatchFunctionForNonSpaceCharacter_116) {

    EXPECT_EQ(spaceRegex.Match("a"), 0);

}



TEST_F(RegExTest_116, RangeMatchFunctionForCharactersInRange_116) {

    for (char ch = 'a'; ch <= 'z'; ++ch) {

        std::string str(1, ch);

        EXPECT_EQ(rangeRegex.Match(str), 1);

    }

}



TEST_F(RegExTest_116, RangeMatchFunctionForCharactersOutsideRange_116) {

    for (char ch : {'A', 'Z', '0', '@', '{'}) {

        std::string str(1, ch);

        EXPECT_EQ(rangeRegex.Match(str), 0);

    }

}



TEST_F(RegExTest_116, RangeMatchFunctionForStringWithinRange_116) {

    EXPECT_EQ(rangeRegex.Match("abc"), 3);

}



TEST_F(RegExTest_116, RangeMatchFunctionForStringOutsideRange_116) {

    EXPECT_EQ(rangeRegex.Match("ABC"), 0);

    EXPECT_EQ(rangeRegex.Match("abc123"), 3); // Matches only up to 'c'

    EXPECT_EQ(rangeRegex.Match("!@#"), 0);

}



TEST_F(RegExTest_116, RangeMatchFunctionForEmptyString_116) {

    EXPECT_EQ(rangeRegex.Match(""), 0);

}
