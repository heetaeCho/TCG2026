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
#include <optional>

class GfxFontTest_1150 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test static method getAlternateName with known base14 font names
TEST_F(GfxFontTest_1150, GetAlternateName_Courier_1150) {
    const char *alt = GfxFont::getAlternateName("Courier");
    // May return nullptr or a valid alternate name
    // We just verify it doesn't crash and returns something reasonable
    // for a well-known font
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

TEST_F(GfxFontTest_1150, GetAlternateName_NullInput_1150) {
    // Testing with an unknown font name
    const char *alt = GfxFont::getAlternateName("CompletelyUnknownFontXYZ123");
    // Should return nullptr for unknown fonts
    EXPECT_EQ(alt, nullptr);
}

TEST_F(GfxFontTest_1150, GetAlternateName_TimesRoman_1150) {
    const char *alt = GfxFont::getAlternateName("Times-Roman");
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

TEST_F(GfxFontTest_1150, GetAlternateName_Helvetica_1150) {
    const char *alt = GfxFont::getAlternateName("Helvetica");
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

TEST_F(GfxFontTest_1150, GetAlternateName_EmptyString_1150) {
    const char *alt = GfxFont::getAlternateName("");
    EXPECT_EQ(alt, nullptr);
}

// Test static method isBase14Font with string_view overload
TEST_F(GfxFontTest_1150, IsBase14Font_CourierRegular_1150) {
    bool result = GfxFont::isBase14Font("Courier", "");
    // Courier is a base14 font
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_TimesRomanRegular_1150) {
    bool result = GfxFont::isBase14Font("Times", "Roman");
    // Times-Roman is a base14 font
    // The exact interface behavior depends on implementation
    // but we test the call doesn't crash
    (void)result;
}

TEST_F(GfxFontTest_1150, IsBase14Font_HelveticaRegular_1150) {
    bool result = GfxFont::isBase14Font("Helvetica", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_UnknownFont_1150) {
    bool result = GfxFont::isBase14Font("SomeRandomFont", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_CourierBold_1150) {
    bool result = GfxFont::isBase14Font("Courier", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_CourierBoldOblique_1150) {
    bool result = GfxFont::isBase14Font("Courier", "BoldOblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_CourierOblique_1150) {
    bool result = GfxFont::isBase14Font("Courier", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_HelveticaBold_1150) {
    bool result = GfxFont::isBase14Font("Helvetica", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_Symbol_1150) {
    bool result = GfxFont::isBase14Font("Symbol", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_ZapfDingbats_1150) {
    bool result = GfxFont::isBase14Font("ZapfDingbats", "");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_EmptyStrings_1150) {
    bool result = GfxFont::isBase14Font("", "");
    EXPECT_FALSE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_TimesBold_1150) {
    bool result = GfxFont::isBase14Font("Times", "Bold");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_TimesItalic_1150) {
    bool result = GfxFont::isBase14Font("Times", "Italic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_TimesBoldItalic_1150) {
    bool result = GfxFont::isBase14Font("Times", "BoldItalic");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_HelveticaOblique_1150) {
    bool result = GfxFont::isBase14Font("Helvetica", "Oblique");
    EXPECT_TRUE(result);
}

TEST_F(GfxFontTest_1150, IsBase14Font_HelveticaBoldOblique_1150) {
    bool result = GfxFont::isBase14Font("Helvetica", "BoldOblique");
    EXPECT_TRUE(result);
}

// Test makeFont with nullptr/invalid inputs - should handle gracefully
TEST_F(GfxFontTest_1150, MakeFont_NullXRef_1150) {
    // Creating a minimal Dict for testing
    // makeFont with null xref should either return nullptr or handle gracefully
    // This depends on the implementation but tests robustness
    auto font = GfxFont::makeFont(nullptr, "F1", Ref::INVALID(), nullptr);
    // Expect null or invalid font when given null inputs
    if (font) {
        EXPECT_FALSE(font->isOk());
    } else {
        EXPECT_EQ(font, nullptr);
    }
}

// Test with a minimal valid setup if possible
TEST_F(GfxFontTest_1150, MakeFont_NullDict_1150) {
    auto font = GfxFont::makeFont(nullptr, "F1", Ref::INVALID(), nullptr);
    if (font) {
        EXPECT_FALSE(font->isOk());
    }
}

// Test flag-related methods conceptually: these are bit-flag checks
// We test them through a font object if we can create one
TEST_F(GfxFontTest_1150, GetAlternateName_CourierBold_1150) {
    const char *alt = GfxFont::getAlternateName("Courier-Bold");
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

TEST_F(GfxFontTest_1150, GetAlternateName_HelveticaBold_1150) {
    const char *alt = GfxFont::getAlternateName("Helvetica-Bold");
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

TEST_F(GfxFontTest_1150, GetAlternateName_TimesItalic_1150) {
    const char *alt = GfxFont::getAlternateName("Times-Italic");
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

TEST_F(GfxFontTest_1150, GetAlternateName_Symbol_1150) {
    const char *alt = GfxFont::getAlternateName("Symbol");
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

TEST_F(GfxFontTest_1150, GetAlternateName_ZapfDingbats_1150) {
    const char *alt = GfxFont::getAlternateName("ZapfDingbats");
    if (alt != nullptr) {
        EXPECT_TRUE(strlen(alt) > 0);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
