#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SplashOutputDev.h"
#include "splash/SplashBitmap.h"
#include "splash/Splash.h"
#include "splash/SplashTypes.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class SplashOutputDevTest_1110 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize globalParams if needed
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    SplashOutputDev* createDevRGB(bool topDown = true) {
        SplashColor paperColor;
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        return new SplashOutputDev(splashModeRGB8, 1, paperColor, topDown, splashThinLineDefault, false);
    }

    SplashOutputDev* createDevMono(bool topDown = true) {
        SplashColor paperColor;
        paperColor[0] = 255;
        return new SplashOutputDev(splashModeMono8, 1, paperColor, topDown, splashThinLineDefault, false);
    }
};

// Test that constructor creates a valid object and getBitmap returns non-null after startPage
TEST_F(SplashOutputDevTest_1110, ConstructorCreatesValidObject_1110) {
    SplashOutputDev* dev = createDevRGB();
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test getBitmap before startPage - bitmap may be null initially
TEST_F(SplashOutputDevTest_1110, GetBitmapBeforeStartPage_1110) {
    SplashOutputDev* dev = createDevRGB();
    // Before startPage, bitmap state is implementation-defined
    // Just ensure it doesn't crash
    SplashBitmap* bmp = dev->getBitmap();
    // bmp may or may not be null
    (void)bmp;
    delete dev;
}

// Test getBitmapWidth and getBitmapHeight before startPage
TEST_F(SplashOutputDevTest_1110, GetBitmapDimensionsBeforeStartPage_1110) {
    SplashOutputDev* dev = createDevRGB();
    int w = dev->getBitmapWidth();
    int h = dev->getBitmapHeight();
    // Before startPage, dimensions should be 0 or some default
    EXPECT_GE(w, 0);
    EXPECT_GE(h, 0);
    delete dev;
}

// Test useDrawChar returns true (SplashOutputDev typically uses drawChar)
TEST_F(SplashOutputDevTest_1110, UseDrawCharReturnsTrue_1110) {
    SplashOutputDev* dev = createDevRGB();
    EXPECT_TRUE(dev->useDrawChar());
    delete dev;
}

// Test interpretType3Chars returns true
TEST_F(SplashOutputDevTest_1110, InterpretType3CharsReturnsTrue_1110) {
    SplashOutputDev* dev = createDevRGB();
    EXPECT_TRUE(dev->interpretType3Chars());
    delete dev;
}

// Test upsideDown returns true (Splash coordinate system)
TEST_F(SplashOutputDevTest_1110, UpsideDownReturnsTrue_1110) {
    SplashOutputDev* dev = createDevRGB();
    EXPECT_TRUE(dev->upsideDown());
    delete dev;
}

// Test useTilingPatternFill
TEST_F(SplashOutputDevTest_1110, UseTilingPatternFill_1110) {
    SplashOutputDev* dev = createDevRGB();
    bool result = dev->useTilingPatternFill();
    EXPECT_TRUE(result);
    delete dev;
}

// Test useShadedFills for various types
TEST_F(SplashOutputDevTest_1110, UseShadedFillsType1_1110) {
    SplashOutputDev* dev = createDevRGB();
    // Type 1 = function shading
    bool result = dev->useShadedFills(1);
    // Implementation may return true or false
    (void)result;
    delete dev;
}

TEST_F(SplashOutputDevTest_1110, UseShadedFillsType2_1110) {
    SplashOutputDev* dev = createDevRGB();
    bool result = dev->useShadedFills(2);
    EXPECT_TRUE(result);
    delete dev;
}

TEST_F(SplashOutputDevTest_1110, UseShadedFillsType3_1110) {
    SplashOutputDev* dev = createDevRGB();
    bool result = dev->useShadedFills(3);
    EXPECT_TRUE(result);
    delete dev;
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashOutputDevTest_1110, VectorAntialiasSetGet_1110) {
    SplashOutputDev* dev = createDevRGB();
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
    delete dev;
}

// Test setFontAntialias and getFontAntialias
TEST_F(SplashOutputDevTest_1110, FontAntialiasSetGet_1110) {
    SplashOutputDev* dev = createDevRGB();
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
    delete dev;
}

// Test setEnableFreeType doesn't crash
TEST_F(SplashOutputDevTest_1110, SetEnableFreeTypeNoCrash_1110) {
    SplashOutputDev* dev = createDevRGB();
    dev->setEnableFreeType(true);
    dev->setEnableFreeType(false);
    delete dev;
}

// Test setFreeTypeHinting doesn't crash
TEST_F(SplashOutputDevTest_1110, SetFreeTypeHintingNoCrash_1110) {
    SplashOutputDev* dev = createDevRGB();
    dev->setFreeTypeHinting(true, false);
    dev->setFreeTypeHinting(false, true);
    dev->setFreeTypeHinting(true, true);
    dev->setFreeTypeHinting(false, false);
    delete dev;
}

// Test setSkipText doesn't crash
TEST_F(SplashOutputDevTest_1110, SetSkipTextNoCrash_1110) {
    SplashOutputDev* dev = createDevRGB();
    dev->setSkipText(true, true);
    dev->setSkipText(false, false);
    dev->setSkipText(true, false);
    dev->setSkipText(false, true);
    delete dev;
}

// Test setPaperColor
TEST_F(SplashOutputDevTest_1110, SetPaperColorNoCrash_1110) {
    SplashOutputDev* dev = createDevRGB();
    SplashColor newColor;
    newColor[0] = 0;
    newColor[1] = 0;
    newColor[2] = 0;
    dev->setPaperColor(newColor);
    delete dev;
}

// Test getSplash before startPage
TEST_F(SplashOutputDevTest_1110, GetSplashBeforeStartPage_1110) {
    SplashOutputDev* dev = createDevRGB();
    Splash* sp = dev->getSplash();
    // May be null or valid before startPage
    (void)sp;
    delete dev;
}

// Test getCurrentFont before any font is set
TEST_F(SplashOutputDevTest_1110, GetCurrentFontBeforeSetup_1110) {
    SplashOutputDev* dev = createDevRGB();
    SplashFont* f = dev->getCurrentFont();
    // Should be null before any font setup
    EXPECT_EQ(f, nullptr);
    delete dev;
}

// Test with Mono8 color mode
TEST_F(SplashOutputDevTest_1110, ConstructorMono8Mode_1110) {
    SplashOutputDev* dev = createDevMono();
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->useDrawChar());
    EXPECT_TRUE(dev->interpretType3Chars());
    delete dev;
}

// Test constructor with topDown false
TEST_F(SplashOutputDevTest_1110, ConstructorTopDownFalse_1110) {
    SplashOutputDev* dev = createDevRGB(false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test constructor with different thin line modes
TEST_F(SplashOutputDevTest_1110, ConstructorThinLineShape_1110) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineShape, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test constructor with overprintPreview enabled
TEST_F(SplashOutputDevTest_1110, ConstructorOverprintPreview_1110) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineDefault, true);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test constructor with different row padding
TEST_F(SplashOutputDevTest_1110, ConstructorDifferentRowPad_1110) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeRGB8, 4, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test takeBitmap - should return a bitmap and transfer ownership
TEST_F(SplashOutputDevTest_1110, TakeBitmapBeforeStartPage_1110) {
    SplashOutputDev* dev = createDevRGB();
    SplashBitmap* bmp = dev->takeBitmap();
    // After take, the dev's bitmap should be different (new one created or null)
    if (bmp) {
        delete bmp;
    }
    delete dev;
}

// Test checkTransparencyGroup
TEST_F(SplashOutputDevTest_1110, CheckTransparencyGroupNoCrash_1110) {
    SplashOutputDev* dev = createDevRGB();
    // This should return a bool without crashing
    bool result = dev->checkTransparencyGroup(nullptr, false);
    (void)result;
    delete dev;
}

// Test multiple set/get cycles for vector antialias
TEST_F(SplashOutputDevTest_1110, VectorAntialiasMultipleToggle_1110) {
    SplashOutputDev* dev = createDevRGB();
    for (int i = 0; i < 10; i++) {
        bool val = (i % 2 == 0);
        dev->setVectorAntialias(val);
        EXPECT_EQ(dev->getVectorAntialias(), val);
    }
    delete dev;
}

// Test multiple set/get cycles for font antialias
TEST_F(SplashOutputDevTest_1110, FontAntialiasMultipleToggle_1110) {
    SplashOutputDev* dev = createDevRGB();
    for (int i = 0; i < 10; i++) {
        bool val = (i % 2 == 0);
        dev->setFontAntialias(val);
        EXPECT_EQ(dev->getFontAntialias(), val);
    }
    delete dev;
}

// Test BGRA8 mode if available
TEST_F(SplashOutputDevTest_1110, ConstructorBGR8Mode_1110) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeBGR8, 1, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    EXPECT_TRUE(dev->useDrawChar());
    delete dev;
}

// Test XBGR8 mode
TEST_F(SplashOutputDevTest_1110, ConstructorXBGR8Mode_1110) {
    SplashColor paperColor;
    paperColor[0] = 255;
    paperColor[1] = 255;
    paperColor[2] = 255;
    paperColor[3] = 255;
    SplashOutputDev* dev = new SplashOutputDev(splashModeXBGR8, 1, paperColor, true, splashThinLineDefault, false);
    ASSERT_NE(dev, nullptr);
    delete dev;
}

// Test that getBitmap returns same pointer on consecutive calls (no startPage in between)
TEST_F(SplashOutputDevTest_1110, GetBitmapConsistency_1110) {
    SplashOutputDev* dev = createDevRGB();
    SplashBitmap* bmp1 = dev->getBitmap();
    SplashBitmap* bmp2 = dev->getBitmap();
    EXPECT_EQ(bmp1, bmp2);
    delete dev;
}

// Test useShadedFills with type 4 (Gouraud triangle)
TEST_F(SplashOutputDevTest_1110, UseShadedFillsType4_1110) {
    SplashOutputDev* dev = createDevRGB();
    bool result = dev->useShadedFills(4);
    EXPECT_TRUE(result);
    delete dev;
}

// Test useShadedFills with unsupported type
TEST_F(SplashOutputDevTest_1110, UseShadedFillsType6_1110) {
    SplashOutputDev* dev = createDevRGB();
    bool result = dev->useShadedFills(6);
    // Type 6 (Coons patch) may not be supported
    (void)result;
    delete dev;
}

// Test useShadedFills with type 0 (invalid)
TEST_F(SplashOutputDevTest_1110, UseShadedFillsType0_1110) {
    SplashOutputDev* dev = createDevRGB();
    bool result = dev->useShadedFills(0);
    EXPECT_FALSE(result);
    delete dev;
}
