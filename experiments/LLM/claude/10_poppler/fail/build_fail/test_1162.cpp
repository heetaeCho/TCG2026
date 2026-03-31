#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"

// Since GfxFont has a protected constructor and is typically created via makeFont,
// we need to test through the public factory method or through subclass access.
// We'll test what we can through the static methods and through makeFont if possible.

class GfxFontTest_1162 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test static method getAlternateName with known base14 font names
TEST_F(GfxFontTest_1162, GetAlternateNameWithKnownFont_1162)
{
    const char *alt = GfxFont::getAlternateName("Helvetica");
    // getAlternateName may return nullptr or a valid alternate name
    // We just verify it doesn't crash and returns something reasonable
    // for a known font name
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

TEST_F(GfxFontTest_1162, GetAlternateNameWithUnknownFont_1162)
{
    const char *alt = GfxFont::getAlternateName("CompletelyUnknownFontXYZ123");
    // For an unknown font, it should return nullptr
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontTest_1162, GetAlternateNameWithNullptr_1162)
{
    // Test with nullptr - should handle gracefully
    const char *alt = GfxFont::getAlternateName(nullptr);
    // Expect nullptr or no crash
    EXPECT_EQ(alt, nullptr);
}

// Test isBase14Font with known Base14 fonts
TEST_F(GfxFontTest_1162, IsBase14FontCourier_1162)
{
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontHelvetica_1162)
{
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontTimesRoman_1162)
{
    bool result = GfxFont::isBase14Font("Times", "Roman");
    // Times-Roman is a base14 font
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontSymbol_1162)
{
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontZapfDingbats_1162)
{
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontUnknown_1162)
{
    bool result = GfxFont::isBase14Font("UnknownFont", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontEmptyStrings_1162)
{
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontCourierBold_1162)
{
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontHelveticaBold_1162)
{
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontHelveticaOblique_1162)
{
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontHelveticaBoldOblique_1162)
{
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontCourierOblique_1162)
{
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontTimesBold_1162)
{
    bool result = GfxFont::isBase14Font("Times", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontTimesItalic_1162)
{
    bool result = GfxFont::isBase14Font("Times", "Italic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1162, IsBase14FontTimesBoldItalic_1162)
{
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    EXPECT_TRUE(result);
}

// Test getAlternateName with various Base14 font alternate names
TEST_F(GfxFontTest_1162, GetAlternateNameArialIsHelvetica_1162)
{
    const char *alt = GfxFont::getAlternateName("Arial");
    if (alt != nullptr) {
        // Arial is commonly mapped to Helvetica
        std::string altStr(alt);
        EXPECT_FALSE(altStr.empty());
    }
}

TEST_F(GfxFontTest_1162, GetAlternateNameTimesNewRoman_1162)
{
    const char *alt = GfxFont::getAlternateName("TimesNewRoman");
    // TimesNewRoman might map to Times-Roman
    // Just verify no crash
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

TEST_F(GfxFontTest_1162, GetAlternateNameCourierNew_1162)
{
    const char *alt = GfxFont::getAlternateName("CourierNew");
    // CourierNew might map to Courier
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

TEST_F(GfxFontTest_1162, GetAlternateNameEmptyString_1162)
{
    const char *alt = GfxFont::getAlternateName("");
    // Empty string should return nullptr
    EXPECT_EQ(alt, nullptr);
}

// Test makeFont with nullptr parameters to check error handling
TEST_F(GfxFontTest_1162, MakeFontWithNullDict_1162)
{
    // makeFont should handle null dict gracefully
    // This tests error/boundary conditions
    auto font = GfxFont::makeFont(nullptr, "F1", Ref::INVALID(), nullptr);
    // With null dict, makeFont should return nullptr or an invalid font
    EXPECT_EQ(font, nullptr);
}
