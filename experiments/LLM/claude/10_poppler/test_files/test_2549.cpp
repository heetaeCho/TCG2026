#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definition based on known dependencies
extern "C" {

typedef struct _PopplerTextSpan PopplerTextSpan;

struct _PopplerTextSpan {
    gchar *text;
    gchar *font_name;
    // There may be other fields, but we only need font_name for our tests
};

const gchar *poppler_text_span_get_font_name(PopplerTextSpan *poppler_text_span);

}

class PopplerTextSpanGetFontNameTest_2549 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing a valid PopplerTextSpan with a non-null font_name returns that font name
TEST_F(PopplerTextSpanGetFontNameTest_2549, ReturnsValidFontName_2549) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.font_name = g_strdup("Arial");

    const gchar *result = poppler_text_span_get_font_name(&span);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Arial");

    g_free(span.font_name);
}

// Test that passing a valid PopplerTextSpan with a null font_name returns null
TEST_F(PopplerTextSpanGetFontNameTest_2549, ReturnsNullWhenFontNameIsNull_2549) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.font_name = nullptr;

    const gchar *result = poppler_text_span_get_font_name(&span);
    EXPECT_EQ(result, nullptr);
}

// Test that passing nullptr as the span returns NULL (g_return_val_if_fail behavior)
TEST_F(PopplerTextSpanGetFontNameTest_2549, ReturnsNullForNullSpan_2549) {
    const gchar *result = poppler_text_span_get_font_name(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with an empty string font name
TEST_F(PopplerTextSpanGetFontNameTest_2549, ReturnsEmptyStringFontName_2549) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.font_name = g_strdup("");

    const gchar *result = poppler_text_span_get_font_name(&span);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    g_free(span.font_name);
}

// Test with a long font name string
TEST_F(PopplerTextSpanGetFontNameTest_2549, ReturnsLongFontName_2549) {
    PopplerTextSpan span;
    span.text = nullptr;
    // Create a long font name
    std::string long_name(1024, 'A');
    span.font_name = g_strdup(long_name.c_str());

    const gchar *result = poppler_text_span_get_font_name(&span);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_name.c_str());

    g_free(span.font_name);
}

// Test that the returned pointer points to the same memory as font_name (not a copy)
TEST_F(PopplerTextSpanGetFontNameTest_2549, ReturnsSamePointerAsFontName_2549) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.font_name = g_strdup("TimesNewRoman");

    const gchar *result = poppler_text_span_get_font_name(&span);
    EXPECT_EQ(result, span.font_name);

    g_free(span.font_name);
}

// Test with a font name containing special characters
TEST_F(PopplerTextSpanGetFontNameTest_2549, ReturnsSpecialCharFontName_2549) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.font_name = g_strdup("Font-Name_With.Special+Chars");

    const gchar *result = poppler_text_span_get_font_name(&span);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Font-Name_With.Special+Chars");

    g_free(span.font_name);
}

// Test with a font name containing UTF-8 characters
TEST_F(PopplerTextSpanGetFontNameTest_2549, ReturnsUtf8FontName_2549) {
    PopplerTextSpan span;
    span.text = nullptr;
    span.font_name = g_strdup("フォント名");

    const gchar *result = poppler_text_span_get_font_name(&span);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "フォント名");

    g_free(span.font_name);
}
