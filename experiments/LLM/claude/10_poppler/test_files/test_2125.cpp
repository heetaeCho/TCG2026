#include <gtest/gtest.h>
#include <glib.h>

// Include the header for the struct and function declarations
extern "C" {
#include "poppler-annot.h"
}

// Forward declare the function under test
extern "C" void poppler_font_description_free(PopplerFontDescription *font_desc);

class PopplerFontDescriptionFreeTest_2125 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that freeing a properly allocated PopplerFontDescription with a valid font_name does not crash
TEST_F(PopplerFontDescriptionFreeTest_2125, FreeValidFontDescription_2125)
{
    PopplerFontDescription *font_desc = g_new0(PopplerFontDescription, 1);
    font_desc->font_name = g_strdup("Arial");
    font_desc->size_pt = 12.0;

    // Should not crash or leak
    EXPECT_NO_FATAL_FAILURE(poppler_font_description_free(font_desc));
}

// Test that freeing a PopplerFontDescription with NULL font_name does not crash
// (g_free handles NULL gracefully)
TEST_F(PopplerFontDescriptionFreeTest_2125, FreeWithNullFontName_2125)
{
    PopplerFontDescription *font_desc = g_new0(PopplerFontDescription, 1);
    font_desc->font_name = NULL;
    font_desc->size_pt = 10.0;

    // g_free(NULL) is valid, so this should not crash
    EXPECT_NO_FATAL_FAILURE(poppler_font_description_free(font_desc));
}

// Test that freeing a PopplerFontDescription with an empty string font_name works
TEST_F(PopplerFontDescriptionFreeTest_2125, FreeWithEmptyFontName_2125)
{
    PopplerFontDescription *font_desc = g_new0(PopplerFontDescription, 1);
    font_desc->font_name = g_strdup("");
    font_desc->size_pt = 0.0;

    EXPECT_NO_FATAL_FAILURE(poppler_font_description_free(font_desc));
}

// Test freeing a font description with a long font name
TEST_F(PopplerFontDescriptionFreeTest_2125, FreeWithLongFontName_2125)
{
    PopplerFontDescription *font_desc = g_new0(PopplerFontDescription, 1);
    // Create a long font name string
    GString *long_name = g_string_new("");
    for (int i = 0; i < 1000; i++) {
        g_string_append(long_name, "A");
    }
    font_desc->font_name = g_strdup(long_name->str);
    font_desc->size_pt = 72.0;
    g_string_free(long_name, TRUE);

    EXPECT_NO_FATAL_FAILURE(poppler_font_description_free(font_desc));
}

// Test freeing a font description with various field values set
TEST_F(PopplerFontDescriptionFreeTest_2125, FreeWithAllFieldsPopulated_2125)
{
    PopplerFontDescription *font_desc = g_new0(PopplerFontDescription, 1);
    font_desc->font_name = g_strdup("Times New Roman");
    font_desc->size_pt = 24.5;

    EXPECT_NO_FATAL_FAILURE(poppler_font_description_free(font_desc));
}

// Test freeing a zero-initialized font description
TEST_F(PopplerFontDescriptionFreeTest_2125, FreeZeroInitialized_2125)
{
    PopplerFontDescription *font_desc = g_new0(PopplerFontDescription, 1);
    // All fields are zero/NULL from g_new0

    EXPECT_NO_FATAL_FAILURE(poppler_font_description_free(font_desc));
}
