#include <gtest/gtest.h>

#include "re2/re2.h"

#include "re2/regexp.h"



using namespace re2;



class RegexpErrorToRE2Test_240 : public ::testing::Test {

protected:

    // No additional setup required for this function as it is static and self-contained.

};



TEST_F(RegexpErrorToRE2Test_240, SuccessCase_240) {

    EXPECT_EQ(RE2::NoError, RegexpErrorToRE2(kRegexpSuccess));

}



TEST_F(RegexpErrorToRE2Test_240, InternalErrorCase_240) {

    EXPECT_EQ(RE2::ErrorInternal, RegexpErrorToRE2(kRegexpInternalError));

}



TEST_F(RegexpErrorToRE2Test_240, BadEscapeCase_240) {

    EXPECT_EQ(RE2::ErrorBadEscape, RegexpErrorToRE2(kRegexpBadEscape));

}



TEST_F(RegexpErrorToRE2Test_240, BadCharClassCase_240) {

    EXPECT_EQ(RE2::ErrorBadCharClass, RegexpErrorToRE2(kRegexpBadCharClass));

}



TEST_F(RegexpErrorToRE2Test_240, BadCharRangeCase_240) {

    EXPECT_EQ(RE2::ErrorBadCharRange, RegexpErrorToRE2(kRegexpBadCharRange));

}



TEST_F(RegexpErrorToRE2Test_240, MissingBracketCase_240) {

    EXPECT_EQ(RE2::ErrorMissingBracket, RegexpErrorToRE2(kRegexpMissingBracket));

}



TEST_F(RegexpErrorToRE2Test_240, MissingParenCase_240) {

    EXPECT_EQ(RE2::ErrorMissingParen, RegexpErrorToRE2(kRegexpMissingParen));

}



TEST_F(RegexpErrorToRE2Test_240, UnexpectedParenCase_240) {

    EXPECT_EQ(RE2::ErrorUnexpectedParen, RegexpErrorToRE2(kRegexpUnexpectedParen));

}



TEST_F(RegexpErrorToRE2Test_240, TrailingBackslashCase_240) {

    EXPECT_EQ(RE2::ErrorTrailingBackslash, RegexpErrorToRE2(kRegexpTrailingBackslash));

}



TEST_F(RegexpErrorToRE2Test_240, RepeatArgumentCase_240) {

    EXPECT_EQ(RE2::ErrorRepeatArgument, RegexpErrorToRE2(kRegexpRepeatArgument));

}



TEST_F(RegexpErrorToRE2Test_240, RepeatSizeCase_240) {

    EXPECT_EQ(RE2::ErrorRepeatSize, RegexpErrorToRE2(kRegexpRepeatSize));

}



TEST_F(RegexpErrorToRE2Test_240, RepeatOpCase_240) {

    EXPECT_EQ(RE2::ErrorRepeatOp, RegexpErrorToRE2(kRegexpRepeatOp));

}



TEST_F(RegexpErrorToRE2Test_240, BadPerlOpCase_240) {

    EXPECT_EQ(RE2::ErrorBadPerlOp, RegexpErrorToRE2(kRegexpBadPerlOp));

}



TEST_F(RegexpErrorToRE2Test_240, BadUTF8Case_240) {

    EXPECT_EQ(RE2::ErrorBadUTF8, RegexpErrorToRE2(kRegexpBadUTF8));

}



TEST_F(RegexpErrorToRE2Test_240, BadNamedCaptureCase_240) {

    EXPECT_EQ(RE2::ErrorBadNamedCapture, RegexpErrorToRE2(kRegexpBadNamedCapture));

}



// Test case for an unknown status code

TEST_F(RegexpErrorToRE2Test_240, UnknownStatusCodeCase_240) {

    EXPECT_EQ(RE2::ErrorInternal, RegexpErrorToRE2(static_cast<RegexpStatusCode>(100)));

}
