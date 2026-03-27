#include <gtest/gtest.h>

#include "exp.h"

#include "regex_yaml.h"



using namespace YAML::Exp;



class DocStartTest_128 : public ::testing::Test {

protected:

    const RegEx& docStartRegex = DocStart();

};



TEST_F(DocStartTest_128, MatchesDocStartString_128) {

    EXPECT_TRUE(docStartRegex.Matches("---"));

}



TEST_F(DocStartTest_128, DoesNotMatchOtherStrings_128) {

    EXPECT_FALSE(docStartRegex.Matches("..."));

    EXPECT_FALSE(docStartRegex.Matches("--"));

    EXPECT_FALSE(docStartRegex.Matches("----"));

    EXPECT_FALSE(docStartRegex.Matches("a---b"));

}



TEST_F(DocStartTest_128, MatchesDocStartWithBlankOrBreak_128) {

    EXPECT_TRUE(docStartRegex.Matches("--- "));

    EXPECT_TRUE(docStartRegex.Matches("---\n"));

    EXPECT_TRUE(docStartRegex.Matches("---\r"));

    EXPECT_TRUE(docStartRegex.Matches("---\t"));

}



TEST_F(DocStartTest_128, MatchesEmptyStringAfterDocStart_128) {

    EXPECT_TRUE(docStartRegex.Matches("---"));

}



TEST_F(DocStartTest_128, MatchLengthForValidDocStart_128) {

    EXPECT_EQ(docStartRegex.Match("---"), 3);

}



TEST_F(DocStartTest_128, MatchLengthForInvalidString_128) {

    EXPECT_EQ(docStartRegex.Match("..."), -1);

    EXPECT_EQ(docStartRegex.Match("--"), -1);

    EXPECT_EQ(docStartRegex.Match("----"), -1);

    EXPECT_EQ(docStartRegex.Match("a---b"), 3);

}



TEST_F(DocStartTest_128, MatchLengthForDocStartWithBlankOrBreak_128) {

    EXPECT_EQ(docStartRegex.Match("--- "), 4);

    EXPECT_EQ(docStartRegex.Match("---\n"), 4);

    EXPECT_EQ(docStartRegex.Match("---\r"), 4);

    EXPECT_EQ(docStartRegex.Match("---\t"), 4);

}
