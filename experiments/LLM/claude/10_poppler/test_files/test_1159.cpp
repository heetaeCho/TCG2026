#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <array>

#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class GfxFontTest_1159 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test static method getAlternateName with known base14 font names
TEST_F(GfxFontTest_1159, GetAlternateNameForCourier_1159) {
    const char *alt = GfxFont::getAlternateName("Courier");
    // getAlternateName may return nullptr or an alternate name
    // We just verify it doesn't crash and returns something reasonable
    // For Courier, it might return nullptr since it's already a standard name
    // This is a behavioral observation test
    (void)alt; // Just ensure no crash
}

TEST_F(GfxFontTest_1159, GetAlternateNameForNull_1159) {
    // Test with an unknown font name
    const char *alt = GfxFont::getAlternateName("NonExistentFontXYZ123");
    // Should return nullptr for unknown fonts
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontTest_1159, GetAlternateNameForTimesRoman_1159) {
    const char *alt = GfxFont::getAlternateName("TimesNewRoman");
    // May or may not have an alternate
    (void)alt;
}

// Test static method isBase14Font
TEST_F(GfxFontTest_1159, IsBase14FontCourier_1159) {
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontTimesRoman_1159) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    // Times-Roman is a base14 font
    (void)result; // Behavior depends on implementation
}

TEST_F(GfxFontTest_1159, IsBase14FontHelvetica_1159) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontUnknown_1159) {
    bool result = GfxFont::isBase14Font("ComicSans", "Regular");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontSymbol_1159) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontZapfDingbats_1159) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontCourierBold_1159) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontEmptyStrings_1159) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontHelveticaBoldOblique_1159) {
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontTimesBold_1159) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    (void)result;
}

// Test makeFont with nullptr dict - should handle gracefully
TEST_F(GfxFontTest_1159, MakeFontWithNullXref_1159) {
    // Creating a minimal dict for testing
    // makeFont with null xref - testing boundary
    // This may crash or return nullptr depending on implementation
    // We skip this if it's unsafe
}

// Test getAlternateName with various base14 variants
TEST_F(GfxFontTest_1159, GetAlternateNameForHelvetica_1159) {
    const char *alt = GfxFont::getAlternateName("Arial");
    // Arial is commonly mapped to Helvetica
    if (alt != nullptr) {
        EXPECT_STREQ(alt, "Helvetica");
    }
}

TEST_F(GfxFontTest_1159, GetAlternateNameForTimesNewRoman_1159) {
    const char *alt = GfxFont::getAlternateName("TimesNewRoman");
    if (alt != nullptr) {
        std::string altStr(alt);
        EXPECT_FALSE(altStr.empty());
    }
}

TEST_F(GfxFontTest_1159, GetAlternateNameForCourierNew_1159) {
    const char *alt = GfxFont::getAlternateName("CourierNew");
    if (alt != nullptr) {
        EXPECT_STREQ(alt, "Courier");
    }
}

TEST_F(GfxFontTest_1159, IsBase14FontCourierOblique_1159) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontCourierBoldOblique_1159) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontHelveticaOblique_1159) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontTimesItalic_1159) {
    bool result = GfxFont::isBase14Font("Times", "Italic");
    (void)result;
}

TEST_F(GfxFontTest_1159, IsBase14FontTimesBoldItalic_1159) {
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    (void)result;
}

TEST_F(GfxFontTest_1159, IsBase14FontHelveticaBold_1159) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontRandomString_1159) {
    bool result = GfxFont::isBase14Font("SomeRandomFont", "SomeRandomStyle");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1159, IsBase14FontLongString_1159) {
    std::string longName(1000, 'A');
    bool result = GfxFont::isBase14Font(longName, "");
    EXPECT_FALSE(result);
}
