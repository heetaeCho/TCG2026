// File: regexp_codetext_test_350.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/regexp.h"

namespace {

using re2::RegexpStatus;
using re2::RegexpStatusCode;

class RegexpStatusCodeTextTest_350 : public ::testing::Test {
protected:
    RegexpStatus status_;
};

// --- Normal operation: each valid enum value maps to the expected text ---

TEST_F(RegexpStatusCodeTextTest_350, SuccessReturnsNoError_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpSuccess), "no error");
}

TEST_F(RegexpStatusCodeTextTest_350, InternalErrorMapsToUnexpectedError_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpInternalError), "unexpected error");
}

TEST_F(RegexpStatusCodeTextTest_350, BadEscape_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpBadEscape), "invalid escape sequence");
}

TEST_F(RegexpStatusCodeTextTest_350, BadCharClass_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpBadCharClass), "invalid character class");
}

TEST_F(RegexpStatusCodeTextTest_350, BadCharRange_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpBadCharRange), "invalid character class range");
}

TEST_F(RegexpStatusCodeTextTest_350, MissingBracket_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpMissingBracket), "missing ]");
}

TEST_F(RegexpStatusCodeTextTest_350, MissingParen_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpMissingParen), "missing )");
}

TEST_F(RegexpStatusCodeTextTest_350, UnexpectedParen_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpUnexpectedParen), "unexpected )");
}

TEST_F(RegexpStatusCodeTextTest_350, TrailingBackslash_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpTrailingBackslash), "trailing \\");
}

TEST_F(RegexpStatusCodeTextTest_350, RepeatArgument_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpRepeatArgument), "no argument for repetition operator");
}

TEST_F(RegexpStatusCodeTextTest_350, RepeatSize_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpRepeatSize), "invalid repetition size");
}

TEST_F(RegexpStatusCodeTextTest_350, RepeatOp_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpRepeatOp), "bad repetition operator");
}

TEST_F(RegexpStatusCodeTextTest_350, BadPerlOp_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpBadPerlOp), "invalid perl operator");
}

TEST_F(RegexpStatusCodeTextTest_350, BadUTF8_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpBadUTF8), "invalid UTF-8");
}

TEST_F(RegexpStatusCodeTextTest_350, BadNamedCapture_350) {
    EXPECT_EQ(status_.CodeText(re2::kRegexpBadNamedCapture), "invalid named capture group");
}

// --- Boundary conditions & exceptional cases (observable via return value) ---

// Below lower bound: negative enum value -> should map to "unexpected error"
TEST_F(RegexpStatusCodeTextTest_350, BelowLowerBoundMapsToInternalErrorText_350) {
    auto invalid = static_cast<RegexpStatusCode>(-1);
    EXPECT_EQ(status_.CodeText(invalid), "unexpected error");
}

// Above upper bound: one past the last valid enum -> should map to "unexpected error"
TEST_F(RegexpStatusCodeTextTest_350, AboveUpperBoundMapsToInternalErrorText_350) {
    // kRegexpBadNamedCapture is the highest valid (value 14). Use 15 as out-of-range.
    auto invalid = static_cast<RegexpStatusCode>(static_cast<int>(re2::kRegexpBadNamedCapture) + 1);
    EXPECT_EQ(status_.CodeText(invalid), "unexpected error");
}

// Far out-of-range positive value -> should still map to "unexpected error"
TEST_F(RegexpStatusCodeTextTest_350, FarOutOfRangeMapsToInternalErrorText_350) {
    auto invalid = static_cast<RegexpStatusCode>(999);
    EXPECT_EQ(status_.CodeText(invalid), "unexpected error");
}

} // namespace
