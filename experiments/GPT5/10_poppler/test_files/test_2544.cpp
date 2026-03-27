// File: poppler_text_span_is_fixed_width_font_test_2544.cc

#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations based on the provided interface.
extern "C" {
    typedef struct _PopplerTextSpan PopplerTextSpan;
    gboolean poppler_text_span_is_fixed_width_font(PopplerTextSpan *poppler_text_span);
}

// We re-declare the structure here only to allow test construction.
// We do NOT re-implement any logic of the function under test.
struct _PopplerTextSpan {
    int *text;
    int flags;
};

// The flag value is not defined in the snippet, so we declare it here
// to construct observable scenarios. We are not re-implementing logic,
// only controlling inputs for black-box testing.
#ifndef POPPLER_TEXT_SPAN_FIXED_WIDTH
#define POPPLER_TEXT_SPAN_FIXED_WIDTH (1 << 0)
#endif

class PopplerTextSpanIsFixedWidthFontTest_2544 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * Test normal operation:
 * When the FIXED_WIDTH flag is set, the function should return TRUE.
 */
TEST_F(PopplerTextSpanIsFixedWidthFontTest_2544,
       ReturnsTrueWhenFixedWidthFlagIsSet_2544) {
    PopplerTextSpan span{};
    span.text = nullptr;
    span.flags = POPPLER_TEXT_SPAN_FIXED_WIDTH;

    gboolean result = poppler_text_span_is_fixed_width_font(&span);

    EXPECT_TRUE(result);
}

/**
 * Test normal operation:
 * When the FIXED_WIDTH flag is not set, the function should return FALSE.
 */
TEST_F(PopplerTextSpanIsFixedWidthFontTest_2544,
       ReturnsFalseWhenFixedWidthFlagIsNotSet_2544) {
    PopplerTextSpan span{};
    span.text = nullptr;
    span.flags = 0;

    gboolean result = poppler_text_span_is_fixed_width_font(&span);

    EXPECT_FALSE(result);
}

/**
 * Boundary condition:
 * When multiple flags are set including FIXED_WIDTH,
 * the function should still return TRUE.
 */
TEST_F(PopplerTextSpanIsFixedWidthFontTest_2544,
       ReturnsTrueWhenMultipleFlagsIncludeFixedWidth_2544) {
    PopplerTextSpan span{};
    span.text = nullptr;
    span.flags = POPPLER_TEXT_SPAN_FIXED_WIDTH | (1 << 3);

    gboolean result = poppler_text_span_is_fixed_width_font(&span);

    EXPECT_TRUE(result);
}

/**
 * Boundary condition:
 * When multiple flags are set but FIXED_WIDTH is not included,
 * the function should return FALSE.
 */
TEST_F(PopplerTextSpanIsFixedWidthFontTest_2544,
       ReturnsFalseWhenMultipleFlagsExcludeFixedWidth_2544) {
    PopplerTextSpan span{};
    span.text = nullptr;
    span.flags = (1 << 2) | (1 << 4);

    gboolean result = poppler_text_span_is_fixed_width_font(&span);

    EXPECT_FALSE(result);
}

/**
 * Exceptional / error case:
 * Passing nullptr should return FALSE (as guarded by g_return_val_if_fail).
 */
TEST_F(PopplerTextSpanIsFixedWidthFontTest_2544,
       ReturnsFalseWhenSpanIsNull_2544) {
    gboolean result = poppler_text_span_is_fixed_width_font(nullptr);

    EXPECT_FALSE(result);
}