// dragonbox_test_407.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <cfloat>
#include <limits>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

template <class DecimalFp>
static long double DecimalFpToLongDouble(const DecimalFp& v) {
  // Dragonbox decimal_fp is typically: value = significand * 10^exponent (with optional sign).
  long double sig = static_cast<long double>(v.significand);
  long double p10 = std::powl(10.0L, static_cast<long double>(v.exponent));
  long double out = sig * p10;

  if constexpr (requires { v.is_negative; }) {
    if (v.is_negative) out = -out;
  } else if constexpr (requires { v.sign; }) {
    // Some variants may store sign differently; if present and boolean-like.
    if (static_cast<bool>(v.sign)) out = -out;
  }
  return out;
}

template <class T>
static void ExpectRoundTripOrAdjacent(T x, long double reconstructed) {
  // Convert back through the FP type; allow equality or 1-ULP adjacency to be robust
  // against long double rounding for extreme magnitudes.
  T y = static_cast<T>(reconstructed);
  if (y == x) {
    SUCCEED();
    return;
  }

  const T up = std::nextafter(y, std::numeric_limits<T>::infinity());
  const T dn = std::nextafter(y, -std::numeric_limits<T>::infinity());
  EXPECT_TRUE(up == x || dn == x)
      << "x=" << static_cast<long double>(x)
      << " reconstructed=" << reconstructed
      << " cast=" << static_cast<long double>(y)
      << " nextup=" << static_cast<long double>(up)
      << " nextdn=" << static_cast<long double>(dn);
}

}  // namespace

TEST(DragonboxTest_407, ToDecimalFloatSimpleValues_407) {
  using YAML::jkj::dragonbox::to_decimal;

  // 0.0
  {
    auto d = to_decimal(0.0f);
    EXPECT_EQ(d.significand, 0u);
    // exponent may be 0 for zero in many implementations; if it isn't, we still require
    // the reconstructed value to be 0.0.
    const long double r = DecimalFpToLongDouble(d);
    EXPECT_EQ(static_cast<float>(r), 0.0f);
  }

  // 1.0
  {
    auto d = to_decimal(1.0f);
    EXPECT_EQ(d.significand, 1u);
    EXPECT_EQ(d.exponent, 0);
    ExpectRoundTripOrAdjacent(1.0f, DecimalFpToLongDouble(d));
  }

  // -1.0 (verify sign handling if the return type exposes it)
  {
    auto d = to_decimal(-1.0f);
    EXPECT_EQ(d.significand, 1u);
    EXPECT_EQ(d.exponent, 0);
    if constexpr (requires { d.is_negative; }) {
      EXPECT_TRUE(d.is_negative);
    }
    ExpectRoundTripOrAdjacent(-1.0f, DecimalFpToLongDouble(d));
  }

  // 1.5 -> 15 * 10^-1
  {
    auto d = to_decimal(1.5f);
    EXPECT_EQ(d.significand, 15u);
    EXPECT_EQ(d.exponent, -1);
    ExpectRoundTripOrAdjacent(1.5f, DecimalFpToLongDouble(d));
  }

  // 0.1f should round-trip
  {
    auto d = to_decimal(0.1f);
    ExpectRoundTripOrAdjacent(0.1f, DecimalFpToLongDouble(d));
  }
}

TEST(DragonboxTest_407, ToDecimalDoubleSimpleValues_407) {
  using YAML::jkj::dragonbox::to_decimal;

  // 1.0
  {
    auto d = to_decimal(1.0);
    EXPECT_EQ(d.significand, 1u);
    EXPECT_EQ(d.exponent, 0);
    ExpectRoundTripOrAdjacent(1.0, DecimalFpToLongDouble(d));
  }

  // 1.25 -> 125 * 10^-2
  {
    auto d = to_decimal(1.25);
    EXPECT_EQ(d.significand, 125u);
    EXPECT_EQ(d.exponent, -2);
    ExpectRoundTripOrAdjacent(1.25, DecimalFpToLongDouble(d));
  }

  // -0.0 (sign may be preserved; require numeric value to be zero)
  {
    auto d = to_decimal(-0.0);
    const long double r = DecimalFpToLongDouble(d);
    EXPECT_EQ(static_cast<double>(r), 0.0);
    // If sign is exposed, ensure it's negative.
    if constexpr (requires { d.is_negative; }) {
      EXPECT_TRUE(d.is_negative);
    }
  }
}

TEST(DragonboxTest_407, ToDecimalFloatBoundaryValues_407) {
  using YAML::jkj::dragonbox::to_decimal;

  // Smallest positive subnormal
  {
    const float x = std::numeric_limits<float>::denorm_min();
    auto d = to_decimal(x);
    EXPECT_NE(d.significand, 0u);
    ExpectRoundTripOrAdjacent(x, DecimalFpToLongDouble(d));
  }

  // Smallest positive normal
  {
    const float x = std::numeric_limits<float>::min();
    auto d = to_decimal(x);
    EXPECT_NE(d.significand, 0u);
    ExpectRoundTripOrAdjacent(x, DecimalFpToLongDouble(d));
  }

  // Largest finite
  {
    const float x = std::numeric_limits<float>::max();
    auto d = to_decimal(x);
    EXPECT_NE(d.significand, 0u);
    ExpectRoundTripOrAdjacent(x, DecimalFpToLongDouble(d));
  }
}

TEST(DragonboxTest_407, ToDecimalDoubleBoundaryValues_407) {
  using YAML::jkj::dragonbox::to_decimal;

  // Smallest positive subnormal
  {
    const double x = std::numeric_limits<double>::denorm_min();
    auto d = to_decimal(x);
    EXPECT_NE(d.significand, 0u);
    ExpectRoundTripOrAdjacent(x, DecimalFpToLongDouble(d));
  }

  // Smallest positive normal
  {
    const double x = std::numeric_limits<double>::min();
    auto d = to_decimal(x);
    EXPECT_NE(d.significand, 0u);
    ExpectRoundTripOrAdjacent(x, DecimalFpToLongDouble(d));
  }

  // Largest finite
  {
    const double x = std::numeric_limits<double>::max();
    auto d = to_decimal(x);
    EXPECT_NE(d.significand, 0u);
    ExpectRoundTripOrAdjacent(x, DecimalFpToLongDouble(d));
  }
}

TEST(DragonboxTest_407, ToDecimalIsDeterministic_407) {
  using YAML::jkj::dragonbox::to_decimal;

  const double x = 1234567.890123;
  const auto a = to_decimal(x);
  const auto b = to_decimal(x);

  EXPECT_EQ(a.significand, b.significand);
  EXPECT_EQ(a.exponent, b.exponent);

  if constexpr (requires { a.is_negative; }) {
    EXPECT_EQ(a.is_negative, b.is_negative);
  }
}

TEST(DragonboxTest_407, ToDecimalHandlesFiniteSpecialPatterns_407) {
  using YAML::jkj::dragonbox::to_decimal;

  // A value near a power-of-two boundary; should still round-trip.
  {
    const double x = std::ldexp(1.0, 52) - 1.0;  // 2^52 - 1
    auto d = to_decimal(x);
    ExpectRoundTripOrAdjacent(x, DecimalFpToLongDouble(d));
  }

  // Another tricky value: exactly representable decimal fraction in binary
  {
    const double x = 0.5;  // exact
    auto d = to_decimal(x);
    ExpectRoundTripOrAdjacent(x, DecimalFpToLongDouble(d));
  }
}