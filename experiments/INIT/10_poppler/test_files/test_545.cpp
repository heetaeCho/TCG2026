// SPDX-License-Identifier: GPL-2.0-or-later
// File: gfxsubpath_getcurve_unittest_545.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxSubpathTest_545 : public ::testing::Test {};

TEST_F(GfxSubpathTest_545, GetCurve_InitialPointIsNotCurve_545) {
  GfxSubpath sp(1.0, 2.0);

  ASSERT_GE(sp.getNumPoints(), 1);
  EXPECT_FALSE(sp.getCurve(0));
}

TEST_F(GfxSubpathTest_545, GetCurve_LineToAddsNonCurvePoint_545) {
  GfxSubpath sp(0.0, 0.0);

  const int n0 = sp.getNumPoints();
  sp.lineTo(10.0, 20.0);
  const int n1 = sp.getNumPoints();

  ASSERT_GE(n1, n0 + 1);

  // For a straight line segment, newly added point(s) should not be marked as curve points.
  EXPECT_FALSE(sp.getCurve(n1 - 1));

  // The initial point should remain non-curve.
  EXPECT_FALSE(sp.getCurve(0));
}

TEST_F(GfxSubpathTest_545, GetCurve_CurveToMarksAddedPointsAsCurve_545) {
  GfxSubpath sp(0.0, 0.0);

  const int n0 = sp.getNumPoints();
  sp.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  const int n1 = sp.getNumPoints();

  // Poppler curveTo() typically adds three points (two control points + end point).
  ASSERT_GE(n1, n0 + 3);

  // The three newest points should be marked as curve points.
  EXPECT_TRUE(sp.getCurve(n1 - 3));
  EXPECT_TRUE(sp.getCurve(n1 - 2));
  EXPECT_TRUE(sp.getCurve(n1 - 1));

  // Initial point should not become a curve point.
  EXPECT_FALSE(sp.getCurve(0));
}

TEST_F(GfxSubpathTest_545, GetCurve_OffsetDoesNotChangeCurveFlags_545) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(10.0, 0.0);
  sp.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

  const int n = sp.getNumPoints();
  ASSERT_GT(n, 0);

  // Snapshot curve flags.
  std::vector<bool> before;
  before.reserve(static_cast<size_t>(n));
  for (int i = 0; i < n; ++i) {
    before.push_back(sp.getCurve(i));
  }

  sp.offset(100.0, -50.0);

  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(sp.getCurve(i), before[static_cast<size_t>(i)]);
  }
}

TEST_F(GfxSubpathTest_545, GetCurve_SetXSetYDoNotChangeCurveFlags_545) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(1.0, 1.0);
  sp.curveTo(1.0, 2.0, 2.0, 3.0, 3.0, 4.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 1);

  std::vector<bool> before;
  before.reserve(static_cast<size_t>(n));
  for (int i = 0; i < n; ++i) {
    before.push_back(sp.getCurve(i));
  }

  // Mutate coordinates via public setters; curve-ness should be independent of coordinates.
  for (int i = 0; i < n; ++i) {
    sp.setX(i, sp.getX(i) + 0.25);
    sp.setY(i, sp.getY(i) - 0.75);
  }

  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(sp.getCurve(i), before[static_cast<size_t>(i)]);
  }
}

TEST_F(GfxSubpathTest_545, GetCurve_CopyPreservesCurveFlags_545) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(5.0, 0.0);
  sp.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  sp.close();

  const int n = sp.getNumPoints();
  ASSERT_GT(n, 0);

  std::vector<bool> before;
  before.reserve(static_cast<size_t>(n));
  for (int i = 0; i < n; ++i) {
    before.push_back(sp.getCurve(i));
  }

  GfxSubpath* cp = sp.copy();
  ASSERT_NE(cp, nullptr);

  ASSERT_EQ(cp->getNumPoints(), n);
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(cp->getCurve(i), before[static_cast<size_t>(i)]);
  }

  delete cp;
}

TEST_F(GfxSubpathTest_545, GetCurve_CloseDoesNotChangeCurveFlags_545) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(1.0, 0.0);
  sp.lineTo(1.0, 1.0);

  const int n = sp.getNumPoints();
  ASSERT_GT(n, 0);

  std::vector<bool> before;
  before.reserve(static_cast<size_t>(n));
  for (int i = 0; i < n; ++i) {
    before.push_back(sp.getCurve(i));
  }

  sp.close();

  // Closing a subpath should not reclassify points as curve/non-curve.
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(sp.getCurve(i), before[static_cast<size_t>(i)]);
  }
}

#if GTEST_HAS_DEATH_TEST
#ifndef NDEBUG
TEST_F(GfxSubpathTest_545, GetCurve_IndexNegativeDiesInDebug_545) {
  GfxSubpath sp(0.0, 0.0);
  EXPECT_DEATH({ (void)sp.getCurve(-1); }, ".*");
}

TEST_F(GfxSubpathTest_545, GetCurve_IndexTooLargeDiesInDebug_545) {
  GfxSubpath sp(0.0, 0.0);
  const int n = sp.getNumPoints();
  EXPECT_DEATH({ (void)sp.getCurve(n); }, ".*");
}
#endif  // !NDEBUG
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace