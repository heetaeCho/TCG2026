#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Test fixture for GfxICCBasedColorSpace
class GfxICCBasedColorSpaceTest_464 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getProfile returns the profile that was set via setProfile
TEST_F(GfxICCBasedColorSpaceTest_464, GetProfileReturnsSetProfile_464) {
    // Create a GfxICCBasedColorSpace with a simple alternate color space
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    // Initially profile should be null/empty
    GfxLCMSProfilePtr initialProfile = iccCS->getProfile();
    // We can check if it's a default/null profile
    // The exact check depends on GfxLCMSProfilePtr type, but we test the getter works
    
    // Set a profile and verify we get the same one back
#ifdef USE_CMS
    GfxLCMSProfilePtr srgbProfile = make_GfxLCMSProfilePtr(cmsCreate_sRGBProfile());
    iccCS->setProfile(srgbProfile);
    GfxLCMSProfilePtr retrievedProfile = iccCS->getProfile();
    EXPECT_EQ(retrievedProfile, srgbProfile);
#else
    // Without CMS, profile should be a null/default pointer
    EXPECT_FALSE(initialProfile);
#endif
}

// Test that getProfile returns empty/null profile when none has been set
TEST_F(GfxICCBasedColorSpaceTest_464, GetProfileReturnsNullWhenNotSet_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    GfxLCMSProfilePtr profile = iccCS->getProfile();
    // When no profile is set, it should be null/empty
    EXPECT_FALSE(profile);
}

// Test getMode returns expected mode for ICCBased color space
TEST_F(GfxICCBasedColorSpaceTest_464, GetModeReturnsICCBased_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    EXPECT_EQ(iccCS->getMode(), csICCBased);
}

// Test getNComps returns the number of components passed in constructor
TEST_F(GfxICCBasedColorSpaceTest_464, GetNCompsReturnsCorrectValue_464) {
    Ref ref = Ref::INVALID();
    
    // Test with 3 components (RGB alternate)
    {
        auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
        auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
        EXPECT_EQ(iccCS->getNComps(), 3);
    }
    
    // Test with 1 component (Gray alternate)
    {
        auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
        auto iccCS = std::make_unique<GfxICCBasedColorSpace>(1, std::move(altCS), &ref);
        EXPECT_EQ(iccCS->getNComps(), 1);
    }
    
    // Test with 4 components (CMYK alternate)
    {
        auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
        auto iccCS = std::make_unique<GfxICCBasedColorSpace>(4, std::move(altCS), &ref);
        EXPECT_EQ(iccCS->getNComps(), 4);
    }
}

// Test getAlt returns the alternate color space
TEST_F(GfxICCBasedColorSpaceTest_464, GetAltReturnsAlternateColorSpace_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxColorSpace *altPtr = altCS.get();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    GfxColorSpace *retrievedAlt = iccCS->getAlt();
    EXPECT_NE(retrievedAlt, nullptr);
    EXPECT_EQ(retrievedAlt, altPtr);
    EXPECT_EQ(retrievedAlt->getMode(), csDeviceRGB);
}

// Test getRef returns the ICC profile stream reference
TEST_F(GfxICCBasedColorSpaceTest_464, GetRefReturnsCorrectRef_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    Ref retrievedRef = iccCS->getRef();
    EXPECT_EQ(retrievedRef, Ref::INVALID());
}

// Test copy creates a valid copy
TEST_F(GfxICCBasedColorSpaceTest_464, CopyCreatesValidCopy_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    auto copiedCS = iccCS->copy();
    ASSERT_NE(copiedCS, nullptr);
    EXPECT_EQ(copiedCS->getMode(), csICCBased);
    EXPECT_EQ(copiedCS->getNComps(), 3);
}

// Test copyAsOwnType creates a valid typed copy
TEST_F(GfxICCBasedColorSpaceTest_464, CopyAsOwnTypeCreatesValidCopy_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    auto copiedCS = iccCS->copyAsOwnType();
    ASSERT_NE(copiedCS, nullptr);
    EXPECT_EQ(copiedCS->getMode(), csICCBased);
    EXPECT_EQ(copiedCS->getNComps(), 3);
}

// Test getDefaultColor sets a valid default color
TEST_F(GfxICCBasedColorSpaceTest_464, GetDefaultColorSetsColor_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    GfxColor color;
    iccCS->getDefaultColor(&color);
    // Default color should be initialized (typically all zeros or within range)
    // We just verify it doesn't crash and produces some values
    for (int i = 0; i < 3; i++) {
        EXPECT_GE(color.c[i], 0);
    }
}

// Test getGray produces a valid gray value
TEST_F(GfxICCBasedColorSpaceTest_464, GetGrayProducesValidValue_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    GfxColor color;
    iccCS->getDefaultColor(&color);
    
    GfxGray gray;
    iccCS->getGray(&color, &gray);
    // Gray should be within valid range [0, gfxColorComp1]
    EXPECT_GE(gray, 0);
}

// Test getRGB produces valid RGB values
TEST_F(GfxICCBasedColorSpaceTest_464, GetRGBProducesValidValues_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    GfxColor color;
    iccCS->getDefaultColor(&color);
    
    GfxRGB rgb;
    iccCS->getRGB(&color, &rgb);
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK produces valid CMYK values
TEST_F(GfxICCBasedColorSpaceTest_464, GetCMYKProducesValidValues_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    GfxColor color;
    iccCS->getDefaultColor(&color);
    
    GfxCMYK cmyk;
    iccCS->getCMYK(&color, &cmyk);
    EXPECT_GE(cmyk.c, 0);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_GE(cmyk.y, 0);
    EXPECT_GE(cmyk.k, 0);
}

// Test getDefaultRanges with 1 component (gray)
TEST_F(GfxICCBasedColorSpaceTest_464, GetDefaultRangesOneComponent_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(1, std::move(altCS), &ref);

    double decodeLow[1];
    double decodeRange[1];
    iccCS->getDefaultRanges(decodeLow, decodeRange, 255);
    // Should have valid range values
    EXPECT_LE(decodeLow[0], decodeRange[0] + decodeLow[0]);
}

// Test getDefaultRanges with 3 components (RGB)
TEST_F(GfxICCBasedColorSpaceTest_464, GetDefaultRangesThreeComponents_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    double decodeLow[3];
    double decodeRange[3];
    iccCS->getDefaultRanges(decodeLow, decodeRange, 255);
    for (int i = 0; i < 3; i++) {
        EXPECT_LE(decodeLow[i], decodeRange[i] + decodeLow[i]);
    }
}

// Test useGetRGBLine returns a boolean
TEST_F(GfxICCBasedColorSpaceTest_464, UseGetRGBLineReturnsBool_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    bool result = iccCS->useGetRGBLine();
    // Just verify it returns without error; value depends on CMS availability
    SUCCEED();
}

// Test useGetCMYKLine returns a boolean
TEST_F(GfxICCBasedColorSpaceTest_464, UseGetCMYKLineReturnsBool_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    bool result = iccCS->useGetCMYKLine();
    SUCCEED();
}

// Test useGetDeviceNLine returns a boolean
TEST_F(GfxICCBasedColorSpaceTest_464, UseGetDeviceNLineReturnsBool_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    bool result = iccCS->useGetDeviceNLine();
    SUCCEED();
}

// Test setProfile and getProfile roundtrip
TEST_F(GfxICCBasedColorSpaceTest_464, SetProfileAndGetProfileRoundtrip_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

#ifdef USE_CMS
    GfxLCMSProfilePtr profile1 = make_GfxLCMSProfilePtr(cmsCreate_sRGBProfile());
    iccCS->setProfile(profile1);
    EXPECT_EQ(iccCS->getProfile(), profile1);
    
    // Set a different profile
    GfxLCMSProfilePtr profile2 = make_GfxLCMSProfilePtr(cmsCreate_sRGBProfile());
    iccCS->setProfile(profile2);
    EXPECT_EQ(iccCS->getProfile(), profile2);
    EXPECT_NE(iccCS->getProfile(), profile1);
#else
    GfxLCMSProfilePtr profile = iccCS->getProfile();
    EXPECT_FALSE(profile);
#endif
}

// Test with 4 components (CMYK-based ICC)
TEST_F(GfxICCBasedColorSpaceTest_464, FourComponentICCBased_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(4, std::move(altCS), &ref);

    EXPECT_EQ(iccCS->getMode(), csICCBased);
    EXPECT_EQ(iccCS->getNComps(), 4);
    
    GfxColorSpace *alt = iccCS->getAlt();
    ASSERT_NE(alt, nullptr);
    EXPECT_EQ(alt->getMode(), csDeviceCMYK);
}

// Test getDeviceN with default color
TEST_F(GfxICCBasedColorSpaceTest_464, GetDeviceNWithDefaultColor_464) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);

    GfxColor color;
    iccCS->getDefaultColor(&color);
    
    GfxColor deviceN;
    iccCS->getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash
    SUCCEED();
}
