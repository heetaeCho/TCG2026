// File: HtmlFonts_setRotMat_test_2625.cc

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <memory>

// Class under test
#include "TestProjects/poppler/utils/HtmlFonts.h"

// Poppler deps needed to construct HtmlFont
#include "poppler/GfxFont.h"
#include "poppler/GfxState.h"
#include "goo/GooString.h"
#include "poppler/Object.h"

// A minimal concrete GfxFont so we can instantiate HtmlFont.
// We only implement what is required by the GfxFont interface (pure virtual getNextChar),
// and provide stable backing storage for the font name string.
class DummyGfxFont_2625 final : public GfxFont {
public:
  DummyGfxFont_2625()
      : GfxFont(
            "F1",                // tag
            Ref{1, 0},           // id
            &(nameStorage_),     // name (must outlive GfxFont)
            fontType1,           // type
            Ref{0, 0}            // embFontID
        ),
        nameStorage_("DummyFont") {}

  int getNextChar(const char * /*s*/,
                  int /*len*/,
                  CharCode *code,
                  Unicode const **u,
                  int *uLen,
                  double *dx,
                  double *dy,
                  double *ox,
                  double *oy) const override
  {
    // Minimal, deterministic outputs. HtmlFont construction should not depend
    // on real text extraction here for these tests.
    if (code) {
      *code = 0;
    }
    if (u) {
      *u = nullptr;
    }
    if (uLen) {
      *uLen = 0;
    }
    if (dx) {
      *dx = 0.0;
    }
    if (dy) {
      *dy = 0.0;
    }
    if (ox) {
      *ox = 0.0;
    }
    if (oy) {
      *oy = 0.0;
    }
    return 0;
  }

private:
  GooString nameStorage_;
};

class HtmlFontTest_2625 : public ::testing::Test {
protected:
  static HtmlFont MakeFont_2625(const GfxFont &gfxFont)
  {
    GfxRGB rgb;
    rgb.r = 0.0;
    rgb.g = 0.0;
    rgb.b = 0.0;

    // Size/opacity values are not the target of these tests; they just allow construction.
    return HtmlFont(gfxFont, /*_size=*/12, rgb, /*opacity=*/1.0);
  }
};

TEST_F(HtmlFontTest_2625, SetRotMatSetsRotOrSkewedTrue_2625)
{
  DummyGfxFont_2625 gfxFont;
  HtmlFont font = MakeFont_2625(gfxFont);

  font.setRotMat(std::array<double, 4>{1.0, 0.0, 0.0, 1.0});

  EXPECT_TRUE(font.isRotOrSkewed());
}

TEST_F(HtmlFontTest_2625, SetRotMatStoresMatrixAndGetRotMatReturnsSameValues_2625)
{
  DummyGfxFont_2625 gfxFont;
  HtmlFont font = MakeFont_2625(gfxFont);

  const std::array<double, 4> mat{0.866025403784, -0.5, 0.5, 0.866025403784};
  font.setRotMat(mat);

  const std::array<double, 4> &out = font.getRotMat();
  EXPECT_DOUBLE_EQ(out[0], mat[0]);
  EXPECT_DOUBLE_EQ(out[1], mat[1]);
  EXPECT_DOUBLE_EQ(out[2], mat[2]);
  EXPECT_DOUBLE_EQ(out[3], mat[3]);
}

TEST_F(HtmlFontTest_2625, SetRotMatCanBeCalledMultipleTimesLastCallWins_2625)
{
  DummyGfxFont_2625 gfxFont;
  HtmlFont font = MakeFont_2625(gfxFont);

  const std::array<double, 4> mat1{1.0, 2.0, 3.0, 4.0};
  const std::array<double, 4> mat2{4.0, 3.0, 2.0, 1.0};

  font.setRotMat(mat1);
  font.setRotMat(mat2);

  const auto &out = font.getRotMat();
  EXPECT_DOUBLE_EQ(out[0], mat2[0]);
  EXPECT_DOUBLE_EQ(out[1], mat2[1]);
  EXPECT_DOUBLE_EQ(out[2], mat2[2]);
  EXPECT_DOUBLE_EQ(out[3], mat2[3]);
  EXPECT_TRUE(font.isRotOrSkewed());
}

TEST_F(HtmlFontTest_2625, SetRotMatAcceptsZeroMatrix_Boundary_2625)
{
  DummyGfxFont_2625 gfxFont;
  HtmlFont font = MakeFont_2625(gfxFont);

  const std::array<double, 4> zero{0.0, 0.0, 0.0, 0.0};
  font.setRotMat(zero);

  const auto &out = font.getRotMat();
  EXPECT_DOUBLE_EQ(out[0], 0.0);
  EXPECT_DOUBLE_EQ(out[1], 0.0);
  EXPECT_DOUBLE_EQ(out[2], 0.0);
  EXPECT_DOUBLE_EQ(out[3], 0.0);
  EXPECT_TRUE(font.isRotOrSkewed());
}

TEST_F(HtmlFontTest_2625, SetRotMatPreservesNaNValues_Boundary_2625)
{
  DummyGfxFont_2625 gfxFont;
  HtmlFont font = MakeFont_2625(gfxFont);

  const double nan = std::numeric_limits<double>::quiet_NaN();
  const std::array<double, 4> mat{nan, 1.0, nan, 2.0};

  font.setRotMat(mat);

  const auto &out = font.getRotMat();
  EXPECT_TRUE(std::isnan(out[0]));
  EXPECT_DOUBLE_EQ(out[1], 1.0);
  EXPECT_TRUE(std::isnan(out[2]));
  EXPECT_DOUBLE_EQ(out[3], 2.0);
  EXPECT_TRUE(font.isRotOrSkewed());
}