#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/parse.cc"

#include "./TestProjects/re2/re2/regexp.h"



namespace re2 {



class ParseStateTest : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{ParseFlags::NoParseFlags, "test", &status};

};



TEST_F(ParseStateTest_607, ConstructorInitializesCorrectly_607) {

    EXPECT_EQ(parse_state.flags(), ParseFlags::NoParseFlags);

    EXPECT_EQ(parse_state.rune_max(), Runemax);

}



TEST_F(ParseStateTest_607, ConstructorWithLatin1FlagSetsRuneMax_607) {

    ParseState parse_state_latin1{ParseFlags::Latin1, "test", &status};

    EXPECT_EQ(parse_state_latin1.flags(), ParseFlags::Latin1);

    EXPECT_EQ(parse_state_latin1.rune_max(), 0xFF);

}



TEST_F(ParseStateTest_607, PushLiteralReturnsTrueOnSuccess_607) {

    EXPECT_TRUE(parse_state.PushLiteral('a'));

}



TEST_F(ParseStateTest_607, PushSimpleOpReturnsTrueOnSuccess_607) {

    EXPECT_TRUE(parse_state.PushSimpleOp(kRegexpStar));

}



TEST_F(ParseStateTest_607, PushCaretReturnsTrueOnSuccess_607) {

    EXPECT_TRUE(parse_state.PushCaret());

}



TEST_F(ParseStateTest_607, PushWordBoundaryReturnsTrueOnSuccess_607) {

    EXPECT_TRUE(parse_state.PushWordBoundary(true));

    EXPECT_TRUE(parse_state.PushWordBoundary(false));

}



TEST_F(ParseStateTest_607, PushDollarReturnsTrueOnSuccess_607) {

    EXPECT_TRUE(parse_state.PushDollar());

}



TEST_F(ParseStateTest_607, PushDotReturnsTrueOnSuccess_607) {

    EXPECT_TRUE(parse_state.PushDot());

}



TEST_F(ParseStateTest_607, PushRepeatOpReturnsTrueOnSuccess_607) {

    absl::string_view s = "test";

    EXPECT_TRUE(parse_state.PushRepeatOp(kRegexpStar, s, true));

    EXPECT_TRUE(parse_state.PushRepeatOp(kRegexpPlus, s, false));

}



TEST_F(ParseStateTest_607, PushRepetitionReturnsTrueOnSuccess_607) {

    absl::string_view s = "test";

    EXPECT_TRUE(parse_state.PushRepetition(1, 2, s, true));

    EXPECT_TRUE(parse_state.PushRepetition(0, -1, s, false));

}



TEST_F(ParseStateTest_607, DoLeftParenReturnsTrueOnSuccess_607) {

    absl::string_view name = "test";

    EXPECT_TRUE(parse_state.DoLeftParen(name));

}



TEST_F(ParseStateTest_607, DoLeftParenNoCaptureReturnsTrueOnSuccess_607) {

    EXPECT_TRUE(parse_state.DoLeftParenNoCapture());

}



TEST_F(ParseStateTest_607, DoVerticalBarReturnsTrueOnSuccess_607) {

    EXPECT_TRUE(parse_state.DoVerticalBar());

}



TEST_F(ParseStateTest_607, DoRightParenReturnsTrueOnSuccess_607) {

    EXPECT_TRUE(parse_state.DoRightParen());

}



TEST_F(ParseStateTest_607, FinishRegexpReturnsNonNullPointer_607) {

    Regexp* re = parse_state.FinishRegexp(nullptr);

    EXPECT_NE(re, nullptr);

}



}  // namespace re2
