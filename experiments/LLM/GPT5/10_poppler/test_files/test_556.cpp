// TEST_ID = 556
//
// Unit tests for GfxPath::getLastX()
// File: gfxpath_getLastX_unittest_556.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "poppler/GfxState.h"

class GfxPathTest_556 : public ::testing::Test {
protected:
  GfxPath path;
};

TEST_F(GfxPathTest_556, MoveToSetsLastX_556) {
  path.moveTo(10.5, -3.25);
  EXPECT_DOUBLE_EQ(path.getLastX(), 10.5);
}

TEST_F(GfxPathTest_556, LineToUpdatesLastX_556) {
  path.moveTo(0.0, 0.0);
  path.lineTo(1.25, 2.5);
  EXPECT_DOUBLE_EQ(path.getLastX(), 1.25);

  path.lineTo(-7.0, 9.0);
  EXPECT_DOUBLE_EQ(path.getLastX(), -7.0);
}

TEST_F(GfxPathTest_556, CurveToUpdatesLastXToThirdControlPointX_556) {
  path.moveTo(0.0, 0.0);

  // Typical cubic Bezier: last point is (x3, y3).
  path.curveTo(1.0, 2.0, 3.0, 4.0, 5.5, 6.5);
  EXPECT_DOUBLE_EQ(path.getLastX(), 5.5);

  path.curveTo(-1.0, -2.0, -3.0, -4.0, -8.25, 9.75);
  EXPECT_DOUBLE_EQ(path.getLastX(), -8.25);
}

TEST_F(GfxPathTest_556, CloseDoesNotChangeLastX_556) {
  path.moveTo(2.0, 3.0);
  path.lineTo(4.0, 5.0);
  const double before = path.getLastX();

  path.close();

  EXPECT_DOUBLE_EQ(path.getLastX(), before);
}

TEST_F(GfxPathTest_556, OffsetShiftsLastX_556) {
  path.moveTo(1.0, 1.0);
  path.lineTo(3.5, 2.0);

  path.offset(2.25, -100.0);
  EXPECT_DOUBLE_EQ(path.getLastX(), 3.5 + 2.25);

  path.offset(-1.25, 0.0);
  EXPECT_DOUBLE_EQ(path.getLastX(), 3.5 + 2.25 - 1.25);
}

TEST_F(GfxPathTest_556, AppendMakesLastXComeFromAppendedPathEnd_556) {
  GfxPath base;
  base.moveTo(0.0, 0.0);
  base.lineTo(1.0, 0.0);

  GfxPath other;
  other.moveTo(10.0, 10.0);
  other.lineTo(20.0, 30.0);
  other.lineTo(40.0, 50.0);

  base.append(&other);

  // Observable expectation: after appending a non-empty path, the last point of
  // the combined path should match the appended path's last point.
  EXPECT_DOUBLE_EQ(base.getLastX(), other.getLastX());
  EXPECT_DOUBLE_EQ(base.getLastX(), 40.0);
}

TEST_F(GfxPathTest_556, OffsetBoundaryLargeValues_556) {
  const double big = 1e300;
  const double dx = 1e200;

  path.moveTo(big, 0.0);
  path.lineTo(big, 1.0);
  path.offset(dx, 0.0);

  EXPECT_DOUBLE_EQ(path.getLastX(), big + dx);
}

TEST_F(GfxPathTest_556, AcceptsNaNAndInfinity_556) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  const double inf = std::numeric_limits<double>::infinity();

  path.moveTo(inf, 0.0);
  EXPECT_TRUE(std::isinf(path.getLastX()));

  path.lineTo(nan, 1.0);
  EXPECT_TRUE(std::isnan(path.getLastX()));
}

TEST_F(GfxPathTest_556, GetLastXOnEmptyPathDies_556) {
  // With a default-constructed GfxPath (no moveTo/lineTo/etc.), getLastX()
  // is not meaningfully defined. The provided snippet shows it indexing the
  // last subpath; this is expected to be unsafe when empty.
#if GTEST_HAS_DEATH_TEST
  ASSERT_DEATH(
      {
        volatile double x = path.getLastX();
        (void)x;
      },
      ".*");
#else
  GTEST_SKIP() << "Death tests are not supported on this platform/config.";
#endif
}