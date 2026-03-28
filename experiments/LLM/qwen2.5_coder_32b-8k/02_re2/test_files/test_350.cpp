#include <gtest/gtest.h>

#include "re2/regexp.h"



namespace {



class RegexpStatusTest_350 : public ::testing::Test {

protected:

    re2::RegexpStatus status_;

};



TEST_F(RegexpStatusTest_350, CodeText_ReturnsCorrectStringForValidCode_350) {

    EXPECT_EQ(status_.CodeText(re2::kRegexpSuccess), "no error");

    EXPECT_EQ(status_.CodeText(re2::kRegexpInternalError), "unexpected error");

    EXPECT_EQ(status_.CodeText(re2::kRegexpBadEscape), "invalid escape sequence");

    EXPECT_EQ(status_.CodeText(re2::kRegexpBadCharClass), "invalid character class");

    EXPECT_EQ(status_.CodeText(re2::kRegexpBadCharRange), "invalid character class range");

    EXPECT_EQ(status_.CodeText(re2::kRegexpMissingBracket), "missing ]");

    EXPECT_EQ(status_.CodeText(re2::kRegexpMissingParen), "missing )");

    EXPECT_EQ(status_.CodeText(re2::kRegexpUnexpectedParen), "unexpected )");

    EXPECT_EQ(status_.CodeText(re2::kRegexpTrailingBackslash), "trailing \\");

    EXPECT_EQ(status_.CodeText(re2::kRegexpRepeatArgument), "no argument for repetition operator");

    EXPECT_EQ(status_.CodeText(re2::kRegexpRepeatSize), "invalid repetition size");

    EXPECT_EQ(status_.CodeText(re2::kRegexpRepeatOp), "bad repetition operator");

    EXPECT_EQ(status_.CodeText(re2::kRegexpBadPerlOp), "invalid perl operator");

    EXPECT_EQ(status_.CodeText(re2::kRegexpBadUTF8), "invalid UTF-8");

    EXPECT_EQ(status_.CodeText(re2::kRegexpBadNamedCapture), "invalid named capture group");

}



TEST_F(RegexpStatusTest_350, CodeText_ReturnsInternalErrorForInvalidCode_350) {

    EXPECT_EQ(status_.CodeText(-1), "unexpected error");

    EXPECT_EQ(status_.CodeText(16), "unexpected error");

}



}  // namespace
