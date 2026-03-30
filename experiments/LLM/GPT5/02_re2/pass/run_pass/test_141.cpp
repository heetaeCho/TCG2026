// File: regexp_status_ok_test_141.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::RegexpStatus;
using re2::RegexpStatusCode;
using re2::kRegexpSuccess;
using re2::kRegexpInternalError;
using re2::kRegexpBadEscape;
using re2::kRegexpBadCharClass;
using re2::kRegexpBadCharRange;
using re2::kRegexpMissingBracket;
using re2::kRegexpMissingParen;
using re2::kRegexpUnexpectedParen;
using re2::kRegexpTrailingBackslash;
using re2::kRegexpRepeatArgument;
using re2::kRegexpRepeatSize;
using re2::kRegexpRepeatOp;
using re2::kRegexpBadPerlOp;
using re2::kRegexpBadUTF8;
using re2::kRegexpBadNamedCapture;

// -----------------------------------------------------------------------------
// Normal operation: default-constructed status should be "ok".
// -----------------------------------------------------------------------------
TEST(RegexpStatusTest_141, DefaultIsOk_141) {
    RegexpStatus s;
    EXPECT_TRUE(s.ok());
}

// -----------------------------------------------------------------------------
// Boundary/representative cases: setting non-success codes should make ok()==false.
// Also verify flipping back to success restores ok()==true.
// -----------------------------------------------------------------------------
TEST(RegexpStatusTest_141, OkReflectsCodeTransitions_141) {
    RegexpStatus s;

    // Move to an error state.
    s.set_code(kRegexpInternalError);
    EXPECT_FALSE(s.ok());

    // Back to success.
    s.set_code(kRegexpSuccess);
    EXPECT_TRUE(s.ok());
}

// -----------------------------------------------------------------------------
// Parameterized: every known non-success code should yield ok()==false.
// -----------------------------------------------------------------------------
class RegexpStatusParamTest_141
    : public ::testing::TestWithParam<RegexpStatusCode> {};

INSTANTIATE_TEST_SUITE_P(
    AllNonSuccessCodes_141,
    RegexpStatusParamTest_141,
    ::testing::Values(
        kRegexpInternalError,
        kRegexpBadEscape,
        kRegexpBadCharClass,
        kRegexpBadCharRange,
        kRegexpMissingBracket,
        kRegexpMissingParen,
        kRegexpUnexpectedParen,
        kRegexpTrailingBackslash,
        kRegexpRepeatArgument,
        kRegexpRepeatSize,
        kRegexpRepeatOp,
        kRegexpBadPerlOp,
        kRegexpBadUTF8,
        kRegexpBadNamedCapture));

TEST_P(RegexpStatusParamTest_141, NonSuccessYieldsFalse_141) {
    RegexpStatus s;
    s.set_code(GetParam());
    EXPECT_FALSE(s.ok());
}

// -----------------------------------------------------------------------------
// Consistency: ok() should be equivalent to (code() == kRegexpSuccess).
// This directly checks the observable relationship stated by the interface.
// -----------------------------------------------------------------------------
TEST(RegexpStatusTest_141, OkMatchesCodeEquality_141) {
    RegexpStatus s;

    // Success -> ok() true
    s.set_code(kRegexpSuccess);
    EXPECT_EQ(s.code() == kRegexpSuccess, s.ok());

    // A handful of different non-success codes -> ok() false
    RegexpStatusCode samples[] = {
        kRegexpInternalError,
        kRegexpBadEscape,
        kRegexpBadUTF8,
        kRegexpBadNamedCapture
    };
    for (auto c : samples) {
        s.set_code(c);
        EXPECT_EQ(s.code() == kRegexpSuccess, s.ok());
    }
}
