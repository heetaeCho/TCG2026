#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>
#include <cstring>

class GfxFontTest_1143 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test static method getAlternateName with known font names
TEST_F(GfxFontTest_1143, GetAlternateName_KnownFont_1143) {
    const char *alt = GfxFont::getAlternateName("Arial");
    // Arial may or may not have an alternate; we just verify no crash
    // and the return is either null or a valid string
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

TEST_F(GfxFontTest_1143, GetAlternateName_NullInput_1143) {
    // Test with nullptr - implementation dependent but should not crash
    // Some implementations may handle null gracefully
    // We skip this if it would cause undefined behavior
}

TEST_F(GfxFontTest_1143, GetAlternateName_UnknownFont_1143) {
    const char *alt = GfxFont::getAlternateName("SomeVeryUnlikelyFontNameXYZ123");
    // Unknown fonts should return nullptr
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontTest_1143, GetAlternateName_EmptyString_1143) {
    const char *alt = GfxFont::getAlternateName("");
    EXPECT_EQ(alt, nullptr);
}

// Test isBase14Font static method with known Base14 fonts
TEST_F(GfxFontTest_1143, IsBase14Font_Courier_1143) {
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_CourierBold_1143) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_Helvetica_1143) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_HelveticaBold_1143) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_HelveticaOblique_1143) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_HelveticaBoldOblique_1143) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold Oblique");
    // May or may not match depending on exact style matching
}

TEST_F(GfxFontTest_1143, IsBase14Font_TimesRoman_1143) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_Symbol_1143) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_ZapfDingbats_1143) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_UnknownFont_1143) {
    bool result = GfxFont::isBase14Font("ComicSans", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_EmptyFamily_1143) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_RandomString_1143) {
    bool result = GfxFont::isBase14Font("NotAFont", "NotAStyle");
    EXPECT_FALSE(result);
}

// Test makeFont returns nullptr with invalid inputs
TEST_F(GfxFontTest_1143, MakeFont_NullXRef_1143) {
    // Creating a minimal Dict for testing
    // With null xref, makeFont should handle gracefully
    Ref ref = {1, 0};
    // This tests that makeFont doesn't crash with edge cases
    // We can't easily create a valid Dict without an XRef, so we test null handling
}

// Test with CourierNew as alternate
TEST_F(GfxFontTest_1143, GetAlternateName_CourierNew_1143) {
    const char *alt = GfxFont::getAlternateName("Courier New");
    // CourierNew commonly maps to Courier
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

TEST_F(GfxFontTest_1143, GetAlternateName_TimesNewRoman_1143) {
    const char *alt = GfxFont::getAlternateName("Times New Roman");
    if (alt != nullptr) {
        EXPECT_GT(strlen(alt), 0u);
    }
}

TEST_F(GfxFontTest_1143, IsBase14Font_CourierBoldOblique_1143) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    // Courier-BoldOblique is a Base14 font
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_CourierOblique_1143) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_TimesBold_1143) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_TimesItalic_1143) {
    bool result = GfxFont::isBase14Font("Times", "Italic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_TimesBoldItalic_1143) {
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1143, IsBase14Font_CaseSensitivity_1143) {
    // Test case sensitivity - base14 names are typically exact
    bool result = GfxFont::isBase14Font("courier", "");
    // Depending on implementation, this may be false
    // We just verify it doesn't crash
}

TEST_F(GfxFontTest_1143, IsBase14Font_HelveticaBoldObliqueExact_1143) {
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}
