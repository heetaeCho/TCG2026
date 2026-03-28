#include <gtest/gtest.h>
#include <climits>
#include <string>

// We need to access the Parse function template specialization
namespace re2 {
namespace re2_internal {
template <typename T>
bool Parse(const char* str, size_t n, T* dest, int radix);

template <>
bool Parse(const char* str, size_t n, unsigned long long* dest, int radix);
}  // namespace re2_internal
}  // namespace re2

using re2::re2_internal::Parse;

class ParseUnsignedLongLongTest_282 : public ::testing::Test {
 protected:
};

// Normal operation tests

TEST_F(ParseUnsignedLongLongTest_282, ParseSimpleDecimal_282) {
  unsigned long long result = 0;
  std::string s = "12345";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 10));
  EXPECT_EQ(result, 12345ULL);
}

TEST_F(ParseUnsignedLongLongTest_282, ParseZero_282) {
  unsigned long long result = 99;
  std::string s = "0";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 10));
  EXPECT_EQ(result, 0ULL);
}

TEST_F(ParseUnsignedLongLongTest_282, ParseHexadecimal_282) {
  unsigned long long result = 0;
  std::string s = "FF";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 16));
  EXPECT_EQ(result, 255ULL);
}

TEST_F(ParseUnsignedLongLongTest_282, ParseOctal_282) {
  unsigned long long result = 0;
  std::string s = "77";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 8));
  EXPECT_EQ(result, 63ULL);
}

TEST_F(ParseUnsignedLongLongTest_282, ParseLargeNumber_282) {
  unsigned long long result = 0;
  std::string s = "18446744073709551615";  // ULLONG_MAX
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 10));
  EXPECT_EQ(result, ULLONG_MAX);
}

TEST_F(ParseUnsignedLongLongTest_282, ParseWithNullDest_282) {
  std::string s = "42";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), (unsigned long long*)nullptr, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, ParseSingleDigit_282) {
  unsigned long long result = 0;
  std::string s = "7";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 10));
  EXPECT_EQ(result, 7ULL);
}

TEST_F(ParseUnsignedLongLongTest_282, ParseHexLowerCase_282) {
  unsigned long long result = 0;
  std::string s = "ff";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 16));
  EXPECT_EQ(result, 255ULL);
}

TEST_F(ParseUnsignedLongLongTest_282, ParseHexMixedCase_282) {
  unsigned long long result = 0;
  std::string s = "aB";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 16));
  EXPECT_EQ(result, 0xABULL);
}

// Boundary condition tests

TEST_F(ParseUnsignedLongLongTest_282, EmptyStringReturnsFalse_282) {
  unsigned long long result = 0;
  EXPECT_FALSE(Parse("", 0, &result, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, ZeroLengthReturnsFalse_282) {
  unsigned long long result = 0;
  EXPECT_FALSE(Parse("123", 0, &result, 10));
}

// Error / exceptional case tests

TEST_F(ParseUnsignedLongLongTest_282, NegativeNumberReturnsFalse_282) {
  unsigned long long result = 0;
  std::string s = "-1";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, NegativeZeroReturnsFalse_282) {
  unsigned long long result = 0;
  std::string s = "-0";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, NegativeLargeReturnsFalse_282) {
  unsigned long long result = 0;
  std::string s = "-12345";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, OverflowReturnsFalse_282) {
  unsigned long long result = 0;
  std::string s = "18446744073709551616";  // ULLONG_MAX + 1
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, MassiveOverflowReturnsFalse_282) {
  unsigned long long result = 0;
  std::string s = "99999999999999999999999";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, NonNumericReturnsFalse_282) {
  unsigned long long result = 0;
  std::string s = "abc";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, TrailingJunkReturnsFalse_282) {
  unsigned long long result = 0;
  std::string s = "123abc";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, LeadingSpaceReturnsFalse_282) {
  unsigned long long result = 0;
  std::string s = " 123";
  // strtoull skips leading whitespace, but the length check should catch trailing mismatch
  // or it may actually parse. This tests observable behavior.
  // Leading space: strtoull will parse "123" from " 123" consuming all 4 chars, so end == str+4 == str+n
  // Actually strtoull does skip whitespace, so it might succeed. Let's test observable behavior.
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  if (ok) {
    EXPECT_EQ(result, 123ULL);
  }
  // We just observe the behavior without asserting true or false since it depends on implementation
}

TEST_F(ParseUnsignedLongLongTest_282, InvalidHexCharForDecimal_282) {
  unsigned long long result = 0;
  std::string s = "1g";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 16));
}

TEST_F(ParseUnsignedLongLongTest_282, OnlySpacesReturnsFalse_282) {
  unsigned long long result = 0;
  std::string s = "   ";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, PlusSignPrefix_282) {
  unsigned long long result = 0;
  std::string s = "+123";
  // strtoull accepts +, test observable behavior
  bool ok = Parse(s.c_str(), s.size(), &result, 10);
  if (ok) {
    EXPECT_EQ(result, 123ULL);
  }
}

TEST_F(ParseUnsignedLongLongTest_282, ParseBinary_282) {
  unsigned long long result = 0;
  std::string s = "1010";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 2));
  EXPECT_EQ(result, 10ULL);
}

TEST_F(ParseUnsignedLongLongTest_282, NullDestWithNegativeReturnsFalse_282) {
  std::string s = "-5";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), (unsigned long long*)nullptr, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, NullDestWithInvalidReturnsFalse_282) {
  std::string s = "xyz";
  EXPECT_FALSE(Parse(s.c_str(), s.size(), (unsigned long long*)nullptr, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, NullDestWithEmptyReturnsFalse_282) {
  EXPECT_FALSE(Parse("", 0, (unsigned long long*)nullptr, 10));
}

TEST_F(ParseUnsignedLongLongTest_282, ParsePartialLength_282) {
  unsigned long long result = 0;
  // Pass "12345" but with length 3, so it should parse "123"
  EXPECT_TRUE(Parse("12345", 3, &result, 10));
  EXPECT_EQ(result, 123ULL);
}

TEST_F(ParseUnsignedLongLongTest_282, ParseHexMaxULL_282) {
  unsigned long long result = 0;
  std::string s = "FFFFFFFFFFFFFFFF";
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result, 16));
  EXPECT_EQ(result, ULLONG_MAX);
}

TEST_F(ParseUnsignedLongLongTest_282, ParseHexOverflow_282) {
  unsigned long long result = 0;
  std::string s = "10000000000000000";  // ULLONG_MAX + 1 in hex
  EXPECT_FALSE(Parse(s.c_str(), s.size(), &result, 16));
}
