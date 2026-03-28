#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"
#include <memory>
#include <string>
#include <array>

// Test fixture for GfxFont static methods and basic operations
class GfxFontTest_1152 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test isBase14Font with known base14 font families
TEST_F(GfxFontTest_1152, IsBase14Font_TimesRoman_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Roman"));
}

TEST_F(GfxFontTest_1152, IsBase14Font_TimesBold_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Bold"));
}

TEST_F(GfxFontTest_1152, IsBase14Font_TimesItalic_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Italic"));
}

TEST_F(GfxFontTest_1152, IsBase14Font_TimesBoldItalic_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "BoldItalic"));
}

TEST_F(GfxFontTest_1152, IsBase14Font_Helvetica_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", ""));
}

TEST_F(GfxFontTest_1152, IsBase14Font_HelveticaBold_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Bold"));
}

TEST_F(GfxFontTest_1152, IsBase14Font_Courier_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", ""));
}

TEST_F(GfxFontTest_1152, IsBase14Font_CourierBold_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "Bold"));
}

TEST_F(GfxFontTest_1152, IsBase14Font_Symbol_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Symbol", ""));
}

TEST_F(GfxFontTest_1152, IsBase14Font_ZapfDingbats_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("ZapfDingbats", ""));
}

TEST_F(GfxFontTest_1152, IsBase14Font_UnknownFont_1152) {
    EXPECT_FALSE(GfxFont::isBase14Font("Arial", ""));
}

TEST_F(GfxFontTest_1152, IsBase14Font_UnknownFamily_1152) {
    EXPECT_FALSE(GfxFont::isBase14Font("ComicSans", "Regular"));
}

TEST_F(GfxFontTest_1152, IsBase14Font_EmptyStrings_1152) {
    EXPECT_FALSE(GfxFont::isBase14Font("", ""));
}

TEST_F(GfxFontTest_1152, IsBase14Font_RandomString_1152) {
    EXPECT_FALSE(GfxFont::isBase14Font("RandomFont", "RandomStyle"));
}

// Test getAlternateName with known font names
TEST_F(GfxFontTest_1152, GetAlternateName_NullInput_1152) {
    const char *result = GfxFont::getAlternateName(nullptr);
    // Should handle null gracefully - either return nullptr or some default
    // We just verify it doesn't crash
    (void)result;
}

TEST_F(GfxFontTest_1152, GetAlternateName_UnknownFont_1152) {
    const char *result = GfxFont::getAlternateName("SomeUnknownFont");
    // For unknown fonts, result might be nullptr
    // Just verify no crash
    (void)result;
}

TEST_F(GfxFontTest_1152, GetAlternateName_KnownFont_1152) {
    const char *result = GfxFont::getAlternateName("Helvetica");
    // May return an alternate name or nullptr
    (void)result;
}

// Test makeFont with nullptr parameters to verify error handling
TEST_F(GfxFontTest_1152, MakeFont_NullDict_1152) {
    Ref id = {0, 0};
    auto font = GfxFont::makeFont(nullptr, "F1", id, nullptr);
    // With null dict, font creation should fail or return nullptr
    EXPECT_EQ(font, nullptr);
}

// Test with a minimal valid Dict setup
TEST_F(GfxFontTest_1152, MakeFont_MinimalType1Font_1152) {
    // Create a minimal font dictionary for a Type1 font
    // This tests that makeFont can handle a basic font dictionary
    Ref id = {1, 0};
    
    // Without a proper XRef and Dict, we expect nullptr or an invalid font
    auto font = GfxFont::makeFont(nullptr, "F1", id, nullptr);
    if (font) {
        // If somehow a font is created, verify basic properties
        EXPECT_EQ(font->getTag(), "F1");
        const Ref *fontId = font->getID();
        EXPECT_NE(fontId, nullptr);
        if (fontId) {
            EXPECT_EQ(fontId->num, 1);
            EXPECT_EQ(fontId->gen, 0);
        }
    }
}

// Test Ref-based matching
TEST_F(GfxFontTest_1152, IsBase14Font_CourierOblique_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "Oblique"));
}

TEST_F(GfxFontTest_1152, IsBase14Font_HelveticaOblique_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Oblique"));
}

TEST_F(GfxFontTest_1152, IsBase14Font_HelveticaBoldOblique_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "BoldOblique"));
}

TEST_F(GfxFontTest_1152, IsBase14Font_CourierBoldOblique_1152) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "BoldOblique"));
}

// Boundary: very long font name
TEST_F(GfxFontTest_1152, IsBase14Font_VeryLongFamilyName_1152) {
    std::string longName(10000, 'A');
    EXPECT_FALSE(GfxFont::isBase14Font(longName, ""));
}

// Boundary: very long style name
TEST_F(GfxFontTest_1152, IsBase14Font_VeryLongStyleName_1152) {
    std::string longStyle(10000, 'B');
    EXPECT_FALSE(GfxFont::isBase14Font("Helvetica", longStyle));
}

// Test case sensitivity for isBase14Font
TEST_F(GfxFontTest_1152, IsBase14Font_LowercaseHelvetica_1152) {
    // Depending on implementation, lowercase might not match
    bool result = GfxFont::isBase14Font("helvetica", "");
    // We just verify it doesn't crash; the actual behavior depends on implementation
    (void)result;
}

TEST_F(GfxFontTest_1152, IsBase14Font_MixedCaseTimesRoman_1152) {
    bool result = GfxFont::isBase14Font("times", "roman");
    (void)result;
}

// Test getAlternateName with known base14 names
TEST_F(GfxFontTest_1152, GetAlternateName_TimesNewRoman_1152) {
    const char *result = GfxFont::getAlternateName("Times-Roman");
    // Should potentially return an alternate name
    (void)result;
}

TEST_F(GfxFontTest_1152, GetAlternateName_CourierNew_1152) {
    const char *result = GfxFont::getAlternateName("Courier");
    (void)result;
}

TEST_F(GfxFontTest_1152, GetAlternateName_EmptyString_1152) {
    const char *result = GfxFont::getAlternateName("");
    (void)result;
}
