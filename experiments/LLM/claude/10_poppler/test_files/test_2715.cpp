#include <gtest/gtest.h>
#include <splash/SplashTypes.h>
#include <splash/SplashBitmap.h>
#include <SplashOutputDev.h>

// We need to include the header or source that defines SplashOutputDevNoText.
// Since it's defined in pdftohtml.cc, we may need to include it or replicate the class declaration.
// Based on the known dependencies, we include the necessary headers.

// Forward declare or include the class. Since the class is in a .cc file,
// we need to define it here based on the known interface for testing purposes.
// However, per constraints, we treat implementation as black box and only test the interface.

// Minimal redeclaration based on provided interface for compilation:
#include <SplashOutputDev.h>
#include <GfxState.h>

class SplashOutputDevNoText : public SplashOutputDev {
public:
    SplashOutputDevNoText(SplashColorMode colorModeA, int bitmapRowPadA, SplashColorPtr paperColorA, bool bitmapTopDownA = true)
        : SplashOutputDev(colorModeA, bitmapRowPadA, paperColorA, bitmapTopDownA) { }

    ~SplashOutputDevNoText() override;

    void drawChar(GfxState * /*state*/, double /*x*/, double /*y*/, double /*dx*/, double /*dy*/, double /*originX*/, double /*originY*/, CharCode /*code*/, int /*nBytes*/, const Unicode * /*u*/, int /*uLen*/) override;

    bool beginType3Char(GfxState * /*state*/, double /*x*/, double /*y*/, double /*dx*/, double /*dy*/, CharCode /*code*/, const Unicode * /*u*/, int /*uLen*/) override;

    void endType3Char(GfxState * /*state*/) override;

    void beginTextObject(GfxState * /*state*/) override;

    void endTextObject(GfxState * /*state*/) override;

    bool interpretType3Chars() override;
};

class SplashOutputDevNoTextTest_2715 : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up a white paper color for splash
        paperColor[0] = 255;
        paperColor[1] = 255;
        paperColor[2] = 255;
    }

    SplashColor paperColor;
};

// Test that interpretType3Chars returns false
TEST_F(SplashOutputDevNoTextTest_2715, InterpretType3CharsReturnsFalse_2715) {
    SplashOutputDevNoText dev(splashModeRGB8, 1, paperColor, true);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test that interpretType3Chars consistently returns false on repeated calls
TEST_F(SplashOutputDevNoTextTest_2715, InterpretType3CharsConsistentlyReturnsFalse_2715) {
    SplashOutputDevNoText dev(splashModeRGB8, 1, paperColor, true);
    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test construction with different color modes
TEST_F(SplashOutputDevNoTextTest_2715, ConstructWithMono1_2715) {
    SplashColor mono = { 0 };
    mono[0] = 255;
    SplashOutputDevNoText dev(splashModeMono1, 1, mono, true);
    EXPECT_FALSE(dev.interpretType3Chars());
}

TEST_F(SplashOutputDevNoTextTest_2715, ConstructWithMono8_2715) {
    SplashColor mono = { 0 };
    mono[0] = 255;
    SplashOutputDevNoText dev(splashModeMono8, 1, mono, true);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test construction with bitmapTopDown set to false
TEST_F(SplashOutputDevNoTextTest_2715, ConstructWithTopDownFalse_2715) {
    SplashOutputDevNoText dev(splashModeRGB8, 1, paperColor, false);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test that drawChar can be called without crashing (with nullptr state)
TEST_F(SplashOutputDevNoTextTest_2715, DrawCharWithNullStateDoesNotCrash_2715) {
    SplashOutputDevNoText dev(splashModeRGB8, 1, paperColor, true);
    // drawChar should be a no-op for this class (suppresses text)
    EXPECT_NO_THROW(dev.drawChar(nullptr, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, nullptr, 0));
}

// Test that beginTextObject with nullptr does not crash
TEST_F(SplashOutputDevNoTextTest_2715, BeginTextObjectNullStateDoesNotCrash_2715) {
    SplashOutputDevNoText dev(splashModeRGB8, 1, paperColor, true);
    EXPECT_NO_THROW(dev.beginTextObject(nullptr));
}

// Test that endTextObject with nullptr does not crash
TEST_F(SplashOutputDevNoTextTest_2715, EndTextObjectNullStateDoesNotCrash_2715) {
    SplashOutputDevNoText dev(splashModeRGB8, 1, paperColor, true);
    EXPECT_NO_THROW(dev.endTextObject(nullptr));
}

// Test that endType3Char with nullptr does not crash
TEST_F(SplashOutputDevNoTextTest_2715, EndType3CharNullStateDoesNotCrash_2715) {
    SplashOutputDevNoText dev(splashModeRGB8, 1, paperColor, true);
    EXPECT_NO_THROW(dev.endType3Char(nullptr));
}

// Test construction with different row padding values
TEST_F(SplashOutputDevNoTextTest_2715, ConstructWithVariousRowPadding_2715) {
    {
        SplashOutputDevNoText dev(splashModeRGB8, 4, paperColor, true);
        EXPECT_FALSE(dev.interpretType3Chars());
    }
    {
        SplashOutputDevNoText dev(splashModeRGB8, 8, paperColor, true);
        EXPECT_FALSE(dev.interpretType3Chars());
    }
}

// Test that the override of interpretType3Chars differs from base SplashOutputDev behavior
// Base SplashOutputDev::interpretType3Chars() returns true; the override returns false
TEST_F(SplashOutputDevNoTextTest_2715, InterpretType3CharsDiffersFromBase_2715) {
    SplashOutputDev baseDev(splashModeRGB8, 1, paperColor, true);
    SplashOutputDevNoText derivedDev(splashModeRGB8, 1, paperColor, true);

    // Base class should return true, derived should return false
    EXPECT_TRUE(baseDev.interpretType3Chars());
    EXPECT_FALSE(derivedDev.interpretType3Chars());
}
