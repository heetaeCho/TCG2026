// TEST_ID: 542
// File: gfxsubpath_getnumpoints_542_test.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

// NOTE:
// - We treat GfxSubpath as a black box.
// - We only assert observable, minimal properties about getNumPoints() and
//   how it behaves across public API calls (no private state access).

namespace {

class GfxSubpathTest_542 : public ::testing::Test {
protected:
  static GfxSubpath MakeBasicSubpath() {
    return GfxSubpath(0.0, 0.0);
  }
};

TEST_F(GfxSubpathTest_542, InitialNumPointsIsNonNegative_542) {
  GfxSubpath sp = MakeBasicSubpath();
  const int n = sp.getNumPoints();
  EXPECT_GE(n, 0);
}

TEST_F(GfxSubpathTest_542, GetNumPointsIsStableAcrossRepeatedCalls_542) {
  GfxSubpath sp = MakeBasicSubpath();

  const int n1 = sp.getNumPoints();
  const int n2 = sp.getNumPoints();
  const int n3 = sp.getNumPoints();

  EXPECT_EQ(n1, n2);
  EXPECT_EQ(n2, n3);
}

TEST_F(GfxSubpathTest_542, LineToDoesNotDecreaseNumPoints_542) {
  GfxSubpath sp = MakeBasicSubpath();
  const int before = sp.getNumPoints();

  sp.lineTo(10.0, 20.0);

  const int after = sp.getNumPoints();
  EXPECT_GE(after, before);
}

TEST_F(GfxSubpathTest_542, CurveToDoesNotDecreaseNumPoints_542) {
  GfxSubpath sp = MakeBasicSubpath();
  const int before = sp.getNumPoints();

  sp.curveTo(1.0, 1.0, 2.0, 2.0, 3.0, 3.0);

  const int after = sp.getNumPoints();
  EXPECT_GE(after, before);
}

TEST_F(GfxSubpathTest_542, CloseDoesNotDecreaseNumPoints_542) {
  GfxSubpath sp = MakeBasicSubpath();
  sp.lineTo(1.0, 0.0);
  sp.lineTo(1.0, 1.0);

  const int before = sp.getNumPoints();
  sp.close();
  const int after = sp.getNumPoints();

  EXPECT_GE(after, before);
}

TEST_F(GfxSubpathTest_542, OffsetDoesNotChangeNumPoints_542) {
  GfxSubpath sp = MakeBasicSubpath();
  sp.lineTo(5.0, 6.0);
  sp.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

  const int before = sp.getNumPoints();
  sp.offset(100.0, -50.0);
  const int after = sp.getNumPoints();

  EXPECT_EQ(after, before);
}

TEST_F(GfxSubpathTest_542, CopyPreservesNumPoints_542) {
  GfxSubpath sp = MakeBasicSubpath();
  sp.lineTo(1.0, 2.0);
  sp.curveTo(3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
  sp.close();

  const int before = sp.getNumPoints();

  GfxSubpath* copy = sp.copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_EQ(copy->getNumPoints(), before);

  delete copy;
}

TEST_F(GfxSubpathTest_542, MutatingOriginalDoesNotDecreaseItsNumPointsAfterCopy_542) {
  GfxSubpath sp = MakeBasicSubpath();
  sp.lineTo(1.0, 1.0);

  GfxSubpath* copy = sp.copy();
  ASSERT_NE(copy, nullptr);

  const int orig_before = sp.getNumPoints();
  const int copy_before = copy->getNumPoints();

  sp.lineTo(2.0, 2.0);
  sp.curveTo(0.0, 0.0, 1.0, 0.0, 1.0, 1.0);

  const int orig_after = sp.getNumPoints();
  const int copy_after = copy->getNumPoints();

  // Minimal, observable expectations:
  // - Original should not lose points by adding segments.
  // - Copy remains a valid object and its count remains stable without mutation.
  EXPECT_GE(orig_after, orig_before);
  EXPECT_EQ(copy_after, copy_before);

  delete copy;
}

TEST_F(GfxSubpathTest_542, ManyOperationsDoesNotProduceNegativeNumPoints_542) {
  GfxSubpath sp = MakeBasicSubpath();

  for (int i = 0; i < 200; ++i) {
    sp.lineTo(static_cast<double>(i), static_cast<double>(-i));
    if (i % 3 == 0) {
      sp.curveTo(i + 0.1, i + 0.2, i + 0.3, i + 0.4, i + 0.5, i + 0.6);
    }
    if (i % 10 == 0) {
      sp.offset(0.25, -0.25);
    }
    if (i % 50 == 0) {
      sp.close();
    }

    EXPECT_GE(sp.getNumPoints(), 0);
  }
}

}  // namespace