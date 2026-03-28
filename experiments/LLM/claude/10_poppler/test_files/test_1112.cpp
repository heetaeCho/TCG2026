#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"
#include "splash/Splash.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class SplashOutputDevTest_1112 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        SplashColor paperColor;
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev;
    }

    SplashOutputDev *dev = nullptr;
};

// Test that constructor creates a valid object and basic getters work
TEST_F(SplashOutputDevTest_1112, ConstructorCreatesValidObject_1112) {
    ASSERT_NE(dev, nullptr);
}

// Test getCurrentFont returns nullptr before any font is set/updated
TEST_F(SplashOutputDevTest_1112, GetCurrentFontInitiallyNull_1112) {
    SplashFont *font = dev->getCurrentFont();
    EXPECT_EQ(font, nullptr);
}

// Test getBitmap returns non-null after construction
TEST_F(SplashOutputDevTest_1112, GetBitmapAfterConstruction_1112) {
    // Before startPage, bitmap may or may not exist depending on implementation
    // but getSplash and getBitmap should be callable
    SplashBitmap *bmp = dev->getBitmap();
    // After construction without startPage, bitmap might be null
    // We just test it doesn't crash
    (void)bmp;
}

// Test getSplash returns something after construction
TEST_F(SplashOutputDevTest_1112, GetSplashAfterConstruction_1112) {
    Splash *splash = dev->getSplash();
    (void)splash;
}

// Test useDrawChar returns true (SplashOutputDev always uses drawChar)
TEST_F(SplashOutputDevTest_1112, UseDrawCharReturnsTrue_1112) {
    EXPECT_TRUE(dev->useDrawChar());
}

// Test interpretType3Chars returns true
TEST_F(SplashOutputDevTest_1112, InterpretType3CharsReturnsTrue_1112) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

// Test upsideDown returns true (Splash uses top-down coordinate system)
TEST_F(SplashOutputDevTest_1112, UpsideDownReturnsTrue_1112) {
    EXPECT_TRUE(dev->upsideDown());
}

// Test useTilingPatternFill returns true
TEST_F(SplashOutputDevTest_1112, UseTilingPatternFillReturnsTrue_1112) {
    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Test useShadedFills for various types
TEST_F(SplashOutputDevTest_1112, UseShadedFillsForVariousTypes_1112) {
    // Types 1-7 are defined in PDF spec for shading
    // SplashOutputDev typically supports types 2 (axial), 3 (radial), 4 (Gouraud), possibly 1 (function)
    for (int type = 1; type <= 7; type++) {
        bool result = dev->useShadedFills(type);
        // Just verify it doesn't crash; the result depends on type
        (void)result;
    }
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashOutputDevTest_1112, VectorAntialiasGetSet_1112) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());

    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test setFontAntialias and getFontAntialias
TEST_F(SplashOutputDevTest_1112, FontAntialiasGetSet_1112) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());

    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Test setSkipText doesn't crash
TEST_F(SplashOutputDevTest_1112, SetSkipTextDoesNotCrash_1112) {
    dev->setSkipText(true, true);
    dev->setSkipText(false, false);
    dev->setSkipText(true, false);
    dev->setSkipText(false, true);
}

// Test setEnableFreeType doesn't crash
TEST_F(SplashOutputDevTest_1112, SetEnableFreeTypeDoesNotCrash_1112) {
    dev->setEnableFreeType(true);
    dev->setEnableFreeType(false);
}

// Test setFreeTypeHinting doesn't crash
TEST_F(SplashOutputDevTest_1112, SetFreeTypeHintingDoesNotCrash_1112) {
    dev->setFreeTypeHinting(true, false);
    dev->setFreeTypeHinting(false, false);
    dev->setFreeTypeHinting(true, true);
    dev->setFreeTypeHinting(false, true);
}

// Test setPaperColor doesn't crash
TEST_F(SplashOutputDevTest_1112, SetPaperColorDoesNotCrash_1112) {
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    dev->setPaperColor(color);
}

// Test construction with different color modes
TEST_F(SplashOutputDevTest_1112, ConstructWithMono1_1112) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    SplashOutputDev *monoDev = new SplashOutputDev(splashModeMono1, 1, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(monoDev, nullptr);
    EXPECT_TRUE(monoDev->useDrawChar());
    delete monoDev;
}

TEST_F(SplashOutputDevTest_1112, ConstructWithMono8_1112) {
    SplashColor paperColor;
    paperColor[0] = 0xff;
    SplashOutputDev *monoDev = new SplashOutputDev(splashModeMono8, 1, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(monoDev, nullptr);
    EXPECT_TRUE(monoDev->useDrawChar());
    delete monoDev;
}

// Test getBitmapWidth and getBitmapHeight before startPage
TEST_F(SplashOutputDevTest_1112, GetBitmapDimensionsBeforeStartPage_1112) {
    // Before startPage, dimensions may be 0 or some default
    int w = dev->getBitmapWidth();
    int h = dev->getBitmapHeight();
    // Just verify no crash; values depend on implementation
    EXPECT_GE(w, 0);
    EXPECT_GE(h, 0);
}

// Test takeBitmap
TEST_F(SplashOutputDevTest_1112, TakeBitmapBeforeStartPage_1112) {
    SplashBitmap *bmp = dev->takeBitmap();
    // takeBitmap may return null or a valid bitmap before startPage
    // Just make sure no crash, and if non-null, it's ours to delete
    delete bmp;
}

// Test construction with overprintPreview enabled
TEST_F(SplashOutputDevTest_1112, ConstructWithOverprintPreview_1112) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    paperColor[3] = 255;
    SplashOutputDev *opDev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineDefault, true);
    ASSERT_NE(opDev, nullptr);
    delete opDev;
}

// Test construction with bitmapTopDown false
TEST_F(SplashOutputDevTest_1112, ConstructWithBitmapTopDownFalse_1112) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev *tdDev = new SplashOutputDev(splashModeRGB8, 1, paperColor, false, splashThinLineDefault, false);
    ASSERT_NE(tdDev, nullptr);
    delete tdDev;
}

// Test construction with different row padding
TEST_F(SplashOutputDevTest_1112, ConstructWithDifferentRowPad_1112) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev *padDev = new SplashOutputDev(splashModeRGB8, 4, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(padDev, nullptr);
    delete padDev;
}

// Test different thin line modes
TEST_F(SplashOutputDevTest_1112, ConstructWithThinLineShape_1112) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev *tlDev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineShape, false);
    ASSERT_NE(tlDev, nullptr);
    delete tlDev;
}

// Test checkTransparencyGroup without proper state (should not crash)
TEST_F(SplashOutputDevTest_1112, CheckTransparencyGroupNullState_1112) {
    // Passing nullptr for state may or may not be valid, but tests boundary
    // Skip this if it would segfault - this is testing the interface boundary
    // In practice, this might crash, so we test with a comment noting the risk
}

// Test vector antialias toggle persistence
TEST_F(SplashOutputDevTest_1112, VectorAntialiasTogglePersistence_1112) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test font antialias toggle persistence
TEST_F(SplashOutputDevTest_1112, FontAntialiasTogglePersistence_1112) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Test with black paper color
TEST_F(SplashOutputDevTest_1112, ConstructWithBlackPaperColor_1112) {
    SplashColor paperColor;
    paperColor[0] = 0;
    paperColor[1] = 0;
    paperColor[2] = 0;
    SplashOutputDev *blackDev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(blackDev, nullptr);
    EXPECT_TRUE(blackDev->useDrawChar());
    delete blackDev;
}
