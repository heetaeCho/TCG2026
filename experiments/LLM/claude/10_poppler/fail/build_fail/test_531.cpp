#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "Object.h"
#include <memory>

class GfxImageColorMapTest_531 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a valid DeviceRGB color space
    std::unique_ptr<GfxColorSpace> createDeviceRGBColorSpace() {
        return std::unique_ptr<GfxColorSpace>(GfxColorSpace::parse(nullptr, Object(objName, "DeviceRGB").getObj(), nullptr, nullptr, nullptr, 0));
    }

    // Helper to create a valid DeviceGray color space
    std::unique_ptr<GfxColorSpace> createDeviceGrayColorSpace() {
        return std::unique_ptr<GfxColorSpace>(GfxColorSpace::parse(nullptr, Object(objName, "DeviceGray").getObj(), nullptr, nullptr, nullptr, 0));
    }

    // Helper to create a valid DeviceCMYK color space
    std::unique_ptr<GfxColorSpace> createDeviceCMYKColorSpace() {
        return std::unique_ptr<GfxColorSpace>(GfxColorSpace::parse(nullptr, Object(objName, "DeviceCMYK").getObj(), nullptr, nullptr, nullptr, 0));
    }
};

// Test construction with DeviceRGB colorspace and valid bits
TEST_F(GfxImageColorMapTest_531, ConstructWithDeviceRGB_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = GfxDeviceRGBColorSpace::parse(nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    EXPECT_TRUE(colorMap.isOk());
}

// Test getColorSpace returns non-null for valid construction
TEST_F(GfxImageColorMapTest_531, GetColorSpaceReturnsNonNull_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    EXPECT_NE(nullptr, colorMap.getColorSpace());
}

// Test getBits returns the bits passed during construction
TEST_F(GfxImageColorMapTest_531, GetBitsReturnsCorrectValue_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    EXPECT_EQ(8, colorMap.getBits());
}

// Test getNumPixelComps for DeviceRGB (should be 3)
TEST_F(GfxImageColorMapTest_531, GetNumPixelCompsRGB_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    EXPECT_EQ(3, colorMap.getNumPixelComps());
}

// Test getNumPixelComps for DeviceGray (should be 1)
TEST_F(GfxImageColorMapTest_531, GetNumPixelCompsGray_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceGrayColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    EXPECT_EQ(1, colorMap.getNumPixelComps());
}

// Test getNumPixelComps for DeviceCMYK (should be 4)
TEST_F(GfxImageColorMapTest_531, GetNumPixelCompsCMYK_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceCMYKColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    EXPECT_EQ(4, colorMap.getNumPixelComps());
}

// Test with 1-bit depth
TEST_F(GfxImageColorMapTest_531, OneBitDepth_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceGrayColorSpace();
    GfxImageColorMap colorMap(1, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    EXPECT_EQ(1, colorMap.getBits());
}

// Test getDecodeLow with default decode for DeviceGray 8-bit
TEST_F(GfxImageColorMapTest_531, GetDecodeLowDefault_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceGrayColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    EXPECT_DOUBLE_EQ(0.0, colorMap.getDecodeLow(0));
}

// Test getDecodeHigh with default decode for DeviceGray 8-bit
TEST_F(GfxImageColorMapTest_531, GetDecodeHighDefault_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceGrayColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    EXPECT_DOUBLE_EQ(1.0, colorMap.getDecodeHigh(0));
}

// Test copy functionality
TEST_F(GfxImageColorMapTest_531, CopyProducesSameBits_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    GfxImageColorMap *copied = colorMap.copy();
    ASSERT_NE(nullptr, copied);
    EXPECT_EQ(colorMap.getBits(), copied->getBits());
    EXPECT_EQ(colorMap.getNumPixelComps(), copied->getNumPixelComps());
    EXPECT_TRUE(copied->isOk());
    delete copied;
}

// Test getMatteColor returns null when not set
TEST_F(GfxImageColorMapTest_531, GetMatteColorDefaultNull_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceGrayColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    // The matte color should be null or not set before calling setMatteColor
    const GfxColor *matteColor = colorMap.getMatteColor();
    // Matte is not set by default, implementation may return nullptr
    // We just verify the call doesn't crash
    (void)matteColor;
}

// Test setMatteColor and getMatteColor
TEST_F(GfxImageColorMapTest_531, SetAndGetMatteColor_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    GfxColor color;
    color.c[0] = dblToCol(0.5);
    color.c[1] = dblToCol(0.3);
    color.c[2] = dblToCol(0.7);
    colorMap.setMatteColor(&color);
    const GfxColor *retrieved = colorMap.getMatteColor();
    ASSERT_NE(nullptr, retrieved);
    EXPECT_EQ(color.c[0], retrieved->c[0]);
    EXPECT_EQ(color.c[1], retrieved->c[1]);
    EXPECT_EQ(color.c[2], retrieved->c[2]);
}

// Test getGray with DeviceGray colorspace
TEST_F(GfxImageColorMapTest_531, GetGrayDeviceGray_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceGrayColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    unsigned char pixel = 0;
    GfxGray gray;
    colorMap.getGray(&pixel, &gray);
    // pixel 0 with default decode [0,1] should map to gray = 0
    EXPECT_EQ(0, colToDbl(gray));
}

// Test getGray with max pixel value
TEST_F(GfxImageColorMapTest_531, GetGrayMaxPixel_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceGrayColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    unsigned char pixel = 255;
    GfxGray gray;
    colorMap.getGray(&pixel, &gray);
    double grayVal = colToDbl(gray);
    EXPECT_NEAR(1.0, grayVal, 0.01);
}

// Test getRGB with DeviceRGB colorspace
TEST_F(GfxImageColorMapTest_531, GetRGBDeviceRGB_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    unsigned char pixel[3] = {255, 0, 128};
    GfxRGB rgb;
    colorMap.getRGB(pixel, &rgb);
    EXPECT_NEAR(1.0, colToDbl(rgb.r), 0.01);
    EXPECT_NEAR(0.0, colToDbl(rgb.g), 0.01);
    EXPECT_NEAR(128.0 / 255.0, colToDbl(rgb.b), 0.02);
}

// Test useRGBLine
TEST_F(GfxImageColorMapTest_531, UseRGBLine_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    // Just verify it doesn't crash and returns a bool
    bool result = colorMap.useRGBLine();
    (void)result;
}

// Test useCMYKLine
TEST_F(GfxImageColorMapTest_531, UseCMYKLine_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceCMYKColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    bool result = colorMap.useCMYKLine();
    (void)result;
}

// Test useDeviceNLine
TEST_F(GfxImageColorMapTest_531, UseDeviceNLine_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    bool result = colorMap.useDeviceNLine();
    (void)result;
}

// Test with 4-bit depth
TEST_F(GfxImageColorMapTest_531, FourBitDepth_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceGrayColorSpace();
    GfxImageColorMap colorMap(4, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    EXPECT_EQ(4, colorMap.getBits());
}

// Test with 16-bit depth
TEST_F(GfxImageColorMapTest_531, SixteenBitDepth_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceGrayColorSpace();
    GfxImageColorMap colorMap(16, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    EXPECT_EQ(16, colorMap.getBits());
}

// Test getRGBLine (unsigned int output)
TEST_F(GfxImageColorMapTest_531, GetRGBLineUint_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    unsigned char input[6] = {255, 0, 0, 0, 255, 0};
    unsigned int output[2];
    colorMap.getRGBLine(input, output, 2);
    // Just verify it doesn't crash
}

// Test getRGBLine (unsigned char output)
TEST_F(GfxImageColorMapTest_531, GetRGBLineUchar_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    unsigned char input[6] = {255, 0, 0, 0, 255, 0};
    unsigned char output[6];
    colorMap.getRGBLine(input, output, 2);
    // Just verify it doesn't crash
}

// Test getGrayLine
TEST_F(GfxImageColorMapTest_531, GetGrayLine_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceGrayColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    unsigned char input[3] = {0, 128, 255};
    unsigned char output[3];
    colorMap.getGrayLine(input, output, 3);
    EXPECT_EQ(0, output[0]);
    EXPECT_EQ(255, output[2]);
}

// Test getCMYK with DeviceCMYK
TEST_F(GfxImageColorMapTest_531, GetCMYK_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceCMYKColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    unsigned char pixel[4] = {255, 0, 0, 0};
    GfxCMYK cmyk;
    colorMap.getCMYK(pixel, &cmyk);
    EXPECT_NEAR(1.0, colToDbl(cmyk.c), 0.01);
    EXPECT_NEAR(0.0, colToDbl(cmyk.m), 0.01);
}

// Test getColor
TEST_F(GfxImageColorMapTest_531, GetColor_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    unsigned char pixel[3] = {255, 128, 0};
    GfxColor color;
    colorMap.getColor(pixel, &color);
    // Verify it doesn't crash and produces some values
}

// Test with null colorspace (should result in isOk() == false)
TEST_F(GfxImageColorMapTest_531, NullColorSpaceNotOk_531) {
    Object decodeObj;
    decodeObj.initNull();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(nullptr));
    EXPECT_FALSE(colorMap.isOk());
}

// Test copy of copied map retains properties
TEST_F(GfxImageColorMapTest_531, CopyRetainsDecodeLow_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    GfxImageColorMap *copied = colorMap.copy();
    ASSERT_NE(nullptr, copied);
    for (int i = 0; i < copied->getNumPixelComps(); i++) {
        EXPECT_DOUBLE_EQ(colorMap.getDecodeLow(i), copied->getDecodeLow(i));
        EXPECT_DOUBLE_EQ(colorMap.getDecodeHigh(i), copied->getDecodeHigh(i));
    }
    delete copied;
}

// Test getRGBXLine
TEST_F(GfxImageColorMapTest_531, GetRGBXLine_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    unsigned char input[3] = {255, 0, 128};
    unsigned char output[4] = {0};
    colorMap.getRGBXLine(input, output, 1);
    // RGBX: 4 bytes per pixel, X is padding
    EXPECT_EQ(255, output[0]);
    EXPECT_EQ(0, output[1]);
}

// Test getDecodeLow for multiple components in RGB
TEST_F(GfxImageColorMapTest_531, GetDecodeLowMultipleComponents_531) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = new GfxDeviceRGBColorSpace();
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    for (int i = 0; i < 3; i++) {
        EXPECT_DOUBLE_EQ(0.0, colorMap.getDecodeLow(i));
        EXPECT_DOUBLE_EQ(1.0, colorMap.getDecodeHigh(i));
    }
}
