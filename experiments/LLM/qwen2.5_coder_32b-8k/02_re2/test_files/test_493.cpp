#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/parse.cc"



namespace re2 {



class ParseStateTest_493 : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state_{NoParseFlags, "", &status};

};



TEST_F(ParseStateTest_493, PushDot_ReturnsTrueWhenDotNLIsSetAndNeverNLIsNotSet_493) {

    parse_state_.flags_ = DotNL;

    EXPECT_TRUE(parse_state_.PushDot());

}



TEST_F(ParseStateTest_493, PushDot_ReturnsFalseWhenNeverNLIsSet_493) {

    parse_state_.flags_ = NeverNL | DotNL;

    EXPECT_FALSE(parse_state_.PushDot());

}



TEST_F(ParseStateTest_493, PushDot_CreatesCharClassBuilderWithCorrectRanges_493) {

    parse_state_.flags_ = 0; // Neither DotNL nor NeverNL

    EXPECT_TRUE(parse_state_.PushDot());

    Regexp* re = parse_state_.stacktop_;

    ASSERT_NE(re->ccb_, nullptr);

    EXPECT_FALSE(re->ccb_->Contains('\n'));

    EXPECT_TRUE(re->ccb_->Contains('a'));  // Assuming 'a' is within the range (0, '\n'-1) and ('\n'+1, rune_max_)

}



TEST_F(ParseStateTest_493, PushDot_PushesSimpleOpWhenDotNLAndNotNeverNL_493) {

    parse_state_.flags_ = DotNL;

    EXPECT_TRUE(parse_state_.PushDot());

    Regexp* re = parse_state_.stacktop_;

    ASSERT_EQ(re->op(), kRegexpAnyChar);

}



}  // namespace re2
