#include <gtest/gtest.h>

#include "re2/parse.h"



namespace re2 {



class ParseStateTest : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{ParseFlags{}, "test", &status};

};



TEST_F(ParseStateTest_479, FlagsReturnsCorrectValue_479) {

    EXPECT_EQ(parse_state.flags(), ParseFlags{});

}



TEST_F(ParseStateTest_479, PushRegexp_ReturnsTrueForValidInput_479) {

    Regexp* re = nullptr; // Assuming a valid Regexp pointer is provided in actual usage

    EXPECT_TRUE(parse_state.PushRegexp(re));

}



TEST_F(ParseStateTest_479, PushLiteral_ReturnsTrueForValidRune_479) {

    Rune r = 'a';

    EXPECT_TRUE(parse_state.PushLiteral(r));

}



TEST_F(ParseStateTest_479, PushSimpleOp_ReturnsTrueForValidOp_479) {

    RegexpOp op = kRegexpNoOp; // Assuming a valid RegexpOp is provided in actual usage

    EXPECT_TRUE(parse_state.PushSimpleOp(op));

}



TEST_F(ParseStateTest_479, PushCaret_ReturnsTrue_479) {

    EXPECT_TRUE(parse_state.PushCaret());

}



TEST_F(ParseStateTest_479, PushWordBoundary_ReturnsTrueForValidInput_479) {

    bool word = true;

    EXPECT_TRUE(parse_state.PushWordBoundary(word));

}



TEST_F(ParseStateTest_479, PushDollar_ReturnsTrue_479) {

    EXPECT_TRUE(parse_state.PushDollar());

}



TEST_F(ParseStateTest_479, PushDot_ReturnsTrue_479) {

    EXPECT_TRUE(parse_state.PushDot());

}



TEST_F(ParseStateTest_479, PushRepeatOp_ReturnsTrueForValidInput_479) {

    RegexpOp op = kRegexpStar; // Assuming a valid RegexpOp is provided in actual usage

    absl::string_view s = "test";

    bool nongreedy = false;

    EXPECT_TRUE(parse_state.PushRepeatOp(op, s, nongreedy));

}



TEST_F(ParseStateTest_479, PushRepetition_ReturnsTrueForValidInput_479) {

    int min = 1;

    int max = 2;

    absl::string_view s = "test";

    bool nongreedy = false;

    EXPECT_TRUE(parse_state.PushRepetition(min, max, s, nongreedy));

}



TEST_F(ParseStateTest_479, IsMarker_ReturnsFalseForInvalidOp_479) {

    RegexpOp op = kRegexpNoOp; // Assuming an invalid RegexpOp is provided in actual usage

    EXPECT_FALSE(parse_state.IsMarker(op));

}



TEST_F(ParseStateTest_479, DoLeftParen_ReturnsTrueForValidName_479) {

    absl::string_view name = "test";

    EXPECT_TRUE(parse_state.DoLeftParen(name));

}



TEST_F(ParseStateTest_479, DoLeftParenNoCapture_ReturnsTrue_479) {

    EXPECT_TRUE(parse_state.DoLeftParenNoCapture());

}



TEST_F(ParseStateTest_479, DoVerticalBar_ReturnsTrue_479) {

    EXPECT_TRUE(parse_state.DoVerticalBar());

}



TEST_F(ParseStateTest_479, DoRightParen_ReturnsTrue_479) {

    EXPECT_TRUE(parse_state.DoRightParen());

}



TEST_F(ParseStateTest_479, FinishRegexp_ReturnsNullptrForNullInput_479) {

    Regexp* re = nullptr;

    EXPECT_EQ(parse_state.FinishRegexp(re), nullptr);

}



TEST_F(ParseStateTest_479, DoFinish_ReturnsNullptr_479) {

    EXPECT_EQ(parse_state.DoFinish(), nullptr);

}



TEST_F(ParseStateTest_479, DoConcatenation_NoCrash_479) {

    EXPECT_NO_THROW(parse_state.DoConcatenation());

}



TEST_F(ParseStateTest_479, DoAlternation_NoCrash_479) {

    EXPECT_NO_THROW(parse_state.DoAlternation());

}



TEST_F(ParseStateTest_479, DoCollapse_NoCrashForValidOp_479) {

    RegexpOp op = kRegexpNoOp; // Assuming a valid RegexpOp is provided in actual usage

    EXPECT_NO_THROW(parse_state.DoCollapse(op));

}



TEST_F(ParseStateTest_479, MaybeConcatString_ReturnsTrueForValidInput_479) {

    int r = 'a';

    ParseFlags flags{};

    EXPECT_TRUE(parse_state.MaybeConcatString(r, flags));

}



TEST_F(ParseStateTest_479, ParseCCCharacter_ReturnsFalseForInvalidInput_479) {

    absl::string_view s = "";

    Rune* rp = nullptr;

    absl::string_view whole_class = "test";

    EXPECT_FALSE(parse_state.ParseCCCharacter(&s, rp, whole_class, &status));

}



TEST_F(ParseStateTest_479, ParseCCRange_ReturnsFalseForInvalidInput_479) {

    absl::string_view s = "";

    RuneRange* rr = nullptr;

    absl::string_view whole_class = "test";

    EXPECT_FALSE(parse_state.ParseCCRange(&s, rr, whole_class, &status));

}



TEST_F(ParseStateTest_479, ParseCharClass_ReturnsFalseForInvalidInput_479) {

    absl::string_view s = "";

    Regexp** out_re = nullptr;

    EXPECT_FALSE(parse_state.ParseCharClass(&s, out_re, &status));

}



TEST_F(ParseStateTest_479, ParsePerlFlags_ReturnsFalseForInvalidInput_479) {

    absl::string_view s = "";

    EXPECT_FALSE(parse_state.ParsePerlFlags(&s));

}



} // namespace re2
