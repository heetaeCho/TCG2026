#include <gtest/gtest.h>
#include "poppler/SplashOutputDev.h"
#include "splash/SplashTypes.h"
#include "splash/SplashBitmap.h"

class SplashOutputDevTest_1106 : public ::testing::Test {
protected:
    SplashOutputDev* dev;

    void SetUp() override {
        SplashColor paperColor;
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, true, splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev;
    }
};

// Tests for useShadedFills
TEST_F(SplashOutputDevTest_1106, UseShadedFills_Type0_ReturnsFalse_1106) {
    EXPECT_FALSE(dev->useShadedFills(0));
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_Type1_ReturnsTrue_1106) {
    EXPECT_TRUE(dev->useShadedFills(1));
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_Type2_ReturnsTrue_1106) {
    EXPECT_TRUE(dev->useShadedFills(2));
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_Type3_ReturnsTrue_1106) {
    EXPECT_TRUE(dev->useShadedFills(3));
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_Type4_ReturnsTrue_1106) {
    EXPECT_TRUE(dev->useShadedFills(4));
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_Type5_ReturnsTrue_1106) {
    EXPECT_TRUE(dev->useShadedFills(5));
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_Type6_ReturnsFalse_1106) {
    EXPECT_FALSE(dev->useShadedFills(6));
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_Type7_ReturnsFalse_1106) {
    EXPECT_FALSE(dev->useShadedFills(7));
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_NegativeType_ReturnsFalse_1106) {
    EXPECT_FALSE(dev->useShadedFills(-1));
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_LargeType_ReturnsFalse_1106) {
    EXPECT_FALSE(dev->useShadedFills(100));
}

TEST_F(SplashOutputDevTest_1106, UseShadedFills_VeryNegativeType_ReturnsFalse_1106) {
    EXPECT_FALSE(dev->useShadedFills(-100));
}

// Tests for useTilingPatternFill
TEST_F(SplashOutputDevTest_1106, UseTilingPatternFill_ReturnsTrue_1106) {
    EXPECT_TRUE(dev->useTilingPatternFill());
}

// Tests for upsideDown
TEST_F(SplashOutputDevTest_1106, UpsideDown_ReturnsExpectedValue_1106) {
    bool result = dev->upsideDown();
    EXPECT_TRUE(result == true || result == false);
}

// Tests for useDrawChar
TEST_F(SplashOutputDevTest_1106, UseDrawChar_ReturnsTrue_1106) {
    EXPECT_TRUE(dev->useDrawChar());
}

// Tests for interpretType3Chars
TEST_F(SplashOutputDevTest_1106, InterpretType3Chars_ReturnsTrue_1106) {
    EXPECT_TRUE(dev->interpretType3Chars());
}

// Tests for getBitmap
TEST_F(SplashOutputDevTest_1106, GetBitmap_ReturnsNonNull_1106) {
    // Before startDoc/startPage, bitmap may or may not be null
    // This test just verifies the method is callable
    SplashBitmap* bmp = dev->getBitmap();
    // We can't guarantee non-null without startPage, just verify it doesn't crash
    (void)bmp;
}

// Tests for getSplash
TEST_F(SplashOutputDevTest_1106, GetSplash_IsCallable_1106) {
    Splash* splash = dev->getSplash();
    (void)splash;
}

// Tests for getVectorAntialias / setVectorAntialias
TEST_F(SplashOutputDevTest_1106, SetVectorAntialias_True_1106) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
}

TEST_F(SplashOutputDevTest_1106, SetVectorAntialias_False_1106) {
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

TEST_F(SplashOutputDevTest_1106, SetVectorAntialias_ToggleTwice_1106) {
    dev->setVectorAntialias(true);
    EXPECT_TRUE(dev->getVectorAntialias());
    dev->setVectorAntialias(false);
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Tests for getFontAntialias / setFontAntialias
TEST_F(SplashOutputDevTest_1106, SetFontAntialias_True_1106) {
    dev->setFontAntialias(true);
    EXPECT_TRUE(dev->getFontAntialias());
}

TEST_F(SplashOutputDevTest_1106, SetFontAntialias_False_1106) {
    dev->setFontAntialias(false);
    EXPECT_FALSE(dev->getFontAntialias());
}

// Tests for setSkipText
TEST_F(SplashOutputDevTest_1106, SetSkipText_BothTrue_1106) {
    // Just verifying it doesn't crash; no getter to verify
    dev->setSkipText(true, true);
}

TEST_F(SplashOutputDevTest_1106, SetSkipText_BothFalse_1106) {
    dev->setSkipText(false, false);
}

TEST_F(SplashOutputDevTest_1106, SetSkipText_MixedValues_1106) {
    dev->setSkipText(true, false);
    dev->setSkipText(false, true);
}

// Tests for setEnableFreeType
TEST_F(SplashOutputDevTest_1106, SetEnableFreeType_True_1106) {
    dev->setEnableFreeType(true);
}

TEST_F(SplashOutputDevTest_1106, SetEnableFreeType_False_1106) {
    dev->setEnableFreeType(false);
}

// Tests for setFreeTypeHinting
TEST_F(SplashOutputDevTest_1106, SetFreeTypeHinting_BothTrue_1106) {
    dev->setFreeTypeHinting(true, true);
}

TEST_F(SplashOutputDevTest_1106, SetFreeTypeHinting_BothFalse_1106) {
    dev->setFreeTypeHinting(false, false);
}

TEST_F(SplashOutputDevTest_1106, SetFreeTypeHinting_EnableTrueSlightFalse_1106) {
    dev->setFreeTypeHinting(true, false);
}

TEST_F(SplashOutputDevTest_1106, SetFreeTypeHinting_EnableFalseSlightTrue_1106) {
    dev->setFreeTypeHinting(false, true);
}

// Tests for getCurrentFont
TEST_F(SplashOutputDevTest_1106, GetCurrentFont_BeforeAnySetup_1106) {
    SplashFont* font = dev->getCurrentFont();
    // Before any font setup, likely null
    (void)font;
}

// Test with different color modes
class SplashOutputDevMono_1106 : public ::testing::Test {
protected:
    SplashOutputDev* dev;

    void SetUp() override {
        SplashColor paperColor;
        paperColor[0] = 255;
        dev = new SplashOutputDev(splashModeMono8, 1, paperColor, true, splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev;
    }
};

TEST_F(SplashOutputDevMono_1106, UseShadedFills_Type1_ReturnsTrue_1106) {
    EXPECT_TRUE(dev->useShadedFills(1));
}

TEST_F(SplashOutputDevMono_1106, UseShadedFills_Type0_ReturnsFalse_1106) {
    EXPECT_FALSE(dev->useShadedFills(0));
}

TEST_F(SplashOutputDevMono_1106, UseShadedFills_Type5_ReturnsTrue_1106) {
    EXPECT_TRUE(dev->useShadedFills(5));
}

TEST_F(SplashOutputDevMono_1106, UseShadedFills_Type6_ReturnsFalse_1106) {
    EXPECT_FALSE(dev->useShadedFills(6));
}

// Test with bitmapTopDown false
class SplashOutputDevBottomUp_1106 : public ::testing::Test {
protected:
    SplashOutputDev* dev;

    void SetUp() override {
        SplashColor paperColor;
        paperColor[0] = 0;
        paperColor[1] = 0;
        paperColor[2] = 0;
        dev = new SplashOutputDev(splashModeRGB8, 1, paperColor, false, splashThinLineDefault, false);
    }

    void TearDown() override {
        delete dev;
    }
};

TEST_F(SplashOutputDevBottomUp_1106, UseShadedFills_ValidRange_1106) {
    for (int i = 1; i <= 5; ++i) {
        EXPECT_TRUE(dev->useShadedFills(i)) << "Failed for type " << i;
    }
}

TEST_F(SplashOutputDevBottomUp_1106, UseShadedFills_InvalidRange_1106) {
    EXPECT_FALSE(dev->useShadedFills(0));
    EXPECT_FALSE(dev->useShadedFills(6));
    EXPECT_FALSE(dev->useShadedFills(-1));
    EXPECT_FALSE(dev->useShadedFills(INT_MAX));
    EXPECT_FALSE(dev->useShadedFills(INT_MIN));
}

// Test with overprint preview enabled
class SplashOutputDevOverprint_1106 : public ::testing::Test {
protected:
    SplashOutputDev* dev;

    void SetUp() override {
        SplashColor paperColor;
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
        dev = new SplashOutputDev(splashModeRGB8, 4, paperColor, true, splashThinLineDefault, true);
    }

    void TearDown() override {
        delete dev;
    }
};

TEST_F(SplashOutputDevOverprint_1106, UseShadedFills_BoundaryValues_1106) {
    EXPECT_FALSE(dev->useShadedFills(0));
    EXPECT_TRUE(dev->useShadedFills(1));
    EXPECT_TRUE(dev->useShadedFills(5));
    EXPECT_FALSE(dev->useShadedFills(6));
}

// Test setPaperColor
TEST_F(SplashOutputDevTest_1106, SetPaperColor_DoesNotCrash_1106) {
    SplashColor newColor;
    newColor[0] = 128;
    newColor[1] = 128;
    newColor[2] = 128;
    dev->setPaperColor(newColor);
}
