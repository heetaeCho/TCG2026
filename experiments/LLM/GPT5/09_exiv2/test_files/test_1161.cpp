// File: test_types_floatToRationalCast_1161.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>
#include <numeric>

#include "exiv2/types.hpp"

namespace {

// Helper: convert Rational to double (handles sentinel den==0)
double ToDouble(const Exiv2::Rational& r) {
  const auto num = static_cast<double>(r.first);
  const auto den = static_cast<double>(r.second);
  if (r.second == 0) return (r.first >= 0) ? std::numeric_limits<double>::infinity()
                                           : -std::numeric_limits<double>::infinity();
  return num / den;
}

// Helper: check reduced form when den!=0 and num!=0
bool IsReduced(const Exiv2::Rational& r) {
  if (r.second == 0) return true;  // sentinel case, not a normal rational
  if (r.first == 0) return true;   // allow any (implementation may normalize)
  const auto a = static_cast<int32_t>(std::abs(static_cast<long long>(r.first)));
  const auto b = static_cast<int32_t>(std::abs(static_cast<long long>(r.second)));
  return std::gcd(a, b) == 1;
}

class FloatToRationalCastTest_1161 : public ::testing::Test {};

}  // namespace

TEST_F(FloatToRationalCastTest_1161, ZeroProducesZeroValue_1161) {
  const Exiv2::Rational r = Exiv2::floatToRationalCast(0.0f);

  EXPECT_EQ(r.first, 0);
  EXPECT_NE(r.second, 0) << "Zero should be representable as a finite rational";
  EXPECT_DOUBLE_EQ(ToDouble(r), 0.0);
  EXPECT_TRUE(IsReduced(r));
}

TEST_F(FloatToRationalCastTest_1161, SimplePositiveValueIsAccurate_1161) {
  const float input = 1.5f;
  const Exiv2::Rational r = Exiv2::floatToRationalCast(input);

  EXPECT_NE(r.second, 0);
  EXPECT_NEAR(ToDouble(r), static_cast<double>(input), 1e-12);
  EXPECT_TRUE(IsReduced(r));
}

TEST_F(FloatToRationalCastTest_1161, SimpleNegativeValueIsAccurate_1161) {
  const float input = -2.75f;
  const Exiv2::Rational r = Exiv2::floatToRationalCast(input);

  EXPECT_NE(r.second, 0);
  EXPECT_NEAR(ToDouble(r), static_cast<double>(input), 1e-12);
  EXPECT_TRUE(IsReduced(r));
}

TEST_F(FloatToRationalCastTest_1161, VerySmallMagnitudeRemainsFiniteAndAccurate_1161) {
  const float input = 1.0e-6f;
  const Exiv2::Rational r = Exiv2::floatToRationalCast(input);

  EXPECT_NE(r.second, 0);
  // Float->double conversion and rounding may introduce slight error; allow a small tolerance.
  EXPECT_NEAR(ToDouble(r), static_cast<double>(input), 1e-12);
  EXPECT_TRUE(IsReduced(r));
}

TEST_F(FloatToRationalCastTest_1161, LargeFiniteValueRemainsFiniteOrSignalsOverflow_1161) {
  // Use a large finite value (not infinity).
  const float input = 1.0e20f;
  ASSERT_TRUE(std::isfinite(input));

  const Exiv2::Rational r = Exiv2::floatToRationalCast(input);

  if (r.second == 0) {
    // If the implementation signals overflow, verify sign behavior is consistent.
    EXPECT_GT(r.first, 0);
  } else {
    // Otherwise it should still approximate the input.
    EXPECT_NEAR(ToDouble(r), static_cast<double>(input), 1e8);  // wide tolerance at huge scale
    EXPECT_TRUE(IsReduced(r));
  }
}

TEST_F(FloatToRationalCastTest_1161, PositiveInfinitySignalsOverflowSentinel_1161) {
  const float input = std::numeric_limits<float>::infinity();
  const Exiv2::Rational r = Exiv2::floatToRationalCast(input);

  EXPECT_EQ(r.second, 0);
  EXPECT_GT(r.first, 0);
}

TEST_F(FloatToRationalCastTest_1161, NegativeInfinitySignalsOverflowSentinel_1161) {
  const float input = -std::numeric_limits<float>::infinity();
  const Exiv2::Rational r = Exiv2::floatToRationalCast(input);

  EXPECT_EQ(r.second, 0);
  EXPECT_LT(r.first, 0);
}

TEST_F(FloatToRationalCastTest_1161, NaNSignalsOverflowSentinelWithNonPositiveSign_1161) {
  const float input = std::numeric_limits<float>::quiet_NaN();
  ASSERT_TRUE(std::isnan(input));

  const Exiv2::Rational r = Exiv2::floatToRationalCast(input);

  EXPECT_EQ(r.second, 0);
  // For NaN, the sign is not meaningful; just verify it is not positive.
  EXPECT_LE(r.first, 0);
}