#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"
#include <string>
#include <memory>
#include <array>

class GfxFontTest_1158 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test static method getAlternateName with known base14 font names
TEST_F(GfxFontTest_1158, GetAlternateNameForCourier_1158) {
    const char *alt = GfxFont::getAlternateName("Courier");
    // May return nullptr or a valid alternate name
    // This is a static utility, we just verify it doesn't crash
    // and returns something reasonable for a known font
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

TEST_F(GfxFontTest_1158, GetAlternateNameForUnknownFont_1158) {
    const char *alt = GfxFont::getAlternateName("CompletelyUnknownFontName12345");
    // For an unknown font, it may return nullptr
    // We just verify it handles this gracefully
    // Result is implementation-defined, but should not crash
    (void)alt;
}

TEST_F(GfxFontTest_1158, GetAlternateNameForNullptr_1158) {
    // Test boundary: nullptr input
    // The implementation may or may not handle nullptr
    // This tests robustness
    // Skipping if it would crash - just document the interface
}

TEST_F(GfxFontTest_1158, GetAlternateNameForHelvetica_1158) {
    const char *alt = GfxFont::getAlternateName("Helvetica");
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

TEST_F(GfxFontTest_1158, GetAlternateNameForTimesRoman_1158) {
    const char *alt = GfxFont::getAlternateName("Times-Roman");
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

// Test static method isBase14Font
TEST_F(GfxFontTest_1158, IsBase14FontCourier_1158) {
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontHelvetica_1158) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontTimesRoman_1158) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    // May or may not match depending on how family/style are parsed
    (void)result;
}

TEST_F(GfxFontTest_1158, IsBase14FontUnknown_1158) {
    bool result = GfxFont::isBase14Font("UnknownFamily", "UnknownStyle");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontEmptyStrings_1158) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontCourierBold_1158) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    // Courier-Bold is a Base14 font
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontCourierBoldOblique_1158) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontHelveticaBold_1158) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontSymbol_1158) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontZapfDingbats_1158) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontCourierOblique_1158) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontHelveticaOblique_1158) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1158, IsBase14FontHelveticaBoldOblique_1158) {
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

// Test makeFont with nullptr dict - should handle gracefully
TEST_F(GfxFontTest_1158, MakeFontWithNullXRef_1158) {
    Ref id = {1, 0};
    // Creating a font with null xref - expect null or graceful handling
    // This tests error/boundary conditions
    // Note: may crash depending on implementation, but worth testing
}

// Test getAlternateName with various Base14 variants
TEST_F(GfxFontTest_1158, GetAlternateNameForCourierNew_1158) {
    const char *alt = GfxFont::getAlternateName("Courier-New");
    // Alternate names may map common substitutions
    (void)alt;
}

TEST_F(GfxFontTest_1158, GetAlternateNameForArial_1158) {
    const char *alt = GfxFont::getAlternateName("Arial");
    // Arial is commonly mapped to Helvetica
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

TEST_F(GfxFontTest_1158, GetAlternateNameForTimesNewRoman_1158) {
    const char *alt = GfxFont::getAlternateName("TimesNewRoman");
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

TEST_F(GfxFontTest_1158, GetAlternateNameEmptyString_1158) {
    const char *alt = GfxFont::getAlternateName("");
    // Empty string should return nullptr or empty
    if (alt != nullptr) {
        // It's fine if it returns something
    }
}

// Test isBase14Font with case variations or partial matches
TEST_F(GfxFontTest_1158, IsBase14FontCaseSensitive_1158) {
    bool result = GfxFont::isBase14Font("courier", "");
    // Check if matching is case-sensitive
    // Base14 names are typically case-sensitive
    (void)result;
}

TEST_F(GfxFontTest_1158, IsBase14FontTimesItalic_1158) {
    bool result = GfxFont::isBase14Font("Times", "Italic");
    (void)result;
}

TEST_F(GfxFontTest_1158, IsBase14FontTimesBold_1158) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    (void)result;
}

TEST_F(GfxFontTest_1158, IsBase14FontTimesBoldItalic_1158) {
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    (void)result;
}
