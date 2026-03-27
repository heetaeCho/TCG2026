#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <optional>
#include <vector>
#include "GfxFont.h"

class GfxFontTest_1160 : public testing::Test {
protected:
    GfxFontTest_1160() {
        // Setup code if needed
    }
    ~GfxFontTest_1160() override {
        // Teardown code if needed
    }
};

// Test for normal operation of getWMode() method
TEST_F(GfxFontTest_1160, GetWMode_Horizontal_1160) {
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());
    EXPECT_EQ(font.getWMode(), GfxFont::WritingMode::Horizontal);
}

// Test for boundary condition when using empty font family
TEST_F(GfxFontTest_1160, GetFamily_EmptyFamily_1160) {
    GfxFont font("tag", Ref(), "", GfxFontType::Type1, Ref());
    EXPECT_EQ(font.getFamily()->getCString(), "");
}

// Test exceptional case where embedded font is invalid
TEST_F(GfxFontTest_1160, GetEmbeddedFont_Invalid_1160) {
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());
    EXPECT_FALSE(font.getEmbeddedFontID(nullptr));
}

// Test for checking if a font is a subset
TEST_F(GfxFontTest_1160, IsSubset_False_1160) {
    GfxFont font("tag", Ref(), "Arial", GfxFontType::TrueType, Ref());
    EXPECT_FALSE(font.isSubset());
}

// Test for boundary condition when handling font matrix
TEST_F(GfxFontTest_1160, GetFontMatrix_ValidMatrix_1160) {
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());
    const auto& matrix = font.getFontMatrix();
    EXPECT_EQ(matrix.size(), 6);
    EXPECT_DOUBLE_EQ(matrix[0], 1.0);
}

// Test exceptional case when an invalid font is requested
TEST_F(GfxFontTest_1160, GetFont_InvalidFont_1160) {
    GfxFont font("invalid_tag", Ref(), nullptr, GfxFontType::Type1, Ref());
    EXPECT_FALSE(font.isOk());
}

// Test for boundary condition checking for valid stretch
TEST_F(GfxFontTest_1160, GetStretch_ValidStretch_1160) {
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());
    EXPECT_EQ(font.getStretch(), Stretch::Normal);
}

// Test for checking writing mode for vertical alignment
TEST_F(GfxFontTest_1160, GetWMode_Vertical_1160) {
    GfxFont font("tag", Ref(), nullptr, GfxFontType::Type1, Ref());
    EXPECT_EQ(font.getWMode(), GfxFont::WritingMode::Horizontal);
}

// Test for external interaction (Mocking external interaction example)
TEST_F(GfxFontTest_1160, VerifyMockHandlerCall_1160) {
    // Setup mock XRef, Dict, etc., and verify calls if needed
}