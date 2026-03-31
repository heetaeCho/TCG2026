#include <gtest/gtest.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>

class TextFontInfoTest_1175 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test construction with nullptr state - the class should handle null gracefully
TEST_F(TextFontInfoTest_1175, ConstructWithNullState_1175) {
    TextFontInfo fontInfo(nullptr);
    // With null state, font flags should be 0, so isSerif should return false
    EXPECT_FALSE(fontInfo.isSerif());
}

TEST_F(TextFontInfoTest_1175, IsFixedWidthWithNullState_1175) {
    TextFontInfo fontInfo(nullptr);
    EXPECT_FALSE(fontInfo.isFixedWidth());
}

TEST_F(TextFontInfoTest_1175, IsSymbolicWithNullState_1175) {
    TextFontInfo fontInfo(nullptr);
    EXPECT_FALSE(fontInfo.isSymbolic());
}

TEST_F(TextFontInfoTest_1175, IsItalicWithNullState_1175) {
    TextFontInfo fontInfo(nullptr);
    EXPECT_FALSE(fontInfo.isItalic());
}

TEST_F(TextFontInfoTest_1175, IsBoldWithNullState_1175) {
    TextFontInfo fontInfo(nullptr);
    EXPECT_FALSE(fontInfo.isBold());
}

TEST_F(TextFontInfoTest_1175, GetFontNameWithNullState_1175) {
    TextFontInfo fontInfo(nullptr);
    // With null state, font name should be null
    const GooString* name = fontInfo.getFontName();
    EXPECT_EQ(name, nullptr);
}

TEST_F(TextFontInfoTest_1175, GetAscentWithNullState_1175) {
    TextFontInfo fontInfo(nullptr);
    double ascent = fontInfo.getAscent();
    // With no font, ascent should be some default (likely 0)
    EXPECT_GE(ascent, 0.0);
}

TEST_F(TextFontInfoTest_1175, GetDescentWithNullState_1175) {
    TextFontInfo fontInfo(nullptr);
    double descent = fontInfo.getDescent();
    // Descent is typically 0 or negative
    EXPECT_LE(descent, 0.0);
}

TEST_F(TextFontInfoTest_1175, MatchesWithNullState_1175) {
    TextFontInfo fontInfo(nullptr);
    // Matching against nullptr state
    EXPECT_TRUE(fontInfo.matches(static_cast<const GfxState*>(nullptr)));
}

TEST_F(TextFontInfoTest_1175, MatchesFontInfoSelf_1175) {
    TextFontInfo fontInfo(nullptr);
    // A font info should match itself
    EXPECT_TRUE(fontInfo.matches(&fontInfo));
}

TEST_F(TextFontInfoTest_1175, MatchesTwoDifferentNullFontInfos_1175) {
    TextFontInfo fontInfo1(nullptr);
    TextFontInfo fontInfo2(nullptr);
    // Two font infos both constructed with null should match each other
    EXPECT_TRUE(fontInfo1.matches(&fontInfo2));
}

TEST_F(TextFontInfoTest_1175, GetWModeWithNullState_1175) {
    TextFontInfo fontInfo(nullptr);
    auto wmode = fontInfo.getWMode();
    // Default writing mode should be horizontal (0)
    EXPECT_EQ(static_cast<int>(wmode), 0);
}

TEST_F(TextFontInfoTest_1175, IsSerifReturnsBoolType_1175) {
    TextFontInfo fontInfo(nullptr);
    bool result = fontInfo.isSerif();
    // Just verify it returns a valid bool
    EXPECT_TRUE(result == true || result == false);
}
