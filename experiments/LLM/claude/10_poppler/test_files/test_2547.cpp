#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definitions based on the known dependencies
// We need to include the actual headers or replicate the structures for testing

extern "C" {

typedef struct {
    guint16 red;
    guint16 green;
    guint16 blue;
} PopplerColor;

typedef struct {
    gchar *text;
    PopplerColor color;
    // There may be other fields, but we only care about color for these tests
} PopplerTextSpan;

void poppler_text_span_get_color(PopplerTextSpan *poppler_text_span, PopplerColor *color);

} // extern "C"

class PopplerTextSpanGetColorTest_2547 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal operation: retrieving color from a valid text span
TEST_F(PopplerTextSpanGetColorTest_2547, ReturnsCorrectColor_2547) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.color.red = 255;
    span.color.green = 128;
    span.color.blue = 64;

    PopplerColor result_color;
    memset(&result_color, 0, sizeof(result_color));

    poppler_text_span_get_color(&span, &result_color);

    EXPECT_EQ(result_color.red, 255);
    EXPECT_EQ(result_color.green, 128);
    EXPECT_EQ(result_color.blue, 64);
}

// Test with zero color values
TEST_F(PopplerTextSpanGetColorTest_2547, ReturnsZeroColor_2547) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.color.red = 0;
    span.color.green = 0;
    span.color.blue = 0;

    PopplerColor result_color;
    result_color.red = 999;
    result_color.green = 999;
    result_color.blue = 999;

    poppler_text_span_get_color(&span, &result_color);

    EXPECT_EQ(result_color.red, 0);
    EXPECT_EQ(result_color.green, 0);
    EXPECT_EQ(result_color.blue, 0);
}

// Test with maximum color values (guint16 max = 65535)
TEST_F(PopplerTextSpanGetColorTest_2547, ReturnsMaxColor_2547) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.color.red = 65535;
    span.color.green = 65535;
    span.color.blue = 65535;

    PopplerColor result_color;
    memset(&result_color, 0, sizeof(result_color));

    poppler_text_span_get_color(&span, &result_color);

    EXPECT_EQ(result_color.red, 65535);
    EXPECT_EQ(result_color.green, 65535);
    EXPECT_EQ(result_color.blue, 65535);
}

// Test that passing nullptr for poppler_text_span does not crash (g_return_if_fail handles it)
TEST_F(PopplerTextSpanGetColorTest_2547, NullTextSpanDoesNotCrash_2547) {
    PopplerColor result_color;
    result_color.red = 42;
    result_color.green = 42;
    result_color.blue = 42;

    // g_return_if_fail should just return without modifying color
    poppler_text_span_get_color(nullptr, &result_color);

    // Color should remain unchanged since the function returned early
    EXPECT_EQ(result_color.red, 42);
    EXPECT_EQ(result_color.green, 42);
    EXPECT_EQ(result_color.blue, 42);
}

// Test that passing nullptr for color does not crash (g_return_if_fail handles it)
TEST_F(PopplerTextSpanGetColorTest_2547, NullColorDoesNotCrash_2547) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.color.red = 100;
    span.color.green = 200;
    span.color.blue = 300;

    // g_return_if_fail should just return without crashing
    poppler_text_span_get_color(&span, nullptr);
    // If we reach here, the function handled the null gracefully
}

// Test that both null parameters do not crash
TEST_F(PopplerTextSpanGetColorTest_2547, BothNullDoesNotCrash_2547) {
    poppler_text_span_get_color(nullptr, nullptr);
    // If we reach here, the function handled both nulls gracefully
}

// Test with distinct color component values to ensure correct field mapping
TEST_F(PopplerTextSpanGetColorTest_2547, DistinctColorComponents_2547) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.color.red = 1;
    span.color.green = 2;
    span.color.blue = 3;

    PopplerColor result_color;
    memset(&result_color, 0, sizeof(result_color));

    poppler_text_span_get_color(&span, &result_color);

    // Verify each component is independently correct
    EXPECT_EQ(result_color.red, 1);
    EXPECT_EQ(result_color.green, 2);
    EXPECT_EQ(result_color.blue, 3);
    
    // Verify they are different from each other (ensures no aliasing)
    EXPECT_NE(result_color.red, result_color.green);
    EXPECT_NE(result_color.green, result_color.blue);
    EXPECT_NE(result_color.red, result_color.blue);
}

// Test that the output color is a copy, not a reference
TEST_F(PopplerTextSpanGetColorTest_2547, ColorIsCopied_2547) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.color.red = 100;
    span.color.green = 200;
    span.color.blue = 300;

    PopplerColor result_color;
    poppler_text_span_get_color(&span, &result_color);

    // Modify the span's color after getting
    span.color.red = 999;
    span.color.green = 999;
    span.color.blue = 999;

    // result_color should still have original values
    EXPECT_EQ(result_color.red, 100);
    EXPECT_EQ(result_color.green, 200);
    EXPECT_EQ(result_color.blue, 300);
}

// Test calling the function multiple times with different colors
TEST_F(PopplerTextSpanGetColorTest_2547, MultipleCallsReturnCorrectColors_2547) {
    PopplerTextSpan span;
    span.text = nullptr;
    PopplerColor result_color;

    span.color.red = 10;
    span.color.green = 20;
    span.color.blue = 30;
    poppler_text_span_get_color(&span, &result_color);
    EXPECT_EQ(result_color.red, 10);
    EXPECT_EQ(result_color.green, 20);
    EXPECT_EQ(result_color.blue, 30);

    span.color.red = 40;
    span.color.green = 50;
    span.color.blue = 60;
    poppler_text_span_get_color(&span, &result_color);
    EXPECT_EQ(result_color.red, 40);
    EXPECT_EQ(result_color.green, 50);
    EXPECT_EQ(result_color.blue, 60);
}
