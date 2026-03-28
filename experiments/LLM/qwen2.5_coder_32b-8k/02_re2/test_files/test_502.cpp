#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/parse.cc"



using namespace re2;

using ::testing::Eq;



class ParseStateTest : public ::testing::Test {

protected:

    RegexpStatus status_;

    ParseState parse_state_{ParseFlags::FoldCase, "test", &status_};

};



TEST_F(ParseStateTest, DoLeftParenNoCapture_ReturnsTrue_502) {

    EXPECT_TRUE(parse_state_.DoLeftParenNoCapture());

}



TEST_F(ParseStateTest, DoLeftParenNoCapture_CreatesRegexpWithCorrectOp_502) {

    parse_state_.DoLeftParenNoCapture();

    Regexp* re = parse_state_.FinishRegexp(nullptr);

    EXPECT_EQ(re->op(), kLeftParen);

    re->Decref();

}



TEST_F(ParseStateTest, DoLeftParenNoCapture_CreatesRegexpWithCapMinusOne_502) {

    parse_state_.DoLeftParenNoCapture();

    Regexp* re = parse_state_.FinishRegexp(nullptr);

    EXPECT_EQ(re->cap(), -1);

    re->Decref();

}



TEST_F(ParseStateTest, DoLeftParenNoCapture_IncrementsNcap_502) {

    int initial_ncap = parse_state_.ncap_;

    parse_state_.DoLeftParenNoCapture();

    EXPECT_EQ(parse_state_.ncap_, initial_ncap + 1);

}
