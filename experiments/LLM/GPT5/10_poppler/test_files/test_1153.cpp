#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"

// Mock dependencies (if needed)
class MockXRef : public XRef {};
class MockDict : public Dict {};

class GfxFontTest_1153 : public testing::Test {
protected:
    GfxFontTest_1153() = default;
    ~GfxFontTest_1153() override = default;
};

TEST_F(GfxFontTest_1153, isSymbolic_ReturnsTrue_WhenFontIsSymbolic) {
    // Mock the flags directly or use a constructor if possible (based on real implementation).
    GfxFont font(/*appropriate constructor args*/);
    // Mock flags to return a value that indicates the font is symbolic
    font.flags = fontSymbolic;  // Assuming flags can be set in tests, if not use appropriate setter.

    EXPECT_TRUE(font.isSymbolic());
}

TEST_F(GfxFontTest_1153, isSymbolic_ReturnsFalse_WhenFontIsNotSymbolic) {
    GfxFont font(/*appropriate constructor args*/);
    font.flags = 0;  // Flags set to a value that indicates no symbolic font.

    EXPECT_FALSE(font.isSymbolic());
}

TEST_F(GfxFontTest_1153, isSymbolic_ReturnsCorrectValue_AfterMultipleFlagsModifications) {
    GfxFont font(/*appropriate constructor args*/);

    // Test with symbolic font
    font.flags = fontSymbolic;
    EXPECT_TRUE(font.isSymbolic());

    // Test with non-symbolic font
    font.flags = 0;
    EXPECT_FALSE(font.isSymbolic());
}