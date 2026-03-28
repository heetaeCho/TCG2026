// TEST_ID: 553
// File: test_gfxpath_ispath_553.cpp

#include <gtest/gtest.h>

// Include the real header from the project.
#include "poppler/GfxState.h"

namespace {

class GfxPathTest_553 : public ::testing::Test {};

TEST_F(GfxPathTest_553, DefaultConstructedIsNotPath_553) {
  GfxPath path;
  EXPECT_FALSE(path.isPath());
}

TEST_F(GfxPathTest_553, MoveToMakesItAPath_553) {
  GfxPath path;
  path.moveTo(0.0, 0.0);
  EXPECT_TRUE(path.isPath());
}

TEST_F(GfxPathTest_553, LineToAfterMoveToIsPath_553) {
  GfxPath path;
  path.moveTo(1.0, 2.0);
  path.lineTo(3.0, 4.0);
  EXPECT_TRUE(path.isPath());
}

TEST_F(GfxPathTest_553, CloseOnFreshPathDoesNotCreatePath_553) {
  GfxPath path;
  path.close();
  EXPECT_FALSE(path.isPath());
}

TEST_F(GfxPathTest_553, CloseAfterMoveToRemainsPath_553) {
  GfxPath path;
  path.moveTo(-5.0, 7.5);
  path.close();
  EXPECT_TRUE(path.isPath());
}

TEST_F(GfxPathTest_553, CurveToAfterMoveToIsPath_553) {
  GfxPath path;
  path.moveTo(0.0, 0.0);
  path.curveTo(1.0, 0.0, 2.0, 1.0, 3.0, 3.0);
  EXPECT_TRUE(path.isPath());
}

TEST_F(GfxPathTest_553, AppendNullPointerIsSafeAndPreservesState_553) {
  GfxPath path;
  EXPECT_FALSE(path.isPath());

  // Boundary/error-ish case: appending nullptr should not crash. If the API
  // tolerates it, observable behavior should remain stable.
  path.append(nullptr);

  EXPECT_FALSE(path.isPath());

  path.moveTo(0.0, 0.0);
  EXPECT_TRUE(path.isPath());

  path.append(nullptr);
  EXPECT_TRUE(path.isPath());
}

TEST_F(GfxPathTest_553, AppendEmptyPathDoesNotMakeNonEmpty_553) {
  GfxPath dst;
  GfxPath src;

  EXPECT_FALSE(dst.isPath());
  EXPECT_FALSE(src.isPath());

  dst.append(&src);

  // Appending an empty path should not create a path out of nothing.
  EXPECT_FALSE(dst.isPath());
}

TEST_F(GfxPathTest_553, AppendNonEmptyPathMakesDestinationPath_553) {
  GfxPath dst;
  GfxPath src;

  EXPECT_FALSE(dst.isPath());
  src.moveTo(10.0, 20.0);
  EXPECT_TRUE(src.isPath());

  dst.append(&src);

  // Observable: destination should now represent a path.
  EXPECT_TRUE(dst.isPath());
}

TEST_F(GfxPathTest_553, OffsetDoesNotCreatePathFromEmpty_553) {
  GfxPath path;
  EXPECT_FALSE(path.isPath());

  path.offset(1.0, -2.0);
  EXPECT_FALSE(path.isPath());
}

TEST_F(GfxPathTest_553, OffsetPreservesPathStatusForNonEmpty_553) {
  GfxPath path;
  path.moveTo(0.0, 0.0);
  EXPECT_TRUE(path.isPath());

  path.offset(100.0, 200.0);
  EXPECT_TRUE(path.isPath());
}

TEST_F(GfxPathTest_553, CopyOfEmptyPreservesIsPathFalse_553) {
  GfxPath original;
  EXPECT_FALSE(original.isPath());

  GfxPath *copy = original.copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_FALSE(copy->isPath());

  delete copy;
}

TEST_F(GfxPathTest_553, CopyOfNonEmptyPreservesIsPathTrue_553) {
  GfxPath original;
  original.moveTo(1.0, 1.0);
  EXPECT_TRUE(original.isPath());

  GfxPath *copy = original.copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->isPath());

  delete copy;
}

TEST_F(GfxPathTest_553, RepeatedOperationsMaintainConsistentIsPath_553) {
  GfxPath path;
  EXPECT_FALSE(path.isPath());

  // Do some benign ops on an empty path.
  path.offset(0.0, 0.0);
  path.close();
  EXPECT_FALSE(path.isPath());

  // Make it non-empty and ensure it stays non-empty.
  path.moveTo(0.0, 0.0);
  EXPECT_TRUE(path.isPath());

  path.lineTo(0.0, 0.0);  // degenerate segment boundary case
  EXPECT_TRUE(path.isPath());

  path.curveTo(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  // degenerate curve boundary case
  EXPECT_TRUE(path.isPath());

  path.close();
  EXPECT_TRUE(path.isPath());

  path.offset(-0.0, +0.0);
  EXPECT_TRUE(path.isPath());
}

}  // namespace