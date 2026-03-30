// SplashFTFont_glyphPathConicTo_test_2609.cc
#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>

// Poppler / Splash
#include "SplashPath.h"

// FreeType (for FT_Vector)
#include <ft2build.h>
#include FT_OUTLINE_H

// NOTE: glyphPathConicTo is a `static` function in SplashFTFont.cc (internal linkage).
// To unit test it, we include the .cc directly so the tests are in the same TU.
// The test target must NOT also compile/link SplashFTFont.cc separately, or you'll get ODR issues.
#include "SplashFTFont.cc"

namespace {

class SplashFTFontGlyphPathConicToTest_2609 : public ::testing::Test {
protected:
  SplashPath path_;
};

// Helper: get current point (returns true if available)
static bool GetCur(SplashPath &p, SplashCoord *x, SplashCoord *y) {
  return p.getCurPt(x, y);
}

TEST_F(SplashFTFontGlyphPathConicToTest_2609, NoCurrentPoint_DoesNotModifyPathOrNeedClose_2609) {
  // No moveTo() => no current point.
  SplashFTFontPath fp;
  fp.path = &path_;
  fp.textScale = 1.0;
  fp.needClose = false;

  const int len0 = path_.getLength();

  FT_Vector ctrl{};
  ctrl.x = 64;   // arbitrary
  ctrl.y = 128;  // arbitrary
  FT_Vector pt{};
  pt.x = 256;
  pt.y = -64;

  EXPECT_EQ(0, glyphPathConicTo(&ctrl, &pt, &fp));
  EXPECT_EQ(len0, path_.getLength()) << "Path length should not change when there is no current point";
  EXPECT_FALSE(fp.needClose) << "needClose should not be set when there is no current point";
}

TEST_F(SplashFTFontGlyphPathConicToTest_2609, WithCurrentPoint_AppendsCurveAndSetsNeedClose_2609) {
  ASSERT_EQ(splashOk, path_.moveTo((SplashCoord)0, (SplashCoord)0));

  SplashCoord x_before = 0, y_before = 0;
  ASSERT_TRUE(GetCur(path_, &x_before, &y_before));

  const int len0 = path_.getLength();

  SplashFTFontPath fp;
  fp.path = &path_;
  fp.textScale = 1.0;
  fp.needClose = false;

  FT_Vector ctrl{};
  ctrl.x = 64;
  ctrl.y = 64;
  FT_Vector pt{};
  pt.x = 512;
  pt.y = 256;

  EXPECT_EQ(0, glyphPathConicTo(&ctrl, &pt, &fp));

  EXPECT_GT(path_.getLength(), len0) << "Expected curve points appended to the path";
  EXPECT_TRUE(fp.needClose) << "Expected needClose to be set true after adding a curve";

  // Observable behavior via public API: current point should still be available.
  SplashCoord x_after = 0, y_after = 0;
  EXPECT_TRUE(GetCur(path_, &x_after, &y_after));

  // We avoid asserting exact coordinates (black-box), but a non-NaN sanity check is reasonable.
  EXPECT_FALSE(std::isnan((double)x_after));
  EXPECT_FALSE(std::isnan((double)y_after));
}

TEST_F(SplashFTFontGlyphPathConicToTest_2609, TextScaleZero_DoesNotCrashAndAppendsCurve_2609) {
  ASSERT_EQ(splashOk, path_.moveTo((SplashCoord)10, (SplashCoord)-5));
  const int len0 = path_.getLength();

  SplashFTFontPath fp;
  fp.path = &path_;
  fp.textScale = 0.0;
  fp.needClose = false;

  FT_Vector ctrl{};
  ctrl.x = 1000;
  ctrl.y = -2000;
  FT_Vector pt{};
  pt.x = 3000;
  pt.y = 4000;

  EXPECT_EQ(0, glyphPathConicTo(&ctrl, &pt, &fp));
  EXPECT_GT(path_.getLength(), len0) << "Even with zero scale, a curve should be appended when current point exists";
  EXPECT_TRUE(fp.needClose);
}

TEST_F(SplashFTFontGlyphPathConicToTest_2609, LargeVectorInputs_DoesNotCrashAndAppendsCurve_2609) {
  ASSERT_EQ(splashOk, path_.moveTo((SplashCoord)1, (SplashCoord)2));
  const int len0 = path_.getLength();

  SplashFTFontPath fp;
  fp.path = &path_;
  fp.textScale = 2.5;
  fp.needClose = false;

  // Boundary-ish: large-but-reasonable FT_Pos values (signed long).
  FT_Vector ctrl{};
  ctrl.x = (FT_Pos)(1L << 20);
  ctrl.y = (FT_Pos)(-(1L << 20));
  FT_Vector pt{};
  pt.x = (FT_Pos)(1L << 21);
  pt.y = (FT_Pos)(1L << 19);

  EXPECT_EQ(0, glyphPathConicTo(&ctrl, &pt, &fp));
  EXPECT_GT(path_.getLength(), len0);
  EXPECT_TRUE(fp.needClose);

  SplashCoord x_after = 0, y_after = 0;
  EXPECT_TRUE(GetCur(path_, &x_after, &y_after));
  EXPECT_FALSE(std::isnan((double)x_after));
  EXPECT_FALSE(std::isnan((double)y_after));
}

} // namespace