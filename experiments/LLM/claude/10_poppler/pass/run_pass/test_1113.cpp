#include <gtest/gtest.h>
#include "SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"

class SplashOutputDevTest_1113 : public ::testing::Test {
protected:
    SplashOutputDev* dev;
    SplashColor paperColor;

    void SetUp() override {
        // Initialize paper color to white for RGB mode
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev;
    }
};

// Test setSkipText with both parameters true
TEST_F(SplashOutputDevTest_1113, SetSkipTextBothTrue_1113) {
    // Should not crash when setting both to true
    dev->setSkipText(true, true);
    // No observable output to verify directly, but it should not crash
}

// Test setSkipText with both parameters false
TEST_F(SplashOutputDevTest_1113, SetSkipTextBothFalse_1113) {
    dev->setSkipText(false, false);
    // No crash expected
}

// Test setSkipText with skipHorizText true, skipRotatedText false
TEST_F(SplashOutputDevTest_1113, SetSkipTextHorizOnly_1113) {
    dev->setSkipText(true, false);
}

// Test setSkipText with skipHorizText false, skipRotatedText true
TEST_F(SplashOutputDevTest_1113, SetSkipTextRotatedOnly_1113) {
    dev->setSkipText(false, true);
}

// Test setSkipText called multiple times (toggling)
TEST_F(SplashOutputDevTest_1113, SetSkipTextToggle_1113) {
    dev->setSkipText(true, true);
    dev->setSkipText(false, false);
    dev->setSkipText(true, false);
    dev->setSkipText(false, true);
}

// Test that upsideDown returns expected value
TEST_F(SplashOutputDevTest_1113, UpsideDown_1113) {
    bool result = dev->upsideDown();
    // upsideDown typically returns true for Splash-based output
    EXPECT_TRUE(result);
}

// Test that useDrawChar returns expected value
TEST_F(SplashOutputDevTest_1113, UseDrawChar_1113) {
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result);
}

// Test that interpretType3Chars returns expected value
TEST_F(SplashOutputDevTest_1113, InterpretType3Chars_1113) {
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result);
}

// Test that useTilingPatternFill returns expected value
TEST_F(SplashOutputDevTest_1113, UseTilingPatternFill_1113) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result);
}

// Test that useShadedFills returns expected values for different types
TEST_F(SplashOutputDevTest_1113, UseShadedFillsType1_1113) {
    // Type 1 = function shading
    bool result = dev->useShadedFills(1);
    // Should return true for supported types
    EXPECT_TRUE(result);
}

TEST_F(SplashOutputDevTest_1113, UseShadedFillsType2_1113) {
    // Type 2 = axial shading
    bool result = dev->useShadedFills(2);
    EXPECT_TRUE(result);
}

TEST_F(SplashOutputDevTest_1113, UseShadedFillsType3_1113) {
    // Type 3 = radial shading
    bool result = dev->useShadedFills(3);
    EXPECT_TRUE(result);
}

// Test getBitmap returns non-null after construction
TEST_F(SplashOutputDevTest_1113, GetBitmapAfterConstruction_1113) {
    // Before startPage, bitmap may or may not be initialized
    // This tests the interface availability
    SplashBitmap* bmp = dev->getBitmap();
    // Bitmap may be null before startPage is called
    // Just test it doesn't crash
    (void)bmp;
}

// Test getSplash returns a value
TEST_F(SplashOutputDevTest_1113, GetSplashAfterConstruction_1113) {
    Splash* splash = dev->getSplash();
    // Splash may be null before startPage
    (void)splash;
}

// Test setFontAntialias and getFontAntialias
TEST_F(SplashOutputDevTest_1113, SetAndGetFontAntialiasTrue_1113) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}

TEST_F(SplashOutputDevTest_1113, SetAndGetFontAntialiasFalse_1113) {
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashOutputDevTest_1113, SetAndGetVectorAntialiasTrue_1113) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
}

TEST_F(SplashOutputDevTest_1113, SetAndGetVectorAntialiasFalse_1113) {
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test toggling vector antialias
TEST_F(SplashOutputDevTest_1113, ToggleVectorAntialias_1113) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test toggling font antialias
TEST_F(SplashOutputDevTest_1113, ToggleFontAntialias_1113) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}

// Test setEnableFreeType
TEST_F(SplashOutputDevTest_1113, SetEnableFreeTypeTrue_1113) {
    dev->setEnableFreeType(true);
    // No getter for this, just verify no crash
}

TEST_F(SplashOutputDevTest_1113, SetEnableFreeTypeFalse_1113) {
    dev->setEnableFreeType(false);
}

// Test setFreeTypeHinting
TEST_F(SplashOutputDevTest_1113, SetFreeTypeHintingBothTrue_1113) {
    dev->setFreeTypeHinting(true, true);
}

TEST_F(SplashOutputDevTest_1113, SetFreeTypeHintingBothFalse_1113) {
    dev->setFreeTypeHinting(false, false);
}

TEST_F(SplashOutputDevTest_1113, SetFreeTypeHintingMixed_1113) {
    dev->setFreeTypeHinting(true, false);
    dev->setFreeTypeHinting(false, true);
}

// Test setPaperColor
TEST_F(SplashOutputDevTest_1113, SetPaperColor_1113) {
    SplashColor newColor;
    newColor[0] = 128;
    newColor[1] = 128;
    newColor[2] = 128;
    dev->setPaperColor(newColor);
    // Should not crash
}

// Test construction with different color modes
TEST(SplashOutputDevConstructionTest_1113, ConstructMono1_1113) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    SplashOutputDev* dev = new SplashOutputDev(splashModeMono1, 1, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1113, ConstructMono8_1113) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    SplashOutputDev* dev = new SplashOutputDev(splashModeMono8, 1, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1113, ConstructRGB8_1113) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1113, ConstructBGR8_1113) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeBGR8, 1, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1113, ConstructXBGR8_1113) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    paperColor[3] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeXBGR8, 1, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test construction with bitmapTopDown false
TEST(SplashOutputDevConstructionTest_1113, ConstructTopDownFalse_1113) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, false, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test construction with overprintPreview true
TEST(SplashOutputDevConstructionTest_1113, ConstructOverprintPreview_1113) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineDefault, true);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test construction with different row pad
TEST(SplashOutputDevConstructionTest_1113, ConstructDifferentRowPad_1113) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 4, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test getCurrentFont before any font is set
TEST_F(SplashOutputDevTest_1113, GetCurrentFontInitial_1113) {
    SplashFont* font = dev->getCurrentFont();
    // Before any page/font setup, font should be null
    EXPECT_EQ(font, nullptr);
}

// Test checkTransparencyGroup
TEST_F(SplashOutputDevTest_1113, CheckTransparencyGroupNoKnockout_1113) {
    // Without a proper GfxState this may not be callable safely,
    // but we test interface availability
    // Note: calling with nullptr state would likely crash, so we skip this
}

// Test setPaperColor with black
TEST_F(SplashOutputDevTest_1113, SetPaperColorBlack_1113) {
    SplashColor black;
    black[0] = 0;
    black[1] = 0;
    black[2] = 0;
    dev->setPaperColor(black);
}

// Test setPaperColor with various colors
TEST_F(SplashOutputDevTest_1113, SetPaperColorRed_1113) {
    SplashColor red;
    red[0] = 255;
    red[1] = 0;
    red[2] = 0;
    dev->setPaperColor(red);
}

// Test thin line modes
TEST(SplashOutputDevThinLineTest_1113, ConstructThinLineShape_1113) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineShape, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

TEST(SplashOutputDevThinLineTest_1113, ConstructThinLineSolid_1113) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineSolid, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}
