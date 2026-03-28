// File: HtmlFonts_isRotOrSkewed_test_2621.cc

#include <gtest/gtest.h>

#include <cstring>
#include <optional>
#include <string>

#include "HtmlFonts.h"

// Poppler core headers for GfxFont/GfxRGB dependencies.
#include "GfxFont.h"
#include "GfxState.h"
#include "CharCodeToUnicode.h"

// A minimal concrete GfxFont implementation to satisfy HtmlFont's constructor dependency.
// This is a test-only stub used only to provide a valid GfxFont reference.
class DummyGfxFont_2621 final : public GfxFont {
public:
  DummyGfxFont_2621()
      : GfxFont("F1", Ref::INVALID(), std::optional<std::string>(std::string("DummyFont")),
                // Use a commonly available font type value.
                fontType1, Ref::INVALID()) {
    // Ensure commonly-used fields queried by HtmlFont are in a safe state.
    flags = 0;
    weight = WeightNotDefined;
    stretch = StretchNotDefined;
  }

  const CharCodeToUnicode *getToUnicode() const override { return nullptr; }

  int getNextChar(const char * /*s*/, int /*len*/, CharCode *code, Unicode const **u, int *uLen,
                  double *dx, double *dy, double *ox, double *oy) const override {
    if (code) *code = 0;
    static const Unicode kEmptyUnicode[1] = {0};
    if (u) *u = kEmptyUnicode;
    if (uLen) *uLen = 0;
    if (dx) *dx = 0.0;
    if (dy) *dy = 0.0;
    if (ox) *ox = 0.0;
    if (oy) *oy = 0.0;
    return 0;
  }
};

class HtmlFontTest_2621 : public ::testing::Test {
protected:
  static GfxRGB MakeRgb_2621(double r, double g, double b) {
    GfxRGB rgb;
    rgb.r = dblToCol(r);
    rgb.g = dblToCol(g);
    rgb.b = dblToCol(b);
    return rgb;
  }
};

TEST_F(HtmlFontTest_2621, IsRotOrSkewed_IsStableAcrossRepeatedCalls_2621) {
  DummyGfxFont_2621 gfxFont;
  HtmlFont font(gfxFont, /*_size=*/12, MakeRgb_2621(0.1, 0.2, 0.3), /*opacity=*/1.0);

  const bool first = font.isRotOrSkewed();
  const bool second = font.isRotOrSkewed();
  const bool third = font.isRotOrSkewed();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(HtmlFontTest_2621, IsRotOrSkewed_DefaultIsFalseAfterConstruction_2621) {
  DummyGfxFont_2621 gfxFont;
  HtmlFont font(gfxFont, /*_size=*/10, MakeRgb_2621(0.0, 0.0, 0.0), /*opacity=*/1.0);

  // Observable post-condition: a freshly constructed HtmlFont should not be rotated/skewed.
  EXPECT_FALSE(font.isRotOrSkewed());
}

TEST_F(HtmlFontTest_2621, IsRotOrSkewed_BecomesTrueAfterSetRotMat_2621) {
  DummyGfxFont_2621 gfxFont;
  HtmlFont font(gfxFont, /*_size=*/11, MakeRgb_2621(0.4, 0.5, 0.6), /*opacity=*/0.75);

  EXPECT_FALSE(font.isRotOrSkewed());

  // Apply an arbitrary rotation/skew matrix (4 values as exposed by the public API).
  // The exact semantics of the matrix are not asserted beyond the observable flag change.
#if defined(POPPLER_HAS_HTMLFONT_STD_ARRAY_ROT_MAT)  // (optional project define, if present)
  const std::array<double, 4> mat = {1.0, 0.0, 0.2, 1.0};
  font.setRotMat(mat);
#else
  // Common Poppler html code uses a pointer to 4 doubles.
  const double mat[4] = {1.0, 0.0, 0.2, 1.0};
  font.setRotMat(mat);
#endif

  EXPECT_TRUE(font.isRotOrSkewed());
}

TEST_F(HtmlFontTest_2621, IsRotOrSkewed_CopyConstructorPreservesState_2621) {
  DummyGfxFont_2621 gfxFont;
  HtmlFont original(gfxFont, /*_size=*/9, MakeRgb_2621(0.2, 0.2, 0.2), /*opacity=*/1.0);

#if defined(POPPLER_HAS_HTMLFONT_STD_ARRAY_ROT_MAT)
  const std::array<double, 4> mat = {0.9, 0.1, 0.0, 1.1};
  original.setRotMat(mat);
#else
  const double mat[4] = {0.9, 0.1, 0.0, 1.1};
  original.setRotMat(mat);
#endif
  ASSERT_TRUE(original.isRotOrSkewed());

  HtmlFont copy(original);
  EXPECT_EQ(copy.isRotOrSkewed(), original.isRotOrSkewed());
}

TEST_F(HtmlFontTest_2621, IsRotOrSkewed_AssignmentPreservesState_2621) {
  DummyGfxFont_2621 gfxFont;
  HtmlFont src(gfxFont, /*_size=*/14, MakeRgb_2621(0.8, 0.1, 0.1), /*opacity=*/0.5);
  HtmlFont dst(gfxFont, /*_size=*/14, MakeRgb_2621(0.1, 0.8, 0.1), /*opacity=*/0.5);

  EXPECT_FALSE(src.isRotOrSkewed());
  EXPECT_FALSE(dst.isRotOrSkewed());

#if defined(POPPLER_HAS_HTMLFONT_STD_ARRAY_ROT_MAT)
  const std::array<double, 4> mat = {1.0, -0.3, 0.0, 1.0};
  src.setRotMat(mat);
#else
  const double mat[4] = {1.0, -0.3, 0.0, 1.0};
  src.setRotMat(mat);
#endif
  ASSERT_TRUE(src.isRotOrSkewed());

  dst = src;
  EXPECT_EQ(dst.isRotOrSkewed(), src.isRotOrSkewed());
}