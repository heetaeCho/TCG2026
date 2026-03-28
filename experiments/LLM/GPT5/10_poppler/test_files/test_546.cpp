// TEST_ID: 546
// File: test_gfxsubpath_setx_546.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

class GfxSubpathTest_546 : public ::testing::Test {
protected:
  static GfxSubpath MakeSimplePathWithExtraPoint() {
    GfxSubpath sp(1.25, -2.5);
    sp.lineTo(10.0, 20.0);
    return sp; // NRVO/move elision; copy is deleted but return-by-value is OK.
  }
};

TEST_F(GfxSubpathTest_546, SetXUpdatesPointAtIndex0_546) {
  GfxSubpath sp(3.0, 4.0);

  ASSERT_GE(sp.getNumPoints(), 1);
  const double oldY0 = sp.getY(0);

  sp.setX(0, 123.456);

  EXPECT_DOUBLE_EQ(sp.getX(0), 123.456);
  EXPECT_DOUBLE_EQ(sp.getY(0), oldY0);
}

TEST_F(GfxSubpathTest_546, SetXUpdatesPointAddedByLineTo_546) {
  GfxSubpath sp = MakeSimplePathWithExtraPoint();

  ASSERT_GE(sp.getNumPoints(), 2);
  const int idx = sp.getNumPoints() - 1;
  const double oldY = sp.getY(idx);

  sp.setX(idx, -999.0);

  EXPECT_DOUBLE_EQ(sp.getX(idx), -999.0);
  EXPECT_DOUBLE_EQ(sp.getY(idx), oldY);
}

TEST_F(GfxSubpathTest_546, SetXDoesNotChangeOtherPoints_546) {
  GfxSubpath sp(0.0, 0.0);
  sp.lineTo(5.0, 6.0);
  sp.lineTo(7.0, 8.0);

  ASSERT_GE(sp.getNumPoints(), 3);

  const double x0 = sp.getX(0);
  const double y0 = sp.getY(0);
  const double x1 = sp.getX(1);
  const double y1 = sp.getY(1);

  sp.setX(2, 42.0);

  EXPECT_DOUBLE_EQ(sp.getX(2), 42.0);
  EXPECT_DOUBLE_EQ(sp.getX(0), x0);
  EXPECT_DOUBLE_EQ(sp.getY(0), y0);
  EXPECT_DOUBLE_EQ(sp.getX(1), x1);
  EXPECT_DOUBLE_EQ(sp.getY(1), y1);
}

TEST_F(GfxSubpathTest_546, SetXUpdatesLastXConsistently_546) {
  GfxSubpath sp(1.0, 2.0);
  sp.lineTo(3.0, 4.0);

  ASSERT_GE(sp.getNumPoints(), 2);
  const int last = sp.getNumPoints() - 1;

  sp.setX(last, 111.0);

  EXPECT_DOUBLE_EQ(sp.getX(last), 111.0);
  EXPECT_DOUBLE_EQ(sp.getLastX(), 111.0);
  EXPECT_DOUBLE_EQ(sp.getLastY(), sp.getY(last));
}

TEST_F(GfxSubpathTest_546, SetXOnCopyDoesNotAffectOriginal_546) {
  GfxSubpath sp(9.0, 10.0);
  sp.lineTo(11.0, 12.0);

  ASSERT_GE(sp.getNumPoints(), 2);

  GfxSubpath* copy = sp.copy();
  ASSERT_NE(copy, nullptr);

  const double origX0 = sp.getX(0);
  const double origX1 = sp.getX(1);

  copy->setX(0, -1.0);
  copy->setX(1, -2.0);

  // Original unchanged
  EXPECT_DOUBLE_EQ(sp.getX(0), origX0);
  EXPECT_DOUBLE_EQ(sp.getX(1), origX1);

  // Copy updated
  EXPECT_DOUBLE_EQ(copy->getX(0), -1.0);
  EXPECT_DOUBLE_EQ(copy->getX(1), -2.0);

  delete copy;
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GfxSubpathTest_546, SetXOutOfRangeHighMayDeath_546) {
  GfxSubpath sp(0.0, 0.0);
  const int n = sp.getNumPoints();
  ASSERT_GE(n, 1);

  // If the implementation has bounds checks/asserts, this should terminate.
  // If it doesn't, this test may be flaky/UB; so we only run it as a death test.
  EXPECT_DEATH_IF_SUPPORTED(sp.setX(n, 1.0), "");
}

TEST_F(GfxSubpathTest_546, SetXOutOfRangeNegativeMayDeath_546) {
  GfxSubpath sp(0.0, 0.0);
  ASSERT_GE(sp.getNumPoints(), 1);

  EXPECT_DEATH_IF_SUPPORTED(sp.setX(-1, 1.0), "");
}
#endif