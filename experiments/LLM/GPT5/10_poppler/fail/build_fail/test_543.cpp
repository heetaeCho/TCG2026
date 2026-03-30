// TEST_ID: 543
// File: test_gfxsubpath_getx_543.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxSubpathTest_543 : public ::testing::Test {};

TEST_F(GfxSubpathTest_543, ConstructorCreatesSinglePointAndGetXMatches_543) {
  const double x1 = 12.5;
  const double y1 = -3.75;

  GfxSubpath subpath(x1, y1);

  EXPECT_EQ(subpath.getNumPoints(), 1);
  EXPECT_DOUBLE_EQ(subpath.getX(0), x1);
  EXPECT_DOUBLE_EQ(subpath.getY(0), y1);
}

TEST_F(GfxSubpathTest_543, LineToAddsPointAndGetXReturnsNewPointX_543) {
  GfxSubpath subpath(1.0, 2.0);

  subpath.lineTo(10.0, 20.0);

  ASSERT_EQ(subpath.getNumPoints(), 2);
  EXPECT_DOUBLE_EQ(subpath.getX(0), 1.0);
  EXPECT_DOUBLE_EQ(subpath.getX(1), 10.0);
  EXPECT_DOUBLE_EQ(subpath.getY(1), 20.0);
}

TEST_F(GfxSubpathTest_543, GetXValidBoundaryIndicesFirstAndLast_543) {
  GfxSubpath subpath(0.0, 0.0);

  subpath.lineTo(1.0, 10.0);
  subpath.lineTo(2.0, 20.0);
  subpath.lineTo(3.0, 30.0);

  const int n = subpath.getNumPoints();
  ASSERT_GE(n, 1);

  // Boundary: first point
  EXPECT_DOUBLE_EQ(subpath.getX(0), 0.0);

  // Boundary: last point
  EXPECT_DOUBLE_EQ(subpath.getX(n - 1), 3.0);
}

TEST_F(GfxSubpathTest_543, SetXUpdatesCoordinateObservedViaGetX_543) {
  GfxSubpath subpath(5.0, 6.0);
  subpath.lineTo(7.0, 8.0);

  ASSERT_EQ(subpath.getNumPoints(), 2);

  EXPECT_DOUBLE_EQ(subpath.getX(1), 7.0);

  subpath.setX(1, -99.25);
  EXPECT_DOUBLE_EQ(subpath.getX(1), -99.25);

  // Ensure other index remains unchanged.
  EXPECT_DOUBLE_EQ(subpath.getX(0), 5.0);
}

TEST_F(GfxSubpathTest_543, CopyProducesIndependentObjectWithSameXValuesInitially_543) {
  GfxSubpath original(1.25, 2.5);
  original.lineTo(3.75, 4.0);
  original.lineTo(-6.0, 7.125);

  const int n = original.getNumPoints();
  ASSERT_GE(n, 1);

  GfxSubpath* copied = original.copy();
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->getNumPoints(), n);
  for (int i = 0; i < n; ++i) {
    EXPECT_DOUBLE_EQ(copied->getX(i), original.getX(i));
    EXPECT_DOUBLE_EQ(copied->getY(i), original.getY(i));
    EXPECT_EQ(copied->getCurve(i), original.getCurve(i));
  }

  // Mutate original and ensure copy is unaffected (observable independence).
  original.setX(0, 1234.5);
  EXPECT_DOUBLE_EQ(original.getX(0), 1234.5);
  EXPECT_DOUBLE_EQ(copied->getX(0), 1.25);

  delete copied;
}

}  // namespace