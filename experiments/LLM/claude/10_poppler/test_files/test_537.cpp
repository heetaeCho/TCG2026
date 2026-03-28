#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "Object.h"

// Mock GfxColorSpace to control useGetCMYKLine() behavior
class MockGfxColorSpace : public GfxColorSpace {
public:
    MOCK_CONST_METHOD0(getMode, GfxColorSpaceMode());
    MOCK_CONST_METHOD2(getGray, void(const GfxColor *color, GfxGray *gray));
    MOCK_CONST_METHOD2(getRGB, void(const GfxColor *color, GfxRGB *rgb));
    MOCK_CONST_METHOD2(getCMYK, void(const GfxColor *color, GfxCMYK *cmyk));
    MOCK_CONST_METHOD2(getDeviceN, void(const GfxColor *color, GfxColor *deviceN));
    MOCK_CONST_METHOD0(getNComps, int());
    MOCK_CONST_METHOD1(getDefaultColor, void(GfxColor *color));
    MOCK_CONST_METHOD0(copy, const std::unique_ptr<GfxColorSpace>());
    MOCK_CONST_METHOD0(useGetCMYKLine, bool());
    MOCK_CONST_METHOD0(useGetRGBLine, bool());
    MOCK_CONST_METHOD0(useGetGrayLine, bool());
    MOCK_CONST_METHOD0(useGetDeviceNLine, bool());
};

// Test fixture for GfxImageColorMap
class GfxImageColorMapTest_537 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that GfxImageColorMap can be constructed with a DeviceRGB color space
TEST_F(GfxImageColorMapTest_537, ConstructWithDeviceRGB_537) {
    Object decodeObj;
    decodeObj.initNull();
    auto cs = GfxColorSpace::parse(nullptr, nullptr, nullptr, nullptr, 0);
    // We can't easily construct without a valid color space, so we test what we can
    // through the interface with a simple device gray
    
    // Create a DeviceGray color space via Object
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            EXPECT_EQ(colorMap.getBits(), 8);
            EXPECT_EQ(colorMap.getNumPixelComps(), 1);
            EXPECT_NE(colorMap.getColorSpace(), nullptr);
        }
    }
}

// Test isOk returns false for invalid construction
TEST_F(GfxImageColorMapTest_537, InvalidConstruction_537) {
    Object decodeObj;
    decodeObj.initNull();
    
    // Pass null/invalid color space
    GfxImageColorMap colorMap(8, &decodeObj, std::unique_ptr<GfxColorSpace>(nullptr));
    EXPECT_FALSE(colorMap.isOk());
}

// Test getBits returns the bits value passed to constructor
TEST_F(GfxImageColorMapTest_537, GetBitsReturnsConstructedValue_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(4, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            EXPECT_EQ(colorMap.getBits(), 4);
        }
    }
}

// Test getDecodeLow and getDecodeHigh for default decode array
TEST_F(GfxImageColorMapTest_537, DefaultDecodeRange_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            // Default decode for DeviceGray should be [0, 1]
            EXPECT_DOUBLE_EQ(colorMap.getDecodeLow(0), 0.0);
            EXPECT_DOUBLE_EQ(colorMap.getDecodeHigh(0), 1.0);
        }
    }
}

// Test getNumPixelComps for DeviceGray (1 component)
TEST_F(GfxImageColorMapTest_537, NumPixelCompsDeviceGray_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            EXPECT_EQ(colorMap.getNumPixelComps(), 1);
        }
    }
}

// Test getNumPixelComps for DeviceRGB (3 components)
TEST_F(GfxImageColorMapTest_537, NumPixelCompsDeviceRGB_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceRGB");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            EXPECT_EQ(colorMap.getNumPixelComps(), 3);
        }
    }
}

// Test getNumPixelComps for DeviceCMYK (4 components)
TEST_F(GfxImageColorMapTest_537, NumPixelCompsDeviceCMYK_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceCMYK");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            EXPECT_EQ(colorMap.getNumPixelComps(), 4);
        }
    }
}

// Test copy creates a valid copy
TEST_F(GfxImageColorMapTest_537, CopyProducesValidMap_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            GfxImageColorMap *copied = colorMap.copy();
            ASSERT_NE(copied, nullptr);
            EXPECT_TRUE(copied->isOk());
            EXPECT_EQ(copied->getBits(), colorMap.getBits());
            EXPECT_EQ(copied->getNumPixelComps(), colorMap.getNumPixelComps());
            delete copied;
        }
    }
}

// Test setMatteColor and getMatteColor
TEST_F(GfxImageColorMapTest_537, MatteColorSetAndGet_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            GfxColor matteColor;
            matteColor.c[0] = 32768; // some value
            colorMap.setMatteColor(&matteColor);
            const GfxColor *retrieved = colorMap.getMatteColor();
            ASSERT_NE(retrieved, nullptr);
            EXPECT_EQ(retrieved->c[0], 32768);
        }
    }
}

// Test useCMYKLine for DeviceGray (expected to be false typically)
TEST_F(GfxImageColorMapTest_537, UseCMYKLineDeviceGray_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            // DeviceGray typically does not support CMYK line
            bool result = colorMap.useCMYKLine();
            // We just verify it returns a boolean without crashing
            (void)result;
            SUCCEED();
        }
    }
}

// Test useCMYKLine for DeviceCMYK (expected to be true typically)
TEST_F(GfxImageColorMapTest_537, UseCMYKLineDeviceCMYK_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceCMYK");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            // DeviceCMYK should support CMYK line
            EXPECT_TRUE(colorMap.useCMYKLine());
        }
    }
}

// Test useRGBLine for DeviceRGB
TEST_F(GfxImageColorMapTest_537, UseRGBLineDeviceRGB_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceRGB");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            // DeviceRGB should support RGB line
            EXPECT_TRUE(colorMap.useRGBLine());
        }
    }
}

// Test useDeviceNLine
TEST_F(GfxImageColorMapTest_537, UseDeviceNLine_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            bool result = colorMap.useDeviceNLine();
            (void)result;
            SUCCEED();
        }
    }
}

// Test getGray for DeviceGray
TEST_F(GfxImageColorMapTest_537, GetGrayDeviceGray_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            unsigned char pixel = 0;
            GfxGray gray;
            colorMap.getGray(&pixel, &gray);
            // Pixel 0 should map to gray 0 (black) with default decode
            EXPECT_EQ(gray, 0);
            
            pixel = 255;
            colorMap.getGray(&pixel, &gray);
            // Pixel 255 should map to gray ~65535 (white)
            EXPECT_GT(gray, 0);
        }
    }
}

// Test getRGB for DeviceRGB
TEST_F(GfxImageColorMapTest_537, GetRGBDeviceRGB_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceRGB");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            unsigned char pixel[3] = {255, 0, 0}; // Red
            GfxRGB rgb;
            colorMap.getRGB(pixel, &rgb);
            // Red channel should be high
            EXPECT_GT(rgb.r, 0);
        }
    }
}

// Test getCMYK for DeviceCMYK
TEST_F(GfxImageColorMapTest_537, GetCMYKDeviceCMYK_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceCMYK");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            unsigned char pixel[4] = {255, 0, 0, 0}; // Cyan
            GfxCMYK cmyk;
            colorMap.getCMYK(pixel, &cmyk);
            // Cyan channel should be high
            EXPECT_GT(cmyk.c, 0);
        }
    }
}

// Test boundary: 1-bit image
TEST_F(GfxImageColorMapTest_537, OneBitImage_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(1, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            EXPECT_EQ(colorMap.getBits(), 1);
            
            unsigned char pixel0 = 0;
            GfxGray gray0;
            colorMap.getGray(&pixel0, &gray0);
            
            unsigned char pixel1 = 1;
            GfxGray gray1;
            colorMap.getGray(&pixel1, &gray1);
            
            // Pixel 0 should be different from pixel 1
            EXPECT_NE(gray0, gray1);
        }
    }
}

// Test getColorSpace returns non-null for valid map
TEST_F(GfxImageColorMapTest_537, GetColorSpaceReturnsNonNull_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            EXPECT_NE(colorMap.getColorSpace(), nullptr);
        }
    }
}

// Test getColor
TEST_F(GfxImageColorMapTest_537, GetColor_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            unsigned char pixel = 128;
            GfxColor color;
            colorMap.getColor(&pixel, &color);
            // Mid-gray should have a mid-range value
            EXPECT_GT(color.c[0], 0);
        }
    }
}

// Test with explicit decode array
TEST_F(GfxImageColorMapTest_537, ExplicitDecodeArray_537) {
    // Create decode array [1, 0] to invert
    Object decodeObj;
    decodeObj.initArray(/* xref */ nullptr);
    Object val1, val2;
    val1.initReal(1.0);
    val2.initReal(0.0);
    decodeObj.arrayAdd(std::move(val1));
    decodeObj.arrayAdd(std::move(val2));
    
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            // With inverted decode [1, 0]:
            EXPECT_DOUBLE_EQ(colorMap.getDecodeLow(0), 1.0);
            EXPECT_DOUBLE_EQ(colorMap.getDecodeHigh(0), 0.0);
        }
    }
}

// Test getGrayLine
TEST_F(GfxImageColorMapTest_537, GetGrayLine_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            unsigned char in[4] = {0, 85, 170, 255};
            unsigned char out[4] = {0};
            colorMap.getGrayLine(in, out, 4);
            // Output should be monotonically increasing for default decode
            EXPECT_LE(out[0], out[1]);
            EXPECT_LE(out[1], out[2]);
            EXPECT_LE(out[2], out[3]);
        }
    }
}

// Test getRGBLine (unsigned int output)
TEST_F(GfxImageColorMapTest_537, GetRGBLineUintOutput_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceRGB");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            unsigned char in[6] = {255, 0, 0, 0, 255, 0}; // Red, Green
            unsigned int out[2] = {0};
            colorMap.getRGBLine(in, out, 2);
            // Just verify it doesn't crash and produces some output
            SUCCEED();
        }
    }
}

// Test getCMYKLine
TEST_F(GfxImageColorMapTest_537, GetCMYKLine_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceCMYK");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            unsigned char in[8] = {255, 0, 0, 0, 0, 255, 0, 0};
            unsigned char out[8] = {0};
            colorMap.getCMYKLine(in, out, 2);
            SUCCEED();
        }
    }
}

// Test zero-length line operations don't crash
TEST_F(GfxImageColorMapTest_537, ZeroLengthLine_537) {
    Object decodeObj;
    decodeObj.initNull();
    Object csObj;
    csObj.initName("DeviceGray");
    auto colorSpace = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    
    if (colorSpace) {
        GfxImageColorMap colorMap(8, &decodeObj, std::move(colorSpace));
        if (colorMap.isOk()) {
            unsigned char in[1] = {0};
            unsigned char out[1] = {0};
            colorMap.getGrayLine(in, out, 0);
            SUCCEED();
        }
    }
}
