#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

// Test fixture for GfxIndexedColorSpace
class GfxIndexedColorSpaceTest_468 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a GfxIndexedColorSpace with a DeviceRGB base
    std::unique_ptr<GfxIndexedColorSpace> createIndexedRGB(int indexHigh) {
        auto base = GfxColorSpace::create(csDeviceRGB);
        if (!base) return nullptr;
        auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
        return indexed;
    }

    // Helper to create a GfxIndexedColorSpace with a DeviceCMYK base
    std::unique_ptr<GfxIndexedColorSpace> createIndexedCMYK(int indexHigh) {
        auto base = GfxColorSpace::create(csDeviceCMYK);
        if (!base) return nullptr;
        auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
        return indexed;
    }

    // Helper to create a GfxIndexedColorSpace with a DeviceGray base
    std::unique_ptr<GfxIndexedColorSpace> createIndexedGray(int indexHigh) {
        auto base = GfxColorSpace::create(csDeviceGray);
        if (!base) return nullptr;
        auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
        return indexed;
    }
};

// Test that getMode returns csIndexed
TEST_F(GfxIndexedColorSpaceTest_468, GetModeReturnsIndexed_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csIndexed);
}

// Test that getNComps returns 1 (indexed color spaces have 1 component)
TEST_F(GfxIndexedColorSpaceTest_468, GetNCompsReturnsOne_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getNComps(), 1);
}

// Test that getIndexHigh returns the value passed in constructor
TEST_F(GfxIndexedColorSpaceTest_468, GetIndexHighReturnsCorrectValue_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 255);
}

// Test with a different indexHigh value
TEST_F(GfxIndexedColorSpaceTest_468, GetIndexHighWithSmallValue_468) {
    auto cs = createIndexedRGB(15);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 15);
}

// Test indexHigh of zero
TEST_F(GfxIndexedColorSpaceTest_468, GetIndexHighZero_468) {
    auto cs = createIndexedRGB(0);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 0);
}

// Test that getBase returns a non-null pointer
TEST_F(GfxIndexedColorSpaceTest_468, GetBaseReturnsNonNull_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    GfxColorSpace* base = cs->getBase();
    ASSERT_NE(base, nullptr);
}

// Test that the base color space has the expected mode
TEST_F(GfxIndexedColorSpaceTest_468, GetBaseReturnsRGBBase_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    GfxColorSpace* base = cs->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceRGB);
}

// Test base with CMYK
TEST_F(GfxIndexedColorSpaceTest_468, GetBaseReturnsCMYKBase_468) {
    auto cs = createIndexedCMYK(255);
    ASSERT_NE(cs, nullptr);
    GfxColorSpace* base = cs->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceCMYK);
}

// Test that getLookup returns a non-null pointer
TEST_F(GfxIndexedColorSpaceTest_468, GetLookupReturnsNonNull_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    unsigned char* lookup = cs->getLookup();
    EXPECT_NE(lookup, nullptr);
}

// Test useGetRGBLine
TEST_F(GfxIndexedColorSpaceTest_468, UseGetRGBLineReturnsTrue_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    // The base DeviceRGB should support getRGBLine
    EXPECT_TRUE(cs->useGetRGBLine());
}

// Test useGetDeviceNLine returns true
TEST_F(GfxIndexedColorSpaceTest_468, UseGetDeviceNLineReturnsTrue_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_TRUE(cs->useGetDeviceNLine());
}

// Test useGetCMYKLine
TEST_F(GfxIndexedColorSpaceTest_468, UseGetCMYKLine_468) {
    auto cs = createIndexedCMYK(255);
    ASSERT_NE(cs, nullptr);
    // CMYK base should support getCMYKLine
    EXPECT_TRUE(cs->useGetCMYKLine());
}

// Test copy creates a valid copy
TEST_F(GfxIndexedColorSpaceTest_468, CopyCreatesValidCopy_468) {
    auto cs = createIndexedRGB(127);
    ASSERT_NE(cs, nullptr);
    auto csCopy = cs->copy();
    ASSERT_NE(csCopy, nullptr);
    EXPECT_EQ(csCopy->getMode(), csIndexed);

    // Cast to GfxIndexedColorSpace to check properties
    GfxIndexedColorSpace* copiedIndexed = dynamic_cast<GfxIndexedColorSpace*>(csCopy.get());
    ASSERT_NE(copiedIndexed, nullptr);
    EXPECT_EQ(copiedIndexed->getIndexHigh(), 127);
    EXPECT_EQ(copiedIndexed->getNComps(), 1);
}

// Test getDefaultColor
TEST_F(GfxIndexedColorSpaceTest_468, GetDefaultColor_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    cs->getDefaultColor(&color);
    // Default color for indexed should have first component as 0
    EXPECT_EQ(color.c[0], 0);
}

// Test getGray with index 0
TEST_F(GfxIndexedColorSpaceTest_468, GetGrayWithZeroIndex_468) {
    auto cs = createIndexedGray(255);
    ASSERT_NE(cs, nullptr);
    
    // Set lookup values - all zeros initially
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    cs->getGray(&color, &gray);
    // Should succeed without crashing; exact value depends on lookup
}

// Test getRGB with index 0
TEST_F(GfxIndexedColorSpaceTest_468, GetRGBWithZeroIndex_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Should succeed without crashing
}

// Test getCMYK with index 0
TEST_F(GfxIndexedColorSpaceTest_468, GetCMYKWithZeroIndex_468) {
    auto cs = createIndexedCMYK(255);
    ASSERT_NE(cs, nullptr);
    
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    cs->getCMYK(&color, &cmyk);
    // Should succeed without crashing
}

// Test getDeviceN
TEST_F(GfxIndexedColorSpaceTest_468, GetDeviceNWithZeroIndex_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    cs->getDeviceN(&color, &deviceN);
    // Should succeed without crashing
}

// Test getDefaultRanges
TEST_F(GfxIndexedColorSpaceTest_468, GetDefaultRanges_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    
    double decodeLow, decodeRange;
    cs->getDefaultRanges(&decodeLow, &decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow, 0.0);
    EXPECT_DOUBLE_EQ(decodeRange, 255.0);
}

// Test getDefaultRanges with different maxImgPixel
TEST_F(GfxIndexedColorSpaceTest_468, GetDefaultRangesWithDifferentMaxPixel_468) {
    auto cs = createIndexedRGB(127);
    ASSERT_NE(cs, nullptr);
    
    double decodeLow, decodeRange;
    cs->getDefaultRanges(&decodeLow, &decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow, 0.0);
    // The range should be indexHigh (127)
    EXPECT_DOUBLE_EQ(decodeRange, 127.0);
}

// Test mapColorToBase
TEST_F(GfxIndexedColorSpaceTest_468, MapColorToBase_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    
    GfxColor color;
    color.c[0] = 0;
    GfxColor baseColor;
    const GfxColor* result = cs->mapColorToBase(&color, &baseColor);
    ASSERT_NE(result, nullptr);
}

// Test getRGBLine (unsigned int* out version)
TEST_F(GfxIndexedColorSpaceTest_468, GetRGBLineUintOut_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    
    unsigned char in[3] = {0, 1, 2};
    unsigned int out[3] = {0, 0, 0};
    cs->getRGBLine(in, out, 3);
    // Should complete without crashing
}

// Test getRGBLine (unsigned char* out version)
TEST_F(GfxIndexedColorSpaceTest_468, GetRGBLineUcharOut_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    
    unsigned char in[3] = {0, 1, 2};
    unsigned char out[9] = {0};  // 3 pixels * 3 components (RGB)
    cs->getRGBLine(in, out, 3);
    // Should complete without crashing
}

// Test getRGBXLine
TEST_F(GfxIndexedColorSpaceTest_468, GetRGBXLine_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    
    unsigned char in[3] = {0, 1, 2};
    unsigned char out[12] = {0};  // 3 pixels * 4 components (RGBX)
    cs->getRGBXLine(in, out, 3);
    // Should complete without crashing
}

// Test getCMYKLine
TEST_F(GfxIndexedColorSpaceTest_468, GetCMYKLine_468) {
    auto cs = createIndexedCMYK(255);
    ASSERT_NE(cs, nullptr);
    
    unsigned char in[3] = {0, 1, 2};
    unsigned char out[12] = {0};  // 3 pixels * 4 components (CMYK)
    cs->getCMYKLine(in, out, 3);
    // Should complete without crashing
}

// Test getDeviceNLine
TEST_F(GfxIndexedColorSpaceTest_468, GetDeviceNLine_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    
    unsigned char in[3] = {0, 1, 2};
    unsigned char out[3 * (SPOT_NCOMPS + 4)] = {0};
    cs->getDeviceNLine(in, out, 3);
    // Should complete without crashing
}

// Test getOverprintMask
TEST_F(GfxIndexedColorSpaceTest_468, GetOverprintMask_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    unsigned int mask = cs->getOverprintMask();
    // Should return some valid value; for RGB base it should be non-zero
    EXPECT_NE(mask, 0u);
}

// Test with Gray base
TEST_F(GfxIndexedColorSpaceTest_468, GrayBaseGetMode_468) {
    auto cs = createIndexedGray(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csIndexed);
    GfxColorSpace* base = cs->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceGray);
}

// Test copy preserves base mode
TEST_F(GfxIndexedColorSpaceTest_468, CopyPreservesBaseMode_468) {
    auto cs = createIndexedCMYK(100);
    ASSERT_NE(cs, nullptr);
    auto csCopy = cs->copy();
    ASSERT_NE(csCopy, nullptr);
    
    GfxIndexedColorSpace* copiedIndexed = dynamic_cast<GfxIndexedColorSpace*>(csCopy.get());
    ASSERT_NE(copiedIndexed, nullptr);
    EXPECT_EQ(copiedIndexed->getIndexHigh(), 100);
    GfxColorSpace* base = copiedIndexed->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceCMYK);
}

// Test with single-entry lookup (indexHigh = 0)
TEST_F(GfxIndexedColorSpaceTest_468, SingleEntryLookup_468) {
    auto cs = createIndexedRGB(0);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 0);
    
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Should not crash
}

// Test with large indexHigh boundary
TEST_F(GfxIndexedColorSpaceTest_468, LargeIndexHighBoundary_468) {
    auto cs = createIndexedRGB(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 255);
    
    // Access at boundary
    GfxColor color;
    color.c[0] = dblToCol(255.0);
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Should not crash
}
