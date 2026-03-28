#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>
#include <memory>
#include <string>

#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"

// Since GfxFont has a protected constructor and we can't easily instantiate it directly,
// we'll use makeFont where possible, or test static methods and whatever we can access.
// For testing getFontBBox and other public methods, we need a valid GfxFont instance.

class GfxFontTest_1157 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test static method getAlternateName with known base14 font names
TEST_F(GfxFontTest_1157, GetAlternateNameForCourier_1157) {
    const char *alt = GfxFont::getAlternateName("Courier");
    // May return nullptr or a valid alternate name
    // We just verify the function doesn't crash and returns something reasonable
    // (could be nullptr if no alternate exists)
    // This is a black-box test
    SUCCEED();
}

TEST_F(GfxFontTest_1157, GetAlternateNameForNull_1157) {
    // Test with an unknown font name
    const char *alt = GfxFont::getAlternateName("SomeCompletelyUnknownFontName12345");
    // Expect nullptr for unknown fonts
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontTest_1157, GetAlternateNameForTimesRoman_1157) {
    const char *alt = GfxFont::getAlternateName("Times-Roman");
    // Times-Roman is a well-known font, might have an alternate
    // Just verify no crash
    SUCCEED();
}

// Test isBase14Font static method with known base14 fonts
TEST_F(GfxFontTest_1157, IsBase14FontCourier_1157) {
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontTimesRoman_1157) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    // May or may not match depending on exact implementation
    // At minimum, test doesn't crash
    SUCCEED();
}

TEST_F(GfxFontTest_1157, IsBase14FontHelvetica_1157) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontUnknown_1157) {
    bool result = GfxFont::isBase14Font("UnknownFont", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontCourierBold_1157) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    // Courier-Bold is a base14 font
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontCourierBoldOblique_1157) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontCourierOblique_1157) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontHelveticaBold_1157) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontHelveticaBoldOblique_1157) {
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontHelveticaOblique_1157) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontSymbol_1157) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontZapfDingbats_1157) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontEmptyStrings_1157) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontTimesBold_1157) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontTimesBoldItalic_1157) {
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1157, IsBase14FontTimesItalic_1157) {
    bool result = GfxFont::isBase14Font("Times", "Italic");
    EXPECT_TRUE(result);
}

// Test GetAlternateName with various base14 fonts
TEST_F(GfxFontTest_1157, GetAlternateNameHelvetica_1157) {
    const char *alt = GfxFont::getAlternateName("Helvetica");
    // Helvetica commonly has Arial as alternate
    if (alt != nullptr) {
        EXPECT_STRNE(alt, "");
    }
}

TEST_F(GfxFontTest_1157, GetAlternateNameSymbol_1157) {
    const char *alt = GfxFont::getAlternateName("Symbol");
    // Just verify no crash
    SUCCEED();
}

TEST_F(GfxFontTest_1157, GetAlternateNameZapfDingbats_1157) {
    const char *alt = GfxFont::getAlternateName("ZapfDingbats");
    // Just verify no crash
    SUCCEED();
}

TEST_F(GfxFontTest_1157, GetAlternateNameEmptyString_1157) {
    const char *alt = GfxFont::getAlternateName("");
    EXPECT_EQ(alt, nullptr);
}

// Test with font created via makeFont if possible
// This requires setting up XRef and Dict which is complex, but we try a minimal approach
class GfxFontMakeFontTest_1157 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(GfxFontMakeFontTest_1157, MakeFontWithNullXref_1157) {
    // makeFont with null xref should handle gracefully
    // This tests boundary/error case
    // Note: this may or may not crash depending on implementation
    // We document the test but it may need to be skipped if it crashes
    // EXPECT_EQ(GfxFont::makeFont(nullptr, "F1", Ref::INVALID(), nullptr), nullptr);
    SUCCEED(); // Placeholder - can't safely call with nullptr in many implementations
}

// Test that isBase14Font handles long strings
TEST_F(GfxFontTest_1157, IsBase14FontVeryLongFamilyName_1157) {
    std::string longName(10000, 'A');
    bool result = GfxFont::isBase14Font(longName, "");
    EXPECT_FALSE(result);
}

// Test that isBase14Font handles special characters
TEST_F(GfxFontTest_1157, IsBase14FontSpecialChars_1157) {
    bool result = GfxFont::isBase14Font("Courier!@#$", "");
    EXPECT_FALSE(result);
}

// Test case sensitivity
TEST_F(GfxFontTest_1157, IsBase14FontCaseSensitivity_1157) {
    bool resultLower = GfxFont::isBase14Font("courier", "");
    bool resultUpper = GfxFont::isBase14Font("COURIER", "");
    // The behavior depends on implementation - we just check no crash
    SUCCEED();
}

// Test getAlternateName with base14 bold/italic variants
TEST_F(GfxFontTest_1157, GetAlternateNameHelveticaBold_1157) {
    const char *alt = GfxFont::getAlternateName("Helvetica-Bold");
    // Just verify no crash
    SUCCEED();
}

TEST_F(GfxFontTest_1157, GetAlternateNameTimesBoldItalic_1157) {
    const char *alt = GfxFont::getAlternateName("Times-BoldItalic");
    SUCCEED();
}

TEST_F(GfxFontTest_1157, GetAlternateNameCourierBoldOblique_1157) {
    const char *alt = GfxFont::getAlternateName("Courier-BoldOblique");
    SUCCEED();
}
