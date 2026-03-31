#include <gtest/gtest.h>
#include <climits>
#include <string>
#include <cstring>

// We need to access the Parse template specialization
namespace re2 {
namespace re2_internal {
template <typename T>
bool Parse(const char* str, size_t n, T* dest, int radix);

// Explicit declaration for the specialization we're testing
template <>
bool Parse(const char* str, size_t n, long* dest, int radix);
}  // namespace re2_internal

extern const int kMaxNumberLength;
}  // namespace re2

class ParseLongTest_275 : public ::testing::Test {
 protected:
  bool CallParse(const char* str, size_t n, long* dest, int radix = 10) {
    return re2::re2_internal::Parse(str, n, dest, radix);
  }
};

// Normal operation: parse a simple positive integer
TEST_F(ParseLongTest_275, ParseSimplePositiveInteger_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("123", 3, &result, 10));
  EXPECT_EQ(result, 123L);
}

// Normal operation: parse a simple negative integer
TEST_F(ParseLongTest_275, ParseSimpleNegativeInteger_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("-456", 4, &result, 10));
  EXPECT_EQ(result, -456L);
}

// Normal operation: parse zero
TEST_F(ParseLongTest_275, ParseZero_275) {
  long result = -1;
  EXPECT_TRUE(CallParse("0", 1, &result, 10));
  EXPECT_EQ(result, 0L);
}

// Normal operation: parse with hexadecimal radix
TEST_F(ParseLongTest_275, ParseHexadecimal_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("ff", 2, &result, 16));
  EXPECT_EQ(result, 255L);
}

// Normal operation: parse with octal radix
TEST_F(ParseLongTest_275, ParseOctal_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("77", 2, &result, 8));
  EXPECT_EQ(result, 63L);
}

// Normal operation: parse with binary radix
TEST_F(ParseLongTest_275, ParseBinary_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("1010", 4, &result, 2));
  EXPECT_EQ(result, 10L);
}

// Normal operation: parse with uppercase hex
TEST_F(ParseLongTest_275, ParseHexUppercase_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("FF", 2, &result, 16));
  EXPECT_EQ(result, 255L);
}

// Boundary: n == 0 should return false
TEST_F(ParseLongTest_275, EmptyStringReturnsFalse_275) {
  long result = 0;
  EXPECT_FALSE(CallParse("123", 0, &result, 10));
}

// Boundary: null destination should return true for valid input
TEST_F(ParseLongTest_275, NullDestValidInput_275) {
  EXPECT_TRUE(CallParse("123", 3, nullptr, 10));
}

// Boundary: null destination should return false for invalid input
TEST_F(ParseLongTest_275, NullDestInvalidInput_275) {
  EXPECT_FALSE(CallParse("abc", 3, nullptr, 10));
}

// Error: non-numeric string in base 10
TEST_F(ParseLongTest_275, NonNumericStringReturnsFalse_275) {
  long result = 0;
  EXPECT_FALSE(CallParse("abc", 3, &result, 10));
}

// Error: leftover junk after number
TEST_F(ParseLongTest_275, LeftoverJunkReturnsFalse_275) {
  long result = 0;
  EXPECT_FALSE(CallParse("12x", 3, &result, 10));
}

// Error: string with only spaces
TEST_F(ParseLongTest_275, OnlySpacesReturnsFalse_275) {
  long result = 0;
  EXPECT_FALSE(CallParse("   ", 3, &result, 10));
}

// Normal operation: parse "1" (single digit)
TEST_F(ParseLongTest_275, ParseSingleDigit_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("1", 1, &result, 10));
  EXPECT_EQ(result, 1L);
}

// Normal operation: negative one
TEST_F(ParseLongTest_275, ParseNegativeOne_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("-1", 2, &result, 10));
  EXPECT_EQ(result, -1L);
}

// Boundary: LONG_MAX
TEST_F(ParseLongTest_275, ParseLongMax_275) {
  std::string s = std::to_string(LONG_MAX);
  long result = 0;
  EXPECT_TRUE(CallParse(s.c_str(), s.size(), &result, 10));
  EXPECT_EQ(result, LONG_MAX);
}

// Boundary: LONG_MIN
TEST_F(ParseLongTest_275, ParseLongMin_275) {
  std::string s = std::to_string(LONG_MIN);
  long result = 0;
  EXPECT_TRUE(CallParse(s.c_str(), s.size(), &result, 10));
  EXPECT_EQ(result, LONG_MIN);
}

// Error: overflow beyond LONG_MAX
TEST_F(ParseLongTest_275, OverflowReturnsFalse_275) {
  // Use a string that is clearly larger than LONG_MAX
  std::string s = "99999999999999999999999999999999";
  long result = 0;
  EXPECT_FALSE(CallParse(s.c_str(), s.size(), &result, 10));
}

// Error: underflow beyond LONG_MIN
TEST_F(ParseLongTest_275, UnderflowReturnsFalse_275) {
  std::string s = "-99999999999999999999999999999999";
  long result = 0;
  EXPECT_FALSE(CallParse(s.c_str(), s.size(), &result, 10));
}

// Boundary: parse using partial length (n < actual string length)
TEST_F(ParseLongTest_275, PartialLengthParsesSubstring_275) {
  long result = 0;
  // "12345" but only parse first 3 chars "123"
  EXPECT_TRUE(CallParse("12345", 3, &result, 10));
  EXPECT_EQ(result, 123L);
}

// Normal: hex with leading "0" 
TEST_F(ParseLongTest_275, ParseHexWithLeadingZero_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("0a", 2, &result, 16));
  EXPECT_EQ(result, 10L);
}

// Error: just a minus sign
TEST_F(ParseLongTest_275, JustMinusSignReturnsFalse_275) {
  long result = 0;
  EXPECT_FALSE(CallParse("-", 1, &result, 10));
}

// Error: just a plus sign
TEST_F(ParseLongTest_275, JustPlusSignReturnsFalse_275) {
  long result = 0;
  EXPECT_FALSE(CallParse("+", 1, &result, 10));
}

// Normal: parse with leading plus sign
TEST_F(ParseLongTest_275, ParseWithLeadingPlusSign_275) {
  long result = 0;
  // strtol accepts leading '+', so this should work
  EXPECT_TRUE(CallParse("+42", 3, &result, 10));
  EXPECT_EQ(result, 42L);
}

// Normal: parse number with radix 0 (auto-detect)
TEST_F(ParseLongTest_275, ParseWithRadixZeroDecimal_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("42", 2, &result, 0));
  EXPECT_EQ(result, 42L);
}

// Normal: parse number with radix 0 auto-detect hex
TEST_F(ParseLongTest_275, ParseWithRadixZeroHex_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("0x1f", 4, &result, 0));
  EXPECT_EQ(result, 31L);
}

// Normal: parse number with radix 0 auto-detect octal
TEST_F(ParseLongTest_275, ParseWithRadixZeroOctal_275) {
  long result = 0;
  EXPECT_TRUE(CallParse("010", 3, &result, 0));
  EXPECT_EQ(result, 8L);
}

// Boundary: parse multiple zeros
TEST_F(ParseLongTest_275, ParseMultipleZeros_275) {
  long result = -1;
  EXPECT_TRUE(CallParse("000", 3, &result, 10));
  EXPECT_EQ(result, 0L);
}

// Error: invalid digit for octal
TEST_F(ParseLongTest_275, InvalidOctalDigitReturnsFalse_275) {
  long result = 0;
  EXPECT_FALSE(CallParse("89", 2, &result, 8));
}

// Error: invalid digit for binary
TEST_F(ParseLongTest_275, InvalidBinaryDigitReturnsFalse_275) {
  long result = 0;
  EXPECT_FALSE(CallParse("2", 1, &result, 2));
}
