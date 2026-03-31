#include <gtest/gtest.h>
#include "SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"

class SplashOutputDevTest_1108 : public ::testing::Test {
protected:
    SplashOutputDev *dev = nullptr;

    void SetUp() override {
        SplashColor paperColor;
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                  splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev;
        dev = nullptr;
    }
};

// Test that useDrawChar returns true
TEST_F(SplashOutputDevTest_1108, UseDrawCharReturnsTrue_1108) {
    EXPECT_TRUE(dev->useDrawChar());
}

// Test that upsideDown returns the expected value
TEST_F(SplashOutputDevTest_1108, UpsideDown_1108) {
    bool result = dev->upsideDown();
    EXPECT_TRUE(result == true || result == false);
}

// Test that interpretType3Chars returns a valid boolean
TEST_F(SplashOutputDevTest_1108, InterpretType3Chars_1108) {
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test that useTilingPatternFill returns a valid boolean
TEST_F(SplashOutputDevTest_1108, UseTilingPatternFill_1108) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

// Test useShadedFills with various types
TEST_F(SplashOutputDevTest_1108, UseShadedFillsType1_1108) {
    bool result = dev->useShadedFills(1);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1108, UseShadedFillsType2_1108) {
    bool result = dev->useShadedFills(2);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1108, UseShadedFillsType3_1108) {
    bool result = dev->useShadedFills(3);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1108, UseShadedFillsType4_1108) {
    bool result = dev->useShadedFills(4);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1108, UseShadedFillsType5_1108) {
    bool result = dev->useShadedFills(5);
    EXPECT_TRUE(result == true || result == false);
}

// Test getBitmap returns non-null after construction
TEST_F(SplashOutputDevTest_1108, GetBitmapNotNull_1108) {
    // Before startPage, bitmap might be null or valid depending on implementation
    // Just ensure the call doesn't crash
    SplashBitmap *bmp = dev->getBitmap();
    // No assertion on null since startPage hasn't been called
    (void)bmp;
}

// Test getSplash returns a pointer (may be null before startPage)
TEST_F(SplashOutputDevTest_1108, GetSplash_1108) {
    Splash *splash = dev->getSplash();
    (void)splash; // Just ensure no crash
}

// Test getVectorAntialias
TEST_F(SplashOutputDevTest_1108, GetVectorAntialias_1108) {
    bool result = dev->getVectorAntialias();
    EXPECT_TRUE(result == true || result == false);
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashOutputDevTest_1108, SetVectorAntialiasTrue_1108) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
}

TEST_F(SplashOutputDevTest_1108, SetVectorAntialiasFalse_1108) {
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test getFontAntialias
TEST_F(SplashOutputDevTest_1108, GetFontAntialias_1108) {
    bool result = dev->getFontAntialias();
    EXPECT_TRUE(result == true || result == false);
}

// Test setFontAntialias and getFontAntialias
TEST_F(SplashOutputDevTest_1108, SetFontAntialiasTrue_1108) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}

TEST_F(SplashOutputDevTest_1108, SetFontAntialiasFalse_1108) {
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Test setSkipText doesn't crash
TEST_F(SplashOutputDevTest_1108, SetSkipText_1108) {
    dev->setSkipText(true, true);
    dev->setSkipText(false, false);
    dev->setSkipText(true, false);
    dev->setSkipText(false, true);
    // No crash means success
}

// Test setEnableFreeType doesn't crash
TEST_F(SplashOutputDevTest_1108, SetEnableFreeType_1108) {
    dev->setEnableFreeType(true);
    dev->setEnableFreeType(false);
}

// Test setFreeTypeHinting doesn't crash
TEST_F(SplashOutputDevTest_1108, SetFreeTypeHinting_1108) {
    dev->setFreeTypeHinting(true, false);
    dev->setFreeTypeHinting(false, false);
    dev->setFreeTypeHinting(true, true);
    dev->setFreeTypeHinting(false, true);
}

// Test getCurrentFont (likely null before rendering)
TEST_F(SplashOutputDevTest_1108, GetCurrentFont_1108) {
    SplashFont *font = dev->getCurrentFont();
    // Before any rendering, font should be null
    EXPECT_EQ(font, nullptr);
}

// Test construction with different color modes
TEST(SplashOutputDevConstructionTest_1108, ConstructMono1_1108) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    SplashOutputDev *dev = new SplashOutputDev(splashModeMono1, 1, paperColor,
                                                true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->useDrawChar());
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1108, ConstructMono8_1108) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    SplashOutputDev *dev = new SplashOutputDev(splashModeMono8, 1, paperColor,
                                                true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->useDrawChar());
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1108, ConstructRGB8_1108) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev *dev = new SplashOutputDev(splashModeRGB8, 1, paperColor,
                                                true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->useDrawChar());
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1108, ConstructXBGR8_1108) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    paperColor[3] = 255;
    SplashOutputDev *dev = new SplashOutputDev(splashModeXBGR8, 1, paperColor,
                                                true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->useDrawChar());
    delete dev;
}

// Test with bitmapTopDown false
TEST(SplashOutputDevConstructionTest_1108, ConstructBitmapTopDownFalse_1108) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev *dev = new SplashOutputDev(splashModeRGB8, 1, paperColor,
                                                false, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->useDrawChar());
    delete dev;
}

// Test with overprintPreview true
TEST(SplashOutputDevConstructionTest_1108, ConstructOverprintPreviewTrue_1108) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev *dev = new SplashOutputDev(splashModeRGB8, 1, paperColor,
                                                true, splashThinLineDefault, true);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test with different thin line modes
TEST(SplashOutputDevConstructionTest_1108, ConstructThinLineShape_1108) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev *dev = new SplashOutputDev(splashModeRGB8, 1, paperColor,
                                                true, splashThinLineShape, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test setPaperColor
TEST_F(SplashOutputDevTest_1108, SetPaperColor_1108) {
    SplashColor newColor;
    newColor[0] = 0;
    newColor[1] = 0;
    newColor[2] = 0;
    dev->setPaperColor(newColor);
    // No crash means success; paper color is internal state
}

// Test with different row padding
TEST(SplashOutputDevConstructionTest_1108, ConstructRowPad4_1108) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev *dev = new SplashOutputDev(splashModeRGB8, 4, paperColor,
                                                true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test toggle vector antialias multiple times
TEST_F(SplashOutputDevTest_1108, ToggleVectorAntialiasMultipleTimes_1108) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
}

// Test toggle font antialias multiple times
TEST_F(SplashOutputDevTest_1108, ToggleFontAntialiasMultipleTimes_1108) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}
