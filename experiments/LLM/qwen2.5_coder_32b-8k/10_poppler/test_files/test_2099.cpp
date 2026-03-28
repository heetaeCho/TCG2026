#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.cc"

#include "Catalog.h"

#include "Annot.h"

#include "Form.h"

#include "PDFDoc.h"



using namespace testing;



class PopplerAnnotFreeTextTest : public ::testing::Test {

protected:

    void SetUp() override {

        pdf_doc = new PDFDoc();

        catalog = new Catalog(pdf_doc);

        annot = new AnnotFreeText(pdf_doc, nullptr);

        poppler_annot = new _PopplerAnnotFreeText();

        POPPLER_ANNOT(poppler_annot)->annot.reset(annot);

    }



    void TearDown() override {

        delete poppler_annot;

        delete catalog;

        delete pdf_doc;

    }



    PDFDoc* pdf_doc;

    Catalog* catalog;

    AnnotFreeText* annot;

    _PopplerAnnotFreeText* poppler_annot;

};



TEST_F(PopplerAnnotFreeTextTest_SetDAToNative_NormalOperation_2099, NormalFontAndSize) {

    poppler_annot->font_desc = new PopplerFontDescription();

    poppler_annot->font_desc->font_name = strdup("Arial");

    poppler_annot->font_desc->size_pt = 14.0;

    poppler_annot_free_text_set_da_to_native(poppler_annot);

    const DefaultAppearance& da = ((AnnotFreeText*)POPPLER_ANNOT(poppler_annot)->annot.get())->getDefaultAppearance();

    EXPECT_EQ(da.getFontName(), "Arial");

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 14.0);

}



TEST_F(PopplerAnnotFreeTextTest_SetDAToNative_BoundaryConditions_2099, NullFontDescription) {

    poppler_annot_free_text_set_da_to_native(poppler_annot);

    const DefaultAppearance& da = ((AnnotFreeText*)POPPLER_ANNOT(poppler_annot)->annot.get())->getDefaultAppearance();

    EXPECT_EQ(da.getFontName(), "Sans");

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);

}



TEST_F(PopplerAnnotFreeTextTest_SetDAToNative_BoundaryConditions_2099, EmptyFontName) {

    poppler_annot->font_desc = new PopplerFontDescription();

    poppler_annot->font_desc->font_name = strdup("");

    poppler_annot_free_text_set_da_to_native(poppler_annot);

    const DefaultAppearance& da = ((AnnotFreeText*)POPPLER_ANNOT(poppler_annot)->annot.get())->getDefaultAppearance();

    EXPECT_EQ(da.getFontName(), "Sans");

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);

}



TEST_F(PopplerAnnotFreeTextTest_SetDAToNative_BoundaryConditions_2099, ZeroFontSize) {

    poppler_annot->font_desc = new PopplerFontDescription();

    poppler_annot->font_desc->font_name = strdup("Arial");

    poppler_annot->font_desc->size_pt = 0.0;

    poppler_annot_free_text_set_da_to_native(poppler_annot);

    const DefaultAppearance& da = ((AnnotFreeText*)POPPLER_ANNOT(poppler_annot)->annot.get())->getDefaultAppearance();

    EXPECT_EQ(da.getFontName(), "Arial");

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);

}



TEST_F(PopplerAnnotFreeTextTest_SetDAToNative_BoundaryConditions_2099, NegativeFontSize) {

    poppler_annot->font_desc = new PopplerFontDescription();

    poppler_annot->font_desc->font_name = strdup("Arial");

    poppler_annot->font_desc->size_pt = -14.0;

    poppler_annot_free_text_set_da_to_native(poppler_annot);

    const DefaultAppearance& da = ((AnnotFreeText*)POPPLER_ANNOT(poppler_annot)->annot.get())->getDefaultAppearance();

    EXPECT_EQ(da.getFontName(), "Arial");

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);

}



TEST_F(PopplerAnnotFreeTextTest_SetDAToNative_ExternalFontHandling_2099, FontNotFoundInDocument) {

    poppler_annot->font_desc = new PopplerFontDescription();

    poppler_annot->font_desc->font_name = strdup("NonExistentFont");

    poppler_annot_free_text_set_da_to_native(poppler_annot);

    const DefaultAppearance& da = ((AnnotFreeText*)POPPLER_ANNOT(poppler_annot)->annot.get())->getDefaultAppearance();

    EXPECT_EQ(da.getFontName(), "NonExistentFont");

    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 14.0);

}



TEST_F(PopplerAnnotFreeTextTest_SetDAToNative_FontColorHandling_2099, DefaultFontColor) {

    poppler_annot->font_color.red = 0;

    poppler_annot->font_color.green = 0;

    poppler_annot->font_color.blue = 0;

    poppler_annot_free_text_set_da_to_native(poppler_annot);

    // Assuming the default color is not modified by the function

}



TEST_F(PopplerAnnotFreeTextTest_SetDAToNative_FontColorHandling_2099, CustomFontColor) {

    poppler_annot->font_color.red = 1;

    poppler_annot->font_color.green = 0.5;

    poppler_annot->font_color.blue = 0;

    poppler_annot_free_text_set_da_to_native(poppler_annot);

    // Assuming the color is not modified by the function

}
