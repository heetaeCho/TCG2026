#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exp.h"



using namespace YAML::Exp;



class DocEndTest_129 : public ::testing::Test {

protected:

    const RegEx& doc_end_regex = DocEnd();

};



TEST_F(DocEndTest_129, MatchesDocEndPattern_129) {

    EXPECT_TRUE(doc_end_regex.Matches("...\n"));

    EXPECT_TRUE(doc_end_regex.Matches("... "));

}



TEST_F(DocEndTest_129, DoesNotMatchInvalidPatterns_129) {

    EXPECT_FALSE(doc_end_regex.Matches(".."));

    EXPECT_FALSE(doc_end_regex.Matches("...."));

    EXPECT_FALSE(doc_end_regex.Matches("...a"));

    EXPECT_FALSE(doc_end_regex.Matches("abc...\n"));

}



TEST_F(DocEndTest_129, MatchesDocEndWithBlankOrBreak_129) {

    EXPECT_TRUE(doc_end_regex.Matches("...\t"));

    EXPECT_TRUE(doc_end_regex.Matches("...\r\n"));

}



TEST_F(DocEndTest_129, MatchesEmptyAfterDocEnd_129) {

    EXPECT_TRUE(doc_end_regex.Matches("..."));

}



TEST_F(DocEndTest_129, MatchFunctionReturnsCorrectLength_129) {

    EXPECT_EQ(doc_end_regex.Match("...\n"), 3);

    EXPECT_EQ(doc_end_regex.Match("... "), 3);

    EXPECT_EQ(doc_end_regex.Match("..."), 3);

}



TEST_F(DocEndTest_129, MatchFunctionReturnsZeroForNonMatches_129) {

    EXPECT_EQ(doc_end_regex.Match(".."), 0);

    EXPECT_EQ(doc_end_regex.Match("...."), 0);

    EXPECT_EQ(doc_end_regex.Match("...a"), 0);

    EXPECT_EQ(doc_end_regex.Match("abc...\n"), 0);

}
