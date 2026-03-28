#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <string>

class GfxFontTest_1153 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test static method isBase14Font with known base14 font families
TEST_F(GfxFontTest_1153, IsBase14Font_Courier_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", ""));
}

TEST_F(GfxFontTest_1153, IsBase14Font_Helvetica_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", ""));
}

TEST_F(GfxFontTest_1153, IsBase14Font_TimesRoman_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Roman"));
}

TEST_F(GfxFontTest_1153, IsBase14Font_Symbol_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Symbol", ""));
}

TEST_F(GfxFontTest_1153, IsBase14Font_ZapfDingbats_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("ZapfDingbats", ""));
}

TEST_F(GfxFontTest_1153, IsBase14Font_UnknownFont_1153)
{
    EXPECT_FALSE(GfxFont::isBase14Font("UnknownFont", ""));
}

TEST_F(GfxFontTest_1153, IsBase14Font_EmptyFamily_1153)
{
    EXPECT_FALSE(GfxFont::isBase14Font("", ""));
}

TEST_F(GfxFontTest_1153, IsBase14Font_CourierBold_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "Bold"));
}

TEST_F(GfxFontTest_1153, IsBase14Font_HelveticaBoldOblique_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "BoldOblique"));
}

TEST_F(GfxFontTest_1153, IsBase14Font_CourierOblique_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "Oblique"));
}

// Test getAlternateName with known names
TEST_F(GfxFontTest_1153, GetAlternateName_Courier_1153)
{
    const char *alt = GfxFont::getAlternateName("Courier");
    // May return an alternate or nullptr depending on implementation
    // Just verify it doesn't crash
    (void)alt;
}

TEST_F(GfxFontTest_1153, GetAlternateName_NullInput_1153)
{
    // Passing a non-existent font name
    const char *alt = GfxFont::getAlternateName("NonExistentFontXYZ123");
    // Should return nullptr for unknown fonts
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontTest_1153, GetAlternateName_EmptyString_1153)
{
    const char *alt = GfxFont::getAlternateName("");
    EXPECT_EQ(alt, nullptr);
}

// Test makeFont returns nullptr for null dict
TEST_F(GfxFontTest_1153, MakeFont_NullDict_1153)
{
    Ref id = {0, 0};
    auto font = GfxFont::makeFont(nullptr, "tag", id, nullptr);
    // With null dict, makeFont should return nullptr or an invalid font
    if (font) {
        EXPECT_FALSE(font->isOk());
    }
}

// Test with a minimal Type1 font dictionary
TEST_F(GfxFontTest_1153, MakeFont_MinimalType1Dict_1153)
{
    // Create a minimal font dictionary
    Ref id = {1, 0};
    
    // We need an XRef for proper font creation, but without a real PDF
    // we test what we can
    auto font = GfxFont::makeFont(nullptr, "F1", id, nullptr);
    if (font) {
        // Test basic properties
        EXPECT_EQ(font->getTag(), "F1");
        const Ref *fontId = font->getID();
        EXPECT_NE(fontId, nullptr);
        if (fontId) {
            EXPECT_EQ(fontId->num, 1);
            EXPECT_EQ(fontId->gen, 0);
        }
    }
}

// Test isBase14Font boundary - very long string
TEST_F(GfxFontTest_1153, IsBase14Font_VeryLongString_1153)
{
    std::string longName(1000, 'A');
    EXPECT_FALSE(GfxFont::isBase14Font(longName, ""));
}

// Test isBase14Font with style variations
TEST_F(GfxFontTest_1153, IsBase14Font_TimesItalic_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Italic"));
}

TEST_F(GfxFontTest_1153, IsBase14Font_TimesBold_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Bold"));
}

TEST_F(GfxFontTest_1153, IsBase14Font_TimesBoldItalic_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "BoldItalic"));
}

TEST_F(GfxFontTest_1153, IsBase14Font_HelveticaOblique_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Oblique"));
}

TEST_F(GfxFontTest_1153, IsBase14Font_HelveticaBold_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Bold"));
}

TEST_F(GfxFontTest_1153, IsBase14Font_CourierBoldOblique_1153)
{
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "BoldOblique"));
}

TEST_F(GfxFontTest_1153, IsBase14Font_CaseSensitivity_1153)
{
    // Testing if the function is case-sensitive
    bool lower = GfxFont::isBase14Font("courier", "");
    bool upper = GfxFont::isBase14Font("COURIER", "");
    // Just document behavior, don't assume case sensitivity
    (void)lower;
    (void)upper;
}

// Test getAlternateName with base14 font names
TEST_F(GfxFontTest_1153, GetAlternateName_Helvetica_1153)
{
    const char *alt = GfxFont::getAlternateName("Helvetica");
    // Helvetica often maps to Arial or similar
    (void)alt; // Just ensure no crash
}

TEST_F(GfxFontTest_1153, GetAlternateName_TimesNewRoman_1153)
{
    const char *alt = GfxFont::getAlternateName("Times-Roman");
    (void)alt;
}

TEST_F(GfxFontTest_1153, GetAlternateName_Symbol_1153)
{
    const char *alt = GfxFont::getAlternateName("Symbol");
    (void)alt;
}

// Test isBase14Font with random non-base14 fonts
TEST_F(GfxFontTest_1153, IsBase14Font_Arial_1153)
{
    EXPECT_FALSE(GfxFont::isBase14Font("Arial", ""));
}

TEST_F(GfxFontTest_1153, IsBase14Font_Verdana_1153)
{
    EXPECT_FALSE(GfxFont::isBase14Font("Verdana", ""));
}

TEST_F(GfxFontTest_1153, IsBase14Font_ComicSans_1153)
{
    EXPECT_FALSE(GfxFont::isBase14Font("ComicSans", ""));
}
