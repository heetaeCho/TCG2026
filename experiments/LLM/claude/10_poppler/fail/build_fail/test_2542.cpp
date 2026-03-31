#include <glib.h>
#include <gtest/gtest.h>

// We need the PopplerTextSpan structure and the functions under test.
// Based on the partial code, PopplerTextSpan has at least text and font_name fields.
// We include the public header or replicate the minimal struct needed.

extern "C" {

// Minimal struct definition matching what we can infer from the implementation
typedef struct _PopplerTextSpan {
    char *text;
    char *font_name;
    // There may be other fields, but we only test observable behavior through the API
} PopplerTextSpan;

// Function declarations
PopplerTextSpan *poppler_text_span_copy(PopplerTextSpan *poppler_text_span);

// We also need poppler_text_span_free if available; if not, we manually free.
// For safety, let's declare a helper to free since the actual free function
// may or may not be available. We'll use g_slice_free.
void test_free_text_span(PopplerTextSpan *span) {
    if (span) {
        g_free(span->text);
        g_free(span->font_name);
        g_slice_free(PopplerTextSpan, span);
    }
}

} // extern "C"

class PopplerTextSpanCopyTest_2542 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup handled per test
    }
};

// Test that copying a valid PopplerTextSpan with both text and font_name works
TEST_F(PopplerTextSpanCopyTest_2542, CopyWithTextAndFontName_2542) {
    PopplerTextSpan original;
    original.text = g_strdup("Hello, World!");
    original.font_name = g_strdup("Arial");

    PopplerTextSpan *copy = poppler_text_span_copy(&original);

    ASSERT_NE(copy, nullptr);
    // The copy should have the same text content
    EXPECT_STREQ(copy->text, "Hello, World!");
    // The copy should have the same font_name content
    EXPECT_STREQ(copy->font_name, "Arial");
    // The pointers should be different (deep copy)
    EXPECT_NE(copy->text, original.text);
    EXPECT_NE(copy->font_name, original.font_name);

    test_free_text_span(copy);
    g_free(original.text);
    g_free(original.font_name);
}

// Test that copying a PopplerTextSpan with NULL font_name works
TEST_F(PopplerTextSpanCopyTest_2542, CopyWithNullFontName_2542) {
    PopplerTextSpan original;
    original.text = g_strdup("Some text");
    original.font_name = nullptr;

    PopplerTextSpan *copy = poppler_text_span_copy(&original);

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->text, "Some text");
    EXPECT_EQ(copy->font_name, nullptr);
    EXPECT_NE(copy->text, original.text);

    test_free_text_span(copy);
    g_free(original.text);
}

// Test that copying a PopplerTextSpan with empty text works
TEST_F(PopplerTextSpanCopyTest_2542, CopyWithEmptyText_2542) {
    PopplerTextSpan original;
    original.text = g_strdup("");
    original.font_name = g_strdup("Times");

    PopplerTextSpan *copy = poppler_text_span_copy(&original);

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->text, "");
    EXPECT_STREQ(copy->font_name, "Times");
    EXPECT_NE(copy->text, original.text);
    EXPECT_NE(copy->font_name, original.font_name);

    test_free_text_span(copy);
    g_free(original.text);
    g_free(original.font_name);
}

// Test that passing NULL returns NULL (g_return_val_if_fail should handle this)
TEST_F(PopplerTextSpanCopyTest_2542, CopyNullReturnsNull_2542) {
    // g_return_val_if_fail with nullptr should return NULL
    // This will produce a g_warning, but should not crash
    PopplerTextSpan *copy = poppler_text_span_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

// Test that the copy is independent - modifying copy doesn't affect original
TEST_F(PopplerTextSpanCopyTest_2542, CopyIsIndependent_2542) {
    PopplerTextSpan original;
    original.text = g_strdup("Original text");
    original.font_name = g_strdup("Helvetica");

    PopplerTextSpan *copy = poppler_text_span_copy(&original);

    ASSERT_NE(copy, nullptr);

    // Free and replace copy's text
    g_free(copy->text);
    copy->text = g_strdup("Modified text");

    // Original should be unchanged
    EXPECT_STREQ(original.text, "Original text");
    EXPECT_STREQ(copy->text, "Modified text");

    test_free_text_span(copy);
    g_free(original.text);
    g_free(original.font_name);
}

// Test copy with NULL text (edge case - text could potentially be NULL)
TEST_F(PopplerTextSpanCopyTest_2542, CopyWithNullText_2542) {
    PopplerTextSpan original;
    original.text = nullptr;
    original.font_name = g_strdup("Courier");

    // g_strdup(NULL) returns NULL, so this should work
    PopplerTextSpan *copy = poppler_text_span_copy(&original);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->text, nullptr);
    EXPECT_STREQ(copy->font_name, "Courier");

    test_free_text_span(copy);
    g_free(original.font_name);
}

// Test copy with empty font_name
TEST_F(PopplerTextSpanCopyTest_2542, CopyWithEmptyFontName_2542) {
    PopplerTextSpan original;
    original.text = g_strdup("Test");
    original.font_name = g_strdup("");

    PopplerTextSpan *copy = poppler_text_span_copy(&original);

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->text, "Test");
    EXPECT_STREQ(copy->font_name, "");
    EXPECT_NE(copy->font_name, original.font_name);

    test_free_text_span(copy);
    g_free(original.text);
    g_free(original.font_name);
}

// Test copy with long text string
TEST_F(PopplerTextSpanCopyTest_2542, CopyWithLongText_2542) {
    PopplerTextSpan original;
    // Create a long string
    std::string long_text(10000, 'A');
    original.text = g_strdup(long_text.c_str());
    original.font_name = nullptr;

    PopplerTextSpan *copy = poppler_text_span_copy(&original);

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->text, long_text.c_str());
    EXPECT_NE(copy->text, original.text);

    test_free_text_span(copy);
    g_free(original.text);
}

// Test that copying works with Unicode text
TEST_F(PopplerTextSpanCopyTest_2542, CopyWithUnicodeText_2542) {
    PopplerTextSpan original;
    original.text = g_strdup("日本語テキスト");
    original.font_name = g_strdup("NotoSansCJK");

    PopplerTextSpan *copy = poppler_text_span_copy(&original);

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->text, "日本語テキスト");
    EXPECT_STREQ(copy->font_name, "NotoSansCJK");

    test_free_text_span(copy);
    g_free(original.text);
    g_free(original.font_name);
}

// Test multiple copies from the same original
TEST_F(PopplerTextSpanCopyTest_2542, MultipleCopiesFromSameOriginal_2542) {
    PopplerTextSpan original;
    original.text = g_strdup("Shared source");
    original.font_name = g_strdup("Mono");

    PopplerTextSpan *copy1 = poppler_text_span_copy(&original);
    PopplerTextSpan *copy2 = poppler_text_span_copy(&original);

    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2);
    EXPECT_STREQ(copy1->text, "Shared source");
    EXPECT_STREQ(copy2->text, "Shared source");
    EXPECT_NE(copy1->text, copy2->text);

    test_free_text_span(copy1);
    test_free_text_span(copy2);
    g_free(original.text);
    g_free(original.font_name);
}
