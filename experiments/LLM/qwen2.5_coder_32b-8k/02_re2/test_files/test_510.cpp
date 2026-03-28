#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/parse.cc"



namespace re2 {



class ParseStateTest : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{ParseFlags(0), absl::string_view(""), &status};

};



TEST_F(ParseStateTest_510, DoConcatenation_NoStackTop_RegExpEmptyMatchCreated_510) {

    EXPECT_TRUE(parse_state.DoConcatenation());

    ASSERT_NE(parse_state.stacktop_, nullptr);

    EXPECT_EQ(parse_state.stacktop_->op(), kRegexpEmptyMatch);

}



TEST_F(ParseStateTest_510, DoConcatenation_StackTopIsMarker_RegExpEmptyMatchCreated_510) {

    Regexp* marker = new Regexp(RegexpOp::kMaxRegexpOp + 1, ParseFlags(0));

    parse_state.stacktop_ = marker;

    EXPECT_TRUE(parse_state.DoConcatenation());

    ASSERT_NE(parse_state.stacktop_, nullptr);

    EXPECT_EQ(parse_state.stacktop_->op(), kRegexpEmptyMatch);

    delete marker; // Clean up the mock marker

}



TEST_F(ParseStateTest_510, DoConcatenation_NormalOperation_RegExpConcatPerformed_510) {

    Regexp* re1 = new Regexp(kRegexpLiteral, ParseFlags(0));

    Regexp* re2 = new Regexp(kRegexpLiteralString, ParseFlags(0));

    parse_state.stacktop_ = re1;

    EXPECT_TRUE(parse_state.PushRegexp(re2)); // Push re2 onto the stack

    EXPECT_TRUE(parse_state.DoConcatenation());

    ASSERT_NE(parse_state.stacktop_, nullptr);

    EXPECT_EQ(parse_state.stacktop_->op(), kRegexpConcat);

    delete parse_state.stacktop_; // Clean up the concatenated result

}



}  // namespace re2
