#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <string>

#include "GfxState.h"

// Test fixture for GfxDeviceNColorSpace
class GfxDeviceNColorSpaceTest_481 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getMode returns csDeviceN
TEST_F(GfxDeviceNColorSpaceTest_481, GetModeReturnsDeviceN_481) {
    // We need to construct a GfxDeviceNColorSpace. This requires:
    // - nComps
    // - names (vector of strings)
    // - alt color space
    // - function (tint transform)
    // - sepsCS (vector of separation color spaces)
    
    // Create a simple alternate color space (DeviceGray or DeviceRGB)
    std::unique_ptr<GfxColorSpace> altCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(altCS, nullptr);
    
    std::vector<std::string> names;
    names.push_back("Cyan");
    names.push_back("Magenta");
    
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;
    
    // Try to construct with nullptr function - this may or may not work
    // depending on implementation, but getMode should still return csDeviceN
    // if construction succeeds
    GfxDeviceNColorSpace colorSpace(2, std::move(names), std::move(altCS), nullptr, std::move(sepsCS));
    
    EXPECT_EQ(colorSpace.getMode(), csDeviceN);
}

// Test that csDeviceN has the expected enum value
TEST_F(GfxDeviceNColorSpaceTest_481, CsDeviceNEnumValue_481) {
    EXPECT_EQ(csDeviceN, 9);
}

// Test getNComps returns the number of components passed in constructor
TEST_F(GfxDeviceNColorSpaceTest_481, GetNCompsReturnsCorrectValue_481) {
    std::unique_ptr<GfxColorSpace> altCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(altCS, nullptr);
    
    std::vector<std::string> names;
    names.push_back("Spot1");
    names.push_back("Spot2");
    names.push_back("Spot3");
    
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;
    
    GfxDeviceNColorSpace colorSpace(3, std::move(names), std::move(altCS), nullptr, std::move(sepsCS));
    
    EXPECT_EQ(colorSpace.getNComps(), 3);
}

// Test getColorantName returns correct names
TEST_F(GfxDeviceNColorSpaceTest_481, GetColorantNameReturnsCorrectNames_481) {
    std::unique_ptr<GfxColorSpace> altCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(altCS, nullptr);
    
    std::vector<std::string> names;
    names.push_back("Red");
    names.push_back("Green");
    
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;
    
    GfxDeviceNColorSpace colorSpace(2, std::move(names), std::move(altCS), nullptr, std::move(sepsCS));
    
    EXPECT_EQ(colorSpace.getColorantName(0), "Red");
    EXPECT_EQ(colorSpace.getColorantName(1), "Green");
}

// Test getAlt returns non-null alternate color space
TEST_F(GfxDeviceNColorSpaceTest_481, GetAltReturnsNonNull_481) {
    std::unique_ptr<GfxColorSpace> altCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(altCS, nullptr);
    
    std::vector<std::string> names;
    names.push_back("Spot1");
    
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;
    
    GfxDeviceNColorSpace colorSpace(1, std::move(names), std::move(altCS), nullptr, std::move(sepsCS));
    
    GfxColorSpace* alt = colorSpace.getAlt();
    ASSERT_NE(alt, nullptr);
    EXPECT_EQ(alt->getMode(), csDeviceRGB);
}

// Test getDefaultColor produces a valid color
TEST_F(GfxDeviceNColorSpaceTest_481, GetDefaultColorSetsValues_481) {
    std::unique_ptr<GfxColorSpace> altCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(altCS, nullptr);
    
    std::vector<std::string> names;
    names.push_back("Spot1");
    names.push_back("Spot2");
    
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;
    
    GfxDeviceNColorSpace colorSpace(2, std::move(names), std::move(altCS), nullptr, std::move(sepsCS));
    
    GfxColor color;
    colorSpace.getDefaultColor(&color);
    
    // Default color for DeviceN typically sets all components to 1.0
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(color.c[i], gfxColorComp1);
    }
}

// Test copy produces a valid copy with same mode
TEST_F(GfxDeviceNColorSpaceTest_481, CopyPreservesMode_481) {
    std::unique_ptr<GfxColorSpace> altCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(altCS, nullptr);
    
    std::vector<std::string> names;
    names.push_back("Spot1");
    
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;
    
    GfxDeviceNColorSpace colorSpace(1, std::move(names), std::move(altCS), nullptr, std::move(sepsCS));
    
    std::unique_ptr<GfxColorSpace> copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceN);
}

// Test that all color space mode enum values are distinct
TEST_F(GfxDeviceNColorSpaceTest_481, ColorSpaceModeEnumValuesDistinct_481) {
    EXPECT_EQ(csDeviceGray, 0);
    EXPECT_EQ(csCalGray, 1);
    EXPECT_EQ(csDeviceRGB, 2);
    EXPECT_EQ(csCalRGB, 3);
    EXPECT_EQ(csDeviceCMYK, 4);
    EXPECT_EQ(csLab, 5);
    EXPECT_EQ(csICCBased, 6);
    EXPECT_EQ(csIndexed, 7);
    EXPECT_EQ(csSeparation, 8);
    EXPECT_EQ(csDeviceN, 9);
    EXPECT_EQ(csPattern, 10);
    EXPECT_EQ(csDeviceRGBA, 11);
}
