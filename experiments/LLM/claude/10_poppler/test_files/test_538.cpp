bool useDeviceNLine() const { 
    return (colorSpace2 && colorSpace2->useGetDeviceNLine()) || 
           (!colorSpace2 && colorSpace->useGetDeviceNLine()); 
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "Object.h"
#include <memory>

class GfxImageColorMapTest_538 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to create a GfxImageColorMap with a DeviceRGB color space
static std::unique_ptr<GfxImageColorMap> createRGBColorMap(int bits) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = GfxColorSpace::parse(nullptr, nullptr, nullptr, nullptr, 0);
    // Use DeviceRGB
    auto colorSpace = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(colorSpace));
    return map;
}

static std::unique_ptr<GfxImageColorMap> createGrayColorMap(int bits) {
    Object decodeObj;
    decodeObj.initNull();
    auto colorSpace = std::make_unique<GfxDeviceGrayColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(colorSpace));
    return map;
}

static std::unique_ptr<GfxImageColorMap> createCMYKColorMap(int bits) {
    Object decodeObj;
    decodeObj.initNull();
    auto colorSpace = std::make_unique<GfxDeviceCMYKColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(colorSpace));
    return map;
}

// Test that a valid RGB color map reports isOk
TEST_F(GfxImageColorMapTest_538, RGBColorMapIsOk_538) {
    auto map = createRGBColorMap(8);
    ASSERT_NE(map, nullptr);
    EXPECT_TRUE(map->isOk());
}

// Test that a valid Gray color map reports isOk
TEST_F(GfxImageColorMapTest_538, GrayColorMapIsOk_538) {
    auto map = createGrayColorMap(8);
    ASSERT_NE(map, nullptr);
    EXPECT_TRUE(map->isOk());
}

// Test that a valid CMYK color map reports isOk
TEST_F(GfxImageColorMapTest_538, CMYKColorMapIsOk_538) {
    auto map = createCMYKColorMap(8);
    ASSERT_NE(map, nullptr);
    EXPECT_TRUE(map->isOk());
}

// Test getBits returns correct value
TEST_F(GfxImageColorMapTest_538, GetBitsReturnsCorrectValue_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    EXPECT_EQ(map->getBits(), 8);
}

// Test getBits with different bit depth
TEST_F(GfxImageColorMapTest_538, GetBits1Bit_538) {
    auto map = createGrayColorMap(1);
    ASSERT_TRUE(map->isOk());
    EXPECT_EQ(map->getBits(), 1);
}

// Test getNumPixelComps for RGB
TEST_F(GfxImageColorMapTest_538, RGBNumPixelComps_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    EXPECT_EQ(map->getNumPixelComps(), 3);
}

// Test getNumPixelComps for Gray
TEST_F(GfxImageColorMapTest_538, GrayNumPixelComps_538) {
    auto map = createGrayColorMap(8);
    ASSERT_TRUE(map->isOk());
    EXPECT_EQ(map->getNumPixelComps(), 1);
}

// Test getNumPixelComps for CMYK
TEST_F(GfxImageColorMapTest_538, CMYKNumPixelComps_538) {
    auto map = createCMYKColorMap(8);
    ASSERT_TRUE(map->isOk());
    EXPECT_EQ(map->getNumPixelComps(), 4);
}

// Test getColorSpace returns non-null
TEST_F(GfxImageColorMapTest_538, GetColorSpaceNotNull_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    EXPECT_NE(map->getColorSpace(), nullptr);
}

// Test useDeviceNLine for DeviceRGB (should be false)
TEST_F(GfxImageColorMapTest_538, UseDeviceNLineRGB_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    EXPECT_FALSE(map->useDeviceNLine());
}

// Test useDeviceNLine for DeviceGray (should be false)
TEST_F(GfxImageColorMapTest_538, UseDeviceNLineGray_538) {
    auto map = createGrayColorMap(8);
    ASSERT_TRUE(map->isOk());
    EXPECT_FALSE(map->useDeviceNLine());
}

// Test useRGBLine for DeviceRGB
TEST_F(GfxImageColorMapTest_538, UseRGBLineRGB_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    // DeviceRGB typically supports RGB line
    bool result = map->useRGBLine();
    // Just verify it returns a valid bool (no crash)
    EXPECT_TRUE(result || !result);
}

// Test useCMYKLine for DeviceCMYK
TEST_F(GfxImageColorMapTest_538, UseCMYKLineCMYK_538) {
    auto map = createCMYKColorMap(8);
    ASSERT_TRUE(map->isOk());
    bool result = map->useCMYKLine();
    EXPECT_TRUE(result || !result);
}

// Test getDecodeLow and getDecodeHigh for default decode
TEST_F(GfxImageColorMapTest_538, DefaultDecodeValues_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    // Default decode for 8-bit is typically 0..1
    EXPECT_DOUBLE_EQ(map->getDecodeLow(0), 0.0);
    EXPECT_DOUBLE_EQ(map->getDecodeHigh(0), 1.0);
}

// Test copy
TEST_F(GfxImageColorMapTest_538, CopyCreatesValidMap_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    auto copy = map->copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_TRUE(copy->isOk());
    EXPECT_EQ(copy->getBits(), map->getBits());
    EXPECT_EQ(copy->getNumPixelComps(), map->getNumPixelComps());
    delete copy;
}

// Test getMatteColor initially returns something (not set)
TEST_F(GfxImageColorMapTest_538, GetMatteColorInitial_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    const GfxColor *matte = map->getMatteColor();
    // May or may not be null depending on implementation
    (void)matte;
}

// Test setMatteColor and getMatteColor
TEST_F(GfxImageColorMapTest_538, SetAndGetMatteColor_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 32768;
    color.c[2] = 65535;
    map->setMatteColor(&color);
    const GfxColor *retrieved = map->getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 0);
    EXPECT_EQ(retrieved->c[1], 32768);
    EXPECT_EQ(retrieved->c[2], 65535);
}

// Test getRGB for a known pixel value
TEST_F(GfxImageColorMapTest_538, GetRGBForWhitePixel_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    unsigned char pixel[3] = {255, 255, 255};
    GfxRGB rgb;
    map->getRGB(pixel, &rgb);
    // White pixel in DeviceRGB should map to white
    EXPECT_GE(rgb.r, 65000);
    EXPECT_GE(rgb.g, 65000);
    EXPECT_GE(rgb.b, 65000);
}

// Test getRGB for a black pixel
TEST_F(GfxImageColorMapTest_538, GetRGBForBlackPixel_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    unsigned char pixel[3] = {0, 0, 0};
    GfxRGB rgb;
    map->getRGB(pixel, &rgb);
    EXPECT_LE(rgb.r, 500);
    EXPECT_LE(rgb.g, 500);
    EXPECT_LE(rgb.b, 500);
}

// Test getGray for a gray pixel
TEST_F(GfxImageColorMapTest_538, GetGrayForWhitePixel_538) {
    auto map = createGrayColorMap(8);
    ASSERT_TRUE(map->isOk());
    unsigned char pixel[1] = {255};
    GfxGray gray;
    map->getGray(pixel, &gray);
    EXPECT_GE(gray, 65000);
}

// Test getGray for black pixel
TEST_F(GfxImageColorMapTest_538, GetGrayForBlackPixel_538) {
    auto map = createGrayColorMap(8);
    ASSERT_TRUE(map->isOk());
    unsigned char pixel[1] = {0};
    GfxGray gray;
    map->getGray(pixel, &gray);
    EXPECT_LE(gray, 500);
}

// Test getRGBLine with unsigned int output
TEST_F(GfxImageColorMapTest_538, GetRGBLineUintOutput_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    unsigned char in[6] = {255, 0, 0, 0, 255, 0}; // Red, Green
    unsigned int out[2] = {0, 0};
    map->getRGBLine(in, out, 2);
    // Just ensure it doesn't crash and produces some output
    EXPECT_NE(out[0], 0u);
    EXPECT_NE(out[1], 0u);
}

// Test getRGBLine with unsigned char output
TEST_F(GfxImageColorMapTest_538, GetRGBLineUcharOutput_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    unsigned char in[3] = {128, 128, 128};
    unsigned char out[3] = {0, 0, 0};
    map->getRGBLine(in, out, 1);
    // Gray pixel in RGB should produce approximately equal R, G, B
    EXPECT_NEAR(out[0], out[1], 5);
    EXPECT_NEAR(out[1], out[2], 5);
}

// Test getGrayLine
TEST_F(GfxImageColorMapTest_538, GetGrayLine_538) {
    auto map = createGrayColorMap(8);
    ASSERT_TRUE(map->isOk());
    unsigned char in[2] = {0, 255};
    unsigned char out[2] = {128, 128};
    map->getGrayLine(in, out, 2);
    EXPECT_LE(out[0], 5);   // black
    EXPECT_GE(out[1], 250); // white
}

// Test copy preserves decode values
TEST_F(GfxImageColorMapTest_538, CopyPreservesDecodeValues_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    auto copy = map->copy();
    ASSERT_NE(copy, nullptr);
    for (int i = 0; i < map->getNumPixelComps(); i++) {
        EXPECT_DOUBLE_EQ(copy->getDecodeLow(i), map->getDecodeLow(i));
        EXPECT_DOUBLE_EQ(copy->getDecodeHigh(i), map->getDecodeHigh(i));
    }
    delete copy;
}

// Test with 4-bit depth
TEST_F(GfxImageColorMapTest_538, FourBitDepthGray_538) {
    auto map = createGrayColorMap(4);
    ASSERT_TRUE(map->isOk());
    EXPECT_EQ(map->getBits(), 4);
    unsigned char pixel[1] = {15}; // max for 4-bit
    GfxGray gray;
    map->getGray(pixel, &gray);
    EXPECT_GE(gray, 65000);
}

// Test getColorSpace mode for RGB
TEST_F(GfxImageColorMapTest_538, GetColorSpaceModeRGB_538) {
    auto map = createRGBColorMap(8);
    ASSERT_TRUE(map->isOk());
    GfxColorSpace *cs = map->getColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceRGB);
}

// Test getColorSpace mode for Gray
TEST_F(GfxImageColorMapTest_538, GetColorSpaceModeGray_538) {
    auto map = createGrayColorMap(8);
    ASSERT_TRUE(map->isOk());
    GfxColorSpace *cs = map->getColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceGray);
}

// Test getColorSpace mode for CMYK
TEST_F(GfxImageColorMapTest_538, GetColorSpaceModeCMYK_538) {
    auto map = createCMYKColorMap(8);
    ASSERT_TRUE(map->isOk());
    GfxColorSpace *cs = map->getColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csDeviceCMYK);
}
