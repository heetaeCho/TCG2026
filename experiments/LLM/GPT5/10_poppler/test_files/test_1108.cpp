#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/SplashOutputDev.h"

// Mock dependencies (if needed)
class MockGfxState : public GfxState {
    // Mock methods for GfxState if needed
};

// TEST: useDrawChar
TEST_F(SplashOutputDevTest_1108, useDrawChar_1108) {
    SplashOutputDev dev(SplashColorMode::eRGB, 8, nullptr, true, SplashThinLineMode::eThinLines, true);
    EXPECT_TRUE(dev.useDrawChar());
}

// TEST: setFontAntialias
TEST_F(SplashOutputDevTest_1108, setFontAntialias_1108) {
    SplashOutputDev dev(SplashColorMode::eRGB, 8, nullptr, true, SplashThinLineMode::eThinLines, true);

    dev.setFontAntialias(true);
    EXPECT_TRUE(dev.getFontAntialias());

    dev.setFontAntialias(false);
    EXPECT_FALSE(dev.getFontAntialias());
}

// TEST: getBitmap
TEST_F(SplashOutputDevTest_1108, getBitmap_1108) {
    SplashOutputDev dev(SplashColorMode::eRGB, 8, nullptr, true, SplashThinLineMode::eThinLines, true);
    
    // Simulate expected behavior based on provided interface
    SplashBitmap *bitmap = dev.getBitmap();
    EXPECT_NE(bitmap, nullptr);
}

// TEST: setEnableFreeType
TEST_F(SplashOutputDevTest_1108, setEnableFreeType_1108) {
    SplashOutputDev dev(SplashColorMode::eRGB, 8, nullptr, true, SplashThinLineMode::eThinLines, true);

    dev.setEnableFreeType(true);
    // Since no getter is provided for this property, verify via effects (like expected behavior)
    // In case of side effects or observable behavior, check them accordingly

    dev.setEnableFreeType(false);
    // Same as above, check for side effects or observable behavior
}

// Boundary Test: getBitmapWidth
TEST_F(SplashOutputDevTest_1108, getBitmapWidth_Boundary_1108) {
    SplashOutputDev dev(SplashColorMode::eRGB, 8, nullptr, true, SplashThinLineMode::eThinLines, true);
    EXPECT_GT(dev.getBitmapWidth(), 0);  // Ensure bitmap width is positive
}

// Boundary Test: getBitmapHeight
TEST_F(SplashOutputDevTest_1108, getBitmapHeight_Boundary_1108) {
    SplashOutputDev dev(SplashColorMode::eRGB, 8, nullptr, true, SplashThinLineMode::eThinLines, true);
    EXPECT_GT(dev.getBitmapHeight(), 0);  // Ensure bitmap height is positive
}

// Exceptional Test: getBitmap when not initialized
TEST_F(SplashOutputDevTest_1108, getBitmap_Exceptional_1108) {
    SplashOutputDev dev(SplashColorMode::eRGB, 8, nullptr, true, SplashThinLineMode::eThinLines, true);
    // Simulate an uninitialized bitmap or erroneous condition
    EXPECT_EQ(dev.getBitmap(), nullptr);
}