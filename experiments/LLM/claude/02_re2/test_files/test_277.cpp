#include <gtest/gtest.h>
#include <climits>
#include <string>

// We need to declare the template and its specializations that we're testing
namespace re2 {
namespace re2_internal {

template <typename T>
bool Parse(const char* str, size_t n, T* dest, int radix);

// The specialization for long must exist (it's called by the short specialization)
template <>
bool Parse(const char* str, size_t n, long* dest, int radix);

// The specialization we're testing
template <>
bool Parse(const char* str, size_t n, short* dest, int radix);

}  // namespace re2_internal
}  // namespace re2

class ParseShortTest_277 : public ::testing::Test {
 protected:
  bool ParseShort(const char* str, size_t n, short* dest, int radix = 10) {
    return re2::re2_internal::Parse(str, n, dest, radix);
  }
};

// Normal operation: parse a simple positive number
TEST_F(ParseShortTest_277, ParseSimplePositiveNumber_277) {
  short result = 0;
  EXPECT_TRUE(ParseShort("123", 3, &result));
  EXPECT_EQ(result, 123);
}

// Normal operation: parse zero
TEST_F(ParseShortTest_277, ParseZero_277) {
  short result = -1;
  EXPECT_TRUE(ParseShort("0", 1, &result));
  EXPECT_EQ(result, 0);
}

// Normal operation: parse a negative number
TEST_F(ParseShortTest_277, ParseNegativeNumber_277) {
  short result = 0;
  EXPECT_TRUE(ParseShort("-456", 4, &result));
  EXPECT_EQ(result, -456);
}

// Normal operation: parse with null destination (validation only)
TEST_F(ParseShortTest_277, ParseWithNullDest_277) {
  EXPECT_TRUE(ParseShort("100", 3, nullptr));
}

// Boundary: parse SHRT_MAX
TEST_F(ParseShortTest_277, ParseShortMax_277) {
  std::string s = std::to_string(SHRT_MAX);
  short result = 0;
  EXPECT_TRUE(ParseShort(s.c_str(), s.size(), &result));
  EXPECT_EQ(result, SHRT_MAX);
}

// Boundary: parse SHRT_MIN
TEST_F(ParseShortTest_277, ParseShortMin_277) {
  std::string s = std::to_string(SHRT_MIN);
  short result = 0;
  EXPECT_TRUE(ParseShort(s.c_str(), s.size(), &result));
  EXPECT_EQ(result, SHRT_MIN);
}

// Error: value exceeds SHRT_MAX (out of range)
TEST_F(ParseShortTest_277, ParseOverflowAboveShortMax_277) {
  long val = (long)SHRT_MAX + 1;
  std::string s = std::to_string(val);
  short result = 0;
  EXPECT_FALSE(ParseShort(s.c_str(), s.size(), &result));
}

// Error: value below SHRT_MIN (out of range)
TEST_F(ParseShortTest_277, ParseUnderflowBelowShortMin_277) {
  long val = (long)SHRT_MIN - 1;
  std::string s = std::to_string(val);
  short result = 0;
  EXPECT_FALSE(ParseShort(s.c_str(), s.size(), &result));
}

// Error: completely invalid string
TEST_F(ParseShortTest_277, ParseInvalidString_277) {
  short result = 0;
  EXPECT_FALSE(ParseShort("abc", 3, &result));
}

// Error: empty string
TEST_F(ParseShortTest_277, ParseEmptyString_277) {
  short result = 0;
  EXPECT_FALSE(ParseShort("", 0, &result));
}

// Normal: parse with radix 16 (hex)
TEST_F(ParseShortTest_277, ParseHexNumber_277) {
  short result = 0;
  EXPECT_TRUE(ParseShort("FF", 2, &result, 16));
  EXPECT_EQ(result, 255);
}

// Normal: parse with radix 8 (octal)
TEST_F(ParseShortTest_277, ParseOctalNumber_277) {
  short result = 0;
  EXPECT_TRUE(ParseShort("77", 2, &result, 8));
  EXPECT_EQ(result, 63);
}

// Error: out of range with null dest still returns false
TEST_F(ParseShortTest_277, ParseOutOfRangeWithNullDest_277) {
  long val = (long)SHRT_MAX + 1;
  std::string s = std::to_string(val);
  EXPECT_FALSE(ParseShort(s.c_str(), s.size(), nullptr));
}

// Boundary: parse with partial length
TEST_F(ParseShortTest_277, ParsePartialString_277) {
  short result = 0;
  // Only parse first 2 characters of "12345"
  EXPECT_TRUE(ParseShort("12345", 2, &result));
  EXPECT_EQ(result, 12);
}

// Normal: large negative value within short range
TEST_F(ParseShortTest_277, ParseLargeNegativeInRange_277) {
  short result = 0;
  EXPECT_TRUE(ParseShort("-32000", 6, &result));
  EXPECT_EQ(result, -32000);
}

// Error: very large number well beyond short range
TEST_F(ParseShortTest_277, ParseVeryLargeNumber_277) {
  short result = 0;
  EXPECT_FALSE(ParseShort("100000", 6, &result));
}

// Normal: single digit
TEST_F(ParseShortTest_277, ParseSingleDigit_277) {
  short result = 0;
  EXPECT_TRUE(ParseShort("5", 1, &result));
  EXPECT_EQ(result, 5);
}

// Normal: hex value at short max boundary
TEST_F(ParseShortTest_277, ParseHexShortMax_277) {
  short result = 0;
  EXPECT_TRUE(ParseShort("7FFF", 4, &result, 16));
  EXPECT_EQ(result, SHRT_MAX);
}

// Error: hex value just over short max
TEST_F(ParseShortTest_277, ParseHexOverShortMax_277) {
  short result = 0;
  // 0x8000 = 32768, which is SHRT_MAX + 1
  EXPECT_FALSE(ParseShort("8000", 4, &result, 16));
}
