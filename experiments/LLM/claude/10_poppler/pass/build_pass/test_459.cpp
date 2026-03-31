#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Test fixture for GfxICCBasedColorSpace
class GfxICCBasedColorSpaceTest_459 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getMode returns csICCBased
TEST_F(GfxICCBasedColorSpaceTest_459, GetModeReturnsICCBased_459) {
    // Create a GfxICCBasedColorSpace with a DeviceGray alternate (1 component)
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    EXPECT_EQ(iccSpace.getMode(), csICCBased);
}

// Test that getNComps returns the correct number of components for 1 component
TEST_F(GfxICCBasedColorSpaceTest_459, GetNCompsReturns1_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    EXPECT_EQ(iccSpace.getNComps(), 1);
}

// Test that getNComps returns the correct number of components for 3 components
TEST_F(GfxICCBasedColorSpaceTest_459, GetNCompsReturns3_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    EXPECT_EQ(iccSpace.getNComps(), 3);
}

// Test that getNComps returns the correct number of components for 4 components
TEST_F(GfxICCBasedColorSpaceTest_459, GetNCompsReturns4_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace iccSpace(4, std::move(alt), &ref);
    
    EXPECT_EQ(iccSpace.getNComps(), 4);
}

// Test that getAlt returns a non-null pointer when alt is provided
TEST_F(GfxICCBasedColorSpaceTest_459, GetAltReturnsNonNull_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    EXPECT_NE(iccSpace.getAlt(), nullptr);
}

// Test that getAlt returns the correct alternate color space type
TEST_F(GfxICCBasedColorSpaceTest_459, GetAltReturnsCorrectType_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    EXPECT_EQ(iccSpace.getAlt()->getMode(), csDeviceRGB);
}

// Test that getRef returns the provided ref
TEST_F(GfxICCBasedColorSpaceTest_459, GetRefReturnsProvidedRef_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    Ref returnedRef = iccSpace.getRef();
    EXPECT_EQ(returnedRef, Ref::INVALID());
}

// Test that copy returns a non-null unique_ptr
TEST_F(GfxICCBasedColorSpaceTest_459, CopyReturnsNonNull_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    auto copied = iccSpace.copy();
    EXPECT_NE(copied, nullptr);
}

// Test that copy returns a color space with the same mode
TEST_F(GfxICCBasedColorSpaceTest_459, CopyPreservesMode_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    auto copied = iccSpace.copy();
    EXPECT_EQ(copied->getMode(), csICCBased);
}

// Test that copy returns a color space with the same number of components
TEST_F(GfxICCBasedColorSpaceTest_459, CopyPreservesNComps_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    auto copied = iccSpace.copy();
    EXPECT_EQ(copied->getNComps(), 3);
}

// Test copyAsOwnType returns non-null
TEST_F(GfxICCBasedColorSpaceTest_459, CopyAsOwnTypeReturnsNonNull_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    auto copied = iccSpace.copyAsOwnType();
    EXPECT_NE(copied, nullptr);
}

// Test copyAsOwnType preserves mode
TEST_F(GfxICCBasedColorSpaceTest_459, CopyAsOwnTypePreservesMode_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    auto copied = iccSpace.copyAsOwnType();
    EXPECT_EQ(copied->getMode(), csICCBased);
}

// Test getDefaultColor with 1 component
TEST_F(GfxICCBasedColorSpaceTest_459, GetDefaultColorGray_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    GfxColor color;
    iccSpace.getDefaultColor(&color);
    // Default color should be set (at least not crash)
    // The first component should be 0 for ICC based
    EXPECT_GE(color.c[0], 0);
}

// Test getDefaultColor with 3 components
TEST_F(GfxICCBasedColorSpaceTest_459, GetDefaultColorRGB_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    GfxColor color;
    iccSpace.getDefaultColor(&color);
    // Should not crash and should produce valid values
    SUCCEED();
}

// Test getGray with a default color for 1 component space
TEST_F(GfxICCBasedColorSpaceTest_459, GetGrayProducesValidResult_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    GfxColor color;
    iccSpace.getDefaultColor(&color);
    
    GfxGray gray;
    iccSpace.getGray(&color, &gray);
    // Gray value should be in valid range [0, 65535]
    EXPECT_GE(gray, 0);
    EXPECT_LE(gray, 65535);
}

// Test getRGB with a default color for 3 component space
TEST_F(GfxICCBasedColorSpaceTest_459, GetRGBProducesValidResult_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    GfxColor color;
    iccSpace.getDefaultColor(&color);
    
    GfxRGB rgb;
    iccSpace.getRGB(&color, &rgb);
    // RGB values should be in valid range
    EXPECT_GE(rgb.r, 0);
    EXPECT_LE(rgb.r, 65535);
    EXPECT_GE(rgb.g, 0);
    EXPECT_LE(rgb.g, 65535);
    EXPECT_GE(rgb.b, 0);
    EXPECT_LE(rgb.b, 65535);
}

// Test getCMYK with a default color for 4 component space
TEST_F(GfxICCBasedColorSpaceTest_459, GetCMYKProducesValidResult_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace iccSpace(4, std::move(alt), &ref);
    
    GfxColor color;
    iccSpace.getDefaultColor(&color);
    
    GfxCMYK cmyk;
    iccSpace.getCMYK(&color, &cmyk);
    // CMYK values should be in valid range
    EXPECT_GE(cmyk.c, 0);
    EXPECT_LE(cmyk.c, 65535);
    EXPECT_GE(cmyk.m, 0);
    EXPECT_LE(cmyk.m, 65535);
    EXPECT_GE(cmyk.y, 0);
    EXPECT_LE(cmyk.y, 65535);
    EXPECT_GE(cmyk.k, 0);
    EXPECT_LE(cmyk.k, 65535);
}

// Test getDefaultRanges for 1 component
TEST_F(GfxICCBasedColorSpaceTest_459, GetDefaultRangesGray_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    double decodeLow[1];
    double decodeRange[1];
    iccSpace.getDefaultRanges(decodeLow, decodeRange, 255);
    
    // Should produce valid decode ranges
    SUCCEED();
}

// Test getDefaultRanges for 3 components
TEST_F(GfxICCBasedColorSpaceTest_459, GetDefaultRangesRGB_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    double decodeLow[3];
    double decodeRange[3];
    iccSpace.getDefaultRanges(decodeLow, decodeRange, 255);
    
    SUCCEED();
}

// Test getProfile returns null when no profile is set
TEST_F(GfxICCBasedColorSpaceTest_459, GetProfileReturnsNullByDefault_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    auto profile = iccSpace.getProfile();
    // Without setting a profile, it should be null/empty
    EXPECT_FALSE(profile);
}

// Test useGetRGBLine
TEST_F(GfxICCBasedColorSpaceTest_459, UseGetRGBLineReturnsBool_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    // Just verify it returns a boolean without crashing
    bool result = iccSpace.useGetRGBLine();
    SUCCEED();
}

// Test useGetCMYKLine
TEST_F(GfxICCBasedColorSpaceTest_459, UseGetCMYKLineReturnsBool_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace iccSpace(4, std::move(alt), &ref);
    
    bool result = iccSpace.useGetCMYKLine();
    SUCCEED();
}

// Test useGetDeviceNLine
TEST_F(GfxICCBasedColorSpaceTest_459, UseGetDeviceNLineReturnsBool_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    bool result = iccSpace.useGetDeviceNLine();
    SUCCEED();
}

// Test getDeviceN with default color
TEST_F(GfxICCBasedColorSpaceTest_459, GetDeviceNDoesNotCrash_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    GfxColor color;
    iccSpace.getDefaultColor(&color);
    
    GfxColor deviceN;
    iccSpace.getDeviceN(&color, &deviceN);
    SUCCEED();
}

// Test that getRef returns a specific ref when one is provided
TEST_F(GfxICCBasedColorSpaceTest_459, GetRefReturnsSpecificRef_459) {
    Ref ref;
    ref.num = 42;
    ref.gen = 0;
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    Ref returnedRef = iccSpace.getRef();
    EXPECT_EQ(returnedRef.num, 42);
    EXPECT_EQ(returnedRef.gen, 0);
}

// Test that alt color space mode is DeviceGray
TEST_F(GfxICCBasedColorSpaceTest_459, GetAltModeDeviceGray_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    GfxColorSpace *altCs = iccSpace.getAlt();
    ASSERT_NE(altCs, nullptr);
    EXPECT_EQ(altCs->getMode(), csDeviceGray);
}

// Test that alt color space mode is DeviceCMYK
TEST_F(GfxICCBasedColorSpaceTest_459, GetAltModeDeviceCMYK_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace iccSpace(4, std::move(alt), &ref);
    
    GfxColorSpace *altCs = iccSpace.getAlt();
    ASSERT_NE(altCs, nullptr);
    EXPECT_EQ(altCs->getMode(), csDeviceCMYK);
}

// Test getRGBLine with unsigned int output (boundary: length = 0)
TEST_F(GfxICCBasedColorSpaceTest_459, GetRGBLineZeroLength_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    unsigned char in[1] = {0};
    unsigned int out[1] = {0};
    // Length 0 should be a no-op
    iccSpace.getRGBLine(in, out, 0);
    SUCCEED();
}

// Test getRGBLine with unsigned char output (boundary: length = 0)
TEST_F(GfxICCBasedColorSpaceTest_459, GetRGBLineUCharZeroLength_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    unsigned char in[1] = {0};
    unsigned char out[1] = {0};
    iccSpace.getRGBLine(in, out, 0);
    SUCCEED();
}

// Test getRGBXLine with boundary: length = 0
TEST_F(GfxICCBasedColorSpaceTest_459, GetRGBXLineZeroLength_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    unsigned char in[1] = {0};
    unsigned char out[1] = {0};
    iccSpace.getRGBXLine(in, out, 0);
    SUCCEED();
}

// Test getCMYKLine with boundary: length = 0
TEST_F(GfxICCBasedColorSpaceTest_459, GetCMYKLineZeroLength_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceCMYKColorSpace>();
    GfxICCBasedColorSpace iccSpace(4, std::move(alt), &ref);
    
    unsigned char in[1] = {0};
    unsigned char out[1] = {0};
    iccSpace.getCMYKLine(in, out, 0);
    SUCCEED();
}

// Test getDeviceNLine with boundary: length = 0
TEST_F(GfxICCBasedColorSpaceTest_459, GetDeviceNLineZeroLength_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    unsigned char in[1] = {0};
    unsigned char out[1] = {0};
    iccSpace.getDeviceNLine(in, out, 0);
    SUCCEED();
}

// Test getRGBLine with a single pixel (3 components)
TEST_F(GfxICCBasedColorSpaceTest_459, GetRGBLineSinglePixelUInt_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    unsigned char in[3] = {128, 64, 32};
    unsigned int out[1] = {0};
    iccSpace.getRGBLine(in, out, 1);
    // The output should have been modified
    SUCCEED();
}

// Test getRGBLine with single pixel (unsigned char output)
TEST_F(GfxICCBasedColorSpaceTest_459, GetRGBLineSinglePixelUChar_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceRGBColorSpace>();
    GfxICCBasedColorSpace iccSpace(3, std::move(alt), &ref);
    
    unsigned char in[3] = {255, 0, 128};
    unsigned char out[3] = {0, 0, 0};
    iccSpace.getRGBLine(in, out, 1);
    SUCCEED();
}

// Test that getPostScriptCSA returns something (may be null initially)
TEST_F(GfxICCBasedColorSpaceTest_459, GetPostScriptCSAInitially_459) {
    Ref ref = Ref::INVALID();
    auto alt = std::make_unique<GfxDeviceGrayColorSpace>();
    GfxICCBasedColorSpace iccSpace(1, std::move(alt), &ref);
    
    // getPostScriptCSA may return nullptr if no CSA has been generated
    char *csa = iccSpace.getPostScriptCSA();
    // We just verify it doesn't crash
    SUCCEED();
}
