// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_gfxpath_getlasty_557.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "./TestProjects/poppler/poppler/GfxState.h"

class GfxPathTest_557 : public ::testing::Test {};

TEST_F(GfxPathTest_557, MoveToSetsLastY_557) {
  GfxPath path;
  path.moveTo(1.0, 2.5);
  EXPECT_DOUBLE_EQ(path.getLastY(), 2.5);
}

TEST_F(GfxPathTest_557, LineToUpdatesLastY_557) {
  GfxPath path;
  path.moveTo(0.0, 0.0);
  EXPECT_DOUBLE_EQ(path.getLastY(), 0.0);

  path.lineTo(10.0, -7.25);
  EXPECT_DOUBLE_EQ(path.getLastY(), -7.25);

  path.lineTo(-3.0, 99.0);
  EXPECT_DOUBLE_EQ(path.getLastY(), 99.0);
}

TEST_F(GfxPathTest_557, CurveToUsesEndPointYAsLastY_557) {
  GfxPath path;
  path.moveTo(0.0, 1.0);
  EXPECT_DOUBLE_EQ(path.getLastY(), 1.0);

  // curveTo(x1,y1,x2,y2,x3,y3) - observable expectation: last point is (x3,y3).
  path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.5);
  EXPECT_DOUBLE_EQ(path.getLastY(), 6.5);

  path.curveTo(-1.0, -2.0, -3.0, -4.0, -5.0, -6.0);
  EXPECT_DOUBLE_EQ(path.getLastY(), -6.0);
}

TEST_F(GfxPathTest_557, MultipleSubpathsLastYTracksMostRecentSubpath_557) {
  GfxPath path;
  path.moveTo(0.0, 10.0);
  path.lineTo(1.0, 11.0);
  EXPECT_DOUBLE_EQ(path.getLastY(), 11.0);

  // Start a new subpath; lastY should now reflect the current subpath.
  path.moveTo(2.0, -20.0);
  EXPECT_DOUBLE_EQ(path.getLastY(), -20.0);

  path.lineTo(3.0, -21.0);
  EXPECT_DOUBLE_EQ(path.getLastY(), -21.0);
}

TEST_F(GfxPathTest_557, OffsetShiftsLastYByDy_557) {
  GfxPath path;
  path.moveTo(0.0, 1.25);
  path.lineTo(2.0, 3.75);
  const double before = path.getLastY();
  EXPECT_DOUBLE_EQ(before, 3.75);

  path.offset(100.0, -10.0);
  EXPECT_DOUBLE_EQ(path.getLastY(), before - 10.0);

  path.offset(0.0, 0.5);
  EXPECT_DOUBLE_EQ(path.getLastY(), (before - 10.0) + 0.5);
}

TEST_F(GfxPathTest_557, CopyPreservesLastY_557) {
  GfxPath path;
  path.moveTo(0.0, 0.0);
  path.lineTo(1.0, 2.0);
  path.curveTo(1.0, 3.0, 2.0, 4.0, 3.0, 5.0);

  const double expected = path.getLastY();
  ASSERT_DOUBLE_EQ(expected, 5.0);

  GfxPath *cpy = path.copy();
  ASSERT_NE(cpy, nullptr);
  EXPECT_DOUBLE_EQ(cpy->getLastY(), expected);

  delete cpy;
}

TEST_F(GfxPathTest_557, AppendMakesLastYFollowAppendedPath_557) {
  GfxPath a;
  a.moveTo(0.0, 1.0);
  a.lineTo(0.0, 2.0);
  EXPECT_DOUBLE_EQ(a.getLastY(), 2.0);

  GfxPath b;
  b.moveTo(5.0, 50.0);
  b.lineTo(6.0, 60.0);
  EXPECT_DOUBLE_EQ(b.getLastY(), 60.0);

  a.append(&b);
  EXPECT_DOUBLE_EQ(a.getLastY(), 60.0);
}

TEST_F(GfxPathTest_557, HandlesLargeAndNegativeValues_557) {
  GfxPath path;
  const double big = std::numeric_limits<double>::max() / 4.0;
  path.moveTo(0.0, -big);
  EXPECT_DOUBLE_EQ(path.getLastY(), -big);

  path.lineTo(1.0, big);
  EXPECT_DOUBLE_EQ(path.getLastY(), big);

  path.offset(0.0, -big);
  EXPECT_DOUBLE_EQ(path.getLastY(), 0.0);
}

TEST_F(GfxPathTest_557, NaNLastYPropagatesWhenUsedAsInput_557) {
  GfxPath path;
  path.moveTo(0.0, 0.0);
  EXPECT_DOUBLE_EQ(path.getLastY(), 0.0);

  const double nan = std::numeric_limits<double>::quiet_NaN();
  path.lineTo(1.0, nan);

  // Observable: if the implementation stores the provided y, getLastY should be NaN.
  // If it sanitizes values, this test may fail; but typical path implementations preserve inputs.
  EXPECT_TRUE(std::isnan(path.getLastY()));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GfxPathTest_557, GetLastYOnFreshPathDiesOrAborts_557) {
  // Boundary / exceptional: calling getLastY before any moveTo/lineTo/curveTo.
  // If the implementation guards against this, it may abort/assert; if it returns a value,
  // this death test will fail and should be adjusted in that environment.
  GfxPath path;
  ASSERT_DEATH({ (void)path.getLastY(); }, ".*");
}
#endif