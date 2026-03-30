// SplashImgCoordMungeUpperC_test_2614.cc
#include <gtest/gtest.h>

#include <limits>
#include <vector>

// NOTE:
// imgCoordMungeUpperC() is a `static inline` function in Splash.cc, so it is not link-visible.
// To test it as a black box through its signature/return value, we include the implementation
// translation unit here so the symbol is available in this test TU.
#include "TestProjects/poppler/splash/Splash.cc"

namespace {

class ImgCoordMungeUpperCTest_2614 : public ::testing::Test {};

// Helper to make assertions easier to read.
static int Call(SplashCoord x, bool glyphMode) {
  return imgCoordMungeUpperC(x, glyphMode);
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphModeFalse_KnownPoints_2614) {
  struct Case {
    SplashCoord x;
    int expected;
  };

  const std::vector<Case> cases = {
      {-1.2, -1}, {-1.0, 0}, {-0.6, 0}, {-0.5, 0}, {-0.4, 0}, {0.0, 1},
      {0.4, 1},   {0.5, 1},  {0.6, 1},  {1.0, 2},  {1.2, 2},  {2.49, 3},
      {2.5, 3},   {2.51, 3},
  };

  for (const auto& tc : cases) {
    EXPECT_EQ(Call(tc.x, /*glyphMode=*/false), tc.expected) << "x=" << tc.x;
  }
}

TEST_F(ImgCoordMungeUpperCTest_2614, GlyphModeTrue_KnownPoints_2614) {
  struct Case {
    SplashCoord x;
    int expected;
  };

  const std::vector<Case> cases = {
      {-1.2, -1}, {-1.0, -1}, {-0.6, -1}, {-0.5, -1}, {-0.4, 0}, {0.0, 0},
      {0.4, 0},   {0.5, 0},   {0.6, 1},   {1.0, 1},  {1.2, 1},  {2.49, 2},
      {2.5, 2},   {2.51, 3},
  };

  for (const auto& tc : cases) {
    EXPECT_EQ(Call(tc.x, /*glyphMode=*/true), tc.expected) << "x=" << tc.x;
  }
}

TEST_F(ImgCoordMungeUpperCTest_2614, Boundary_AroundHalfStep_2614) {
  // Focus on values around the 0.5 boundary where behavior can change.
  EXPECT_EQ(Call(-0.5, /*glyphMode=*/true), -1);
  EXPECT_EQ(Call(-0.4, /*glyphMode=*/true), 0);

  EXPECT_EQ(Call(0.5, /*glyphMode=*/true), 0);
  EXPECT_EQ(Call(0.6, /*glyphMode=*/true), 1);

  // For non-glyph mode, ensure these representative boundaries are stable too.
  EXPECT_EQ(Call(-0.5, /*glyphMode=*/false), 0);
  EXPECT_EQ(Call(0.0, /*glyphMode=*/false), 1);
  EXPECT_EQ(Call(0.999999, /*glyphMode=*/false), 1);
  EXPECT_EQ(Call(1.0, /*glyphMode=*/false), 2);
}

TEST_F(ImgCoordMungeUpperCTest_2614, ModeToggle_ProducesDifferentResultForSomeInputs_2614) {
  // There should exist inputs where glyphMode changes the result.
  EXPECT_NE(Call(0.0, /*glyphMode=*/false), Call(0.0, /*glyphMode=*/true));
  EXPECT_NE(Call(1.0, /*glyphMode=*/false), Call(1.0, /*glyphMode=*/true));
}

TEST_F(ImgCoordMungeUpperCTest_2614, MonotonicNonDecreasing_ForIncreasingX_2614) {
  const std::vector<SplashCoord> xs = {-2.0, -1.2, -1.0, -0.6, -0.5, -0.4, 0.0,
                                       0.4,  0.5,  0.6,  0.9,  1.0,  1.2, 2.49,
                                       2.5,  2.51, 10.0};

  for (bool glyphMode : {false, true}) {
    int prev = Call(xs.front(), glyphMode);
    for (size_t i = 1; i < xs.size(); ++i) {
      const int cur = Call(xs[i], glyphMode);
      EXPECT_LE(prev, cur) << "glyphMode=" << glyphMode << " at x=" << xs[i];
      prev = cur;
    }
  }
}

TEST_F(ImgCoordMungeUpperCTest_2614, LargeMagnitudeInputs_DoNotCrashAndReturnInt_2614) {
  // Use large but reasonable magnitudes to avoid platform-specific UB from int overflow.
  const SplashCoord big1 = static_cast<SplashCoord>(1e6) + 0.25;
  const SplashCoord big2 = static_cast<SplashCoord>(-1e6) - 0.25;

  const int r1 = Call(big1, /*glyphMode=*/false);
  const int r2 = Call(big1, /*glyphMode=*/true);
  const int r3 = Call(big2, /*glyphMode=*/false);
  const int r4 = Call(big2, /*glyphMode=*/true);

  // Observable contract: returns an int (no further assumptions).
  (void)r1;
  (void)r2;
  (void)r3;
  (void)r4;

  SUCCEED();
}

}  // namespace