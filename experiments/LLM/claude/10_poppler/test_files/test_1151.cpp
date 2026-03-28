#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"
#include <string>
#include <array>
#include <memory>

class GfxFontTest_1151 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test static method getAlternateName with known font name
TEST_F(GfxFontTest_1151, GetAlternateNameWithKnownFont_1151) {
    const char *altName = GfxFont::getAlternateName("Arial");
    // Result may be nullptr or a valid alternate name string
    // We just verify it doesn't crash and returns something reasonable
    if (altName != nullptr) {
        EXPECT_GT(strlen(altName), 0u);
    }
}

// Test static method getAlternateName with nullptr
TEST_F(GfxFontTest_1151, GetAlternateNameWithNullptr_1151) {
    // Depending on implementation, this may return nullptr or handle gracefully
    const char *altName = GfxFont::getAlternateName("NonExistentFontNameXYZ123");
    // For an unknown font, the alternate name is likely nullptr
    // We just test it doesn't crash
    SUCCEED();
}

// Test static method getAlternateName with empty string
TEST_F(GfxFontTest_1151, GetAlternateNameWithEmptyString_1151) {
    const char *altName = GfxFont::getAlternateName("");
    // Should handle empty string gracefully
    SUCCEED();
}

// Test isBase14Font with known Base14 fonts
TEST_F(GfxFontTest_1151, IsBase14FontCourier_1151) {
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontHelvetica_1151) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontTimesRoman_1151) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontSymbol_1151) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontZapfDingbats_1151) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontCourierBold_1151) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontHelveticaBold_1151) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

// Test isBase14Font with non-Base14 font
TEST_F(GfxFontTest_1151, IsBase14FontUnknownFont_1151) {
    bool result = GfxFont::isBase14Font("UnknownFont", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontEmptyString_1151) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontRandomName_1151) {
    bool result = GfxFont::isBase14Font("ComicSans", "Regular");
    EXPECT_FALSE(result);
}

// Test makeFont with nullptr dict returns nullptr or handles gracefully
TEST_F(GfxFontTest_1151, MakeFontWithNullDict_1151) {
    Ref id = {1, 0};
    // makeFont with null xref and null dict - should handle gracefully
    // This tests error handling in the factory method
    auto font = GfxFont::makeFont(nullptr, "F1", id, nullptr);
    // Expect nullptr or a font that reports !isOk()
    if (font) {
        EXPECT_FALSE(font->isOk());
    } else {
        EXPECT_EQ(font, nullptr);
    }
}

// Test getAlternateName with common substitute names
TEST_F(GfxFontTest_1151, GetAlternateNameTimesNewRoman_1151) {
    const char *altName = GfxFont::getAlternateName("TimesNewRoman");
    // TimesNewRoman might map to Times-Roman or similar
    if (altName != nullptr) {
        EXPECT_GT(strlen(altName), 0u);
    }
}

TEST_F(GfxFontTest_1151, GetAlternateNameArialBold_1151) {
    const char *altName = GfxFont::getAlternateName("Arial,Bold");
    if (altName != nullptr) {
        EXPECT_GT(strlen(altName), 0u);
    }
}

// Test isBase14Font with various style combinations
TEST_F(GfxFontTest_1151, IsBase14FontCourierOblique_1151) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontCourierBoldOblique_1151) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontHelveticaOblique_1151) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontHelveticaBoldOblique_1151) {
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontTimesBold_1151) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontTimesItalic_1151) {
    bool result = GfxFont::isBase14Font("Times", "Italic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1151, IsBase14FontTimesBoldItalic_1151) {
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    EXPECT_TRUE(result);
}
