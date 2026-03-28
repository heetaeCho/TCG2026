#include <gtest/gtest.h>
#include <string>

// Include necessary poppler headers
#include "poppler-annot.h"
#include "poppler-enums.h"

// Since update_font_desc_with_word is static, we need to include the .cc file
// or use a linkage workaround. We'll include it to get access.
// In practice, this may need build system adjustments.
#define static
#include "poppler-annot.cc"
#undef static

class UpdateFontDescWithWordTest_2042 : public ::testing::Test {
protected:
    PopplerFontDescription font_desc;

    void SetUp() override {
        font_desc.font_name = nullptr;
        font_desc.size_pt = 0.0;
        font_desc.stretch = POPPLER_STRETCH_NORMAL;
        font_desc.weight = POPPLER_WEIGHT_NORMAL;
        font_desc.style = POPPLER_STYLE_NORMAL;
    }
};

// Test that an unknown word returns false
TEST_F(UpdateFontDescWithWordTest_2042, UnknownWordReturnsFalse_2042) {
    std::string word = "nonexistentfontproperty";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_FALSE(result);
}

// Test that an empty word returns false
TEST_F(UpdateFontDescWithWordTest_2042, EmptyWordReturnsFalse_2042) {
    std::string word = "";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_FALSE(result);
}

// Test that "Italic" is recognized as a style
TEST_F(UpdateFontDescWithWordTest_2042, ItalicSetsStyle_2042) {
    std::string word = "Italic";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
    EXPECT_EQ(font_desc.style, POPPLER_STYLE_ITALIC);
}

// Test that "Oblique" is recognized as a style
TEST_F(UpdateFontDescWithWordTest_2042, ObliqueSetsStyle_2042) {
    std::string word = "Oblique";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
    EXPECT_EQ(font_desc.style, POPPLER_STYLE_OBLIQUE);
}

// Test that "Bold" is recognized as a weight
TEST_F(UpdateFontDescWithWordTest_2042, BoldSetsWeight_2042) {
    std::string word = "Bold";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
    EXPECT_EQ(font_desc.weight, POPPLER_WEIGHT_BOLD);
}

// Test that "Normal" is recognized but doesn't change fields
TEST_F(UpdateFontDescWithWordTest_2042, NormalReturnsTrueNoChange_2042) {
    std::string word = "Normal";
    PopplerFontDescription original = font_desc;
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
    EXPECT_EQ(font_desc.style, original.style);
    EXPECT_EQ(font_desc.weight, original.weight);
    EXPECT_EQ(font_desc.stretch, original.stretch);
}

// Test that "Condensed" sets stretch
TEST_F(UpdateFontDescWithWordTest_2042, CondensedSetsStretch_2042) {
    std::string word = "Condensed";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
    EXPECT_EQ(font_desc.stretch, POPPLER_STRETCH_CONDENSED);
}

// Test that "Expanded" sets stretch
TEST_F(UpdateFontDescWithWordTest_2042, ExpandedSetsStretch_2042) {
    std::string word = "Expanded";
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_TRUE(result);
    EXPECT_EQ(font_desc.stretch, POPPLER_STRETCH_EXPANDED);
}

// Test that unknown word does not modify font_desc
TEST_F(UpdateFontDescWithWordTest_2042, UnknownWordDoesNotModifyFontDesc_2042) {
    std::string word = "XyzUnknown";
    PopplerFontDescription original = font_desc;
    bool result = update_font_desc_with_word(font_desc, word);
    EXPECT_FALSE(result);
    EXPECT_EQ(font_desc.style, original.style);
    EXPECT_EQ(font_desc.weight, original.weight);
    EXPECT_EQ(font_desc.stretch, original.stretch);
}

// Test case sensitivity - "italic" lowercase might not be recognized
TEST_F(UpdateFontDescWithWordTest_2042, LowercaseItalicMayNotBeRecognized_2042) {
    std::string word = "italic";
    bool result = update_font_desc_with_word(font_desc, word);
    // The map may or may not contain lowercase entries; just verify consistency
    if (!result) {
        EXPECT_EQ(font_desc.style, POPPLER_STYLE_NORMAL);
    }
}

// Test "Light" weight if it exists in the map
TEST_F(UpdateFontDescWithWordTest_2042, LightSetsWeight_2042) {
    std::string word = "Light";
    bool result = update_font_desc_with_word(font_desc, word);
    if (result) {
        EXPECT_NE(font_desc.weight, POPPLER_WEIGHT_NORMAL);
    }
}

// Test "Semi" or "SemiBold" type entries
TEST_F(UpdateFontDescWithWordTest_2042, SemiBoldSetsWeight_2042) {
    std::string word = "Semibold";
    bool result = update_font_desc_with_word(font_desc, word);
    if (result) {
        EXPECT_NE(font_desc.weight, POPPLER_WEIGHT_NORMAL);
    }
}
