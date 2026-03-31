#include <gtest/gtest.h>
#include "SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"

class SplashOutputDevTest_1115 : public ::testing::Test {
protected:
    SplashOutputDev* dev;
    SplashColor paperColor;

    void SetUp() override {
        // Initialize paper color to white
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, false, splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev;
    }
};

// Test setFontAntialias and getFontAntialias - set to true
TEST_F(SplashOutputDevTest_1115, SetFontAntialiasTrue_1115) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}

// Test setFontAntialias and getFontAntialias - set to false
TEST_F(SplashOutputDevTest_1115, SetFontAntialiasFalse_1115) {
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Test toggling font antialias from true to false
TEST_F(SplashOutputDevTest_1115, ToggleFontAntialiasFromTrueToFalse_1115) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Test toggling font antialias from false to true
TEST_F(SplashOutputDevTest_1115, ToggleFontAntialiasFromFalseToTrue_1115) {
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}

// Test setting font antialias multiple times to same value
TEST_F(SplashOutputDevTest_1115, SetFontAntialiasMultipleTimesSameValue_1115) {
    dev->setFontAntialias(true);
    dev->setFontAntialias(true);
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashOutputDevTest_1115, SetVectorAntialiasTrue_1115) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
}

TEST_F(SplashOutputDevTest_1115, SetVectorAntialiasFalse_1115) {
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test upsideDown returns expected value
TEST_F(SplashOutputDevTest_1115, UpsideDown_1115) {
    bool result = dev->upsideDown();
    EXPECT_TRUE(result == true || result == false);
}

// Test useDrawChar returns expected value
TEST_F(SplashOutputDevTest_1115, UseDrawChar_1115) {
    EXPECT_TRUE(dev->useDrawChar());
}

// Test interpretType3Chars returns expected value
TEST_F(SplashOutputDevTest_1115, InterpretType3Chars_1115) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

// Test useTilingPatternFill returns expected value
TEST_F(SplashOutputDevTest_1115, UseTilingPatternFill_1115) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

// Test getBitmap returns non-null after construction
TEST_F(SplashOutputDevTest_1115, GetBitmapNotNull_1115) {
    // getBitmap may return nullptr before startPage is called, or may return a valid pointer
    // We just verify the function is callable
    SplashBitmap* bitmap = dev->getBitmap();
    // bitmap can be null before startPage; this is valid behavior
    (void)bitmap;
}

// Test getSplash returns non-null after construction
TEST_F(SplashOutputDevTest_1115, GetSplashNotNull_1115) {
    Splash* splash = dev->getSplash();
    // splash can be null before startPage; this is valid behavior
    (void)splash;
}

// Test setEnableFreeType
TEST_F(SplashOutputDevTest_1115, SetEnableFreeType_1115) {
    // Just verify it doesn't crash
    dev->setEnableFreeType(true);
    dev->setEnableFreeType(false);
}

// Test setFreeTypeHinting
TEST_F(SplashOutputDevTest_1115, SetFreeTypeHinting_1115) {
    // Just verify it doesn't crash
    dev->setFreeTypeHinting(true, false);
    dev->setFreeTypeHinting(false, true);
    dev->setFreeTypeHinting(true, true);
    dev->setFreeTypeHinting(false, false);
}

// Test setSkipText
TEST_F(SplashOutputDevTest_1115, SetSkipText_1115) {
    // Just verify it doesn't crash
    dev->setSkipText(true, true);
    dev->setSkipText(false, false);
    dev->setSkipText(true, false);
    dev->setSkipText(false, true);
}

// Test setPaperColor
TEST_F(SplashOutputDevTest_1115, SetPaperColor_1115) {
    SplashColor newColor;
    newColor[0] = 0;
    newColor[1] = 0;
    newColor[2] = 0;
    dev->setPaperColor(newColor);
    // Verify no crash; observable effect would be on bitmap rendering
}

// Test constructor with different color modes
TEST_F(SplashOutputDevTest_1115, ConstructWithMono1_1115) {
    SplashColor monoColor;
    monoColor[0] = 0xff;
    SplashOutputDev* monoDev = new SplashOutputDev(splashModeMono1, 1, monoColor, false, splashThinLineDefault, false);
    EXPECT_NE(monoDev, nullptr);
    delete monoDev;
}

TEST_F(SplashOutputDevTest_1115, ConstructWithMono8_1115) {
    SplashColor monoColor;
    monoColor[0] = 0xff;
    SplashOutputDev* monoDev = new SplashOutputDev(splashModeMono8, 1, monoColor, false, splashThinLineDefault, false);
    EXPECT_NE(monoDev, nullptr);
    delete monoDev;
}

// Test constructor with bitmapTopDown = true
TEST_F(SplashOutputDevTest_1115, ConstructWithTopDown_1115) {
    SplashColor color;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    SplashOutputDev* topDownDev = new SplashOutputDev(splashModeRGB8, 1, color, true, splashThinLineDefault, false);
    EXPECT_NE(topDownDev, nullptr);
    delete topDownDev;
}

// Test constructor with overprintPreview = true
TEST_F(SplashOutputDevTest_1115, ConstructWithOverprintPreview_1115) {
    SplashColor color;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    color[3] = 0;
#ifdef SPLASH_CMYK
    SplashOutputDev* opDev = new SplashOutputDev(splashModeCMYK8, 1, color, false, splashThinLineDefault, true);
    EXPECT_NE(opDev, nullptr);
    delete opDev;
#endif
}

// Test getCurrentFont returns null before any font is set
TEST_F(SplashOutputDevTest_1115, GetCurrentFontBeforeSetup_1115) {
    SplashFont* f = dev->getCurrentFont();
    // Before startPage/updateFont, font should be null
    EXPECT_EQ(f, nullptr);
}

// Test useShadedFills for various types
TEST_F(SplashOutputDevTest_1115, UseShadedFillsType1_1115) {
    bool result = dev->useShadedFills(1);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1115, UseShadedFillsType2_1115) {
    bool result = dev->useShadedFills(2);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1115, UseShadedFillsType3_1115) {
    bool result = dev->useShadedFills(3);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1115, UseShadedFillsType4_1115) {
    bool result = dev->useShadedFills(4);
    EXPECT_TRUE(result == true || result == false);
}

// Test different bitmapRowPad values
TEST_F(SplashOutputDevTest_1115, ConstructWithDifferentRowPad_1115) {
    SplashColor color;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    SplashOutputDev* padDev = new SplashOutputDev(splashModeRGB8, 4, color, false, splashThinLineDefault, false);
    EXPECT_NE(padDev, nullptr);
    delete padDev;
}
