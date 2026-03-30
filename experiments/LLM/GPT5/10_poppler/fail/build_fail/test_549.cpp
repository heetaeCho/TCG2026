// TEST_ID: 549
// File: GfxSubpath_getLastY_549_test.cpp

#include <gtest/gtest.h>

#include "GfxState.h"

// The class under test is treated as a black box. We only use the public API.

class GfxSubpathTest_549 : public ::testing::Test {};

// Normal operation: constructor initializes last point.
TEST_F(GfxSubpathTest_549, GetLastY_AfterConstructionMatchesLastPointY_549) {
  GfxSubpath sp(10.0, 20.5);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 1);

  EXPECT_DOUBLE_EQ(sp.getLastY(), sp.getY(n - 1));
  EXPECT_DOUBLE_EQ(sp.getLastY(), 20.5);
}

// Normal operation: lineTo updates the last point.
TEST_F(GfxSubpathTest_549, GetLastY_AfterLineToMatchesNewLastPointY_549) {
  GfxSubpath sp(0.0, 0.0);

  sp.lineTo(3.25, -7.75);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  EXPECT_DOUBLE_EQ(sp.getLastY(), sp.getY(n - 1));
  EXPECT_DOUBLE_EQ(sp.getLastY(), -7.75);
}

// Normal operation: curveTo updates the last point (end point of the curve).
TEST_F(GfxSubpathTest_549, GetLastY_AfterCurveToMatchesCurveEndPointY_549) {
  GfxSubpath sp(1.0, 2.0);

  sp.curveTo(10.0, 11.0, 20.0, 21.0, 30.0, 31.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  EXPECT_DOUBLE_EQ(sp.getLastY(), sp.getY(n - 1));
  EXPECT_DOUBLE_EQ(sp.getLastY(), 31.0);
}

// Boundary-ish: multiple operations in sequence; lastY should track the last point consistently.
TEST_F(GfxSubpathTest_549, GetLastY_AfterMultipleAddsMatchesGetYOfLastIndex_549) {
  GfxSubpath sp(-1.0, -2.0);

  sp.lineTo(5.0, 6.0);
  sp.curveTo(0.0, 1.0, 2.0, 3.0, 4.0, 5.0);
  sp.lineTo(7.0, 8.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  EXPECT_DOUBLE_EQ(sp.getLastY(), sp.getY(n - 1));
  EXPECT_DOUBLE_EQ(sp.getLastY(), 8.0);
}

// Normal operation: offset shifts all points; lastY should reflect the shifted last point.
TEST_F(GfxSubpathTest_549, GetLastY_AfterOffsetShiftsByDy_549) {
  GfxSubpath sp(0.0, 1.0);

  sp.lineTo(10.0, 20.0);
  const double before = sp.getLastY();

  sp.offset(123.0, -4.5);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  EXPECT_DOUBLE_EQ(sp.getLastY(), sp.getY(n - 1));
  EXPECT_DOUBLE_EQ(sp.getLastY(), before - 4.5);
}

// Boundary: setY on the last index should update getLastY accordingly.
TEST_F(GfxSubpathTest_549, GetLastY_ReflectsSetYOnLastIndex_549) {
  GfxSubpath sp(9.0, 9.0);

  sp.lineTo(1.0, 2.0);
  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  sp.setY(n - 1, 999.25);

  EXPECT_DOUBLE_EQ(sp.getLastY(), sp.getY(n - 1));
  EXPECT_DOUBLE_EQ(sp.getLastY(), 999.25);
}

// External interaction / object creation via API: copy() returns an object whose lastY matches at copy time.
TEST_F(GfxSubpathTest_549, Copy_CopiesLastYValue_549) {
  GfxSubpath sp(1.0, 2.0);
  sp.lineTo(3.0, 4.0);
  sp.curveTo(5.0, 6.0, 7.0, 8.0, 9.0, 10.0);

  GfxSubpath *cp = sp.copy();
  ASSERT_NE(cp, nullptr);

  EXPECT_DOUBLE_EQ(cp->getLastY(), sp.getLastY());

  delete cp;
}