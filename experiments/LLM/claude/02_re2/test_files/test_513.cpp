#include <gtest/gtest.h>
#include "absl/strings/string_view.h"

// We need to access the static function ParseInteger from re2 namespace.
// Since it's static in parse.cc, we need to include or redeclare it.
// For testing purposes, we'll include the source or use a test-friendly approach.

namespace re2 {
// Forward declaration - this function is defined as static in parse.cc
// For testing, we need access to it. In practice, this would require
// either making it non-static or using a test helper.
static bool ParseInteger(absl::string_view* s, int* np);
}

// Include the actual implementation
#include "re2/parse.cc"

namespace {

class ParseIntegerTest_513 : public ::testing::Test {
protected:
    bool CallParseInteger(absl::string_view* s, int* np) {
        return re2::ParseInteger(s, np);
    }
};

// Normal operation: single digit
TEST_F(ParseIntegerTest_513, SingleDigit_513) {
    absl::string_view s("5");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 5);
    EXPECT_TRUE(s.empty());
}

// Normal operation: multiple digits
TEST_F(ParseIntegerTest_513, MultipleDigits_513) {
    absl::string_view s("123");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 123);
    EXPECT_TRUE(s.empty());
}

// Normal operation: digits followed by non-digit characters
TEST_F(ParseIntegerTest_513, DigitsFollowedByNonDigit_513) {
    absl::string_view s("42abc");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 42);
    EXPECT_EQ(s, "abc");
}

// Normal operation: zero
TEST_F(ParseIntegerTest_513, Zero_513) {
    absl::string_view s("0");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 0);
    EXPECT_TRUE(s.empty());
}

// Zero followed by non-digit
TEST_F(ParseIntegerTest_513, ZeroFollowedByNonDigit_513) {
    absl::string_view s("0abc");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 0);
    EXPECT_EQ(s, "abc");
}

// Boundary: leading zero is rejected (octal-like)
TEST_F(ParseIntegerTest_513, LeadingZeroRejected_513) {
    absl::string_view s("07");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
    // String should be unchanged
    EXPECT_EQ(s, "07");
}

// Boundary: leading zeros "00"
TEST_F(ParseIntegerTest_513, DoubleZeroRejected_513) {
    absl::string_view s("00");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
    EXPECT_EQ(s, "00");
}

// Boundary: leading zero "0123"
TEST_F(ParseIntegerTest_513, LeadingZeroMultiDigitRejected_513) {
    absl::string_view s("0123");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
    EXPECT_EQ(s, "0123");
}

// Error: empty string
TEST_F(ParseIntegerTest_513, EmptyString_513) {
    absl::string_view s("");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
}

// Error: starts with non-digit
TEST_F(ParseIntegerTest_513, StartsWithNonDigit_513) {
    absl::string_view s("abc");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
    EXPECT_EQ(s, "abc");
}

// Error: starts with minus sign
TEST_F(ParseIntegerTest_513, StartsWithMinus_513) {
    absl::string_view s("-5");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
    EXPECT_EQ(s, "-5");
}

// Error: starts with plus sign
TEST_F(ParseIntegerTest_513, StartsWithPlus_513) {
    absl::string_view s("+5");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
    EXPECT_EQ(s, "+5");
}

// Boundary: large number just below overflow threshold
TEST_F(ParseIntegerTest_513, LargeNumberBelowThreshold_513) {
    absl::string_view s("99999999");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 99999999);
    EXPECT_TRUE(s.empty());
}

// Boundary: number at the overflow threshold (100000000)
TEST_F(ParseIntegerTest_513, NumberAtThreshold_513) {
    absl::string_view s("100000000");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 100000000);
    EXPECT_TRUE(s.empty());
}

// Boundary: number exceeding the overflow threshold
// When n reaches 100000000 and there's another digit, it should fail
TEST_F(ParseIntegerTest_513, NumberExceedsThreshold_513) {
    absl::string_view s("1000000000");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
}

// Very large number that would overflow
TEST_F(ParseIntegerTest_513, VeryLargeNumberOverflow_513) {
    absl::string_view s("9999999999");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
}

// Normal: digit 0-9 individually
TEST_F(ParseIntegerTest_513, AllSingleDigits_513) {
    for (int i = 0; i <= 9; i++) {
        std::string str = std::to_string(i);
        absl::string_view s(str);
        int n = -1;
        EXPECT_TRUE(CallParseInteger(&s, &n));
        EXPECT_EQ(n, i);
        EXPECT_TRUE(s.empty());
    }
}

// Normal: string with space after digits
TEST_F(ParseIntegerTest_513, DigitsFollowedBySpace_513) {
    absl::string_view s("99 ");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 99);
    EXPECT_EQ(s, " ");
}

// Starts with space
TEST_F(ParseIntegerTest_513, StartsWithSpace_513) {
    absl::string_view s(" 42");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
    EXPECT_EQ(s, " 42");
}

// Number with exactly 9 digits (all 9s) - should succeed
TEST_F(ParseIntegerTest_513, NineDigitNumber_513) {
    absl::string_view s("999999999");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 999999999);
    EXPECT_TRUE(s.empty());
}

// Digits followed by closing brace (common regex pattern context)
TEST_F(ParseIntegerTest_513, DigitsFollowedByBrace_513) {
    absl::string_view s("255}");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 255);
    EXPECT_EQ(s, "}");
}

// Digits followed by comma (common regex repeat context)
TEST_F(ParseIntegerTest_513, DigitsFollowedByComma_513) {
    absl::string_view s("10,20}");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 10);
    EXPECT_EQ(s, ",20}");
}

// String "0" followed by non-digit - this is valid (single zero)
TEST_F(ParseIntegerTest_513, ZeroFollowedByCloseBrace_513) {
    absl::string_view s("0}");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 0);
    EXPECT_EQ(s, "}");
}

// Test that string_view is properly advanced
TEST_F(ParseIntegerTest_513, StringViewAdvanced_513) {
    absl::string_view s("12345rest");
    int n = -1;
    EXPECT_TRUE(CallParseInteger(&s, &n));
    EXPECT_EQ(n, 12345);
    EXPECT_EQ(s.size(), 4u);
    EXPECT_EQ(s, "rest");
}

// Boundary: exactly at 100000000 with trailing digit should fail
TEST_F(ParseIntegerTest_513, ExactlyAtThresholdWithTrailingDigit_513) {
    absl::string_view s("1000000001");
    int n = -1;
    EXPECT_FALSE(CallParseInteger(&s, &n));
}

}  // namespace
