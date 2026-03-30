#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "parse.cc"

#include "regexp.h"



using namespace re2;

using ::testing::Eq;



class ParseStateTest_530 : public ::testing::Test {

protected:

    RegexpStatus status_;

    ParseFlags flags_ = 0;

    absl::string_view whole_regexp_ = "";

    ParseState parse_state_{flags_, whole_regexp_, &status_};

};



TEST_F(ParseStateTest_530, ParseCCRange_SingleCharacter_530) {

    absl::string_view s = "a";

    RuneRange rr;

    EXPECT_TRUE(parse_state_.ParseCCRange(&s, &rr, "[a]", &status_));

    EXPECT_EQ(rr.lo, 'a');

    EXPECT_EQ(rr.hi, 'a');

}



TEST_F(ParseStateTest_530, ParseCCRange_CharacterRange_530) {

    absl::string_view s = "a-z";

    RuneRange rr;

    EXPECT_TRUE(parse_state_.ParseCCRange(&s, &rr, "[a-z]", &status_));

    EXPECT_EQ(rr.lo, 'a');

    EXPECT_EQ(rr.hi, 'z');

}



TEST_F(ParseStateTest_530, ParseCCRange_CharacterRangeWithDashAtEnd_530) {

    absl::string_view s = "a-";

    RuneRange rr;

    EXPECT_TRUE(parse_state_.ParseCCRange(&s, &rr, "[a-]", &status_));

    EXPECT_EQ(rr.lo, 'a');

    EXPECT_EQ(rr.hi, '-');

}



TEST_F(ParseStateTest_530, ParseCCRange_CharacterRangeWithDashAtStart_530) {

    absl::string_view s = "-z";

    RuneRange rr;

    EXPECT_TRUE(parse_state_.ParseCCRange(&s, &rr, "[-z]", &status_));

    EXPECT_EQ(rr.lo, '-');

    EXPECT_EQ(rr.hi, 'z');

}



TEST_F(ParseStateTest_530, ParseCCRange_CharacterRangeReversedOrder_530) {

    absl::string_view s = "z-a";

    RuneRange rr;

    EXPECT_FALSE(parse_state_.ParseCCRange(&s, &rr, "[z-a]", &status_));

    EXPECT_EQ(status_.code(), kRegexpBadCharRange);

}



TEST_F(ParseStateTest_530, ParseCCRange_EmptyString_530) {

    absl::string_view s = "";

    RuneRange rr;

    EXPECT_FALSE(parse_state_.ParseCCRange(&s, &rr, "[]", &status_));

    EXPECT_EQ(status_.code(), kRegexpBadCharRange);

}



TEST_F(ParseStateTest_530, ParseCCRange_SingleDashOnly_530) {

    absl::string_view s = "-";

    RuneRange rr;

    EXPECT_TRUE(parse_state_.ParseCCRange(&s, &rr, "[-]", &status_));

    EXPECT_EQ(rr.lo, '-');

    EXPECT_EQ(rr.hi, '-');

}



TEST_F(ParseStateTest_530, ParseCCRange_DashFollowedByCloseBracket_530) {

    absl::string_view s = "-]";

    RuneRange rr;

    EXPECT_TRUE(parse_state_.ParseCCRange(&s, &rr, "[-]", &status_));

    EXPECT_EQ(rr.lo, '-');

    EXPECT_EQ(rr.hi, '-');

}
