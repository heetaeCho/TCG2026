#include <gtest/gtest.h>

#include "poppler-page.h"

#include "poppler-annot.h"



class PopplerAnnotFreeTextTest_2102 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_annot = new PopplerAnnotFreeText();

    }



    void TearDown() override {

        delete poppler_annot;

    }



    PopplerAnnotFreeText* poppler_annot;

};



TEST_F(PopplerAnnotFreeTextTest_2102, SetFontColor_NormalOperation_2102) {

    PopplerColor color = {255, 0, 0}; // Red

    poppler_annot_free_text_set_font_color(poppler_annot, &color);

    EXPECT_EQ(poppler_annot->font_color.red, 255);

    EXPECT_EQ(poppler_annot->font_color.green, 0);

    EXPECT_EQ(poppler_annot->font_color.blue, 0);

}



TEST_F(PopplerAnnotFreeTextTest_2102, SetFontColor_BoundaryConditions_2102) {

    PopplerColor color = {0, 0, 0}; // Black

    poppler_annot_free_text_set_font_color(poppler_annot, &color);

    EXPECT_EQ(poppler_annot->font_color.red, 0);

    EXPECT_EQ(poppler_annot->font_color.green, 0);

    EXPECT_EQ(poppler_annot->font_color.blue, 0);



    color = {255, 255, 255}; // White

    poppler_annot_free_text_set_font_color(poppler_annot, &color);

    EXPECT_EQ(poppler_annot->font_color.red, 255);

    EXPECT_EQ(poppler_annot->font_color.green, 255);

    EXPECT_EQ(poppler_annot->font_color.blue, 255);

}



TEST_F(PopplerAnnotFreeTextTest_2102, SetFontColor_ExceptionalCases_2102) {

    PopplerColor* null_color = nullptr;

    // Assuming the function handles null pointers gracefully

    poppler_annot_free_text_set_font_color(poppler_annot, null_color);

    // No assertion needed if no crash occurs

}
