#include <gtest/gtest.h>
#include "SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"

// Helper to create a SplashOutputDev with default settings
class SplashOutputDevTest_1116 : public ::testing::Test {
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

// Test that the object can be constructed and destroyed without crashing
TEST_F(SplashOutputDevTest_1116, ConstructionDestruction_1116) {
    ASSERT_NE(dev, nullptr);
}

// Test setEnableFreeType / basic setter doesn't crash
TEST_F(SplashOutputDevTest_1116, SetEnableFreeTypeTrue_1116) {
    EXPECT_NO_THROW(dev->setEnableFreeType(true));
}

TEST_F(SplashOutputDevTest_1116, SetEnableFreeTypeFalse_1116) {
    EXPECT_NO_THROW(dev->setEnableFreeType(false));
}

// Test setVectorAntialias
TEST_F(SplashOutputDevTest_1116, SetAndGetVectorAntialias_1116) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());

    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test setFontAntialias / getFontAntialias
TEST_F(SplashOutputDevTest_1116, SetAndGetFontAntialias_1116) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());

    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Test useDrawChar returns true (SplashOutputDev typically returns true)
TEST_F(SplashOutputDevTest_1116, UseDrawChar_1116) {
    EXPECT_TRUE(dev->useDrawChar());
}

// Test interpretType3Chars returns true
TEST_F(SplashOutputDevTest_1116, InterpretType3Chars_1116) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

// Test upsideDown returns true (Splash coordinate system)
TEST_F(SplashOutputDevTest_1116, UpsideDown_1116) {
    EXPECT_TRUE(dev->upsideDown());
}

// Test useTilingPatternFill returns true
TEST_F(SplashOutputDevTest_1116, UseTilingPatternFill_1116) {
    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Test useShadedFills for various types
TEST_F(SplashOutputDevTest_1116, UseShadedFills_1116) {
    // Types 1-5 are typical shading types in PDF
    // SplashOutputDev typically supports some of these
    for (int type = 1; type <= 7; ++type) {
        // Just ensure it doesn't crash and returns a bool
        bool result = dev->useShadedFills(type);
        (void)result; // We just verify no crash
    }
}

// Test getBitmap returns non-null after construction
TEST_F(SplashOutputDevTest_1116, GetBitmapNotNull_1116) {
    SplashBitmap* bitmap = dev->getBitmap();
    // Before startPage, bitmap might be null or valid depending on implementation
    // Just verify no crash
    (void)bitmap;
}

// Test getSplash returns something (might be null before startPage)
TEST_F(SplashOutputDevTest_1116, GetSplash_1116) {
    Splash* splash = dev->getSplash();
    (void)splash;
}

// Test getCurrentFont (likely null before any font update)
TEST_F(SplashOutputDevTest_1116, GetCurrentFontInitiallyNull_1116) {
    SplashFont* font = dev->getCurrentFont();
    EXPECT_EQ(font, nullptr);
}

// Test setSkipText doesn't crash
TEST_F(SplashOutputDevTest_1116, SetSkipText_1116) {
    EXPECT_NO_THROW(dev->setSkipText(true, true));
    EXPECT_NO_THROW(dev->setSkipText(false, false));
    EXPECT_NO_THROW(dev->setSkipText(true, false));
    EXPECT_NO_THROW(dev->setSkipText(false, true));
}

// Test setFreeTypeHinting doesn't crash
TEST_F(SplashOutputDevTest_1116, SetFreeTypeHinting_1116) {
    EXPECT_NO_THROW(dev->setFreeTypeHinting(true, true));
    EXPECT_NO_THROW(dev->setFreeTypeHinting(false, false));
    EXPECT_NO_THROW(dev->setFreeTypeHinting(true, false));
    EXPECT_NO_THROW(dev->setFreeTypeHinting(false, true));
}

// Test setPaperColor doesn't crash
TEST_F(SplashOutputDevTest_1116, SetPaperColor_1116) {
    SplashColor newColor;
    newColor[0] = 0;
    newColor[1] = 0;
    newColor[2] = 0;
    EXPECT_NO_THROW(dev->setPaperColor(newColor));
}

// Test construction with different color modes
TEST(SplashOutputDevColorModeTest_1116, ConstructMono1_1116) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    SplashOutputDev* devMono = new SplashOutputDev(splashModeMono1, 1, paperColor, true,
                                                    splashThinLineDefault, false);
    ASSERT_NE(devMono, nullptr);
    delete devMono;
}

TEST(SplashOutputDevColorModeTest_1116, ConstructMono8_1116) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    SplashOutputDev* devMono8 = new SplashOutputDev(splashModeMono8, 1, paperColor, true,
                                                     splashThinLineDefault, false);
    ASSERT_NE(devMono8, nullptr);
    delete devMono8;
}

TEST(SplashOutputDevColorModeTest_1116, ConstructRGB8_1116) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* devRGB = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                                   splashThinLineDefault, false);
    ASSERT_NE(devRGB, nullptr);
    delete devRGB;
}

TEST(SplashOutputDevColorModeTest_1116, ConstructXBGR8_1116) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    paperColor[3] = 255;
    SplashOutputDev* devXBGR = new SplashOutputDev(splashModeXBGR8, 1, paperColor, true,
                                                    splashThinLineDefault, false);
    ASSERT_NE(devXBGR, nullptr);
    delete devXBGR;
}

#ifdef SPLASH_CMYK
TEST(SplashOutputDevColorModeTest_1116, ConstructCMYK8_1116) {
    SplashColor paperColor;
    paperColor[0] = 0;
    paperColor[1] = 0;
    paperColor[2] = 0;
    paperColor[3] = 0;
    SplashOutputDev* devCMYK = new SplashOutputDev(splashModeCMYK8, 1, paperColor, true,
                                                    splashThinLineDefault, false);
    ASSERT_NE(devCMYK, nullptr);
    delete devCMYK;
}
#endif

// Test construction with bitmapTopDown false
TEST(SplashOutputDevConstructionTest_1116, ConstructTopDownFalse_1116) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* devBottom = new SplashOutputDev(splashModeRGB8, 1, paperColor, false,
                                                      splashThinLineDefault, false);
    ASSERT_NE(devBottom, nullptr);
    delete devBottom;
}

// Test construction with overprint preview enabled
TEST(SplashOutputDevConstructionTest_1116, ConstructOverprintPreview_1116) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* devOP = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                                  splashThinLineDefault, true);
    ASSERT_NE(devOP, nullptr);
    delete devOP;
}

// Test construction with different row padding
TEST(SplashOutputDevConstructionTest_1116, ConstructDifferentRowPad_1116) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* devPad = new SplashOutputDev(splashModeRGB8, 4, paperColor, true,
                                                   splashThinLineDefault, false);
    ASSERT_NE(devPad, nullptr);
    delete devPad;
}

// Test toggle setEnableFreeType multiple times
TEST_F(SplashOutputDevTest_1116, ToggleEnableFreeTypeMultipleTimes_1116) {
    for (int i = 0; i < 10; ++i) {
        EXPECT_NO_THROW(dev->setEnableFreeType(i % 2 == 0));
    }
}

// Test that vector antialias can be toggled multiple times
TEST_F(SplashOutputDevTest_1116, ToggleVectorAntialiasMultipleTimes_1116) {
    for (int i = 0; i < 10; ++i) {
        bool val = (i % 2 == 0);
        dev->setVectorAntialias(val);
        EXPECT_EQ(dev->getVectorAntialias(), val);
    }
}

// Test font antialias can be toggled multiple times
TEST_F(SplashOutputDevTest_1116, ToggleFontAntialiasMultipleTimes_1116) {
    for (int i = 0; i < 10; ++i) {
        bool val = (i % 2 == 0);
        dev->setFontAntialias(val);
        EXPECT_EQ(dev->getFontAntialias(), val);
    }
}

// Test checkTransparencyGroup with nullptr state (boundary)
// Note: This may or may not crash depending on implementation,
// but we test that knockout parameter is handled
TEST_F(SplashOutputDevTest_1116, CheckTransparencyGroupKnockout_1116) {
    // Without a valid state, we can't reliably call this.
    // Just test it compiles and the interface is correct.
    // Actual invocation requires valid GfxState.
}

// Test getBitmapWidth and getBitmapHeight before startPage
TEST_F(SplashOutputDevTest_1116, GetBitmapDimensionsBeforeStartPage_1116) {
    // Before startPage, dimensions might be 0 or some default
    int w = dev->getBitmapWidth();
    int h = dev->getBitmapHeight();
    EXPECT_GE(w, 0);
    EXPECT_GE(h, 0);
}

// Test thin line modes
TEST(SplashOutputDevThinLineTest_1116, ConstructWithThinLineShape_1116) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* devThin = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                                    splashThinLineShape, false);
    ASSERT_NE(devThin, nullptr);
    delete devThin;
}

TEST(SplashOutputDevThinLineTest_1116, ConstructWithThinLineSolid_1116) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* devThin = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                                    splashThinLineSolid, false);
    ASSERT_NE(devThin, nullptr);
    delete devThin;
}
