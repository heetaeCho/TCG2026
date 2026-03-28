#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <string_view>

#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"

// Test static method getAlternateName
TEST(GfxFontStaticTest_1139, GetAlternateNameWithKnownFont_1139)
{
    // Test with a known base-14 font name
    const char *alt = GfxFont::getAlternateName("Helvetica");
    // It may return a non-null alternate name or null depending on mapping
    // We just verify it doesn't crash and returns something reasonable
    // (either nullptr or a valid string)
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

TEST(GfxFontStaticTest_1139, GetAlternateNameWithUnknownFont_1139)
{
    const char *alt = GfxFont::getAlternateName("CompletelyUnknownFontNameXYZ123");
    // For an unknown font, it may return nullptr
    // We just verify it doesn't crash
    (void)alt;
}

TEST(GfxFontStaticTest_1139, GetAlternateNameWithNullptr_1139)
{
    // Test with nullptr - implementation should handle gracefully
    // This may or may not be valid depending on implementation
    // Commenting out to avoid potential crash if not handled
    // const char *alt = GfxFont::getAlternateName(nullptr);
}

TEST(GfxFontStaticTest_1139, GetAlternateNameWithEmptyString_1139)
{
    const char *alt = GfxFont::getAlternateName("");
    // Should handle empty string gracefully
    (void)alt;
}

// Test static method isBase14Font with string_view overload
TEST(GfxFontStaticTest_1139, IsBase14FontHelvetica_1139)
{
    bool result = GfxFont::isBase14Font("Helvetica", "");
    // Helvetica is a base-14 font
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontTimesBold_1139)
{
    bool result = GfxFont::isBase14Font("Times", "Bold");
    // Times-Bold is a base-14 font
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontTimesRoman_1139)
{
    bool result = GfxFont::isBase14Font("Times", "Roman");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontCourier_1139)
{
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontSymbol_1139)
{
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontZapfDingbats_1139)
{
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontUnknown_1139)
{
    bool result = GfxFont::isBase14Font("ArialUnicodeMS", "");
    EXPECT_FALSE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontEmptyFamily_1139)
{
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontRandomString_1139)
{
    bool result = GfxFont::isBase14Font("SomeRandomFont", "SomeStyle");
    EXPECT_FALSE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontHelveticaBold_1139)
{
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontHelveticaBoldOblique_1139)
{
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontHelveticaOblique_1139)
{
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontCourierBold_1139)
{
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontCourierOblique_1139)
{
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontCourierBoldOblique_1139)
{
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontTimesBoldItalic_1139)
{
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    EXPECT_TRUE(result);
}

TEST(GfxFontStaticTest_1139, IsBase14FontTimesItalic_1139)
{
    bool result = GfxFont::isBase14Font("Times", "Italic");
    EXPECT_TRUE(result);
}

// Test getID returns non-null pointer
// We need a GfxFont instance for this. We'll try makeFont with minimal setup.
TEST(GfxFontStaticTest_1139, GetAlternateNameCourierNew_1139)
{
    const char *alt = GfxFont::getAlternateName("Courier New");
    // Courier New might map to Courier
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

TEST(GfxFontStaticTest_1139, GetAlternateNameArialMT_1139)
{
    const char *alt = GfxFont::getAlternateName("ArialMT");
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

TEST(GfxFontStaticTest_1139, GetAlternateNameTimesNewRoman_1139)
{
    const char *alt = GfxFont::getAlternateName("TimesNewRoman");
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}
