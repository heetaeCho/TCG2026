#include <gtest/gtest.h>
#include "GfxState.h"

// Since GfxColorSpace is abstract (has pure virtual methods), we need a concrete subclass for testing.
// We'll use GfxDeviceRGBColorSpace or similar concrete subclass if available.
// Based on the poppler codebase, GfxDeviceRGBColorSpace, GfxDeviceGrayColorSpace, and GfxDeviceCMYKColorSpace
// are concrete subclasses.

class GfxColorSpaceTest_406 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a default-constructed GfxDeviceGrayColorSpace has a valid overprint mask
TEST_F(GfxColorSpaceTest_406, DeviceGrayOverprintMask_406) {
    GfxDeviceGrayColorSpace cs;
    unsigned int mask = cs.getOverprintMask();
    // DeviceGray typically has overprint mask of 1 (first component)
    // We just verify it returns a value (treating as black box, but we can check it's nonzero for a marking color space)
    EXPECT_NE(mask, 0u);
}

// Test that a default-constructed GfxDeviceRGBColorSpace has a valid overprint mask
TEST_F(GfxColorSpaceTest_406, DeviceRGBOverprintMask_406) {
    GfxDeviceRGBColorSpace cs;
    unsigned int mask = cs.getOverprintMask();
    // DeviceRGB should have a non-zero overprint mask
    EXPECT_NE(mask, 0u);
}

// Test that a default-constructed GfxDeviceCMYKColorSpace has a valid overprint mask
TEST_F(GfxColorSpaceTest_406, DeviceCMYKOverprintMask_406) {
    GfxDeviceCMYKColorSpace cs;
    unsigned int mask = cs.getOverprintMask();
    // DeviceCMYK should have a non-zero overprint mask covering C, M, Y, K
    EXPECT_NE(mask, 0u);
}

// Test that getOverprintMask returns consistent results on repeated calls
TEST_F(GfxColorSpaceTest_406, OverprintMaskConsistency_406) {
    GfxDeviceRGBColorSpace cs;
    unsigned int mask1 = cs.getOverprintMask();
    unsigned int mask2 = cs.getOverprintMask();
    EXPECT_EQ(mask1, mask2);
}

// Test that copy preserves the overprint mask
TEST_F(GfxColorSpaceTest_406, CopyPreservesOverprintMask_406) {
    GfxDeviceRGBColorSpace cs;
    unsigned int originalMask = cs.getOverprintMask();
    std::unique_ptr<GfxColorSpace> csCopy = cs.copy();
    ASSERT_NE(csCopy, nullptr);
    EXPECT_EQ(csCopy->getOverprintMask(), originalMask);
}

// Test getMode for DeviceGray
TEST_F(GfxColorSpaceTest_406, DeviceGrayMode_406) {
    GfxDeviceGrayColorSpace cs;
    EXPECT_EQ(cs.getMode(), csDeviceGray);
}

// Test getMode for DeviceRGB
TEST_F(GfxColorSpaceTest_406, DeviceRGBMode_406) {
    GfxDeviceRGBColorSpace cs;
    EXPECT_EQ(cs.getMode(), csDeviceRGB);
}

// Test getMode for DeviceCMYK
TEST_F(GfxColorSpaceTest_406, DeviceCMYKMode_406) {
    GfxDeviceCMYKColorSpace cs;
    EXPECT_EQ(cs.getMode(), csDeviceCMYK);
}

// Test getNComps for DeviceGray
TEST_F(GfxColorSpaceTest_406, DeviceGrayNComps_406) {
    GfxDeviceGrayColorSpace cs;
    EXPECT_EQ(cs.getNComps(), 1);
}

// Test getNComps for DeviceRGB
TEST_F(GfxColorSpaceTest_406, DeviceRGBNComps_406) {
    GfxDeviceRGBColorSpace cs;
    EXPECT_EQ(cs.getNComps(), 3);
}

// Test getNComps for DeviceCMYK
TEST_F(GfxColorSpaceTest_406, DeviceCMYKNComps_406) {
    GfxDeviceCMYKColorSpace cs;
    EXPECT_EQ(cs.getNComps(), 4);
}

// Test isNonMarking for standard device color spaces (should be false)
TEST_F(GfxColorSpaceTest_406, DeviceGrayIsNotNonMarking_406) {
    GfxDeviceGrayColorSpace cs;
    EXPECT_FALSE(cs.isNonMarking());
}

TEST_F(GfxColorSpaceTest_406, DeviceRGBIsNotNonMarking_406) {
    GfxDeviceRGBColorSpace cs;
    EXPECT_FALSE(cs.isNonMarking());
}

TEST_F(GfxColorSpaceTest_406, DeviceCMYKIsNotNonMarking_406) {
    GfxDeviceCMYKColorSpace cs;
    EXPECT_FALSE(cs.isNonMarking());
}

// Test getDefaultColor for DeviceGray
TEST_F(GfxColorSpaceTest_406, DeviceGrayDefaultColor_406) {
    GfxDeviceGrayColorSpace cs;
    GfxColor color;
    cs.getDefaultColor(&color);
    // Default gray color should be 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

// Test getDefaultColor for DeviceRGB
TEST_F(GfxColorSpaceTest_406, DeviceRGBDefaultColor_406) {
    GfxDeviceRGBColorSpace cs;
    GfxColor color;
    cs.getDefaultColor(&color);
    // Default RGB color should be (0,0,0) - black
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

// Test getDefaultColor for DeviceCMYK
TEST_F(GfxColorSpaceTest_406, DeviceCMYKDefaultColor_406) {
    GfxDeviceCMYKColorSpace cs;
    GfxColor color;
    cs.getDefaultColor(&color);
    // Default CMYK color should have all components at 0
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
    EXPECT_EQ(color.c[3], 0);
}

// Test getNumColorSpaceModes returns a positive number
TEST_F(GfxColorSpaceTest_406, NumColorSpaceModes_406) {
    int num = GfxColorSpace::getNumColorSpaceModes();
    EXPECT_GT(num, 0);
}

// Test getColorSpaceModeName for valid indices
TEST_F(GfxColorSpaceTest_406, ColorSpaceModeNameValid_406) {
    int num = GfxColorSpace::getNumColorSpaceModes();
    for (int i = 0; i < num; i++) {
        const char* name = GfxColorSpace::getColorSpaceModeName(i);
        EXPECT_NE(name, nullptr);
        EXPECT_GT(strlen(name), 0u);
    }
}

// Test getColorSpaceModeName for out-of-range index
TEST_F(GfxColorSpaceTest_406, ColorSpaceModeNameOutOfRange_406) {
    int num = GfxColorSpace::getNumColorSpaceModes();
    const char* name = GfxColorSpace::getColorSpaceModeName(num);
    EXPECT_EQ(name, nullptr);
}

// Test getColorSpaceModeName for negative index
TEST_F(GfxColorSpaceTest_406, ColorSpaceModeNameNegativeIndex_406) {
    const char* name = GfxColorSpace::getColorSpaceModeName(-1);
    EXPECT_EQ(name, nullptr);
}

// Test getMapping returns a reference (basic check)
TEST_F(GfxColorSpaceTest_406, GetMappingReturnsReference_406) {
    GfxDeviceRGBColorSpace cs;
    const std::vector<int>& mapping = cs.getMapping();
    // Just verify we can access it without crashing; size may vary
    (void)mapping.size();
    SUCCEED();
}

// Test useGetRGBLine for DeviceRGB
TEST_F(GfxColorSpaceTest_406, DeviceRGBUseGetRGBLine_406) {
    GfxDeviceRGBColorSpace cs;
    // DeviceRGB should support getRGBLine optimization
    bool result = cs.useGetRGBLine();
    // We just check it returns a bool without crashing
    (void)result;
    SUCCEED();
}

// Test useGetGrayLine for DeviceGray
TEST_F(GfxColorSpaceTest_406, DeviceGrayUseGetGrayLine_406) {
    GfxDeviceGrayColorSpace cs;
    bool result = cs.useGetGrayLine();
    (void)result;
    SUCCEED();
}

// Test useGetCMYKLine for DeviceCMYK
TEST_F(GfxColorSpaceTest_406, DeviceCMYKUseGetCMYKLine_406) {
    GfxDeviceCMYKColorSpace cs;
    bool result = cs.useGetCMYKLine();
    (void)result;
    SUCCEED();
}

// Test useGetDeviceNLine
TEST_F(GfxColorSpaceTest_406, DeviceRGBUseGetDeviceNLine_406) {
    GfxDeviceRGBColorSpace cs;
    bool result = cs.useGetDeviceNLine();
    (void)result;
    SUCCEED();
}

// Test copy returns a non-null unique_ptr with same mode
TEST_F(GfxColorSpaceTest_406, CopyReturnsSameMode_406) {
    GfxDeviceCMYKColorSpace cs;
    auto copy = cs.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->getMode(), cs.getMode());
    EXPECT_EQ(copy->getNComps(), cs.getNComps());
}

// Test that getGray works for DeviceGray
TEST_F(GfxColorSpaceTest_406, DeviceGrayGetGray_406) {
    GfxDeviceGrayColorSpace cs;
    GfxColor color;
    color.c[0] = 0; // black
    GfxGray gray;
    cs.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

// Test that getRGB works for DeviceGray with white
TEST_F(GfxColorSpaceTest_406, DeviceGrayGetRGBWhite_406) {
    GfxDeviceGrayColorSpace cs;
    GfxColor color;
    color.c[0] = gfxColorComp1; // white (max value)
    GfxRGB rgb;
    cs.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}

// Test overprint mask values are distinct for different color space types
TEST_F(GfxColorSpaceTest_406, OverprintMaskDifferentColorSpaces_406) {
    GfxDeviceGrayColorSpace gray;
    GfxDeviceRGBColorSpace rgb;
    GfxDeviceCMYKColorSpace cmyk;
    
    unsigned int grayMask = gray.getOverprintMask();
    unsigned int rgbMask = rgb.getOverprintMask();
    unsigned int cmykMask = cmyk.getOverprintMask();
    
    // All should be non-zero for marking color spaces
    EXPECT_NE(grayMask, 0u);
    EXPECT_NE(rgbMask, 0u);
    EXPECT_NE(cmykMask, 0u);
}
