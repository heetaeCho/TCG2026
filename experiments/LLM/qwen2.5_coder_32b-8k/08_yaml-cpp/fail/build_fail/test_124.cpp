#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML;

using namespace YAML::Exp;



class RegExTest : public ::testing::Test {

protected:

    RegEx wordRegex = Word();

};



TEST_F(RegExTest_124, MatchesValidWordCharacters_124) {

    EXPECT_TRUE(wordRegex.Matches('a'));

    EXPECT_TRUE(wordRegex.Matches('Z'));

    EXPECT_TRUE(wordRegex.Matches('0'));

    EXPECT_TRUE(wordRegex.Matches('-'));

}



TEST_F(RegExTest_124, DoesNotMatchInvalidWordCharacters_124) {

    EXPECT_FALSE(wordRegex.Matches('@'));

    EXPECT_FALSE(wordRegex.Matches(' '));

    EXPECT_FALSE(wordRegex.Matches('_'));

}



TEST_F(RegExTest_124, MatchesValidWordStrings_124) {

    EXPECT_TRUE(wordRegex.Matches("abc"));

    EXPECT_TRUE(wordRegex.Matches("Z9-"));

    EXPECT_TRUE(wordRegex.Matches("0123"));

}



TEST_F(RegExTest_124, DoesNotMatchInvalidWordStrings_124) {

    EXPECT_FALSE(wordRegex.Matches("abc@"));

    EXPECT_FALSE(wordRegex.Matches("Z9_"));

    EXPECT_FALSE(wordRegex.Matches("  "));

}



TEST_F(RegExTest_124, MatchesEmptyString_124) {

    EXPECT_FALSE(wordRegex.Matches(""));

}



TEST_F(RegExTest_124, MatchValidWordCharacters_124) {

    EXPECT_EQ(wordRegex.Match('a'), 1);

    EXPECT_EQ(wordRegex.Match('Z'), 1);

    EXPECT_EQ(wordRegex.Match('0'), 1);

    EXPECT_EQ(wordRegex.Match('-'), 1);

}



TEST_F(RegExTest_124, MatchInvalidWordCharacters_124) {

    EXPECT_EQ(wordRegex.Match('@'), -1);

    EXPECT_EQ(wordRegex.Match(' '), -1);

    EXPECT_EQ(wordRegex.Match('_'), -1);

}



TEST_F(RegExTest_124, MatchValidWordStrings_124) {

    EXPECT_EQ(wordRegex.Match("abc"), 3);

    EXPECT_EQ(wordRegex.Match("Z9-"), 3);

    EXPECT_EQ(wordRegex.Match("0123"), 4);

}



TEST_F(RegExTest_124, MatchInvalidWordStrings_124) {

    EXPECT_EQ(wordRegex.Match("abc@"), -1);

    EXPECT_EQ(wordRegex.Match("Z9_"), -1);

    EXPECT_EQ(wordRegex.Match("  "), -1);

}



TEST_F(RegExTest_124, MatchEmptyString_124) {

    EXPECT_EQ(wordRegex.Match(""), -1);

}
