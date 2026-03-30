#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/parse.cc"



using namespace re2;



class ParseStateTest_509 : public ::testing::Test {

protected:

    void SetUp() override {

        status = new RegexpStatus();

        parse_state = new Regexp::ParseState(kNoParseFlags, "", status);

    }



    void TearDown() override {

        delete parse_state;

        delete status;

    }



    RegexpStatus* status;

    Regexp::ParseState* parse_state;

};



TEST_F(ParseStateTest_509, DoCollapse_NormalOperation_509) {

    // Arrange

    Regexp* re1 = new Regexp(kRegexpLiteral, kNoParseFlags);

    Regexp* re2 = new Regexp(kRegexpLiteral, kNoParseFlags);

    parse_state->PushRegexp(re1);

    parse_state->PushRegexp(re2);



    // Act

    parse_state->DoCollapse(kConcatOp);



    // Assert

    EXPECT_EQ(parse_state->FinishRegexp()->op(), kConcatOp);

}



TEST_F(ParseStateTest_509, DoCollapse_BoundaryCondition_EmptyStack_509) {

    // Arrange & Act & Assert

    parse_state->DoCollapse(kConcatOp);  // Should not crash or change state significantly

    EXPECT_EQ(parse_state->stacktop_, nullptr);

}



TEST_F(ParseStateTest_509, DoCollapse_Exceptional_NoMarkerAtEnd_509) {

    // Arrange

    Regexp* re1 = new Regexp(kRegexpLiteral, kNoParseFlags);

    parse_state->PushRegexp(re1);



    // Act

    parse_state->DoCollapse(kConcatOp);



    // Assert

    EXPECT_NE(parse_state->stacktop_, nullptr);

}



TEST_F(ParseStateTest_509, DoCollapse_Exceptional_MultipleSameOps_509) {

    // Arrange

    Regexp* re1 = new Regexp(kRegexpLiteral, kNoParseFlags);

    Regexp* re2 = new Regexp(kRegexpLiteral, kNoParseFlags);

    Regexp* re3 = new Regexp(kRegexpLiteral, kNoParseFlags);

    parse_state->PushRegexp(re1);

    parse_state->PushRegexp(re2);

    parse_state->PushRegexp(re3);



    // Act

    parse_state->DoCollapse(kConcatOp);



    // Assert

    EXPECT_EQ(parse_state->FinishRegexp()->op(), kConcatOp);

}



TEST_F(ParseStateTest_509, DoCollapse_VerificationOfExternalInteractions_509) {

    // Arrange

    Regexp* re1 = new Regexp(kRegexpLiteral, kNoParseFlags);

    Regexp* re2 = new Regexp(kRegexpLiteral, kNoParseFlags);

    parse_state->PushRegexp(re1);

    parse_state->PushRegexp(re2);



    // Act

    parse_state->DoCollapse(kConcatOp);



    // Assert

    EXPECT_EQ(parse_state->FinishRegexp()->nsub(), 2);

}
