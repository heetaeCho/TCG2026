#include <gtest/gtest.h>

#include "regeximpl.h"



class RegExTest_109 : public ::testing::Test {

protected:

    YAML::RegEx regex_a;

    YAML::RegEx regex_az;

    YAML::RegEx regex_empty;



    void SetUp() override {

        regex_a = YAML::RegEx('a');

        regex_az = YAML::RegEx('a', 'z');

        regex_empty = YAML::RegEx();

    }

};



TEST_F(RegExTest_109, MatchesSingleCharacter_109) {

    EXPECT_TRUE(regex_a.Matches("a"));

    EXPECT_FALSE(regex_a.Matches("b"));

}



TEST_F(RegExTest_109, MatchesCharacterInRange_109) {

    EXPECT_TRUE(regex_az.Matches("a"));

    EXPECT_TRUE(regex_az.Matches("z"));

    EXPECT_TRUE(regex_az.Matches("m"));

    EXPECT_FALSE(regex_az.Matches("{"));

    EXPECT_FALSE(regex_az.Matches("`"));

}



TEST_F(RegExTest_109, MatchesEmptyString_109) {

    EXPECT_TRUE(regex_empty.Matches(""));

    EXPECT_FALSE(regex_empty.Matches("a"));

}



TEST_F(RegExTest_109, MatchReturnsPositionForMatch_109) {

    EXPECT_EQ(regex_a.Match("a"), 0);

    EXPECT_EQ(regex_az.Match("m"), 0);

}



TEST_F(RegExTest_109, MatchReturnsNegativeOneForNoMatch_109) {

    EXPECT_EQ(regex_a.Match("b"), -1);

    EXPECT_EQ(regex_az.Match("{"), -1);

}



TEST_F(RegExTest_109, MatchesSingleCharacterBoundary_109) {

    EXPECT_TRUE(regex_a.Matches(std::string(1, 'a')));

    EXPECT_FALSE(regex_a.Matches(std::string(1, 'b')));

}



TEST_F(RegExTest_109, MatchEmptyStringBoundary_109) {

    EXPECT_EQ(regex_empty.Match(""), 0);

    EXPECT_EQ(regex_empty.Match("a"), -1);

}
