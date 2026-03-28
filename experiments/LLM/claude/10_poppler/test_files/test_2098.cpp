#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary headers and the source to access the static function
// We need the enums and struct definitions
#include "poppler-annot.h"

// Since the function is static, we include the .cc file to access it
// This is a testing workaround for static functions
#include "poppler-annot.cc"

class PopplerFontDescriptionToStyleTest_2098 : public ::testing::Test {
protected:
    PopplerFontDescription font_desc;

    void SetUp() override {
        font_desc.font_name = nullptr;
        font_desc.size_pt = 12.0;
        font_desc.stretch = static_cast<PopplerStretch>(4); // Normal stretch (empty string)
        font_desc.weight = POPPLER_WEIGHT_NORMAL;
        font_desc.style = POPPLER_STYLE_NORMAL;
    }
};

// Test: Normal weight, normal style, normal stretch => empty string
TEST_F(PopplerFontDescriptionToStyleTest_2098, NormalWeightNormalStyleNormalStretch_2098) {
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    font_desc.style = POPPLER_STYLE_NORMAL;
    font_desc.stretch = static_cast<PopplerStretch>(4);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "");
}

// Weight tests with normal stretch and normal style
TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightThin_2098) {
    font_desc.weight = POPPLER_WEIGHT_THIN;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Thin");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightBelowThin_2098) {
    font_desc.weight = static_cast<PopplerWeight>(50);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Thin");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightUltraLight_2098) {
    font_desc.weight = POPPLER_WEIGHT_ULTRALIGHT;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "UltraLight");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightBetweenThinAndUltraLight_2098) {
    font_desc.weight = static_cast<PopplerWeight>(150);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "UltraLight");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightLight_2098) {
    font_desc.weight = POPPLER_WEIGHT_LIGHT;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Light");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightNormal_2098) {
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightMedium_2098) {
    font_desc.weight = POPPLER_WEIGHT_MEDIUM;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Medium");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightSemiBold_2098) {
    font_desc.weight = POPPLER_WEIGHT_SEMIBOLD;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "SemiBold");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightBold_2098) {
    font_desc.weight = POPPLER_WEIGHT_BOLD;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Bold");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightUltraBold_2098) {
    font_desc.weight = POPPLER_WEIGHT_ULTRABOLD;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "UltraBold");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightHeavy_2098) {
    font_desc.weight = POPPLER_WEIGHT_HEAVY;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Heavy");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightAboveHeavy_2098) {
    font_desc.weight = static_cast<PopplerWeight>(1000);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Heavy");
}

// Style tests
TEST_F(PopplerFontDescriptionToStyleTest_2098, StyleItalicWithNormalWeight_2098) {
    font_desc.style = POPPLER_STYLE_ITALIC;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Italic");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, StyleObliqueWithNormalWeight_2098) {
    font_desc.style = POPPLER_STYLE_OBLIQUE;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Oblique");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, BoldItalic_2098) {
    font_desc.weight = POPPLER_WEIGHT_BOLD;
    font_desc.style = POPPLER_STYLE_ITALIC;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Bold Italic");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, BoldOblique_2098) {
    font_desc.weight = POPPLER_WEIGHT_BOLD;
    font_desc.style = POPPLER_STYLE_OBLIQUE;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Bold Oblique");
}

// Stretch tests
TEST_F(PopplerFontDescriptionToStyleTest_2098, StretchUltraCondensed_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(0);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "UltraCondensed");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, StretchExtraCondensed_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(1);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "ExtraCondensed");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, StretchCondensed_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(2);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Condensed");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, StretchSemiCondensed_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(3);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "SemiCondensed");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, StretchSemiExpanded_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(5);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "SemiExpanded");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, StretchExpanded_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(6);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Expanded");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, StretchExtraExpanded_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(7);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "ExtraExpanded");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, StretchUltraExpanded_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(8);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "UltraExpanded");
}

// Combined stretch + weight + style
TEST_F(PopplerFontDescriptionToStyleTest_2098, CondensedBoldItalic_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(2);
    font_desc.weight = POPPLER_WEIGHT_BOLD;
    font_desc.style = POPPLER_STYLE_ITALIC;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Condensed Bold Italic");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, SemiExpandedMediumOblique_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(5);
    font_desc.weight = POPPLER_WEIGHT_MEDIUM;
    font_desc.style = POPPLER_STYLE_OBLIQUE;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "SemiExpanded Medium Oblique");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, UltraCondensedHeavyItalic_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(0);
    font_desc.weight = static_cast<PopplerWeight>(950);
    font_desc.style = POPPLER_STYLE_ITALIC;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "UltraCondensed Heavy Italic");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, StretchWithNormalWeightAndNormalStyle_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(2);
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    font_desc.style = POPPLER_STYLE_NORMAL;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Condensed");
}

// Boundary: weight exactly at boundary values
TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightExactly101_2098) {
    font_desc.weight = static_cast<PopplerWeight>(101);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "UltraLight");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightExactly201_2098) {
    font_desc.weight = static_cast<PopplerWeight>(201);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Light");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightExactly301_2098) {
    font_desc.weight = static_cast<PopplerWeight>(301);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightExactly401_2098) {
    font_desc.weight = static_cast<PopplerWeight>(401);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Medium");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightExactly501_2098) {
    font_desc.weight = static_cast<PopplerWeight>(501);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "SemiBold");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightExactly601_2098) {
    font_desc.weight = static_cast<PopplerWeight>(601);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Bold");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightExactly701_2098) {
    font_desc.weight = static_cast<PopplerWeight>(701);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "UltraBold");
}

TEST_F(PopplerFontDescriptionToStyleTest_2098, WeightExactly801_2098) {
    font_desc.weight = static_cast<PopplerWeight>(801);
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Heavy");
}

// Normal stretch with italic only
TEST_F(PopplerFontDescriptionToStyleTest_2098, NormalStretchNormalWeightItalic_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(4);
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    font_desc.style = POPPLER_STYLE_ITALIC;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Italic");
}

// Expanded stretch with thin weight and oblique
TEST_F(PopplerFontDescriptionToStyleTest_2098, ExpandedThinOblique_2098) {
    font_desc.stretch = static_cast<PopplerStretch>(6);
    font_desc.weight = POPPLER_WEIGHT_THIN;
    font_desc.style = POPPLER_STYLE_OBLIQUE;
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Expanded Thin Oblique");
}
