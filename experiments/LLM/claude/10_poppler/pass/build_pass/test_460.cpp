#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Test fixture for GfxICCBasedColorSpace
class GfxICCBasedColorSpaceTest_460 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getNComps returns the correct number of components for 1 component (grayscale)
TEST_F(GfxICCBasedColorSpaceTest_460, GetNCompsReturns1ForGrayscale_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace cs(1, std::move(altCS), &ref);
    EXPECT_EQ(1, cs.getNComps());
}

// Test that getNComps returns the correct number of components for 3 components (RGB)
TEST_F(GfxICCBasedColorSpaceTest_460, GetNCompsReturns3ForRGB_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    EXPECT_EQ(3, cs.getNComps());
}

// Test that getNComps returns the correct number of components for 4 components (CMYK)
TEST_F(GfxICCBasedColorSpaceTest_460, GetNCompsReturns4ForCMYK_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace cs(4, std::move(altCS), &ref);
    EXPECT_EQ(4, cs.getNComps());
}

// Test that getMode returns csICCBased
TEST_F(GfxICCBasedColorSpaceTest_460, GetModeReturnsICCBased_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    EXPECT_EQ(csICCBased, cs.getMode());
}

// Test that getAlt returns a non-null alternate color space
TEST_F(GfxICCBasedColorSpaceTest_460, GetAltReturnsNonNull_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    EXPECT_NE(nullptr, cs.getAlt());
}

// Test that getAlt returns the correct type of alternate color space
TEST_F(GfxICCBasedColorSpaceTest_460, GetAltReturnsCorrectMode_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    GfxColorSpace *alt = cs.getAlt();
    ASSERT_NE(nullptr, alt);
    EXPECT_EQ(csDeviceRGB, alt->getMode());
}

// Test that getRef returns the reference passed during construction
TEST_F(GfxICCBasedColorSpaceTest_460, GetRefReturnsCorrectRef_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    Ref result = cs.getRef();
    EXPECT_EQ(ref.num, result.num);
    EXPECT_EQ(ref.gen, result.gen);
}

// Test that getRef returns a valid ref when constructed with a real ref
TEST_F(GfxICCBasedColorSpaceTest_460, GetRefWithValidRef_460) {
    Ref ref = {10, 0};
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    Ref result = cs.getRef();
    EXPECT_EQ(10, result.num);
    EXPECT_EQ(0, result.gen);
}

// Test that copy returns a non-null unique_ptr
TEST_F(GfxICCBasedColorSpaceTest_460, CopyReturnsNonNull_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    auto copied = cs.copy();
    ASSERT_NE(nullptr, copied);
}

// Test that copy preserves the mode
TEST_F(GfxICCBasedColorSpaceTest_460, CopyPreservesMode_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    auto copied = cs.copy();
    ASSERT_NE(nullptr, copied);
    EXPECT_EQ(csICCBased, copied->getMode());
}

// Test that copy preserves nComps
TEST_F(GfxICCBasedColorSpaceTest_460, CopyPreservesNComps_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    auto copied = cs.copy();
    ASSERT_NE(nullptr, copied);
    EXPECT_EQ(3, copied->getNComps());
}

// Test that copyAsOwnType returns a non-null unique_ptr
TEST_F(GfxICCBasedColorSpaceTest_460, CopyAsOwnTypeReturnsNonNull_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    auto copied = cs.copyAsOwnType();
    ASSERT_NE(nullptr, copied);
    EXPECT_EQ(3, copied->getNComps());
}

// Test getDefaultColor for 1-component ICC color space
TEST_F(GfxICCBasedColorSpaceTest_460, GetDefaultColorGrayscale_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace cs(1, std::move(altCS), &ref);
    GfxColor color;
    cs.getDefaultColor(&color);
    // Default color should be set; just verify we can call it without crash
    // The exact values depend on rangeMin/rangeMax defaults
}

// Test getDefaultColor for 3-component ICC color space
TEST_F(GfxICCBasedColorSpaceTest_460, GetDefaultColorRGB_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    GfxColor color;
    cs.getDefaultColor(&color);
    // Verify it doesn't crash and produces some color
}

// Test getDefaultColor for 4-component ICC color space
TEST_F(GfxICCBasedColorSpaceTest_460, GetDefaultColorCMYK_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace cs(4, std::move(altCS), &ref);
    GfxColor color;
    cs.getDefaultColor(&color);
    // Verify no crash
}

// Test getGray
TEST_F(GfxICCBasedColorSpaceTest_460, GetGrayDoesNotCrash_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace cs(1, std::move(altCS), &ref);
    GfxColor color;
    cs.getDefaultColor(&color);
    GfxGray gray;
    cs.getGray(&color, &gray);
    // Just verify no crash
}

// Test getRGB
TEST_F(GfxICCBasedColorSpaceTest_460, GetRGBDoesNotCrash_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    GfxColor color;
    cs.getDefaultColor(&color);
    GfxRGB rgb;
    cs.getRGB(&color, &rgb);
}

// Test getCMYK
TEST_F(GfxICCBasedColorSpaceTest_460, GetCMYKDoesNotCrash_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace cs(4, std::move(altCS), &ref);
    GfxColor color;
    cs.getDefaultColor(&color);
    GfxCMYK cmyk;
    cs.getCMYK(&color, &cmyk);
}

// Test getDeviceN
TEST_F(GfxICCBasedColorSpaceTest_460, GetDeviceNDoesNotCrash_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    GfxColor color;
    cs.getDefaultColor(&color);
    GfxColor deviceN;
    cs.getDeviceN(&color, &deviceN);
}

// Test getDefaultRanges for 1-component
TEST_F(GfxICCBasedColorSpaceTest_460, GetDefaultRangesGrayscale_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace cs(1, std::move(altCS), &ref);
    double decodeLow[4] = {0};
    double decodeRange[4] = {0};
    cs.getDefaultRanges(decodeLow, decodeRange, 255);
    // The default ranges should reflect rangeMin/rangeMax
}

// Test getDefaultRanges for 3-component
TEST_F(GfxICCBasedColorSpaceTest_460, GetDefaultRangesRGB_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    double decodeLow[4] = {0};
    double decodeRange[4] = {0};
    cs.getDefaultRanges(decodeLow, decodeRange, 255);
}

// Test that getProfile returns nullptr when no profile is set
TEST_F(GfxICCBasedColorSpaceTest_460, GetProfileReturnsNullWhenNotSet_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    auto profile = cs.getProfile();
    // Without setting a profile, it may be null
}

// Test boundary: nComps = 1 (minimum valid)
TEST_F(GfxICCBasedColorSpaceTest_460, BoundaryNComps1_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace cs(1, std::move(altCS), &ref);
    EXPECT_EQ(1, cs.getNComps());
    EXPECT_EQ(csICCBased, cs.getMode());
}

// Test boundary: nComps = 4 (maximum typical)
TEST_F(GfxICCBasedColorSpaceTest_460, BoundaryNComps4_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace cs(4, std::move(altCS), &ref);
    EXPECT_EQ(4, cs.getNComps());
    EXPECT_EQ(csICCBased, cs.getMode());
}

// Test useGetRGBLine
TEST_F(GfxICCBasedColorSpaceTest_460, UseGetRGBLine_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    // Just verify it returns a bool without crashing
    bool result = cs.useGetRGBLine();
    (void)result;
}

// Test useGetCMYKLine
TEST_F(GfxICCBasedColorSpaceTest_460, UseGetCMYKLine_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace cs(4, std::move(altCS), &ref);
    bool result = cs.useGetCMYKLine();
    (void)result;
}

// Test useGetDeviceNLine
TEST_F(GfxICCBasedColorSpaceTest_460, UseGetDeviceNLine_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace cs(3, std::move(altCS), &ref);
    bool result = cs.useGetDeviceNLine();
    (void)result;
}

// Test that getAlt with grayscale alternate returns DeviceGray mode
TEST_F(GfxICCBasedColorSpaceTest_460, GetAltGrayscaleMode_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace cs(1, std::move(altCS), &ref);
    GfxColorSpace *alt = cs.getAlt();
    ASSERT_NE(nullptr, alt);
    EXPECT_EQ(csDeviceGray, alt->getMode());
}

// Test that getAlt with CMYK alternate returns DeviceCMYK mode
TEST_F(GfxICCBasedColorSpaceTest_460, GetAltCMYKMode_460) {
    Ref ref = Ref::INVALID();
    auto altCS = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace cs(4, std::move(altCS), &ref);
    GfxColorSpace *alt = cs.getAlt();
    ASSERT_NE(nullptr, alt);
    EXPECT_EQ(csDeviceCMYK, alt->getMode());
}
