#include <gtest/gtest.h>

#include "exp.h"



using namespace YAML;

using namespace YAML::Exp;



class RegExTest_150 : public ::testing::Test {

protected:

    const RegEx& escBreak = EscBreak();

};



TEST_F(RegExTest_150, MatchesSingleBackslash_150) {

    EXPECT_TRUE(escBreak.Matches('\\'));

}



TEST_F(RegExTest_150, DoesNotMatchOtherCharacters_150) {

    EXPECT_FALSE(escBreak.Matches('a'));

    EXPECT_FALSE(escBreak.Matches('9'));

    EXPECT_FALSE(escBreak.Matches('\n'));

}



TEST_F(RegExTest_150, MatchesStringWithBackslashAtStart_150) {

    EXPECT_TRUE(escBreak.Matches("\\string"));

}



TEST_F(RegExTest_150, DoesNotMatchStringWithoutBackslash_150) {

    EXPECT_FALSE(escBreak.Matches("string"));

}



TEST_F(RegExTest_150, MatchesEmptyString_150) {

    EXPECT_FALSE(escBreak.Matches(""));

}



TEST_F(RegExTest_150, MatchPositionSingleBackslash_150) {

    EXPECT_EQ(escBreak.Match("\\"), 1);

}



TEST_F(RegExTest_150, MatchPositionStringWithBackslashAtStart_150) {

    EXPECT_EQ(escBreak.Match("\\string"), 1);

}



TEST_F(RegExTest_150, NoMatchPositionOtherCharacters_150) {

    EXPECT_EQ(escBreak.Match("a"), -1);

    EXPECT_EQ(escBreak.Match("9"), -1);

    EXPECT_EQ(escBreak.Match("\n"), -1);

}



TEST_F(RegExTest_150, NoMatchPositionEmptyString_150) {

    EXPECT_EQ(escBreak.Match(""), -1);

}
