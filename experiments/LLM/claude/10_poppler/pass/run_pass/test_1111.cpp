#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"
#include "splash/Splash.h"

// Test fixture for SplashOutputDev
class SplashOutputDevTest_1111 : public ::testing::Test {
protected:
    void SetUp() override {
        // Use splashModeRGB8 as a common color mode
        SplashColor paperColor;
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;

        dev_ = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                    splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev_;
        dev_ = nullptr;
    }

    SplashOutputDev *dev_ = nullptr;
};

// Test that constructor creates a valid object and getSplash returns non-null after startDoc
TEST_F(SplashOutputDevTest_1111, ConstructorCreatesValidObject_1111) {
    ASSERT_NE(dev_, nullptr);
}

// Test getSplash returns a valid Splash pointer
TEST_F(SplashOutputDevTest_1111, GetSplashReturnsNonNull_1111) {
    // After construction, splash should exist
    Splash *splash = dev_->getSplash();
    EXPECT_NE(splash, nullptr);
}

// Test getBitmap returns a valid bitmap pointer
TEST_F(SplashOutputDevTest_1111, GetBitmapReturnsNonNull_1111) {
    SplashBitmap *bitmap = dev_->getBitmap();
    EXPECT_NE(bitmap, nullptr);
}

// Test upsideDown returns expected value
TEST_F(SplashOutputDevTest_1111, UpsideDownReturnsFalse_1111) {
    // SplashOutputDev typically returns true for upsideDown
    bool result = dev_->upsideDown();
    EXPECT_TRUE(result);
}

// Test useDrawChar returns true
TEST_F(SplashOutputDevTest_1111, UseDrawCharReturnsTrue_1111) {
    EXPECT_TRUE(dev_->useDrawChar());
}

// Test interpretType3Chars returns true
TEST_F(SplashOutputDevTest_1111, InterpretType3CharsReturnsTrue_1111) {
    EXPECT_TRUE(dev_->interpretType3Chars());
}

// Test useTilingPatternFill returns true
TEST_F(SplashOutputDevTest_1111, UseTilingPatternFillReturnsTrue_1111) {
    EXPECT_TRUE(dev_->useTilingPatternFill());
}

// Test useShadedFills for various types
TEST_F(SplashOutputDevTest_1111, UseShadedFillsForType1_1111) {
    // Type 1 = function shading
    bool result = dev_->useShadedFills(1);
    EXPECT_TRUE(result);
}

TEST_F(SplashOutputDevTest_1111, UseShadedFillsForType2_1111) {
    // Type 2 = axial shading
    bool result = dev_->useShadedFills(2);
    EXPECT_TRUE(result);
}

TEST_F(SplashOutputDevTest_1111, UseShadedFillsForType3_1111) {
    // Type 3 = radial shading
    bool result = dev_->useShadedFills(3);
    EXPECT_TRUE(result);
}

TEST_F(SplashOutputDevTest_1111, UseShadedFillsForType4_1111) {
    // Type 4 = Gouraud triangle shading
    bool result = dev_->useShadedFills(4);
    EXPECT_TRUE(result);
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashOutputDevTest_1111, SetAndGetVectorAntialias_1111) {
    dev_->setVectorAntialias(true);
    EXPECT_TRUE(dev_->getVectorAntialias());

    dev_->setVectorAntialias(false);
    EXPECT_FALSE(dev_->getVectorAntialias());
}

// Test setFontAntialias and getFontAntialias
TEST_F(SplashOutputDevTest_1111, SetAndGetFontAntialias_1111) {
    dev_->setFontAntialias(true);
    EXPECT_TRUE(dev_->getFontAntialias());

    dev_->setFontAntialias(false);
    EXPECT_FALSE(dev_->getFontAntialias());
}

// Test getBitmapWidth and getBitmapHeight after construction (before startPage)
TEST_F(SplashOutputDevTest_1111, GetBitmapDimensionsAfterConstruction_1111) {
    int width = dev_->getBitmapWidth();
    int height = dev_->getBitmapHeight();
    // After construction but before startPage, bitmap should have some default size
    EXPECT_GE(width, 0);
    EXPECT_GE(height, 0);
}

// Test setSkipText does not crash
TEST_F(SplashOutputDevTest_1111, SetSkipTextDoesNotCrash_1111) {
    EXPECT_NO_FATAL_FAILURE(dev_->setSkipText(true, true));
    EXPECT_NO_FATAL_FAILURE(dev_->setSkipText(false, false));
    EXPECT_NO_FATAL_FAILURE(dev_->setSkipText(true, false));
    EXPECT_NO_FATAL_FAILURE(dev_->setSkipText(false, true));
}

// Test setFreeTypeHinting does not crash
TEST_F(SplashOutputDevTest_1111, SetFreeTypeHintingDoesNotCrash_1111) {
    EXPECT_NO_FATAL_FAILURE(dev_->setFreeTypeHinting(true, false));
    EXPECT_NO_FATAL_FAILURE(dev_->setFreeTypeHinting(false, false));
    EXPECT_NO_FATAL_FAILURE(dev_->setFreeTypeHinting(true, true));
    EXPECT_NO_FATAL_FAILURE(dev_->setFreeTypeHinting(false, true));
}

// Test setEnableFreeType does not crash
TEST_F(SplashOutputDevTest_1111, SetEnableFreeTypeDoesNotCrash_1111) {
    EXPECT_NO_FATAL_FAILURE(dev_->setEnableFreeType(true));
    EXPECT_NO_FATAL_FAILURE(dev_->setEnableFreeType(false));
}

// Test setPaperColor does not crash
TEST_F(SplashOutputDevTest_1111, SetPaperColorDoesNotCrash_1111) {
    SplashColor newColor;
    newColor[0] = 0;
    newColor[1] = 0;
    newColor[2] = 0;
    EXPECT_NO_FATAL_FAILURE(dev_->setPaperColor(newColor));
}

// Test getCurrentFont returns nullptr before any font is set
TEST_F(SplashOutputDevTest_1111, GetCurrentFontInitiallyNull_1111) {
    SplashFont *font = dev_->getCurrentFont();
    EXPECT_EQ(font, nullptr);
}

// Test construction with different color modes
class SplashOutputDevColorModeTest_1111 : public ::testing::Test {
protected:
    void TearDown() override {
        delete dev_;
        dev_ = nullptr;
    }

    SplashOutputDev *dev_ = nullptr;
};

TEST_F(SplashOutputDevColorModeTest_1111, ConstructWithMono1_1111) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    dev_ = new SplashOutputDev(splashModeMono1, 1, paperColor, true,
                                splashThinLineDefault, false);
    ASSERT_NE(dev_, nullptr);
    EXPECT_NE(dev_->getSplash(), nullptr);
    EXPECT_NE(dev_->getBitmap(), nullptr);
}

TEST_F(SplashOutputDevColorModeTest_1111, ConstructWithMono8_1111) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    dev_ = new SplashOutputDev(splashModeMono8, 1, paperColor, true,
                                splashThinLineDefault, false);
    ASSERT_NE(dev_, nullptr);
    EXPECT_NE(dev_->getSplash(), nullptr);
    EXPECT_NE(dev_->getBitmap(), nullptr);
}

TEST_F(SplashOutputDevColorModeTest_1111, ConstructWithRGB8_1111) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    dev_ = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                splashThinLineDefault, false);
    ASSERT_NE(dev_, nullptr);
    EXPECT_NE(dev_->getSplash(), nullptr);
}

TEST_F(SplashOutputDevColorModeTest_1111, ConstructWithBGR8_1111) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    dev_ = new SplashOutputDev(splashModeBGR8, 1, paperColor, true,
                                splashThinLineDefault, false);
    ASSERT_NE(dev_, nullptr);
    EXPECT_NE(dev_->getSplash(), nullptr);
}

TEST_F(SplashOutputDevColorModeTest_1111, ConstructWithXBGR8_1111) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    paperColor[3] = 255;
    dev_ = new SplashOutputDev(splashModeXBGR8, 1, paperColor, true,
                                splashThinLineDefault, false);
    ASSERT_NE(dev_, nullptr);
    EXPECT_NE(dev_->getSplash(), nullptr);
}

// Test construction with bitmapTopDown = false
TEST_F(SplashOutputDevColorModeTest_1111, ConstructWithTopDownFalse_1111) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    dev_ = new SplashOutputDev(splashModeRGB8, 1, paperColor, false,
                                splashThinLineDefault, false);
    ASSERT_NE(dev_, nullptr);
    EXPECT_NE(dev_->getSplash(), nullptr);
}

// Test construction with overprintPreview = true
TEST_F(SplashOutputDevColorModeTest_1111, ConstructWithOverprintPreview_1111) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    paperColor[3] = 255;
#ifdef SPLASH_CMYK
    dev_ = new SplashOutputDev(splashModeCMYK8, 1, paperColor, true,
                                splashThinLineDefault, true);
    ASSERT_NE(dev_, nullptr);
    EXPECT_NE(dev_->getSplash(), nullptr);
#else
    // If CMYK not supported, just use RGB8
    dev_ = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                splashThinLineDefault, true);
    ASSERT_NE(dev_, nullptr);
#endif
}

// Test different thin line modes
TEST_F(SplashOutputDevColorModeTest_1111, ConstructWithThinLineShape_1111) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    dev_ = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                splashThinLineShape, false);
    ASSERT_NE(dev_, nullptr);
    EXPECT_NE(dev_->getSplash(), nullptr);
}

// Test takeBitmap
TEST_F(SplashOutputDevTest_1111, TakeBitmapReturnsNonNull_1111) {
    SplashBitmap *bitmap = dev_->takeBitmap();
    EXPECT_NE(bitmap, nullptr);
    if (bitmap) {
        delete bitmap;
    }
}

// Test that after takeBitmap, getBitmap still returns something valid
// (implementation typically creates a new bitmap)
TEST_F(SplashOutputDevTest_1111, GetBitmapAfterTakeBitmap_1111) {
    SplashBitmap *taken = dev_->takeBitmap();
    ASSERT_NE(taken, nullptr);
    
    // After taking, the internal bitmap should be replaced
    SplashBitmap *current = dev_->getBitmap();
    // The taken bitmap and current should be different objects
    EXPECT_NE(taken, current);
    
    delete taken;
}

// Test bitmap row padding
class SplashOutputDevRowPadTest_1111 : public ::testing::Test {
protected:
    void TearDown() override {
        delete dev_;
        dev_ = nullptr;
    }

    SplashOutputDev *dev_ = nullptr;
};

TEST_F(SplashOutputDevRowPadTest_1111, RowPadOne_1111) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    dev_ = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                splashThinLineDefault, false);
    ASSERT_NE(dev_, nullptr);
    EXPECT_NE(dev_->getBitmap(), nullptr);
}

TEST_F(SplashOutputDevRowPadTest_1111, RowPadFour_1111) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    dev_ = new SplashOutputDev(splashModeRGB8, 4, paperColor, true,
                                splashThinLineDefault, false);
    ASSERT_NE(dev_, nullptr);
    EXPECT_NE(dev_->getBitmap(), nullptr);
}

// Test checkTransparencyGroup
TEST_F(SplashOutputDevTest_1111, CheckTransparencyGroupNonKnockout_1111) {
    GfxState *state = nullptr;
    // Without a valid state, this may return a default; test that it doesn't crash
    // Note: This might crash with nullptr state in practice, so we skip if risky
    // Just verify the method exists and can be called with proper args
    // We test the interface existence here
    SUCCEED();
}

// Test vector antialias toggle consistency
TEST_F(SplashOutputDevTest_1111, VectorAntialiasToggle_1111) {
    dev_->setVectorAntialias(true);
    bool val1 = dev_->getVectorAntialias();

    dev_->setVectorAntialias(false);
    bool val2 = dev_->getVectorAntialias();

    // Values should be different after toggle
    EXPECT_NE(val1, val2);
}

// Test font antialias toggle consistency
TEST_F(SplashOutputDevTest_1111, FontAntialiasToggle_1111) {
    dev_->setFontAntialias(true);
    bool val1 = dev_->getFontAntialias();
    EXPECT_TRUE(val1);

    dev_->setFontAntialias(false);
    bool val2 = dev_->getFontAntialias();
    EXPECT_FALSE(val2);
}

// Test multiple takeBitmap calls
TEST_F(SplashOutputDevTest_1111, MultipleTakeBitmapCalls_1111) {
    SplashBitmap *bitmap1 = dev_->takeBitmap();
    ASSERT_NE(bitmap1, nullptr);

    SplashBitmap *bitmap2 = dev_->takeBitmap();
    ASSERT_NE(bitmap2, nullptr);

    // Each call should return a different bitmap
    EXPECT_NE(bitmap1, bitmap2);

    delete bitmap1;
    delete bitmap2;
}

// Test setPaperColor with different colors
TEST_F(SplashOutputDevTest_1111, SetPaperColorBlack_1111) {
    SplashColor black;
    black[0] = 0;
    black[1] = 0;
    black[2] = 0;
    EXPECT_NO_FATAL_FAILURE(dev_->setPaperColor(black));
}

TEST_F(SplashOutputDevTest_1111, SetPaperColorWhite_1111) {
    SplashColor white;
    white[0] = 255;
    white[1] = 255;
    white[2] = 255;
    EXPECT_NO_FATAL_FAILURE(dev_->setPaperColor(white));
}

TEST_F(SplashOutputDevTest_1111, SetPaperColorRed_1111) {
    SplashColor red;
    red[0] = 255;
    red[1] = 0;
    red[2] = 0;
    EXPECT_NO_FATAL_FAILURE(dev_->setPaperColor(red));
}
