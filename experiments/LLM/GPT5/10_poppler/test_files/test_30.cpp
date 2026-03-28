// SPDX-License-Identifier: GPL-2.0-or-later
// File: gstrtod_gatof_test_30.cc
//
// Unit tests for:
//   double gatof(const char* nptr);
//
// Constraints honored:
// - Treat implementation as a black box.
// - Test only observable behavior via the public function signature.

#include <gtest/gtest.h>

#include <cmath>
#include <cfloat>
#include <limits>

// Forward declaration (avoids depending on internal headers/paths).
// The implementation is provided by ./TestProjects/poppler/goo/gstrtod.cc
double gatof(const char* nptr);

namespace {

class GatofTest_30 : public ::testing::Test {};

TEST_F(GatofTest_30, ParsesSimpleIntegers_30) {
  EXPECT_DOUBLE_EQ(gatof("0"), 0.0);
  EXPECT_DOUBLE_EQ(gatof("1"), 1.0);
  EXPECT_DOUBLE_EQ(gatof("-2"), -2.0);
  EXPECT_DOUBLE_EQ(gatof("42"), 42.0);
}

TEST_F(GatofTest_30, ParsesWhitespaceAndSign_30) {
  EXPECT_DOUBLE_EQ(gatof("   7"), 7.0);
  EXPECT_DOUBLE_EQ(gatof("  -8"), -8.0);
  EXPECT_DOUBLE_EQ(gatof("\t\n +9"), 9.0);
}

TEST_F(GatofTest_30, ParsesExactBinaryFractions_30) {
  // These are exactly representable in binary floating point.
  EXPECT_DOUBLE_EQ(gatof("1.5"), 1.5);
  EXPECT_DOUBLE_EQ(gatof("-2.25"), -2.25);
  EXPECT_DOUBLE_EQ(gatof("0.125"), 0.125);  // 1/8
}

TEST_F(GatofTest_30, ParsesExponentNotation_30) {
  EXPECT_DOUBLE_EQ(gatof("1e3"), 1000.0);
  EXPECT_DOUBLE_EQ(gatof("-2E2"), -200.0);

  // Not exactly representable; use a tight tolerance.
  EXPECT_NEAR(gatof("1e-3"), 0.001, 1e-15);
  EXPECT_NEAR(gatof("-3.5e-2"), -0.035, 1e-15);
}

TEST_F(GatofTest_30, StopsParsingAtFirstInvalidCharacter_30) {
  // Observable behavior: parsing a valid numeric prefix should yield that value.
  EXPECT_DOUBLE_EQ(gatof("12abc"), 12.0);
  EXPECT_DOUBLE_EQ(gatof("  -3.0xyz"), -3.0);
  EXPECT_DOUBLE_EQ(gatof("5.5  trailing"), 5.5);
}

TEST_F(GatofTest_30, EmptyOrNonNumericInputYieldsZero_30) {
  // With no endptr exposed, we can only verify the returned value.
  EXPECT_DOUBLE_EQ(gatof(""), 0.0);
  EXPECT_DOUBLE_EQ(gatof("   "), 0.0);
  EXPECT_DOUBLE_EQ(gatof("abc"), 0.0);
  EXPECT_DOUBLE_EQ(gatof("+-"), 0.0);
}

TEST_F(GatofTest_30, HandlesVeryLargeMagnitudeInputWithoutNaN_30) {
  // Keep expectation broad but still observable/deterministic:
  // - Result should not be NaN for a syntactically numeric string.
  // - It may be finite or infinite depending on implementation/limits.
  const double v = gatof("1e309");
  EXPECT_FALSE(std::isnan(v));

  const double w = gatof("-1e309");
  EXPECT_FALSE(std::isnan(w));
}

TEST_F(GatofTest_30, RoundTripForCommonValues_30) {
  // A few representative values; compare with tolerance for non-exact cases.
  struct Case {
    const char* s;
    double expected;
    double tol;
  };

  const Case cases[] = {
      {"3.141592653589793", 3.141592653589793, 1e-15},
      {"2.718281828459045", 2.718281828459045, 1e-15},
      {"0.000000000000001", 1e-15, 1e-30},
      {"-123456.75", -123456.75, 0.0},  // exactly representable (.75 = 3/4)
  };

  for (const auto& c : cases) {
    const double got = gatof(c.s);
    if (c.tol == 0.0) {
      EXPECT_DOUBLE_EQ(got, c.expected) << "input: " << c.s;
    } else {
      EXPECT_NEAR(got, c.expected, c.tol) << "input: " << c.s;
    }
  }
}

}  // namespace