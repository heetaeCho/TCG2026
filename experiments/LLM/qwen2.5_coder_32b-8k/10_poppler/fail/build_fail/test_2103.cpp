#include <gtest/gtest.h>

#include "poppler-annot.h"

#include <gmock/gmock.h>



// Mocking external collaborators if needed (none in this case)



class PopplerAnnotFreeTextTest_2103 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_annot = g_new(PopplerAnnotFreeText, 1);

        // Initialize with a known color

        poppler_annot->font_color.red = 0.5;

        poppler_annot->font_color.green = 0.5;

        poppler_annot->font_color.blue = 0.5;

    }



    void TearDown() override {

        g_free(poppler_annot);

    }



    PopplerAnnotFreeText *poppler_annot;

};



TEST_F(PopplerAnnotFreeTextTest_2103, GetFontColor_ReturnsCorrectColor_2103) {

    PopplerColor* color = poppler_annot_free_text_get_font_color(poppler_annot);

    EXPECT_FLOAT_EQ(color->red, 0.5f);

    EXPECT_FLOAT_EQ(color->green, 0.5f);

    EXPECT_FLOAT_EQ(color->blue, 0.5f);

    g_free(color);

}



TEST_F(PopplerAnnotFreeTextTest_2103, GetFontColor_ReturnsNewInstance_2103) {

    PopplerColor* color1 = poppler_annot_free_text_get_font_color(poppler_annot);

    PopplerColor* color2 = poppler_annot_free_text_get_font_color(poppler_annot);

    EXPECT_NE(color1, color2);

    g_free(color1);

    g_free(color2);

}



TEST_F(PopplerAnnotFreeTextTest_2103, GetFontColor_BoundaryConditions_2103) {

    // Test with zero values

    poppler_annot->font_color.red = 0.0;

    poppler_annot->font_color.green = 0.0;

    poppler_annot->font_color.blue = 0.0;

    PopplerColor* color = poppler_annot_free_text_get_font_color(poppler_annot);

    EXPECT_FLOAT_EQ(color->red, 0.0f);

    EXPECT_FLOAT_EQ(color->green, 0.0f);

    EXPECT_FLOAT_EQ(color->blue, 0.0f);

    g_free(color);



    // Test with max values

    poppler_annot->font_color.red = 1.0;

    poppler_annot->font_color.green = 1.0;

    poppler_annot->font_color.blue = 1.0;

    color = poppler_annot_free_text_get_font_color(poppler_annot);

    EXPECT_FLOAT_EQ(color->red, 1.0f);

    EXPECT_FLOAT_EQ(color->green, 1.0f);

    EXPECT_FLOAT_EQ(color->blue, 1.0f);

    g_free(color);

}



// Assuming no exceptional cases are observable through the interface for this function
