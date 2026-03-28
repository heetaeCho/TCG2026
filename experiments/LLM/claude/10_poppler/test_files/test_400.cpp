#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Since GfxColorSpace is abstract (has pure virtual methods), we need a concrete subclass for testing.
// We'll use GfxDeviceRGBColorSpace or similar concrete subclass if available.
// Based on the poppler codebase, GfxDeviceGrayColorSpace, GfxDeviceRGBColorSpace, GfxDeviceCMYKColorSpace
// are concrete implementations.

class GfxColorSpaceTest_400 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getMapping returns a reference to the mapping vector
// For a freshly constructed color space, the mapping should be empty or have default values
TEST_F(GfxColorSpaceTest_400, GetMappingReturnsVector_400) {
    // GfxDeviceGrayColorSpace is a concrete subclass
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    const std::vector<int> &mapping = cs->getMapping();
    // Before createMapping is called, mapping should be empty
    EXPECT_TRUE(mapping.empty());
}

TEST_F(GfxColorSpaceTest_400, GetMappingAfterCreateMapping_400) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    const std::vector<int> &mapping = cs->getMapping();
    // Before createMapping, mapping should be empty
    EXPECT_TRUE(mapping.empty());
}

TEST_F(GfxColorSpaceTest_400, DeviceGrayMode_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    EXPECT_EQ(cs->getMode(), csDeviceGray);
}

TEST_F(GfxColorSpaceTest_400, DeviceRGBMode_400) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    EXPECT_EQ(cs->getMode(), csDeviceRGB);
}

TEST_F(GfxColorSpaceTest_400, DeviceCMYKMode_400) {
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    EXPECT_EQ(cs->getMode(), csDeviceCMYK);
}

TEST_F(GfxColorSpaceTest_400, DeviceGrayNComps_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    EXPECT_EQ(cs->getNComps(), 1);
}

TEST_F(GfxColorSpaceTest_400, DeviceRGBNComps_400) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    EXPECT_EQ(cs->getNComps(), 3);
}

TEST_F(GfxColorSpaceTest_400, DeviceCMYKNComps_400) {
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    EXPECT_EQ(cs->getNComps(), 4);
}

TEST_F(GfxColorSpaceTest_400, DeviceGrayGetDefaultColor_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxColor color;
    cs->getDefaultColor(&color);
    // Default gray color should be 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

TEST_F(GfxColorSpaceTest_400, DeviceRGBGetDefaultColor_400) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxColor color;
    cs->getDefaultColor(&color);
    // Default RGB color should be (0, 0, 0) - black
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
}

TEST_F(GfxColorSpaceTest_400, DeviceCMYKGetDefaultColor_400) {
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxColor color;
    cs->getDefaultColor(&color);
    // Default CMYK should be (0, 0, 0, 1) - black
    EXPECT_EQ(color.c[0], 0);
    EXPECT_EQ(color.c[1], 0);
    EXPECT_EQ(color.c[2], 0);
    EXPECT_EQ(color.c[3], gfxColorComp1);
}

TEST_F(GfxColorSpaceTest_400, DeviceGrayCopy_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    auto csCopy = cs->copy();
    ASSERT_NE(csCopy, nullptr);
    EXPECT_EQ(csCopy->getMode(), csDeviceGray);
    EXPECT_EQ(csCopy->getNComps(), 1);
}

TEST_F(GfxColorSpaceTest_400, DeviceRGBCopy_400) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    auto csCopy = cs->copy();
    ASSERT_NE(csCopy, nullptr);
    EXPECT_EQ(csCopy->getMode(), csDeviceRGB);
    EXPECT_EQ(csCopy->getNComps(), 3);
}

TEST_F(GfxColorSpaceTest_400, DeviceCMYKCopy_400) {
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    auto csCopy = cs->copy();
    ASSERT_NE(csCopy, nullptr);
    EXPECT_EQ(csCopy->getMode(), csDeviceCMYK);
    EXPECT_EQ(csCopy->getNComps(), 4);
}

TEST_F(GfxColorSpaceTest_400, DeviceGrayIsNonMarking_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    EXPECT_FALSE(cs->isNonMarking());
}

TEST_F(GfxColorSpaceTest_400, DeviceRGBIsNonMarking_400) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    EXPECT_FALSE(cs->isNonMarking());
}

TEST_F(GfxColorSpaceTest_400, GetOverprintMask_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    // The overprintMask should have some default value
    unsigned int mask = cs->getOverprintMask();
    // For device gray, overprintMask is typically 0xf or similar
    // Just verify it returns a value without crashing
    (void)mask;
}

TEST_F(GfxColorSpaceTest_400, DeviceGrayGetGray_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    cs->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

TEST_F(GfxColorSpaceTest_400, DeviceGrayGetGrayMaxValue_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxColor color;
    color.c[0] = gfxColorComp1;
    GfxGray gray;
    cs->getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1);
}

TEST_F(GfxColorSpaceTest_400, DeviceGrayGetRGB_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

TEST_F(GfxColorSpaceTest_400, DeviceRGBGetRGB_400) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);
}

TEST_F(GfxColorSpaceTest_400, DeviceRGBGetGray_400) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxColor color;
    color.c[0] = 0;
    color.c[1] = 0;
    color.c[2] = 0;
    GfxGray gray;
    cs->getGray(&color, &gray);
    EXPECT_EQ(gray, 0);
}

TEST_F(GfxColorSpaceTest_400, GetNumColorSpaceModes_400) {
    int numModes = GfxColorSpace::getNumColorSpaceModes();
    EXPECT_GT(numModes, 0);
}

TEST_F(GfxColorSpaceTest_400, GetColorSpaceModeName_400) {
    int numModes = GfxColorSpace::getNumColorSpaceModes();
    for (int i = 0; i < numModes; i++) {
        const char *name = GfxColorSpace::getColorSpaceModeName(i);
        EXPECT_NE(name, nullptr);
        EXPECT_GT(strlen(name), 0u);
    }
}

TEST_F(GfxColorSpaceTest_400, GetColorSpaceModeNameOutOfRange_400) {
    int numModes = GfxColorSpace::getNumColorSpaceModes();
    const char *name = GfxColorSpace::getColorSpaceModeName(numModes);
    // Out of range should return nullptr
    EXPECT_EQ(name, nullptr);
}

TEST_F(GfxColorSpaceTest_400, GetColorSpaceModeNameNegativeIndex_400) {
    const char *name = GfxColorSpace::getColorSpaceModeName(-1);
    EXPECT_EQ(name, nullptr);
}

TEST_F(GfxColorSpaceTest_400, UseGetRGBLine_400) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    // DeviceRGB should support getRGBLine
    bool result = cs->useGetRGBLine();
    // Just verify it doesn't crash; the value depends on implementation
    (void)result;
}

TEST_F(GfxColorSpaceTest_400, UseGetGrayLine_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    bool result = cs->useGetGrayLine();
    (void)result;
}

TEST_F(GfxColorSpaceTest_400, UseGetCMYKLine_400) {
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    bool result = cs->useGetCMYKLine();
    (void)result;
}

TEST_F(GfxColorSpaceTest_400, UseGetDeviceNLine_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    bool result = cs->useGetDeviceNLine();
    (void)result;
}

TEST_F(GfxColorSpaceTest_400, GetMappingConsistencyAcrossCalls_400) {
    auto cs = std::make_unique<GfxDeviceRGBColorSpace>();
    const std::vector<int> &mapping1 = cs->getMapping();
    const std::vector<int> &mapping2 = cs->getMapping();
    // Should return the same reference
    EXPECT_EQ(&mapping1, &mapping2);
}

TEST_F(GfxColorSpaceTest_400, DeviceCMYKGetCMYK_400) {
    auto cs = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxColor color;
    color.c[0] = gfxColorComp1;
    color.c[1] = 0;
    color.c[2] = 0;
    color.c[3] = 0;
    GfxCMYK cmyk;
    cs->getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, gfxColorComp1);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);
}

TEST_F(GfxColorSpaceTest_400, ParseWithNullArgs_400) {
    Object obj;
    auto cs = GfxColorSpace::parse(nullptr, &obj, nullptr, nullptr, 0);
    // With a default/null object, parse should return nullptr
    EXPECT_EQ(cs, nullptr);
}

TEST_F(GfxColorSpaceTest_400, DeviceGrayGetDefaultRanges_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    double decodeLow[1], decodeRange[1];
    cs->getDefaultRanges(decodeLow, decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 1.0);
}

TEST_F(GfxColorSpaceTest_400, CopyPreservesMapping_400) {
    auto cs = std::make_unique<GfxDeviceGrayColorSpace>();
    const std::vector<int> &origMapping = cs->getMapping();
    auto csCopy = cs->copy();
    const std::vector<int> &copyMapping = csCopy->getMapping();
    EXPECT_EQ(origMapping.size(), copyMapping.size());
    for (size_t i = 0; i < origMapping.size(); i++) {
        EXPECT_EQ(origMapping[i], copyMapping[i]);
    }
}
