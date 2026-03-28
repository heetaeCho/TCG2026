// -*- mode: c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// File: gfxsubpath_getlastx_unittest_548.cc

#include <gtest/gtest.h>

#include "GfxState.h"

namespace {

class GfxSubpathTest_548 : public ::testing::Test {};

TEST_F(GfxSubpathTest_548, LastXMatchesXOfLastIndexAfterConstruction_548) {
  GfxSubpath sp(1.25, -3.5);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 1);

  EXPECT_DOUBLE_EQ(sp.getLastX(), sp.getX(n - 1));
}

TEST_F(GfxSubpathTest_548, LastXMatchesXOfLastIndexAfterLineTo_548) {
  GfxSubpath sp(0.0, 0.0);

  const int n0 = sp.getNumPoints();
  ASSERT_GE(n0, 1);

  sp.lineTo(2.0, 5.0);

  const int n1 = sp.getNumPoints();
  ASSERT_GE(n1, 1);

  EXPECT_DOUBLE_EQ(sp.getLastX(), sp.getX(n1 - 1));
  // Boundary-ish: if the path grew, last point should be at a new valid index.
  EXPECT_GE(n1, n0);
}

TEST_F(GfxSubpathTest_548, LastXMatchesXOfLastIndexAfterCurveTo_548) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(1.0, 1.0);

  const int n0 = sp.getNumPoints();
  ASSERT_GE(n0, 1);

  sp.curveTo(2.0, 2.0, 3.0, 3.0, 4.0, 4.0);

  const int n1 = sp.getNumPoints();
  ASSERT_GE(n1, 1);

  EXPECT_DOUBLE_EQ(sp.getLastX(), sp.getX(n1 - 1));
  // Observable growth check (without assuming exact number of points added).
  EXPECT_GE(n1, n0);
}

TEST_F(GfxSubpathTest_548, LastXMatchesXOfLastIndexAfterClose_548) {
  GfxSubpath sp(10.0, 20.0);
  sp.lineTo(30.0, 40.0);

  const int n0 = sp.getNumPoints();
  ASSERT_GE(n0, 1);

  sp.close();

  const int n1 = sp.getNumPoints();
  ASSERT_GE(n1, 1);

  EXPECT_DOUBLE_EQ(sp.getLastX(), sp.getX(n1 - 1));
  // Closing should not make last index invalid regardless of any internal behavior.
}

TEST_F(GfxSubpathTest_548, LastXMatchesXOfLastIndexAfterOffset_548) {
  GfxSubpath sp(1.0, 2.0);
  sp.lineTo(3.0, 4.0);

  const int n0 = sp.getNumPoints();
  ASSERT_GE(n0, 1);

  sp.offset(0.0, 0.0);  // boundary: no-op offset should be safe

  const int n1 = sp.getNumPoints();
  ASSERT_GE(n1, 1);

  EXPECT_DOUBLE_EQ(sp.getLastX(), sp.getX(n1 - 1));
  EXPECT_EQ(n1, n0);
}

TEST_F(GfxSubpathTest_548, CopyPreservesLastXAtTimeOfCopy_548) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(1.0, 2.0);
  sp.curveTo(3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

  const double last_before = sp.getLastX();

  GfxSubpath* copied = sp.copy();
  ASSERT_NE(copied, nullptr);

  EXPECT_DOUBLE_EQ(copied->getLastX(), last_before);

  // If the original is subsequently modified, the copy should still remain usable
  // and internally consistent (black-box observable behavior).
  sp.lineTo(9.0, 10.0);

  const int n_copy = copied->getNumPoints();
  ASSERT_GE(n_copy, 1);
  EXPECT_DOUBLE_EQ(copied->getLastX(), copied->getX(n_copy - 1));

  delete copied;
}

}  // namespace