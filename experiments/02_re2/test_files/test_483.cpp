#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regexp.h"

#include "parse.cc"



using namespace re2;



class ParseStateTest_483 : public ::testing::Test {

protected:

    RegexpStatus status_;

    ParseState parse_state_{NoParseFlags, "", &status_};

};



TEST_F(ParseStateTest_483, PushRegexp_LiteralCharClassWithOneRune_SimplifiedToLiteral_483) {

    CharClassBuilder ccb;

    ccb.AddRange('a', 'a');

    auto re = Regexp::NewCharClass(&ccb, NoParseFlags);

    EXPECT_TRUE(parse_state_.PushRegexp(re));

    EXPECT_EQ(kRegexpLiteral, parse_state_.stacktop_->op());

    EXPECT_EQ('a', parse_state_.stacktop_->rune());

}



TEST_F(ParseStateTest_483, PushRegexp_LiteralCharClassWithTwoRuneUpperCaseLowerCase_SimplifiedToLiteralLowerCaseFoldCase_483) {

    CharClassBuilder ccb;

    ccb.AddRange('A', 'A');

    ccb.AddRange('a', 'a');

    auto re = Regexp::NewCharClass(&ccb, NoParseFlags);

    EXPECT_TRUE(parse_state_.PushRegexp(re));

    EXPECT_EQ(kRegexpLiteral, parse_state_.stacktop_->op());

    EXPECT_EQ('a', parse_state_.stacktop_->rune());

    EXPECT_EQ(FoldCase, parse_state_.stacktop_->parse_flags());

}



TEST_F(ParseStateTest_483, PushRegexp_CharClassWithMoreThanTwoRunes_NotSimplified_483) {

    CharClassBuilder ccb;

    ccb.AddRange('a', 'b');

    ccb.AddRange('c', 'd');

    auto re = Regexp::NewCharClass(&ccb, NoParseFlags);

    EXPECT_TRUE(parse_state_.PushRegexp(re));

    EXPECT_EQ(kRegexpCharClass, parse_state_.stacktop_->op());

}



TEST_F(ParseStateTest_483, PushRegexp_CharClassWithOneRuneAboveRuneMax_RemovedAboveSimplifiedToLiteral_483) {

    CharClassBuilder ccb;

    ccb.AddRange('a', 'z');

    auto re = Regexp::NewCharClass(&ccb, NoParseFlags);

    parse_state_.rune_max_ = 'm';

    EXPECT_TRUE(parse_state_.PushRegexp(re));

    EXPECT_EQ(kRegexpLiteral, parse_state_.stacktop_->op());

    EXPECT_EQ('a', parse_state_.stacktop_->rune());

}



TEST_F(ParseStateTest_483, PushRegexp_MarkerOp_NotSimplified_483) {

    auto re = Regexp::NewLiteral('a', NoParseFlags);

    re->op_ = kRegexpBeginLine;

    EXPECT_TRUE(parse_state_.PushRegexp(re));

    EXPECT_EQ(kRegexpBeginLine, parse_state_.stacktop_->op());

}



TEST_F(ParseStateTest_483, PushRegexp_NormalOperation_ReturnsTrueAndUpdatesStackTop_483) {

    auto re = Regexp::NewLiteral('a', NoParseFlags);

    EXPECT_TRUE(parse_state_.PushRegexp(re));

    EXPECT_EQ(kRegexpLiteral, parse_state_.stacktop_->op());

    EXPECT_EQ('a', parse_state_.stacktop_->rune());

}



TEST_F(ParseStateTest_483, PushRegexp_ExceptionalCase_ReturnsFalseAndSetsStatus_483) {

    // Assuming there is an exceptional case scenario like a nullptr input

    Regexp* re = nullptr;

    EXPECT_FALSE(parse_state_.PushRegexp(re));

    // Additional checks on status can be done if needed based on actual implementation behavior

}
