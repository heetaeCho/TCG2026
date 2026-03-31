#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>

class TextFontInfoTest_1178 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Since TextFontInfo requires a GfxState* for construction, and GfxState
// requires complex setup, we test with nullptr state to check robustness,
// and with valid states where possible.

TEST_F(TextFontInfoTest_1178, ConstructWithNullState_1178) {
    // Test construction with null GfxState - the constructor should handle this
    // This tests boundary/error behavior
    TextFontInfo fontInfo(nullptr);
    
    // After construction with null state, font name should be null or empty
    const GooString* name = fontInfo.getFontName();
    // Just verify we can call it without crashing
    (void)name;
}

TEST_F(TextFontInfoTest_1178, IsBoldWithNullState_1178) {
    TextFontInfo fontInfo(nullptr);
    // With no font, bold flag should be false
    bool bold = fontInfo.isBold();
    EXPECT_FALSE(bold);
}

TEST_F(TextFontInfoTest_1178, IsItalicWithNullState_1178) {
    TextFontInfo fontInfo(nullptr);
    bool italic = fontInfo.isItalic();
    EXPECT_FALSE(italic);
}

TEST_F(TextFontInfoTest_1178, IsFixedWidthWithNullState_1178) {
    TextFontInfo fontInfo(nullptr);
    bool fixedWidth = fontInfo.isFixedWidth();
    EXPECT_FALSE(fixedWidth);
}

TEST_F(TextFontInfoTest_1178, IsSerifWithNullState_1178) {
    TextFontInfo fontInfo(nullptr);
    bool serif = fontInfo.isSerif();
    EXPECT_FALSE(serif);
}

TEST_F(TextFontInfoTest_1178, IsSymbolicWithNullState_1178) {
    TextFontInfo fontInfo(nullptr);
    bool symbolic = fontInfo.isSymbolic();
    EXPECT_FALSE(symbolic);
}

TEST_F(TextFontInfoTest_1178, GetAscentWithNullState_1178) {
    TextFontInfo fontInfo(nullptr);
    double ascent = fontInfo.getAscent();
    // With no font, ascent should have some default value
    (void)ascent;
}

TEST_F(TextFontInfoTest_1178, GetDescentWithNullState_1178) {
    TextFontInfo fontInfo(nullptr);
    double descent = fontInfo.getDescent();
    (void)descent;
}

TEST_F(TextFontInfoTest_1178, GetWModeWithNullState_1178) {
    TextFontInfo fontInfo(nullptr);
    auto wmode = fontInfo.getWMode();
    (void)wmode;
}

TEST_F(TextFontInfoTest_1178, MatchesWithNullState_1178) {
    TextFontInfo fontInfo(nullptr);
    // Test matches with null state
    bool result = fontInfo.matches(static_cast<const GfxState*>(nullptr));
    // When both have no font, they might match
    (void)result;
}

TEST_F(TextFontInfoTest_1178, MatchesFontInfoWithNullState_1178) {
    TextFontInfo fontInfo1(nullptr);
    TextFontInfo fontInfo2(nullptr);
    bool result = fontInfo1.matches(&fontInfo2);
    // Two TextFontInfo objects created with null state should match each other
    EXPECT_TRUE(result);
}

TEST_F(TextFontInfoTest_1178, GetFontNameWithNullState_1178) {
    TextFontInfo fontInfo(nullptr);
    const GooString* name = fontInfo.getFontName();
    // With null state, font name should be null
    EXPECT_EQ(name, nullptr);
}

TEST_F(TextFontInfoTest_1178, CopyConstructorDeleted_1178) {
    // Verify copy constructor is deleted - this is a compile-time check
    EXPECT_FALSE(std::is_copy_constructible<TextFontInfo>::value);
}

TEST_F(TextFontInfoTest_1178, CopyAssignmentDeleted_1178) {
    // Verify copy assignment is deleted - this is a compile-time check
    EXPECT_FALSE(std::is_copy_assignable<TextFontInfo>::value);
}
