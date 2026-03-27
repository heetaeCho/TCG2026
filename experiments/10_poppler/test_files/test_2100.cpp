#include <gtest/gtest.h>

#include "poppler-annot.h"



class PopplerAnnotFreeTextTest_2100 : public ::testing::Test {

protected:

    void SetUp() override {

        font_desc = poppler_font_description_new();

        font_desc->font_name = strdup("Arial");

        font_desc->size_pt = 12.0;

        font_desc->stretch = POPPLER_STRETCH_NORMAL;

        font_desc->weight = POPPLER_WEIGHT_NORMAL;

        font_desc->style = POPPLER_STYLE_NORMAL;



        new_font_desc = poppler_font_description_new();

        new_font_desc->font_name = strdup("Times New Roman");

        new_font_desc->size_pt = 14.0;

        new_font_desc->stretch = POPPLER_STRETCH_EXPANDED;

        new_font_desc->weight = POPPLER_WEIGHT_BOLD;

        new_font_desc->style = POPPLER_STYLE_ITALIC;



        annot_free_text = (PopplerAnnotFreeText *)malloc(sizeof(PopplerAnnotFreeText));

        annot_free_text->font_desc = nullptr;

    }



    void TearDown() override {

        if (annot_free_text->font_desc) {

            poppler_font_description_free(annot_free_text->font_desc);

        }

        free(annot_free_text);

        poppler_font_description_free(font_desc);

        poppler_font_description_free(new_font_desc);

    }



    PopplerAnnotFreeText *annot_free_text;

    PopplerFontDescription *font_desc;

    PopplerFontDescription *new_font_desc;

};



TEST_F(PopplerAnnotFreeTextTest_2100, SetFontDesc_NormalOperation_2100) {

    poppler_annot_free_text_set_font_desc(annot_free_text, font_desc);

    EXPECT_STREQ(font_desc->font_name, annot_free_text->font_desc->font_name);

    EXPECT_EQ(font_desc->size_pt, annot_free_text->font_desc->size_pt);

    EXPECT_EQ(font_desc->stretch, annot_free_text->font_desc->stretch);

    EXPECT_EQ(font_desc->weight, annot_free_text->font_desc->weight);

    EXPECT_EQ(font_desc->style, annot_free_text->font_desc->style);

}



TEST_F(PopplerAnnotFreeTextTest_2100, SetFontDesc_UpdateExistingFontDesc_2100) {

    poppler_annot_free_text_set_font_desc(annot_free_text, font_desc);

    poppler_annot_free_text_set_font_desc(annot_free_text, new_font_desc);

    EXPECT_STREQ(new_font_desc->font_name, annot_free_text->font_desc->font_name);

    EXPECT_EQ(new_font_desc->size_pt, annot_free_text->font_desc->size_pt);

    EXPECT_EQ(new_font_desc->stretch, annot_free_text->font_desc->stretch);

    EXPECT_EQ(new_font_desc->weight, annot_free_text->font_desc->weight);

    EXPECT_EQ(new_font_desc->style, annot_free_text->font_desc->style);

}



TEST_F(PopplerAnnotFreeTextTest_2100, SetFontDesc_NullFontDesc_2100) {

    poppler_annot_free_text_set_font_desc(annot_free_text, font_desc);

    poppler_annot_free_text_set_font_desc(annot_free_text, nullptr);

    EXPECT_EQ(nullptr, annot_free_text->font_desc);

}



TEST_F(PopplerAnnotFreeTextTest_2100, SetFontDesc_BoundaryConditionEmptyFontName_2100) {

    font_desc->font_name = strdup("");

    poppler_annot_free_text_set_font_desc(annot_free_text, font_desc);

    EXPECT_STREQ(font_desc->font_name, annot_free_text->font_desc->font_name);

}
