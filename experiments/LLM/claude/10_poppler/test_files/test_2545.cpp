#include <glib.h>
#include <gtest/gtest.h>

// Minimal definitions needed to test the interface

// Flag definition - matching the pattern used in poppler's glib bindings
#define POPPLER_TEXT_SPAN_SERIF (1 << 2)

// Forward declare the struct as used by the API
typedef struct _PopplerTextSpan {
    gchar *text;
    gchar *font_name;
    guint flags;
    GdkRGBA color;
} PopplerTextSpan;

// Declaration of the function under test
extern "C" {
gboolean poppler_text_span_is_serif_font(PopplerTextSpan *poppler_text_span);
}

class PopplerTextSpanSerifTest_2545 : public ::testing::Test {
protected:
    PopplerTextSpan span;

    void SetUp() override
    {
        memset(&span, 0, sizeof(span));
    }
};

TEST_F(PopplerTextSpanSerifTest_2545, ReturnsFalseWhenNullPointerPassed_2545)
{
    // Passing nullptr should return FALSE (handled by g_return_val_if_fail)
    gboolean result = poppler_text_span_is_serif_font(nullptr);
    EXPECT_EQ(result, FALSE);
}

TEST_F(PopplerTextSpanSerifTest_2545, ReturnsFalseWhenNoFlagsSet_2545)
{
    span.flags = 0;
    gboolean result = poppler_text_span_is_serif_font(&span);
    EXPECT_EQ(result, FALSE);
}

TEST_F(PopplerTextSpanSerifTest_2545, ReturnsTrueWhenSerifFlagSet_2545)
{
    span.flags = POPPLER_TEXT_SPAN_SERIF;
    gboolean result = poppler_text_span_is_serif_font(&span);
    EXPECT_NE(result, FALSE);
}

TEST_F(PopplerTextSpanSerifTest_2545, ReturnsTrueWhenSerifFlagSetAmongOthers_2545)
{
    // Set serif flag along with other flags
    span.flags = POPPLER_TEXT_SPAN_SERIF | (1 << 0) | (1 << 1) | (1 << 3);
    gboolean result = poppler_text_span_is_serif_font(&span);
    EXPECT_NE(result, FALSE);
}

TEST_F(PopplerTextSpanSerifTest_2545, ReturnsFalseWhenOtherFlagsSetButNotSerif_2545)
{
    // Set flags that are NOT the serif flag
    span.flags = (1 << 0) | (1 << 1) | (1 << 3);
    gboolean result = poppler_text_span_is_serif_font(&span);
    EXPECT_EQ(result, FALSE);
}

TEST_F(PopplerTextSpanSerifTest_2545, ReturnsFalseWhenAllBitsExceptSerifSet_2545)
{
    span.flags = ~POPPLER_TEXT_SPAN_SERIF;
    gboolean result = poppler_text_span_is_serif_font(&span);
    EXPECT_EQ(result, FALSE);
}

TEST_F(PopplerTextSpanSerifTest_2545, ReturnsTrueWhenAllBitsSet_2545)
{
    span.flags = 0xFFFFFFFF;
    gboolean result = poppler_text_span_is_serif_font(&span);
    EXPECT_NE(result, FALSE);
}

TEST_F(PopplerTextSpanSerifTest_2545, ReturnsTrueWhenOnlySerifBitSet_2545)
{
    span.flags = POPPLER_TEXT_SPAN_SERIF;
    gboolean result = poppler_text_span_is_serif_font(&span);
    // The result should be exactly the flag value (bitwise AND result)
    EXPECT_TRUE(result != 0);
}
