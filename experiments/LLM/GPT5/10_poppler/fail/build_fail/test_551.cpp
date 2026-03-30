// TEST_ID: 551
//
// Unit tests for GfxPath::copy() based strictly on the public interface.
// We treat the implementation as a black box and only verify observable behavior.

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxPathTest_551 : public ::testing::Test {
protected:
  static void ExpectSameObservableState(const GfxPath &a, const GfxPath &b) {
    EXPECT_EQ(a.isCurPt(), b.isCurPt());
    EXPECT_EQ(a.isPath(), b.isPath());

    const int na = a.getNumSubpaths();
    const int nb = b.getNumSubpaths();
    EXPECT_EQ(na, nb);

    // Only compare last point if a current point exists (avoids assumptions about empty-path behavior).
    if (a.isCurPt()) {
      EXPECT_DOUBLE_EQ(a.getLastX(), b.getLastX());
      EXPECT_DOUBLE_EQ(a.getLastY(), b.getLastY());
    }
  }

  static void ExpectSubpathsIndependentWhenPresent(const GfxPath &orig, const GfxPath &cpy) {
    const int n = orig.getNumSubpaths();
    ASSERT_EQ(n, cpy.getNumSubpaths());

    // If subpaths are exposed via pointers, a deep copy is expected to not alias the same subpath objects.
    for (int i = 0; i < n; ++i) {
      GfxSubpath *so = orig.getSubpath(i);
      GfxSubpath *sc = cpy.getSubpath(i);
      ASSERT_NE(so, nullptr);
      ASSERT_NE(sc, nullptr);
      EXPECT_NE(so, sc);
    }
  }
};

TEST_F(GfxPathTest_551, CopyEmptyPath_MatchesObservableState_551) {
  GfxPath original;

  GfxPath *copy = nullptr;
  ASSERT_NO_THROW(copy = original.copy());
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, &original);

  ExpectSameObservableState(original, *copy);

  delete copy;
}

TEST_F(GfxPathTest_551, CopyAfterMoveToLineTo_MatchesObservableState_551) {
  GfxPath original;
  original.moveTo(10.0, 20.0);
  original.lineTo(30.0, 40.0);

  GfxPath *copy = nullptr;
  ASSERT_NO_THROW(copy = original.copy());
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, &original);

  ExpectSameObservableState(original, *copy);
  if (original.getNumSubpaths() > 0) {
    ExpectSubpathsIndependentWhenPresent(original, *copy);
  }

  delete copy;
}

TEST_F(GfxPathTest_551, CopyAfterCurveAndClose_MatchesObservableState_551) {
  GfxPath original;
  original.moveTo(1.0, 2.0);
  original.curveTo(3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
  original.close();

  GfxPath *copy = nullptr;
  ASSERT_NO_THROW(copy = original.copy());
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, &original);

  ExpectSameObservableState(original, *copy);
  if (original.getNumSubpaths() > 0) {
    ExpectSubpathsIndependentWhenPresent(original, *copy);
  }

  delete copy;
}

TEST_F(GfxPathTest_551, CopyThenModifyOriginal_CopyRemainsUnchanged_551) {
  GfxPath original;
  original.moveTo(0.0, 0.0);
  original.lineTo(1.0, 2.0);

  GfxPath *copy = original.copy();
  ASSERT_NE(copy, nullptr);

  // Snapshot the copy's observable state before mutating original.
  const bool copyCurPtBefore = copy->isCurPt();
  const bool copyIsPathBefore = copy->isPath();
  const int copyNumSubpathsBefore = copy->getNumSubpaths();
  const double copyLastXBefore = copyCurPtBefore ? copy->getLastX() : 0.0;
  const double copyLastYBefore = copyCurPtBefore ? copy->getLastY() : 0.0;

  // Mutate original in a way that's observable.
  original.offset(100.0, -50.0);
  original.lineTo(9.0, 9.0);

  // Copy should retain its previous observable state (independence).
  EXPECT_EQ(copyCurPtBefore, copy->isCurPt());
  EXPECT_EQ(copyIsPathBefore, copy->isPath());
  EXPECT_EQ(copyNumSubpathsBefore, copy->getNumSubpaths());
  if (copyCurPtBefore) {
    EXPECT_DOUBLE_EQ(copyLastXBefore, copy->getLastX());
    EXPECT_DOUBLE_EQ(copyLastYBefore, copy->getLastY());
  }

  delete copy;
}

TEST_F(GfxPathTest_551, CopyThenModifyCopy_OriginalRemainsUnchanged_551) {
  GfxPath original;
  original.moveTo(-5.0, 6.0);
  original.lineTo(7.0, -8.0);

  GfxPath *copy = original.copy();
  ASSERT_NE(copy, nullptr);

  // Snapshot the original's observable state before mutating the copy.
  const bool origCurPtBefore = original.isCurPt();
  const bool origIsPathBefore = original.isPath();
  const int origNumSubpathsBefore = original.getNumSubpaths();
  const double origLastXBefore = origCurPtBefore ? original.getLastX() : 0.0;
  const double origLastYBefore = origCurPtBefore ? original.getLastY() : 0.0;

  // Mutate the copy.
  copy->offset(3.25, 4.75);
  copy->lineTo(123.0, 456.0);

  // Original should retain its previous observable state (independence).
  EXPECT_EQ(origCurPtBefore, original.isCurPt());
  EXPECT_EQ(origIsPathBefore, original.isPath());
  EXPECT_EQ(origNumSubpathsBefore, original.getNumSubpaths());
  if (origCurPtBefore) {
    EXPECT_DOUBLE_EQ(origLastXBefore, original.getLastX());
    EXPECT_DOUBLE_EQ(origLastYBefore, original.getLastY());
  }

  delete copy;
}

TEST_F(GfxPathTest_551, CopyCalledMultipleTimes_ReturnsDistinctEquivalentObjects_551) {
  GfxPath original;
  original.moveTo(1.0, 1.0);
  original.lineTo(2.0, 3.0);
  original.curveTo(4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

  GfxPath *c1 = original.copy();
  GfxPath *c2 = original.copy();
  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  EXPECT_NE(c1, c2);
  EXPECT_NE(c1, &original);
  EXPECT_NE(c2, &original);

  ExpectSameObservableState(original, *c1);
  ExpectSameObservableState(original, *c2);
  ExpectSameObservableState(*c1, *c2);

  delete c1;
  delete c2;
}

}  // namespace