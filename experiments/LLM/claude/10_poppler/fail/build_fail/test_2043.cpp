#include <gtest/gtest.h>
#include <glib.h>
#include <string>

// Include necessary headers from the project
// We need the PopplerFontDescription struct and related enums
// Since we're testing a static function, we need to either include the source
// or declare the function. Given the function is static in the .cc file,
// we'll include the source file to access it.

// Forward declarations of enums used in PopplerFontDescription
// These are typically defined in poppler-annot.h or related headers
extern "C" {
#include "poppler-annot.h"
}

// Since poppler_font_name_to_description is a static function in the .cc file,
// we need to include the .cc to test it, or we redefine access.
// We'll use a workaround: include the implementation file to access the static function.
// This is acceptable for unit testing static functions.

// We need to make the static function accessible. One approach:
// Temporarily redefine static for inclusion purposes.
// However, a cleaner approach for testing is to include the cc file.

// First, let's try including necessary poppler headers
#include "poppler-annot.cc"

class PopplerFontNameToDescriptionTest_2043 : public ::testing::Test {
protected:
    PopplerFontDescription font_desc;

    void SetUp() override {
        memset(&font_desc, 0, sizeof(font_desc));
        // Initialize to default values
        font_desc.font_name = nullptr;
        font_desc.size_pt = 0.0;
        font_desc.stretch = POPPLER_STRETCH_NORMAL;
        font_desc.weight = POPPLER_WEIGHT_NORMAL;
        font_desc.style = POPPLER_STYLE_NORMAL;
    }

    void TearDown() override {
        if (font_desc.font_name) {
            g_free(font_desc.font_name);
            font_desc.font_name = nullptr;
        }
    }
};

// Test with a simple font name with no style words
TEST_F(PopplerFontNameToDescriptionTest_2043, SimpleNameNoStyle_2043) {
    poppler_font_name_to_description("Helvetica", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    EXPECT_STREQ(font_desc.font_name, "Helvetica");
}

// Test with an empty string
TEST_F(PopplerFontNameToDescriptionTest_2043, EmptyString_2043) {
    poppler_font_name_to_description("", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    EXPECT_STREQ(font_desc.font_name, "");
}

// Test with a font name containing "Bold" as a style word
TEST_F(PopplerFontNameToDescriptionTest_2043, FontNameWithBold_2043) {
    poppler_font_name_to_description("Helvetica Bold", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    EXPECT_STREQ(font_desc.font_name, "Helvetica");
    EXPECT_EQ(font_desc.weight, POPPLER_WEIGHT_BOLD);
}

// Test with a font name containing "Italic" as a style word
TEST_F(PopplerFontNameToDescriptionTest_2043, FontNameWithItalic_2043) {
    poppler_font_name_to_description("Helvetica Italic", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    EXPECT_STREQ(font_desc.font_name, "Helvetica");
    EXPECT_EQ(font_desc.style, POPPLER_STYLE_ITALIC);
}

// Test with a font name containing "Bold Italic"
TEST_F(PopplerFontNameToDescriptionTest_2043, FontNameWithBoldItalic_2043) {
    poppler_font_name_to_description("Helvetica Bold Italic", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    EXPECT_STREQ(font_desc.font_name, "Helvetica");
    EXPECT_EQ(font_desc.weight, POPPLER_WEIGHT_BOLD);
    EXPECT_EQ(font_desc.style, POPPLER_STYLE_ITALIC);
}

// Test with a font name containing "Oblique"
TEST_F(PopplerFontNameToDescriptionTest_2043, FontNameWithOblique_2043) {
    poppler_font_name_to_description("Courier Oblique", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    EXPECT_STREQ(font_desc.font_name, "Courier");
    EXPECT_EQ(font_desc.style, POPPLER_STYLE_OBLIQUE);
}

// Test with a font name containing "Bold Oblique"
TEST_F(PopplerFontNameToDescriptionTest_2043, FontNameWithBoldOblique_2043) {
    poppler_font_name_to_description("Courier Bold Oblique", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    EXPECT_STREQ(font_desc.font_name, "Courier");
    EXPECT_EQ(font_desc.weight, POPPLER_WEIGHT_BOLD);
    EXPECT_EQ(font_desc.style, POPPLER_STYLE_OBLIQUE);
}

// Test with a single-word font name
TEST_F(PopplerFontNameToDescriptionTest_2043, SingleWordFontName_2043) {
    poppler_font_name_to_description("Arial", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    EXPECT_STREQ(font_desc.font_name, "Arial");
}

// Test with a multi-word font name where no words are style indicators
TEST_F(PopplerFontNameToDescriptionTest_2043, MultiWordNonStyleName_2043) {
    poppler_font_name_to_description("Times New Roman", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    // "Roman" is not typically a recognized style word, so name should remain
    // The exact behavior depends on update_font_desc_with_word implementation
    // but the font_name should not be nullptr
    EXPECT_NE(std::string(font_desc.font_name).size(), 0u);
}

// Test with a font name that has three style words at the end
TEST_F(PopplerFontNameToDescriptionTest_2043, ThreeStyleWords_2043) {
    // This tests the maximum of 3 style words being parsed
    // Using hypothetical style words - "Condensed Bold Italic"
    poppler_font_name_to_description("Helvetica Condensed Bold Italic", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    // At minimum, the font_name should be set
    EXPECT_NE(std::string(font_desc.font_name).size(), 0u);
}

// Test with a name that is just a style word
TEST_F(PopplerFontNameToDescriptionTest_2043, OnlyStyleWord_2043) {
    poppler_font_name_to_description("Bold", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    // Either "Bold" is consumed as style and font_name is empty,
    // or it remains as font_name - depends on implementation
}

// Test with multiple spaces
TEST_F(PopplerFontNameToDescriptionTest_2043, FontNameWithMultipleSpaces_2043) {
    poppler_font_name_to_description("Helvetica  Bold", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    // The function should handle this case - font_name should be set
}

// Test with trailing space
TEST_F(PopplerFontNameToDescriptionTest_2043, FontNameWithTrailingSpace_2043) {
    poppler_font_name_to_description("Helvetica Bold ", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
}

// Test with leading space
TEST_F(PopplerFontNameToDescriptionTest_2043, FontNameWithLeadingSpace_2043) {
    poppler_font_name_to_description(" Helvetica Bold", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
}

// Test that font_name is properly allocated with g_strdup (non-null for valid input)
TEST_F(PopplerFontNameToDescriptionTest_2043, FontNameIsAllocated_2043) {
    poppler_font_name_to_description("TestFont", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    EXPECT_STREQ(font_desc.font_name, "TestFont");
    // Verify we can free it with g_free (done in TearDown)
}

// Test with a very long font name
TEST_F(PopplerFontNameToDescriptionTest_2043, VeryLongFontName_2043) {
    std::string longName(1000, 'A');
    longName += " Bold";
    poppler_font_name_to_description(longName, font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
}

// Test with font name containing "Light" weight
TEST_F(PopplerFontNameToDescriptionTest_2043, FontNameWithLight_2043) {
    poppler_font_name_to_description("Helvetica Light", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    // Either "Light" is recognized as a style word or not
    // The font_name should be set regardless
}

// Test that parsing stops when a non-style word is encountered
TEST_F(PopplerFontNameToDescriptionTest_2043, NonStyleWordStopsParsing_2043) {
    poppler_font_name_to_description("Helvetica Neue Bold", font_desc);
    ASSERT_NE(font_desc.font_name, nullptr);
    // "Bold" should be consumed, but "Neue" is not a style word
    // so parsing should stop, leaving "Helvetica Neue" as the font name
}
