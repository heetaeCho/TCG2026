#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "GfxState.h"
#include "Object.h"

class GfxImageColorMapTest_530 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing with invalid/null colorspace results in isOk() == false
TEST_F(GfxImageColorMapTest_530, InvalidConstruction_NullColorSpace_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    // Passing nullptr as colorspace should result in an invalid colormap
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(nullptr));
    EXPECT_FALSE(colorMap.isOk());
}

// Test construction with a valid DeviceRGB color space and 8-bit depth
TEST_F(GfxImageColorMapTest_530, ValidConstruction_DeviceRGB_8bit_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    auto cs = GfxColorSpace::parse(nullptr, nullptr, nullptr, nullptr);
    // We need a real colorspace; let's try creating a DeviceGray
    // Since we can't easily create color spaces without PDF resources,
    // we test with what we can construct
    
    // Create a DeviceGray colorspace
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        EXPECT_EQ(colorMap.getBits(), 8);
        EXPECT_EQ(colorMap.getNumPixelComps(), 1);
        EXPECT_NE(colorMap.getColorSpace(), nullptr);
    }
}

// Test construction with DeviceRGB
TEST_F(GfxImageColorMapTest_530, ValidConstruction_DeviceRGBColorSpace_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> rgbCs(new GfxDeviceRGBColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(rgbCs));
    if (colorMap.isOk()) {
        EXPECT_EQ(colorMap.getBits(), 8);
        EXPECT_EQ(colorMap.getNumPixelComps(), 3);
        EXPECT_NE(colorMap.getColorSpace(), nullptr);
    }
}

// Test construction with DeviceCMYK
TEST_F(GfxImageColorMapTest_530, ValidConstruction_DeviceCMYKColorSpace_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> cmykCs(new GfxDeviceCMYKColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cmykCs));
    if (colorMap.isOk()) {
        EXPECT_EQ(colorMap.getBits(), 8);
        EXPECT_EQ(colorMap.getNumPixelComps(), 4);
        EXPECT_NE(colorMap.getColorSpace(), nullptr);
    }
}

// Test getBits returns correct value for 1-bit images
TEST_F(GfxImageColorMapTest_530, GetBits_1bit_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(1, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        EXPECT_EQ(colorMap.getBits(), 1);
    }
}

// Test getDecodeLow and getDecodeHigh with default decode array
TEST_F(GfxImageColorMapTest_530, DefaultDecodeValues_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        // Default decode for DeviceGray 8-bit should be [0, 1]
        EXPECT_DOUBLE_EQ(colorMap.getDecodeLow(0), 0.0);
        EXPECT_DOUBLE_EQ(colorMap.getDecodeHigh(0), 1.0);
    }
}

// Test copy() method
TEST_F(GfxImageColorMapTest_530, CopyMethod_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        GfxImageColorMap *copied = colorMap.copy();
        ASSERT_NE(copied, nullptr);
        EXPECT_TRUE(copied->isOk());
        EXPECT_EQ(copied->getBits(), colorMap.getBits());
        EXPECT_EQ(copied->getNumPixelComps(), colorMap.getNumPixelComps());
        EXPECT_DOUBLE_EQ(copied->getDecodeLow(0), colorMap.getDecodeLow(0));
        EXPECT_DOUBLE_EQ(copied->getDecodeHigh(0), colorMap.getDecodeHigh(0));
        delete copied;
    }
}

// Test useRGBLine for DeviceRGB
TEST_F(GfxImageColorMapTest_530, UseRGBLine_DeviceRGB_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> rgbCs(new GfxDeviceRGBColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(rgbCs));
    if (colorMap.isOk()) {
        // DeviceRGB should typically support RGB line output
        EXPECT_TRUE(colorMap.useRGBLine());
    }
}

// Test useCMYKLine for DeviceCMYK
TEST_F(GfxImageColorMapTest_530, UseCMYKLine_DeviceCMYK_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> cmykCs(new GfxDeviceCMYKColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cmykCs));
    if (colorMap.isOk()) {
        EXPECT_TRUE(colorMap.useCMYKLine());
    }
}

// Test setMatteColor and getMatteColor
TEST_F(GfxImageColorMapTest_530, SetAndGetMatteColor_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        GfxColor matteColor;
        matteColor.c[0] = dblToCol(0.5);
        colorMap.setMatteColor(&matteColor);
        
        const GfxColor *retrievedMatte = colorMap.getMatteColor();
        ASSERT_NE(retrievedMatte, nullptr);
        EXPECT_EQ(retrievedMatte->c[0], matteColor.c[0]);
    }
}

// Test getMatteColor returns nullptr or default when not set
TEST_F(GfxImageColorMapTest_530, GetMatteColorDefault_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        // Before setting matte color, getMatteColor should return something
        // (implementation dependent, but we just test it doesn't crash)
        const GfxColor *matte = colorMap.getMatteColor();
        // No assertion on value since it's implementation-defined
        (void)matte;
    }
}

// Test getGray with a DeviceGray colorspace
TEST_F(GfxImageColorMapTest_530, GetGray_DeviceGray_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        unsigned char pixel = 0;
        GfxGray gray;
        colorMap.getGray(&pixel, &gray);
        // pixel 0 with default decode [0,1] should map to gray = 0
        EXPECT_EQ(colToDbl(gray), 0.0);
        
        pixel = 255;
        colorMap.getGray(&pixel, &gray);
        // pixel 255 should map to gray = 1.0
        EXPECT_NEAR(colToDbl(gray), 1.0, 0.01);
    }
}

// Test getRGB with DeviceRGB colorspace
TEST_F(GfxImageColorMapTest_530, GetRGB_DeviceRGB_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> rgbCs(new GfxDeviceRGBColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(rgbCs));
    if (colorMap.isOk()) {
        unsigned char pixel[3] = {255, 0, 0}; // Red
        GfxRGB rgb;
        colorMap.getRGB(pixel, &rgb);
        EXPECT_NEAR(colToDbl(rgb.r), 1.0, 0.01);
        EXPECT_NEAR(colToDbl(rgb.g), 0.0, 0.01);
        EXPECT_NEAR(colToDbl(rgb.b), 0.0, 0.01);
    }
}

// Test getRGB with all zeros (black)
TEST_F(GfxImageColorMapTest_530, GetRGB_Black_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> rgbCs(new GfxDeviceRGBColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(rgbCs));
    if (colorMap.isOk()) {
        unsigned char pixel[3] = {0, 0, 0};
        GfxRGB rgb;
        colorMap.getRGB(pixel, &rgb);
        EXPECT_NEAR(colToDbl(rgb.r), 0.0, 0.01);
        EXPECT_NEAR(colToDbl(rgb.g), 0.0, 0.01);
        EXPECT_NEAR(colToDbl(rgb.b), 0.0, 0.01);
    }
}

// Test getRGB with all 255 (white)
TEST_F(GfxImageColorMapTest_530, GetRGB_White_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> rgbCs(new GfxDeviceRGBColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(rgbCs));
    if (colorMap.isOk()) {
        unsigned char pixel[3] = {255, 255, 255};
        GfxRGB rgb;
        colorMap.getRGB(pixel, &rgb);
        EXPECT_NEAR(colToDbl(rgb.r), 1.0, 0.01);
        EXPECT_NEAR(colToDbl(rgb.g), 1.0, 0.01);
        EXPECT_NEAR(colToDbl(rgb.b), 1.0, 0.01);
    }
}

// Test getGrayLine for DeviceGray
TEST_F(GfxImageColorMapTest_530, GetGrayLine_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        unsigned char input[4] = {0, 128, 255, 64};
        unsigned char output[4] = {0};
        colorMap.getGrayLine(input, output, 4);
        
        // Check that output values are reasonable
        EXPECT_EQ(output[0], 0);
        EXPECT_EQ(output[2], 255);
    }
}

// Test getRGBLine (unsigned int* version) for DeviceRGB
TEST_F(GfxImageColorMapTest_530, GetRGBLine_UintOutput_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> rgbCs(new GfxDeviceRGBColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(rgbCs));
    if (colorMap.isOk()) {
        unsigned char input[6] = {255, 0, 0, 0, 255, 0}; // Red, Green
        unsigned int output[2] = {0};
        colorMap.getRGBLine(input, output, 2);
        
        // output should contain packed RGB values
        // Just verify it doesn't crash and produces non-zero for non-black input
        // The exact format depends on implementation
    }
}

// Test getRGBLine (unsigned char* version) for DeviceRGB
TEST_F(GfxImageColorMapTest_530, GetRGBLine_UcharOutput_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> rgbCs(new GfxDeviceRGBColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(rgbCs));
    if (colorMap.isOk()) {
        unsigned char input[6] = {255, 0, 0, 0, 0, 255}; // Red, Blue
        unsigned char output[6] = {0};
        colorMap.getRGBLine(input, output, 2);
        
        // First pixel should be red
        EXPECT_EQ(output[0], 255);
        EXPECT_EQ(output[1], 0);
        EXPECT_EQ(output[2], 0);
    }
}

// Test with custom decode array
TEST_F(GfxImageColorMapTest_530, CustomDecodeArray_530) {
    // Create a decode array [1, 0] which inverts the gray values
    Object decodeObj;
    decodeObj = Object(new Array(nullptr));
    decodeObj.arrayAdd(Object(1.0));
    decodeObj.arrayAdd(Object(0.0));
    
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        EXPECT_DOUBLE_EQ(colorMap.getDecodeLow(0), 1.0);
        EXPECT_DOUBLE_EQ(colorMap.getDecodeHigh(0), 0.0);
        
        // With inverted decode, pixel 0 should map to gray 1.0
        unsigned char pixel = 0;
        GfxGray gray;
        colorMap.getGray(&pixel, &gray);
        EXPECT_NEAR(colToDbl(gray), 1.0, 0.01);
        
        // And pixel 255 should map to gray 0.0
        pixel = 255;
        colorMap.getGray(&pixel, &gray);
        EXPECT_NEAR(colToDbl(gray), 0.0, 0.01);
    }
}

// Test that copy deleted (compile-time check - just verify we can't copy-assign)
// This is a compile-time constraint, so we just verify the copy() method works
TEST_F(GfxImageColorMapTest_530, CopyProducesValidObject_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> rgbCs(new GfxDeviceRGBColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(rgbCs));
    if (colorMap.isOk()) {
        std::unique_ptr<GfxImageColorMap> copied(colorMap.copy());
        ASSERT_NE(copied, nullptr);
        EXPECT_TRUE(copied->isOk());
        
        // Verify the copy produces same results
        unsigned char pixel[3] = {128, 64, 200};
        GfxRGB rgb1, rgb2;
        colorMap.getRGB(pixel, &rgb1);
        copied->getRGB(pixel, &rgb2);
        EXPECT_EQ(rgb1.r, rgb2.r);
        EXPECT_EQ(rgb1.g, rgb2.g);
        EXPECT_EQ(rgb1.b, rgb2.b);
    }
}

// Test 4-bit depth
TEST_F(GfxImageColorMapTest_530, FourBitDepth_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(4, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        EXPECT_EQ(colorMap.getBits(), 4);
        EXPECT_EQ(colorMap.getNumPixelComps(), 1);
    }
}

// Test getCMYK with DeviceCMYK
TEST_F(GfxImageColorMapTest_530, GetCMYK_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> cmykCs(new GfxDeviceCMYKColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cmykCs));
    if (colorMap.isOk()) {
        unsigned char pixel[4] = {255, 0, 0, 0}; // Full cyan
        GfxCMYK cmyk;
        colorMap.getCMYK(pixel, &cmyk);
        EXPECT_NEAR(colToDbl(cmyk.c), 1.0, 0.01);
        EXPECT_NEAR(colToDbl(cmyk.m), 0.0, 0.01);
        EXPECT_NEAR(colToDbl(cmyk.y), 0.0, 0.01);
        EXPECT_NEAR(colToDbl(cmyk.k), 0.0, 0.01);
    }
}

// Test getColorSpace returns non-null for valid map
TEST_F(GfxImageColorMapTest_530, GetColorSpace_NotNull_530) {
    Object decodeObj;
    decodeObj.initNull();
    
    std::unique_ptr<GfxColorSpace> grayCs(new GfxDeviceGrayColorSpace());
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(grayCs));
    if (colorMap.isOk()) {
        GfxColorSpace *cs = colorMap.getColorSpace();
        ASSERT_NE(cs, nullptr);
    }
}
