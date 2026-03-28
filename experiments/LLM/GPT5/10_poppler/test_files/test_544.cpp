// TEST_ID: 544
// File: GfxSubpath_getY_544_test.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxSubpathTest_544 : public ::testing::Test {};

TEST_F(GfxSubpathTest_544, Constructor_SetsInitialY_544) {
  const double x0 = 1.25;
  const double y0 = -3.5;

  GfxSubpath sp(x0, y0);

  ASSERT_GE(sp.getNumPoints(), 1);
  EXPECT_DOUBLE_EQ(sp.getY(0), y0);
}

TEST_F(GfxSubpathTest_544, LineTo_AppendsPointAndGetYMatches_544) {
  GfxSubpath sp(0.0, 10.0);

  const int n0 = sp.getNumPoints();
  ASSERT_GE(n0, 1);

  sp.lineTo(5.0, -2.25);

  const int n1 = sp.getNumPoints();
  ASSERT_GE(n1, n0);
  ASSERT_GE(n1, 2);

  // Check first and last points' Y values through the public interface.
  EXPECT_DOUBLE_EQ(sp.getY(0), 10.0);
  EXPECT_DOUBLE_EQ(sp.getY(n1 - 1), -2.25);
}

TEST_F(GfxSubpathTest_544, SetY_UpdatesExistingPoint_544) {
  GfxSubpath sp(0.0, 1.0);
  sp.lineTo(2.0, 3.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  // Update Y of the first point and verify getY reflects it.
  sp.setY(0, 99.0);
  EXPECT_DOUBLE_EQ(sp.getY(0), 99.0);

  // Update Y of the last point and verify getY reflects it.
  sp.setY(n - 1, -123.5);
  EXPECT_DOUBLE_EQ(sp.getY(n - 1), -123.5);
}

TEST_F(GfxSubpathTest_544, Offset_ShiftsYValues_544) {
  GfxSubpath sp(1.0, 2.0);
  sp.lineTo(3.0, 4.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  const double y0_before = sp.getY(0);
  const double y1_before = sp.getY(n - 1);

  const double dx = 10.0;
  const double dy = -7.25;
  sp.offset(dx, dy);

  EXPECT_DOUBLE_EQ(sp.getY(0), y0_before + dy);
  EXPECT_DOUBLE_EQ(sp.getY(n - 1), y1_before + dy);
}

TEST_F(GfxSubpathTest_544, CurveTo_AddsPointsAndGetYReadableForNewPoints_544) {
  GfxSubpath sp(0.0, 0.0);

  const int n0 = sp.getNumPoints();
  ASSERT_GE(n0, 1);

  // Add a cubic Bezier segment (number of points added is implementation-defined;
  // we only assert that the subpath has at least one additional point).
  sp.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

  const int n1 = sp.getNumPoints();
  ASSERT_GT(n1, n0);

  // Pick a valid new point index and verify setY/getY works via public API.
  const int newIdx = n1 - 1;
  const double newY = 42.0;

  sp.setY(newIdx, newY);
  EXPECT_DOUBLE_EQ(sp.getY(newIdx), newY);
}

}  // namespace