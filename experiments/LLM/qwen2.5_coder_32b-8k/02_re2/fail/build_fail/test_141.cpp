#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpStatusTest : public ::testing::Test {

protected:

    RegexpStatus status;

};



TEST_F(RegexpStatusTest_NormalOperation_141, InitialStateIsSuccess_141) {

    EXPECT_TRUE(status.ok());

}



TEST_F(RegexpStatusTest_NormalOperation_141, SetCodeChangesOkStatus_141) {

    status.set_code(kRegexpInternalError);

    EXPECT_FALSE(status.ok());



    status.set_code(kRegexpSuccess);

    EXPECT_TRUE(status.ok());

}



TEST_F(RegexpStatusTest_BoundaryConditions_141, SetInvalidErrorCodeDoesNotCrash_141) {

    status.set_code(static_cast<RegexpStatusCode>(-1));

    EXPECT_FALSE(status.ok());



    status.set_code(static_cast<RegexpStatusCode>(20));

    EXPECT_FALSE(status.ok());

}



TEST_F(RegexpStatusTest_ErrorCases_141, SetSpecificErrorCodesSetsCorrectly_141) {

    status.set_code(kRegexpBadEscape);

    EXPECT_EQ(status.code(), kRegexpBadEscape);



    status.set_code(kRegexpBadCharClass);

    EXPECT_EQ(status.code(), kRegexpBadCharClass);



    status.set_code(kRegexpBadCharRange);

    EXPECT_EQ(status.code(), kRegexpBadCharRange);



    status.set_code(kRegexpMissingBracket);

    EXPECT_EQ(status.code(), kRegexpMissingBracket);



    status.set_code(kRegexpMissingParen);

    EXPECT_EQ(status.code(), kRegexpMissingParen);



    status.set_code(kRegexpUnexpectedParen);

    EXPECT_EQ(status.code(), kRegexpUnexpectedParen);



    status.set_code(kRegexpTrailingBackslash);

    EXPECT_EQ(status.code(), kRegexpTrailingBackslash);



    status.set_code(kRegexpRepeatArgument);

    EXPECT_EQ(status.code(), kRegexpRepeatArgument);



    status.set_code(kRegexpRepeatSize);

    EXPECT_EQ(status.code(), kRegexpRepeatSize);



    status.set_code(kRegexpRepeatOp);

    EXPECT_EQ(status.code(), kRegexpRepeatOp);



    status.set_code(kRegexpBadPerlOp);

    EXPECT_EQ(status.code(), kRegexpBadPerlOp);



    status.set_code(kRegexpBadUTF8);

    EXPECT_EQ(status.code(), kRegexpBadUTF8);



    status.set_code(kRegexpBadNamedCapture);

    EXPECT_EQ(status.code(), kRegexpBadNamedCapture);

}



TEST_F(RegexpStatusTest_ErrorCases_141, SetErrorArgReflectsInText_141) {

    status.set_error_arg("test error");

    EXPECT_NE(status.Text().find("test error"), std::string::npos);

}
