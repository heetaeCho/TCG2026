#include <gtest/gtest.h>
#include <cstring>
#include <functional>
#include <string>

#include "poppler-annot.h"

// Test Fixture
class PopplerFontDescriptionTest_2098 : public ::testing::Test {
protected:
    // You can add setup code if needed, for example, initializing some variables
    PopplerFontDescription font_desc;
};

// TEST_F(WriteBatchTest_85, PutIncreasesCount_85) style naming convention used for test names.
TEST_F(PopplerFontDescriptionTest_2098, PopplerFontDescriptionToStyle_Thin_2098) {
    // Test for POPPLER_WEIGHT_THIN
    font_desc.weight = POPPLER_WEIGHT_THIN;
    font_desc.style = POPPLER_STYLE_NORMAL;
    font_desc.stretch = 4; // Assuming 'Normal' stretch as example
    
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Thin");
}

TEST_F(PopplerFontDescriptionTest_2098, PopplerFontDescriptionToStyle_Bold_2098) {
    // Test for POPPLER_WEIGHT_BOLD
    font_desc.weight = POPPLER_WEIGHT_BOLD;
    font_desc.style = POPPLER_STYLE_NORMAL;
    font_desc.stretch = 4; // Assuming 'Normal' stretch as example
    
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Bold");
}

TEST_F(PopplerFontDescriptionTest_2098, PopplerFontDescriptionToStyle_Italic_2098) {
    // Test for POPPLER_WEIGHT_NORMAL with POPPLER_STYLE_ITALIC
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    font_desc.style = POPPLER_STYLE_ITALIC;
    font_desc.stretch = 4; // Assuming 'Normal' stretch as example
    
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Italic");
}

TEST_F(PopplerFontDescriptionTest_2098, PopplerFontDescriptionToStyle_Oblique_2098) {
    // Test for POPPLER_WEIGHT_NORMAL with POPPLER_STYLE_OBLIQUE
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    font_desc.style = POPPLER_STYLE_OBLIQUE;
    font_desc.stretch = 4; // Assuming 'Normal' stretch as example
    
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Oblique");
}

TEST_F(PopplerFontDescriptionTest_2098, PopplerFontDescriptionToStyle_Heavy_2098) {
    // Test for POPPLER_WEIGHT_HEAVY
    font_desc.weight = POPPLER_WEIGHT_HEAVY;
    font_desc.style = POPPLER_STYLE_NORMAL;
    font_desc.stretch = 4; // Assuming 'Normal' stretch as example
    
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Heavy");
}

TEST_F(PopplerFontDescriptionTest_2098, PopplerFontDescriptionToStyle_EmptyStretch_2098) {
    // Test for empty stretch, this should result in an empty string for stretch
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    font_desc.style = POPPLER_STYLE_NORMAL;
    font_desc.stretch = 4; // Corresponding to "Normal" stretch
    
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "");
}

TEST_F(PopplerFontDescriptionTest_2098, PopplerFontDescriptionToStyle_CondensedStretch_2098) {
    // Test for a condensed stretch type
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    font_desc.style = POPPLER_STYLE_NORMAL;
    font_desc.stretch = 2; // Corresponding to "Condensed"
    
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Condensed");
}

TEST_F(PopplerFontDescriptionTest_2098, PopplerFontDescriptionToStyle_ExpandedStretch_2098) {
    // Test for expanded stretch
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    font_desc.style = POPPLER_STYLE_NORMAL;
    font_desc.stretch = 6; // Corresponding to "Expanded"
    
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "Expanded");
}

TEST_F(PopplerFontDescriptionTest_2098, PopplerFontDescriptionToStyle_UltraCondensedStretch_2098) {
    // Test for ultra-condensed stretch
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    font_desc.style = POPPLER_STYLE_NORMAL;
    font_desc.stretch = 0; // Corresponding to "UltraCondensed"
    
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "UltraCondensed");
}

TEST_F(PopplerFontDescriptionTest_2098, PopplerFontDescriptionToStyle_ExtraExpandedStretch_2098) {
    // Test for extra-expanded stretch
    font_desc.weight = POPPLER_WEIGHT_NORMAL;
    font_desc.style = POPPLER_STYLE_NORMAL;
    font_desc.stretch = 7; // Corresponding to "ExtraExpanded"
    
    std::string result = poppler_font_description_to_style(&font_desc);
    EXPECT_EQ(result, "ExtraExpanded");
}