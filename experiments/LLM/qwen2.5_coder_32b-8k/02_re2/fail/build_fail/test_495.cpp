#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/parse.cc"



using namespace re2;



class ParseStateTest : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{Regexp::NoParseFlags, "", &status};

};



TEST_F(ParseStateTest_495, PushRepeatOp_NormalOperation_495) {

    // Arrange

    Regexp* re = new Regexp(RegexpOp::kRegexpLiteral, Regexp::NoParseFlags);

    parse_state.PushRegexp(re);



    // Act & Assert

    EXPECT_TRUE(parse_state.PushRepeatOp(RegexpOp::kRegexpStar, "s", false));

}



TEST_F(ParseStateTest_495, PushRepeatOp_EmptyStack_495) {

    // Arrange

    // Stack is initially empty



    // Act & Assert

    EXPECT_FALSE(parse_state.PushRepeatOp(RegexpOp::kRegexpStar, "s", false));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpRepeatArgument);

}



TEST_F(ParseStateTest_495, PushRepeatOp_MarkerOnTop_495) {

    // Arrange

    Regexp* re = new Regexp(RegexpOp::kMaxRegexpOp, Regexp::NoParseFlags);  // Assuming kMaxRegexpOp is used as a marker

    parse_state.PushRegexp(re);



    // Act & Assert

    EXPECT_FALSE(parse_state.PushRepeatOp(RegexpOp::kRegexpStar, "s", false));

    EXPECT_EQ(status.code(), RegexpStatusCode::kRegexpRepeatArgument);

}



TEST_F(ParseStateTest_495, PushRepeatOp_SameOperatorAndFlags_495) {

    // Arrange

    Regexp* re = new Regexp(RegexpOp::kRegexpStar, Regexp::NoParseFlags);

    parse_state.PushRegexp(re);



    // Act & Assert

    EXPECT_TRUE(parse_state.PushRepeatOp(RegexpOp::kRegexpStar, "s", false));

}



TEST_F(ParseStateTest_495, PushRepeatOp_NonGreedyFlag_495) {

    // Arrange

    Regexp* re = new Regexp(RegexpOp::kRegexpPlus, Regexp::NoParseFlags);

    parse_state.PushRegexp(re);



    // Act & Assert

    EXPECT_TRUE(parse_state.PushRepeatOp(RegexpOp::kRegexpStar, "s", true));

}



TEST_F(ParseStateTest_495, PushRepeatOp_SameOperatorDifferentFlags_495) {

    // Arrange

    Regexp* re = new Regexp(RegexpOp::kRegexpQuest, Regexp::NoParseFlags);

    parse_state.PushRegexp(re);



    // Act & Assert

    EXPECT_TRUE(parse_state.PushRepeatOp(RegexpOp::kRegexpStar, "s", false));

}



TEST_F(ParseStateTest_495, PushRepeatOp_ReduceToStar_495) {

    // Arrange

    Regexp* re = new Regexp(RegexpOp::kRegexpPlus, Regexp::NoParseFlags);

    parse_state.PushRegexp(re);



    // Act & Assert

    EXPECT_TRUE(parse_state.PushRepeatOp(RegexpOp::kRegexpQuest, "s", false));

}



TEST_F(ParseStateTest_495, PushRepeatOp_ReduceToStarNonGreedy_495) {

    // Arrange

    Regexp* re = new Regexp(RegexpOp::kRegexpPlus, Regexp::NoParseFlags);

    parse_state.PushRegexp(re);



    // Act & Assert

    EXPECT_TRUE(parse_state.PushRepeatOp(RegexpOp::kRegexpQuest, "s", true));

}
