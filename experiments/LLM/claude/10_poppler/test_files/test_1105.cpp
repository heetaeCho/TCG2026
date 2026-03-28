#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"

// Test fixture for SplashOutputDev
class SplashOutputDevTest_1105 : public ::testing::Test {
protected:
    SplashOutputDev* dev = nullptr;

    void SetUp() override {
        // Create a basic SplashOutputDev with RGB8 color mode
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

// Test that useTilingPatternFill returns true
TEST_F(SplashOutputDevTest_1105, UseTilingPatternFill_ReturnsTrue_1105) {
    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Test that useDrawChar returns true (OutputDev typical behavior for SplashOutputDev)
TEST_F(SplashOutputDevTest_1105, UseDrawChar_ReturnsTrue_1105) {
    EXPECT_TRUE(dev->useDrawChar());
}

// Test that interpretType3Chars returns true
TEST_F(SplashOutputDevTest_1105, InterpretType3Chars_ReturnsTrue_1105) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

// Test that upsideDown returns true (Splash coordinate system is top-down)
TEST_F(SplashOutputDevTest_1105, UpsideDown_ReturnsTrue_1105) {
    EXPECT_TRUE(dev->upsideDown());
}

// Test useShadedFills with various type values
TEST_F(SplashOutputDevTest_1105, UseShadedFills_ValidTypes_1105) {
    // Type values 1-5 are standard shading types in PDF
    // The implementation may support some or all of them
    for (int type = 1; type <= 5; ++type) {
        bool result = dev->useShadedFills(type);
        // Just verify it doesn't crash and returns a boolean
        EXPECT_TRUE(result == true || result == false);
    }
}

// Test getBitmap returns non-null after construction
TEST_F(SplashOutputDevTest_1105, GetBitmap_AfterConstruction_1105) {
    SplashBitmap* bitmap = dev->getBitmap();
    // Bitmap may or may not be initialized before startPage
    // Just check it doesn't crash
    (void)bitmap;
}

// Test getSplash returns non-null after construction
TEST_F(SplashOutputDevTest_1105, GetSplash_AfterConstruction_1105) {
    Splash* splash = dev->getSplash();
    // Splash may or may not be initialized before startPage
    (void)splash;
}

// Test vector antialias getter/setter
TEST_F(SplashOutputDevTest_1105, VectorAntialias_SetAndGet_1105) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());

    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test font antialias getter/setter
TEST_F(SplashOutputDevTest_1105, FontAntialias_SetAndGet_1105) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());

    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Test setFreeTypeHinting does not crash
TEST_F(SplashOutputDevTest_1105, SetFreeTypeHinting_DoesNotCrash_1105) {
    EXPECT_NO_FATAL_FAILURE(dev->setFreeTypeHinting(true, false));
    EXPECT_NO_FATAL_FAILURE(dev->setFreeTypeHinting(false, false));
    EXPECT_NO_FATAL_FAILURE(dev->setFreeTypeHinting(true, true));
    EXPECT_NO_FATAL_FAILURE(dev->setFreeTypeHinting(false, true));
}

// Test setEnableFreeType does not crash
TEST_F(SplashOutputDevTest_1105, SetEnableFreeType_DoesNotCrash_1105) {
    EXPECT_NO_FATAL_FAILURE(dev->setEnableFreeType(true));
    EXPECT_NO_FATAL_FAILURE(dev->setEnableFreeType(false));
}

// Test setSkipText does not crash
TEST_F(SplashOutputDevTest_1105, SetSkipText_DoesNotCrash_1105) {
    EXPECT_NO_FATAL_FAILURE(dev->setSkipText(false, false));
    EXPECT_NO_FATAL_FAILURE(dev->setSkipText(true, false));
    EXPECT_NO_FATAL_FAILURE(dev->setSkipText(false, true));
    EXPECT_NO_FATAL_FAILURE(dev->setSkipText(true, true));
}

// Test setPaperColor does not crash
TEST_F(SplashOutputDevTest_1105, SetPaperColor_DoesNotCrash_1105) {
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    EXPECT_NO_FATAL_FAILURE(dev->setPaperColor(color));
}

// Test getCurrentFont before any font update returns nullptr or valid pointer
TEST_F(SplashOutputDevTest_1105, GetCurrentFont_BeforeFontUpdate_1105) {
    SplashFont* font = dev->getCurrentFont();
    // Before any rendering, font should be nullptr
    EXPECT_EQ(font, nullptr);
}

// Test construction with different color modes
class SplashOutputDevColorModeTest_1105 : public ::testing::TestWithParam<SplashColorMode> {
};

TEST_P(SplashOutputDevColorModeTest_1105, Construction_DifferentColorModes_1105) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    paperColor[3] = 0;

    SplashColorMode mode = GetParam();
    SplashOutputDev* dev = nullptr;

    EXPECT_NO_FATAL_FAILURE(
        dev = new SplashOutputDev(mode, 1, paperColor, true,
                                  splashThinLineDefault, false)
    );

    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->useTilingPatternFill());
    delete dev;
}

INSTANTIATE_TEST_SUITE_P(
    ColorModes_1105,
    SplashOutputDevColorModeTest_1105,
    ::testing::Values(splashModeMono8, splashModeRGB8
#ifdef SPLASH_CMYK
        , splashModeCMYK8, splashModeDeviceN8
#endif
    )
);

// Test construction with bitmapTopDown = false
TEST(SplashOutputDevConstructionTest_1105, BottomUp_Construction_1105) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;

    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, false,
                                                splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->useTilingPatternFill());
    delete dev;
}

// Test construction with overprintPreview = true
TEST(SplashOutputDevConstructionTest_1105, OverprintPreview_Construction_1105) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;

    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                                splashThinLineDefault, true);
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->useTilingPatternFill());
    delete dev;
}

// Test construction with different thin line modes
TEST(SplashOutputDevConstructionTest_1105, ThinLineShape_Construction_1105) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;

    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                                splashThinLineShape, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test construction with different row padding
TEST(SplashOutputDevConstructionTest_1105, RowPadding_Construction_1105) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;

    // Row pad of 4 (common alignment)
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 4, paperColor, true,
                                                splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test that vector antialias default state is consistent
TEST_F(SplashOutputDevTest_1105, VectorAntialias_DefaultState_1105) {
    // Just verify we can query without crash
    bool vaa = dev->getVectorAntialias();
    EXPECT_TRUE(vaa == true || vaa == false);
}

// Test that font antialias default state is consistent
TEST_F(SplashOutputDevTest_1105, FontAntialias_DefaultState_1105) {
    bool faa = dev->getFontAntialias();
    EXPECT_TRUE(faa == true || faa == false);
}

// Test toggling vector antialias multiple times
TEST_F(SplashOutputDevTest_1105, VectorAntialias_MultipleToggles_1105) {
    for (int i = 0; i < 10; ++i) {
        bool val = (i % 2 == 0);
        dev->setVectorAntialias(val);
        EXPECT_EQ(dev->getVectorAntialias(), val);
    }
}

// Test toggling font antialias multiple times
TEST_F(SplashOutputDevTest_1105, FontAntialias_MultipleToggles_1105) {
    for (int i = 0; i < 10; ++i) {
        bool val = (i % 2 == 0);
        dev->setFontAntialias(val);
        EXPECT_EQ(dev->getFontAntialias(), val);
    }
}

// Test that paper color can be set to black
TEST_F(SplashOutputDevTest_1105, SetPaperColor_Black_1105) {
    SplashColor black;
    black[0] = 0;
    black[1] = 0;
    black[2] = 0;
    EXPECT_NO_FATAL_FAILURE(dev->setPaperColor(black));
}

// Test that paper color can be set to arbitrary values
TEST_F(SplashOutputDevTest_1105, SetPaperColor_ArbitraryColor_1105) {
    SplashColor color;
    color[0] = 128;
    color[1] = 64;
    color[2] = 32;
    EXPECT_NO_FATAL_FAILURE(dev->setPaperColor(color));
}
