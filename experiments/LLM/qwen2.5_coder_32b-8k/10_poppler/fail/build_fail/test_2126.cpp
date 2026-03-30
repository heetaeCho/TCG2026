#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



// Mocking any dependencies if necessary (none in this case)

// For example, if there were callbacks or external dependencies, we would mock them here.



// Test fixture for PopplerFontDescription tests

class PopplerFontDescriptionTest_2126 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary resources before each test

        original_font_desc = g_new(PopplerFontDescription, 1);

        original_font_desc->font_name = g_strdup("Arial");

        original_font_desc->size_pt = 12.0;

        original_font_desc->stretch = POPPLER_STRETCH_NORMAL;

        original_font_desc->weight = POPPLER_WEIGHT_NORMAL;

        original_font_desc->style = POPPLER_STYLE_NORMAL;

    }



    void TearDown() override {

        // Clean up any resources after each test

        g_free(original_font_desc->font_name);

        g_free(original_font_desc);

        if (copied_font_desc) {

            g_free(copied_font_desc->font_name);

            g_free(copied_font_desc);

        }

    }



    PopplerFontDescription *original_font_desc = nullptr;

    PopplerFontDescription *copied_font_desc = nullptr;

};



// Test normal operation: successful copy

TEST_F(PopplerFontDescriptionTest_2126, SuccessfulCopy_2126) {

    copied_font_desc = poppler_font_description_copy(original_font_desc);

    EXPECT_STREQ(copied_font_desc->font_name, "Arial");

    EXPECT_EQ(copied_font_desc->size_pt, 12.0);

    EXPECT_EQ(copied_font_desc->stretch, POPPLER_STRETCH_NORMAL);

    EXPECT_EQ(copied_font_desc->weight, POPPLER_WEIGHT_NORMAL);

    EXPECT_EQ(copied_font_desc->style, POPPLER_STYLE_NORMAL);



    // Ensure that the original and copied are different pointers

    EXPECT_NE(original_font_desc, copied_font_desc);

}



// Test boundary condition: empty font name

TEST_F(PopplerFontDescriptionTest_2126, EmptyFontName_2126) {

    g_free(original_font_desc->font_name);

    original_font_desc->font_name = nullptr;

    copied_font_desc = poppler_font_description_copy(original_font_desc);

    EXPECT_EQ(copied_font_desc->font_name, static_cast<char*>(nullptr));

}



// Test boundary condition: zero size

TEST_F(PopplerFontDescriptionTest_2126, ZeroSize_2126) {

    original_font_desc->size_pt = 0.0;

    copied_font_desc = poppler_font_description_copy(original_font_desc);

    EXPECT_EQ(copied_font_desc->size_pt, 0.0);

}



// Test boundary condition: extreme values for size

TEST_F(PopplerFontDescriptionTest_2126, ExtremeSizeValues_2126) {

    original_font_desc->size_pt = -100.0;

    copied_font_desc = poppler_font_description_copy(original_font_desc);

    EXPECT_EQ(copied_font_desc->size_pt, -100.0);



    g_free(original_font_desc->font_name);

    original_font_desc->font_name = nullptr;

    original_font_desc->size_pt = 1000.0;

    copied_font_desc = poppler_font_description_copy(original_font_desc);

    EXPECT_EQ(copied_font_desc->size_pt, 1000.0);

}



// Test boundary condition: different style and weight values

TEST_F(PopplerFontDescriptionTest_2126, DifferentStyleAndWeightValues_2126) {

    original_font_desc->style = POPPLER_STYLE_OBLIQUE;

    original_font_desc->weight = POPPLER_WEIGHT_BOLD;

    copied_font_desc = poppler_font_description_copy(original_font_desc);

    EXPECT_EQ(copied_font_desc->style, POPPLER_STYLE_OBLIQUE);

    EXPECT_EQ(copied_font_desc->weight, POPPLER_WEIGHT_BOLD);



    original_font_desc->style = POPPLER_STYLE_NORMAL;

    original_font_desc->weight = POPPLER_WEIGHT_NORMAL;

    copied_font_desc = poppler_font_description_copy(original_font_desc);

    EXPECT_EQ(copied_font_desc->style, POPPLER_STYLE_NORMAL);

    EXPECT_EQ(copied_font_desc->weight, POPPLER_WEIGHT_NORMAL);



    original_font_desc->style = POPPLER_STYLE_ITALIC;

    original_font_desc->weight = POPPLER_WEIGHT_ULTRABOLD;

    copied_font_desc = poppler_font_description_copy(original_font_desc);

    EXPECT_EQ(copied_font_desc->style, POPPLER_STYLE_ITALIC);

    EXPECT_EQ(copied_font_desc->weight, POPPLER_WEIGHT_ULTRABOLD);

}



// Test boundary condition: different stretch values

TEST_F(PopplerFontDescriptionTest_2126, DifferentStretchValues_2126) {

    original_font_desc->stretch = POPPLER_STRETCH_CONDENSED;

    copied_font_desc = poppler_font_description_copy(original_font_desc);

    EXPECT_EQ(copied_font_desc->stretch, POPPLER_STRETCH_CONDENSED);



    original_font_desc->stretch = POPPLER_STRETCH_EXPANDED;

    copied_font_desc = poppler_font_description_copy(original_font_desc);

    EXPECT_EQ(copied_font_desc->stretch, POPPLER_STRETCH_EXPANDED);

}
