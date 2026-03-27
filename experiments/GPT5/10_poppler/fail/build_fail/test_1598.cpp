// SplashOutputDev_clip255_test_1598.cc
#include <gtest/gtest.h>

#include <limits>

// NOTE:
// clip255() is declared as `static inline` inside SplashOutputDev.cc, so it has
// internal linkage and is not visible across translation units.
// For black-box testing of the *provided interface* (the function signature and
// its observable return values), we include the implementation file here to
// make clip255() callable from this test TU.
#include "SplashOutputDev.cc"

namespace {

class Clip255Test_1598 : public ::testing::Test {};

TEST_F(Clip255Test_1598, ReturnsSameValueForInRangeInputs_1598) {
  EXPECT_EQ(0u, clip255(0));
  EXPECT_EQ(1u, clip255(1));
  EXPECT_EQ(42u, clip255(42));
  EXPECT_EQ(254u, clip255(254));
  EXPECT_EQ(255u, clip255(255));
}

TEST_F(Clip255Test_1598, ClampsNegativeValuesToZero_1598) {
  EXPECT_EQ(0u, clip255(-1));
  EXPECT_EQ(0u, clip255(-42));
  EXPECT_EQ(0u, clip255(std::numeric_limits<int>::min()));
}

TEST_F(Clip255Test_1598, ClampsValuesAbove255To255_1598) {
  EXPECT_EQ(255u, clip255(256));
  EXPECT_EQ(255u, clip255(300));
  EXPECT_EQ(255u, clip255(std::numeric_limits<int>::max()));
}

TEST_F(Clip255Test_1598, BoundaryConditionsAroundLimits_1598) {
  // Just below / at / just above the clamp thresholds.
  EXPECT_EQ(0u, clip255(-1));
  EXPECT_EQ(0u, clip255(0));
  EXPECT_EQ(1u, clip255(1));

  EXPECT_EQ(254u, clip255(254));
  EXPECT_EQ(255u, clip255(255));
  EXPECT_EQ(255u, clip255(256));
}

}  // namespace