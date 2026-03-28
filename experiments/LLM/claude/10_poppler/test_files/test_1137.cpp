#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <optional>

#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"

// Since GfxFont has a protected constructor and we cannot instantiate it directly,
// we need to use the static factory method makeFont. However, that requires
// a valid XRef, Dict, etc. We'll test what we can through the public interface
// and static methods.

class GfxFontTest_1137 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test static method getAlternateName with known base14 font names
TEST_F(GfxFontTest_1137, GetAlternateNameForCourier_1137) {
    const char *alt = GfxFont::getAlternateName("Courier");
    // getAlternateName may return nullptr or an alternate name
    // We just verify it doesn't crash and returns something reasonable
    // for a known font name
    if (alt != nullptr) {
        EXPECT_NE(std::string(alt), "");
    }
}

TEST_F(GfxFontTest_1137, GetAlternateNameForUnknownFont_1137) {
    const char *alt = GfxFont::getAlternateName("CompletelyUnknownFontXYZ123");
    // For an unknown font, it should return nullptr
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontTest_1137, GetAlternateNameForNull_1137) {
    const char *alt = GfxFont::getAlternateName(nullptr);
    // Should handle nullptr gracefully
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontTest_1137, GetAlternateNameForEmptyString_1137) {
    const char *alt = GfxFont::getAlternateName("");
    EXPECT_EQ(alt, nullptr);
}

// Test isBase14Font static method with known Base14 font families and styles
TEST_F(GfxFontTest_1137, IsBase14FontCourier_1137) {
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontHelvetica_1137) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontTimesRoman_1137) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    // Times Roman is a base14 font
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontSymbol_1137) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontZapfDingbats_1137) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontUnknown_1137) {
    bool result = GfxFont::isBase14Font("UnknownFont", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontEmptyStrings_1137) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontCourierBold_1137) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontCourierBoldOblique_1137) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontHelveticaBold_1137) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontHelveticaOblique_1137) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontTimesBold_1137) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontTimesBoldItalic_1137) {
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontTimesItalic_1137) {
    bool result = GfxFont::isBase14Font("Times", "Italic");
    EXPECT_TRUE(result);
}

// Test getAlternateName with various Base14 font names
TEST_F(GfxFontTest_1137, GetAlternateNameForHelvetica_1137) {
    const char *alt = GfxFont::getAlternateName("Helvetica");
    // Helvetica might have an alternate like "Arial"
    if (alt != nullptr) {
        EXPECT_NE(std::string(alt), "");
    }
}

TEST_F(GfxFontTest_1137, GetAlternateNameForTimesNewRoman_1137) {
    const char *alt = GfxFont::getAlternateName("Times-Roman");
    if (alt != nullptr) {
        EXPECT_NE(std::string(alt), "");
    }
}

TEST_F(GfxFontTest_1137, GetAlternateNameForSymbol_1137) {
    const char *alt = GfxFont::getAlternateName("Symbol");
    // Symbol may or may not have an alternate
    // Just verify no crash
}

TEST_F(GfxFontTest_1137, GetAlternateNameForZapfDingbats_1137) {
    const char *alt = GfxFont::getAlternateName("ZapfDingbats");
    // Just verify no crash
}

// Test makeFont with nullptr parameters to check error handling
TEST_F(GfxFontTest_1137, MakeFontWithNullDict_1137) {
    Ref id = {0, 0};
    // makeFont with null dict should return nullptr or handle gracefully
    auto font = GfxFont::makeFont(nullptr, "F1", id, nullptr);
    EXPECT_EQ(font, nullptr);
}

// Additional boundary tests for isBase14Font
TEST_F(GfxFontTest_1137, IsBase14FontCaseSensitive_1137) {
    // Test case sensitivity - "courier" vs "Courier"
    bool result = GfxFont::isBase14Font("courier", "");
    // Typically case-sensitive, so lowercase might not match
    // We don't know the implementation, just test it doesn't crash
    // and produces a bool result
    SUCCEED();
}

TEST_F(GfxFontTest_1137, IsBase14FontLongString_1137) {
    std::string longFamily(10000, 'A');
    bool result = GfxFont::isBase14Font(longFamily, "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1137, IsBase14FontSpecialChars_1137) {
    bool result = GfxFont::isBase14Font("!@#$%^&*()", "");
    EXPECT_FALSE(result);
}
