// TEST_ID: 554
// File: gfxpath_getnumsubpaths_554_test.cpp

#include <gtest/gtest.h>

#include "GfxState.h"

// These tests treat GfxPath as a black box and only verify behavior that is
// observable through the public interface.

namespace {

class GfxPathTest_554 : public ::testing::Test {
protected:
  static int NumSubpaths(const GfxPath &p) { return p.getNumSubpaths(); }
};

TEST_F(GfxPathTest_554, DefaultConstructed_IsNonNegative_554) {
  GfxPath p;
  const int n = NumSubpaths(p);
  EXPECT_GE(n, 0);
}

TEST_F(GfxPathTest_554, GetNumSubpaths_IsStableAcrossRepeatedCalls_554) {
  GfxPath p;
  const int n1 = NumSubpaths(p);
  const int n2 = NumSubpaths(p);
  const int n3 = NumSubpaths(p);

  EXPECT_EQ(n1, n2);
  EXPECT_EQ(n2, n3);
}

TEST_F(GfxPathTest_554, MoveTo_CreatesOrAdvancesSubpathCount_MonotonicNonDecreasing_554) {
  GfxPath p;

  const int before = NumSubpaths(p);

  ASSERT_NO_THROW(p.moveTo(10.0, 20.0));
  const int afterMove1 = NumSubpaths(p);
  EXPECT_GE(afterMove1, before);

  // A second moveTo commonly starts a new subpath in path APIs; at minimum,
  // the count should not decrease.
  ASSERT_NO_THROW(p.moveTo(30.0, 40.0));
  const int afterMove2 = NumSubpaths(p);
  EXPECT_GE(afterMove2, afterMove1);
}

TEST_F(GfxPathTest_554, LineToAndCurveTo_DoNotDecreaseSubpathCount_554) {
  GfxPath p;

  ASSERT_NO_THROW(p.moveTo(0.0, 0.0));
  const int afterMove = NumSubpaths(p);

  ASSERT_NO_THROW(p.lineTo(10.0, 0.0));
  const int afterLine = NumSubpaths(p);
  EXPECT_GE(afterLine, afterMove);

  ASSERT_NO_THROW(p.curveTo(10.0, 5.0, 5.0, 10.0, 0.0, 10.0));
  const int afterCurve = NumSubpaths(p);
  EXPECT_GE(afterCurve, afterLine);
}

TEST_F(GfxPathTest_554, Close_DoesNotDecreaseSubpathCount_554) {
  GfxPath p;

  ASSERT_NO_THROW(p.moveTo(1.0, 1.0));
  ASSERT_NO_THROW(p.lineTo(2.0, 2.0));
  const int beforeClose = NumSubpaths(p);

  ASSERT_NO_THROW(p.close());
  const int afterClose = NumSubpaths(p);

  EXPECT_GE(afterClose, beforeClose);
}

TEST_F(GfxPathTest_554, Offset_DoesNotChangeSubpathCount_554) {
  GfxPath p;

  ASSERT_NO_THROW(p.moveTo(1.0, 1.0));
  ASSERT_NO_THROW(p.lineTo(2.0, 2.0));
  ASSERT_NO_THROW(p.moveTo(3.0, 3.0)); // potentially creates another subpath

  const int before = NumSubpaths(p);

  ASSERT_NO_THROW(p.offset(100.0, -50.0));
  const int after = NumSubpaths(p);

  EXPECT_EQ(after, before);
}

TEST_F(GfxPathTest_554, Append_IncludesOtherPathSubpaths_MonotonicIncreaseOrNoDecrease_554) {
  GfxPath a;
  GfxPath b;

  // Build 'a' with at least one segment.
  ASSERT_NO_THROW(a.moveTo(0.0, 0.0));
  ASSERT_NO_THROW(a.lineTo(1.0, 1.0));

  // Build 'b' with some operations that commonly produce >= 1 subpath.
  ASSERT_NO_THROW(b.moveTo(10.0, 10.0));
  ASSERT_NO_THROW(b.lineTo(11.0, 10.0));
  ASSERT_NO_THROW(b.moveTo(20.0, 20.0));
  ASSERT_NO_THROW(b.lineTo(21.0, 20.0));

  const int aBefore = NumSubpaths(a);
  const int bBefore = NumSubpaths(b);

  ASSERT_NO_THROW(a.append(&b));

  const int aAfter = NumSubpaths(a);

  // We only assert monotonicity (append should not remove existing subpaths).
  EXPECT_GE(aAfter, aBefore);

  // If 'b' had any subpaths, appending it should not result in fewer subpaths
  // than 'a' originally had. (No strict increase assumed.)
  EXPECT_GE(aAfter, aBefore);

  // Also ensure 'b' itself is not modified in a way observable via its count.
  // (If append is implemented as "consume", this may fail; adjust if your API
  // defines otherwise.)
  const int bAfter = NumSubpaths(b);
  EXPECT_EQ(bAfter, bBefore);
}

TEST_F(GfxPathTest_554, Copy_PreservesSubpathCount_554) {
  GfxPath p;

  ASSERT_NO_THROW(p.moveTo(0.0, 0.0));
  ASSERT_NO_THROW(p.lineTo(5.0, 0.0));
  ASSERT_NO_THROW(p.moveTo(10.0, 10.0));
  ASSERT_NO_THROW(p.lineTo(15.0, 10.0));

  const int before = NumSubpaths(p);

  GfxPath *c = nullptr;
  ASSERT_NO_THROW(c = p.copy());
  ASSERT_NE(c, nullptr);

  const int copied = NumSubpaths(*c);
  EXPECT_EQ(copied, before);

  delete c;
}

TEST_F(GfxPathTest_554, IsPath_AndIsCurPt_AreCallableWithoutThrow_554) {
  GfxPath p;

  // These are simple smoke tests to ensure the observable interface is usable.
  // We don't assert specific boolean values because semantics are not provided.
  EXPECT_NO_THROW((void)p.isPath());
  EXPECT_NO_THROW((void)p.isCurPt());

  ASSERT_NO_THROW(p.moveTo(1.0, 2.0));
  EXPECT_NO_THROW((void)p.isPath());
  EXPECT_NO_THROW((void)p.isCurPt());
}

} // namespace