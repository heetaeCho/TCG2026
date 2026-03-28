// File: parse_double_tests_274.cc
#include <gtest/gtest.h>
#include <cstddef>

namespace re2 { namespace re2_internal {
// Forward-declare the specialization under test.
template <> bool Parse(const char* str, size_t n, double* dest);
}}

// Small helper for numeric comparisons without assuming internal behavior.
static ::testing::AssertionResult Near(double actual, double expected, double tol = 1e-12) {
  if (std::abs(actual - expected) <= tol) return ::testing::AssertionSuccess();
  return ::testing::AssertionFailure()
         << "actual " << actual << " not within " << tol << " of expected " << expected;
}

using re2::re2_internal::Parse;

TEST(ParseDoubleTest_274, EmptyStringReturnsFalse_274) {
  double out = 0.0;
  const char* s = "";
  EXPECT_FALSE(Parse(s, 0, &out));
}

TEST(ParseDoubleTest_274, ValidIntegerParsesAndSetsDest_274) {
  double out = 0.0;
  const char* s = "42";
  ASSERT_TRUE(Parse(s, 2, &out));
  EXPECT_TRUE(Near(out, 42.0));
}

TEST(ParseDoubleTest_274, ValidFloatParsesAndSetsDest_274) {
  double out = 0.0;
  const char* s = "3.14159";
  ASSERT_TRUE(Parse(s, 7, &out));
  EXPECT_TRUE(Near(out, 3.14159, 1e-15));
}

TEST(ParseDoubleTest_274, ScientificNotationParses_274) {
  double out = 0.0;
  const char* s = "2.5e-3";
  ASSERT_TRUE(Parse(s, 6, &out));
  EXPECT_TRUE(Near(out, 0.0025));
}

TEST(ParseDoubleTest_274, UsesOnlyFirstNCharacters_274) {
  // Only the first 3 chars ("123") should be considered even though the buffer is longer.
  double out = 0.0;
  const char* s = "12345";
  ASSERT_TRUE(Parse(s, 3, &out));
  EXPECT_TRUE(Near(out, 123.0));
}

TEST(ParseDoubleTest_274, DestNullStillValidatesAndReturnsTrue_274) {
  // When dest == nullptr and the input is valid, Parse should succeed and not dereference dest.
  const char* s = "99.5";
  EXPECT_TRUE(Parse(s, 4, nullptr));
}

TEST(ParseDoubleTest_274, LeftoverJunkCausesFailure_274) {
  double out = 0.0;
  const char* s = "12x";
  EXPECT_FALSE(Parse(s, 3, &out));
}

TEST(ParseDoubleTest_274, OverflowSetsErrnoAndCausesFailure_274) {
  // A very large exponent should overflow a double in strtod on typical platforms.
  // We only assert the observable behavior: Parse returns false.
  double out = 0.0;
  const char* s = "1e4000";
  EXPECT_FALSE(Parse(s, 6, &out));
}

TEST(ParseDoubleTest_274, NegativeZeroParses_274) {
  double out = 1.0;  // seed with non-zero
  const char* s = "-0.0";
  ASSERT_TRUE(Parse(s, 4, &out));
  // Observable check: result equals 0.0 within tolerance; sign is not asserted.
  EXPECT_TRUE(Near(out, 0.0));
}
