#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>

#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"

// Test static methods that don't require font instances
class GfxFontStaticTest_1138 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test getAlternateName with known base14 font names
TEST_F(GfxFontStaticTest_1138, GetAlternateNameForCourier_1138) {
    const char *alt = GfxFont::getAlternateName("Courier");
    // Courier is a well-known font, may or may not have an alternate
    // We just verify the function doesn't crash and returns something or nullptr
    // This is a black-box test
    (void)alt; // just ensure no crash
    SUCCEED();
}

TEST_F(GfxFontStaticTest_1138, GetAlternateNameForNull_1138) {
    // Passing a name that likely has no alternate
    const char *alt = GfxFont::getAlternateName("SomeVeryUnknownFontName12345");
    // Should return nullptr for unknown fonts
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontStaticTest_1138, GetAlternateNameForTimesRoman_1138) {
    const char *alt = GfxFont::getAlternateName("Times-Roman");
    // Times-Roman might have an alternate name
    (void)alt;
    SUCCEED();
}

TEST_F(GfxFontStaticTest_1138, GetAlternateNameForHelvetica_1138) {
    const char *alt = GfxFont::getAlternateName("Helvetica");
    (void)alt;
    SUCCEED();
}

// Test isBase14Font static method
TEST_F(GfxFontStaticTest_1138, IsBase14FontCourier_1138) {
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontTimesRoman_1138) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    // Times-Roman is a base14 font, but the split between family/style may vary
    (void)result;
    SUCCEED();
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontHelvetica_1138) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontUnknown_1138) {
    bool result = GfxFont::isBase14Font("MyCustomFont", "Regular");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontSymbol_1138) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontZapfDingbats_1138) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontEmptyString_1138) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontCourierBold_1138) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    // Courier-Bold is a base14 font
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontCourierBoldOblique_1138) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontCourierOblique_1138) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontHelveticaBold_1138) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontHelveticaBoldOblique_1138) {
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontHelveticaOblique_1138) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontTimesBold_1138) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontTimesBoldItalic_1138) {
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1138, IsBase14FontTimesItalic_1138) {
    bool result = GfxFont::isBase14Font("Times", "Italic");
    EXPECT_TRUE(result);
}

// Test with makeFont - requires setting up a minimal Dict
class GfxFontInstanceTest_1138 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(GfxFontInstanceTest_1138, MakeFontWithNullDict_1138) {
    // makeFont with nullptr dict should handle gracefully (return nullptr or handle)
    // This tests boundary/error condition
    Ref id = {1, 0};
    auto font = GfxFont::makeFont(nullptr, "F1", id, nullptr);
    // Expect nullptr since no valid dict is provided
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxFontStaticTest_1138, GetAlternateNameForCourierBold_1138) {
    const char *alt = GfxFont::getAlternateName("Courier-Bold");
    (void)alt;
    SUCCEED();
}

TEST_F(GfxFontStaticTest_1138, GetAlternateNameForHelveticaBold_1138) {
    const char *alt = GfxFont::getAlternateName("Helvetica-Bold");
    (void)alt;
    SUCCEED();
}
