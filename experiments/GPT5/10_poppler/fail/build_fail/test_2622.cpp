// HtmlFont_getSize_test_2622.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Prefer the project header first.
#include "TestProjects/poppler/utils/HtmlFonts.h"

// Try to include Poppler types used by HtmlFont's constructor (if available).
#if __has_include("GfxState.h")
#include "GfxState.h" // GfxRGB
#endif
#if __has_include("GfxFont.h")
#include "GfxFont.h" // GfxFont
#endif

namespace {

class HtmlFontTest_2622 : public ::testing::Test {};

// ---------- Always-on: signature/const/return-type checks (no instantiation required) ----------

TEST_F(HtmlFontTest_2622, GetSize_IsConstAndReturnsInt_2622) {
  // Verify the expression is well-formed and returns int (or something implicitly convertible to int).
  static_assert(std::is_same_v<decltype(std::declval<const HtmlFont&>().getSize()), int>,
                "HtmlFont::getSize() must return int");
}

TEST_F(HtmlFontTest_2622, GetSize_IsNotCallableOnNonObject_2622) {
  // Sanity: getSize is a member function; ensure it's invocable on a const HtmlFont instance.
  static_assert(std::is_invocable_r_v<int, decltype(&HtmlFont::getSize), const HtmlFont*>,
                "HtmlFont::getSize must be invocable on const HtmlFont* and return int");
}

// ---------- Runtime checks (only if we can actually construct HtmlFont in this build) ----------
// These tests exercise observable behavior: getSize() matches the size passed to the constructor.
// If your build environment provides the full Poppler types and constructor, these should compile/run.

#if defined(GfxFont) || __has_include("GfxFont.h")
#if defined(GfxRGB) || __has_include("GfxState.h")

// Helper to make an RGB value in a way that's compatible across Poppler versions/builds.
static GfxRGB MakeRgb_2622(double r, double g, double b) {
  GfxRGB rgb{};
#if defined(gfxColorComp)
  // Some builds use gfxColorComp; others use plain doubles. Assigning doubles is generally OK.
#endif
  rgb.r = r;
  rgb.g = g;
  rgb.b = b;
  return rgb;
}

TEST_F(HtmlFontTest_2622, GetSize_ReturnsCtorProvidedSize_Normal_2622) {
  // Assumption for the test harness: a default-constructible concrete GfxFont is available.
  // If your build requires a different way to obtain a GfxFont, replace this with your factory.
  GfxFont font;

  const int kSize = 12;
  const GfxRGB rgb = MakeRgb_2622(0.0, 0.0, 0.0);
  const double kOpacity = 1.0;

  HtmlFont hf(font, kSize, rgb, kOpacity);
  EXPECT_EQ(hf.getSize(), kSize);
}

TEST_F(HtmlFontTest_2622, GetSize_Boundary_ZeroSize_2622) {
  GfxFont font;

  const int kSize = 0;
  const GfxRGB rgb = MakeRgb_2622(1.0, 1.0, 1.0);
  const double kOpacity = 0.0;

  HtmlFont hf(font, kSize, rgb, kOpacity);
  EXPECT_EQ(hf.getSize(), kSize);
}

TEST_F(HtmlFontTest_2622, GetSize_Boundary_NegativeSize_2622) {
  GfxFont font;

  const int kSize = -1;
  const GfxRGB rgb = MakeRgb_2622(0.25, 0.5, 0.75);
  const double kOpacity = 0.5;

  HtmlFont hf(font, kSize, rgb, kOpacity);
  EXPECT_EQ(hf.getSize(), kSize);
}

TEST_F(HtmlFontTest_2622, GetSize_Boundary_LargeSize_2622) {
  GfxFont font;

  const int kSize = 1000000;
  const GfxRGB rgb = MakeRgb_2622(0.0, 0.0, 0.0);
  const double kOpacity = 1.0;

  HtmlFont hf(font, kSize, rgb, kOpacity);
  EXPECT_EQ(hf.getSize(), kSize);
}

TEST_F(HtmlFontTest_2622, GetSize_DoesNotChangeAcrossMultipleCalls_2622) {
  GfxFont font;

  const int kSize = 42;
  const GfxRGB rgb = MakeRgb_2622(0.1, 0.2, 0.3);
  const double kOpacity = 0.9;

  HtmlFont hf(font, kSize, rgb, kOpacity);

  const int first = hf.getSize();
  const int second = hf.getSize();
  const int third = hf.getSize();

  EXPECT_EQ(first, kSize);
  EXPECT_EQ(second, kSize);
  EXPECT_EQ(third, kSize);
}

#endif  // GfxRGB available
#endif  // GfxFont available

}  // namespace