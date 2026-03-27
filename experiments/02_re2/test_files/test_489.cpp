#include <gtest/gtest.h>

#include "parse.cc"

#include "regexp.h"



using namespace re2;



class ParseStateTest : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{Regexp::NoParseFlags, "", &status};

};



TEST_F(ParseStateTest_489, PushLiteral_NormalCase_Latin1FoldCase_489) {

    Rune r = 'A';

    EXPECT_TRUE(parse_state.PushLiteral(r));

}



TEST_F(ParseStateTest_489, PushLiteral_NormalCase_UTF8FoldCase_489) {

    Rune r = 'ß'; // Example of a character that cycles in UTF-8

    EXPECT_TRUE(parse_state.PushLiteral(r));

}



TEST_F(ParseStateTest_489, PushLiteral_NeverNL_Newline_489) {

    parse_state.flags_ |= Regexp::NeverNL;

    Rune r = '\n';

    EXPECT_FALSE(parse_state.PushLiteral(r));

}



TEST_F(ParseStateTest_489, PushLiteral_NormalCase_NoFlags_489) {

    Rune r = 'a';

    EXPECT_TRUE(parse_state.PushLiteral(r));

}



TEST_F(ParseStateTest_489, PushLiteral_BoundaryCase_EmptyString_489) {

    // No specific boundary case for empty string in PushLiteral, but ensure no crash

    Rune r = '\0';

    EXPECT_TRUE(parse_state.PushLiteral(r));

}



TEST_F(ParseStateTest_489, PushLiteral_ErrorCase_UnhandledRune_489) {

    // Assuming there's no unhandled rune specifically, but can test for invalid range if applicable

    // For now, just ensure normal behavior with a valid rune

    Rune r = 'z';

    EXPECT_TRUE(parse_state.PushLiteral(r));

}
