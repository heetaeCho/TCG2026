// ============================================================================
// SplashFTFont_glyphPathMoveTo_test_2607.cc
//
// Unit tests for glyphPathMoveTo() in SplashFTFont.cc
// ============================================================================

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "SplashPath.h"

// FreeType type used by glyphPathMoveTo signature.
#include <ft2build.h>
#include FT_FREETYPE_H

// NOTE:
// glyphPathMoveTo is declared "static" in SplashFTFont.cc, so it has internal
// linkage. To test it directly, we compile it into this test translation unit
// by including the .cc file.
// This is a common pattern for unit-testing file-local helpers.
#include "SplashFTFont.cc"

namespace {

// Helper to fetch the last point from a SplashPath.
static void GetLastPoint(const SplashPath &path, double *x, double *y, unsigned char *f) {
  ASSERT_GT(path.getLength(), 0);
  path.getPoint(path.getLength() - 1, x, y, f);
}

class SplashFTFontGlyphPathMoveToTest_2607 : public ::testing::Test {
protected:
  SplashPath path_;
};

} // namespace

TEST_F(SplashFTFontGlyphPathMoveToTest_2607, ReturnsZero_2607) {
  SplashFTFontPath p;
  p.path = &path_;
  p.textScale = 1.0;
  p.needClose = false;

  FT_Vector v;
  v.x = 0;
  v.y = 0;

  EXPECT_EQ(glyphPathMoveTo(&v, &p), 0);
}

TEST_F(SplashFTFontGlyphPathMoveToTest_2607, AddsMoveToPointWithScaling_2607) {
  SplashFTFontPath p;
  p.path = &path_;
  p.textScale = 2.0; // scale factor applied in glyphPathMoveTo
  p.needClose = false;

  FT_Vector v;
  v.x = 64;   // 1.0 in 26.6 fixed-point
  v.y = -128; // -2.0 in 26.6 fixed-point

  const int beforeLen = path_.getLength();
  ASSERT_EQ(glyphPathMoveTo(&v, &p), 0);
  EXPECT_EQ(path_.getLength(), beforeLen + 1);

  double x = 0, y = 0;
  unsigned char f = 0;
  GetLastPoint(path_, &x, &y, &f);

  // Expected: pt->x * textScale / 64.0, same for y.
  const double expectedX = static_cast<double>(v.x) * static_cast<double>(p.textScale) / 64.0;
  const double expectedY = static_cast<double>(v.y) * static_cast<double>(p.textScale) / 64.0;

  EXPECT_NEAR(x, expectedX, 1e-9);
  EXPECT_NEAR(y, expectedY, 1e-9);
}

TEST_F(SplashFTFontGlyphPathMoveToTest_2607, NeedCloseFalseDoesNotForceCloseBeforeMove_2607) {
  // Build an open subpath: moveTo + lineTo (not closed).
  ASSERT_EQ(path_.moveTo(0, 0), splashOk);
  ASSERT_EQ(path_.lineTo(10, 0), splashOk);

  // Capture the last point flags before calling glyphPathMoveTo.
  double bx = 0, by = 0;
  unsigned char bf = 0;
  GetLastPoint(path_, &bx, &by, &bf);

  SplashFTFontPath p;
  p.path = &path_;
  p.textScale = 1.0;
  p.needClose = false;

  FT_Vector v;
  v.x = 0;
  v.y = 0;

  ASSERT_EQ(glyphPathMoveTo(&v, &p), 0);

  // Re-check the previously-last point (index: length - 2 after adding a point).
  ASSERT_GE(path_.getLength(), 3);
  const int oldLastIdx = path_.getLength() - 2;

  double ax = 0, ay = 0;
  unsigned char af = 0;
  path_.getPoint(oldLastIdx, &ax, &ay, &af);

  // We don't assume internal flag meanings beyond "closed" bit existing.
  // If needClose is false, the helper should not close an open subpath.
  EXPECT_EQ((af & splashPathClosed) != 0, (bf & splashPathClosed) != 0);
}

TEST_F(SplashFTFontGlyphPathMoveToTest_2607, NeedCloseTrueClosesPreviousSubpathAndClearsNeedClose_2607) {
  // Build an open subpath first.
  ASSERT_EQ(path_.moveTo(0, 0), splashOk);
  ASSERT_EQ(path_.lineTo(10, 0), splashOk);

  // Ensure it is open prior to the call (best-effort observable check).
  double x0 = 0, y0 = 0;
  unsigned char f0 = 0;
  GetLastPoint(path_, &x0, &y0, &f0);
  const bool wasClosed = (f0 & splashPathClosed) != 0;

  SplashFTFontPath p;
  p.path = &path_;
  p.textScale = 1.0;
  p.needClose = true;

  FT_Vector v;
  v.x = 64;
  v.y = 64;

  ASSERT_EQ(glyphPathMoveTo(&v, &p), 0);

  // The helper is expected to clear the flag after closing.
  EXPECT_FALSE(p.needClose);

  // Now check whether the previously-open subpath became closed.
  // The previous "last point" is now at (length - 2).
  ASSERT_GE(path_.getLength(), 3);
  const int prevLastIdx = path_.getLength() - 2;

  double x1 = 0, y1 = 0;
  unsigned char f1 = 0;
  path_.getPoint(prevLastIdx, &x1, &y1, &f1);

  const bool isClosedNow = (f1 & splashPathClosed) != 0;

  // Observable expectation: if it wasn't closed before, needClose=true should close it.
  // If it was already closed (unusual here), we at least require it remains closed.
  if (!wasClosed) {
    EXPECT_TRUE(isClosedNow);
  } else {
    EXPECT_TRUE(isClosedNow);
  }
}

TEST_F(SplashFTFontGlyphPathMoveToTest_2607, TextScaleZeroMovesToOriginRegardlessOfVector_2607) {
  SplashFTFontPath p;
  p.path = &path_;
  p.textScale = 0.0;
  p.needClose = false;

  FT_Vector v;
  v.x = 123456;
  v.y = -654321;

  ASSERT_EQ(glyphPathMoveTo(&v, &p), 0);

  double x = 0, y = 0;
  unsigned char f = 0;
  GetLastPoint(path_, &x, &y, &f);

  EXPECT_NEAR(x, 0.0, 1e-12);
  EXPECT_NEAR(y, 0.0, 1e-12);
}

TEST_F(SplashFTFontGlyphPathMoveToTest_2607, NegativeTextScaleProducesNegatedCoordinates_2607) {
  SplashFTFontPath p;
  p.path = &path_;
  p.textScale = -3.0;
  p.needClose = false;

  FT_Vector v;
  v.x = 64;   // 1.0
  v.y = -64;  // -1.0

  ASSERT_EQ(glyphPathMoveTo(&v, &p), 0);

  double x = 0, y = 0;
  unsigned char f = 0;
  GetLastPoint(path_, &x, &y, &f);

  const double expectedX = static_cast<double>(v.x) * static_cast<double>(p.textScale) / 64.0; // -3
  const double expectedY = static_cast<double>(v.y) * static_cast<double>(p.textScale) / 64.0; // +3

  EXPECT_NEAR(x, expectedX, 1e-9);
  EXPECT_NEAR(y, expectedY, 1e-9);
}