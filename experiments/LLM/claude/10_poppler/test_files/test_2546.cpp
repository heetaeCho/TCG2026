#include <glib.h>
#include <gtest/gtest.h>

// Reproduce the necessary structures and declarations from the source
// Based on the interface provided

// From the poppler-structure-element header/source
enum PopplerTextSpanFlags {
    POPPLER_TEXT_SPAN_BOLD = (1 << 0),
    POPPLER_TEXT_SPAN_FIXED_WIDTH = (1 << 1),
    POPPLER_TEXT_SPAN_SERIF_FONT = (1 << 2),
    POPPLER_TEXT_SPAN_ITALIC = (1 << 3),
};

struct PopplerTextSpan {
    gchar *text;
    guint flags;
    // Additional fields may exist but are not relevant for these tests
    gchar *font_name;
    guint link_target;
    PopplerColor color;
};

// Declaration of the function under test
extern "C" {
    gboolean poppler_text_span_is_bold_font(PopplerTextSpan *poppler_text_span);
}

class PopplerTextSpanIsBoldFontTest_2546 : public ::testing::Test {
protected:
    PopplerTextSpan span;

    void SetUp() override {
        memset(&span, 0, sizeof(span));
    }
};

TEST_F(PopplerTextSpanIsBoldFontTest_2546, ReturnsTrueWhenBoldFlagSet_2546) {
    span.flags = POPPLER_TEXT_SPAN_BOLD;
    EXPECT_TRUE(poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanIsBoldFontTest_2546, ReturnsFalseWhenBoldFlagNotSet_2546) {
    span.flags = 0;
    EXPECT_FALSE(poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanIsBoldFontTest_2546, ReturnsFalseWhenOnlyOtherFlagsSet_2546) {
    span.flags = POPPLER_TEXT_SPAN_FIXED_WIDTH | POPPLER_TEXT_SPAN_SERIF_FONT | POPPLER_TEXT_SPAN_ITALIC;
    EXPECT_FALSE(poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanIsBoldFontTest_2546, ReturnsTrueWhenBoldAndOtherFlagsSet_2546) {
    span.flags = POPPLER_TEXT_SPAN_BOLD | POPPLER_TEXT_SPAN_ITALIC | POPPLER_TEXT_SPAN_SERIF_FONT;
    EXPECT_TRUE(poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanIsBoldFontTest_2546, ReturnsTrueWhenAllFlagsSet_2546) {
    span.flags = POPPLER_TEXT_SPAN_BOLD | POPPLER_TEXT_SPAN_FIXED_WIDTH | POPPLER_TEXT_SPAN_SERIF_FONT | POPPLER_TEXT_SPAN_ITALIC;
    EXPECT_TRUE(poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanIsBoldFontTest_2546, ReturnsFalseForNullPointer_2546) {
    // g_return_val_if_fail should return FALSE for nullptr
    // Note: This will produce a GLib warning message, which is expected behavior
    gboolean result = poppler_text_span_is_bold_font(nullptr);
    EXPECT_FALSE(result);
}

TEST_F(PopplerTextSpanIsBoldFontTest_2546, ReturnsFalseWhenFlagsAreZero_2546) {
    span.flags = 0;
    EXPECT_EQ(FALSE, poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanIsBoldFontTest_2546, ReturnsTrueWhenOnlyBoldFlagExact_2546) {
    span.flags = 1; // POPPLER_TEXT_SPAN_BOLD is (1 << 0) = 1
    EXPECT_TRUE(poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanIsBoldFontTest_2546, ReturnsFalseWhenHighBitsSetButNotBold_2546) {
    span.flags = 0xFFFFFFFE; // All bits set except bit 0 (BOLD)
    EXPECT_FALSE(poppler_text_span_is_bold_font(&span));
}

TEST_F(PopplerTextSpanIsBoldFontTest_2546, ReturnsTrueWhenAllBitsSet_2546) {
    span.flags = 0xFFFFFFFF; // All bits set including BOLD
    EXPECT_TRUE(poppler_text_span_is_bold_font(&span));
}
