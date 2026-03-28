#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definition based on known dependencies
extern "C" {

typedef struct _PopplerTextSpan PopplerTextSpan;

struct _PopplerTextSpan {
    gchar *text;
};

const gchar *poppler_text_span_get_text(PopplerTextSpan *poppler_text_span);

}

class PopplerTextSpanTest_2548 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerTextSpanTest_2548, ReturnsNullWhenSpanIsNull_2548) {
    const gchar *result = poppler_text_span_get_text(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerTextSpanTest_2548, ReturnsTextWhenSpanHasText_2548) {
    PopplerTextSpan span;
    span.text = g_strdup("Hello, World!");
    
    const gchar *result = poppler_text_span_get_text(&span);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hello, World!");
    
    g_free(span.text);
}

TEST_F(PopplerTextSpanTest_2548, ReturnsEmptyStringWhenTextIsEmpty_2548) {
    PopplerTextSpan span;
    span.text = g_strdup("");
    
    const gchar *result = poppler_text_span_get_text(&span);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
    
    g_free(span.text);
}

TEST_F(PopplerTextSpanTest_2548, ReturnsNullWhenTextFieldIsNull_2548) {
    PopplerTextSpan span;
    span.text = nullptr;
    
    const gchar *result = poppler_text_span_get_text(&span);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerTextSpanTest_2548, ReturnsPointerToInternalText_2548) {
    PopplerTextSpan span;
    span.text = g_strdup("Test string");
    
    const gchar *result = poppler_text_span_get_text(&span);
    // The returned pointer should be the same as the internal text pointer
    EXPECT_EQ(result, span.text);
    
    g_free(span.text);
}

TEST_F(PopplerTextSpanTest_2548, HandlesUTF8Text_2548) {
    PopplerTextSpan span;
    span.text = g_strdup("Héllo Wörld — 日本語");
    
    const gchar *result = poppler_text_span_get_text(&span);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Héllo Wörld — 日本語");
    
    g_free(span.text);
}

TEST_F(PopplerTextSpanTest_2548, HandlesLongText_2548) {
    PopplerTextSpan span;
    // Create a long string
    GString *long_str = g_string_new("");
    for (int i = 0; i < 1000; i++) {
        g_string_append(long_str, "abcdefghij");
    }
    span.text = g_strdup(long_str->str);
    
    const gchar *result = poppler_text_span_get_text(&span);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_str->str);
    EXPECT_EQ(strlen(result), 10000u);
    
    g_free(span.text);
    g_string_free(long_str, TRUE);
}

TEST_F(PopplerTextSpanTest_2548, ConsistentReturnOnMultipleCalls_2548) {
    PopplerTextSpan span;
    span.text = g_strdup("Consistent");
    
    const gchar *result1 = poppler_text_span_get_text(&span);
    const gchar *result2 = poppler_text_span_get_text(&span);
    
    EXPECT_EQ(result1, result2);
    EXPECT_STREQ(result1, "Consistent");
    
    g_free(span.text);
}

TEST_F(PopplerTextSpanTest_2548, HandlesSpecialCharacters_2548) {
    PopplerTextSpan span;
    span.text = g_strdup("Line1\nLine2\tTabbed\r\nWindows");
    
    const gchar *result = poppler_text_span_get_text(&span);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Line1\nLine2\tTabbed\r\nWindows");
    
    g_free(span.text);
}
