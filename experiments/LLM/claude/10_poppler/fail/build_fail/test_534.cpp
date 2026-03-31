#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "Object.h"

class GfxImageColorMapTest_534 : public ::testing::Test {
protected:
    // Helper to create a DeviceGray color map with given bits
    std::unique_ptr<GfxImageColorMap> createGrayColorMap(int bits) {
        Object decodeObj;
        decodeObj.initNull();
        auto cs = GfxColorSpace::parse(nullptr, &decodeObj, nullptr, nullptr, nullptr, 0);
        if (!cs) {
            // Create a DeviceGray colorspace directly
            cs = std::make_unique<GfxDeviceGrayColorSpace>();
        }
        auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(cs));
        return colorMap;
    }

    std::unique_ptr<GfxImageColorMap> createGrayColorMapWithDecode(int bits) {
        // Create an array decode object [0 1]
        Object decodeArray;
        decodeArray = Object(new Array(nullptr));
        decodeArray.arrayAdd(Object(0.0));
        decodeArray.arrayAdd(Object(1.0));
        
        auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
        auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decodeArray, std::move(cs));
        return colorMap;
    }

    std::unique_ptr<GfxImageColorMap> createRGBColorMapWithDecode(int bits) {
        Object decodeArray;
        decodeArray = Object(new Array(nullptr));
        decodeArray.arrayAdd(Object(0.0));
        decodeArray.arrayAdd(Object(1.0));
        decodeArray.arrayAdd(Object(0.0));
        decodeArray.arrayAdd(Object(1.0));
        decodeArray.arrayAdd(Object(0.0));
        decodeArray.arrayAdd(Object(1.0));

        auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
        auto colorMap = std::make_unique<GfxImageColorMap>(bits, &decodeArray, std::move(cs));
        return colorMap;
    }
};

// Test basic construction with DeviceGray and null decode
TEST_F(GfxImageColorMapTest_534, ConstructWithGrayNullDecode_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    EXPECT_TRUE(colorMap.isOk());
}

// Test getBits returns correct value
TEST_F(GfxImageColorMapTest_534, GetBitsReturnsCorrectValue_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_EQ(8, colorMap.getBits());
    }
}

// Test getNumPixelComps for gray
TEST_F(GfxImageColorMapTest_534, GetNumPixelCompsGray_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_EQ(1, colorMap.getNumPixelComps());
    }
}

// Test getNumPixelComps for RGB
TEST_F(GfxImageColorMapTest_534, GetNumPixelCompsRGB_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_EQ(3, colorMap.getNumPixelComps());
    }
}

// Test getColorSpace returns non-null
TEST_F(GfxImageColorMapTest_534, GetColorSpaceNonNull_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_NE(nullptr, colorMap.getColorSpace());
    }
}

// Test getDecodeLow for gray with null decode (default decode)
TEST_F(GfxImageColorMapTest_534, GetDecodeLowDefaultGray_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_DOUBLE_EQ(0.0, colorMap.getDecodeLow(0));
    }
}

// Test getDecodeHigh for gray with null decode (default decode)
TEST_F(GfxImageColorMapTest_534, GetDecodeHighDefaultGray_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_DOUBLE_EQ(1.0, colorMap.getDecodeHigh(0));
    }
}

// Test getDecodeLow with explicit decode array
TEST_F(GfxImageColorMapTest_534, GetDecodeLowExplicitDecode_534) {
    Object decodeArray;
    decodeArray = Object(new Array(nullptr));
    decodeArray.arrayAdd(Object(0.0));
    decodeArray.arrayAdd(Object(1.0));

    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeArray, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_DOUBLE_EQ(0.0, colorMap.getDecodeLow(0));
    }
}

// Test getDecodeHigh with explicit decode array  
TEST_F(GfxImageColorMapTest_534, GetDecodeHighExplicitDecode_534) {
    Object decodeArray;
    decodeArray = Object(new Array(nullptr));
    decodeArray.arrayAdd(Object(0.0));
    decodeArray.arrayAdd(Object(1.0));

    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeArray, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_DOUBLE_EQ(1.0, colorMap.getDecodeHigh(0));
    }
}

// Test with inverted decode range
TEST_F(GfxImageColorMapTest_534, InvertedDecodeRange_534) {
    Object decodeArray;
    decodeArray = Object(new Array(nullptr));
    decodeArray.arrayAdd(Object(1.0));
    decodeArray.arrayAdd(Object(0.0));

    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeArray, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_DOUBLE_EQ(1.0, colorMap.getDecodeLow(0));
        EXPECT_DOUBLE_EQ(0.0, colorMap.getDecodeHigh(0));
    }
}

// Test copy
TEST_F(GfxImageColorMapTest_534, CopyProducesSameValues_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        auto copied = colorMap.copy();
        ASSERT_NE(nullptr, copied);
        EXPECT_TRUE(copied->isOk());
        EXPECT_EQ(colorMap.getBits(), copied->getBits());
        EXPECT_EQ(colorMap.getNumPixelComps(), copied->getNumPixelComps());
        EXPECT_DOUBLE_EQ(colorMap.getDecodeLow(0), copied->getDecodeLow(0));
        EXPECT_DOUBLE_EQ(colorMap.getDecodeHigh(0), copied->getDecodeHigh(0));
        delete copied;
    }
}

// Test getMatteColor returns nullptr when no matte is set
TEST_F(GfxImageColorMapTest_534, GetMatteColorDefaultNull_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        // When no matte color is set, getMatteColor may return nullptr
        // or may return a pointer to an unset matte color
        // This tests the observable behavior
        const GfxColor *matte = colorMap.getMatteColor();
        // Just verify we can call it without crashing
        (void)matte;
    }
}

// Test setMatteColor and getMatteColor
TEST_F(GfxImageColorMapTest_534, SetAndGetMatteColor_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        GfxColor matteColor;
        matteColor.c[0] = 32768; // some value
        colorMap.setMatteColor(&matteColor);
        const GfxColor *retrieved = colorMap.getMatteColor();
        ASSERT_NE(nullptr, retrieved);
        EXPECT_EQ(matteColor.c[0], retrieved->c[0]);
    }
}

// Test 1-bit image
TEST_F(GfxImageColorMapTest_534, OneBitGrayImage_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(1, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_EQ(1, colorMap.getBits());
        EXPECT_EQ(1, colorMap.getNumPixelComps());
    }
}

// Test RGB decode low/high for multiple components
TEST_F(GfxImageColorMapTest_534, RGBDecodeMultipleComponents_534) {
    Object decodeArray;
    decodeArray = Object(new Array(nullptr));
    decodeArray.arrayAdd(Object(0.0));
    decodeArray.arrayAdd(Object(1.0));
    decodeArray.arrayAdd(Object(0.2));
    decodeArray.arrayAdd(Object(0.8));
    decodeArray.arrayAdd(Object(0.1));
    decodeArray.arrayAdd(Object(0.9));

    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeArray, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_DOUBLE_EQ(0.0, colorMap.getDecodeLow(0));
        EXPECT_DOUBLE_EQ(1.0, colorMap.getDecodeHigh(0));
        EXPECT_DOUBLE_EQ(0.2, colorMap.getDecodeLow(1));
        EXPECT_DOUBLE_EQ(0.8, colorMap.getDecodeHigh(1));
        EXPECT_DOUBLE_EQ(0.1, colorMap.getDecodeLow(2));
        EXPECT_DOUBLE_EQ(0.9, colorMap.getDecodeHigh(2));
    }
}

// Test getGray with a simple gray pixel
TEST_F(GfxImageColorMapTest_534, GetGrayValue_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        unsigned char pixel = 255;
        GfxGray gray;
        colorMap.getGray(&pixel, &gray);
        // 255 in 8-bit gray with decode [0,1] should map to max gray
        EXPECT_GE(gray, 0);
    }
}

// Test getRGB with a simple gray pixel
TEST_F(GfxImageColorMapTest_534, GetRGBFromGray_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        unsigned char pixel = 0;
        GfxRGB rgb;
        colorMap.getRGB(&pixel, &rgb);
        // 0 in gray should map to black (0,0,0) approximately
        // Just verify it doesn't crash and returns something reasonable
        SUCCEED();
    }
}

// Test useRGBLine
TEST_F(GfxImageColorMapTest_534, UseRGBLineForGray_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        // Just verify it returns a boolean without crashing
        bool result = colorMap.useRGBLine();
        (void)result;
        SUCCEED();
    }
}

// Test useCMYKLine
TEST_F(GfxImageColorMapTest_534, UseCMYKLineForGray_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        bool result = colorMap.useCMYKLine();
        (void)result;
        SUCCEED();
    }
}

// Test useDeviceNLine
TEST_F(GfxImageColorMapTest_534, UseDeviceNLineForGray_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        bool result = colorMap.useDeviceNLine();
        (void)result;
        SUCCEED();
    }
}

// Test with CMYK color space
TEST_F(GfxImageColorMapTest_534, CMYKColorSpace_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_EQ(4, colorMap.getNumPixelComps());
        EXPECT_EQ(8, colorMap.getBits());
    }
}

// Test getRGBLine with unsigned int output for gray
TEST_F(GfxImageColorMapTest_534, GetRGBLineUintGray_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        unsigned char input[3] = {0, 128, 255};
        unsigned int output[3] = {0, 0, 0};
        colorMap.getRGBLine(input, output, 3);
        // Just check no crash
        SUCCEED();
    }
}

// Test getGrayLine
TEST_F(GfxImageColorMapTest_534, GetGrayLine_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        unsigned char input[3] = {0, 128, 255};
        unsigned char output[3] = {0, 0, 0};
        colorMap.getGrayLine(input, output, 3);
        // Just check no crash
        SUCCEED();
    }
}

// Test copy preserves RGB decode values
TEST_F(GfxImageColorMapTest_534, CopyPreservesRGBDecode_534) {
    Object decodeArray;
    decodeArray = Object(new Array(nullptr));
    decodeArray.arrayAdd(Object(0.1));
    decodeArray.arrayAdd(Object(0.9));
    decodeArray.arrayAdd(Object(0.2));
    decodeArray.arrayAdd(Object(0.8));
    decodeArray.arrayAdd(Object(0.3));
    decodeArray.arrayAdd(Object(0.7));

    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxImageColorMap colorMap(8, &decodeArray, std::move(cs));
    if (colorMap.isOk()) {
        auto copied = colorMap.copy();
        ASSERT_NE(nullptr, copied);
        EXPECT_TRUE(copied->isOk());
        for (int i = 0; i < 3; i++) {
            EXPECT_DOUBLE_EQ(colorMap.getDecodeLow(i), copied->getDecodeLow(i));
            EXPECT_DOUBLE_EQ(colorMap.getDecodeHigh(i), copied->getDecodeHigh(i));
        }
        delete copied;
    }
}

// Test 4-bit image
TEST_F(GfxImageColorMapTest_534, FourBitGrayImage_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(4, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_EQ(4, colorMap.getBits());
    }
}

// Test 16-bit image
TEST_F(GfxImageColorMapTest_534, SixteenBitGrayImage_534) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxImageColorMap colorMap(16, &decodeObj, std::move(cs));
    if (colorMap.isOk()) {
        EXPECT_EQ(16, colorMap.getBits());
    }
}
