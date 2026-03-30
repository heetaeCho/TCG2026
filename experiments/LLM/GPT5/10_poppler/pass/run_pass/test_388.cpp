// TEST_ID: 388
// Unit tests for dblToCol(double) in poppler/GfxState.h

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <type_traits>

#include "GfxState.h"

class DblToColTest_388 : public ::testing::Test {};

TEST_F(DblToColTest_388, ReturnsZeroForZero_388) {
  EXPECT_EQ(dblToCol(0.0), static_cast<GfxColorComp>(0));
}

TEST_F(DblToColTest_388, ScalesOneToGfxColorComp1_388) {
  // Expect exact scaling of 1.0 by gfxColorComp1 with cast to GfxColorComp.
  const GfxColorComp expected = static_cast<GfxColorComp>(1.0 * gfxColorComp1);
  EXPECT_EQ(dblToCol(1.0), expected);
}

TEST_F(DblToColTest_388, ScalesFractionalValue_388) {
  const double x = 0.5;
  const GfxColorComp expected = static_cast<GfxColorComp>(x * gfxColorComp1);
  EXPECT_EQ(dblToCol(x), expected);
}

TEST_F(DblToColTest_388, TruncatesTowardZeroForPositiveFraction_388) {
  // For integer GfxColorComp, conversion from double truncates toward zero.
  // Pick a value just below 0.5 to ensure truncation behavior is observable.
  const double x = 0.5 - (1.0 / (gfxColorComp1 * 4.0));
  const GfxColorComp expected = static_cast<GfxColorComp>(x * gfxColorComp1);
  EXPECT_EQ(dblToCol(x), expected);
}

TEST_F(DblToColTest_388, TruncatesTowardZeroForNegativeFraction_388) {
  // Keep magnitude small to avoid any range issues.
  const double x = -0.5;
  const GfxColorComp expected = static_cast<GfxColorComp>(x * gfxColorComp1);
  EXPECT_EQ(dblToCol(x), expected);
}

TEST_F(DblToColTest_388, HandlesNearIntegerBoundary_388) {
  // Value that should convert very close to an integer after scaling.
  const double x = 1.0 + (1.0 / gfxColorComp1);  // scaled: gfxColorComp1 + 1
  const GfxColorComp expected = static_cast<GfxColorComp>(x * gfxColorComp1);
  EXPECT_EQ(dblToCol(x), expected);
}

TEST_F(DblToColTest_388, WithinTypeRangeNearMaximum_388) {
  // Choose x such that x * gfxColorComp1 stays within GfxColorComp range.
  using Lim = std::numeric_limits<GfxColorComp>;
  static_assert(Lim::is_integer, "These tests assume GfxColorComp is an integer type.");

  const auto maxv = Lim::max();
  const auto target = static_cast<long double>(maxv) - 1.0L;
  const long double x_ld = target / static_cast<long double>(gfxColorComp1);
  const double x = static_cast<double>(x_ld);

  const GfxColorComp expected = static_cast<GfxColorComp>(x * gfxColorComp1);
  EXPECT_EQ(dblToCol(x), expected);
}

TEST_F(DblToColTest_388, WithinTypeRangeNearMinimumWhenSigned_388) {
  using Lim = std::numeric_limits<GfxColorComp>;
  static_assert(Lim::is_integer, "These tests assume GfxColorComp is an integer type.");

  if constexpr (Lim::is_signed) {
    const auto minv = Lim::min();
    const auto target = static_cast<long double>(minv) + 1.0L;
    const long double x_ld = target / static_cast<long double>(gfxColorComp1);
    const double x = static_cast<double>(x_ld);

    const GfxColorComp expected = static_cast<GfxColorComp>(x * gfxColorComp1);
    EXPECT_EQ(dblToCol(x), expected);
  } else {
    GTEST_SKIP() << "GfxColorComp is unsigned; minimum-range signed test not applicable.";
  }
}

TEST_F(DblToColTest_388, CanBeEvaluatedAtCompileTime_388) {
  // dblToCol is constexpr; validate with a constexpr computation.
  constexpr double x = 0.25;
  constexpr GfxColorComp v = dblToCol(x);
  constexpr GfxColorComp expected = static_cast<GfxColorComp>(x * gfxColorComp1);
  static_assert(v == expected, "dblToCol should be constexpr and match expected scaling.");
  EXPECT_EQ(v, expected);
}