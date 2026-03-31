#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <limits>
#include <cmath>

// Include the header under test
#include "exiv2/error.hpp"

// =============================================================================
// Tests for Exiv2::toBasicString
// =============================================================================

// --- Normal operation tests ---

TEST(ToBasicStringTest_58, IntToString_58) {
  std::string result = Exiv2::toBasicString<char>(42);
  EXPECT_EQ(result, "42");
}

TEST(ToBasicStringTest_58, NegativeIntToString_58) {
  std::string result = Exiv2::toBasicString<char>(-100);
  EXPECT_EQ(result, "-100");
}

TEST(ToBasicStringTest_58, ZeroIntToString_58) {
  std::string result = Exiv2::toBasicString<char>(0);
  EXPECT_EQ(result, "0");
}

TEST(ToBasicStringTest_58, DoubleToString_58) {
  std::string result = Exiv2::toBasicString<char>(3.14);
  // Verify it starts with "3.14" (implementation may vary in trailing digits)
  EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST(ToBasicStringTest_58, FloatToString_58) {
  std::string result = Exiv2::toBasicString<char>(2.5f);
  EXPECT_EQ(result, "2.5");
}

TEST(ToBasicStringTest_58, StringToString_58) {
  std::string input = "hello";
  std::string result = Exiv2::toBasicString<char>(input);
  EXPECT_EQ(result, "hello");
}

TEST(ToBasicStringTest_58, CStringToString_58) {
  const char* input = "world";
  std::string result = Exiv2::toBasicString<char>(input);
  EXPECT_EQ(result, "world");
}

TEST(ToBasicStringTest_58, CharToString_58) {
  char c = 'A';
  std::string result = Exiv2::toBasicString<char>(c);
  EXPECT_EQ(result, "A");
}

TEST(ToBasicStringTest_58, BoolTrueToString_58) {
  std::string result = Exiv2::toBasicString<char>(true);
  EXPECT_EQ(result, "1");
}

TEST(ToBasicStringTest_58, BoolFalseToString_58) {
  std::string result = Exiv2::toBasicString<char>(false);
  EXPECT_EQ(result, "0");
}

TEST(ToBasicStringTest_58, UnsignedIntToString_58) {
  unsigned int val = 12345u;
  std::string result = Exiv2::toBasicString<char>(val);
  EXPECT_EQ(result, "12345");
}

TEST(ToBasicStringTest_58, LongToString_58) {
  long val = 999999L;
  std::string result = Exiv2::toBasicString<char>(val);
  EXPECT_EQ(result, "999999");
}

TEST(ToBasicStringTest_58, LongLongToString_58) {
  long long val = 1234567890123LL;
  std::string result = Exiv2::toBasicString<char>(val);
  EXPECT_EQ(result, "1234567890123");
}

// --- Wide string tests ---

TEST(ToBasicStringTest_58, IntToWString_58) {
  std::wstring result = Exiv2::toBasicString<wchar_t>(42);
  EXPECT_EQ(result, L"42");
}

TEST(ToBasicStringTest_58, NegativeIntToWString_58) {
  std::wstring result = Exiv2::toBasicString<wchar_t>(-7);
  EXPECT_EQ(result, L"-7");
}

TEST(ToBasicStringTest_58, DoubleToWString_58) {
  std::wstring result = Exiv2::toBasicString<wchar_t>(2.5);
  EXPECT_EQ(result, L"2.5");
}

TEST(ToBasicStringTest_58, WCharToWString_58) {
  wchar_t c = L'Z';
  std::wstring result = Exiv2::toBasicString<wchar_t>(c);
  EXPECT_EQ(result, L"Z");
}

TEST(ToBasicStringTest_58, CWStringToWString_58) {
  const wchar_t* input = L"test";
  std::wstring result = Exiv2::toBasicString<wchar_t>(input);
  EXPECT_EQ(result, L"test");
}

// --- Boundary condition tests ---

TEST(ToBasicStringTest_58, IntMaxToString_58) {
  int val = std::numeric_limits<int>::max();
  std::string result = Exiv2::toBasicString<char>(val);
  std::ostringstream oss;
  oss << val;
  EXPECT_EQ(result, oss.str());
}

TEST(ToBasicStringTest_58, IntMinToString_58) {
  int val = std::numeric_limits<int>::min();
  std::string result = Exiv2::toBasicString<char>(val);
  std::ostringstream oss;
  oss << val;
  EXPECT_EQ(result, oss.str());
}

TEST(ToBasicStringTest_58, UnsignedLongLongMaxToString_58) {
  unsigned long long val = std::numeric_limits<unsigned long long>::max();
  std::string result = Exiv2::toBasicString<char>(val);
  std::ostringstream oss;
  oss << val;
  EXPECT_EQ(result, oss.str());
}

TEST(ToBasicStringTest_58, EmptyStringToString_58) {
  std::string input;
  std::string result = Exiv2::toBasicString<char>(input);
  EXPECT_EQ(result, "");
}

TEST(ToBasicStringTest_58, EmptyCStringToString_58) {
  const char* input = "";
  std::string result = Exiv2::toBasicString<char>(input);
  EXPECT_EQ(result, "");
}

TEST(ToBasicStringTest_58, NegativeDoubleToString_58) {
  std::string result = Exiv2::toBasicString<char>(-0.0);
  // -0.0 might be rendered as "0" or "-0" depending on implementation
  // Just verify it doesn't crash and produces something reasonable
  EXPECT_FALSE(result.empty());
}

TEST(ToBasicStringTest_58, VerySmallDoubleToString_58) {
  double val = std::numeric_limits<double>::min();
  std::string result = Exiv2::toBasicString<char>(val);
  EXPECT_FALSE(result.empty());
}

TEST(ToBasicStringTest_58, VeryLargeDoubleToString_58) {
  double val = std::numeric_limits<double>::max();
  std::string result = Exiv2::toBasicString<char>(val);
  EXPECT_FALSE(result.empty());
}

// --- Consistency test: output matches std::ostringstream behavior ---

TEST(ToBasicStringTest_58, ConsistencyWithOstringstream_58) {
  int val = 256;
  std::ostringstream oss;
  oss << val;
  std::string expected = oss.str();
  std::string result = Exiv2::toBasicString<char>(val);
  EXPECT_EQ(result, expected);
}

TEST(ToBasicStringTest_58, ConsistencyWithWOstringstream_58) {
  int val = 256;
  std::wostringstream oss;
  oss << val;
  std::wstring expected = oss.str();
  std::wstring result = Exiv2::toBasicString<wchar_t>(val);
  EXPECT_EQ(result, expected);
}

TEST(ToBasicStringTest_58, ShortToString_58) {
  short val = -32000;
  std::string result = Exiv2::toBasicString<char>(val);
  std::ostringstream oss;
  oss << val;
  EXPECT_EQ(result, oss.str());
}

TEST(ToBasicStringTest_58, UnsignedShortToString_58) {
  unsigned short val = 65000u;
  std::string result = Exiv2::toBasicString<char>(val);
  EXPECT_EQ(result, "65000");
}

TEST(ToBasicStringTest_58, SizeTToString_58) {
  size_t val = 42;
  std::string result = Exiv2::toBasicString<char>(val);
  EXPECT_EQ(result, "42");
}

TEST(ToBasicStringTest_58, StringWithSpacesToString_58) {
  std::string input = "hello world";
  std::string result = Exiv2::toBasicString<char>(input);
  EXPECT_EQ(result, "hello world");
}

TEST(ToBasicStringTest_58, StringWithSpecialCharsToString_58) {
  std::string input = "tab\there\nnewline";
  std::string result = Exiv2::toBasicString<char>(input);
  EXPECT_EQ(result, "tab\there\nnewline");
}
