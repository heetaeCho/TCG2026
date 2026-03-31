#include <gtest/gtest.h>
#include <climits>
#include <string>

// We need to access the Parse function template specialization
namespace re2 {
namespace re2_internal {
template <typename T>
bool Parse(const char* str, size_t n, T* dest, int radix);

// Declare the specialization we're testing
template <>
bool Parse(const char* str, size_t n, unsigned long* dest, int radix);
}  // namespace re2_internal
}  // namespace re2

using re2::re2_internal::Parse;

class ParseUnsignedLongTest_276 : public ::testing::Test {
 protected:
};

// Normal operation tests

TEST_F(ParseUnsignedLongTest_276, ParsesSimpleDecimalNumber_276) {
  unsigned long result = 0;
  EXPECT_TRUE(Parse("123", 3, &result, 10));
  EXPECT_EQ(123UL, result);
}

TEST_F(ParseUnsignedLongTest_276, ParsesZero_276) {
  unsigned long result = 99;
  EXPECT_TRUE(Parse("0", 1, &result, 10));
  EXPECT_EQ(0UL, result);
}

TEST_F(ParseUnsignedLongTest_276, ParsesHexNumber_276) {
  unsigned long result = 0;
  EXPECT_TRUE(Parse("ff", 2, &result, 16));
  EXPECT_EQ(0xffUL, result);
}

TEST_F(ParseUnsignedLongTest_276, ParsesOctalNumber_276) {
  unsigned long result = 0;
  EXPECT_TRUE(Parse("77", 2, &result, 8));
  EXPECT_EQ(077UL, result);
}

TEST_F(ParseUnsignedLongTest_276, ParsesHexUpperCase_276) {
  unsigned long result = 0;
  EXPECT_TRUE(Parse("FF", 2, &result, 16));
  EXPECT_EQ(0xFFUL, result);
}

TEST_F(ParseUnsignedLongTest_276, ParsesSingleDigit_276) {
  unsigned long result = 0;
  EXPECT_TRUE(Parse("5", 1, &result, 10));
  EXPECT_EQ(5UL, result);
}

TEST_F(ParseUnsignedLongTest_276, ParsesLargeDecimal_276) {
  unsigned long result = 0;
  std::string s = "1000000";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 10));
  EXPECT_EQ(1000000UL, result);
}

TEST_F(ParseUnsignedLongTest_276, NullDestReturnsTrue_276) {
  EXPECT_TRUE(Parse("123", 3, static_cast<unsigned long*>(nullptr), 10));
}

TEST_F(ParseUnsignedLongTest_276, ParsesMaxUnsignedLong_276) {
  std::string s = std::to_string(ULONG_MAX);
  unsigned long result = 0;
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 10));
  EXPECT_EQ(ULONG_MAX, result);
}

// Boundary condition tests

TEST_F(ParseUnsignedLongTest_276, EmptyStringReturnsFalse_276) {
  unsigned long result = 0;
  EXPECT_FALSE(Parse("", 0, &result, 10));
}

TEST_F(ParseUnsignedLongTest_276, ZeroLengthReturnsFalse_276) {
  unsigned long result = 0;
  EXPECT_FALSE(Parse("123", 0, &result, 10));
}

// Error / exceptional case tests

TEST_F(ParseUnsignedLongTest_276, NegativeNumberReturnsFalse_276) {
  unsigned long result = 0;
  EXPECT_FALSE(Parse("-1", 2, &result, 10));
}

TEST_F(ParseUnsignedLongTest_276, NegativeZeroReturnsFalse_276) {
  unsigned long result = 0;
  EXPECT_FALSE(Parse("-0", 2, &result, 10));
}

TEST_F(ParseUnsignedLongTest_276, NegativeLargeNumberReturnsFalse_276) {
  unsigned long result = 0;
  EXPECT_FALSE(Parse("-123456", 7, &result, 10));
}

TEST_F(ParseUnsignedLongTest_276, LeftoverJunkReturnsFalse_276) {
  unsigned long result = 0;
  EXPECT_FALSE(Parse("123abc", 6, &result, 10));
}

TEST_F(ParseUnsignedLongTest_276, LeadingSpaceReturnsFalse_276) {
  unsigned long result = 0;
  // Depending on implementation, leading space may or may not be handled
  // strtoul typically skips whitespace, but TerminateNumber may affect this
  // We test partial length to see leftover junk behavior
  EXPECT_FALSE(Parse("12 3", 4, &result, 10));
}

TEST_F(ParseUnsignedLongTest_276, NonNumericStringReturnsFalse_276) {
  unsigned long result = 0;
  EXPECT_FALSE(Parse("abc", 3, &result, 10));
}

TEST_F(ParseUnsignedLongTest_276, OverflowReturnsFalse_276) {
  // A number larger than ULONG_MAX should cause overflow (errno set)
  std::string s = "99999999999999999999999999999999999";
  unsigned long result = 0;
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 10));
}

TEST_F(ParseUnsignedLongTest_276, InvalidHexDigitsReturnsFalse_276) {
  unsigned long result = 0;
  EXPECT_FALSE(Parse("GG", 2, &result, 16));
}

TEST_F(ParseUnsignedLongTest_276, InvalidOctalDigitsReturnsFalse_276) {
  unsigned long result = 0;
  EXPECT_FALSE(Parse("89", 2, &result, 8));
}

TEST_F(ParseUnsignedLongTest_276, PartialLengthParsesCorrectSubstring_276) {
  unsigned long result = 0;
  // Only parse first 2 characters of "123"
  EXPECT_TRUE(Parse("123", 2, &result, 10));
  EXPECT_EQ(12UL, result);
}

TEST_F(ParseUnsignedLongTest_276, HexWithPrefix0x_276) {
  unsigned long result = 0;
  // "0x1a" with radix 16 - strtoul should handle 0x prefix
  EXPECT_TRUE(Parse("0x1a", 4, &result, 16));
  EXPECT_EQ(0x1aUL, result);
}

TEST_F(ParseUnsignedLongTest_276, RadixZeroAutoDetectsDecimal_276) {
  unsigned long result = 0;
  EXPECT_TRUE(Parse("123", 3, &result, 0));
  EXPECT_EQ(123UL, result);
}

TEST_F(ParseUnsignedLongTest_276, RadixZeroAutoDetectsHex_276) {
  unsigned long result = 0;
  EXPECT_TRUE(Parse("0xff", 4, &result, 0));
  EXPECT_EQ(0xffUL, result);
}

TEST_F(ParseUnsignedLongTest_276, RadixZeroAutoDetectsOctal_276) {
  unsigned long result = 0;
  EXPECT_TRUE(Parse("077", 3, &result, 0));
  EXPECT_EQ(077UL, result);
}

TEST_F(ParseUnsignedLongTest_276, NullDestWithInvalidInputReturnsFalse_276) {
  EXPECT_FALSE(Parse("-1", 2, static_cast<unsigned long*>(nullptr), 10));
}

TEST_F(ParseUnsignedLongTest_276, NullDestWithEmptyReturnsFalse_276) {
  EXPECT_FALSE(Parse("", 0, static_cast<unsigned long*>(nullptr), 10));
}

TEST_F(ParseUnsignedLongTest_276, LeadingZerosDecimal_276) {
  unsigned long result = 0;
  EXPECT_TRUE(Parse("00123", 5, &result, 10));
  EXPECT_EQ(123UL, result);
}

TEST_F(ParseUnsignedLongTest_276, SingleZero_276) {
  unsigned long result = 99;
  EXPECT_TRUE(Parse("0", 1, &result, 10));
  EXPECT_EQ(0UL, result);
}
