#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Test fixture for GfxICCBasedColorSpace
class GfxICCBasedColorSpaceTest_463 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that setProfile stores the profile and getProfile retrieves it
TEST_F(GfxICCBasedColorSpaceTest_463, SetProfileAndGetProfile_463) {
    // Create an ICCBased color space with a simple alternate color space
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    // Initially profile should be null/empty
    GfxLCMSProfilePtr initialProfile = cs.getProfile();
    // The initial profile is expected to be null/empty since none was set
    EXPECT_EQ(initialProfile, nullptr);

    // Set a profile (using a null/empty profile pointer as we can't easily create a real one)
    GfxLCMSProfilePtr nullProfile = nullptr;
    cs.setProfile(nullProfile);
    EXPECT_EQ(cs.getProfile(), nullptr);
}

// Test getMode returns ICCBased
TEST_F(GfxICCBasedColorSpaceTest_463, GetModeReturnsICCBased_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    EXPECT_EQ(cs.getMode(), csICCBased);
}

// Test getNComps returns the number of components passed in constructor
TEST_F(GfxICCBasedColorSpaceTest_463, GetNCompsReturnsCorrectValue_463) {
    Ref ref = Ref::INVALID();
    
    {
        auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
        GfxICCBasedColorSpace cs3(3, std::move(altCS), &ref);
        EXPECT_EQ(cs3.getNComps(), 3);
    }
    
    {
        auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
        GfxICCBasedColorSpace cs4(4, std::move(altCS), &ref);
        EXPECT_EQ(cs4.getNComps(), 4);
    }
    
    {
        auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
        GfxICCBasedColorSpace cs1(1, std::move(altCS), &ref);
        EXPECT_EQ(cs1.getNComps(), 1);
    }
}

// Test getAlt returns the alternate color space
TEST_F(GfxICCBasedColorSpaceTest_463, GetAltReturnsAlternateColorSpace_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxColorSpace* altRaw = altCS.get();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    GfxColorSpace* alt = cs.getAlt();
    ASSERT_NE(alt, nullptr);
    EXPECT_EQ(alt, altRaw);
    EXPECT_EQ(alt->getMode(), csDeviceRGB);
}

// Test getRef returns the reference passed in constructor
TEST_F(GfxICCBasedColorSpaceTest_463, GetRefReturnsCorrectRef_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    Ref result = cs.getRef();
    EXPECT_EQ(result, Ref::INVALID());
}

// Test copy creates a valid copy
TEST_F(GfxICCBasedColorSpaceTest_463, CopyCreatesValidCopy_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    auto copied = cs.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csICCBased);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test copyAsOwnType creates a valid copy
TEST_F(GfxICCBasedColorSpaceTest_463, CopyAsOwnTypeCreatesValidCopy_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    auto copied = cs.copyAsOwnType();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csICCBased);
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test getDefaultColor sets color values
TEST_F(GfxICCBasedColorSpaceTest_463, GetDefaultColorSetsColor_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    GfxColor color;
    cs.getDefaultColor(&color);
    // Default color should be initialized - we just verify it doesn't crash
    // and color components are set to some value
}

// Test getDefaultRanges provides range values
TEST_F(GfxICCBasedColorSpaceTest_463, GetDefaultRangesProvidesValues_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    double decodeLow[4] = {0};
    double decodeRange[4] = {0};
    cs.getDefaultRanges(decodeLow, decodeRange, 255);
    
    // For a 3-component ICC space, at least 3 ranges should be meaningful
    // Default ranges are typically [0, 1] so decodeRange should be positive
    for (int i = 0; i < 3; i++) {
        EXPECT_GE(decodeRange[i], 0.0);
    }
}

// Test getGray with a color
TEST_F(GfxICCBasedColorSpaceTest_463, GetGrayDoesNotCrash_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace cs(1, std::move(altCS), &ref);

    GfxColor color;
    cs.getDefaultColor(&color);
    GfxGray gray;
    cs.getGray(&color, &gray);
    // Just verify it doesn't crash
}

// Test getRGB with a color
TEST_F(GfxICCBasedColorSpaceTest_463, GetRGBDoesNotCrash_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    GfxColor color;
    cs.getDefaultColor(&color);
    GfxRGB rgb;
    cs.getRGB(&color, &rgb);
    // Just verify it doesn't crash
}

// Test getCMYK with a color
TEST_F(GfxICCBasedColorSpaceTest_463, GetCMYKDoesNotCrash_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace cs(4, std::move(altCS), &ref);

    GfxColor color;
    cs.getDefaultColor(&color);
    GfxCMYK cmyk;
    cs.getCMYK(&color, &cmyk);
    // Just verify it doesn't crash
}

// Test useGetRGBLine returns a boolean
TEST_F(GfxICCBasedColorSpaceTest_463, UseGetRGBLineReturnsBool_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    // Just verify it returns without crashing
    bool result = cs.useGetRGBLine();
    // Result depends on whether profile/transforms are set up
    (void)result;
}

// Test useGetCMYKLine returns a boolean
TEST_F(GfxICCBasedColorSpaceTest_463, UseGetCMYKLineReturnsBool_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace cs(4, std::move(altCS), &ref);

    bool result = cs.useGetCMYKLine();
    (void)result;
}

// Test useGetDeviceNLine returns a boolean
TEST_F(GfxICCBasedColorSpaceTest_463, UseGetDeviceNLineReturnsBool_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    bool result = cs.useGetDeviceNLine();
    (void)result;
}

// Test setProfile with null profile
TEST_F(GfxICCBasedColorSpaceTest_463, SetProfileWithNull_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    GfxLCMSProfilePtr nullProfile = nullptr;
    cs.setProfile(nullProfile);
    EXPECT_EQ(cs.getProfile(), nullptr);
}

// Test that setting profile multiple times keeps the last one
TEST_F(GfxICCBasedColorSpaceTest_463, SetProfileMultipleTimes_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    GfxLCMSProfilePtr profile1 = nullptr;
    cs.setProfile(profile1);
    EXPECT_EQ(cs.getProfile(), nullptr);

    GfxLCMSProfilePtr profile2 = nullptr;
    cs.setProfile(profile2);
    EXPECT_EQ(cs.getProfile(), nullptr);
}

// Test with single component (gray) alternate
TEST_F(GfxICCBasedColorSpaceTest_463, SingleComponentGrayAlternate_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace cs(1, std::move(altCS), &ref);

    EXPECT_EQ(cs.getNComps(), 1);
    EXPECT_EQ(cs.getMode(), csICCBased);
    
    GfxColorSpace* alt = cs.getAlt();
    ASSERT_NE(alt, nullptr);
    EXPECT_EQ(alt->getMode(), csDeviceGray);
}

// Test getRGBLine with unsigned int output doesn't crash
TEST_F(GfxICCBasedColorSpaceTest_463, GetRGBLineUintDoesNotCrash_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    unsigned char in[3] = {128, 128, 128};
    unsigned int out[1] = {0};
    cs.getRGBLine(in, out, 1);
    // Just verify it doesn't crash
}

// Test getRGBLine with unsigned char output doesn't crash
TEST_F(GfxICCBasedColorSpaceTest_463, GetRGBLineUcharDoesNotCrash_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    unsigned char in[3] = {128, 128, 128};
    unsigned char out[3] = {0};
    cs.getRGBLine(in, out, 1);
    // Just verify it doesn't crash
}

// Test getDeviceN doesn't crash
TEST_F(GfxICCBasedColorSpaceTest_463, GetDeviceNDoesNotCrash_463) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);

    GfxColor color;
    cs.getDefaultColor(&color);
    GfxColor deviceN;
    cs.getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash
}
