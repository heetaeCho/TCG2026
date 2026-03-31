#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/GfxState.h"
#include "splash/SplashTypes.h"
#include "poppler/SplashOutputDev.h"

// We need access to the static inline function. Since it's static inline in the .cc file,
// we need to either include it or redefine the test approach.
// Since convertGfxColor is a static inline function in SplashOutputDev.cc, we cannot directly
// call it from outside. We'll need to include the source or use a wrapper.
// For testing purposes, we'll include the necessary parts.

// Mock GfxColorSpace to control behavior
class MockGfxColorSpace : public GfxColorSpace {
public:
    MockGfxColorSpace() : GfxColorSpace() {}
    ~MockGfxColorSpace() override {}

    MOCK_CONST_METHOD0(getMode, GfxColorSpaceMode());
    MOCK_CONST_METHOD2(getGray, void(const GfxColor *color, GfxGray *gray));
    MOCK_CONST_METHOD2(getRGB, void(const GfxColor *color, GfxRGB *rgb));
    MOCK_CONST_METHOD2(getCMYK, void(const GfxColor *color, GfxCMYK *cmyk));
    MOCK_CONST_METHOD2(getDeviceN, void(const GfxColor *color, GfxColor *deviceN));
    MOCK_CONST_METHOD0(getNComps, int());
    MOCK_CONST_METHOD1(getDefaultColor, void(GfxColor *color));
    MOCK_CONST_METHOD0(copy, const std::unique_ptr<GfxColorSpace>());
};

// Since convertGfxColor is static inline in the .cc file, we need to extract it for testing.
// We'll include the implementation file or define a test helper.
// For this test, we assume we can access the function through a test helper or by including the .cc

// Re-declare the function signature for testing (matching the static inline function)
static inline void convertGfxColor(SplashColorPtr dest, const SplashColorMode colorMode, const GfxColorSpace *colorSpace, const GfxColor *src);

// Include the actual implementation
#include "poppler/SplashOutputDev.cc"

class ConvertGfxColorTest_1574 : public ::testing::Test {
protected:
    void SetUp() override {
        memset(&src, 0, sizeof(GfxColor));
        memset(dest, 0, sizeof(SplashColor));
    }

    GfxColor src;
    SplashColor dest;
};

// Test Mono1 mode
TEST_F(ConvertGfxColorTest_1574, Mono1ModeCallsGetGray_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getGray(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxGray *gray) {
            *gray = byteToCol(128);
        }));

    convertGfxColor(dest, splashModeMono1, &colorSpace, &src);

    EXPECT_EQ(dest[0], 128);
}

// Test Mono8 mode
TEST_F(ConvertGfxColorTest_1574, Mono8ModeCallsGetGray_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getGray(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxGray *gray) {
            *gray = byteToCol(255);
        }));

    convertGfxColor(dest, splashModeMono8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 255);
}

// Test Mono8 mode with zero gray
TEST_F(ConvertGfxColorTest_1574, Mono8ModeZeroGray_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getGray(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxGray *gray) {
            *gray = byteToCol(0);
        }));

    convertGfxColor(dest, splashModeMono8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 0);
}

// Test RGB8 mode
TEST_F(ConvertGfxColorTest_1574, RGB8ModeCallsGetRGB_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getRGB(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxRGB *rgb) {
            rgb->r = byteToCol(100);
            rgb->g = byteToCol(150);
            rgb->b = byteToCol(200);
        }));

    convertGfxColor(dest, splashModeRGB8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 100);
    EXPECT_EQ(dest[1], 150);
    EXPECT_EQ(dest[2], 200);
}

// Test BGR8 mode
TEST_F(ConvertGfxColorTest_1574, BGR8ModeCallsGetRGB_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getRGB(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxRGB *rgb) {
            rgb->r = byteToCol(50);
            rgb->g = byteToCol(100);
            rgb->b = byteToCol(150);
        }));

    convertGfxColor(dest, splashModeBGR8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 50);
    EXPECT_EQ(dest[1], 100);
    EXPECT_EQ(dest[2], 150);
}

// Test XBGR8 mode - should set alpha to 255
TEST_F(ConvertGfxColorTest_1574, XBGR8ModeSetsAlphaTo255_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getRGB(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxRGB *rgb) {
            rgb->r = byteToCol(10);
            rgb->g = byteToCol(20);
            rgb->b = byteToCol(30);
        }));

    convertGfxColor(dest, splashModeXBGR8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 10);
    EXPECT_EQ(dest[1], 20);
    EXPECT_EQ(dest[2], 30);
    EXPECT_EQ(dest[3], 255);
}

// Test CMYK8 mode
TEST_F(ConvertGfxColorTest_1574, CMYK8ModeCallsGetCMYK_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getCMYK(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxCMYK *cmyk) {
            cmyk->c = byteToCol(40);
            cmyk->m = byteToCol(80);
            cmyk->y = byteToCol(120);
            cmyk->k = byteToCol(160);
        }));

    convertGfxColor(dest, splashModeCMYK8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 40);
    EXPECT_EQ(dest[1], 80);
    EXPECT_EQ(dest[2], 120);
    EXPECT_EQ(dest[3], 160);
}

// Test DeviceN8 mode
TEST_F(ConvertGfxColorTest_1574, DeviceN8ModeCallsGetDeviceN_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getDeviceN(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxColor *deviceN) {
            for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
                deviceN->c[i] = byteToCol(i * 10);
            }
        }));

    convertGfxColor(dest, splashModeDeviceN8, &colorSpace, &src);

    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        EXPECT_EQ(dest[i], i * 10);
    }
}

// Test RGB8 with all zeros
TEST_F(ConvertGfxColorTest_1574, RGB8ModeAllZeros_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getRGB(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxRGB *rgb) {
            rgb->r = byteToCol(0);
            rgb->g = byteToCol(0);
            rgb->b = byteToCol(0);
        }));

    convertGfxColor(dest, splashModeRGB8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 0);
    EXPECT_EQ(dest[1], 0);
    EXPECT_EQ(dest[2], 0);
}

// Test RGB8 with all max values
TEST_F(ConvertGfxColorTest_1574, RGB8ModeAllMax_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getRGB(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxRGB *rgb) {
            rgb->r = byteToCol(255);
            rgb->g = byteToCol(255);
            rgb->b = byteToCol(255);
        }));

    convertGfxColor(dest, splashModeRGB8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 255);
    EXPECT_EQ(dest[1], 255);
    EXPECT_EQ(dest[2], 255);
}

// Test CMYK8 with all zeros
TEST_F(ConvertGfxColorTest_1574, CMYK8ModeAllZeros_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getCMYK(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxCMYK *cmyk) {
            cmyk->c = byteToCol(0);
            cmyk->m = byteToCol(0);
            cmyk->y = byteToCol(0);
            cmyk->k = byteToCol(0);
        }));

    convertGfxColor(dest, splashModeCMYK8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 0);
    EXPECT_EQ(dest[1], 0);
    EXPECT_EQ(dest[2], 0);
    EXPECT_EQ(dest[3], 0);
}

// Test CMYK8 with all max values
TEST_F(ConvertGfxColorTest_1574, CMYK8ModeAllMax_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getCMYK(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxCMYK *cmyk) {
            cmyk->c = byteToCol(255);
            cmyk->m = byteToCol(255);
            cmyk->y = byteToCol(255);
            cmyk->k = byteToCol(255);
        }));

    convertGfxColor(dest, splashModeCMYK8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 255);
    EXPECT_EQ(dest[1], 255);
    EXPECT_EQ(dest[2], 255);
    EXPECT_EQ(dest[3], 255);
}

// Test that BGR8 does NOT set alpha channel (unlike XBGR8)
TEST_F(ConvertGfxColorTest_1574, BGR8ModeDoesNotSetAlpha_1574) {
    MockGfxColorSpace colorSpace;

    // Pre-fill dest[3] with a known value
    dest[3] = 42;

    EXPECT_CALL(colorSpace, getRGB(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxRGB *rgb) {
            rgb->r = byteToCol(10);
            rgb->g = byteToCol(20);
            rgb->b = byteToCol(30);
        }));

    convertGfxColor(dest, splashModeBGR8, &colorSpace, &src);

    // In BGR8 mode, dest[3] should be initialized to 0 (from the color initialization)
    // because the function initializes color[3] = 0 before the switch
    EXPECT_EQ(dest[3], 0);
}

// Test XBGR8 vs BGR8 - the key difference is alpha
TEST_F(ConvertGfxColorTest_1574, XBGR8AndBGR8DifferInAlpha_1574) {
    MockGfxColorSpace colorSpace;
    SplashColor destBGR, destXBGR;

    EXPECT_CALL(colorSpace, getRGB(::testing::_, ::testing::_))
        .Times(2)
        .WillRepeatedly(::testing::Invoke([](const GfxColor *color, GfxRGB *rgb) {
            rgb->r = byteToCol(100);
            rgb->g = byteToCol(100);
            rgb->b = byteToCol(100);
        }));

    convertGfxColor(destBGR, splashModeBGR8, &colorSpace, &src);
    convertGfxColor(destXBGR, splashModeXBGR8, &colorSpace, &src);

    // RGB values should be the same
    EXPECT_EQ(destBGR[0], destXBGR[0]);
    EXPECT_EQ(destBGR[1], destXBGR[1]);
    EXPECT_EQ(destBGR[2], destXBGR[2]);

    // Alpha differs
    EXPECT_EQ(destBGR[3], 0);
    EXPECT_EQ(destXBGR[3], 255);
}

// Test DeviceN8 with all zeros
TEST_F(ConvertGfxColorTest_1574, DeviceN8ModeAllZeros_1574) {
    MockGfxColorSpace colorSpace;

    EXPECT_CALL(colorSpace, getDeviceN(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxColor *deviceN) {
            for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
                deviceN->c[i] = byteToCol(0);
            }
        }));

    convertGfxColor(dest, splashModeDeviceN8, &colorSpace, &src);

    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        EXPECT_EQ(dest[i], 0);
    }
}

// Test that the source GfxColor is passed correctly to colorSpace methods
TEST_F(ConvertGfxColorTest_1574, SourceColorPassedToColorSpace_1574) {
    MockGfxColorSpace colorSpace;
    src.c[0] = byteToCol(42);

    EXPECT_CALL(colorSpace, getGray(::testing::_, ::testing::_))
        .WillOnce(::testing::Invoke([](const GfxColor *color, GfxGray *gray) {
            // Verify the source color is passed through
            EXPECT_EQ(colToByte(color->c[0]), 42);
            *gray = byteToCol(42);
        }));

    convertGfxColor(dest, splashModeMono8, &colorSpace, &src);

    EXPECT_EQ(dest[0], 42);
}
