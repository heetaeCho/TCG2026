#include <gtest/gtest.h>

#include "re2/parse.cc"



namespace re2 {



class ParseStateTest_480 : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState state{ParseFlags{}, "test_regex", &status};

};



TEST_F(ParseStateTest_480, RuneMaxReturnsInitialValue_480) {

    EXPECT_EQ(state.rune_max(), 0);

}



TEST_F(ParseStateTest_480, PushRegexpReturnsTrueForValidInput_480) {

    Regexp* re = nullptr; // Assuming a valid Regexp object can be created and passed

    EXPECT_TRUE(state.PushRegexp(re));

}



TEST_F(ParseStateTest_480, PushLiteralReturnsTrueForValidRune_480) {

    EXPECT_TRUE(state.PushLiteral('a'));

}



TEST_F(ParseStateTest_480, PushSimpleOpReturnsTrueForValidOp_480) {

    EXPECT_TRUE(state.PushSimpleOp(kRegexpPlus));

}



TEST_F(ParseStateTest_480, PushCaretReturnsTrue_480) {

    EXPECT_TRUE(state.PushCaret());

}



TEST_F(ParseStateTest_480, PushWordBoundaryReturnsTrueForValidInput_480) {

    EXPECT_TRUE(state.PushWordBoundary(true));

    EXPECT_TRUE(state.PushWordBoundary(false));

}



TEST_F(ParseStateTest_480, PushDollarReturnsTrue_480) {

    EXPECT_TRUE(state.PushDollar());

}



TEST_F(ParseStateTest_480, PushDotReturnsTrue_480) {

    EXPECT_TRUE(state.PushDot());

}



TEST_F(ParseStateTest_480, PushRepeatOpReturnsTrueForValidInput_480) {

    EXPECT_TRUE(state.PushRepeatOp(kRegexpStar, "a", false));

}



TEST_F(ParseStateTest_480, PushRepetitionReturnsTrueForValidInput_480) {

    EXPECT_TRUE(state.PushRepetition(1, 2, "a", false));

}



TEST_F(ParseStateTest_480, IsMarkerReturnsFalseForNonMarkerOp_480) {

    EXPECT_FALSE(state.IsMarker(kRegexpPlus));

}



TEST_F(ParseStateTest_480, DoLeftParenReturnsTrueForValidName_480) {

    EXPECT_TRUE(state.DoLeftParen("name"));

}



TEST_F(ParseStateTest_480, DoLeftParenNoCaptureReturnsTrue_480) {

    EXPECT_TRUE(state.DoLeftParenNoCapture());

}



TEST_F(ParseStateTest_480, DoVerticalBarReturnsTrue_480) {

    EXPECT_TRUE(state.DoVerticalBar());

}



TEST_F(ParseStateTest_480, DoRightParenReturnsTrue_480) {

    EXPECT_TRUE(state.DoRightParen());

}



TEST_F(ParseStateTest_480, FinishRegexpReturnsNullptrForNullInput_480) {

    EXPECT_EQ(state.FinishRegexp(nullptr), nullptr);

}



TEST_F(ParseStateTest_480, DoFinishReturnsValidPointer_480) {

    EXPECT_NE(state.DoFinish(), nullptr);

}



TEST_F(ParseStateTest_480, DoConcatenationDoesNotThrow_480) {

    EXPECT_NO_THROW(state.DoConcatenation());

}



TEST_F(ParseStateTest_480, DoAlternationDoesNotThrow_480) {

    EXPECT_NO_THROW(state.DoAlternation());

}



TEST_F(ParseStateTest_480, DoCollapseDoesNotThrowForValidOp_480) {

    EXPECT_NO_THROW(state.DoCollapse(kRegexpPlus));

}



TEST_F(ParseStateTest_480, MaybeConcatStringReturnsTrueForValidInput_480) {

    EXPECT_TRUE(state.MaybeConcatString('a', ParseFlags{}));

}



TEST_F(ParseStateTest_480, ParseCCCharacterReturnsFalseForInvalidInput_480) {

    absl::string_view s = "";

    Rune r;

    EXPECT_FALSE(state.ParseCCCharacter(&s, &r, "test", &status));

}



TEST_F(ParseStateTest_480, ParseCCRangeReturnsFalseForInvalidInput_480) {

    absl::string_view s = "";

    RuneRange rr;

    EXPECT_FALSE(state.ParseCCRange(&s, &rr, "test", &status));

}



TEST_F(ParseStateTest_480, ParseCharClassReturnsFalseForInvalidInput_480) {

    absl::string_view s = "";

    Regexp* out_re;

    EXPECT_FALSE(state.ParseCharClass(&s, &out_re, &status));

}



TEST_F(ParseStateTest_480, ParsePerlFlagsReturnsFalseForInvalidInput_480) {

    absl::string_view s = "invalid";

    EXPECT_FALSE(state.ParsePerlFlags(&s));

}

} // namespace re2
