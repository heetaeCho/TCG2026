// TEST_ID: 389
//
// Unit tests for:
//   static inline double colToDbl(GfxColorComp x)
//
// File under test:
//   ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "poppler/GfxState.h"

namespace {

class ColToDblTest_389 : public ::testing::Test {};

TEST_F(ColToDblTest_389, ZeroMapsToZero_389) {
  const GfxColorComp x = static_cast<GfxColorComp>(0);
  EXPECT_DOUBLE_EQ(0.0, colToDbl(x));
}

TEST_F(ColToDblTest_389, OneUnitMapsToOne_389) {
  // Boundary: "1.0" should be produced by dividing gfxColorComp1 by itself.
  const GfxColorComp x = static_cast<GfxColorComp>(gfxColorComp1);
  EXPECT_DOUBLE_EQ(1.0, colToDbl(x));
}

TEST_F(ColToDblTest_389, HalfUnitMapsToHalf_389) {
  // Boundary around a common fractional value.
  const GfxColorComp half = static_cast<GfxColorComp>(gfxColorComp1 / 2);
  EXPECT_DOUBLE_EQ(0.5, colToDbl(half));
}

TEST_F(ColToDblTest_389, QuarterUnitMapsToQuarter_389) {
  const GfxColorComp q = static_cast<GfxColorComp>(gfxColorComp1 / 4);
  EXPECT_DOUBLE_EQ(0.25, colToDbl(q));
}

TEST_F(ColToDblTest_389, MaxValueProducesMaxDividedByUnit_389) {
  // Boundary: maximum representable component value for the type.
  const GfxColorComp maxv = (std::numeric_limits<GfxColorComp>::max)();
  const double expected =
      static_cast<double>(maxv) / static_cast<double>(gfxColorComp1);

  const double actual = colToDbl(maxv);

  // Use DOUBLE_EQ: both are computed with the same arithmetic in double.
  EXPECT_DOUBLE_EQ(expected, actual);

  // Basic sanity: result should be finite for normal integer-like GfxColorComp.
  EXPECT_TRUE(std::isfinite(actual));
}

}  // namespace