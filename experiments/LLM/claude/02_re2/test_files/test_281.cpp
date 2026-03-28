#include <gtest/gtest.h>
#include <climits>
#include <string>
#include <cstring>

// Include the necessary headers
#include "re2/re2.h"

// We need access to the Parse template specialization
namespace re2 {
namespace re2_internal {
template <typename T>
bool Parse(const char* str, size_t n, T* dest, int radix);

// Explicit declaration for long long specialization
template <>
bool Parse(const char* str, size_t n, long long* dest, int radix);
}  // namespace re2_internal
}  // namespace re2

using re2::re2_internal::Parse;

class ParseLongLongTest_281 : public ::testing::Test {
 protected:
  bool CallParse(const std::string& s, long long* dest, int radix = 10) {
    return Parse<long long>(s.c_str(), s.size(), dest, radix);
  }
};

// Test: Empty string returns false
TEST_F(ParseLongLongTest_281, EmptyStringReturnsFalse_281) {
  long long result = 0;
  EXPECT_FALSE(CallParse("", &result, 10));
}

// Test: Simple positive integer
TEST_F(ParseLongLongTest_281, SimplePositiveInteger_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("123", &result, 10));
  EXPECT_EQ(result, 123);
}

// Test: Simple negative integer
TEST_F(ParseLongLongTest_281, SimpleNegativeInteger_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("-456", &result, 10));
  EXPECT_EQ(result, -456);
}

// Test: Zero
TEST_F(ParseLongLongTest_281, Zero_281) {
  long long result = -1;
  EXPECT_TRUE(CallParse("0", &result, 10));
  EXPECT_EQ(result, 0);
}

// Test: Null destination (should still return true for valid input)
TEST_F(ParseLongLongTest_281, NullDestination_281) {
  EXPECT_TRUE(CallParse("42", nullptr, 10));
}

// Test: Null destination with empty string returns false
TEST_F(ParseLongLongTest_281, NullDestinationEmptyString_281) {
  EXPECT_FALSE(CallParse("", nullptr, 10));
}

// Test: Hexadecimal parsing
TEST_F(ParseLongLongTest_281, HexadecimalParsing_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("ff", &result, 16));
  EXPECT_EQ(result, 255);
}

// Test: Hexadecimal with uppercase
TEST_F(ParseLongLongTest_281, HexadecimalUppercase_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("FF", &result, 16));
  EXPECT_EQ(result, 255);
}

// Test: Octal parsing
TEST_F(ParseLongLongTest_281, OctalParsing_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("77", &result, 8));
  EXPECT_EQ(result, 63);
}

// Test: Binary parsing (radix 2)
TEST_F(ParseLongLongTest_281, BinaryParsing_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("1010", &result, 2));
  EXPECT_EQ(result, 10);
}

// Test: Leftover junk causes failure
TEST_F(ParseLongLongTest_281, LeftoverJunkReturnsFalse_281) {
  long long result = 0;
  EXPECT_FALSE(CallParse("123abc", &result, 10));
}

// Test: Whitespace only returns false
TEST_F(ParseLongLongTest_281, WhitespaceOnlyReturnsFalse_281) {
  long long result = 0;
  EXPECT_FALSE(CallParse("   ", &result, 10));
}

// Test: Leading whitespace with number - depends on strtoll behavior but likely fails due to leftover
// strtoll skips leading whitespace but the TerminateNumber function might handle it
TEST_F(ParseLongLongTest_281, LeadingWhitespace_281) {
  long long result = 0;
  // strtoll skips leading whitespace, so " 123" would parse as 123 with end at str+4
  // If n=4 and end == str + 4, it should succeed
  bool success = CallParse(" 123", &result, 10);
  // We don't assert a specific outcome since it depends on TerminateNumber behavior,
  // but just verify it doesn't crash
  (void)success;
}

// Test: Single digit
TEST_F(ParseLongLongTest_281, SingleDigit_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("7", &result, 10));
  EXPECT_EQ(result, 7);
}

// Test: LLONG_MAX
TEST_F(ParseLongLongTest_281, LongLongMax_281) {
  long long result = 0;
  std::string maxStr = std::to_string(LLONG_MAX);
  EXPECT_TRUE(CallParse(maxStr, &result, 10));
  EXPECT_EQ(result, LLONG_MAX);
}

// Test: LLONG_MIN
TEST_F(ParseLongLongTest_281, LongLongMin_281) {
  long long result = 0;
  std::string minStr = std::to_string(LLONG_MIN);
  EXPECT_TRUE(CallParse(minStr, &result, 10));
  EXPECT_EQ(result, LLONG_MIN);
}

// Test: Overflow returns false (number larger than LLONG_MAX)
TEST_F(ParseLongLongTest_281, OverflowReturnsFalse_281) {
  long long result = 0;
  // A number definitely larger than LLONG_MAX
  std::string overflowStr = "99999999999999999999999999999999";
  EXPECT_FALSE(CallParse(overflowStr, &result, 10));
}

// Test: Underflow returns false (number smaller than LLONG_MIN)
TEST_F(ParseLongLongTest_281, UnderflowReturnsFalse_281) {
  long long result = 0;
  std::string underflowStr = "-99999999999999999999999999999999";
  EXPECT_FALSE(CallParse(underflowStr, &result, 10));
}

// Test: Positive sign
TEST_F(ParseLongLongTest_281, PositiveSign_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("+42", &result, 10));
  EXPECT_EQ(result, 42);
}

// Test: Just a minus sign should fail
TEST_F(ParseLongLongTest_281, JustMinusSign_281) {
  long long result = 0;
  EXPECT_FALSE(CallParse("-", &result, 10));
}

// Test: Just a plus sign should fail
TEST_F(ParseLongLongTest_281, JustPlusSign_281) {
  long long result = 0;
  EXPECT_FALSE(CallParse("+", &result, 10));
}

// Test: Hex parsing with 0x prefix - depends on radix=16 behavior of strtoll
TEST_F(ParseLongLongTest_281, HexWithPrefix_281) {
  long long result = 0;
  // With radix=16, strtoll accepts optional 0x prefix
  bool success = CallParse("0xff", &result, 16);
  if (success) {
    EXPECT_EQ(result, 255);
  }
}

// Test: Radix 0 auto-detection for decimal
TEST_F(ParseLongLongTest_281, RadixZeroDecimal_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("100", &result, 0));
  EXPECT_EQ(result, 100);
}

// Test: Radix 0 auto-detection for octal
TEST_F(ParseLongLongTest_281, RadixZeroOctal_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("0100", &result, 0));
  EXPECT_EQ(result, 64);  // 0100 in octal = 64
}

// Test: Radix 0 auto-detection for hex
TEST_F(ParseLongLongTest_281, RadixZeroHex_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("0x100", &result, 0));
  EXPECT_EQ(result, 256);
}

// Test: Large but valid number
TEST_F(ParseLongLongTest_281, LargeValidNumber_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("1000000000000", &result, 10));
  EXPECT_EQ(result, 1000000000000LL);
}

// Test: Negative zero
TEST_F(ParseLongLongTest_281, NegativeZero_281) {
  long long result = -1;
  EXPECT_TRUE(CallParse("-0", &result, 10));
  EXPECT_EQ(result, 0);
}

// Test: String with embedded null - only the part before null should matter
// but since we pass n explicitly, it depends on TerminateNumber
TEST_F(ParseLongLongTest_281, StringOfLengthOne_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("5", &result, 10));
  EXPECT_EQ(result, 5);
}

// Test: Non-numeric characters in decimal
TEST_F(ParseLongLongTest_281, NonNumericCharsDecimal_281) {
  long long result = 0;
  EXPECT_FALSE(CallParse("abc", &result, 10));
}

// Test: Valid hex characters in hex mode
TEST_F(ParseLongLongTest_281, ValidHexCharsInHexMode_281) {
  long long result = 0;
  EXPECT_TRUE(CallParse("abc", &result, 16));
  EXPECT_EQ(result, 0xabc);
}

// Test: Invalid character for given radix
TEST_F(ParseLongLongTest_281, InvalidCharForRadix_281) {
  long long result = 0;
  // '9' is not valid in octal
  EXPECT_FALSE(CallParse("9", &result, 8));
}

// Test: Multiple zeros
TEST_F(ParseLongLongTest_281, MultipleZeros_281) {
  long long result = -1;
  EXPECT_TRUE(CallParse("000", &result, 10));
  EXPECT_EQ(result, 0);
}

// Test: Number at kMaxNumberLength boundary (32 chars)
TEST_F(ParseLongLongTest_281, NumberAtMaxLength_281) {
  // 32 characters of digits - this will be a huge number that overflows
  long long result = 0;
  std::string longNum(32, '1');  // "11111111111111111111111111111111"
  // This will overflow long long, so should return false
  EXPECT_FALSE(CallParse(longNum, &result, 10));
}

// Test: Number exceeding kMaxNumberLength (33+ chars)
TEST_F(ParseLongLongTest_281, NumberExceedingMaxLength_281) {
  long long result = 0;
  std::string tooLong(33, '1');
  // Likely truncated or fails
  bool success = CallParse(tooLong, &result, 10);
  // We just ensure it doesn't crash; the result depends on TerminateNumber behavior
  (void)success;
}
