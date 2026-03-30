#include <gtest/gtest.h>

#include "re2/parse.cc"

#include "re2/regexp.h"



using namespace re2;



class ParseStateTest_499 : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{NoParseFlags, "", &status};

};



TEST_F(ParseStateTest_499, PushRepetition_ValidRange_499) {

    EXPECT_TRUE(parse_state.PushRepetition(2, 5, "a", false));

}



TEST_F(ParseStateTest_499, PushRepetition_MaxRepeatCountExceeded_499) {

    re2::maximum_repeat_count = 3;

    EXPECT_FALSE(parse_state.PushRepetition(1, 4, "a", false));

    EXPECT_EQ(status.code(), kRegexpRepeatSize);

}



TEST_F(ParseStateTest_499, PushRepetition_MinGreaterThanMax_499) {

    EXPECT_FALSE(parse_state.PushRepetition(5, 2, "a", false));

    EXPECT_EQ(status.code(), kRegexpRepeatSize);

}



TEST_F(ParseStateTest_499, PushRepetition_EmptyStack_499) {

    parse_state.stacktop_ = nullptr;

    EXPECT_FALSE(parse_state.PushRepetition(1, 3, "a", false));

    EXPECT_EQ(status.code(), kRegexpRepeatArgument);

}



TEST_F(ParseStateTest_499, PushRepetition_MarkerAtTop_499) {

    Regexp marker{kRegexpEmptyMatch, NoParseFlags};

    parse_state.stacktop_ = &marker;

    EXPECT_FALSE(parse_state.PushRepetition(1, 3, "a", false));

    EXPECT_EQ(status.code(), kRegexpRepeatArgument);

}



TEST_F(ParseStateTest_499, PushRepetition_NonGreedyFlag_499) {

    EXPECT_TRUE(parse_state.PushRepetition(2, 5, "a", true));

    EXPECT_NE(parse_state.flags_ & NonGreedy, 0);

}



TEST_F(ParseStateTest_499, PushRepetition_RepetitionWalkerValidation_499) {

    re2::maximum_repeat_count = 1;

    Regexp re{kRegexpRepeat, NoParseFlags};

    parse_state.stacktop_ = &re;

    EXPECT_FALSE(parse_state.PushRepetition(2, 5, "a", false));

    EXPECT_EQ(status.code(), kRegexpRepeatSize);

}



TEST_F(ParseStateTest_499, PushRepetition_RepetitionWalkerSuccess_499) {

    re2::maximum_repeat_count = 10;

    Regexp re{kRegexpRepeat, NoParseFlags};

    parse_state.stacktop_ = &re;

    EXPECT_TRUE(parse_state.PushRepetition(2, 5, "a", false));

}
