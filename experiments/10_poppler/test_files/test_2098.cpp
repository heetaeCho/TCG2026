#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-annot.h"



// Mocking the PopplerFontDescription struct for easier test setup

struct MockPopplerFontDescription : public _PopplerFontDescription {

    MockPopplerFontDescription(const char* font_name, double size_pt, PopplerStretch stretch, PopplerWeight weight, PopplerStyle style)

        : font_name(strdup(font_name)), size_pt(size_pt), stretch(stretch), weight(weight), style(style) {}

    ~MockPopplerFontDescription() { free(font_name); }

};



TEST(poppler_font_description_to_style_2098, NormalOperation_NormalWeightAndStyle_2098) {

    MockPopplerFontDescription font_desc("Arial", 12.0, POPPLER_STRETCH_NORMAL, POPPLER_WEIGHT_NORMAL, POPPLER_STYLE_NORMAL);

    EXPECT_EQ(poppler_font_description_to_style(&font_desc), "");

}



TEST(poppler_font_description_to_style_2098, NormalOperation_BoldWeightAndItalicStyle_2098) {

    MockPopplerFontDescription font_desc("Arial", 12.0, POPPLER_STRETCH_NORMAL, POPPLER_WEIGHT_BOLD, POPPLER_STYLE_ITALIC);

    EXPECT_EQ(poppler_font_description_to_style(&font_desc), "Bold Italic");

}



TEST(poppler_font_description_to_style_2098, BoundaryCondition_ThinWeightAndNormalStyle_2098) {

    MockPopplerFontDescription font_desc("Arial", 12.0, POPPLER_STRETCH_NORMAL, POPPLER_WEIGHT_THIN, POPPLER_STYLE_NORMAL);

    EXPECT_EQ(poppler_font_description_to_style(&font_desc), "Thin");

}



TEST(poppler_font_description_to_style_2098, BoundaryCondition_HeavyWeightAndObliqueStyle_2098) {

    MockPopplerFontDescription font_desc("Arial", 12.0, POPPLER_STRETCH_NORMAL, POPPLER_WEIGHT_HEAVY, POPPLER_STYLE_OBLIQUE);

    EXPECT_EQ(poppler_font_description_to_style(&font_desc), "Heavy Oblique");

}



TEST(poppler_font_description_to_style_2098, BoundaryCondition_SemiExpandedStretchAndNormalStyle_2098) {

    MockPopplerFontDescription font_desc("Arial", 12.0, POPPLER_STRETCH_SEMIEXPANDED, POPPLER_WEIGHT_NORMAL, POPPLER_STYLE_NORMAL);

    EXPECT_EQ(poppler_font_description_to_style(&font_desc), "SemiExpanded");

}



TEST(poppler_font_description_to_style_2098, ExceptionalCase_EmptyFontNameAndNormalWeightAndStyle_2098) {

    MockPopplerFontDescription font_desc("", 12.0, POPPLER_STRETCH_NORMAL, POPPLER_WEIGHT_NORMAL, POPPLER_STYLE_NORMAL);

    EXPECT_EQ(poppler_font_description_to_style(&font_desc), "");

}
