#include <gtest/gtest.h>
#include <glib.h>

// Include the necessary poppler headers
extern "C" {
#include "poppler-page.h"
}

// If poppler-page.h doesn't provide the full declarations, we need the poppler header
// We rely on the public API as declared in the poppler glib headers

class PopplerTextAttributesTest_2479 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_text_attributes_free does not crash when given a valid PopplerTextAttributes
// with a dynamically allocated font_name
TEST_F(PopplerTextAttributesTest_2479, FreeValidAttributes_2479)
{
    PopplerTextAttributes *attrs = g_slice_new0(PopplerTextAttributes);
    attrs->font_name = g_strdup("Arial");
    attrs->font_size = 12.0;
    attrs->is_underlined = FALSE;
    attrs->color.red = 0;
    attrs->color.green = 0;
    attrs->color.blue = 0;
    attrs->start_index = 0;
    attrs->end_index = 10;

    // Should not crash or leak
    poppler_text_attributes_free(attrs);
    // If we reach here, the test passes (no crash)
    SUCCEED();
}

// Test that poppler_text_attributes_free handles a NULL font_name
// g_free(NULL) is valid and should not crash
TEST_F(PopplerTextAttributesTest_2479, FreeWithNullFontName_2479)
{
    PopplerTextAttributes *attrs = g_slice_new0(PopplerTextAttributes);
    attrs->font_name = NULL;
    attrs->font_size = 10.0;
    attrs->is_underlined = FALSE;
    attrs->start_index = 0;
    attrs->end_index = 5;

    // g_free(NULL) is safe, so this should not crash
    poppler_text_attributes_free(attrs);
    SUCCEED();
}

// Test that poppler_text_attributes_free handles an empty font name string
TEST_F(PopplerTextAttributesTest_2479, FreeWithEmptyFontName_2479)
{
    PopplerTextAttributes *attrs = g_slice_new0(PopplerTextAttributes);
    attrs->font_name = g_strdup("");
    attrs->font_size = 0.0;
    attrs->is_underlined = FALSE;
    attrs->start_index = 0;
    attrs->end_index = 0;

    poppler_text_attributes_free(attrs);
    SUCCEED();
}

// Test freeing attributes with various field values set
TEST_F(PopplerTextAttributesTest_2479, FreeWithVariousFieldValues_2479)
{
    PopplerTextAttributes *attrs = g_slice_new0(PopplerTextAttributes);
    attrs->font_name = g_strdup("Times New Roman Bold Italic");
    attrs->font_size = 72.5;
    attrs->is_underlined = TRUE;
    attrs->color.red = 65535;
    attrs->color.green = 32768;
    attrs->color.blue = 0;
    attrs->start_index = 100;
    attrs->end_index = 200;

    poppler_text_attributes_free(attrs);
    SUCCEED();
}

// Test that poppler_text_attributes_new creates a valid object (if available)
// and that it can be freed
TEST_F(PopplerTextAttributesTest_2479, NewAndFree_2479)
{
    PopplerTextAttributes *attrs = poppler_text_attributes_new();
    ASSERT_NE(attrs, nullptr);

    // The new function should initialize with some defaults
    // We can free it without issues
    poppler_text_attributes_free(attrs);
    SUCCEED();
}

// Test freeing attributes with a long font name
TEST_F(PopplerTextAttributesTest_2479, FreeWithLongFontName_2479)
{
    PopplerTextAttributes *attrs = g_slice_new0(PopplerTextAttributes);
    // Create a very long font name
    GString *long_name = g_string_new("");
    for (int i = 0; i < 1000; i++) {
        g_string_append(long_name, "A");
    }
    attrs->font_name = g_strdup(long_name->str);
    g_string_free(long_name, TRUE);

    attrs->font_size = 1.0;
    attrs->is_underlined = FALSE;
    attrs->start_index = 0;
    attrs->end_index = 1;

    poppler_text_attributes_free(attrs);
    SUCCEED();
}

// Test copy functionality if poppler_text_attributes_copy exists
TEST_F(PopplerTextAttributesTest_2479, CopyAndFree_2479)
{
    PopplerTextAttributes *attrs = g_slice_new0(PopplerTextAttributes);
    attrs->font_name = g_strdup("Courier");
    attrs->font_size = 14.0;
    attrs->is_underlined = TRUE;
    attrs->color.red = 255;
    attrs->color.green = 128;
    attrs->color.blue = 64;
    attrs->start_index = 5;
    attrs->end_index = 15;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(attrs);
    ASSERT_NE(copy, nullptr);

    // Verify the copy has the same values
    EXPECT_STREQ(copy->font_name, "Courier");
    EXPECT_DOUBLE_EQ(copy->font_size, 14.0);
    EXPECT_EQ(copy->is_underlined, TRUE);
    EXPECT_EQ(copy->color.red, 255);
    EXPECT_EQ(copy->color.green, 128);
    EXPECT_EQ(copy->color.blue, 64);
    EXPECT_EQ(copy->start_index, 5);
    EXPECT_EQ(copy->end_index, 15);

    // Verify they are independent (different pointers for font_name)
    EXPECT_NE(copy->font_name, attrs->font_name);

    poppler_text_attributes_free(attrs);
    poppler_text_attributes_free(copy);
}

// Test that freeing multiple attributes sequentially works fine
TEST_F(PopplerTextAttributesTest_2479, FreeMultipleAttributes_2479)
{
    for (int i = 0; i < 100; i++) {
        PopplerTextAttributes *attrs = g_slice_new0(PopplerTextAttributes);
        attrs->font_name = g_strdup_printf("Font_%d", i);
        attrs->font_size = (double)i;
        attrs->start_index = i;
        attrs->end_index = i + 10;
        poppler_text_attributes_free(attrs);
    }
    SUCCEED();
}
