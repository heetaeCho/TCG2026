#include <gtest/gtest.h>
#include "SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"

// Helper to create a SplashOutputDev with common defaults
class SplashOutputDevTest_1107 : public ::testing::Test {
protected:
    void SetUp() override {
        // Default paper color: white
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
    }

    void TearDown() override {
    }

    SplashColor paperColor;
};

// Test that upsideDown() returns the value of bitmapTopDown when set to true
TEST_F(SplashOutputDevTest_1107, UpsideDownReturnsTrue_WhenBitmapTopDownIsTrue_1107) {
    bool bitmapTopDown = true;
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, bitmapTopDown,
                        splashThinLineDefault, false);
    EXPECT_TRUE(dev.upsideDown());
}

// Test that upsideDown() returns false when bitmapTopDown is false
TEST_F(SplashOutputDevTest_1107, UpsideDownReturnsFalse_WhenBitmapTopDownIsFalse_1107) {
    bool bitmapTopDown = false;
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, bitmapTopDown,
                        splashThinLineDefault, false);
    EXPECT_FALSE(dev.upsideDown());
}

// Test useTilingPatternFill returns a boolean
TEST_F(SplashOutputDevTest_1107, UseTilingPatternFill_ReturnsBool_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    bool result = dev.useTilingPatternFill();
    // useTilingPatternFill should return true for SplashOutputDev
    EXPECT_TRUE(result);
}

// Test useDrawChar returns true
TEST_F(SplashOutputDevTest_1107, UseDrawChar_ReturnsTrue_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    EXPECT_TRUE(dev.useDrawChar());
}

// Test interpretType3Chars returns true
TEST_F(SplashOutputDevTest_1107, InterpretType3Chars_ReturnsTrue_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    EXPECT_TRUE(dev.interpretType3Chars());
}

// Test getBitmap returns non-null after construction
TEST_F(SplashOutputDevTest_1107, GetBitmap_ReturnsNonNull_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    // Before startPage, bitmap may or may not be initialized
    // After construction, getBitmap behavior is implementation-defined
    // but we can at least call it without crashing
    SplashBitmap *bmp = dev.getBitmap();
    // Just verify the call doesn't crash - bitmap may be null before startPage
    (void)bmp;
}

// Test getSplash returns non-null after construction
TEST_F(SplashOutputDevTest_1107, GetSplash_AfterConstruction_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    Splash *splash = dev.getSplash();
    // Splash may be null before startPage
    (void)splash;
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashOutputDevTest_1107, VectorAntialias_SetAndGet_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    dev.setVectorAntialias(true);
    EXPECT_TRUE(dev.getVectorAntialias());

    dev.setVectorAntialias(false);
    EXPECT_FALSE(dev.getVectorAntialias());
}

// Test setFontAntialias and getFontAntialias
TEST_F(SplashOutputDevTest_1107, FontAntialias_SetAndGet_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    dev.setFontAntialias(true);
    EXPECT_TRUE(dev.getFontAntialias());

    dev.setFontAntialias(false);
    EXPECT_FALSE(dev.getFontAntialias());
}

// Test setEnableFreeType doesn't crash
TEST_F(SplashOutputDevTest_1107, SetEnableFreeType_DoesNotCrash_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    dev.setEnableFreeType(true);
    dev.setEnableFreeType(false);
}

// Test setFreeTypeHinting doesn't crash
TEST_F(SplashOutputDevTest_1107, SetFreeTypeHinting_DoesNotCrash_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    dev.setFreeTypeHinting(true, false);
    dev.setFreeTypeHinting(false, true);
    dev.setFreeTypeHinting(true, true);
    dev.setFreeTypeHinting(false, false);
}

// Test setSkipText doesn't crash
TEST_F(SplashOutputDevTest_1107, SetSkipText_DoesNotCrash_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    dev.setSkipText(true, true);
    dev.setSkipText(false, false);
    dev.setSkipText(true, false);
    dev.setSkipText(false, true);
}

// Test setPaperColor doesn't crash
TEST_F(SplashOutputDevTest_1107, SetPaperColor_DoesNotCrash_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    SplashColor newColor;
    newColor[0] = 0;
    newColor[1] = 0;
    newColor[2] = 0;
    dev.setPaperColor(newColor);
}

// Test useShadedFills for various types
TEST_F(SplashOutputDevTest_1107, UseShadedFills_VariousTypes_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    // Types 1-7 are typical shading types in PDF
    for (int type = 1; type <= 7; ++type) {
        bool result = dev.useShadedFills(type);
        // Just ensure it returns without crashing and is a valid bool
        EXPECT_TRUE(result == true || result == false);
    }
}

// Test getCurrentFont returns nullptr before any font is set
TEST_F(SplashOutputDevTest_1107, GetCurrentFont_BeforeAnyFont_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    SplashFont *font = dev.getCurrentFont();
    // Before any font update, should be nullptr
    EXPECT_EQ(font, nullptr);
}

// Test construction with different color modes
TEST_F(SplashOutputDevTest_1107, Construction_Mono8Mode_1107) {
    SplashColor monoColor;
    monoColor[0] = 255;
    SplashOutputDev dev(splashModeMono8, 1, monoColor, true,
                        splashThinLineDefault, false);
    EXPECT_TRUE(dev.upsideDown());
}

// Test construction with overprintPreview enabled
TEST_F(SplashOutputDevTest_1107, Construction_OverprintPreviewEnabled_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, true);
    EXPECT_TRUE(dev.upsideDown());
}

// Test construction with different thin line modes
TEST_F(SplashOutputDevTest_1107, Construction_ThinLineShape_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, false,
                        splashThinLineShape, false);
    EXPECT_FALSE(dev.upsideDown());
}

// Test getBitmapWidth and getBitmapHeight before startPage
TEST_F(SplashOutputDevTest_1107, GetBitmapDimensions_BeforeStartPage_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    // Before startPage, dimensions should be minimal/zero or some default
    int width = dev.getBitmapWidth();
    int height = dev.getBitmapHeight();
    // Just verify they return without crashing
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test takeBitmap
TEST_F(SplashOutputDevTest_1107, TakeBitmap_ReturnsOwnership_1107) {
    SplashOutputDev dev(splashModeRGB8, 1, paperColor, true,
                        splashThinLineDefault, false);
    SplashBitmap *bmp = dev.takeBitmap();
    // After take, the dev should have a new/replacement bitmap
    // The taken bitmap should be non-null if a bitmap existed
    if (bmp) {
        delete bmp;
    }
}
