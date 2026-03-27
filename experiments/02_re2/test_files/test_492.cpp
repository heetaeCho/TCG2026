#include <gtest/gtest.h>

#include "re2/parse.cc"

#include "re2/regexp.h"



using namespace re2;



class ParseStateTest_492 : public ::testing::Test {

protected:

    RegexpStatus status;

    ParseState parse_state{Regexp::NoParseFlags, "", &status};



    void SetUp() override {

        // Reset status before each test

        status = RegexpStatus();

    }

};



TEST_F(ParseStateTest_492, PushDollar_OneLineFlagSet_PushesEndText_492) {

    parse_state.flags_ |= Regexp::OneLine;

    EXPECT_TRUE(parse_state.PushDollar());

}



TEST_F(ParseStateTest_492, PushDollar_OneLineFlagNotSet_PushesEndLine_492) {

    parse_state.flags_ &= ~Regexp::OneLine;

    EXPECT_TRUE(parse_state.PushDollar());

}



TEST_F(ParseStateTest_492, PushDollar_ReturnsTrueOnSuccess_492) {

    bool result = parse_state.PushDollar();

    EXPECT_TRUE(result);

}
