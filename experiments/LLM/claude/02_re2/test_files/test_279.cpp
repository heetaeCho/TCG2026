#include <gtest/gtest.h>
#include <climits>
#include <cstring>
#include <string>

// Declare the template and specialization we need to test
namespace re2 {
namespace re2_internal {

template <typename T>
bool Parse(const char* str, size_t n, T* dest, int radix);

// The specialization for long that the int version depends on
template <>
bool Parse(const char* str, size_t n, long* dest, int radix);

// The specialization under test
template <>
bool Parse(const char* str, size_t n, int* dest, int radix);

}  // namespace re2_internal
}  // namespace re2

using re2::re2_internal::Parse;

class ParseIntTest_279 : public ::testing::Test {
protected:
};

// Normal operation: parse a simple positive integer in base 10
TEST_F(ParseIntTest_279, ParseSimplePositiveInt_279) {
  int result = 0;
  std::string s = "42";
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(42, result);
}

// Normal operation: parse zero
TEST_F(ParseIntTest_279, ParseZero_279) {
  int result = -1;
  std::string s = "0";
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(0, result);
}

// Normal operation: parse a negative integer
TEST_F(ParseIntTest_279, ParseNegativeInt_279) {
  int result = 0;
  std::string s = "-123";
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(-123, result);
}

// Normal operation: parse hex value
TEST_F(ParseIntTest_279, ParseHexValue_279) {
  int result = 0;
  std::string s = "ff";
  bool ok = Parse(s.c_str(), s.size(), &result, 16);
  EXPECT_TRUE(ok);
  EXPECT_EQ(255, result);
}

// Normal operation: parse octal value
TEST_F(ParseIntTest_279, ParseOctalValue_279) {
  int result = 0;
  std::string s = "77";
  bool ok = Parse(s.c_str(), s.size(), &result, 8);
  EXPECT_TRUE(ok);
  EXPECT_EQ(63, result);
}

// Boundary: INT_MAX should be parseable
TEST_F(ParseIntTest_279, ParseIntMax_279) {
  int result = 0;
  std::string s = std::to_string(INT_MAX);
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(INT_MAX, result);
}

// Boundary: INT_MIN should be parseable
TEST_F(ParseIntTest_279, ParseIntMin_279) {
  int result = 0;
  std::string s = std::to_string(INT_MIN);
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(INT_MIN, result);
}

// Out of range: value larger than INT_MAX (but fits in long on 64-bit)
TEST_F(ParseIntTest_279, OutOfRangeAboveIntMax_279) {
  int result = 0;
  long val = (long)INT_MAX + 1;
  std::string s = std::to_string(val);
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_FALSE(ok);
}

// Out of range: value smaller than INT_MIN (but fits in long on 64-bit)
TEST_F(ParseIntTest_279, OutOfRangeBelowIntMin_279) {
  int result = 0;
  long val = (long)INT_MIN - 1;
  std::string s = std::to_string(val);
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_FALSE(ok);
}

// Error case: empty string
TEST_F(ParseIntTest_279, ParseEmptyString_279) {
  int result = 0;
  bool ok = Parse("", 0, &result, 10);
  EXPECT_FALSE(ok);
}

// Error case: non-numeric string
TEST_F(ParseIntTest_279, ParseNonNumericString_279) {
  int result = 0;
  std::string s = "abc";
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_FALSE(ok);
}

// Null destination: should return true for valid input without writing
TEST_F(ParseIntTest_279, NullDestValidInput_279) {
  std::string s = "42";
  bool ok = Parse(s.c_str(), s.size(), (int*)nullptr, 10);
  EXPECT_TRUE(ok);
}

// Null destination: should return false for invalid input
TEST_F(ParseIntTest_279, NullDestInvalidInput_279) {
  std::string s = "notanumber";
  bool ok = Parse(s.c_str(), s.size(), (int*)nullptr, 10);
  EXPECT_FALSE(ok);
}

// Normal: parse with leading zeros
TEST_F(ParseIntTest_279, ParseWithLeadingZeros_279) {
  int result = 0;
  std::string s = "00042";
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(42, result);
}

// Normal: parse single digit
TEST_F(ParseIntTest_279, ParseSingleDigit_279) {
  int result = -1;
  std::string s = "7";
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(7, result);
}

// Hex: parse uppercase hex
TEST_F(ParseIntTest_279, ParseUppercaseHex_279) {
  int result = 0;
  std::string s = "FF";
  bool ok = Parse(s.c_str(), s.size(), &result, 16);
  EXPECT_TRUE(ok);
  EXPECT_EQ(255, result);
}

// Parse with explicit length shorter than string
TEST_F(ParseIntTest_279, ParsePartialString_279) {
  int result = 0;
  const char* s = "12345";
  bool ok = Parse(s, 3, &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(123, result);
}

// Large out of range for 64-bit long
TEST_F(ParseIntTest_279, ParseVeryLargeNumber_279) {
  int result = 0;
  std::string s = "99999999999999999999";
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_FALSE(ok);
}
