// File: HtmlFontColor_test_2617.cpp

#include <gtest/gtest.h>

#include "HtmlFonts.h"

// Poppler type used by HtmlFontColor(GfxRGB, double).
// In Poppler this is typically declared in GfxState.h.
#include "GfxState.h"

namespace {

static GfxRGB MakeRgb(double r, double g, double b)
{
  GfxRGB rgb;
  rgb.r = r;
  rgb.g = g;
  rgb.b = b;
  return rgb;
}

class HtmlFontColorTest_2617 : public ::testing::Test {
protected:
  // No shared state needed.
};

TEST_F(HtmlFontColorTest_2617, DefaultInstancesAreEqual_2617)
{
  HtmlFontColor a;
  HtmlFontColor b;

  EXPECT_TRUE(a.isEqual(b));
  EXPECT_TRUE(b.isEqual(a));
}

TEST_F(HtmlFontColorTest_2617, ReflexivePropertyHolds_2617)
{
  HtmlFontColor a;
  EXPECT_TRUE(a.isEqual(a));

  HtmlFontColor b(MakeRgb(0.0, 0.0, 0.0), 1.0);
  EXPECT_TRUE(b.isEqual(b));
}

TEST_F(HtmlFontColorTest_2617, SameConstructionParametersAreEqual_2617)
{
  const GfxRGB rgb = MakeRgb(1.0, 0.0, 0.5);
  HtmlFontColor a(rgb, 1.0);
  HtmlFontColor b(rgb, 1.0);

  EXPECT_TRUE(a.isEqual(b));
  EXPECT_TRUE(b.isEqual(a));
}

TEST_F(HtmlFontColorTest_2617, DifferentRgbComponentMakesNotEqual_2617)
{
  HtmlFontColor a(MakeRgb(0.0, 0.0, 0.0), 1.0);
  HtmlFontColor b(MakeRgb(1.0, 0.0, 0.0), 1.0);

  EXPECT_FALSE(a.isEqual(b));
  EXPECT_FALSE(b.isEqual(a));
}

TEST_F(HtmlFontColorTest_2617, DifferentOpacityMakesNotEqual_2617)
{
  const GfxRGB rgb = MakeRgb(0.2, 0.4, 0.6);
  HtmlFontColor a(rgb, 0.0);
  HtmlFontColor b(rgb, 1.0);

  EXPECT_FALSE(a.isEqual(b));
  EXPECT_FALSE(b.isEqual(a));
}

TEST_F(HtmlFontColorTest_2617, DefaultAndNonDefaultAreNotEqual_2617)
{
  HtmlFontColor def;
  HtmlFontColor other(MakeRgb(1.0, 1.0, 1.0), 1.0);

  EXPECT_FALSE(def.isEqual(other));
  EXPECT_FALSE(other.isEqual(def));
}

TEST_F(HtmlFontColorTest_2617, ChainComparisonBehavesAsExpected_2617)
{
  const GfxRGB rgbA = MakeRgb(0.0, 1.0, 0.0);
  const GfxRGB rgbB = MakeRgb(0.0, 0.0, 1.0);

  HtmlFontColor a1(rgbA, 1.0);
  HtmlFontColor a2(rgbA, 1.0);
  HtmlFontColor b(rgbB, 1.0);

  EXPECT_TRUE(a1.isEqual(a2));
  EXPECT_FALSE(a1.isEqual(b));
  EXPECT_FALSE(a2.isEqual(b));
}

} // namespace