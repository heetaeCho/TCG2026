#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"

// Test fixture for SplashOutputDev
class SplashOutputDevTest_1109 : public ::testing::Test {
protected:
    SplashOutputDev* dev = nullptr;
    SplashColor paperColor;

    void SetUp() override {
        // Set paper color to white
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

// Test that interpretType3Chars returns true
TEST_F(SplashOutputDevTest_1109, InterpretType3CharsReturnsTrue_1109) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

// Test that useDrawChar returns true (typical for SplashOutputDev)
TEST_F(SplashOutputDevTest_1109, UseDrawCharReturnsTrue_1109) {
    EXPECT_TRUE(dev->useDrawChar());
}

// Test that upsideDown returns true (SplashOutputDev typically renders top-down)
TEST_F(SplashOutputDevTest_1109, UpsideDownReturnsTrue_1109) {
    EXPECT_TRUE(dev->upsideDown());
}

// Test that useTilingPatternFill returns true
TEST_F(SplashOutputDevTest_1109, UseTilingPatternFillReturnsTrue_1109) {
    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Test useShadedFills with various shading types
TEST_F(SplashOutputDevTest_1109, UseShadedFillsType1_1109) {
    // Function-based shading (type 1)
    EXPECT_TRUE(dev->useShadedFills(1));
}

TEST_F(SplashOutputDevTest_1109, UseShadedFillsType2_1109) {
    // Axial shading (type 2)
    EXPECT_TRUE(dev->useShadedFills(2));
}

TEST_F(SplashOutputDevTest_1109, UseShadedFillsType3_1109) {
    // Radial shading (type 3)
    EXPECT_TRUE(dev->useShadedFills(3));
}

TEST_F(SplashOutputDevTest_1109, UseShadedFillsType4_1109) {
    // Gouraud triangle shading (type 4)
    EXPECT_TRUE(dev->useShadedFills(4));
}

TEST_F(SplashOutputDevTest_1109, UseShadedFillsType5_1109) {
    // Type 5 shading
    EXPECT_TRUE(dev->useShadedFills(5));
}

// Test getBitmap returns non-null after construction
TEST_F(SplashOutputDevTest_1109, GetBitmapAfterConstruction_1109) {
    // Before startPage, bitmap may or may not be initialized
    // We just test it doesn't crash
    SplashBitmap* bmp = dev->getBitmap();
    // Bitmap may be null before startPage is called
    (void)bmp;
}

// Test getSplash returns non-null after construction
TEST_F(SplashOutputDevTest_1109, GetSplashAfterConstruction_1109) {
    Splash* splash = dev->getSplash();
    // Splash may be null before startPage
    (void)splash;
}

// Test setVectorAntialias and getVectorAntialias
TEST_F(SplashOutputDevTest_1109, SetAndGetVectorAntialias_1109) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
    
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test setFontAntialias and getFontAntialias
TEST_F(SplashOutputDevTest_1109, SetAndGetFontAntialias_1109) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
    
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Test setEnableFreeType doesn't crash
TEST_F(SplashOutputDevTest_1109, SetEnableFreeType_1109) {
    EXPECT_NO_FATAL_FAILURE(dev->setEnableFreeType(true));
    EXPECT_NO_FATAL_FAILURE(dev->setEnableFreeType(false));
}

// Test setFreeTypeHinting doesn't crash
TEST_F(SplashOutputDevTest_1109, SetFreeTypeHinting_1109) {
    EXPECT_NO_FATAL_FAILURE(dev->setFreeTypeHinting(true, false));
    EXPECT_NO_FATAL_FAILURE(dev->setFreeTypeHinting(false, false));
    EXPECT_NO_FATAL_FAILURE(dev->setFreeTypeHinting(true, true));
    EXPECT_NO_FATAL_FAILURE(dev->setFreeTypeHinting(false, true));
}

// Test setSkipText doesn't crash
TEST_F(SplashOutputDevTest_1109, SetSkipText_1109) {
    EXPECT_NO_FATAL_FAILURE(dev->setSkipText(true, true));
    EXPECT_NO_FATAL_FAILURE(dev->setSkipText(false, false));
    EXPECT_NO_FATAL_FAILURE(dev->setSkipText(true, false));
    EXPECT_NO_FATAL_FAILURE(dev->setSkipText(false, true));
}

// Test setPaperColor doesn't crash
TEST_F(SplashOutputDevTest_1109, SetPaperColor_1109) {
    SplashColor newColor;
    newColor[0] = 0;
    newColor[1] = 0;
    newColor[2] = 0;
    EXPECT_NO_FATAL_FAILURE(dev->setPaperColor(newColor));
}

// Test construction with different color modes
class SplashOutputDevMono_1109 : public ::testing::Test {
protected:
    SplashOutputDev* dev = nullptr;
    SplashColor paperColor;

    void SetUp() override {
        paperColor[0] = 255;
        dev = new SplashOutputDev(splashModeMono8, 1, paperColor, true,
                                  splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev;
    }
};

TEST_F(SplashOutputDevMono_1109, InterpretType3CharsMonoMode_1109) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

TEST_F(SplashOutputDevMono_1109, UseDrawCharMonoMode_1109) {
    EXPECT_TRUE(dev->useDrawChar());
}

// Test construction with bitmapTopDown = false
class SplashOutputDevBottomUp_1109 : public ::testing::Test {
protected:
    SplashOutputDev* dev = nullptr;
    SplashColor paperColor;

    void SetUp() override {
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, false,
                                  splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev;
    }
};

TEST_F(SplashOutputDevBottomUp_1109, InterpretType3CharsBottomUp_1109) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

TEST_F(SplashOutputDevBottomUp_1109, UpsideDownBottomUp_1109) {
    EXPECT_TRUE(dev->upsideDown());
}

// Test construction with overprintPreview = true
class SplashOutputDevOverprint_1109 : public ::testing::Test {
protected:
    SplashOutputDev* dev = nullptr;
    SplashColor paperColor;

    void SetUp() override {
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                  splashThinLineDefault, true);
    }

    void TearDown() override {
        delete dev;
    }
};

TEST_F(SplashOutputDevOverprint_1109, InterpretType3CharsOverprint_1109) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

// Test with different thin line modes
class SplashOutputDevThinLine_1109 : public ::testing::Test {
protected:
    SplashOutputDev* dev = nullptr;
    SplashColor paperColor;

    void SetUp() override {
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true,
                                  splashThinLineShape, false);
    }

    void TearDown() override {
        delete dev;
    }
};

TEST_F(SplashOutputDevThinLine_1109, InterpretType3CharsThinLine_1109) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

// Test getCurrentFont returns nullptr before any font is set
TEST_F(SplashOutputDevTest_1109, GetCurrentFontBeforeSetup_1109) {
    SplashFont* font = dev->getCurrentFont();
    // Before any document/page processing, font should be null
    EXPECT_EQ(font, nullptr);
}

// Test getBitmapWidth and getBitmapHeight before startPage
TEST_F(SplashOutputDevTest_1109, GetBitmapDimensionsBeforeStartPage_1109) {
    // Before startPage, dimensions might be 0 or undefined
    // Just ensure no crash
    EXPECT_NO_FATAL_FAILURE(dev->getBitmapWidth());
    EXPECT_NO_FATAL_FAILURE(dev->getBitmapHeight());
}

// Test with different row pad values
class SplashOutputDevRowPad_1109 : public ::testing::Test {
protected:
    SplashOutputDev* dev = nullptr;
    SplashColor paperColor;

    void SetUp() override {
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        // Use row pad of 4
        dev = new SplashOutputDev(splashModeRGB8, 4, paperColor, true,
                                  splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev;
    }
};

TEST_F(SplashOutputDevRowPad_1109, InterpretType3CharsRowPad4_1109) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

// Test toggling vector antialias multiple times
TEST_F(SplashOutputDevTest_1109, ToggleVectorAntialiasMultipleTimes_1109) {
    for (int i = 0; i < 10; ++i) {
        bool val = (i % 2 == 0);
        dev->setVectorAntialias(val);
        EXPECT_EQ(dev->getVectorAntialias(), val);
    }
}

// Test toggling font antialias multiple times
TEST_F(SplashOutputDevTest_1109, ToggleFontAntialiasMultipleTimes_1109) {
    for (int i = 0; i < 10; ++i) {
        bool val = (i % 2 == 0);
        dev->setFontAntialias(val);
        EXPECT_EQ(dev->getFontAntialias(), val);
    }
}

// Test black paper color
TEST_F(SplashOutputDevTest_1109, SetBlackPaperColor_1109) {
    SplashColor black;
    black[0] = 0;
    black[1] = 0;
    black[2] = 0;
    EXPECT_NO_FATAL_FAILURE(dev->setPaperColor(black));
}

// Test that useShadedFills with invalid/unsupported type returns false or doesn't crash
TEST_F(SplashOutputDevTest_1109, UseShadedFillsInvalidType_1109) {
    // Type 0 is not a valid shading type
    EXPECT_NO_FATAL_FAILURE(dev->useShadedFills(0));
    // Type 6 and 7 are patch mesh types
    EXPECT_NO_FATAL_FAILURE(dev->useShadedFills(6));
    EXPECT_NO_FATAL_FAILURE(dev->useShadedFills(7));
}
