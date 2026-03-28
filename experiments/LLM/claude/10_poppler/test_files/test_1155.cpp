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

// Test fixture for GfxFont static methods
class GfxFontStaticTest_1155 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test isBase14Font with known base14 font families
TEST_F(GfxFontStaticTest_1155, IsBase14Font_Courier_1155) {
    // Courier is a base 14 font
    bool result = GfxFont::isBase14Font("Courier", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_CourierBold_1155) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_CourierOblique_1155) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_CourierBoldOblique_1155) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_Helvetica_1155) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_HelveticaBold_1155) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_TimesRoman_1155) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_Symbol_1155) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_ZapfDingbats_1155) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_UnknownFont_1155) {
    bool result = GfxFont::isBase14Font("ComicSans", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_EmptyStrings_1155) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontStaticTest_1155, IsBase14Font_RandomString_1155) {
    bool result = GfxFont::isBase14Font("NotAFont", "NotAStyle");
    EXPECT_FALSE(result);
}

// Test getAlternateName
TEST_F(GfxFontStaticTest_1155, GetAlternateName_NullInput_1155) {
    const char *result = GfxFont::getAlternateName(nullptr);
    // Should handle null gracefully - likely returns nullptr
    // This is a boundary test
    EXPECT_EQ(result, nullptr);
}

TEST_F(GfxFontStaticTest_1155, GetAlternateName_UnknownFont_1155) {
    const char *result = GfxFont::getAlternateName("SomeRandomFontName12345");
    // Unknown fonts should return nullptr
    EXPECT_EQ(result, nullptr);
}

TEST_F(GfxFontStaticTest_1155, GetAlternateName_EmptyString_1155) {
    const char *result = GfxFont::getAlternateName("");
    EXPECT_EQ(result, nullptr);
}

// Test with a known font that might have an alternate name
TEST_F(GfxFontStaticTest_1155, GetAlternateName_Courier_1155) {
    const char *result = GfxFont::getAlternateName("Courier");
    // Courier might have an alternate name or might not
    // We just verify it doesn't crash
    // If it returns something, it should be a valid string
    if (result != nullptr) {
        EXPECT_GT(strlen(result), 0u);
    }
}

// Test fixture for GfxFont instance methods using makeFont
class GfxFontInstanceTest_1155 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that makeFont with null/invalid parameters handles gracefully
TEST_F(GfxFontInstanceTest_1155, MakeFont_NullXRef_1155) {
    // Creating a minimal Dict for testing
    // makeFont should handle edge cases
    Ref id = {1, 0};
    // We expect makeFont to handle null xref gracefully
    // This tests error handling
    auto font = GfxFont::makeFont(nullptr, "F1", id, nullptr);
    // With null dict, font creation should fail
    EXPECT_EQ(font, nullptr);
}

// Test creating a font with a minimal valid dictionary
TEST_F(GfxFontInstanceTest_1155, MakeFont_MinimalDict_1155) {
    // Create minimal structures needed
    Ref id = {1, 0};
    
    // Without a proper XRef and Dict, we can't create a valid font
    // but we can test that the factory handles this gracefully
    auto font = GfxFont::makeFont(nullptr, "TestTag", id, nullptr);
    if (font) {
        // If somehow a font is created, test basic accessors
        EXPECT_EQ(font->getTag(), "TestTag");
        const Ref *fontId = font->getID();
        EXPECT_NE(fontId, nullptr);
        EXPECT_EQ(fontId->num, 1);
        EXPECT_EQ(fontId->gen, 0);
    }
}

// Test flags and style detection methods
// These rely on having a valid font instance, which requires full Poppler infrastructure
// We test the relationship between flags and boolean methods

class GfxFontFlagsTest_1155 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Since we can't easily create GfxFont instances without full PDF infrastructure,
// we verify the static interface consistency

TEST_F(GfxFontFlagsTest_1155, IsBase14Font_AllBase14_1155) {
    // Test all 14 base fonts
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", ""));
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "Bold"));
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "Oblique"));
    EXPECT_TRUE(GfxFont::isBase14Font("Courier", "BoldOblique"));
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", ""));
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Bold"));
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Oblique"));
    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "BoldOblique"));
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Roman"));
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Bold"));
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "Italic"));
    EXPECT_TRUE(GfxFont::isBase14Font("Times", "BoldItalic"));
    EXPECT_TRUE(GfxFont::isBase14Font("Symbol", ""));
    EXPECT_TRUE(GfxFont::isBase14Font("ZapfDingbats", ""));
}

TEST_F(GfxFontFlagsTest_1155, IsBase14Font_CaseSensitivity_1155) {
    // Test case sensitivity - base14 font names are case-sensitive
    bool lowerResult = GfxFont::isBase14Font("courier", "");
    bool upperResult = GfxFont::isBase14Font("COURIER", "");
    // These might or might not match depending on implementation
    // We just verify no crash
    (void)lowerResult;
    (void)upperResult;
}

TEST_F(GfxFontFlagsTest_1155, IsBase14Font_PartialMatch_1155) {
    // Partial font names should not match
    EXPECT_FALSE(GfxFont::isBase14Font("Cour", ""));
    EXPECT_FALSE(GfxFont::isBase14Font("Helv", ""));
    EXPECT_FALSE(GfxFont::isBase14Font("Tim", ""));
}

TEST_F(GfxFontFlagsTest_1155, IsBase14Font_ExtraCharacters_1155) {
    // Font names with extra characters should not match
    EXPECT_FALSE(GfxFont::isBase14Font("CourierNew", ""));
    EXPECT_FALSE(GfxFont::isBase14Font("HelveticaNeue", ""));
}

// Test getAlternateName with various known font names
TEST_F(GfxFontFlagsTest_1155, GetAlternateName_KnownFonts_1155) {
    // Test with some common font names that may have alternates
    // We can't know exact return values without implementation,
    // but we verify no crashes and consistent behavior
    
    const char* testNames[] = {
        "Courier", "Helvetica", "Times-Roman", "Symbol",
        "ZapfDingbats", "Arial", "TimesNewRoman"
    };
    
    for (const char* name : testNames) {
        const char* alternate = GfxFont::getAlternateName(name);
        // If an alternate exists, it should be a non-empty string
        if (alternate != nullptr) {
            EXPECT_GT(strlen(alternate), 0u) << "Alternate for " << name << " should be non-empty";
        }
    }
}

// Test consistency: calling getAlternateName twice returns same result
TEST_F(GfxFontFlagsTest_1155, GetAlternateName_ConsistentResults_1155) {
    const char* result1 = GfxFont::getAlternateName("Courier");
    const char* result2 = GfxFont::getAlternateName("Courier");
    
    if (result1 == nullptr) {
        EXPECT_EQ(result2, nullptr);
    } else {
        EXPECT_NE(result2, nullptr);
        EXPECT_STREQ(result1, result2);
    }
}

// Test isBase14Font consistency: calling twice returns same result
TEST_F(GfxFontFlagsTest_1155, IsBase14Font_ConsistentResults_1155) {
    bool result1 = GfxFont::isBase14Font("Courier", "");
    bool result2 = GfxFont::isBase14Font("Courier", "");
    EXPECT_EQ(result1, result2);
    EXPECT_TRUE(result1);
}

TEST_F(GfxFontFlagsTest_1155, IsBase14Font_WrongStyleForFamily_1155) {
    // Symbol with Bold style - may or may not be valid
    bool result = GfxFont::isBase14Font("Symbol", "Bold");
    // Symbol doesn't have a Bold variant in base 14
    EXPECT_FALSE(result);
}

TEST_F(GfxFontFlagsTest_1155, IsBase14Font_ZapfDingbatsWithStyle_1155) {
    // ZapfDingbats with a style should not match
    bool result = GfxFont::isBase14Font("ZapfDingbats", "Bold");
    EXPECT_FALSE(result);
}
