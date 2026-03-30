// TEST_ID: 547
// File: gfxsubpath_sety_unittest_547.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "GfxState.h"

// These tests treat GfxSubpath as a black box and validate only observable behavior
// through the public interface (constructor, lineTo/curveTo, getNumPoints/getY, setY).

class GfxSubpathTest_547 : public ::testing::Test {
protected:
  static void ExpectIsNaN(double v) {
    EXPECT_TRUE(std::isnan(v));
  }
};

TEST_F(GfxSubpathTest_547, SetYUpdatesFirstPoint_547) {
  GfxSubpath sp(1.25, -3.5);

  ASSERT_GE(sp.getNumPoints(), 1);
  const double original0 = sp.getY(0);

  const double newY0 = 42.0;
  sp.setY(0, newY0);

  EXPECT_DOUBLE_EQ(sp.getY(0), newY0);
  // Basic sanity: original may differ; we only require new value is observed.
  (void)original0;
}

TEST_F(GfxSubpathTest_547, SetYUpdatesLastPointAfterLineTo_547) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(10.0, 20.0);
  sp.lineTo(-5.0, 7.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 3);

  const int last = n - 1;
  const double beforeLast = sp.getY(last);

  const double newLastY = -123.456;
  sp.setY(last, newLastY);

  EXPECT_DOUBLE_EQ(sp.getY(last), newLastY);
  (void)beforeLast;
}

TEST_F(GfxSubpathTest_547, SetYUpdatesMiddlePointWithoutAffectingOthers_547) {
  GfxSubpath sp(0.0, 1.0);
  sp.lineTo(2.0, 3.0);
  sp.lineTo(4.0, 5.0);
  sp.lineTo(6.0, 7.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 4);

  const int mid = 1; // pick a stable, valid middle index
  const double y0_before = sp.getY(0);
  const double ymid_before = sp.getY(mid);
  const double ylast_before = sp.getY(n - 1);

  const double newMidY = 999.0;
  sp.setY(mid, newMidY);

  EXPECT_DOUBLE_EQ(sp.getY(mid), newMidY);
  // Other points should remain the same (observable via getters).
  EXPECT_DOUBLE_EQ(sp.getY(0), y0_before);
  EXPECT_DOUBLE_EQ(sp.getY(n - 1), ylast_before);
  (void)ymid_before;
}

TEST_F(GfxSubpathTest_547, SetYWorksAfterCurveToOnAllPoints_547) {
  GfxSubpath sp(0.0, 0.0);

  // Adds a curve segment; exact point count is implementation-defined, but should increase.
  sp.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  // Update each point's y and verify via getY.
  for (int i = 0; i < n; ++i) {
    const double newY = static_cast<double>(i) * 1.5 - 10.0;
    sp.setY(i, newY);
    EXPECT_DOUBLE_EQ(sp.getY(i), newY) << "index=" << i;
  }
}

TEST_F(GfxSubpathTest_547, SetYAcceptsLargeMagnitudeValues_547) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(1.0, 1.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  const double big = std::numeric_limits<double>::max() / 4.0;
  const double small = -std::numeric_limits<double>::max() / 4.0;

  sp.setY(0, big);
  sp.setY(n - 1, small);

  EXPECT_DOUBLE_EQ(sp.getY(0), big);
  EXPECT_DOUBLE_EQ(sp.getY(n - 1), small);
}

TEST_F(GfxSubpathTest_547, SetYAcceptsInfinity_547) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(1.0, 1.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  const double posInf = std::numeric_limits<double>::infinity();
  const double negInf = -std::numeric_limits<double>::infinity();

  sp.setY(0, posInf);
  sp.setY(n - 1, negInf);

  EXPECT_TRUE(std::isinf(sp.getY(0)));
  EXPECT_GT(sp.getY(0), 0.0);

  EXPECT_TRUE(std::isinf(sp.getY(n - 1)));
  EXPECT_LT(sp.getY(n - 1), 0.0);
}

TEST_F(GfxSubpathTest_547, SetYAcceptsNaN_547) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(1.0, 1.0);

  const int n = sp.getNumPoints();
  ASSERT_GE(n, 2);

  const double nanV = std::numeric_limits<double>::quiet_NaN();
  sp.setY(0, nanV);

  // NaN != NaN, so use isnan.
  ExpectIsNaN(sp.getY(0));
}