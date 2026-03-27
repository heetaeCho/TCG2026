// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_string_to_float_948.cpp
//
// Unit tests for:
//   Exiv2::Internal::string_to_float(std::string_view)
//
// Constraints respected:
// - Treat implementation as black box (test only observable behavior: return value / thrown Error)
// - No private state access
// - No re-implementation of parsing logic

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <string_view>

#include "exiv2/error.hpp"

// Forward declaration (function is defined in canonmn_int.cpp inside Exiv2::Internal)
namespace Exiv2::Internal {
float string_to_float(std::string_view str);
}

namespace {

class StringToFloatTest_948 : public ::testing::Test {};

TEST_F(StringToFloatTest_948, ParsesInteger_948) {
  const float v = Exiv2::Internal::string_to_float("123");
  EXPECT_FLOAT_EQ(v, 123.0f);
}

TEST_F(StringToFloatTest_948, ParsesNegativeInteger_948) {
  const float v = Exiv2::Internal::string_to_float("-7");
  EXPECT_FLOAT_EQ(v, -7.0f);
}

TEST_F(StringToFloatTest_948, ParsesDecimal_948) {
  const float v = Exiv2::Internal::string_to_float("3.5");
  EXPECT_FLOAT_EQ(v, 3.5f);
}

TEST_F(StringToFloatTest_948, ParsesLeadingTrailingWhitespace_948) {
  const float v = Exiv2::Internal::string_to_float(" \t\n 42.25 \r\n");
  EXPECT_FLOAT_EQ(v, 42.25f);
}

TEST_F(StringToFloatTest_948, ParsesExponent_948) {
  const float v1 = Exiv2::Internal::string_to_float("1e2");
  const float v2 = Exiv2::Internal::string_to_float("-2.5E1");
  EXPECT_FLOAT_EQ(v1, 100.0f);
  EXPECT_FLOAT_EQ(v2, -25.0f);
}

TEST_F(StringToFloatTest_948, ParsesPlusSign_948) {
  const float v = Exiv2::Internal::string_to_float("+12.0");
  EXPECT_FLOAT_EQ(v, 12.0f);
}

TEST_F(StringToFloatTest_948, ParsesNegativeZero_948) {
  const float v = Exiv2::Internal::string_to_float("-0");
  EXPECT_FLOAT_EQ(v, 0.0f);
  EXPECT_TRUE(std::signbit(v)) << "Expected negative sign bit for -0 if preserved by parsing";
}

TEST_F(StringToFloatTest_948, ParsesInfinityToken_948) {
  const float v = Exiv2::Internal::string_to_float("inf");
  EXPECT_TRUE(std::isinf(v));
  EXPECT_FALSE(std::signbit(v));
}

TEST_F(StringToFloatTest_948, ParsesNegativeInfinityToken_948) {
  const float v = Exiv2::Internal::string_to_float("-inf");
  EXPECT_TRUE(std::isinf(v));
  EXPECT_TRUE(std::signbit(v));
}

TEST_F(StringToFloatTest_948, ParsesNanToken_948) {
  const float v = Exiv2::Internal::string_to_float("nan");
  EXPECT_TRUE(std::isnan(v));
}

TEST_F(StringToFloatTest_948, EmptyStringThrowsError_948) {
  try {
    (void)Exiv2::Internal::string_to_float("");
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Observable through interface: throws Error; (ErrorCode not guaranteed exposed here)
    // Keep assertions minimal to avoid relying on internal formatting.
    SUCCEED();
    (void)e;
  }
}

TEST_F(StringToFloatTest_948, NonNumericThrowsError_948) {
  try {
    (void)Exiv2::Internal::string_to_float("not-a-number");
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    SUCCEED();
    (void)e;
  }
}

TEST_F(StringToFloatTest_948, LocaleCommaDecimalIsRejected_948) {
  // Implementation explicitly imbues "C" locale, so "1,5" should not parse as 1.5.
  // We only check observable behavior: it must not succeed parsing to 1.5.
  // Most stream extractions will fail => throw.
  EXPECT_THROW((void)Exiv2::Internal::string_to_float("1,5"), Exiv2::Error);
}

TEST_F(StringToFloatTest_948, BoundaryVeryLargeExponentDoesNotCrash_948) {
  // Boundary/robustness: ensure it either returns a finite/inf float or throws,
  // but never causes undefined behavior visible here.
  // Use EXPECT_NO_FATAL_FAILURE style by just handling both outcomes.
  try {
    const float v = Exiv2::Internal::string_to_float("1e39");  // beyond float max exponent in many libs
    // If it succeeds, it should be either inf or a very large finite number.
    EXPECT_TRUE(std::isinf(v) || std::isfinite(v));
  } catch (const Exiv2::Error&) {
    SUCCEED();
  }
}

TEST_F(StringToFloatTest_948, BoundarySmallSubnormalOrZeroDoesNotCrash_948) {
  try {
    const float v = Exiv2::Internal::string_to_float("1e-50");
    // If parsing succeeds, it may underflow to 0 or become subnormal; both are acceptable.
    EXPECT_TRUE(v == 0.0f || (std::isfinite(v) && v > 0.0f));
  } catch (const Exiv2::Error&) {
    SUCCEED();
  }
}

}  // namespace