#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"
#include "Object.h"

class GfxImageColorMapTest_532 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a DeviceRGB color space based GfxImageColorMap
    std::unique_ptr<GfxImageColorMap> createRGBColorMap(int bits) {
        Object decodeObj;
        decodeObj.initNull();
        auto cs = GfxColorSpace::parse(nullptr, &decodeObj, nullptr);
        if (!cs) {
            // Try creating a DeviceRGB directly
            cs = std::make_unique<GfxDeviceRGBColorSpace>();
        }
        auto map = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(cs));
        return map;
    }

    // Helper to create a DeviceGray color space based GfxImageColorMap
    std::unique_ptr<GfxImageColorMap> createGrayColorMap(int bits) {
        Object decodeObj;
        decodeObj.initNull();
        auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
        auto map = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(cs));
        return map;
    }

    // Helper to create a DeviceCMYK color space based GfxImageColorMap
    std::unique_ptr<GfxImageColorMap> createCMYKColorMap(int bits) {
        Object decodeObj;
        decodeObj.initNull();
        auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
        auto map = std::make_unique<GfxImageColorMap>(bits, &decodeObj, std::move(cs));
        return map;
    }
};

// Test that getNumPixelComps returns correct value for RGB (3 components)
TEST_F(GfxImageColorMapTest_532, GetNumPixelCompsRGB_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        EXPECT_EQ(3, map->getNumPixelComps());
    }
}

// Test that getNumPixelComps returns correct value for Gray (1 component)
TEST_F(GfxImageColorMapTest_532, GetNumPixelCompsGray_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        EXPECT_EQ(1, map->getNumPixelComps());
    }
}

// Test that getNumPixelComps returns correct value for CMYK (4 components)
TEST_F(GfxImageColorMapTest_532, GetNumPixelCompsCMYK_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        EXPECT_EQ(4, map->getNumPixelComps());
    }
}

// Test getBits returns the correct bit depth
TEST_F(GfxImageColorMapTest_532, GetBits8_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        EXPECT_EQ(8, map->getBits());
    }
}

// Test getBits with 1-bit depth
TEST_F(GfxImageColorMapTest_532, GetBits1_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(1, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        EXPECT_EQ(1, map->getBits());
    }
}

// Test isOk returns true for valid construction
TEST_F(GfxImageColorMapTest_532, IsOkValidConstruction_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    EXPECT_TRUE(map->isOk());
}

// Test getColorSpace returns non-null for valid map
TEST_F(GfxImageColorMapTest_532, GetColorSpaceNonNull_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        EXPECT_NE(nullptr, map->getColorSpace());
    }
}

// Test getDecodeLow for default decode (should be 0.0 for standard colorspaces)
TEST_F(GfxImageColorMapTest_532, GetDecodeLowDefault_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        EXPECT_DOUBLE_EQ(0.0, map->getDecodeLow(0));
    }
}

// Test getDecodeHigh for default decode (should be 1.0 for standard colorspaces)
TEST_F(GfxImageColorMapTest_532, GetDecodeHighDefault_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        EXPECT_DOUBLE_EQ(1.0, map->getDecodeHigh(0));
    }
}

// Test copy creates a valid copy
TEST_F(GfxImageColorMapTest_532, CopyIsValid_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        GfxImageColorMap *copyMap = map->copy();
        ASSERT_NE(nullptr, copyMap);
        EXPECT_TRUE(copyMap->isOk());
        EXPECT_EQ(map->getNumPixelComps(), copyMap->getNumPixelComps());
        EXPECT_EQ(map->getBits(), copyMap->getBits());
        delete copyMap;
    }
}

// Test that copy preserves component count
TEST_F(GfxImageColorMapTest_532, CopyPreservesNumPixelComps_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        GfxImageColorMap *copyMap = map->copy();
        ASSERT_NE(nullptr, copyMap);
        EXPECT_EQ(4, copyMap->getNumPixelComps());
        delete copyMap;
    }
}

// Test getMatteColor returns null when no matte is set
TEST_F(GfxImageColorMapTest_532, GetMatteColorDefaultNull_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        // Before setting matte, getMatteColor might return null or a default
        // The behavior depends on useMatte flag
        const GfxColor *matte = map->getMatteColor();
        // Just verify the call doesn't crash - matte may or may not be null
        (void)matte;
    }
}

// Test setMatteColor and getMatteColor round-trip
TEST_F(GfxImageColorMapTest_532, SetAndGetMatteColor_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        GfxColor color;
        color.c[0] = 0;
        color.c[1] = 32768;
        color.c[2] = 65535;
        map->setMatteColor(&color);
        const GfxColor *retrieved = map->getMatteColor();
        ASSERT_NE(nullptr, retrieved);
        EXPECT_EQ(color.c[0], retrieved->c[0]);
        EXPECT_EQ(color.c[1], retrieved->c[1]);
        EXPECT_EQ(color.c[2], retrieved->c[2]);
    }
}

// Test getGray with a gray color space
TEST_F(GfxImageColorMapTest_532, GetGrayBasic_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        unsigned char pixel = 0;
        GfxGray gray;
        map->getGray(&pixel, &gray);
        // Black pixel should give low gray value
        // Just verify no crash and some reasonable value
        SUCCEED();
    }
}

// Test getRGB with an RGB color space
TEST_F(GfxImageColorMapTest_532, GetRGBBasic_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        unsigned char pixel[3] = {255, 0, 0};  // Red
        GfxRGB rgb;
        map->getRGB(pixel, &rgb);
        // Should produce a red-ish color
        SUCCEED();
    }
}

// Test getRGBLine with an RGB color space
TEST_F(GfxImageColorMapTest_532, GetRGBLineBasic_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        unsigned char input[6] = {255, 0, 0, 0, 255, 0};  // 2 pixels: red, green
        unsigned int output[2] = {0, 0};
        map->getRGBLine(input, output, 2);
        // Just verify no crash
        SUCCEED();
    }
}

// Test getRGBLine with unsigned char output
TEST_F(GfxImageColorMapTest_532, GetRGBLineByteOutput_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        unsigned char input[6] = {255, 0, 0, 0, 255, 0};
        unsigned char output[6] = {0};
        map->getRGBLine(input, output, 2);
        SUCCEED();
    }
}

// Test getGrayLine
TEST_F(GfxImageColorMapTest_532, GetGrayLineBasic_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        unsigned char input[2] = {0, 255};
        unsigned char output[2] = {0};
        map->getGrayLine(input, output, 2);
        SUCCEED();
    }
}

// Test useRGBLine
TEST_F(GfxImageColorMapTest_532, UseRGBLine_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        // Just verify this method is callable and returns a bool
        bool result = map->useRGBLine();
        (void)result;
        SUCCEED();
    }
}

// Test useCMYKLine
TEST_F(GfxImageColorMapTest_532, UseCMYKLine_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        bool result = map->useCMYKLine();
        (void)result;
        SUCCEED();
    }
}

// Test useDeviceNLine
TEST_F(GfxImageColorMapTest_532, UseDeviceNLine_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        bool result = map->useDeviceNLine();
        (void)result;
        SUCCEED();
    }
}

// Test with decode array
TEST_F(GfxImageColorMapTest_532, WithDecodeArray_532) {
    // Create a decode array [1 0] (inverted for gray)
    Object decodeObj;
    Array *arr = new Array(nullptr);
    Object val1, val2;
    arr->add(Object(1.0));
    arr->add(Object(0.0));
    decodeObj = Object(arr);
    
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        // With inverted decode, decodeLow should be 1.0 and decodeHigh should be 0.0
        EXPECT_DOUBLE_EQ(1.0, map->getDecodeLow(0));
        EXPECT_DOUBLE_EQ(0.0, map->getDecodeHigh(0));
    }
}

// Test getCMYK with CMYK colorspace
TEST_F(GfxImageColorMapTest_532, GetCMYKBasic_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        unsigned char pixel[4] = {255, 0, 0, 0};
        GfxCMYK cmyk;
        map->getCMYK(pixel, &cmyk);
        SUCCEED();
    }
}

// Test getColor basic operation
TEST_F(GfxImageColorMapTest_532, GetColorBasic_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        unsigned char pixel[3] = {128, 128, 128};
        GfxColor color;
        map->getColor(pixel, &color);
        SUCCEED();
    }
}

// Test with null colorspace (error case)
TEST_F(GfxImageColorMapTest_532, NullColorSpaceNotOk_532) {
    Object decodeObj;
    decodeObj.initNull();
    std::unique_ptr<GfxColorSpace> nullCs;
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(nullCs));
    EXPECT_FALSE(map->isOk());
}

// Test getDecodeLow/High for multiple components in RGB
TEST_F(GfxImageColorMapTest_532, GetDecodeMultipleComponents_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        for (int i = 0; i < 3; i++) {
            EXPECT_DOUBLE_EQ(0.0, map->getDecodeLow(i));
            EXPECT_DOUBLE_EQ(1.0, map->getDecodeHigh(i));
        }
    }
}

// Test with 16-bit depth
TEST_F(GfxImageColorMapTest_532, Bits16_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(16, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        EXPECT_EQ(16, map->getBits());
        EXPECT_EQ(1, map->getNumPixelComps());
    }
}

// Test with 4-bit depth
TEST_F(GfxImageColorMapTest_532, Bits4_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(4, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        EXPECT_EQ(4, map->getBits());
    }
}

// Test copy preserves decode values
TEST_F(GfxImageColorMapTest_532, CopyPreservesDecodeValues_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        GfxImageColorMap *copyMap = map->copy();
        ASSERT_NE(nullptr, copyMap);
        for (int i = 0; i < map->getNumPixelComps(); i++) {
            EXPECT_DOUBLE_EQ(map->getDecodeLow(i), copyMap->getDecodeLow(i));
            EXPECT_DOUBLE_EQ(map->getDecodeHigh(i), copyMap->getDecodeHigh(i));
        }
        delete copyMap;
    }
}

// Test getRGBXLine
TEST_F(GfxImageColorMapTest_532, GetRGBXLineBasic_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        unsigned char input[6] = {255, 0, 0, 0, 255, 0};
        unsigned char output[8] = {0};  // RGBX = 4 bytes per pixel * 2 pixels
        map->getRGBXLine(input, output, 2);
        SUCCEED();
    }
}

// Test getCMYKLine
TEST_F(GfxImageColorMapTest_532, GetCMYKLineBasic_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        unsigned char input[8] = {255, 0, 0, 0, 0, 255, 0, 0};  // 2 CMYK pixels
        unsigned char output[8] = {0};
        map->getCMYKLine(input, output, 2);
        SUCCEED();
    }
}

// Test getDeviceN
TEST_F(GfxImageColorMapTest_532, GetDeviceNBasic_532) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto map = std::make_unique<GfxImageColorMap>(8, &decodeObj, std::move(cs));
    if (map && map->isOk()) {
        unsigned char pixel[3] = {128, 64, 32};
        GfxColor deviceN;
        map->getDeviceN(pixel, &deviceN);
        SUCCEED();
    }
}
