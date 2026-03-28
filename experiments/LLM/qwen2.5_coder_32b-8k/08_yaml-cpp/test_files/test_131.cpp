#include <gtest/gtest.h>

#include "exp.h"



class RegExTest_131 : public ::testing::Test {

protected:

    YAML::Exp::RegEx blockEntry;

    

    RegExTest_131() : blockEntry(YAML::Exp::BlockEntry()) {}

};



TEST_F(RegExTest_131, MatchesDash_131) {

    EXPECT_TRUE(blockEntry.Matches('-'));

}



TEST_F(RegExTest_131, MatchesSpace_131) {

    EXPECT_TRUE(blockEntry.Matches(' '));

}



TEST_F(RegExTest_131, MatchesTab_131) {

    EXPECT_TRUE(blockEntry.Matches('\t'));

}



TEST_F(RegExTest_131, MatchesNewline_131) {

    EXPECT_TRUE(blockEntry.Matches('\n'));

}



TEST_F(RegExTest_131, MatchesRandomCharacter_131) {

    EXPECT_FALSE(blockEntry.Matches('a'));

}



TEST_F(RegExTest_131, MatchesEmptyString_131) {

    EXPECT_TRUE(blockEntry.Matches(""));

}



TEST_F(RegExTest_131, MatchesDashOnlyString_131) {

    EXPECT_TRUE(blockEntry.Matches("-"));

}



TEST_F(RegExTest_131, MatchesSpaceOnlyString_131) {

    EXPECT_TRUE(blockEntry.Matches(" "));

}



TEST_F(RegExTest_131, MatchesTabOnlyString_131) {

    EXPECT_TRUE(blockEntry.Matches("\t"));

}



TEST_F(RegExTest_131, MatchesNewlineOnlyString_131) {

    EXPECT_TRUE(blockEntry.Matches("\n"));

}



TEST_F(RegExTest_131, MatchesRandomString_131) {

    EXPECT_FALSE(blockEntry.Matches("random"));

}



TEST_F(RegExTest_131, MatchDash_131) {

    EXPECT_EQ(blockEntry.Match("-"), 1);

}



TEST_F(RegExTest_131, MatchSpace_131) {

    EXPECT_EQ(blockEntry.Match(" "), 1);

}



TEST_F(RegExTest_131, MatchTab_131) {

    EXPECT_EQ(blockEntry.Match("\t"), 1);

}



TEST_F(RegExTest_131, MatchNewline_131) {

    EXPECT_EQ(blockEntry.Match("\n"), 1);

}



TEST_F(RegExTest_131, MatchRandomCharacter_131) {

    EXPECT_EQ(blockEntry.Match("a"), 0);

}



TEST_F(RegExTest_131, MatchEmptyString_131) {

    EXPECT_EQ(blockEntry.Match(""), 0);

}



TEST_F(RegExTest_131, MatchDashOnlyString_131) {

    EXPECT_EQ(blockEntry.Match("-"), 1);

}



TEST_F(RegExTest_131, MatchSpaceOnlyString_131) {

    EXPECT_EQ(blockEntry.Match(" "), 1);

}



TEST_F(RegExTest_131, MatchTabOnlyString_131) {

    EXPECT_EQ(blockEntry.Match("\t"), 1);

}



TEST_F(RegExTest_131, MatchNewlineOnlyString_131) {

    EXPECT_EQ(blockEntry.Match("\n"), 1);

}



TEST_F(RegExTest_131, MatchRandomString_131) {

    EXPECT_EQ(blockEntry.Match("random"), 0);

}
