#include <glib.h>
#include <gtest/gtest.h>

// Replicate the necessary structures and declarations from the source
// Based on the known interface

// Flag constant - inferred from usage in the function
#define POPPLER_TEXT_SPAN_FIXED_WIDTH (1 << 0)

// Structure definition based on what we can infer from the code
typedef struct _PopplerTextSpan {
    char *text;
    guint flags;
    // Other fields may exist but are not relevant for this test
} PopplerTextSpan;

// Declaration of the function under test
extern "C" {
gboolean poppler_text_span_is_fixed_width_font(PopplerTextSpan *poppler_text_span);
}

class PopplerTextSpanTest_2544 : public ::testing::Test {
protected:
    PopplerTextSpan *span;

    void SetUp() override
    {
        span = g_new0(PopplerTextSpan, 1);
        span->text = nullptr;
        span->flags = 0;
    }

    void TearDown() override
    {
        if (span) {
            g_free(span);
            span = nullptr;
        }
    }
};

// Test that a span with the fixed width flag set returns TRUE
TEST_F(PopplerTextSpanTest_2544, ReturnsTrue_WhenFixedWidthFlagSet_2544)
{
    span->flags = POPPLER_TEXT_SPAN_FIXED_WIDTH;
    EXPECT_TRUE(poppler_text_span_is_fixed_width_font(span));
}

// Test that a span without the fixed width flag returns FALSE
TEST_F(PopplerTextSpanTest_2544, ReturnsFalse_WhenFixedWidthFlagNotSet_2544)
{
    span->flags = 0;
    EXPECT_FALSE(poppler_text_span_is_fixed_width_font(span));
}

// Test that passing nullptr returns FALSE (g_return_val_if_fail guard)
TEST_F(PopplerTextSpanTest_2544, ReturnsFalse_WhenNullPointerPassed_2544)
{
    EXPECT_FALSE(poppler_text_span_is_fixed_width_font(nullptr));
}

// Test that the function correctly isolates the fixed width flag when other flags are also set
TEST_F(PopplerTextSpanTest_2544, ReturnsTrue_WhenFixedWidthFlagSetAmongOtherFlags_2544)
{
    span->flags = POPPLER_TEXT_SPAN_FIXED_WIDTH | (1 << 1) | (1 << 2) | (1 << 3);
    EXPECT_TRUE(poppler_text_span_is_fixed_width_font(span));
}

// Test that having other flags set but NOT fixed width returns FALSE
TEST_F(PopplerTextSpanTest_2544, ReturnsFalse_WhenOtherFlagsSetButNotFixedWidth_2544)
{
    span->flags = (1 << 1) | (1 << 2) | (1 << 3);
    EXPECT_FALSE(poppler_text_span_is_fixed_width_font(span));
}

// Test with all bits set - fixed width should still be detected
TEST_F(PopplerTextSpanTest_2544, ReturnsTrue_WhenAllFlagBitsSet_2544)
{
    span->flags = 0xFFFFFFFF;
    EXPECT_TRUE(poppler_text_span_is_fixed_width_font(span));
}

// Test with a freshly zeroed-out structure
TEST_F(PopplerTextSpanTest_2544, ReturnsFalse_WhenFreshlyAllocatedZeroedSpan_2544)
{
    PopplerTextSpan *fresh_span = g_new0(PopplerTextSpan, 1);
    EXPECT_FALSE(poppler_text_span_is_fixed_width_font(fresh_span));
    g_free(fresh_span);
}
