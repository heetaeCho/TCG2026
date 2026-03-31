#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/GfxState.h"
#include "poppler/Object.h"
#include <memory>

// Helper to create a valid GfxImageColorMap for testing
// We need a valid colorspace and decode array to construct one
class GfxImageColorMapTest_539 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a DeviceGray colormap (simplest case)
    std::unique_ptr<GfxImageColorMap> createGrayColorMap(int bits = 8) {
        Object decodeObj;
        decodeObj = Object(objNull);
        auto cs = GfxColorSpace::create(csDeviceGray);
        if (!cs) return nullptr;
        auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(cs));
        if (!colorMap->isOk()) return nullptr;
        return colorMap;
    }

    // Helper to create a DeviceRGB colormap
    std::unique_ptr<GfxImageColorMap> createRGBColorMap(int bits = 8) {
        Object decodeObj;
        decodeObj = Object(objNull);
        auto cs = GfxColorSpace::create(csDeviceRGB);
        if (!cs) return nullptr;
        auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(cs));
        if (!colorMap->isOk()) return nullptr;
        return colorMap;
    }

    // Helper to create a DeviceCMYK colormap
    std::unique_ptr<GfxImageColorMap> createCMYKColorMap(int bits = 8) {
        Object decodeObj;
        decodeObj = Object(objNull);
        auto cs = GfxColorSpace::create(csDeviceCMYK);
        if (!cs) return nullptr;
        auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(cs));
        if (!colorMap->isOk()) return nullptr;
        return colorMap;
    }
};

// Test that setMatteColor sets the matte color and getMatteColor retrieves it
TEST_F(GfxImageColorMapTest_539, SetMatteColorAndGetMatteColor_539) {
    auto colorMap = createGrayColorMap();
    ASSERT_NE(colorMap, nullptr);

    GfxColor matteColor;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        matteColor.c[i] = 0;
    }
    matteColor.c[0] = dblToCol(0.5);

    colorMap->setMatteColor(&matteColor);

    const GfxColor *retrieved = colorMap->getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], matteColor.c[0]);
}

// Test setMatteColor with all components set
TEST_F(GfxImageColorMapTest_539, SetMatteColorAllComponents_539) {
    auto colorMap = createRGBColorMap();
    ASSERT_NE(colorMap, nullptr);

    GfxColor matteColor;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        matteColor.c[i] = 0;
    }
    matteColor.c[0] = dblToCol(0.25);
    matteColor.c[1] = dblToCol(0.50);
    matteColor.c[2] = dblToCol(0.75);

    colorMap->setMatteColor(&matteColor);

    const GfxColor *retrieved = colorMap->getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], matteColor.c[0]);
    EXPECT_EQ(retrieved->c[1], matteColor.c[1]);
    EXPECT_EQ(retrieved->c[2], matteColor.c[2]);
}

// Test setMatteColor with zero color
TEST_F(GfxImageColorMapTest_539, SetMatteColorZero_539) {
    auto colorMap = createGrayColorMap();
    ASSERT_NE(colorMap, nullptr);

    GfxColor matteColor;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        matteColor.c[i] = 0;
    }

    colorMap->setMatteColor(&matteColor);

    const GfxColor *retrieved = colorMap->getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 0);
}

// Test setMatteColor overwrite
TEST_F(GfxImageColorMapTest_539, SetMatteColorOverwrite_539) {
    auto colorMap = createGrayColorMap();
    ASSERT_NE(colorMap, nullptr);

    GfxColor matteColor1;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        matteColor1.c[i] = 0;
    }
    matteColor1.c[0] = dblToCol(0.3);
    colorMap->setMatteColor(&matteColor1);

    GfxColor matteColor2;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        matteColor2.c[i] = 0;
    }
    matteColor2.c[0] = dblToCol(0.7);
    colorMap->setMatteColor(&matteColor2);

    const GfxColor *retrieved = colorMap->getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], matteColor2.c[0]);
}

// Test that a newly created colormap is valid (isOk)
TEST_F(GfxImageColorMapTest_539, GrayColorMapIsOk_539) {
    auto colorMap = createGrayColorMap();
    ASSERT_NE(colorMap, nullptr);
    EXPECT_TRUE(colorMap->isOk());
}

// Test getColorSpace returns non-null for a valid colormap
TEST_F(GfxImageColorMapTest_539, GetColorSpaceNotNull_539) {
    auto colorMap = createGrayColorMap();
    ASSERT_NE(colorMap, nullptr);
    EXPECT_NE(colorMap->getColorSpace(), nullptr);
}

// Test getNumPixelComps for gray (should be 1)
TEST_F(GfxImageColorMapTest_539, GrayNumPixelComps_539) {
    auto colorMap = createGrayColorMap();
    ASSERT_NE(colorMap, nullptr);
    EXPECT_EQ(colorMap->getNumPixelComps(), 1);
}

// Test getNumPixelComps for RGB (should be 3)
TEST_F(GfxImageColorMapTest_539, RGBNumPixelComps_539) {
    auto colorMap = createRGBColorMap();
    ASSERT_NE(colorMap, nullptr);
    EXPECT_EQ(colorMap->getNumPixelComps(), 3);
}

// Test getNumPixelComps for CMYK (should be 4)
TEST_F(GfxImageColorMapTest_539, CMYKNumPixelComps_539) {
    auto colorMap = createCMYKColorMap();
    ASSERT_NE(colorMap, nullptr);
    EXPECT_EQ(colorMap->getNumPixelComps(), 4);
}

// Test getBits returns the correct bit depth
TEST_F(GfxImageColorMapTest_539, GetBits8_539) {
    auto colorMap = createGrayColorMap(8);
    ASSERT_NE(colorMap, nullptr);
    EXPECT_EQ(colorMap->getBits(), 8);
}

// Test getBits with 1-bit
TEST_F(GfxImageColorMapTest_539, GetBits1_539) {
    auto colorMap = createGrayColorMap(1);
    ASSERT_NE(colorMap, nullptr);
    EXPECT_EQ(colorMap->getBits(), 1);
}

// Test getDecodeLow and getDecodeHigh for default decode (Gray, 8-bit)
TEST_F(GfxImageColorMapTest_539, DefaultDecodeGray_539) {
    auto colorMap = createGrayColorMap(8);
    ASSERT_NE(colorMap, nullptr);
    // Default decode for gray is [0, 1]
    EXPECT_DOUBLE_EQ(colorMap->getDecodeLow(0), 0.0);
    EXPECT_DOUBLE_EQ(colorMap->getDecodeHigh(0), 1.0);
}

// Test copy creates a valid copy
TEST_F(GfxImageColorMapTest_539, CopyIsOk_539) {
    auto colorMap = createGrayColorMap();
    ASSERT_NE(colorMap, nullptr);

    GfxImageColorMap *copiedMap = colorMap->copy();
    ASSERT_NE(copiedMap, nullptr);
    EXPECT_TRUE(copiedMap->isOk());
    EXPECT_EQ(copiedMap->getBits(), colorMap->getBits());
    EXPECT_EQ(copiedMap->getNumPixelComps(), colorMap->getNumPixelComps());

    delete copiedMap;
}

// Test copy preserves matte color
TEST_F(GfxImageColorMapTest_539, CopyPreservesMatteColor_539) {
    auto colorMap = createGrayColorMap();
    ASSERT_NE(colorMap, nullptr);

    GfxColor matteColor;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        matteColor.c[i] = 0;
    }
    matteColor.c[0] = dblToCol(0.42);
    colorMap->setMatteColor(&matteColor);

    GfxImageColorMap *copiedMap = colorMap->copy();
    ASSERT_NE(copiedMap, nullptr);

    const GfxColor *retrieved = copiedMap->getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], matteColor.c[0]);

    delete copiedMap;
}

// Test getGray on a gray colormap
TEST_F(GfxImageColorMapTest_539, GetGrayFromGrayColorMap_539) {
    auto colorMap = createGrayColorMap(8);
    ASSERT_NE(colorMap, nullptr);

    unsigned char pixel = 0; // black
    GfxGray gray;
    colorMap->getGray(&pixel, &gray);
    // 0 should map to black (gray ~= 0)
    EXPECT_LE(colToDbl(gray), 0.01);

    pixel = 255; // white
    colorMap->getGray(&pixel, &gray);
    // 255 should map to white (gray ~= 1)
    EXPECT_GE(colToDbl(gray), 0.99);
}

// Test getRGB on an RGB colormap
TEST_F(GfxImageColorMapTest_539, GetRGBFromRGBColorMap_539) {
    auto colorMap = createRGBColorMap(8);
    ASSERT_NE(colorMap, nullptr);

    unsigned char pixel[3] = {255, 0, 0}; // red
    GfxRGB rgb;
    colorMap->getRGB(pixel, &rgb);
    EXPECT_GE(colToDbl(rgb.r), 0.99);
    EXPECT_LE(colToDbl(rgb.g), 0.01);
    EXPECT_LE(colToDbl(rgb.b), 0.01);
}

// Test getRGB for green
TEST_F(GfxImageColorMapTest_539, GetRGBGreenFromRGBColorMap_539) {
    auto colorMap = createRGBColorMap(8);
    ASSERT_NE(colorMap, nullptr);

    unsigned char pixel[3] = {0, 255, 0}; // green
    GfxRGB rgb;
    colorMap->getRGB(pixel, &rgb);
    EXPECT_LE(colToDbl(rgb.r), 0.01);
    EXPECT_GE(colToDbl(rgb.g), 0.99);
    EXPECT_LE(colToDbl(rgb.b), 0.01);
}

// Test getRGB for blue
TEST_F(GfxImageColorMapTest_539, GetRGBBlueFromRGBColorMap_539) {
    auto colorMap = createRGBColorMap(8);
    ASSERT_NE(colorMap, nullptr);

    unsigned char pixel[3] = {0, 0, 255}; // blue
    GfxRGB rgb;
    colorMap->getRGB(pixel, &rgb);
    EXPECT_LE(colToDbl(rgb.r), 0.01);
    EXPECT_LE(colToDbl(rgb.g), 0.01);
    EXPECT_GE(colToDbl(rgb.b), 0.99);
}

// Test getRGBLine with unsigned int output
TEST_F(GfxImageColorMapTest_539, GetRGBLineUintOutput_539) {
    auto colorMap = createRGBColorMap(8);
    ASSERT_NE(colorMap, nullptr);

    unsigned char input[6] = {255, 0, 0, 0, 255, 0}; // red, green
    unsigned int output[2] = {0, 0};
    colorMap->getRGBLine(input, output, 2);

    // Output should be non-zero (packed RGB values)
    // Just verify it runs and produces output
    EXPECT_NE(output[0], 0u);
    EXPECT_NE(output[1], 0u);
}

// Test getGrayLine
TEST_F(GfxImageColorMapTest_539, GetGrayLine_539) {
    auto colorMap = createGrayColorMap(8);
    ASSERT_NE(colorMap, nullptr);

    unsigned char input[3] = {0, 128, 255};
    unsigned char output[3] = {0, 0, 0};
    colorMap->getGrayLine(input, output, 3);

    // Black pixel should produce low gray value
    EXPECT_LE(output[0], 5);
    // White pixel should produce high gray value
    EXPECT_GE(output[2], 250);
}

// Test setMatteColor with max component values
TEST_F(GfxImageColorMapTest_539, SetMatteColorMaxValues_539) {
    auto colorMap = createRGBColorMap();
    ASSERT_NE(colorMap, nullptr);

    GfxColor matteColor;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        matteColor.c[i] = dblToCol(1.0);
    }

    colorMap->setMatteColor(&matteColor);

    const GfxColor *retrieved = colorMap->getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    for (int i = 0; i < gfxColorMaxComps; i++) {
        EXPECT_EQ(retrieved->c[i], matteColor.c[i]);
    }
}

// Test that setMatteColor copies the value (doesn't just store pointer)
TEST_F(GfxImageColorMapTest_539, SetMatteColorCopiesValue_539) {
    auto colorMap = createGrayColorMap();
    ASSERT_NE(colorMap, nullptr);

    GfxColor matteColor;
    for (int i = 0; i < gfxColorMaxComps; i++) {
        matteColor.c[i] = 0;
    }
    matteColor.c[0] = dblToCol(0.5);

    colorMap->setMatteColor(&matteColor);

    // Modify original color
    matteColor.c[0] = dblToCol(0.9);

    // Retrieved value should still be the original
    const GfxColor *retrieved = colorMap->getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], dblToCol(0.5));
}

// Test with 4-bit depth
TEST_F(GfxImageColorMapTest_539, FourBitDepth_539) {
    auto colorMap = createGrayColorMap(4);
    ASSERT_NE(colorMap, nullptr);
    EXPECT_TRUE(colorMap->isOk());
    EXPECT_EQ(colorMap->getBits(), 4);
}

// Test with 2-bit depth
TEST_F(GfxImageColorMapTest_539, TwoBitDepth_539) {
    auto colorMap = createGrayColorMap(2);
    ASSERT_NE(colorMap, nullptr);
    EXPECT_TRUE(colorMap->isOk());
    EXPECT_EQ(colorMap->getBits(), 2);
}

// Test getColor on a gray colormap
TEST_F(GfxImageColorMapTest_539, GetColorGray_539) {
    auto colorMap = createGrayColorMap(8);
    ASSERT_NE(colorMap, nullptr);

    unsigned char pixel = 128;
    GfxColor color;
    colorMap->getColor(&pixel, &color);
    // Should produce a mid-range value
    double val = colToDbl(color.c[0]);
    EXPECT_GT(val, 0.3);
    EXPECT_LT(val, 0.7);
}

// Test useRGBLine
TEST_F(GfxImageColorMapTest_539, UseRGBLineGray_539) {
    auto colorMap = createGrayColorMap(8);
    ASSERT_NE(colorMap, nullptr);
    // Just verify it returns a boolean without crashing
    bool result = colorMap->useRGBLine();
    (void)result; // may be true or false depending on implementation
}

// Test useRGBLine for RGB
TEST_F(GfxImageColorMapTest_539, UseRGBLineRGB_539) {
    auto colorMap = createRGBColorMap(8);
    ASSERT_NE(colorMap, nullptr);
    bool result = colorMap->useRGBLine();
    (void)result;
}

// Test useCMYKLine
TEST_F(GfxImageColorMapTest_539, UseCMYKLine_539) {
    auto colorMap = createCMYKColorMap(8);
    ASSERT_NE(colorMap, nullptr);
    bool result = colorMap->useCMYKLine();
    (void)result;
}

// Test getCMYK on CMYK colormap
TEST_F(GfxImageColorMapTest_539, GetCMYKFromCMYKColorMap_539) {
    auto colorMap = createCMYKColorMap(8);
    ASSERT_NE(colorMap, nullptr);

    unsigned char pixel[4] = {255, 0, 0, 0}; // full cyan
    GfxCMYK cmyk;
    colorMap->getCMYK(pixel, &cmyk);
    EXPECT_GE(colToDbl(cmyk.c), 0.99);
    EXPECT_LE(colToDbl(cmyk.m), 0.01);
    EXPECT_LE(colToDbl(cmyk.y), 0.01);
    EXPECT_LE(colToDbl(cmyk.k), 0.01);
}

// Test getDefaultDecodeRGB
TEST_F(GfxImageColorMapTest_539, DefaultDecodeRGB_539) {
    auto colorMap = createRGBColorMap(8);
    ASSERT_NE(colorMap, nullptr);
    // Default decode for RGB channels is [0, 1] each
    for (int i = 0; i < 3; i++) {
        EXPECT_DOUBLE_EQ(colorMap->getDecodeLow(i), 0.0);
        EXPECT_DOUBLE_EQ(colorMap->getDecodeHigh(i), 1.0);
    }
}
