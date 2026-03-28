#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

#include "poppler/GfxState.h"
#include "splash/SplashTypes.h"
#include "poppler/SplashOutputDev.h"

// We need access to the static inline function. Since it's defined in a .cc file,
// we need to either include that file or redeclare. Since the function is static inline
// in the .cc file, we cannot directly call it from outside. We'll need to work around this.
// 
// One approach: include the .cc file to get access to the static function.
// This is a common testing technique for static functions.
#include "poppler/SplashOutputDev.cc"

// Mock class for GfxColorSpace to control getGray, getRGB, getCMYK, getDeviceN
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

class ConvertGfxShortColorTest_1575 : public ::testing::Test {
protected:
    void SetUp() override {
        memset(dest, 0, sizeof(dest));
        memset(&srcColor, 0, sizeof(srcColor));
    }

    SplashColor dest;
    GfxColor srcColor;
    MockGfxColorSpace mockColorSpace;
};

// Test Mono1 mode - should call getGray and set dest[0]
TEST_F(ConvertGfxShortColorTest_1575, Mono1Mode_SetsGrayValue_1575) {
    EXPECT_CALL(mockColorSpace, getGray(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxGray *gray) {
            *gray = byteToCol(128);
        }));

    convertGfxShortColor(dest, splashModeMono1, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 128);
}

// Test Mono8 mode - should call getGray and set dest[0]
TEST_F(ConvertGfxShortColorTest_1575, Mono8Mode_SetsGrayValue_1575) {
    EXPECT_CALL(mockColorSpace, getGray(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxGray *gray) {
            *gray = byteToCol(255);
        }));

    convertGfxShortColor(dest, splashModeMono8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 255);
}

// Test Mono8 mode with zero gray
TEST_F(ConvertGfxShortColorTest_1575, Mono8Mode_ZeroGray_1575) {
    EXPECT_CALL(mockColorSpace, getGray(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxGray *gray) {
            *gray = byteToCol(0);
        }));

    convertGfxShortColor(dest, splashModeMono8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 0);
}

// Test RGB8 mode - should call getRGB and set dest[0..2]
TEST_F(ConvertGfxShortColorTest_1575, RGB8Mode_SetsRGBValues_1575) {
    EXPECT_CALL(mockColorSpace, getRGB(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxRGB *rgb) {
            rgb->r = byteToCol(100);
            rgb->g = byteToCol(150);
            rgb->b = byteToCol(200);
        }));

    convertGfxShortColor(dest, splashModeRGB8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 100);
    EXPECT_EQ(dest[1], 150);
    EXPECT_EQ(dest[2], 200);
}

// Test BGR8 mode - should call getRGB and set dest[0..2] (same as RGB8 in the code)
TEST_F(ConvertGfxShortColorTest_1575, BGR8Mode_SetsRGBValues_1575) {
    EXPECT_CALL(mockColorSpace, getRGB(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxRGB *rgb) {
            rgb->r = byteToCol(50);
            rgb->g = byteToCol(100);
            rgb->b = byteToCol(150);
        }));

    convertGfxShortColor(dest, splashModeBGR8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 50);
    EXPECT_EQ(dest[1], 100);
    EXPECT_EQ(dest[2], 150);
}

// Test XBGR8 mode - should call getRGB, set dest[0..2], and set dest[3] = 255
TEST_F(ConvertGfxShortColorTest_1575, XBGR8Mode_SetsRGBAndAlpha_1575) {
    EXPECT_CALL(mockColorSpace, getRGB(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxRGB *rgb) {
            rgb->r = byteToCol(10);
            rgb->g = byteToCol(20);
            rgb->b = byteToCol(30);
        }));

    convertGfxShortColor(dest, splashModeXBGR8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 10);
    EXPECT_EQ(dest[1], 20);
    EXPECT_EQ(dest[2], 30);
    EXPECT_EQ(dest[3], 255);  // Alpha channel
}

// Test CMYK8 mode - should call getCMYK and set dest[0..3]
TEST_F(ConvertGfxShortColorTest_1575, CMYK8Mode_SetsCMYKValues_1575) {
    EXPECT_CALL(mockColorSpace, getCMYK(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxCMYK *cmyk) {
            cmyk->c = byteToCol(10);
            cmyk->m = byteToCol(20);
            cmyk->y = byteToCol(30);
            cmyk->k = byteToCol(40);
        }));

    convertGfxShortColor(dest, splashModeCMYK8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 10);
    EXPECT_EQ(dest[1], 20);
    EXPECT_EQ(dest[2], 30);
    EXPECT_EQ(dest[3], 40);
}

// Test CMYK8 mode with all zeros
TEST_F(ConvertGfxShortColorTest_1575, CMYK8Mode_AllZeros_1575) {
    EXPECT_CALL(mockColorSpace, getCMYK(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxCMYK *cmyk) {
            cmyk->c = byteToCol(0);
            cmyk->m = byteToCol(0);
            cmyk->y = byteToCol(0);
            cmyk->k = byteToCol(0);
        }));

    convertGfxShortColor(dest, splashModeCMYK8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 0);
    EXPECT_EQ(dest[1], 0);
    EXPECT_EQ(dest[2], 0);
    EXPECT_EQ(dest[3], 0);
}

// Test CMYK8 mode with all max values
TEST_F(ConvertGfxShortColorTest_1575, CMYK8Mode_AllMax_1575) {
    EXPECT_CALL(mockColorSpace, getCMYK(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxCMYK *cmyk) {
            cmyk->c = byteToCol(255);
            cmyk->m = byteToCol(255);
            cmyk->y = byteToCol(255);
            cmyk->k = byteToCol(255);
        }));

    convertGfxShortColor(dest, splashModeCMYK8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 255);
    EXPECT_EQ(dest[1], 255);
    EXPECT_EQ(dest[2], 255);
    EXPECT_EQ(dest[3], 255);
}

// Test DeviceN8 mode - should call getDeviceN and set dest[0..SPOT_NCOMPS+3]
TEST_F(ConvertGfxShortColorTest_1575, DeviceN8Mode_SetsDeviceNValues_1575) {
    EXPECT_CALL(mockColorSpace, getDeviceN(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxColor *deviceN) {
            for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
                deviceN->c[i] = byteToCol(i * 10 % 256);
            }
        }));

    convertGfxShortColor(dest, splashModeDeviceN8, &mockColorSpace, &srcColor);
    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        EXPECT_EQ(dest[i], (unsigned char)(i * 10 % 256)) << "Mismatch at index " << i;
    }
}

// Test DeviceN8 mode with all zeros
TEST_F(ConvertGfxShortColorTest_1575, DeviceN8Mode_AllZeros_1575) {
    EXPECT_CALL(mockColorSpace, getDeviceN(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxColor *deviceN) {
            for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
                deviceN->c[i] = byteToCol(0);
            }
        }));

    convertGfxShortColor(dest, splashModeDeviceN8, &mockColorSpace, &srcColor);
    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        EXPECT_EQ(dest[i], 0) << "Mismatch at index " << i;
    }
}

// Test RGB8 mode with all max values (white)
TEST_F(ConvertGfxShortColorTest_1575, RGB8Mode_White_1575) {
    EXPECT_CALL(mockColorSpace, getRGB(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxRGB *rgb) {
            rgb->r = byteToCol(255);
            rgb->g = byteToCol(255);
            rgb->b = byteToCol(255);
        }));

    convertGfxShortColor(dest, splashModeRGB8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 255);
    EXPECT_EQ(dest[1], 255);
    EXPECT_EQ(dest[2], 255);
}

// Test RGB8 mode with all zero values (black)
TEST_F(ConvertGfxShortColorTest_1575, RGB8Mode_Black_1575) {
    EXPECT_CALL(mockColorSpace, getRGB(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxRGB *rgb) {
            rgb->r = byteToCol(0);
            rgb->g = byteToCol(0);
            rgb->b = byteToCol(0);
        }));

    convertGfxShortColor(dest, splashModeRGB8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 0);
    EXPECT_EQ(dest[1], 0);
    EXPECT_EQ(dest[2], 0);
}

// Test XBGR8 mode alpha is always 255 regardless of color values
TEST_F(ConvertGfxShortColorTest_1575, XBGR8Mode_AlphaAlways255_1575) {
    EXPECT_CALL(mockColorSpace, getRGB(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxRGB *rgb) {
            rgb->r = byteToCol(0);
            rgb->g = byteToCol(0);
            rgb->b = byteToCol(0);
        }));

    // Pre-set dest[3] to something other than 255
    dest[3] = 0;
    convertGfxShortColor(dest, splashModeXBGR8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[3], 255);
}

// Test that the correct color space method is called for each mode
TEST_F(ConvertGfxShortColorTest_1575, Mono1Mode_CallsGetGray_1575) {
    EXPECT_CALL(mockColorSpace, getGray(testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Invoke([](const GfxColor *, GfxGray *gray) {
            *gray = byteToCol(64);
        }));
    // Ensure other methods are NOT called
    EXPECT_CALL(mockColorSpace, getRGB(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mockColorSpace, getCMYK(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mockColorSpace, getDeviceN(testing::_, testing::_)).Times(0);

    convertGfxShortColor(dest, splashModeMono1, &mockColorSpace, &srcColor);
}

TEST_F(ConvertGfxShortColorTest_1575, RGB8Mode_CallsGetRGB_1575) {
    EXPECT_CALL(mockColorSpace, getGray(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mockColorSpace, getRGB(testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Invoke([](const GfxColor *, GfxRGB *rgb) {
            rgb->r = byteToCol(0);
            rgb->g = byteToCol(0);
            rgb->b = byteToCol(0);
        }));
    EXPECT_CALL(mockColorSpace, getCMYK(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mockColorSpace, getDeviceN(testing::_, testing::_)).Times(0);

    convertGfxShortColor(dest, splashModeRGB8, &mockColorSpace, &srcColor);
}

TEST_F(ConvertGfxShortColorTest_1575, CMYK8Mode_CallsGetCMYK_1575) {
    EXPECT_CALL(mockColorSpace, getGray(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mockColorSpace, getRGB(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mockColorSpace, getCMYK(testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Invoke([](const GfxColor *, GfxCMYK *cmyk) {
            cmyk->c = byteToCol(0);
            cmyk->m = byteToCol(0);
            cmyk->y = byteToCol(0);
            cmyk->k = byteToCol(0);
        }));
    EXPECT_CALL(mockColorSpace, getDeviceN(testing::_, testing::_)).Times(0);

    convertGfxShortColor(dest, splashModeCMYK8, &mockColorSpace, &srcColor);
}

TEST_F(ConvertGfxShortColorTest_1575, DeviceN8Mode_CallsGetDeviceN_1575) {
    EXPECT_CALL(mockColorSpace, getGray(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mockColorSpace, getRGB(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mockColorSpace, getCMYK(testing::_, testing::_)).Times(0);
    EXPECT_CALL(mockColorSpace, getDeviceN(testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Invoke([](const GfxColor *, GfxColor *deviceN) {
            for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
                deviceN->c[i] = byteToCol(0);
            }
        }));

    convertGfxShortColor(dest, splashModeDeviceN8, &mockColorSpace, &srcColor);
}

// Test that srcColor pointer is correctly passed to color space methods
TEST_F(ConvertGfxShortColorTest_1575, Mono8Mode_PassesSrcColorToGetGray_1575) {
    srcColor.c[0] = byteToCol(42);

    EXPECT_CALL(mockColorSpace, getGray(testing::_, testing::_))
        .WillOnce(testing::Invoke([this](const GfxColor *color, GfxGray *gray) {
            EXPECT_EQ(color, &srcColor);
            *gray = byteToCol(42);
        }));

    convertGfxShortColor(dest, splashModeMono8, &mockColorSpace, &srcColor);
    EXPECT_EQ(dest[0], 42);
}

// Test DeviceN8 with all max values
TEST_F(ConvertGfxShortColorTest_1575, DeviceN8Mode_AllMax_1575) {
    EXPECT_CALL(mockColorSpace, getDeviceN(testing::_, testing::_))
        .WillOnce(testing::Invoke([](const GfxColor *, GfxColor *deviceN) {
            for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
                deviceN->c[i] = byteToCol(255);
            }
        }));

    convertGfxShortColor(dest, splashModeDeviceN8, &mockColorSpace, &srcColor);
    for (int i = 0; i < SPOT_NCOMPS + 4; i++) {
        EXPECT_EQ(dest[i], 255) << "Mismatch at index " << i;
    }
}
