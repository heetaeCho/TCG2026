// TEST_ID: 431
//
// Unit tests for YAML::detail::fp_formatting::FpToString
//
// Notes:
// - We treat FpToString as a black box and only verify observable output.
// - This is a function template defined in a .cpp in the provided snippet.
//   To make it available to the tests (and avoid relying on hidden explicit instantiations),
//   we include the implementation file here.

#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <cmath>
#include <limits>
#include <string>

// Include the production implementation so the template definition is visible here.
#include "TestProjects/yaml-cpp/src/fptostring.cpp"

namespace {

std::string ToLowerAscii(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return s;
}

bool ContainsCaseInsensitive(const std::string& haystack, const std::string& needle) {
  return ToLowerAscii(haystack).find(ToLowerAscii(needle)) != std::string::npos;
}

bool HasExponentMarker(const std::string& s) {
  return s.find('e') != std::string::npos || s.find('E') != std::string::npos;
}

double ParseDoubleOrNaN(const std::string& s) {
  // std::stod accepts "inf", "-inf", "nan" on common libstdc++/libc++ implementations,
  // but we don't require it for NaN/Inf tests. Used for round-trip tests only.
  try {
    size_t idx = 0;
    double v = std::stod(s, &idx);
    if (idx != s.size()) return std::numeric_limits<double>::quiet_NaN();
    return v;
  } catch (...) {
    return std::numeric_limits<double>::quiet_NaN();
  }
}

}  // namespace

TEST(FpToStringTest_431, ZeroAndSpecialValues_431) {
  using YAML::detail::fp_formatting::FpToString;

  const std::string z = FpToString(0.0);
  EXPECT_TRUE(z == "0" || z == "0.0" || z == "0.000000" || z == "-0")
      << "Unexpected zero formatting: '" << z << "'";

  const std::string pinf = FpToString(std::numeric_limits<double>::infinity());
  EXPECT_TRUE(ContainsCaseInsensitive(pinf, "inf")) << "Expected inf, got: '" << pinf << "'";

  const std::string ninf = FpToString(-std::numeric_limits<double>::infinity());
  EXPECT_TRUE(ContainsCaseInsensitive(ninf, "inf")) << "Expected -inf, got: '" << ninf << "'";
  EXPECT_FALSE(ninf.empty());
  EXPECT_EQ(ninf.front(), '-') << "Expected negative sign for -inf: '" << ninf << "'";

  const std::string nanv = FpToString(std::numeric_limits<double>::quiet_NaN());
  EXPECT_TRUE(ContainsCaseInsensitive(nanv, "nan")) << "Expected nan, got: '" << nanv << "'";
}

TEST(FpToStringTest_431, NegativeZeroIsStable_431) {
  using YAML::detail::fp_formatting::FpToString;

  const double neg_zero = -0.0;
  const std::string s = FpToString(neg_zero);

  // Different standard libraries may render "-0" or "0" for -0.0 in default formatting.
  EXPECT_TRUE(s == "-0" || s == "0" || s == "-0.0" || s == "0.0" || s == "-0.000000" ||
              s == "0.000000")
      << "Unexpected -0 formatting: '" << s << "'";
}

TEST(FpToStringTest_431, UsesScientificForLargeMagnitudeWithDefaultPrecision_431) {
  using YAML::detail::fp_formatting::FpToString;

  // For default precision behavior, verify that sufficiently large exponents choose scientific.
  EXPECT_TRUE(HasExponentMarker(FpToString(1e6))) << "Expected scientific for 1e6";
  EXPECT_TRUE(HasExponentMarker(FpToString(1e7))) << "Expected scientific for 1e7";

  // And that a smaller magnitude does not necessarily require scientific.
  EXPECT_FALSE(HasExponentMarker(FpToString(1e5))) << "Did not expect scientific for 1e5";
}

TEST(FpToStringTest_431, UsesScientificForSmallMagnitudeWithDefaultPrecision_431) {
  using YAML::detail::fp_formatting::FpToString;

  // For default precision behavior, verify that sufficiently small exponents choose scientific.
  EXPECT_TRUE(HasExponentMarker(FpToString(1e-5))) << "Expected scientific for 1e-5";

  // And that a slightly larger value stays in non-scientific formatting.
  EXPECT_FALSE(HasExponentMarker(FpToString(1e-4))) << "Did not expect scientific for 1e-4";
}

TEST(FpToStringTest_431, PrecisionAffectsExponentThreshold_431) {
  using YAML::detail::fp_formatting::FpToString;

  // When precision != 0, the "upper exponent threshold" depends on precision.
  // With precision=2, an exponent of 2 should trigger scientific output.
  EXPECT_TRUE(HasExponentMarker(FpToString(123.0, /*precision=*/2)))
      << "Expected scientific for 123 with precision=2";

  // Exponent 1 should typically not trigger scientific output for precision=2.
  EXPECT_FALSE(HasExponentMarker(FpToString(12.0, /*precision=*/2)))
      << "Did not expect scientific for 12 with precision=2";
}

TEST(FpToStringTest_431, RespectsSignForFiniteNumbers_431) {
  using YAML::detail::fp_formatting::FpToString;

  const std::string neg = FpToString(-123.456);
  ASSERT_FALSE(neg.empty());
  EXPECT_EQ(neg.front(), '-') << "Expected leading '-' for negative value: '" << neg << "'";

  const std::string pos = FpToString(123.456);
  ASSERT_FALSE(pos.empty());
  EXPECT_NE(pos.front(), '-') << "Did not expect leading '-' for positive value: '" << pos << "'";
}

TEST(FpToStringTest_431, OutputIsParseableForTypicalFiniteValues_431) {
  using YAML::detail::fp_formatting::FpToString;

  const double v = 1.234567;  // should be representable well enough for a round-trip at ~6 digits
  const std::string s = FpToString(v);
  const double parsed = ParseDoubleOrNaN(s);

  ASSERT_FALSE(std::isnan(parsed)) << "Expected parseable numeric output, got: '" << s << "'";
  // Default formatting uses a limited number of significant digits; allow a small tolerance.
  EXPECT_NEAR(parsed, v, 1e-6) << "Round-trip mismatch for '" << s << "'";
}

TEST(FpToStringTest_431, CanEmitManyTrailingZerosWhenNotUsingScientific_431) {
  using YAML::detail::fp_formatting::FpToString;

  // Use a large precision to avoid switching to scientific for exponent 20.
  const std::string s = FpToString(1e20, /*precision=*/30);

  // 1e20 should be exactly representable as "1" followed by 20 zeros in decimal string form.
  // This also exercises the code path that may append "overflow_zeros".
  EXPECT_EQ(s, "100000000000000000000") << "Unexpected formatting for 1e20: '" << s << "'";
}