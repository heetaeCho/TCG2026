static inline void getMatteColorRgb(GfxImageColorMap *colorMap, const GfxColor *matteColorIn, GfxRGB *matteColorRgb) {
    colorMap->getColorSpace()->getRGB(matteColorIn, matteColorRgb);
    matteColorRgb->r = colToByte(matteColorRgb->r);
    matteColorRgb->g = colToByte(matteColorRgb->g);
    matteColorRgb->b = colToByte(matteColorRgb->b);
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary poppler headers
#include "poppler/GfxState.h"
#include "poppler/Object.h"

// Include the .cc file to get access to the static inline function
// This is necessary because getMatteColorRgb is static inline
#include "poppler/CairoOutputDev.cc"

class GetMatteColorRgbTest_1926 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to create a GfxImageColorMap with a device RGB color space
static GfxImageColorMap* createRGBColorMap(int bits = 8) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    Object decodeObj;
    decodeObj.initNull();
    auto *colorMap = new GfxImageColorMap(bits, &decodeObj, std::move(cs));
    return colorMap;
}

// Helper to create a GfxImageColorMap with a device Gray color space
static GfxImageColorMap* createGrayColorMap(int bits = 8) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    Object decodeObj;
    decodeObj.initNull();
    auto *colorMap = new GfxImageColorMap(bits, &decodeObj, std::move(cs));
    return colorMap;
}

// Test with a basic RGB color (black - all zeros)
TEST_F(GetMatteColorRgbTest_1926, BlackColor_1926) {
    GfxImageColorMap *colorMap = createRGBColorMap();
    ASSERT_TRUE(colorMap->isOk());

    GfxColor matteColorIn;
    memset(&matteColorIn, 0, sizeof(matteColorIn));
    // Set all components to 0 (black)
    matteColorIn.c[0] = 0;
    matteColorIn.c[1] = 0;
    matteColorIn.c[2] = 0;

    GfxRGB matteColorRgb;
    getMatteColorRgb(colorMap, &matteColorIn, &matteColorRgb);

    // After colToByte, black should remain 0
    EXPECT_EQ(matteColorRgb.r, 0);
    EXPECT_EQ(matteColorRgb.g, 0);
    EXPECT_EQ(matteColorRgb.b, 0);

    delete colorMap;
}

// Test with white color (max values)
TEST_F(GetMatteColorRgbTest_1926, WhiteColor_1926) {
    GfxImageColorMap *colorMap = createRGBColorMap();
    ASSERT_TRUE(colorMap->isOk());

    GfxColor matteColorIn;
    memset(&matteColorIn, 0, sizeof(matteColorIn));
    // Set all components to max (white) - GfxColorComp max is 65535
    matteColorIn.c[0] = 65535;
    matteColorIn.c[1] = 65535;
    matteColorIn.c[2] = 65535;

    GfxRGB matteColorRgb;
    getMatteColorRgb(colorMap, &matteColorIn, &matteColorRgb);

    // colToByte(65535) should give 255
    EXPECT_EQ(matteColorRgb.r, 255);
    EXPECT_EQ(matteColorRgb.g, 255);
    EXPECT_EQ(matteColorRgb.b, 255);

    delete colorMap;
}

// Test with a specific color
TEST_F(GetMatteColorRgbTest_1926, SpecificRedColor_1926) {
    GfxImageColorMap *colorMap = createRGBColorMap();
    ASSERT_TRUE(colorMap->isOk());

    GfxColor matteColorIn;
    memset(&matteColorIn, 0, sizeof(matteColorIn));
    // Set red to max, green and blue to 0
    matteColorIn.c[0] = 65535;
    matteColorIn.c[1] = 0;
    matteColorIn.c[2] = 0;

    GfxRGB matteColorRgb;
    getMatteColorRgb(colorMap, &matteColorIn, &matteColorRgb);

    EXPECT_EQ(matteColorRgb.r, 255);
    EXPECT_EQ(matteColorRgb.g, 0);
    EXPECT_EQ(matteColorRgb.b, 0);

    delete colorMap;
}

// Test with mid-range values
TEST_F(GetMatteColorRgbTest_1926, MidRangeColor_1926) {
    GfxImageColorMap *colorMap = createRGBColorMap();
    ASSERT_TRUE(colorMap->isOk());

    GfxColor matteColorIn;
    memset(&matteColorIn, 0, sizeof(matteColorIn));
    // Approximately half intensity: 32768 should map to ~128
    matteColorIn.c[0] = 32768;
    matteColorIn.c[1] = 32768;
    matteColorIn.c[2] = 32768;

    GfxRGB matteColorRgb;
    getMatteColorRgb(colorMap, &matteColorIn, &matteColorRgb);

    // colToByte should convert to byte range; 32768/65535*255 ≈ 128
    EXPECT_GE(matteColorRgb.r, 127);
    EXPECT_LE(matteColorRgb.r, 129);
    EXPECT_GE(matteColorRgb.g, 127);
    EXPECT_LE(matteColorRgb.g, 129);
    EXPECT_GE(matteColorRgb.b, 127);
    EXPECT_LE(matteColorRgb.b, 129);

    delete colorMap;
}

// Test with GrayColorSpace - getRGB should convert gray to RGB
TEST_F(GetMatteColorRgbTest_1926, GrayColorSpaceWhite_1926) {
    GfxImageColorMap *colorMap = createGrayColorMap();
    ASSERT_TRUE(colorMap->isOk());

    GfxColor matteColorIn;
    memset(&matteColorIn, 0, sizeof(matteColorIn));
    matteColorIn.c[0] = 65535; // white gray

    GfxRGB matteColorRgb;
    getMatteColorRgb(colorMap, &matteColorIn, &matteColorRgb);

    // Gray white should map to RGB white
    EXPECT_EQ(matteColorRgb.r, 255);
    EXPECT_EQ(matteColorRgb.g, 255);
    EXPECT_EQ(matteColorRgb.b, 255);

    delete colorMap;
}

// Test with GrayColorSpace black
TEST_F(GetMatteColorRgbTest_1926, GrayColorSpaceBlack_1926) {
    GfxImageColorMap *colorMap = createGrayColorMap();
    ASSERT_TRUE(colorMap->isOk());

    GfxColor matteColorIn;
    memset(&matteColorIn, 0, sizeof(matteColorIn));
    matteColorIn.c[0] = 0; // black gray

    GfxRGB matteColorRgb;
    getMatteColorRgb(colorMap, &matteColorIn, &matteColorRgb);

    EXPECT_EQ(matteColorRgb.r, 0);
    EXPECT_EQ(matteColorRgb.g, 0);
    EXPECT_EQ(matteColorRgb.b, 0);

    delete colorMap;
}

// Test with different RGB channel values
TEST_F(GetMatteColorRgbTest_1926, DifferentChannelValues_1926) {
    GfxImageColorMap *colorMap = createRGBColorMap();
    ASSERT_TRUE(colorMap->isOk());

    GfxColor matteColorIn;
    memset(&matteColorIn, 0, sizeof(matteColorIn));
    matteColorIn.c[0] = 16384;  // ~64
    matteColorIn.c[1] = 32768;  // ~128
    matteColorIn.c[2] = 49152;  // ~192

    GfxRGB matteColorRgb;
    getMatteColorRgb(colorMap, &matteColorIn, &matteColorRgb);

    // Verify that different input values produce different output values
    EXPECT_NE(matteColorRgb.r, matteColorRgb.g);
    EXPECT_NE(matteColorRgb.g, matteColorRgb.b);
    EXPECT_NE(matteColorRgb.r, matteColorRgb.b);

    // R should be smallest, B should be largest
    EXPECT_LT(matteColorRgb.r, matteColorRgb.g);
    EXPECT_LT(matteColorRgb.g, matteColorRgb.b);

    delete colorMap;
}

// Test that output RGB values are in byte range [0, 255]
TEST_F(GetMatteColorRgbTest_1926, OutputInByteRange_1926) {
    GfxImageColorMap *colorMap = createRGBColorMap();
    ASSERT_TRUE(colorMap->isOk());

    GfxColor matteColorIn;
    memset(&matteColorIn, 0, sizeof(matteColorIn));
    matteColorIn.c[0] = 65535;
    matteColorIn.c[1] = 65535;
    matteColorIn.c[2] = 65535;

    GfxRGB matteColorRgb;
    getMatteColorRgb(colorMap, &matteColorIn, &matteColorRgb);

    EXPECT_GE(matteColorRgb.r, 0);
    EXPECT_LE(matteColorRgb.r, 255);
    EXPECT_GE(matteColorRgb.g, 0);
    EXPECT_LE(matteColorRgb.g, 255);
    EXPECT_GE(matteColorRgb.b, 0);
    EXPECT_LE(matteColorRgb.b, 255);

    delete colorMap;
}

// Test green-only color
TEST_F(GetMatteColorRgbTest_1926, GreenOnlyColor_1926) {
    GfxImageColorMap *colorMap = createRGBColorMap();
    ASSERT_TRUE(colorMap->isOk());

    GfxColor matteColorIn;
    memset(&matteColorIn, 0, sizeof(matteColorIn));
    matteColorIn.c[0] = 0;
    matteColorIn.c[1] = 65535;
    matteColorIn.c[2] = 0;

    GfxRGB matteColorRgb;
    getMatteColorRgb(colorMap, &matteColorIn, &matteColorRgb);

    EXPECT_EQ(matteColorRgb.r, 0);
    EXPECT_EQ(matteColorRgb.g, 255);
    EXPECT_EQ(matteColorRgb.b, 0);

    delete colorMap;
}

// Test blue-only color
TEST_F(GetMatteColorRgbTest_1926, BlueOnlyColor_1926) {
    GfxImageColorMap *colorMap = createRGBColorMap();
    ASSERT_TRUE(colorMap->isOk());

    GfxColor matteColorIn;
    memset(&matteColorIn, 0, sizeof(matteColorIn));
    matteColorIn.c[0] = 0;
    matteColorIn.c[1] = 0;
    matteColorIn.c[2] = 65535;

    GfxRGB matteColorRgb;
    getMatteColorRgb(colorMap, &matteColorIn, &matteColorRgb);

    EXPECT_EQ(matteColorRgb.r, 0);
    EXPECT_EQ(matteColorRgb.g, 0);
    EXPECT_EQ(matteColorRgb.b, 255);

    delete colorMap;
}
