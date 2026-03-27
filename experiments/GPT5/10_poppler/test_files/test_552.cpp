// TEST_ID: 552
// File: gfxpath_isCurPt_test_552.cpp

#include <gtest/gtest.h>

#include "GfxState.h"

class GfxPathTest_552 : public ::testing::Test {
protected:
  GfxPath path;
};

TEST_F(GfxPathTest_552, IsCurPtDoesNotThrowOnFreshObject_552) {
  EXPECT_NO_THROW({
    volatile bool v = path.isCurPt();
    (void)v;
  });
}

TEST_F(GfxPathTest_552, FreshPathHasNoCurrentPoint_552) {
  // A newly constructed path should not have a current point.
  EXPECT_FALSE(path.isCurPt());
}

TEST_F(GfxPathTest_552, MoveToCreatesCurrentPoint_552) {
  EXPECT_FALSE(path.isCurPt());
  path.moveTo(1.25, -3.5);
  EXPECT_TRUE(path.isCurPt());
}

TEST_F(GfxPathTest_552, LineToAfterMoveToKeepsCurrentPoint_552) {
  path.moveTo(0.0, 0.0);
  ASSERT_TRUE(path.isCurPt());

  path.lineTo(10.0, 20.0);
  EXPECT_TRUE(path.isCurPt());
}

TEST_F(GfxPathTest_552, CurveToAfterMoveToKeepsCurrentPoint_552) {
  path.moveTo(0.0, 0.0);
  ASSERT_TRUE(path.isCurPt());

  path.curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  EXPECT_TRUE(path.isCurPt());
}

TEST_F(GfxPathTest_552, CloseAfterMoveToKeepsCurrentPoint_552) {
  path.moveTo(2.0, 3.0);
  ASSERT_TRUE(path.isCurPt());

  path.close();
  EXPECT_TRUE(path.isCurPt());
}

TEST_F(GfxPathTest_552, OffsetDoesNotRemoveCurrentPoint_552) {
  path.moveTo(-1.0, -2.0);
  ASSERT_TRUE(path.isCurPt());

  path.offset(100.0, -50.0);
  EXPECT_TRUE(path.isCurPt());
}

TEST_F(GfxPathTest_552, CopyPreservesCurrentPointState_552) {
  EXPECT_FALSE(path.isCurPt());

  path.moveTo(7.0, 8.0);
  ASSERT_TRUE(path.isCurPt());

  GfxPath *copy = nullptr;
  ASSERT_NO_THROW(copy = path.copy());
  ASSERT_NE(copy, nullptr);

  EXPECT_TRUE(copy->isCurPt());

  delete copy;
}

TEST_F(GfxPathTest_552, AppendDoesNotClearCurrentPointWhenAppendingNonEmptyPath_552) {
  GfxPath other;
  other.moveTo(0.0, 0.0);
  ASSERT_TRUE(other.isCurPt());

  // Start with an empty path.
  EXPECT_FALSE(path.isCurPt());

  // Appending a non-empty path should result in a path that has a current point.
  path.append(&other);
  EXPECT_TRUE(path.isCurPt());
}