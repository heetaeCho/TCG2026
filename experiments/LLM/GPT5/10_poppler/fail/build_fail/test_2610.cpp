// File: glyphPathCubicTo_test_2610.cc
#include <gtest/gtest.h>

#include <cmath>
#include <type_traits>

#include "SplashPath.h"

#include <ft2build.h>
#include FT_FREETYPE_H

// Include the implementation file to access the static function under test.
// NOTE: This is intentional for testing internal-linkage helpers.
#include "TestProjects/poppler/splash/SplashFTFont.cc"

namespace {

// --- compile-time detection for optional member `needClose` ---
template <typename T, typename = void>
struct has_needClose : std::false_type {};
template <typename T>
struct has_needClose<T, std::void_t<decltype(std::declval<T &>().needClose)>> : std::true_type {};

// Helper: read point i from SplashPath as doubles + flags.
static void GetPt(const SplashPath &path, int i, double *x, double *y, unsigned char *f) {
  ASSERT_NE(x, nullptr);
  ASSERT_NE(y, nullptr);
  ASSERT_NE(f, nullptr);
  path.getPoint(i, x, y, f);
}

static double Scaled(long v, double textScale) {
  return static_cast<double>(v) * textScale / 64.0;
}

class GlyphPathCubicToTest_2610 : public ::testing::Test {
protected:
  SplashPath path_;
};

} // namespace

TEST_F(GlyphPathCubicToTest_2610, AppendsThreeCurvePointsScaledBy64_2610) {
  ASSERT_EQ(path_.moveTo(10.0, 20.0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = 1.0;

  FT_Vector c1{64, 128};
  FT_Vector c2{192, 256};
  FT_Vector pt{320, 384};

  const int beforeLen = path_.getLength();
  const int rc = glyphPathCubicTo(&c1, &c2, &pt, &p);

  EXPECT_EQ(rc, 0);
  const int afterLen = path_.getLength();
  EXPECT_EQ(afterLen, beforeLen + 3);

  // Verify the last three points match ctrl1, ctrl2, end (scaled).
  double x = 0, y = 0;
  unsigned char f = 0;

  GetPt(path_, beforeLen + 0, &x, &y, &f);
  EXPECT_NEAR(x, Scaled(c1.x, 1.0), 1e-9);
  EXPECT_NEAR(y, Scaled(c1.y, 1.0), 1e-9);

  GetPt(path_, beforeLen + 1, &x, &y, &f);
  EXPECT_NEAR(x, Scaled(c2.x, 1.0), 1e-9);
  EXPECT_NEAR(y, Scaled(c2.y, 1.0), 1e-9);

  GetPt(path_, beforeLen + 2, &x, &y, &f);
  EXPECT_NEAR(x, Scaled(pt.x, 1.0), 1e-9);
  EXPECT_NEAR(y, Scaled(pt.y, 1.0), 1e-9);
}

TEST_F(GlyphPathCubicToTest_2610, RespectsTextScaleFactor_2610) {
  ASSERT_EQ(path_.moveTo(0.0, 0.0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = 2.5;

  FT_Vector c1{64, -64};
  FT_Vector c2{-128, 256};
  FT_Vector pt{512, 0};

  const int beforeLen = path_.getLength();
  EXPECT_EQ(glyphPathCubicTo(&c1, &c2, &pt, &p), 0);
  EXPECT_EQ(path_.getLength(), beforeLen + 3);

  double x = 0, y = 0;
  unsigned char f = 0;

  GetPt(path_, beforeLen + 0, &x, &y, &f);
  EXPECT_NEAR(x, Scaled(c1.x, 2.5), 1e-9);
  EXPECT_NEAR(y, Scaled(c1.y, 2.5), 1e-9);

  GetPt(path_, beforeLen + 1, &x, &y, &f);
  EXPECT_NEAR(x, Scaled(c2.x, 2.5), 1e-9);
  EXPECT_NEAR(y, Scaled(c2.y, 2.5), 1e-9);

  GetPt(path_, beforeLen + 2, &x, &y, &f);
  EXPECT_NEAR(x, Scaled(pt.x, 2.5), 1e-9);
  EXPECT_NEAR(y, Scaled(pt.y, 2.5), 1e-9);
}

TEST_F(GlyphPathCubicToTest_2610, ZeroScaleProducesZeroDeltaPoints_2610) {
  ASSERT_EQ(path_.moveTo(123.0, 456.0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = 0.0;

  FT_Vector c1{64, 128};
  FT_Vector c2{192, 256};
  FT_Vector pt{320, 384};

  const int beforeLen = path_.getLength();
  EXPECT_EQ(glyphPathCubicTo(&c1, &c2, &pt, &p), 0);
  EXPECT_EQ(path_.getLength(), beforeLen + 3);

  double x = 1, y = 1;
  unsigned char f = 0;

  GetPt(path_, beforeLen + 0, &x, &y, &f);
  EXPECT_NEAR(x, 0.0, 1e-12);
  EXPECT_NEAR(y, 0.0, 1e-12);

  GetPt(path_, beforeLen + 1, &x, &y, &f);
  EXPECT_NEAR(x, 0.0, 1e-12);
  EXPECT_NEAR(y, 0.0, 1e-12);

  GetPt(path_, beforeLen + 2, &x, &y, &f);
  EXPECT_NEAR(x, 0.0, 1e-12);
  EXPECT_NEAR(y, 0.0, 1e-12);
}

TEST_F(GlyphPathCubicToTest_2610, NegativeScaleIsApplied_2610) {
  ASSERT_EQ(path_.moveTo(0.0, 0.0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = -1.0;

  FT_Vector c1{64, 128};
  FT_Vector c2{-64, -128};
  FT_Vector pt{32, -32};

  const int beforeLen = path_.getLength();
  EXPECT_EQ(glyphPathCubicTo(&c1, &c2, &pt, &p), 0);
  EXPECT_EQ(path_.getLength(), beforeLen + 3);

  double x = 0, y = 0;
  unsigned char f = 0;

  GetPt(path_, beforeLen + 0, &x, &y, &f);
  EXPECT_NEAR(x, -1.0, 1e-9);
  EXPECT_NEAR(y, -2.0, 1e-9);

  GetPt(path_, beforeLen + 1, &x, &y, &f);
  EXPECT_NEAR(x, 1.0, 1e-9);
  EXPECT_NEAR(y, 2.0, 1e-9);

  GetPt(path_, beforeLen + 2, &x, &y, &f);
  EXPECT_NEAR(x, -0.5, 1e-9);
  EXPECT_NEAR(y, 0.5, 1e-9);
}

TEST_F(GlyphPathCubicToTest_2610, LargeVectorValuesDoNotPreventAppending_2610) {
  ASSERT_EQ(path_.moveTo(0.0, 0.0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = 1.0;

  // Use large (but reasonable) FT_Pos values to exercise scaling.
  FT_Vector c1{1L << 20, -(1L << 20)};
  FT_Vector c2{(1L << 21), (1L << 19)};
  FT_Vector pt{-(1L << 22), (1L << 18)};

  const int beforeLen = path_.getLength();
  EXPECT_EQ(glyphPathCubicTo(&c1, &c2, &pt, &p), 0);
  EXPECT_EQ(path_.getLength(), beforeLen + 3);

  double x = 0, y = 0;
  unsigned char f = 0;

  GetPt(path_, beforeLen + 2, &x, &y, &f);
  EXPECT_NEAR(x, Scaled(pt.x, 1.0), 1e-6);
  EXPECT_NEAR(y, Scaled(pt.y, 1.0), 1e-6);
}

TEST_F(GlyphPathCubicToTest_2610, SetsNeedCloseWhenMemberExists_2610) {
  ASSERT_EQ(path_.moveTo(0.0, 0.0), splashOk);

  SplashFTFontPath p{};
  p.path = &path_;
  p.textScale = 1.0;

  FT_Vector c1{64, 64};
  FT_Vector c2{128, 128};
  FT_Vector pt{192, 192};

  if constexpr (has_needClose<SplashFTFontPath>::value) {
    // If the real struct has this observable flag, verify it flips to true.
    p.needClose = false;
    EXPECT_EQ(glyphPathCubicTo(&c1, &c2, &pt, &p), 0);
    EXPECT_TRUE(p.needClose);
  } else {
    // Some builds may not expose needClose in the struct; still ensure call succeeds.
    EXPECT_EQ(glyphPathCubicTo(&c1, &c2, &pt, &p), 0);
    SUCCEED();
  }
}