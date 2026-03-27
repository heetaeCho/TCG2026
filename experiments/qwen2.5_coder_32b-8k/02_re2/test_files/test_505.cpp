#include <gtest/gtest.h>

#include "regexp.h"

#include "parse.cc"



using namespace re2;



class ParseStateTest_505 : public ::testing::Test {

protected:

    void SetUp() override {

        status = new RegexpStatus();

        parse_state = new ParseState(ParseFlags(0), absl::string_view(""), status);

    }



    void TearDown() override {

        delete parse_state;

        delete status;

    }



    Regexp* CreateRegexpMock() {

        return new Regexp(kRegexpOpLiteral, ParseFlags(0));

    }



    RegexpStatus* status;

    ParseState* parse_state;

};



TEST_F(ParseStateTest_505, DoFinish_NoParentheses_505) {

    // Setup

    Regexp* re = CreateRegexpMock();

    parse_state->PushRegexp(re);



    // Action

    Regexp* result = parse_state->DoFinish();



    // Verify

    EXPECT_EQ(result, re);

    EXPECT_TRUE(status->ok());

}



TEST_F(ParseStateTest_505, DoFinish_MissingParentheses_505) {

    // Setup

    Regexp* re = CreateRegexpMock();

    re->down_ = CreateRegexpMock(); // Artificially set to simulate missing parenthesis

    parse_state->PushRegexp(re);



    // Action

    Regexp* result = parse_state->DoFinish();



    // Verify

    EXPECT_EQ(result, nullptr);

    EXPECT_FALSE(status->ok());

    EXPECT_EQ(status->code(), kRegexpMissingParen);

}



TEST_F(ParseStateTest_505, DoFinish_EmptyStack_505) {

    // Setup & Action

    Regexp* result = parse_state->DoFinish();



    // Verify

    EXPECT_EQ(result, nullptr);

    EXPECT_TRUE(status->ok());

}
