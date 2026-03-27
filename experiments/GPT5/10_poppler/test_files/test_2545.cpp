// poppler_text_span_is_serif_font_test_2545.cc
#include <gtest/gtest.h>

extern "C" {
#include <glib.h>
#include <poppler.h>

// The function under test (implemented in poppler-structure-element.cc)
gboolean poppler_text_span_is_serif_font(PopplerTextSpan *poppler_text_span);
}

class PopplerTextSpanSerifFontTest_2545 : public ::testing::Test {};

TEST_F(PopplerTextSpanSerifFontTest_2545, NullSpanReturnsFalse_2545) {
  // g_return_val_if_fail() should cause a FALSE return for nullptr.
  EXPECT_FALSE(poppler_text_span_is_serif_font(nullptr));
}

TEST_F(PopplerTextSpanSerifFontTest_2545, FlagsZeroReturnsFalse_2545) {
  PopplerTextSpan span{};
  span.flags = static_cast<PopplerTextSpanFlags>(0);

  EXPECT_FALSE(poppler_text_span_is_serif_font(&span));
}

TEST_F(PopplerTextSpanSerifFontTest_2545, SerifFlagSetReturnsTrue_2545) {
  PopplerTextSpan span{};
  span.flags = POPPLER_TEXT_SPAN_SERIF;

  EXPECT_TRUE(poppler_text_span_is_serif_font(&span));
}

TEST_F(PopplerTextSpanSerifFontTest_2545, NonSerifOtherFlagsReturnFalse_2545) {
  PopplerTextSpan span{};
  // Use any other known flag if available; otherwise, synthesize a non-SERIF bit
  // while keeping it disjoint from POPPLER_TEXT_SPAN_SERIF.
  const auto serif_bit = static_cast<guint>(POPPLER_TEXT_SPAN_SERIF);
  const auto other_bit = static_cast<PopplerTextSpanFlags>(serif_bit ? (serif_bit << 1) : 0x2u);
  span.flags = other_bit;

  EXPECT_FALSE(poppler_text_span_is_serif_font(&span));
}

TEST_F(PopplerTextSpanSerifFontTest_2545, SerifCombinedWithOtherBitsReturnsTrue_2545) {
  PopplerTextSpan span{};
  const auto serif_bit = static_cast<guint>(POPPLER_TEXT_SPAN_SERIF);
  const auto other_bit = static_cast<guint>(serif_bit ? (serif_bit << 1) : 0x2u);

  span.flags = static_cast<PopplerTextSpanFlags>(serif_bit | other_bit);

  EXPECT_TRUE(poppler_text_span_is_serif_font(&span));
}

TEST_F(PopplerTextSpanSerifFontTest_2545, DoesNotModifyFlags_2545) {
  PopplerTextSpan span{};
  const auto initial = static_cast<PopplerTextSpanFlags>(POPPLER_TEXT_SPAN_SERIF);
  span.flags = initial;

  (void)poppler_text_span_is_serif_font(&span);

  EXPECT_EQ(span.flags, initial);
}