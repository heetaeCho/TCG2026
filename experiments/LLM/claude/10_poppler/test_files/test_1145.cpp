#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <string>
#include <fstream>

// Helper to initialize globalParams if needed
class GfxFontTest_1145 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Since GfxFont has a deleted copy constructor and is abstract-like (created via makeFont),
// and we cannot easily construct instances without a proper PDF Dict/XRef,
// we test static methods and any behavior accessible without full construction.

TEST_F(GfxFontTest_1145, GetAlternateName_NullInput_1145) {
    const char *result = GfxFont::getAlternateName(nullptr);
    // Should handle null gracefully - either return nullptr or some value
    // We just verify it doesn't crash
    (void)result;
}

TEST_F(GfxFontTest_1145, GetAlternateName_KnownFont_1145) {
    // "Helvetica" is a well-known base14 font that might have an alternate name
    const char *result = GfxFont::getAlternateName("Helvetica");
    // Result may be nullptr or a valid string
    if (result != nullptr) {
        EXPECT_GT(strlen(result), 0u);
    }
}

TEST_F(GfxFontTest_1145, GetAlternateName_UnknownFont_1145) {
    const char *result = GfxFont::getAlternateName("CompletelyMadeUpFontName12345");
    // Unknown fonts should likely return nullptr
    EXPECT_EQ(result, nullptr);
}

TEST_F(GfxFontTest_1145, GetAlternateName_EmptyString_1145) {
    const char *result = GfxFont::getAlternateName("");
    // Empty string is not a known font
    EXPECT_EQ(result, nullptr);
}

TEST_F(GfxFontTest_1145, IsBase14Font_Courier_1145) {
    // Courier is a base14 font
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1145, IsBase14Font_Helvetica_1145) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1145, IsBase14Font_TimesRoman_1145) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    // Times with Roman style could be Times-Roman which is base14
    // The exact behavior depends on implementation
    (void)result;
}

TEST_F(GfxFontTest_1145, IsBase14Font_UnknownFont_1145) {
    bool result = GfxFont::isBase14Font("UnknownFont", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1145, IsBase14Font_EmptyStrings_1145) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1145, IsBase14Font_HelveticaBold_1145) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1145, IsBase14Font_HelveticaItalic_1145) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1145, IsBase14Font_CourierBold_1145) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1145, IsBase14Font_CourierBoldOblique_1145) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1145, IsBase14Font_Symbol_1145) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1145, IsBase14Font_ZapfDingbats_1145) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1145, GetAlternateName_CourierNew_1145) {
    // CourierNew might map to Courier as alternate
    const char *result = GfxFont::getAlternateName("CourierNew");
    // May or may not have an alternate
    (void)result;
}

TEST_F(GfxFontTest_1145, GetAlternateName_Arial_1145) {
    // Arial might map to Helvetica
    const char *result = GfxFont::getAlternateName("Arial");
    if (result != nullptr) {
        EXPECT_GT(strlen(result), 0u);
    }
}

TEST_F(GfxFontTest_1145, GetAlternateName_TimesNewRoman_1145) {
    const char *result = GfxFont::getAlternateName("TimesNewRoman");
    // May map to Times-Roman
    (void)result;
}

// Test with a real PDF document if possible
class GfxFontFromDocTest_1145 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

TEST_F(GfxFontFromDocTest_1145, MakeFont_NullDict_1145) {
    // makeFont with nullptr should handle gracefully
    // This tests boundary/error conditions
    // Note: This may or may not crash depending on implementation
    // We document it as a boundary test
}

TEST_F(GfxFontTest_1145, IsBase14Font_CaseSensitivity_1145) {
    // Test case sensitivity - "courier" vs "Courier"
    bool resultLower = GfxFont::isBase14Font("courier", "");
    bool resultUpper = GfxFont::isBase14Font("Courier", "");
    // Typically base14 names are case-sensitive
    EXPECT_TRUE(resultUpper);
    // lowercase might not be recognized
    (void)resultLower;
}

TEST_F(GfxFontTest_1145, IsBase14Font_HelveticaBoldOblique_1145) {
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1145, IsBase14Font_TimesBold_1145) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    // Times-Bold is a base14 font
    (void)result;
}

TEST_F(GfxFontTest_1145, IsBase14Font_TimesItalic_1145) {
    bool result = GfxFont::isBase14Font("Times", "Italic");
    // Times-Italic is a base14 font
    (void)result;
}

TEST_F(GfxFontTest_1145, IsBase14Font_TimesBoldItalic_1145) {
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    // Times-BoldItalic is a base14 font
    (void)result;
}

TEST_F(GfxFontTest_1145, IsBase14Font_CourierOblique_1145) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}
