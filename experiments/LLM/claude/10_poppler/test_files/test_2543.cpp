#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and struct definition based on known dependencies
typedef struct _PopplerTextSpan {
    gchar *text;
    gchar *font_name;
} PopplerTextSpan;

// Declaration of the function under test
extern "C" {
void poppler_text_span_free(PopplerTextSpan *poppler_text_span);
}

// If we cannot link against the actual implementation, we provide it here
// based on the given code. In a real scenario, we'd link against the library.
#ifndef POPPLER_LINKED
void poppler_text_span_free(PopplerTextSpan *poppler_text_span)
{
    if (G_UNLIKELY(poppler_text_span == nullptr)) {
        return;
    }
    g_free(poppler_text_span->text);
    g_free(poppler_text_span->font_name);
    g_slice_free(PopplerTextSpan, poppler_text_span);
}
#endif

class PopplerTextSpanFreeTest_2543 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr does not crash
TEST_F(PopplerTextSpanFreeTest_2543, FreeNullPointerDoesNotCrash_2543)
{
    // Should handle nullptr gracefully without crashing
    EXPECT_NO_FATAL_FAILURE(poppler_text_span_free(nullptr));
}

// Test freeing a properly allocated PopplerTextSpan with both fields set
TEST_F(PopplerTextSpanFreeTest_2543, FreeValidSpanWithTextAndFontName_2543)
{
    PopplerTextSpan *span = g_slice_new(PopplerTextSpan);
    span->text = g_strdup("Hello, World!");
    span->font_name = g_strdup("Arial");

    EXPECT_NO_FATAL_FAILURE(poppler_text_span_free(span));
}

// Test freeing a PopplerTextSpan where text is NULL
TEST_F(PopplerTextSpanFreeTest_2543, FreeSpanWithNullText_2543)
{
    PopplerTextSpan *span = g_slice_new(PopplerTextSpan);
    span->text = nullptr;
    span->font_name = g_strdup("Times New Roman");

    EXPECT_NO_FATAL_FAILURE(poppler_text_span_free(span));
}

// Test freeing a PopplerTextSpan where font_name is NULL
TEST_F(PopplerTextSpanFreeTest_2543, FreeSpanWithNullFontName_2543)
{
    PopplerTextSpan *span = g_slice_new(PopplerTextSpan);
    span->text = g_strdup("Some text");
    span->font_name = nullptr;

    EXPECT_NO_FATAL_FAILURE(poppler_text_span_free(span));
}

// Test freeing a PopplerTextSpan where both fields are NULL
TEST_F(PopplerTextSpanFreeTest_2543, FreeSpanWithBothFieldsNull_2543)
{
    PopplerTextSpan *span = g_slice_new(PopplerTextSpan);
    span->text = nullptr;
    span->font_name = nullptr;

    EXPECT_NO_FATAL_FAILURE(poppler_text_span_free(span));
}

// Test freeing a PopplerTextSpan with empty strings
TEST_F(PopplerTextSpanFreeTest_2543, FreeSpanWithEmptyStrings_2543)
{
    PopplerTextSpan *span = g_slice_new(PopplerTextSpan);
    span->text = g_strdup("");
    span->font_name = g_strdup("");

    EXPECT_NO_FATAL_FAILURE(poppler_text_span_free(span));
}

// Test freeing a PopplerTextSpan with very long strings
TEST_F(PopplerTextSpanFreeTest_2543, FreeSpanWithLongStrings_2543)
{
    PopplerTextSpan *span = g_slice_new(PopplerTextSpan);
    
    // Create a long string
    GString *long_str = g_string_new("");
    for (int i = 0; i < 10000; i++) {
        g_string_append_c(long_str, 'A');
    }
    
    span->text = g_strdup(long_str->str);
    span->font_name = g_strdup(long_str->str);
    
    g_string_free(long_str, TRUE);

    EXPECT_NO_FATAL_FAILURE(poppler_text_span_free(span));
}

// Test multiple sequential frees don't cause issues
TEST_F(PopplerTextSpanFreeTest_2543, MultipleFreesOfDifferentSpans_2543)
{
    for (int i = 0; i < 100; i++) {
        PopplerTextSpan *span = g_slice_new(PopplerTextSpan);
        span->text = g_strdup("test text");
        span->font_name = g_strdup("Courier");
        EXPECT_NO_FATAL_FAILURE(poppler_text_span_free(span));
    }
}

// Test freeing with text containing special characters / UTF-8
TEST_F(PopplerTextSpanFreeTest_2543, FreeSpanWithUtf8Text_2543)
{
    PopplerTextSpan *span = g_slice_new(PopplerTextSpan);
    span->text = g_strdup("Héllo Wörld! 日本語テスト");
    span->font_name = g_strdup("Noto Sans CJK");

    EXPECT_NO_FATAL_FAILURE(poppler_text_span_free(span));
}
