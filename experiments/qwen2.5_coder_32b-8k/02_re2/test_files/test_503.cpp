#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/parse.h"

#include "re2/regexp.h"



using namespace re2;



class ParseStateTest_503 : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{NoParseFlags, "", &status};

};



TEST_F(ParseStateTest_503, DoVerticalBar_NormalOperation_503) {

    // Setup

    Regexp* r1 = new Regexp(kRegexpLiteral, NoParseFlags);

    Regexp* r2 = new Regexp(kRegexpAnyChar, NoParseFlags);



    parse_state.PushRegexp(r1);

    parse_state.PushRegexp(r2);

    parse_state.DoConcatenation();



    // Test

    bool result = parse_state.DoVerticalBar();



    // Verify

    EXPECT_TRUE(result);

    ASSERT_NE(parse_state.stacktop_, nullptr);

    EXPECT_EQ(parse_state.stacktop_->op(), kVerticalBar);

}



TEST_F(ParseStateTest_503, DoVerticalBar_BoundaryConditions_503) {

    // Test with no elements on the stack

    bool result = parse_state.DoVerticalBar();

    EXPECT_FALSE(result);



    // Test with one element on the stack

    Regexp* r1 = new Regexp(kRegexpLiteral, NoParseFlags);

    parse_state.PushRegexp(r1);

    result = parse_state.DoVerticalBar();

    EXPECT_FALSE(result);

}



TEST_F(ParseStateTest_503, DoVerticalBar_ExceptionalCases_503) {

    // Test with invalid elements

    Regexp* r1 = new Regexp(kRegexpLiteral, NoParseFlags);

    Regexp* r2 = new Regexp(static_cast<RegexpOp>(kMaxRegexpOp + 3), NoParseFlags);



    parse_state.PushRegexp(r1);

    parse_state.PushRegexp(r2);

    parse_state.DoConcatenation();



    bool result = parse_state.DoVerticalBar();

    EXPECT_FALSE(result);

}



TEST_F(ParseStateTest_503, DoVerticalBar_VerifyExternalInteractions_503) {

    // Setup

    Regexp* r1 = new Regexp(kRegexpLiteral, NoParseFlags);

    Regexp* r2 = new Regexp(kRegexpAnyChar, NoParseFlags);



    parse_state.PushRegexp(r1);

    parse_state.PushRegexp(r2);

    parse_state.DoConcatenation();



    // Mocking is not required here as we are only testing the interactions within DoVerticalBar



    // Test

    bool result = parse_state.DoVerticalBar();



    // Verify

    EXPECT_TRUE(result);

    ASSERT_NE(parse_state.stacktop_, nullptr);

    EXPECT_EQ(parse_state.stacktop_->op(), kVerticalBar);



    // Check if Decref is called correctly

    EXPECT_EQ(r1->Ref(), 0);

    EXPECT_EQ(r2->Ref(), 1);  // r2 becomes part of the vertical bar, so its reference count should remain

}
