#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/parse.cc"



using namespace re2;

using ::testing::Return;



class ParseStateTest : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{ParseFlags::NoFlag, absl::string_view(""), &status};

};



TEST_F(ParseStateTest, PushRegexpNormalOperation_481) {

    Regexp* re = new Regexp(RegexpOp::kLiteral, ParseFlags::NoFlag);

    EXPECT_TRUE(parse_state.PushRegexp(re));

}



TEST_F(ParseStateTest, PushLiteralBoundaryCondition_481) {

    EXPECT_TRUE(parse_state.PushLiteral(static_cast<Rune>(0)));

    EXPECT_TRUE(parse_state.PushLiteral(std::numeric_limits<Rune>::max()));

}



TEST_F(ParseStateTest, PushSimpleOpNormalOperation_481) {

    EXPECT_TRUE(parse_state.PushSimpleOp(RegexpOp::kLiteral));

    EXPECT_TRUE(parse_state.PushSimpleOp(RegexpOp::kConcat));

}



TEST_F(ParseStateTest, PushCaretNormalOperation_481) {

    EXPECT_TRUE(parse_state.PushCaret());

}



TEST_F(ParseStateTest, PushWordBoundaryNormalOperation_481) {

    EXPECT_TRUE(parse_state.PushWordBoundary(true));

    EXPECT_TRUE(parse_state.PushWordBoundary(false));

}



TEST_F(ParseStateTest, PushDollarNormalOperation_481) {

    EXPECT_TRUE(parse_state.PushDollar());

}



TEST_F(ParseStateTest, PushDotNormalOperation_481) {

    EXPECT_TRUE(parse_state.PushDot());

}



TEST_F(ParseStateTest, PushRepeatOpNormalOperation_481) {

    absl::string_view s = "a";

    EXPECT_TRUE(parse_state.PushRepeatOp(RegexpOp::kStar, s, false));

    EXPECT_TRUE(parse_state.PushRepeatOp(RegexpOp::kPlus, s, true));

}



TEST_F(ParseStateTest, PushRepetitionNormalOperation_481) {

    absl::string_view s = "a";

    EXPECT_TRUE(parse_state.PushRepetition(0, 2, s, false));

    EXPECT_TRUE(parse_state.PushRepetition(1, 3, s, true));

}



TEST_F(ParseStateTest, IsMarkerBoundaryCondition_481) {

    EXPECT_FALSE(parse_state.IsMarker(RegexpOp::kLiteral));

    EXPECT_TRUE(parse_state.IsMarker(kLeftParen));

}



TEST_F(ParseStateTest, DoLeftParenNormalOperation_481) {

    absl::string_view name = "test";

    EXPECT_TRUE(parse_state.DoLeftParen(name));

}



TEST_F(ParseStateTest, DoLeftParenNoCaptureNormalOperation_481) {

    EXPECT_TRUE(parse_state.DoLeftParenNoCapture());

}



TEST_F(ParseStateTest, DoVerticalBarNormalOperation_481) {

    EXPECT_TRUE(parse_state.DoVerticalBar());

}



TEST_F(ParseStateTest, DoRightParenNormalOperation_481) {

    EXPECT_TRUE(parse_state.DoRightParen());

}



TEST_F(ParseStateTest, DoFinishNormalOperation_481) {

    Regexp* re = new Regexp(RegexpOp::kLiteral, ParseFlags::NoFlag);

    parse_state.PushRegexp(re);

    EXPECT_NE(nullptr, parse_state.DoFinish());

}



TEST_F(ParseStateTest, FinishRegexpNormalOperation_481) {

    Regexp* re = new Regexp(RegexpOp::kLiteral, ParseFlags::NoFlag);

    EXPECT_NE(nullptr, parse_state.FinishRegexp(re));

}



TEST_F(ParseStateTest, DoConcatenationNormalOperation_481) {

    parse_state.DoConcatenation();

    SUCCEED();  // If it doesn't crash, it's successful.

}



TEST_F(ParseStateTest, DoAlternationNormalOperation_481) {

    parse_state.DoAlternation();

    SUCCEED();  // If it doesn't crash, it's successful.

}



TEST_F(ParseStateTest, DoCollapseNormalOperation_481) {

    parse_state.DoCollapse(RegexpOp::kConcat);

    SUCCEED();  // If it doesn't crash, it's successful.

}



TEST_F(ParseStateTest, MaybeConcatStringBoundaryCondition_481) {

    EXPECT_TRUE(parse_state.MaybeConcatString(static_cast<int>(0), ParseFlags::NoFlag));

    EXPECT_TRUE(parse_state.MaybeConcatString(std::numeric_limits<int>::max(), ParseFlags::NoFlag));

}
