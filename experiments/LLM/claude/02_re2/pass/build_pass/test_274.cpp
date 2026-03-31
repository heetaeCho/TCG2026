#include <gtest/gtest.h>
#include <cmath>
#include <string>
#include <limits>

// We need to access the Parse function template specialization
namespace re2 {
namespace re2_internal {
template <typename T>
bool Parse(const char* str, size_t n, T* dest);

template <>
bool Parse(const char* str, size_t n, double* dest);
}
}

using re2::re2_internal::Parse;

// Normal operation tests

TEST(ParseDoubleTest_274, ParseSimpleInteger_274) {
  double result = 0.0;
  const char* str = "42";
  EXPECT_TRUE(Parse(str, 2, &result));
  EXPECT_DOUBLE_EQ(42.0, result);
}

TEST(ParseDoubleTest_274, ParseSimpleFloat_274) {
  double result = 0.0;
  const char* str = "3.14";
  EXPECT_TRUE(Parse(str, 4, &result));
  EXPECT_DOUBLE_EQ(3.14, result);
}

TEST(ParseDoubleTest_274, ParseNegativeNumber_274) {
  double result = 0.0;
  const char* str = "-2.5";
  EXPECT_TRUE(Parse(str, 4, &result));
  EXPECT_DOUBLE_EQ(-2.5, result);
}

TEST(ParseDoubleTest_274, ParseZero_274) {
  double result = 1.0;
  const char* str = "0";
  EXPECT_TRUE(Parse(str, 1, &result));
  EXPECT_DOUBLE_EQ(0.0, result);
}

TEST(ParseDoubleTest_274, ParseScientificNotation_274) {
  double result = 0.0;
  const char* str = "1.5e10";
  EXPECT_TRUE(Parse(str, 6, &result));
  EXPECT_DOUBLE_EQ(1.5e10, result);
}

TEST(ParseDoubleTest_274, ParseScientificNotationNegativeExponent_274) {
  double result = 0.0;
  const char* str = "1.5e-3";
  EXPECT_TRUE(Parse(str, 6, &result));
  EXPECT_DOUBLE_EQ(1.5e-3, result);
}

TEST(ParseDoubleTest_274, ParseScientificNotationUpperE_274) {
  double result = 0.0;
  const char* str = "2.5E4";
  EXPECT_TRUE(Parse(str, 5, &result));
  EXPECT_DOUBLE_EQ(2.5e4, result);
}

TEST(ParseDoubleTest_274, ParsePositiveSign_274) {
  double result = 0.0;
  const char* str = "+7.5";
  EXPECT_TRUE(Parse(str, 4, &result));
  EXPECT_DOUBLE_EQ(7.5, result);
}

TEST(ParseDoubleTest_274, ParseLeadingDot_274) {
  double result = 0.0;
  const char* str = ".25";
  EXPECT_TRUE(Parse(str, 3, &result));
  EXPECT_DOUBLE_EQ(0.25, result);
}

TEST(ParseDoubleTest_274, ParseTrailingDot_274) {
  double result = 0.0;
  const char* str = "5.";
  EXPECT_TRUE(Parse(str, 2, &result));
  EXPECT_DOUBLE_EQ(5.0, result);
}

// Null destination test (should return true without writing)

TEST(ParseDoubleTest_274, NullDestReturnsTrue_274) {
  const char* str = "42.0";
  EXPECT_TRUE(Parse(str, 4, static_cast<double*>(nullptr)));
}

// Boundary condition tests

TEST(ParseDoubleTest_274, EmptyStringReturnsFalse_274) {
  double result = 0.0;
  const char* str = "";
  EXPECT_FALSE(Parse(str, 0, &result));
}

TEST(ParseDoubleTest_274, ZeroLengthReturnsFalse_274) {
  double result = 0.0;
  const char* str = "123";
  EXPECT_FALSE(Parse(str, 0, &result));
}

TEST(ParseDoubleTest_274, SingleDigit_274) {
  double result = 0.0;
  const char* str = "7";
  EXPECT_TRUE(Parse(str, 1, &result));
  EXPECT_DOUBLE_EQ(7.0, result);
}

TEST(ParseDoubleTest_274, VerySmallNumber_274) {
  double result = 0.0;
  const char* str = "1e-300";
  EXPECT_TRUE(Parse(str, 6, &result));
  EXPECT_DOUBLE_EQ(1e-300, result);
}

TEST(ParseDoubleTest_274, VeryLargeNumber_274) {
  double result = 0.0;
  const char* str = "1e300";
  EXPECT_TRUE(Parse(str, 5, &result));
  EXPECT_DOUBLE_EQ(1e300, result);
}

// Error / exceptional cases

TEST(ParseDoubleTest_274, NonNumericStringReturnsFalse_274) {
  double result = 0.0;
  const char* str = "abc";
  EXPECT_FALSE(Parse(str, 3, &result));
}

TEST(ParseDoubleTest_274, MixedContentReturnsFalse_274) {
  double result = 0.0;
  const char* str = "12abc";
  EXPECT_FALSE(Parse(str, 5, &result));
}

TEST(ParseDoubleTest_274, TrailingSpaceReturnsFalse_274) {
  double result = 0.0;
  const char* str = "42 ";
  EXPECT_FALSE(Parse(str, 3, &result));
}

TEST(ParseDoubleTest_274, LeadingSpaceMayFail_274) {
  double result = 0.0;
  const char* str = " 42";
  // strtod typically handles leading spaces, so it might pass or fail
  // depending on TerminateNumber behavior. We just check it doesn't crash.
  Parse(str, 3, &result);
}

TEST(ParseDoubleTest_274, OverflowReturnsFalse_274) {
  double result = 0.0;
  const char* str = "1e9999";
  EXPECT_FALSE(Parse(str, 6, &result));
}

TEST(ParseDoubleTest_274, NegativeOverflowReturnsFalse_274) {
  double result = 0.0;
  const char* str = "-1e9999";
  EXPECT_FALSE(Parse(str, 7, &result));
}

TEST(ParseDoubleTest_274, JustMinusSignReturnsFalse_274) {
  double result = 0.0;
  const char* str = "-";
  EXPECT_FALSE(Parse(str, 1, &result));
}

TEST(ParseDoubleTest_274, JustPlusSignReturnsFalse_274) {
  double result = 0.0;
  const char* str = "+";
  EXPECT_FALSE(Parse(str, 1, &result));
}

TEST(ParseDoubleTest_274, JustDotReturnsFalse_274) {
  double result = 0.0;
  const char* str = ".";
  // "." alone is not a valid number for strtod
  EXPECT_FALSE(Parse(str, 1, &result));
}

TEST(ParseDoubleTest_274, NullDestWithEmptyStringReturnsFalse_274) {
  const char* str = "";
  EXPECT_FALSE(Parse(str, 0, static_cast<double*>(nullptr)));
}

TEST(ParseDoubleTest_274, NullDestWithInvalidStringReturnsFalse_274) {
  const char* str = "abc";
  EXPECT_FALSE(Parse(str, 3, static_cast<double*>(nullptr)));
}

TEST(ParseDoubleTest_274, ParseNegativeZero_274) {
  double result = 1.0;
  const char* str = "-0";
  EXPECT_TRUE(Parse(str, 2, &result));
  EXPECT_DOUBLE_EQ(0.0, result);
}

TEST(ParseDoubleTest_274, ParseNegativeFloat_274) {
  double result = 0.0;
  const char* str = "-0.001";
  EXPECT_TRUE(Parse(str, 6, &result));
  EXPECT_DOUBLE_EQ(-0.001, result);
}

TEST(ParseDoubleTest_274, LongButValidNumber_274) {
  // A number within the 200-char buffer limit
  std::string s = "1.";
  for (int i = 0; i < 100; i++) s += "1";
  double result = 0.0;
  EXPECT_TRUE(Parse(s.c_str(), s.size(), &result));
  EXPECT_GT(result, 1.0);
  EXPECT_LT(result, 2.0);
}

TEST(ParseDoubleTest_274, VeryLongStringExceedingBuffer_274) {
  // A number exceeding the 200-char buffer limit
  std::string s = "1.";
  for (int i = 0; i < 300; i++) s += "0";
  double result = 0.0;
  // The behavior may vary; we just ensure it doesn't crash
  Parse(s.c_str(), s.size(), &result);
}

TEST(ParseDoubleTest_274, PartialLengthParsing_274) {
  double result = 0.0;
  const char* str = "12345";
  // Only parse first 3 characters: "123"
  EXPECT_TRUE(Parse(str, 3, &result));
  EXPECT_DOUBLE_EQ(123.0, result);
}

TEST(ParseDoubleTest_274, PartialLengthWithTrailingNonDigit_274) {
  double result = 0.0;
  const char* str = "12.5xyz";
  // Only parse first 4 characters: "12.5"
  EXPECT_TRUE(Parse(str, 4, &result));
  EXPECT_DOUBLE_EQ(12.5, result);
}
