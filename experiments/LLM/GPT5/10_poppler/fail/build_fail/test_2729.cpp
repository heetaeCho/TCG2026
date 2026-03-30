// File: HtmlOutputDev_IS_CLOSER_test_2729.cc
#include <gtest/gtest.h>

#include <cmath>
#include <limits>

// NOTE:
// IS_CLOSER is declared `static inline` inside HtmlOutputDev.cc, so it has internal linkage.
// To test it without re-declaring/re-implementing, we include the .cc directly so the test
// translation unit can see the symbol.
//
// If your build system dislikes including .cc files, you’ll need to expose IS_CLOSER via a
// small test-only header or move it to a header in production code.
#include "poppler/utils/HtmlOutputDev.cc"

class IsCloserTest_2729 : public ::testing::Test {};

TEST_F(IsCloserTest_2729, ReturnsTrueWhenYEqualsXAndZDifferent_2729) {
  const double x = 10.0;
  const double y = 10.0;
  const double z = 11.0;

  EXPECT_TRUE(IS_CLOSER(x, y, z));
}

TEST_F(IsCloserTest_2729, ReturnsFalseWhenZEqualsXAndYDifferent_2729) {
  const double x = -3.5;
  const double y = -3.0;
  const double z = -3.5;

  EXPECT_FALSE(IS_CLOSER(x, y, z));
}

TEST_F(IsCloserTest_2729, ReturnsFalseWhenYAndZAreEquidistantFromX_2729) {
  const double x = 0.0;
  const double y = 1.0;
  const double z = -1.0;

  // Tie case: strict comparison should not treat y as closer.
  EXPECT_FALSE(IS_CLOSER(x, y, z));
}

TEST_F(IsCloserTest_2729, ReturnsTrueWhenYIsConstructedCloserThanZ_2729) {
  const double x = 100.0;
  const double y = 101.0;  // closer
  const double z = 105.0;  // farther

  EXPECT_TRUE(IS_CLOSER(x, y, z));
}

TEST_F(IsCloserTest_2729, ReturnsFalseWhenYIsConstructedFartherThanZ_2729) {
  const double x = 100.0;
  const double y = 120.0;  // farther
  const double z = 101.0;  // closer

  EXPECT_FALSE(IS_CLOSER(x, y, z));
}

TEST_F(IsCloserTest_2729, HandlesVerySmallDifferences_2729) {
  const double x = 1.0;
  const double y = std::nextafter(1.0, 2.0);  // minimal step above 1.0
  const double z = 1.0 + 1e-6;

  EXPECT_TRUE(IS_CLOSER(x, y, z));
}

TEST_F(IsCloserTest_2729, HandlesNegativeValues_2729) {
  const double x = -10.0;
  const double y = -9.0;   // distance 1
  const double z = -7.0;   // distance 3

  EXPECT_TRUE(IS_CLOSER(x, y, z));
}

TEST_F(IsCloserTest_2729, NaNInXYOrZYieldsFalse_2729) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  const double x = 0.0;

  // Any NaN participating in fabs/subtraction generally leads to NaN and comparisons are false.
  EXPECT_FALSE(IS_CLOSER(nan, 0.0, 1.0));
  EXPECT_FALSE(IS_CLOSER(x, nan, 1.0));
  EXPECT_FALSE(IS_CLOSER(x, 0.0, nan));
}

TEST_F(IsCloserTest_2729, InfinityCasesBehaveConsistently_2729) {
  const double inf = std::numeric_limits<double>::infinity();

  // x is finite, y is exactly x, z is +inf -> y should be closer.
  EXPECT_TRUE(IS_CLOSER(5.0, 5.0, inf));

  // x is finite, y is +inf, z is finite and equals x -> z is closer, so y is NOT closer.
  EXPECT_FALSE(IS_CLOSER(5.0, inf, 5.0));

  // x is +inf: comparing closeness gets tricky (inf - finite is inf, inf - inf is NaN).
  // We only assert it doesn't crash and returns a boolean; for inf-inf producing NaN,
  // strict comparison should yield false.
  EXPECT_FALSE(IS_CLOSER(inf, inf, 0.0));
}