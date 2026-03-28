#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



// Assuming PopplerFontDescription is defined in poppler-annot.h or another included header

struct PopplerFontDescription {

    char *font_name;

    double size_pt;

    enum PopplerStretch stretch;

    enum PopplerStyle style;

    enum PopplerWeight weight;

};



extern "C" PopplerFontDescription *poppler_font_description_new(const char *font_name);



TEST(PopplerFontDescriptionTest_2124, CreateWithNormalValues_2124) {

    const char* fontName = "Arial";

    PopplerFontDescription* fontDesc = poppler_font_description_new(fontName);

    

    ASSERT_NE(fontDesc, nullptr);

    EXPECT_STREQ(fontDesc->font_name, fontName);

    EXPECT_DOUBLE_EQ(fontDesc->size_pt, 11.0);

    EXPECT_EQ(fontDesc->stretch, POPPLER_STRETCH_NORMAL);

    EXPECT_EQ(fontDesc->style, POPPLER_STYLE_NORMAL);

    EXPECT_EQ(fontDesc->weight, POPPLER_WEIGHT_NORMAL);



    g_free(fontDesc->font_name);

    g_free(fontDesc);

}



TEST(PopplerFontDescriptionTest_2124, CreateWithEmptyString_2124) {

    const char* fontName = "";

    PopplerFontDescription* fontDesc = poppler_font_description_new(fontName);

    

    ASSERT_NE(fontDesc, nullptr);

    EXPECT_STREQ(fontDesc->font_name, fontName);

    EXPECT_DOUBLE_EQ(fontDesc->size_pt, 11.0);

    EXPECT_EQ(fontDesc->stretch, POPPLER_STRETCH_NORMAL);

    EXPECT_EQ(fontDesc->style, POPPLER_STYLE_NORMAL);

    EXPECT_EQ(fontDesc->weight, POPPLER_WEIGHT_NORMAL);



    g_free(fontDesc->font_name);

    g_free(fontDesc);

}



TEST(PopplerFontDescriptionTest_2124, CreateWithLongString_2124) {

    const char* fontName = "AReallyLongFontNameThatMightBeUsedInSomeComplexScenarios";

    PopplerFontDescription* fontDesc = poppler_font_description_new(fontName);

    

    ASSERT_NE(fontDesc, nullptr);

    EXPECT_STREQ(fontDesc->font_name, fontName);

    EXPECT_DOUBLE_EQ(fontDesc->size_pt, 11.0);

    EXPECT_EQ(fontDesc->stretch, POPPLER_STRETCH_NORMAL);

    EXPECT_EQ(fontDesc->style, POPPLER_STYLE_NORMAL);

    EXPECT_EQ(fontDesc->weight, POPPLER_WEIGHT_NORMAL);



    g_free(fontDesc->font_name);

    g_free(fontDesc);

}



TEST(PopplerFontDescriptionTest_2124, CreateWithNullString_2124) {

    PopplerFontDescription* fontDesc = poppler_font_description_new(nullptr);

    

    ASSERT_NE(fontDesc, nullptr);

    EXPECT_STREQ(fontDesc->font_name, "");

    EXPECT_DOUBLE_EQ(fontDesc->size_pt, 11.0);

    EXPECT_EQ(fontDesc->stretch, POPPLER_STRETCH_NORMAL);

    EXPECT_EQ(fontDesc->style, POPPLER_STYLE_NORMAL);

    EXPECT_EQ(fontDesc->weight, POPPLER_WEIGHT_NORMAL);



    g_free(fontDesc->font_name);

    g_free(fontDesc);

}
