// File: SplashImageInterpolationRequiredTest_2615.cc

#include <gtest/gtest.h>

// We include the implementation file so that we can test the internal-linkage
// (static) function in the same translation unit, without modifying production code.
#include "TestProjects/poppler/splash/Splash.cc"

class SplashImageInterpolationRequiredTest_2615 : public ::testing::Test {};

// ---- Normal operation ----

TEST_F(SplashImageInterpolationRequiredTest_2615, ReturnsTrueWhenInterpolateFlagTrue_2615) {
  EXPECT_TRUE(isImageInterpolationRequired(10, 10, 1, 1, true));
  EXPECT_TRUE(isImageInterpolationRequired(0, 0, 0, 0, true));
  EXPECT_TRUE(isImageInterpolationRequired(100, 50, 400, 200, true));
}

TEST_F(SplashImageInterpolationRequiredTest_2615, ReturnsTrueWhenSourceWidthZero_2615) {
  // srcWidth == 0 should force true when interpolate is false.
  EXPECT_TRUE(isImageInterpolationRequired(0, 10, 0, 0, false));
  EXPECT_TRUE(isImageInterpolationRequired(0, 10, 400, 10, false));
}

TEST_F(SplashImageInterpolationRequiredTest_2615, ReturnsTrueWhenSourceHeightZero_2615) {
  // srcHeight == 0 should force true when interpolate is false.
  EXPECT_TRUE(isImageInterpolationRequired(10, 0, 0, 0, false));
  EXPECT_TRUE(isImageInterpolationRequired(10, 0, 10, 400, false));
}

// ---- Boundary conditions around the 4x threshold ----

TEST_F(SplashImageInterpolationRequiredTest_2615, ReturnsFalseAtOrAbove4xScaleInWidth_2615) {
  // Exactly 4x in width -> false (when interpolate is false and src dims non-zero).
  EXPECT_FALSE(isImageInterpolationRequired(100, 100, 400, 399, false));
  // Above 4x in width -> false.
  EXPECT_FALSE(isImageInterpolationRequired(100, 100, 401, 1, false));
}

TEST_F(SplashImageInterpolationRequiredTest_2615, ReturnsFalseAtOrAbove4xScaleInHeight_2615) {
  // Exactly 4x in height -> false (when interpolate is false and src dims non-zero).
  EXPECT_FALSE(isImageInterpolationRequired(100, 100, 399, 400, false));
  // Above 4x in height -> false.
  EXPECT_FALSE(isImageInterpolationRequired(100, 100, 1, 401, false));
}

TEST_F(SplashImageInterpolationRequiredTest_2615, ReturnsTrueJustBelow4xScale_2615) {
  // Just below 4x (integer division) should remain true.
  // 399 / 100 == 3, so interpolation should be required -> true.
  EXPECT_TRUE(isImageInterpolationRequired(100, 100, 399, 399, false));

  // Small sizes: 7 / 2 == 3 (integer division), still below 4 -> true.
  EXPECT_TRUE(isImageInterpolationRequired(2, 2, 7, 7, false));
}

// ---- Exceptional / error-ish inputs (observable via return value) ----

TEST_F(SplashImageInterpolationRequiredTest_2615, HandlesZeroScaledDimensionsWithoutCrashing_2615) {
  // With valid non-zero source sizes and interpolate=false, scale factor 0 -> true.
  EXPECT_TRUE(isImageInterpolationRequired(10, 10, 0, 0, false));
  EXPECT_TRUE(isImageInterpolationRequired(10, 10, 0, 39, false));
  EXPECT_TRUE(isImageInterpolationRequired(10, 10, 39, 0, false));
}

TEST_F(SplashImageInterpolationRequiredTest_2615, HandlesNegativeDimensionsAsNon4xScale_2615) {
  // Negative values are not blocked by the interface; verify stable/observable behavior
  // via return value. With interpolate=false and non-zero src dims, negative ratios
  // should not meet a >=4 threshold and thus should return true.
  EXPECT_TRUE(isImageInterpolationRequired(10, 10, -1, 10, false));
  EXPECT_TRUE(isImageInterpolationRequired(10, 10, 10, -1, false));
  EXPECT_TRUE(isImageInterpolationRequired(10, 10, -400, -400, false));
}