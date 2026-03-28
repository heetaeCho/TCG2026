#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <optional>
#include <memory>

#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"

// Test static method getAlternateName
class GfxFontStaticTest_1144 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(GfxFontStaticTest_1144, GetAlternateNameForKnownFont_1144) {
    // Test that known font names return an alternate name
    const char *alt = GfxFont::getAlternateName("Arial");
    // Arial is a common font that may have an alternate mapping
    // We just verify the function doesn't crash and returns something or nullptr
    // This is black-box: we can only check it returns a valid pointer or nullptr
    // No assertion on specific value since we don't know internal mapping
    (void)alt; // Just verify no crash
}

TEST_F(GfxFontStaticTest_1144, GetAlternateNameForNullptr_1144) {
    // Test with nullptr - should handle gracefully
    // Note: depending on implementation, this might crash, but we test it
    const char *alt = GfxFont::getAlternateName("NonExistentFontNameXYZ12345");
    // For an unknown font, it likely returns nullptr
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontStaticTest_1144, GetAlternateNameForTimesRoman_1144) {
    const char *alt = GfxFont::getAlternateName("Times-Roman");
    // Times-Roman is a well-known base14 font, might have alternate
    (void)alt;
}

TEST_F(GfxFontStaticTest_1144, GetAlternateNameForCourier_1144) {
    const char *alt = GfxFont::getAlternateName("Courier");
    (void)alt;
}

TEST_F(GfxFontStaticTest_1144, GetAlternateNameForHelvetica_1144) {
    const char *alt = GfxFont::getAlternateName("Helvetica");
    (void)alt;
}

// Test static method isBase14Font with string_view parameters
TEST_F(GfxFontStaticTest_1144, IsBase14FontCourier_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", ""));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontCourierBold_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "Bold"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontCourierOblique_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "Oblique"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontCourierBoldOblique_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "BoldOblique"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontHelvetica_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", ""));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontHelveticaBold_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Bold"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontHelveticaOblique_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Oblique"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontHelveticaBoldOblique_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "BoldOblique"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontTimesRoman_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Roman"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontTimesBold_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Bold"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontTimesItalic_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Italic"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontTimesBoldItalic_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "BoldItalic"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontSymbol_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("Symbol", ""));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontZapfDingbats_1144) {
    EXPECT_TRUE(GfxFont::isBase14Font("ZapfDingbats", ""));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontUnknown_1144) {
    EXPECT_FALSE(GfxFont::isBase14Font("UnknownFont", ""));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontEmptyFamily_1144) {
    EXPECT_FALSE(GfxFont::isBase14Font("", ""));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontRandomName_1144) {
    EXPECT_FALSE(GfxFont::isBase14Font("ComicSans", "Regular"));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontCaseSensitivity_1144) {
    // Test case sensitivity - base14 names are specific
    bool result = GfxFont::isBase14Font("courier", "");
    // Depending on implementation, lowercase might not match
    (void)result; // Just verify no crash
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontHelveticaWrongStyle_1144) {
    // Helvetica with a non-standard style
    bool result = GfxFont::isBase14Font("Helvetica", "Italic");
    // Helvetica-Italic is not a base14 font (it's Helvetica-Oblique)
    EXPECT_FALSE(result);
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontTimesWrongStyle_1144) {
    // Times with Oblique is not a base14 font
    bool result = GfxFont::isBase14Font("Times", "Oblique");
    EXPECT_FALSE(result);
}

// Test makeFont with nullptr/invalid inputs
class GfxFontMakeFontTest_1144 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(GfxFontMakeFontTest_1144, MakeFontWithNullDict_1144) {
    // makeFont with null dict should return nullptr or handle gracefully
    Ref id = {0, 0};
    auto font = GfxFont::makeFont(nullptr, "F1", id, nullptr);
    // With null dict, makeFont should likely return nullptr
    EXPECT_EQ(font, nullptr);
}

// Test boundary for getAlternateName with empty string
TEST_F(GfxFontStaticTest_1144, GetAlternateNameEmptyString_1144) {
    const char *alt = GfxFont::getAlternateName("");
    EXPECT_EQ(alt, nullptr);
}

// Test isBase14Font with very long strings
TEST_F(GfxFontStaticTest_1144, IsBase14FontVeryLongFamilyName_1144) {
    std::string longName(1000, 'A');
    EXPECT_FALSE(GfxFont::isBase14Font(longName, ""));
}

TEST_F(GfxFontStaticTest_1144, IsBase14FontVeryLongStyleName_1144) {
    std::string longStyle(1000, 'B');
    EXPECT_FALSE(GfxFont::isBase14Font("Courier", longStyle));
}
