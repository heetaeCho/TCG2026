#include <gtest/gtest.h>

#include "regexp.h"

#include "parse.cc"



using namespace re2;



class ParseStateTest : public ::testing::Test {

protected:

    void SetUp() override {

        status_ = new RegexpStatus();

        parse_state_ = new ParseState(0, "", status_);

    }



    void TearDown() override {

        delete parse_state_;

        delete status_;

    }



    Regexp* CreateMockRegexp(int op) {

        auto* regexp = new Regexp(static_cast<RegexpOp>(op), 0);

        return regexp;

    }



    RegexpStatus* status_;

    ParseState* parse_state_;

};



TEST_F(ParseStateTest_504, DoRightParen_SuccessfulCapture_504) {

    Regexp* r1 = CreateMockRegexp(kMaxRegexpOp + 2); // Simulate a valid capture group

    Regexp* r2 = CreateMockRegexp(kLeftParen);

    r2->down_ = r1;

    parse_state_->stacktop_ = r2;



    EXPECT_TRUE(parse_state_->DoRightParen());

    EXPECT_EQ(status_->code(), kRegexpSuccess);



    delete r1;

    delete r2;

}



TEST_F(ParseStateTest_504, DoRightParen_NoCaptureGroup_504) {

    Regexp* r1 = CreateMockRegexp(kMaxRegexpOp + 2); // Simulate a non-capture group

    parse_state_->stacktop_ = r1;



    EXPECT_TRUE(parse_state_->DoRightParen());

    EXPECT_EQ(status_->code(), kRegexpSuccess);



    delete r1;

}



TEST_F(ParseStateTest_504, DoRightParen_MissingLeftParen_504) {

    Regexp* r1 = CreateMockRegexp(kMaxRegexpOp + 2); // Simulate a non-capture group

    parse_state_->stacktop_ = r1;



    EXPECT_FALSE(parse_state_->DoRightParen());

    EXPECT_EQ(status_->code(), kRegexpUnexpectedParen);



    delete r1;

}



TEST_F(ParseStateTest_504, DoRightParen_EmptyStack_504) {

    EXPECT_FALSE(parse_state_->DoRightParen());

    EXPECT_EQ(status_->code(), kRegexpUnexpectedParen);

}
