#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "GfxState.h"
#include "Object.h"

// Test fixture for GfxICCBasedColorSpace
class GfxICCBasedColorSpaceTest_461 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getAlt returns the alternate color space that was provided
TEST_F(GfxICCBasedColorSpaceTest_461, GetAltReturnsAlternateColorSpace_461) {
    // Create an alternate color space (e.g., DeviceRGB with 3 components)
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxColorSpace* altPtr = altCS.get();
    
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    ASSERT_NE(iccCS->getAlt(), nullptr);
    EXPECT_EQ(iccCS->getAlt(), altPtr);
}

// Test that getAlt returns a color space with the correct mode
TEST_F(GfxICCBasedColorSpaceTest_461, GetAltReturnsCorrectColorSpaceMode_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    GfxColorSpace* alt = iccCS->getAlt();
    ASSERT_NE(alt, nullptr);
    EXPECT_EQ(alt->getMode(), csDeviceRGB);
}

// Test that getMode returns csICCBased
TEST_F(GfxICCBasedColorSpaceTest_461, GetModeReturnsICCBased_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    EXPECT_EQ(iccCS->getMode(), csICCBased);
}

// Test getNComps returns the number of components passed in constructor
TEST_F(GfxICCBasedColorSpaceTest_461, GetNCompsReturnsCorrectValue_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    EXPECT_EQ(iccCS->getNComps(), 3);
}

// Test getNComps with 1 component (grayscale)
TEST_F(GfxICCBasedColorSpaceTest_461, GetNCompsReturnsOneForGrayscale_461) {
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(1, std::move(altCS), &ref);
    
    EXPECT_EQ(iccCS->getNComps(), 1);
}

// Test getNComps with 4 components (CMYK)
TEST_F(GfxICCBasedColorSpaceTest_461, GetNCompsReturnsFourForCMYK_461) {
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(4, std::move(altCS), &ref);
    
    EXPECT_EQ(iccCS->getNComps(), 4);
}

// Test getRef returns the reference passed in constructor
TEST_F(GfxICCBasedColorSpaceTest_461, GetRefReturnsCorrectRef_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    Ref result = iccCS->getRef();
    EXPECT_EQ(result, Ref::INVALID());
}

// Test copy creates a valid copy
TEST_F(GfxICCBasedColorSpaceTest_461, CopyCreatesValidCopy_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    auto copied = iccCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csICCBased);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test copyAsOwnType creates a valid copy with correct type
TEST_F(GfxICCBasedColorSpaceTest_461, CopyAsOwnTypeCreatesValidCopy_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    auto copied = iccCS->copyAsOwnType();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csICCBased);
    EXPECT_EQ(copied->getNComps(), 3);
    
    // The alt should also be copied
    GfxColorSpace* copiedAlt = copied->getAlt();
    ASSERT_NE(copiedAlt, nullptr);
    EXPECT_EQ(copiedAlt->getMode(), csDeviceRGB);
}

// Test getDefaultColor sets default color values
TEST_F(GfxICCBasedColorSpaceTest_461, GetDefaultColorSetsValues_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    GfxColor color;
    iccCS->getDefaultColor(&color);
    // Default color should be set (typically 0 for each component)
    // We just verify it doesn't crash and produces some values
    for (int i = 0; i < 3; i++) {
        // Values should be within valid GfxColorComp range
        EXPECT_GE(color.c[i], 0);
    }
}

// Test getGray produces a valid gray value
TEST_F(GfxICCBasedColorSpaceTest_461, GetGrayProducesValidValue_461) {
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(1, std::move(altCS), &ref);
    
    GfxColor color;
    iccCS->getDefaultColor(&color);
    
    GfxGray gray;
    iccCS->getGray(&color, &gray);
    // Gray should be a valid value
    EXPECT_GE(gray, 0);
}

// Test getRGB produces valid RGB values
TEST_F(GfxICCBasedColorSpaceTest_461, GetRGBProducesValidValues_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    GfxColor color;
    iccCS->getDefaultColor(&color);
    
    GfxRGB rgb;
    iccCS->getRGB(&color, &rgb);
    // RGB values should be set
    EXPECT_GE(rgb.r, 0);
    EXPECT_GE(rgb.g, 0);
    EXPECT_GE(rgb.b, 0);
}

// Test getCMYK produces valid CMYK values
TEST_F(GfxICCBasedColorSpaceTest_461, GetCMYKProducesValidValues_461) {
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(4, std::move(altCS), &ref);
    
    GfxColor color;
    iccCS->getDefaultColor(&color);
    
    GfxCMYK cmyk;
    iccCS->getCMYK(&color, &cmyk);
    EXPECT_GE(cmyk.c, 0);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_GE(cmyk.y, 0);
    EXPECT_GE(cmyk.k, 0);
}

// Test getDefaultRanges provides valid range information
TEST_F(GfxICCBasedColorSpaceTest_461, GetDefaultRangesProducesValidRanges_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    double decodeLow[4] = {0};
    double decodeRange[4] = {0};
    
    iccCS->getDefaultRanges(decodeLow, decodeRange, 255);
    
    // Ranges should have been populated
    for (int i = 0; i < 3; i++) {
        // decodeRange should be non-negative typically
        EXPECT_GE(decodeRange[i], 0.0);
    }
}

// Test that getAlt on a copy returns a different pointer (deep copy)
TEST_F(GfxICCBasedColorSpaceTest_461, CopyAltIsDifferentPointer_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxColorSpace* originalAltPtr = altCS.get();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    auto copied = iccCS->copyAsOwnType();
    ASSERT_NE(copied, nullptr);
    
    GfxColorSpace* copiedAlt = copied->getAlt();
    GfxColorSpace* origAlt = iccCS->getAlt();
    
    // The copied alt should be a different object
    EXPECT_NE(copiedAlt, origAlt);
    // But should have the same mode
    EXPECT_EQ(copiedAlt->getMode(), origAlt->getMode());
}

// Test with DeviceGray alternate color space
TEST_F(GfxICCBasedColorSpaceTest_461, GetAltWithDeviceGray_461) {
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(1, std::move(altCS), &ref);
    
    GfxColorSpace* alt = iccCS->getAlt();
    ASSERT_NE(alt, nullptr);
    EXPECT_EQ(alt->getMode(), csDeviceGray);
}

// Test with DeviceCMYK alternate color space
TEST_F(GfxICCBasedColorSpaceTest_461, GetAltWithDeviceCMYK_461) {
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(4, std::move(altCS), &ref);
    
    GfxColorSpace* alt = iccCS->getAlt();
    ASSERT_NE(alt, nullptr);
    EXPECT_EQ(alt->getMode(), csDeviceCMYK);
}

// Test getPostScriptCSA returns something (may be nullptr if not set)
TEST_F(GfxICCBasedColorSpaceTest_461, GetPostScriptCSAInitiallyNull_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    // Without setting up the PSA, it should be nullptr or a valid string
    // Just verify it doesn't crash
    char* pscsa = iccCS->getPostScriptCSA();
    // No crash is the test
    (void)pscsa;
}

// Test getProfile initially returns empty/null profile
TEST_F(GfxICCBasedColorSpaceTest_461, GetProfileInitiallyEmpty_461) {
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    Ref ref = Ref::INVALID();
    auto iccCS = std::make_unique<GfxICCBasedColorSpace>(3, std::move(altCS), &ref);
    
    auto profile = iccCS->getProfile();
    // Profile should be null/empty when not set
    EXPECT_EQ(profile.get(), nullptr);
}
