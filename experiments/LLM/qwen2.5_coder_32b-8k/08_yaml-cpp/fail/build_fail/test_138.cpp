#include <gtest/gtest.h>

#include "exp.h"

#include "regex_yaml.h"



using namespace YAML::Exp;



class RegExTest_138 : public ::testing::Test {

protected:

    virtual void SetUp() {

        commentRegex = Comment();

    }



    RegEx commentRegex;

};



TEST_F(RegExTest_138, MatchesSingleCommentChar_138) {

    EXPECT_TRUE(commentRegex.Matches('#'));

}



TEST_F(RegExTest_138, DoesNotMatchOtherChars_138) {

    EXPECT_FALSE(commentRegex.Matches('a'));

    EXPECT_FALSE(commentRegex.Matches(' '));

    EXPECT_FALSE(commentRegex.Matches('\n'));

}



TEST_F(RegExTest_138, MatchesCommentAtStartOfString_138) {

    EXPECT_TRUE(commentRegex.Matches("# This is a comment"));

}



TEST_F(RegExTest_138, DoesNotMatchStringWithoutComment_138) {

    EXPECT_FALSE(commentRegex.Matches("This is not a comment"));

}



TEST_F(RegExTest_138, MatchReturnsLengthOfCommentChar_138) {

    EXPECT_EQ(commentRegex.Match("#"), 1);

}



TEST_F(RegExTest_138, MatchReturnsZeroForNonMatchingString_138) {

    EXPECT_EQ(commentRegex.Match("No comment here"), 0);

}
