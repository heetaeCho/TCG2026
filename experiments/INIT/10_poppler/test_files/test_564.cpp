// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_gfxstate_getHDPI_564.cc

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "GfxState.h"

// NOTE:
// - These tests treat GfxState as a black box.
// - We only verify observable behavior via the public interface: getHDPI().
// - Construction is done through the public constructor signature.

class GfxStateTest_564 : public ::testing::Test {
protected:
  PDFRectangle pageBox_{0.0, 0.0, 612.0, 792.0}; // typical US Letter in points (just a valid rectangle)
};

TEST_F(GfxStateTest_564, GetHDPI_ReturnsConstructorValue_564)
{
  const double hDPI = 72.0;
  const double vDPI = 144.0;

  const GfxState state(hDPI, vDPI, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
  EXPECT_DOUBLE_EQ(state.getHDPI(), hDPI);
}

TEST_F(GfxStateTest_564, GetHDPI_WorksOnConstObject_564)
{
  const double hDPI = 96.0;
  const double vDPI = 96.0;

  const GfxState state(hDPI, vDPI, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
  EXPECT_DOUBLE_EQ(state.getHDPI(), hDPI);
}

TEST_F(GfxStateTest_564, GetHDPI_AllowsZero_564)
{
  const double hDPI = 0.0;
  const double vDPI = 72.0;

  const GfxState state(hDPI, vDPI, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
  EXPECT_DOUBLE_EQ(state.getHDPI(), 0.0);
}

TEST_F(GfxStateTest_564, GetHDPI_AllowsNegative_564)
{
  const double hDPI = -1.0;
  const double vDPI = 72.0;

  const GfxState state(hDPI, vDPI, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
  EXPECT_DOUBLE_EQ(state.getHDPI(), hDPI);
}

TEST_F(GfxStateTest_564, GetHDPI_AllowsVeryLargeFiniteValue_564)
{
  const double hDPI = 1e300;
  const double vDPI = 72.0;

  const GfxState state(hDPI, vDPI, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
  EXPECT_DOUBLE_EQ(state.getHDPI(), hDPI);
}

TEST_F(GfxStateTest_564, GetHDPI_AllowsInfinity_564)
{
  const double hDPI = std::numeric_limits<double>::infinity();
  const double vDPI = 72.0;

  const GfxState state(hDPI, vDPI, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
  EXPECT_TRUE(std::isinf(state.getHDPI()));
  EXPECT_GT(state.getHDPI(), 0.0);
}

TEST_F(GfxStateTest_564, GetHDPI_AllowsNaN_564)
{
  const double hDPI = std::numeric_limits<double>::quiet_NaN();
  const double vDPI = 72.0;

  const GfxState state(hDPI, vDPI, &pageBox_, /*rotateA=*/0, /*upsideDown=*/false);
  EXPECT_TRUE(std::isnan(state.getHDPI()));
}