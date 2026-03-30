// poppler_text_span_is_bold_font_test_2546.cpp

#include <gtest/gtest.h>

#include <glib.h>

#include <poppler.h>
// Some build setups expose PopplerTextSpan via a more specific header.
// If your build fails with poppler.h, try including the structure element header instead.
// #include "poppler-structure-element.h"

namespace {

class PopplerTextSpanBoldFontTest_2546 : public ::testing::Test {};

static PopplerTextSpan MakeZeroedSpanWithFlags_2546(decltype(PopplerTextSpan::flags) flags_val)
{
    PopplerTextSpan span;
    // Avoid assuming any constructor/initialization behavior: just zero-fill.
    std::memset(&span, 0, sizeof(span));
    span.flags = flags_val;
    return span;
}

} // namespace

TEST_F(PopplerTextSpanBoldFontTest_2546, NullSpanReturnsFalse_2546)
{
    // Observable error behavior: g_return_val_if_fail => returns FALSE for nullptr.
    EXPECT_FALSE(poppler_text_span_is_bold_font(nullptr));
}

TEST_F(PopplerTextSpanBoldFontTest_2546, BoldFlagSetReturnsTrue_2546)
{
    auto span = MakeZeroedSpanWithFlags_2546(
        static_cast<decltype(PopplerTextSpan::flags)>(POPPLER_TEXT_SPAN_BOLD));

    EXPECT_TRUE(poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanBoldFontTest_2546, BoldFlagNotSetReturnsFalse_2546)
{
    auto span = MakeZeroedSpanWithFlags_2546(static_cast<decltype(PopplerTextSpan::flags)>(0));

    EXPECT_FALSE(poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanBoldFontTest_2546, BoldFlagWithOtherBitsSetStillReturnsTrue_2546)
{
    // Boundary-ish: ensure function checks the bold bit even if other bits are present.
    // We avoid relying on any specific other flag names; we just OR in a non-bold bit pattern.
    const auto other_bits = static_cast<decltype(PopplerTextSpan::flags)>(0x80000000u);
    auto span = MakeZeroedSpanWithFlags_2546(
        static_cast<decltype(PopplerTextSpan::flags)>(POPPLER_TEXT_SPAN_BOLD) | other_bits);

    EXPECT_TRUE(poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanBoldFontTest_2546, AllBitsSetReturnsTrue_2546)
{
    // Boundary: if all bits are set, bold bit is necessarily set.
    auto span = MakeZeroedSpanWithFlags_2546(static_cast<decltype(PopplerTextSpan::flags)>(~0u));

    EXPECT_TRUE(poppler_text_span_is_bold_font(&span));
}