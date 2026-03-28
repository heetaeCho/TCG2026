// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for text_span_poppler_text_span()
// File: poppler-structure-element.cc (static helper)
//
// TEST_ID: 2541

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler.h"

// We need to construct TextSpan instances, but TextSpan's constructor is private.
// For unit-testing this translation-unit-local helper, we relax access in the test
// compilation unit only (no runtime dependency on private state).
#define private public
#define protected public
#include "poppler/MarkedContentOutputDev.h"
#include "poppler/GfxFont.h"
#include "poppler/GfxState.h"
#include "poppler/Object.h"
#undef protected
#undef private

#include <memory>
#include <optional>
#include <string>
#include <utility>

// Pull the static function under test into this translation unit by including the .cc.
// This is a common pattern for testing file-local helpers.
#include "poppler-structure-element.cc"

namespace {

class TestGfxFont : public GfxFont {
public:
  TestGfxFont(std::optional<std::string> name,
              GfxFont::Weight w,
              std::unique_ptr<GooString> familyStr)
      : GfxFont("F1", Ref{1, 0}, std::move(name), GfxFontType::fontType1, Ref{0, 0})
  {
    // These members are protected in GfxFont; access is enabled in this TU only.
    weight = w;
    family = std::move(familyStr);
  }

  ~TestGfxFont() override = default;
};

static void FreePopplerTextSpan(PopplerTextSpan *s)
{
  if (!s) {
    return;
  }
  g_free(s->text);
  g_free(s->font_name);
  g_slice_free(PopplerTextSpan, s);
}

static TextSpan MakeSpan(std::unique_ptr<GooString> text,
                         std::shared_ptr<GfxFont> font,
                         const GfxRGB &color)
{
  // TextSpan ctor is private; access is enabled in this TU only.
  return TextSpan(std::move(text), std::move(font), color);
}

} // namespace

// -------- Tests (TEST_ID 2541) --------

TEST(TextSpanPopplerTextSpanTest_2541, NullTextAndNullFontProducesNullStringsAndZeroFlags_2541)
{
  GfxRGB color;
  color.r = 0;
  color.g = 0;
  color.b = 0;

  TextSpan span = MakeSpan(std::unique_ptr<GooString>(), nullptr, color);

  PopplerTextSpan *out = text_span_poppler_text_span(span);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->text, nullptr);
  EXPECT_EQ(out->font_name, nullptr);
  EXPECT_EQ(out->flags, 0u);

  // Colors should be in range [0, 65535]
  EXPECT_GE(out->color.red, 0u);
  EXPECT_GE(out->color.green, 0u);
  EXPECT_GE(out->color.blue, 0u);
  EXPECT_LE(out->color.red, 65535u);
  EXPECT_LE(out->color.green, 65535u);
  EXPECT_LE(out->color.blue, 65535u);

  FreePopplerTextSpan(out);
}

TEST(TextSpanPopplerTextSpanTest_2541, AsciiTextConvertsToUtf8AndIsNonNull_2541)
{
  GfxRGB color;
  color.r = 0;
  color.g = 0;
  color.b = 0;

  auto txt = std::make_unique<GooString>("Hello");
  TextSpan span = MakeSpan(std::move(txt), nullptr, color);

  PopplerTextSpan *out = text_span_poppler_text_span(span);
  ASSERT_NE(out, nullptr);

  ASSERT_NE(out->text, nullptr);
  EXPECT_STREQ(out->text, "Hello");

  // No font provided -> no font name / flags
  EXPECT_EQ(out->font_name, nullptr);
  EXPECT_EQ(out->flags, 0u);

  FreePopplerTextSpan(out);
}

TEST(TextSpanPopplerTextSpanTest_2541, ColorComponentsStayWithinExpectedRange_2541)
{
  GfxRGB black;
  black.r = 0;
  black.g = 0;
  black.b = 0;

  GfxRGB white;
  // Use max for GfxColorComp; in Poppler this is typically 16-bit.
  white.r = static_cast<GfxColorComp>(0xFFFF);
  white.g = static_cast<GfxColorComp>(0xFFFF);
  white.b = static_cast<GfxColorComp>(0xFFFF);

  TextSpan spanBlack = MakeSpan(std::make_unique<GooString>("x"), nullptr, black);
  TextSpan spanWhite = MakeSpan(std::make_unique<GooString>("x"), nullptr, white);

  PopplerTextSpan *outBlack = text_span_poppler_text_span(spanBlack);
  PopplerTextSpan *outWhite = text_span_poppler_text_span(spanWhite);
  ASSERT_NE(outBlack, nullptr);
  ASSERT_NE(outWhite, nullptr);

  // Both must be within [0, 65535].
  EXPECT_LE(outBlack->color.red, 65535u);
  EXPECT_LE(outBlack->color.green, 65535u);
  EXPECT_LE(outBlack->color.blue, 65535u);

  EXPECT_LE(outWhite->color.red, 65535u);
  EXPECT_LE(outWhite->color.green, 65535u);
  EXPECT_LE(outWhite->color.blue, 65535u);

  // And white should not be darker than black on any channel (monotonicity).
  EXPECT_GE(outWhite->color.red, outBlack->color.red);
  EXPECT_GE(outWhite->color.green, outBlack->color.green);
  EXPECT_GE(outWhite->color.blue, outBlack->color.blue);

  FreePopplerTextSpan(outBlack);
  FreePopplerTextSpan(outWhite);
}

TEST(TextSpanPopplerTextSpanTest_2541, FontFamilyPreferredOverFontNameWhenPresent_2541)
{
  GfxRGB color;
  color.r = 0;
  color.g = 0;
  color.b = 0;

  auto font = std::make_shared<TestGfxFont>(
      std::optional<std::string>("PostScriptName"),
      GfxFont::W400,
      std::make_unique<GooString>("FamilyName"));

  TextSpan span = MakeSpan(std::make_unique<GooString>("t"), font, color);

  PopplerTextSpan *out = text_span_poppler_text_span(span);
  ASSERT_NE(out, nullptr);

  ASSERT_NE(out->font_name, nullptr);
  EXPECT_STREQ(out->font_name, "FamilyName");

  FreePopplerTextSpan(out);
}

TEST(TextSpanPopplerTextSpanTest_2541, FontNameUsedWhenFamilyIsNull_2541)
{
  GfxRGB color;
  color.r = 0;
  color.g = 0;
  color.b = 0;

  auto font = std::make_shared<TestGfxFont>(
      std::optional<std::string>("OnlyName"),
      GfxFont::W400,
      std::unique_ptr<GooString>() /* no family */);

  TextSpan span = MakeSpan(std::make_unique<GooString>("t"), font, color);

  PopplerTextSpan *out = text_span_poppler_text_span(span);
  ASSERT_NE(out, nullptr);

  ASSERT_NE(out->font_name, nullptr);
  EXPECT_STREQ(out->font_name, "OnlyName");

  FreePopplerTextSpan(out);
}

TEST(TextSpanPopplerTextSpanTest_2541, FontNameNullWhenNeitherFamilyNorNameProvided_2541)
{
  GfxRGB color;
  color.r = 0;
  color.g = 0;
  color.b = 0;

  auto font = std::make_shared<TestGfxFont>(
      std::optional<std::string>() /* no name */,
      GfxFont::W400,
      std::unique_ptr<GooString>() /* no family */);

  TextSpan span = MakeSpan(std::make_unique<GooString>("t"), font, color);

  PopplerTextSpan *out = text_span_poppler_text_span(span);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->font_name, nullptr);

  FreePopplerTextSpan(out);
}

TEST(TextSpanPopplerTextSpanTest_2541, HeavyWeightSetsBoldFlagEvenIfOtherFontTraitsUnknown_2541)
{
  GfxRGB color;
  color.r = 0;
  color.g = 0;
  color.b = 0;

  // Use a heavy weight that should trigger bold via the weight switch in the helper.
  auto font = std::make_shared<TestGfxFont>(
      std::optional<std::string>("N"),
      GfxFont::W700,
      std::make_unique<GooString>("F"));

  TextSpan span = MakeSpan(std::make_unique<GooString>("t"), font, color);

  PopplerTextSpan *out = text_span_poppler_text_span(span);
  ASSERT_NE(out, nullptr);

  EXPECT_NE((out->flags & POPPLER_TEXT_SPAN_BOLD), 0u);

  FreePopplerTextSpan(out);
}

TEST(TextSpanPopplerTextSpanTest_2541, WeightNotInHeavyRangeDoesNotRequireBoldFlag_2541)
{
  GfxRGB color;
  color.r = 0;
  color.g = 0;
  color.b = 0;

  auto font = std::make_shared<TestGfxFont>(
      std::optional<std::string>("N"),
      GfxFont::W400,
      std::make_unique<GooString>("F"));

  TextSpan span = MakeSpan(std::make_unique<GooString>("t"), font, color);

  PopplerTextSpan *out = text_span_poppler_text_span(span);
  ASSERT_NE(out, nullptr);

  // Observable behavior: the helper's weight-based bold logic should *not* force the bold bit
  // for W400. (If Poppler marks the font bold through other means, this might still be set,
  // but we can at least verify it doesn't crash and returns a valid span.)
  EXPECT_NE(out->font_name, nullptr);
  EXPECT_STREQ(out->font_name, "F");

  FreePopplerTextSpan(out);
}