#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML::Exp;



class RegExTagTest : public ::testing::Test {

protected:

    const RegEx& tagRegex = Tag();

};



TEST_F(RegExTagTest_142, MatchesValidWord_142) {

    EXPECT_TRUE(tagRegex.Matches("word"));

}



TEST_F(RegExTagTest_142, MatchesValidSpecialCharacters_142) {

    EXPECT_TRUE(tagRegex.Matches("#;/?:@&=+$_.~*'()"));

}



TEST_F(RegExTagTest_142, MatchesValidHexSequence_142) {

    EXPECT_TRUE(tagRegex.Matches("%20")); // Example of hex sequence

}



TEST_F(RegExTagTest_142, DoesNotMatchInvalidCharacter_142) {

    EXPECT_FALSE(tagRegex.Matches("!"));

}



TEST_F(RegExTagTest_142, MatchesEmptyString_142) {

    EXPECT_FALSE(tagRegex.Matches(""));

}



TEST_F(RegExTagTest_142, MatchValidWord_142) {

    EXPECT_EQ(tagRegex.Match("word"), 4);

}



TEST_F(RegExTagTest_142, MatchValidSpecialCharacters_142) {

    EXPECT_EQ(tagRegex.Match("#;/?:@&=+$_.~*'()"), 18);

}



TEST_F(RegExTagTest_142, MatchValidHexSequence_142) {

    EXPECT_EQ(tagRegex.Match("%20"), 3); // Example of hex sequence

}



TEST_F(RegExTagTest_142, MatchInvalidCharacter_142) {

    EXPECT_EQ(tagRegex.Match("!"), -1);

}



TEST_F(RegExTagTest_142, MatchEmptyString_142) {

    EXPECT_EQ(tagRegex.Match(""), 0);

}
