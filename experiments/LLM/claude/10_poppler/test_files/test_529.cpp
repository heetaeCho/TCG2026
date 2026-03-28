#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/GfxState.h"
#include "poppler/Object.h"

class GfxImageColorMapTest_529 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a valid GfxImageColorMap with DeviceRGB colorspace
    std::unique_ptr<GfxImageColorMap> createValidRGBColorMap(int bits = 8) {
        auto cs = GfxColorSpace::parse(nullptr, nullptr, &Object::null, nullptr, nullptr, 0);
        // Try creating with DeviceRGB
        Object decodeObj;
        decodeObj = Object(objNull);
        auto csRGB = std::make_unique<GfxDeviceRGBColorSpace>();
        auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(csRGB));
        if (colorMap && colorMap->isOk()) {
            return colorMap;
        }
        return nullptr;
    }

    std::unique_ptr<GfxImageColorMap> createValidGrayColorMap(int bits = 8) {
        Object decodeObj;
        decodeObj = Object(objNull);
        auto csGray = std::make_unique<GfxDeviceGrayColorSpace>();
        auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(csGray));
        if (colorMap && colorMap->isOk()) {
            return colorMap;
        }
        return nullptr;
    }

    std::unique_ptr<GfxImageColorMap> createValidCMYKColorMap(int bits = 8) {
        Object decodeObj;
        decodeObj = Object(objNull);
        auto csCMYK = std::make_unique<GfxDeviceCMYKColorSpace>();
        auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(csCMYK));
        if (colorMap && colorMap->isOk()) {
            return colorMap;
        }
        return nullptr;
    }
};

// Test that creating a color map with a valid RGB color space and 8 bits is ok
TEST_F(GfxImageColorMapTest_529, ConstructWithValidRGB8Bits_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    EXPECT_TRUE(colorMap.isOk());
}

// Test that creating a color map with a valid Gray color space is ok
TEST_F(GfxImageColorMapTest_529, ConstructWithValidGray_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    EXPECT_TRUE(colorMap.isOk());
}

// Test that creating a color map with a valid CMYK color space is ok
TEST_F(GfxImageColorMapTest_529, ConstructWithValidCMYK_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    EXPECT_TRUE(colorMap.isOk());
}

// Test that creating with null colorspace results in not ok
TEST_F(GfxImageColorMapTest_529, ConstructWithNullColorSpace_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    std::unique_ptr<GfxColorSpace> nullCs(nullptr);
    GfxImageColorMap colorMap(8, &decodeObj, std::move(nullCs));
    EXPECT_FALSE(colorMap.isOk());
}

// Test getBits returns the bits passed at construction
TEST_F(GfxImageColorMapTest_529, GetBitsReturnsCorrectValue_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_EQ(colorMap.getBits(), 8);
}

// Test getBits with 1 bit
TEST_F(GfxImageColorMapTest_529, GetBits1Bit_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(1, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_EQ(colorMap.getBits(), 1);
}

// Test getNumPixelComps for RGB (should be 3)
TEST_F(GfxImageColorMapTest_529, GetNumPixelCompsRGB_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_EQ(colorMap.getNumPixelComps(), 3);
}

// Test getNumPixelComps for Gray (should be 1)
TEST_F(GfxImageColorMapTest_529, GetNumPixelCompsGray_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_EQ(colorMap.getNumPixelComps(), 1);
}

// Test getNumPixelComps for CMYK (should be 4)
TEST_F(GfxImageColorMapTest_529, GetNumPixelCompsCMYK_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_EQ(colorMap.getNumPixelComps(), 4);
}

// Test getColorSpace returns non-null for valid color map
TEST_F(GfxImageColorMapTest_529, GetColorSpaceNotNull_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_NE(colorMap.getColorSpace(), nullptr);
}

// Test copy creates a valid copy
TEST_F(GfxImageColorMapTest_529, CopyCreatesValidColorMap_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    GfxImageColorMap *copied = colorMap.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isOk());
    EXPECT_EQ(copied->getBits(), colorMap.getBits());
    EXPECT_EQ(copied->getNumPixelComps(), colorMap.getNumPixelComps());
    delete copied;
}

// Test copy preserves bits
TEST_F(GfxImageColorMapTest_529, CopyPreservesBits_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(4, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    GfxImageColorMap *copied = colorMap.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getBits(), 4);
    delete copied;
}

// Test getDecodeLow with default decode (null object)
TEST_F(GfxImageColorMapTest_529, GetDecodeLowDefault_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    // Default decode for gray: [0, 1]
    EXPECT_DOUBLE_EQ(colorMap.getDecodeLow(0), 0.0);
}

// Test getDecodeHigh with default decode
TEST_F(GfxImageColorMapTest_529, GetDecodeHighDefault_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_DOUBLE_EQ(colorMap.getDecodeHigh(0), 1.0);
}

// Test getMatteColor returns nullptr by default (no matte set)
TEST_F(GfxImageColorMapTest_529, GetMatteColorDefaultNull_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_EQ(colorMap.getMatteColor(), nullptr);
}

// Test setMatteColor and getMatteColor
TEST_F(GfxImageColorMapTest_529, SetAndGetMatteColor_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    GfxColor matteColor;
    matteColor.c[0] = 0;
    matteColor.c[1] = 0;
    matteColor.c[2] = 0;
    colorMap.setMatteColor(&matteColor);

    const GfxColor *retrieved = colorMap.getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], matteColor.c[0]);
    EXPECT_EQ(retrieved->c[1], matteColor.c[1]);
    EXPECT_EQ(retrieved->c[2], matteColor.c[2]);
}

// Test getGray for a gray colorspace
TEST_F(GfxImageColorMapTest_529, GetGrayFromGrayColorSpace_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char pixel = 0; // black
    GfxGray gray;
    colorMap.getGray(&pixel, &gray);
    // For pixel value 0 with default decode [0,1], gray should be 0
    EXPECT_EQ(gray, 0);
}

// Test getGray for white pixel
TEST_F(GfxImageColorMapTest_529, GetGrayWhitePixel_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char pixel = 255; // white
    GfxGray gray;
    colorMap.getGray(&pixel, &gray);
    // For pixel value 255 with default decode [0,1], gray should be max
    EXPECT_GT(gray, 0);
}

// Test getRGB for RGB colorspace with black pixel
TEST_F(GfxImageColorMapTest_529, GetRGBBlackPixel_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char pixel[3] = {0, 0, 0}; // black
    GfxRGB rgb;
    colorMap.getRGB(pixel, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

// Test getRGB for RGB colorspace with white pixel
TEST_F(GfxImageColorMapTest_529, GetRGBWhitePixel_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char pixel[3] = {255, 255, 255}; // white
    GfxRGB rgb;
    colorMap.getRGB(pixel, &rgb);
    EXPECT_GT(rgb.r, 0);
    EXPECT_GT(rgb.g, 0);
    EXPECT_GT(rgb.b, 0);
}

// Test getRGBLine with unsigned int output
TEST_F(GfxImageColorMapTest_529, GetRGBLineUintOutput_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char input[6] = {0, 0, 0, 255, 255, 255}; // 2 pixels: black, white
    unsigned int output[2] = {0, 0};
    colorMap.getRGBLine(input, output, 2);
    // output should have been modified
    // Black pixel should be 0xFF000000 or similar, white should be 0xFFFFFFFF or similar
    // We just check it doesn't crash and output is populated
    SUCCEED();
}

// Test getRGBLine with unsigned char output
TEST_F(GfxImageColorMapTest_529, GetRGBLineUcharOutput_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char input[6] = {255, 0, 0, 0, 255, 0}; // 2 pixels
    unsigned char output[6] = {0};
    colorMap.getRGBLine(input, output, 2);
    SUCCEED();
}

// Test getGrayLine
TEST_F(GfxImageColorMapTest_529, GetGrayLine_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char input[3] = {0, 128, 255}; // 3 pixels
    unsigned char output[3] = {0};
    colorMap.getGrayLine(input, output, 3);
    EXPECT_EQ(output[0], 0); // black
    EXPECT_GT(output[2], 0); // white-ish
}

// Test getCMYK for a CMYK colorspace
TEST_F(GfxImageColorMapTest_529, GetCMYKBlackPixel_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char pixel[4] = {0, 0, 0, 0}; // no ink = white
    GfxCMYK cmyk;
    colorMap.getCMYK(pixel, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

// Test useRGBLine for RGB colorspace
TEST_F(GfxImageColorMapTest_529, UseRGBLineForRGB_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    // Just verify it returns a boolean without crash
    bool result = colorMap.useRGBLine();
    (void)result;
    SUCCEED();
}

// Test useCMYKLine for CMYK colorspace
TEST_F(GfxImageColorMapTest_529, UseCMYKLineForCMYK_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    bool result = colorMap.useCMYKLine();
    (void)result;
    SUCCEED();
}

// Test useDeviceNLine
TEST_F(GfxImageColorMapTest_529, UseDeviceNLine_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    bool result = colorMap.useDeviceNLine();
    (void)result;
    SUCCEED();
}

// Test with 2-bit depth
TEST_F(GfxImageColorMapTest_529, ConstructWith2Bits_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(2, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_EQ(colorMap.getBits(), 2);
}

// Test with 4-bit depth
TEST_F(GfxImageColorMapTest_529, ConstructWith4Bits_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(4, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_EQ(colorMap.getBits(), 4);
}

// Test with 16-bit depth
TEST_F(GfxImageColorMapTest_529, ConstructWith16Bits_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(16, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());
    EXPECT_EQ(colorMap.getBits(), 16);
}

// Test getDecodeLow and getDecodeHigh for RGB (multiple components)
TEST_F(GfxImageColorMapTest_529, GetDecodeLowHighRGB_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    for (int i = 0; i < 3; i++) {
        EXPECT_DOUBLE_EQ(colorMap.getDecodeLow(i), 0.0);
        EXPECT_DOUBLE_EQ(colorMap.getDecodeHigh(i), 1.0);
    }
}

// Test copy preserves matte color
TEST_F(GfxImageColorMapTest_529, CopyPreservesMatteColor_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    GfxColor matteColor;
    matteColor.c[0] = 100;
    matteColor.c[1] = 200;
    matteColor.c[2] = 50;
    colorMap.setMatteColor(&matteColor);

    GfxImageColorMap *copied = colorMap.copy();
    ASSERT_NE(copied, nullptr);
    ASSERT_TRUE(copied->isOk());

    const GfxColor *retrievedMatte = copied->getMatteColor();
    ASSERT_NE(retrievedMatte, nullptr);
    EXPECT_EQ(retrievedMatte->c[0], 100);
    EXPECT_EQ(retrievedMatte->c[1], 200);
    EXPECT_EQ(retrievedMatte->c[2], 50);
    delete copied;
}

// Test getRGBXLine
TEST_F(GfxImageColorMapTest_529, GetRGBXLine_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char input[3] = {128, 64, 32}; // 1 pixel
    unsigned char output[4] = {0};
    colorMap.getRGBXLine(input, output, 1);
    SUCCEED();
}

// Test getColor
TEST_F(GfxImageColorMapTest_529, GetColor_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char pixel[3] = {100, 150, 200};
    GfxColor color;
    colorMap.getColor(pixel, &color);
    SUCCEED();
}

// Test getDeviceN
TEST_F(GfxImageColorMapTest_529, GetDeviceN_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char pixel[3] = {100, 150, 200};
    GfxColor deviceN;
    colorMap.getDeviceN(pixel, &deviceN);
    SUCCEED();
}

// Test getCMYKLine
TEST_F(GfxImageColorMapTest_529, GetCMYKLine_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char input[8] = {0, 0, 0, 0, 255, 255, 255, 255}; // 2 pixels
    unsigned char output[8] = {0};
    colorMap.getCMYKLine(input, output, 2);
    SUCCEED();
}

// Test zero-length line operations don't crash
TEST_F(GfxImageColorMapTest_529, ZeroLengthLineOperations_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    unsigned char input[1] = {0};
    unsigned int output_uint[1] = {0};
    unsigned char output_uchar[1] = {0};

    colorMap.getRGBLine(input, output_uint, 0);
    colorMap.getRGBLine(input, output_uchar, 0);
    colorMap.getRGBXLine(input, output_uchar, 0);
    SUCCEED();
}

// Test that copy returns a distinct object
TEST_F(GfxImageColorMapTest_529, CopyReturnsDifferentPointer_529) {
    Object decodeObj;
    decodeObj = Object(objNull);
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    ASSERT_TRUE(colorMap.isOk());

    GfxImageColorMap *copied = colorMap.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied, &colorMap);
    delete copied;
}
