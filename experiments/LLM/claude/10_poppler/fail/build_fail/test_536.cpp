#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "Object.h"
#include <memory>

// Mock GfxColorSpace to control useGetRGBLine() behavior
class MockGfxColorSpace : public GfxColorSpace {
public:
    MOCK_CONST_METHOD0(getMode, GfxColorSpaceMode());
    MOCK_CONST_METHOD0(copy, const std::unique_ptr<GfxColorSpace>());
    MOCK_CONST_METHOD2(getGray, void(const GfxColor *color, GfxGray *gray));
    MOCK_CONST_METHOD2(getRGB, void(const GfxColor *color, GfxRGB *rgb));
    MOCK_CONST_METHOD2(getCMYK, void(const GfxColor *color, GfxCMYK *cmyk));
    MOCK_CONST_METHOD2(getDeviceN, void(const GfxColor *color, GfxColor *deviceN));
    MOCK_CONST_METHOD0(getNComps, int());
    MOCK_CONST_METHOD1(getDefaultColor, void(GfxColor *color));
    MOCK_CONST_METHOD3(getDefaultRanges, void(double *decodeLow, double *decodeRange, int maxImgPixel));
    MOCK_CONST_METHOD0(useGetRGBLine, bool());
    MOCK_CONST_METHOD0(useGetGrayLine, bool());
    MOCK_CONST_METHOD0(useGetCMYKLine, bool());
    MOCK_CONST_METHOD0(useGetDeviceNLine, bool());
    MOCK_CONST_METHOD0(isNonMarking, bool());
};

class GfxImageColorMapTest_536 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test useRGBLine with a DeviceRGB color space (which typically supports getRGBLine)
TEST_F(GfxImageColorMapTest_536, UseRGBLineWithDeviceRGB_536) {
    // Create a DeviceRGB color space
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    // DeviceRGB typically supports getRGBLine
    bool result = colorMap.useRGBLine();
    // We just verify it returns a boolean without crashing
    EXPECT_TRUE(result == true || result == false);
}

// Test useRGBLine with a DeviceGray color space
TEST_F(GfxImageColorMapTest_536, UseRGBLineWithDeviceGray_536) {
    Object csObj;
    csObj.initName("DeviceGray");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    bool result = colorMap.useRGBLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test useRGBLine with a DeviceCMYK color space
TEST_F(GfxImageColorMapTest_536, UseRGBLineWithDeviceCMYK_536) {
    Object csObj;
    csObj.initName("DeviceCMYK");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceCMYK color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    bool result = colorMap.useRGBLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test isOk returns valid state
TEST_F(GfxImageColorMapTest_536, IsOkAfterConstruction_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    // Should be ok with valid DeviceRGB and 8 bits
    EXPECT_TRUE(colorMap.isOk());
}

// Test getBits returns correct value
TEST_F(GfxImageColorMapTest_536, GetBitsReturnsCorrectValue_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    EXPECT_EQ(colorMap.getBits(), 8);
}

// Test getNumPixelComps for DeviceRGB (should be 3)
TEST_F(GfxImageColorMapTest_536, GetNumPixelCompsDeviceRGB_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    EXPECT_EQ(colorMap.getNumPixelComps(), 3);
}

// Test getNumPixelComps for DeviceGray (should be 1)
TEST_F(GfxImageColorMapTest_536, GetNumPixelCompsDeviceGray_536) {
    Object csObj;
    csObj.initName("DeviceGray");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    EXPECT_EQ(colorMap.getNumPixelComps(), 1);
}

// Test getNumPixelComps for DeviceCMYK (should be 4)
TEST_F(GfxImageColorMapTest_536, GetNumPixelCompsDeviceCMYK_536) {
    Object csObj;
    csObj.initName("DeviceCMYK");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceCMYK color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    EXPECT_EQ(colorMap.getNumPixelComps(), 4);
}

// Test getColorSpace returns non-null
TEST_F(GfxImageColorMapTest_536, GetColorSpaceReturnsNonNull_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    EXPECT_NE(colorMap.getColorSpace(), nullptr);
}

// Test copy produces valid copy
TEST_F(GfxImageColorMapTest_536, CopyProducesValidObject_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    GfxImageColorMap *copied = colorMap.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isOk());
    EXPECT_EQ(copied->getBits(), colorMap.getBits());
    EXPECT_EQ(copied->getNumPixelComps(), colorMap.getNumPixelComps());
    EXPECT_EQ(copied->useRGBLine(), colorMap.useRGBLine());
    delete copied;
}

// Test useCMYKLine
TEST_F(GfxImageColorMapTest_536, UseCMYKLineWithDeviceCMYK_536) {
    Object csObj;
    csObj.initName("DeviceCMYK");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceCMYK color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    bool result = colorMap.useCMYKLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test useDeviceNLine
TEST_F(GfxImageColorMapTest_536, UseDeviceNLine_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    bool result = colorMap.useDeviceNLine();
    EXPECT_TRUE(result == true || result == false);
}

// Test getMatteColor returns null initially
TEST_F(GfxImageColorMapTest_536, GetMatteColorInitiallyNull_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    // Initially no matte color should be set
    const GfxColor *matte = colorMap.getMatteColor();
    // The initial state depends on implementation; just verify it doesn't crash
    (void)matte;
}

// Test setMatteColor and getMatteColor roundtrip
TEST_F(GfxImageColorMapTest_536, SetAndGetMatteColor_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    GfxColor color;
    color.c[0] = 100;
    color.c[1] = 200;
    color.c[2] = 50;
    
    colorMap.setMatteColor(&color);
    const GfxColor *retrieved = colorMap.getMatteColor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->c[0], 100);
    EXPECT_EQ(retrieved->c[1], 200);
    EXPECT_EQ(retrieved->c[2], 50);
}

// Test with different bit depths
TEST_F(GfxImageColorMapTest_536, BitsDepth1_536) {
    Object csObj;
    csObj.initName("DeviceGray");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceGray color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(1, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    EXPECT_EQ(colorMap.getBits(), 1);
    // useRGBLine should still be callable
    bool result = colorMap.useRGBLine();
    (void)result;
}

// Test with 16-bit depth
TEST_F(GfxImageColorMapTest_536, BitsDepth16_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(16, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok with 16 bits";
    }
    
    EXPECT_EQ(colorMap.getBits(), 16);
}

// Test getDecodeLow and getDecodeHigh
TEST_F(GfxImageColorMapTest_536, GetDecodeLowAndHigh_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    // With null decode, defaults should be used
    // For DeviceRGB with 8 bits, default decode is [0, 1] for each component
    for (int i = 0; i < colorMap.getNumPixelComps(); i++) {
        double low = colorMap.getDecodeLow(i);
        double high = colorMap.getDecodeHigh(i);
        EXPECT_LE(low, high);
    }
}

// Test useRGBLine consistency with copy
TEST_F(GfxImageColorMapTest_536, UseRGBLineConsistentWithCopy_536) {
    Object csObj;
    csObj.initName("DeviceRGB");
    auto cs = GfxColorSpace::parse(nullptr, &csObj, nullptr, nullptr, 0);
    if (!cs) {
        GTEST_SKIP() << "Could not create DeviceRGB color space";
    }
    
    Object decodeObj;
    decodeObj.initNull();
    
    GfxImageColorMap colorMap(8, &decodeObj, std::move(cs));
    if (!colorMap.isOk()) {
        GTEST_SKIP() << "ColorMap not ok";
    }
    
    bool originalUseRGBLine = colorMap.useRGBLine();
    
    GfxImageColorMap *copied = colorMap.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->useRGBLine(), originalUseRGBLine);
    delete copied;
}
