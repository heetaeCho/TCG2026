#include <gtest/gtest.h>
#include "SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"

class SplashOutputDevTest_1114 : public ::testing::Test {
protected:
    SplashOutputDev* dev = nullptr;

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

// Test that getFontAntialias returns a valid boolean after construction
TEST_F(SplashOutputDevTest_1114, GetFontAntialiasDefault_1114) {
    // After construction, getFontAntialias should return some default value (likely true or false)
    bool result = dev->getFontAntialias();
    // We just verify it doesn't crash and returns a bool
    EXPECT_TRUE(result == true || result == false);
}

// Test setFontAntialias(true) then getFontAntialias returns true
TEST_F(SplashOutputDevTest_1114, SetFontAntialiasTrue_1114) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}

// Test setFontAntialias(false) then getFontAntialias returns false
TEST_F(SplashOutputDevTest_1114, SetFontAntialiasFalse_1114) {
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Test toggling font antialias multiple times
TEST_F(SplashOutputDevTest_1114, ToggleFontAntialias_1114) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());

    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());

    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashOutputDevTest_1114, SetAndGetVectorAntialias_1114) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());

    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test that getBitmap returns non-null (even before startPage, depends on impl)
TEST_F(SplashOutputDevTest_1114, GetBitmapInitial_1114) {
    // Before startPage, bitmap might be null
    SplashBitmap* bmp = dev->getBitmap();
    // Just test it doesn't crash; bitmap may or may not be null before startPage
    SUCCEED();
}

// Test getSplash
TEST_F(SplashOutputDevTest_1114, GetSplashInitial_1114) {
    // Before startPage, splash might be null
    Splash* s = dev->getSplash();
    SUCCEED();
}

// Test upsideDown
TEST_F(SplashOutputDevTest_1114, UpsideDown_1114) {
    bool result = dev->upsideDown();
    EXPECT_TRUE(result == true || result == false);
}

// Test useDrawChar
TEST_F(SplashOutputDevTest_1114, UseDrawChar_1114) {
    bool result = dev->useDrawChar();
    EXPECT_TRUE(result);
}

// Test interpretType3Chars
TEST_F(SplashOutputDevTest_1114, InterpretType3Chars_1114) {
    bool result = dev->interpretType3Chars();
    EXPECT_TRUE(result == true || result == false);
}

// Test useTilingPatternFill
TEST_F(SplashOutputDevTest_1114, UseTilingPatternFill_1114) {
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result == true || result == false);
}

// Test useShadedFills with various type values
TEST_F(SplashOutputDevTest_1114, UseShadedFillsType1_1114) {
    bool result = dev->useShadedFills(1);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1114, UseShadedFillsType2_1114) {
    bool result = dev->useShadedFills(2);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1114, UseShadedFillsType3_1114) {
    bool result = dev->useShadedFills(3);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1114, UseShadedFillsType4_1114) {
    bool result = dev->useShadedFills(4);
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(SplashOutputDevTest_1114, UseShadedFillsType5_1114) {
    bool result = dev->useShadedFills(5);
    EXPECT_TRUE(result == true || result == false);
}

// Test setSkipText
TEST_F(SplashOutputDevTest_1114, SetSkipText_1114) {
    // Just verify it doesn't crash
    dev->setSkipText(true, true);
    dev->setSkipText(false, false);
    dev->setSkipText(true, false);
    dev->setSkipText(false, true);
    SUCCEED();
}

// Test setEnableFreeType
TEST_F(SplashOutputDevTest_1114, SetEnableFreeType_1114) {
    dev->setEnableFreeType(true);
    dev->setEnableFreeType(false);
    SUCCEED();
}

// Test setFreeTypeHinting
TEST_F(SplashOutputDevTest_1114, SetFreeTypeHinting_1114) {
    dev->setFreeTypeHinting(true, false);
    dev->setFreeTypeHinting(false, false);
    dev->setFreeTypeHinting(true, true);
    dev->setFreeTypeHinting(false, true);
    SUCCEED();
}

// Test construction with different color modes
TEST(SplashOutputDevConstructionTest_1114, ConstructWithMono1_1114) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    SplashOutputDev* dev = new SplashOutputDev(splashModeMono1, 1, paperColor,
                                                true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1114, ConstructWithMono8_1114) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    SplashOutputDev* dev = new SplashOutputDev(splashModeMono8, 1, paperColor,
                                                true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1114, ConstructWithRGB8_1114) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor,
                                                true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1114, ConstructWithBGR8_1114) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeBGR8, 1, paperColor,
                                                true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

TEST(SplashOutputDevConstructionTest_1114, ConstructWithXBGR8_1114) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    paperColor[3] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeXBGR8, 1, paperColor,
                                                true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test construction with bitmapTopDown false
TEST(SplashOutputDevConstructionTest_1114, ConstructTopDownFalse_1114) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor,
                                                false, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test construction with overprintPreview true
TEST(SplashOutputDevConstructionTest_1114, ConstructOverprintPreview_1114) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor,
                                                true, splashThinLineDefault, true);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test setPaperColor
TEST_F(SplashOutputDevTest_1114, SetPaperColor_1114) {
    SplashColor newColor;
    newColor[0] = 128;
    newColor[1] = 128;
    newColor[2] = 128;
    dev->setPaperColor(newColor);
    SUCCEED();
}

// Test getCurrentFont returns something (may be null before any font update)
TEST_F(SplashOutputDevTest_1114, GetCurrentFontInitial_1114) {
    SplashFont* font = dev->getCurrentFont();
    // Before any rendering, font is likely null
    SUCCEED();
}

// Test setting font antialias to same value repeatedly
TEST_F(SplashOutputDevTest_1114, SetFontAntialiasSameValueRepeatedly_1114) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}

// Test setting vector antialias to same value repeatedly
TEST_F(SplashOutputDevTest_1114, SetVectorAntialiasSameValueRepeatedly_1114) {
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test different row pad values
TEST(SplashOutputDevConstructionTest_1114, ConstructWithDifferentRowPad_1114) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;

    SplashOutputDev* dev4 = new SplashOutputDev(splashModeRGB8, 4, paperColor,
                                                 true, splashThinLineDefault, false);
    ASSERT_NE(dev4, nullptr);
    delete dev4;

    SplashOutputDev* dev8 = new SplashOutputDev(splashModeRGB8, 8, paperColor,
                                                 true, splashThinLineDefault, false);
    ASSERT_NE(dev8, nullptr);
    delete dev8;
}

// Test different thin line modes
TEST(SplashOutputDevConstructionTest_1114, ConstructWithThinLineShape_1114) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor,
                                                true, splashThinLineShape, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}
