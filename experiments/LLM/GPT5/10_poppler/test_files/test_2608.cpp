// SPDX-License-Identifier: GPL-2.0-or-later
// File: SplashFTFont_glyphPathLineTo_test_2608.cc

#include <gtest/gtest.h>

#include "SplashPath.h"

#include <ft2build.h>
#include FT_OUTLINE_H

// NOTE:
// glyphPathLineTo() is a static (internal-linkage) helper in SplashFTFont.cc.
// To test it as a black box via its observable effects, we include the .cc so
// the symbol is available in this translation unit.
#include "SplashFTFont.cc"

namespace {

// Helper: fetch the last point from a SplashPath.
static void GetLastPoint(const SplashPath &path, double *x, double *y, unsigned char *f) {
  ASSERT_GT(path.getLength(), 0);
  path.getPoint(path.getLength() - 1, x, y, f);
}

class SplashFTFontGlyphPathLineToTest_2608 : public ::testing::Test {
protected:
  SplashPath path_;
};

TEST_F(SplashFTFontGlyphPathLineToTest_2608, ReturnsZeroAndAppendsLineTo_2608) {
  // Arrange: ensure there is a current point so lineTo is meaningful.
  ASSERT_EQ(path_.moveTo(0, 0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = 1.0;
  p.needClose = false;

  const int beforeLen = path_.getLength();

  FT_Vector v{};
  v.x = 64;   // 1.0 in 26.6 fixed
  v.y = 128;  // 2.0 in 26.6 fixed

  // Act
  const int ret = glyphPathLineTo(&v, &p);

  // Assert
  EXPECT_EQ(ret, 0);
  EXPECT_EQ(path_.getLength(), beforeLen + 1);

  double x = 0, y = 0;
  unsigned char f = 0;
  GetLastPoint(path_, &x, &y, &f);

  EXPECT_DOUBLE_EQ(x, 1.0);
  EXPECT_DOUBLE_EQ(y, 2.0);
  EXPECT_TRUE(p.needClose);
}

TEST_F(SplashFTFontGlyphPathLineToTest_2608, AppliesTextScale_2608) {
  ASSERT_EQ(path_.moveTo(0, 0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = 2.0;
  p.needClose = false;

  FT_Vector v{};
  v.x = 64;   // 1.0
  v.y = 128;  // 2.0

  const int beforeLen = path_.getLength();
  EXPECT_EQ(glyphPathLineTo(&v, &p), 0);
  EXPECT_EQ(path_.getLength(), beforeLen + 1);

  double x = 0, y = 0;
  unsigned char f = 0;
  GetLastPoint(path_, &x, &y, &f);

  EXPECT_DOUBLE_EQ(x, 2.0);
  EXPECT_DOUBLE_EQ(y, 4.0);
  EXPECT_TRUE(p.needClose);
}

TEST_F(SplashFTFontGlyphPathLineToTest_2608, HandlesNegativeCoordinates_2608) {
  ASSERT_EQ(path_.moveTo(0, 0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = 1.0;
  p.needClose = false;

  FT_Vector v{};
  v.x = -64;  // -1.0
  v.y = -64;  // -1.0

  EXPECT_EQ(glyphPathLineTo(&v, &p), 0);

  double x = 0, y = 0;
  unsigned char f = 0;
  GetLastPoint(path_, &x, &y, &f);

  EXPECT_DOUBLE_EQ(x, -1.0);
  EXPECT_DOUBLE_EQ(y, -1.0);
  EXPECT_TRUE(p.needClose);
}

TEST_F(SplashFTFontGlyphPathLineToTest_2608, BoundaryLargeButReasonableValues_2608) {
  ASSERT_EQ(path_.moveTo(0, 0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = 1.0;
  p.needClose = false;

  // Use a large value that should still be representable as double cleanly.
  // 26.6 fixed: 64 * 10000 => 10000.0
  FT_Vector v{};
  v.x = 64 * 10000;
  v.y = 64 * 20000;

  const int beforeLen = path_.getLength();
  EXPECT_EQ(glyphPathLineTo(&v, &p), 0);
  EXPECT_EQ(path_.getLength(), beforeLen + 1);

  double x = 0, y = 0;
  unsigned char f = 0;
  GetLastPoint(path_, &x, &y, &f);

  EXPECT_DOUBLE_EQ(x, 10000.0);
  EXPECT_DOUBLE_EQ(y, 20000.0);
  EXPECT_TRUE(p.needClose);
}

TEST_F(SplashFTFontGlyphPathLineToTest_2608, NeedCloseSetTrueEvenIfAlreadyTrue_2608) {
  ASSERT_EQ(path_.moveTo(0, 0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = 1.0;
  p.needClose = true;

  FT_Vector v{};
  v.x = 64;
  v.y = 64;

  EXPECT_EQ(glyphPathLineTo(&v, &p), 0);
  EXPECT_TRUE(p.needClose); // remains true
}

} // namespace