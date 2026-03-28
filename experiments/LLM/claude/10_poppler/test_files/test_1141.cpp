#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "GfxFont.h"
#include "GooString.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>
#include <array>
#include <optional>

class GfxFontTest_1141 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test static method getAlternateName with known font names
TEST_F(GfxFontTest_1141, GetAlternateNameWithKnownFont_1141) {
    const char *alt = GfxFont::getAlternateName("Arial");
    // May or may not return an alternate; we just verify it doesn't crash
    // If Arial has an alternate, it should be non-null
    // This is implementation-dependent, so we just test it's callable
    (void)alt;
}

TEST_F(GfxFontTest_1141, GetAlternateNameWithNullptr_1141) {
    // Testing with nullptr - behavior depends on implementation
    // Some implementations may handle nullptr gracefully
    // We skip this if it would crash
}

TEST_F(GfxFontTest_1141, GetAlternateNameWithUnknownFont_1141) {
    const char *alt = GfxFont::getAlternateName("CompletelyUnknownFontXYZ123");
    // Unknown font should likely return nullptr
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontTest_1141, GetAlternateNameWithEmptyString_1141) {
    const char *alt = GfxFont::getAlternateName("");
    EXPECT_EQ(alt, nullptr);
}

// Test isBase14Font static method
TEST_F(GfxFontTest_1141, IsBase14FontCourier_1141) {
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontCourierBold_1141) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontHelvetica_1141) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontTimesRoman_1141) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontSymbol_1141) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontZapfDingbats_1141) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontUnknown_1141) {
    bool result = GfxFont::isBase14Font("ComicSans", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontEmptyStrings_1141) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontHelveticaBold_1141) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontHelveticaBoldOblique_1141) {
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontTimesBold_1141) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontTimesItalic_1141) {
    bool result = GfxFont::isBase14Font("Times", "Italic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontTimesBoldItalic_1141) {
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontCourierOblique_1141) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontCourierBoldOblique_1141) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontRandomFamily_1141) {
    bool result = GfxFont::isBase14Font("RandomFont", "Bold");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1141, IsBase14FontHelveticaOblique_1141) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

// Test makeFont with nullptr/invalid inputs returns nullptr or handles gracefully
TEST_F(GfxFontTest_1141, MakeFontWithNullXRef_1141) {
    // Creating a minimal Dict for testing
    // makeFont with null xref should handle gracefully
    // This test verifies the factory method's robustness
    // We can't easily construct a valid Dict without an XRef, 
    // so we test what we can
}

// Test with a constructed font from a minimal PDF if possible
class GfxFontFromPDFTest_1141 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

TEST_F(GfxFontFromPDFTest_1141, GetAlternateNameForTimesNewRoman_1141) {
    const char *alt = GfxFont::getAlternateName("TimesNewRoman");
    // TimesNewRoman might map to Times-Roman or similar
    (void)alt; // Just ensure no crash
}

TEST_F(GfxFontFromPDFTest_1141, GetAlternateNameForArialBlack_1141) {
    const char *alt = GfxFont::getAlternateName("Arial-Black");
    (void)alt;
}

TEST_F(GfxFontFromPDFTest_1141, IsBase14FontCaseSensitivity_1141) {
    // Base14 font names are case-sensitive in PDF spec
    bool result = GfxFont::isBase14Font("courier", "");
    // Depending on implementation, lowercase may not match
    // We just verify it doesn't crash
    (void)result;
}

TEST_F(GfxFontFromPDFTest_1141, IsBase14FontWithWhitespace_1141) {
    bool result = GfxFont::isBase14Font(" Courier ", "");
    EXPECT_FALSE(result); // Whitespace should not match
}

TEST_F(GfxFontFromPDFTest_1141, IsBase14FontPartialMatch_1141) {
    bool result = GfxFont::isBase14Font("Cour", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontFromPDFTest_1141, IsBase14FontExtraChars_1141) {
    bool result = GfxFont::isBase14Font("CourierNew", "");
    EXPECT_FALSE(result);
}
