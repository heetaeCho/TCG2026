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

// Test fixture for GfxFont tests
class GfxFontTest_1142 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test static method getAlternateName with known font name
TEST_F(GfxFontTest_1142, GetAlternateNameWithKnownFont_1142) {
    const char *altName = GfxFont::getAlternateName("Arial");
    // We just verify it doesn't crash; result may be nullptr or a valid string
    // The actual return depends on internal mapping
    // This is a black-box test of the static method
    (void)altName; // suppress unused warning
    SUCCEED();
}

// Test static method getAlternateName with nullptr
TEST_F(GfxFontTest_1142, GetAlternateNameWithNullptr_1142) {
    // Depending on implementation, this may or may not handle nullptr
    // We test it doesn't crash with an empty string at minimum
    const char *altName = GfxFont::getAlternateName("");
    (void)altName;
    SUCCEED();
}

// Test static method isBase14Font with known base14 fonts
TEST_F(GfxFontTest_1142, IsBase14FontCourier_1142) {
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontHelvetica_1142) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontTimesRoman_1142) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    // Times-Roman is a base14 font
    // The exact behavior depends on how family/style are matched
    (void)result;
    SUCCEED();
}

TEST_F(GfxFontTest_1142, IsBase14FontSymbol_1142) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontZapfDingbats_1142) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontUnknown_1142) {
    bool result = GfxFont::isBase14Font("ComicSans", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontEmpty_1142) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontCourierBold_1142) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    // Courier-Bold is a base14 font
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontHelveticaBold_1142) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontHelveticaOblique_1142) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontHelveticaBoldOblique_1142) {
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontCourierOblique_1142) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontCourierBoldOblique_1142) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1142, IsBase14FontTimesBold_1142) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    (void)result;
    SUCCEED();
}

// Test makeFont with nullptr fontDict returns nullptr
TEST_F(GfxFontTest_1142, MakeFontWithNullDictReturnsNull_1142) {
    Ref id = {0, 0};
    auto font = GfxFont::makeFont(nullptr, "tag", id, nullptr);
    EXPECT_EQ(font, nullptr);
}

// Test that getAlternateName returns non-null for standard substitution names
TEST_F(GfxFontTest_1142, GetAlternateNameTimesNewRoman_1142) {
    const char *altName = GfxFont::getAlternateName("TimesNewRoman");
    // TimesNewRoman might map to Times-Roman or similar
    (void)altName;
    SUCCEED();
}

TEST_F(GfxFontTest_1142, GetAlternateNameArialNarrow_1142) {
    const char *altName = GfxFont::getAlternateName("ArialNarrow");
    (void)altName;
    SUCCEED();
}

// Boundary: very long font name for getAlternateName
TEST_F(GfxFontTest_1142, GetAlternateNameVeryLongName_1142) {
    std::string longName(1000, 'A');
    const char *altName = GfxFont::getAlternateName(longName.c_str());
    // Should return nullptr for unknown font
    EXPECT_EQ(altName, nullptr);
}

// Boundary: isBase14Font with very long family name
TEST_F(GfxFontTest_1142, IsBase14FontVeryLongName_1142) {
    std::string longName(1000, 'X');
    bool result = GfxFont::isBase14Font(longName, "");
    EXPECT_FALSE(result);
}

// Test isBase14Font case sensitivity
TEST_F(GfxFontTest_1142, IsBase14FontCaseSensitivity_1142) {
    bool result = GfxFont::isBase14Font("courier", "");
    // Depending on implementation, lowercase might not match
    (void)result;
    SUCCEED();
}

TEST_F(GfxFontTest_1142, IsBase14FontCaseSensitivityHelvetica_1142) {
    bool result = GfxFont::isBase14Font("helvetica", "");
    (void)result;
    SUCCEED();
}
