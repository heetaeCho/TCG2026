// TEST_ID: 541
// File: test_gfxsubpath_copy_541.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

void ExpectSameSubpathState(const GfxSubpath& a, const GfxSubpath& b) {
  ASSERT_EQ(a.getNumPoints(), b.getNumPoints());
  const int n = a.getNumPoints();
  for (int i = 0; i < n; ++i) {
    EXPECT_DOUBLE_EQ(a.getX(i), b.getX(i)) << "i=" << i;
    EXPECT_DOUBLE_EQ(a.getY(i), b.getY(i)) << "i=" << i;
    EXPECT_EQ(a.getCurve(i), b.getCurve(i)) << "i=" << i;
  }
  EXPECT_DOUBLE_EQ(a.getLastX(), b.getLastX());
  EXPECT_DOUBLE_EQ(a.getLastY(), b.getLastY());
  EXPECT_EQ(a.isClosed(), b.isClosed());
}

class GfxSubpathTest_541 : public ::testing::Test {
protected:
  static GfxSubpath MakeMinimal() {
    // Constructor is part of the public interface.
    return GfxSubpath(1.25, -3.5);
  }

  static GfxSubpath MakeWithLines() {
    GfxSubpath sp(0.0, 0.0);
    sp.lineTo(10.0, 0.0);
    sp.lineTo(10.0, 20.0);
    sp.lineTo(-5.0, 7.0);
    return sp;
  }

  static GfxSubpath MakeWithCurves() {
    GfxSubpath sp(2.0, 3.0);
    sp.lineTo(4.0, 6.0);
    sp.curveTo(5.0, 7.0, 8.0, 9.0, 13.0, 21.0);
    sp.curveTo(-1.0, -2.0, -3.0, -5.0, -8.0, -13.0);
    return sp;
  }
};

TEST_F(GfxSubpathTest_541, CopyReturnsNonNullDistinctObjectAndPreservesMinimalState_541) {
  GfxSubpath original = MakeMinimal();

  GfxSubpath* copy = original.copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, &original);

  ExpectSameSubpathState(original, *copy);

  delete copy;
}

TEST_F(GfxSubpathTest_541, CopyPreservesLinePointsAndLastPoint_541) {
  GfxSubpath original = MakeWithLines();

  GfxSubpath* copy = original.copy();
  ASSERT_NE(copy, nullptr);

  ExpectSameSubpathState(original, *copy);

  delete copy;
}

TEST_F(GfxSubpathTest_541, CopyPreservesCurveFlagsAndCoordinatesAfterCurveTo_541) {
  GfxSubpath original = MakeWithCurves();

  GfxSubpath* copy = original.copy();
  ASSERT_NE(copy, nullptr);

  // Observably, curveTo should affect points/curve flags; copy should preserve them.
  ExpectSameSubpathState(original, *copy);

  delete copy;
}

TEST_F(GfxSubpathTest_541, CopyPreservesClosedStateAfterClose_541) {
  GfxSubpath original = MakeWithLines();
  EXPECT_FALSE(original.isClosed());

  original.close();
  EXPECT_TRUE(original.isClosed());

  GfxSubpath* copy = original.copy();
  ASSERT_NE(copy, nullptr);

  ExpectSameSubpathState(original, *copy);
  EXPECT_TRUE(copy->isClosed());

  delete copy;
}

TEST_F(GfxSubpathTest_541, CopyIsDeepCopy_ModifyingOriginalDoesNotChangeCopy_541) {
  GfxSubpath original = MakeWithLines();
  GfxSubpath* copy = original.copy();
  ASSERT_NE(copy, nullptr);
  ExpectSameSubpathState(original, *copy);

  // Modify original via public interface; copy should remain as it was.
  const int n = original.getNumPoints();
  ASSERT_GT(n, 0);

  original.setX(0, original.getX(0) + 123.0);
  original.setY(0, original.getY(0) - 456.0);
  original.offset(7.0, -9.0);
  original.close();

  // Copy should still match the pre-modification snapshot (i.e., should now differ from original).
  EXPECT_NE(original.getX(0), copy->getX(0));
  EXPECT_NE(original.getY(0), copy->getY(0));
  EXPECT_NE(original.getLastX(), copy->getLastX());
  EXPECT_NE(original.getLastY(), copy->getLastY());
  // Closed state may now differ after original.close().
  EXPECT_NE(original.isClosed(), copy->isClosed());

  delete copy;
}

TEST_F(GfxSubpathTest_541, CopyIsDeepCopy_ModifyingCopyDoesNotChangeOriginal_541) {
  GfxSubpath original = MakeWithCurves();
  GfxSubpath* copy = original.copy();
  ASSERT_NE(copy, nullptr);
  ExpectSameSubpathState(original, *copy);

  const int n = copy->getNumPoints();
  ASSERT_GT(n, 0);

  // Modify copy; original should remain unchanged.
  copy->setX(0, copy->getX(0) * -2.0);
  copy->setY(0, copy->getY(0) + 999.0);
  copy->offset(-11.0, 22.0);
  copy->close();

  EXPECT_NE(original.getX(0), copy->getX(0));
  EXPECT_NE(original.getY(0), copy->getY(0));
  EXPECT_NE(original.getLastX(), copy->getLastX());
  EXPECT_NE(original.getLastY(), copy->getLastY());
  EXPECT_NE(original.isClosed(), copy->isClosed());

  delete copy;
}

TEST_F(GfxSubpathTest_541, MultipleCopiesAreIndependentAndMatchOriginalAtCopyTime_541) {
  GfxSubpath original = MakeWithLines();

  GfxSubpath* copy1 = original.copy();
  ASSERT_NE(copy1, nullptr);
  GfxSubpath* copy2 = original.copy();
  ASSERT_NE(copy2, nullptr);

  EXPECT_NE(copy1, copy2);
  ExpectSameSubpathState(original, *copy1);
  ExpectSameSubpathState(original, *copy2);

  // Mutate one copy and ensure the other copy (and original) are unaffected in observable ways.
  ASSERT_GT(copy1->getNumPoints(), 0);
  copy1->setX(0, copy1->getX(0) + 1.0);

  EXPECT_NE(copy1->getX(0), copy2->getX(0));
  EXPECT_DOUBLE_EQ(original.getX(0), copy2->getX(0));

  delete copy1;
  delete copy2;
}

}  // namespace