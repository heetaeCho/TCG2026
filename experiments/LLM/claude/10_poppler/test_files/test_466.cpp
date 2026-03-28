#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "GfxState.h"

class GfxIndexedColorSpaceTest_466 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<GfxIndexedColorSpace> createIndexedColorSpace(int indexHigh = 255) {
        // Create a base DeviceRGB color space
        auto base = GfxColorSpace::create(csDeviceRGB);
        if (!base) {
            return nullptr;
        }
        auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
        return indexed;
    }
};

// Test that useGetRGBLine returns true
TEST_F(GfxIndexedColorSpaceTest_466, UseGetRGBLineReturnsTrue_466) {
    auto cs = createIndexedColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_TRUE(cs->useGetRGBLine());
}

// Test that getMode returns csIndexed
TEST_F(GfxIndexedColorSpaceTest_466, GetModeReturnsIndexed_466) {
    auto cs = createIndexedColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csIndexed);
}

// Test that getNComps returns 1 for indexed color space
TEST_F(GfxIndexedColorSpaceTest_466, GetNCompsReturnsOne_466) {
    auto cs = createIndexedColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getNComps(), 1);
}

// Test getIndexHigh returns the value set in constructor
TEST_F(GfxIndexedColorSpaceTest_466, GetIndexHighReturnsCorrectValue_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 255);
}

// Test getIndexHigh with different value
TEST_F(GfxIndexedColorSpaceTest_466, GetIndexHighReturnsDifferentValue_466) {
    auto cs = createIndexedColorSpace(127);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 127);
}

// Test getIndexHigh with zero
TEST_F(GfxIndexedColorSpaceTest_466, GetIndexHighReturnsZero_466) {
    auto cs = createIndexedColorSpace(0);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 0);
}

// Test that getBase returns non-null
TEST_F(GfxIndexedColorSpaceTest_466, GetBaseReturnsNonNull_466) {
    auto cs = createIndexedColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_NE(cs->getBase(), nullptr);
}

// Test that getBase returns DeviceRGB mode
TEST_F(GfxIndexedColorSpaceTest_466, GetBaseReturnsDeviceRGB_466) {
    auto cs = createIndexedColorSpace();
    ASSERT_NE(cs, nullptr);
    GfxColorSpace* base = cs->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceRGB);
}

// Test that getLookup returns non-null pointer
TEST_F(GfxIndexedColorSpaceTest_466, GetLookupReturnsNonNull_466) {
    auto cs = createIndexedColorSpace();
    ASSERT_NE(cs, nullptr);
    EXPECT_NE(cs->getLookup(), nullptr);
}

// Test getDefaultColor
TEST_F(GfxIndexedColorSpaceTest_466, GetDefaultColorSetsValue_466) {
    auto cs = createIndexedColorSpace();
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    cs->getDefaultColor(&color);
    // For indexed color space, default color component 0 should be 0
    EXPECT_EQ(color.c[0], 0);
}

// Test copy creates a valid copy
TEST_F(GfxIndexedColorSpaceTest_466, CopyCreatesValidCopy_466) {
    auto cs = createIndexedColorSpace(200);
    ASSERT_NE(cs, nullptr);
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csIndexed);

    // Cast to GfxIndexedColorSpace to check properties
    GfxIndexedColorSpace* copiedIndexed = dynamic_cast<GfxIndexedColorSpace*>(copied.get());
    ASSERT_NE(copiedIndexed, nullptr);
    EXPECT_EQ(copiedIndexed->getIndexHigh(), 200);
    EXPECT_NE(copiedIndexed->getBase(), nullptr);
    EXPECT_NE(copiedIndexed->getLookup(), nullptr);
}

// Test useGetCMYKLine
TEST_F(GfxIndexedColorSpaceTest_466, UseGetCMYKLine_466) {
    auto cs = createIndexedColorSpace();
    ASSERT_NE(cs, nullptr);
    // The result depends on the base color space's useGetCMYKLine
    // For DeviceRGB base, this should be a valid boolean
    bool result = cs->useGetCMYKLine();
    // Just verify it doesn't crash; the actual value depends on implementation
    (void)result;
}

// Test useGetDeviceNLine
TEST_F(GfxIndexedColorSpaceTest_466, UseGetDeviceNLine_466) {
    auto cs = createIndexedColorSpace();
    ASSERT_NE(cs, nullptr);
    bool result = cs->useGetDeviceNLine();
    (void)result;
}

// Test getDefaultRanges
TEST_F(GfxIndexedColorSpaceTest_466, GetDefaultRangesSetCorrectValues_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    double decodeLow[1];
    double decodeRange[1];
    cs->getDefaultRanges(decodeLow, decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 255.0);
}

// Test getDefaultRanges with different maxImgPixel
TEST_F(GfxIndexedColorSpaceTest_466, GetDefaultRangesWithDifferentMaxImgPixel_466) {
    auto cs = createIndexedColorSpace(100);
    ASSERT_NE(cs, nullptr);
    double decodeLow[1];
    double decodeRange[1];
    cs->getDefaultRanges(decodeLow, decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 100.0);
}

// Test getGray with a color
TEST_F(GfxIndexedColorSpaceTest_466, GetGrayProducesResult_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    color.c[0] = 0;  // Index 0
    GfxGray gray;
    cs->getGray(&color, &gray);
    // Just verify it doesn't crash
}

// Test getRGB with a color
TEST_F(GfxIndexedColorSpaceTest_466, GetRGBProducesResult_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    color.c[0] = 0;  // Index 0
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Just verify it doesn't crash
}

// Test getCMYK with a color
TEST_F(GfxIndexedColorSpaceTest_466, GetCMYKProducesResult_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    color.c[0] = 0;  // Index 0
    GfxCMYK cmyk;
    cs->getCMYK(&color, &cmyk);
    // Just verify it doesn't crash
}

// Test mapColorToBase
TEST_F(GfxIndexedColorSpaceTest_466, MapColorToBaseProducesResult_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    color.c[0] = 0;
    GfxColor baseColor;
    const GfxColor* result = cs->mapColorToBase(&color, &baseColor);
    ASSERT_NE(result, nullptr);
}

// Test getOverprintMask
TEST_F(GfxIndexedColorSpaceTest_466, GetOverprintMaskReturnsValue_466) {
    auto cs = createIndexedColorSpace();
    ASSERT_NE(cs, nullptr);
    unsigned int mask = cs->getOverprintMask();
    // For DeviceRGB base, overprint mask should be non-zero
    // Just ensure it doesn't crash
    (void)mask;
}

// Test with indexHigh of 1 (minimum meaningful)
TEST_F(GfxIndexedColorSpaceTest_466, IndexHighOfOne_466) {
    auto cs = createIndexedColorSpace(1);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 1);
    EXPECT_EQ(cs->getNComps(), 1);
}

// Test getRGBLine with unsigned int output
TEST_F(GfxIndexedColorSpaceTest_466, GetRGBLineUintOutput_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    unsigned char input[3] = {0, 1, 2};
    unsigned int output[3] = {0, 0, 0};
    cs->getRGBLine(input, output, 3);
    // Just verify it doesn't crash
}

// Test getRGBLine with unsigned char output
TEST_F(GfxIndexedColorSpaceTest_466, GetRGBLineUcharOutput_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    unsigned char input[3] = {0, 1, 2};
    unsigned char output[9] = {0}; // 3 pixels * 3 components (RGB)
    cs->getRGBLine(input, output, 3);
    // Just verify it doesn't crash
}

// Test getRGBXLine
TEST_F(GfxIndexedColorSpaceTest_466, GetRGBXLine_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    unsigned char input[3] = {0, 1, 2};
    unsigned char output[12] = {0}; // 3 pixels * 4 components (RGBX)
    cs->getRGBXLine(input, output, 3);
    // Just verify it doesn't crash
}

// Test getCMYKLine
TEST_F(GfxIndexedColorSpaceTest_466, GetCMYKLine_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    unsigned char input[3] = {0, 1, 2};
    unsigned char output[12] = {0}; // 3 pixels * 4 components (CMYK)
    cs->getCMYKLine(input, output, 3);
    // Just verify it doesn't crash
}

// Test getDeviceNLine
TEST_F(GfxIndexedColorSpaceTest_466, GetDeviceNLine_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    unsigned char input[3] = {0, 1, 2};
    unsigned char output[3 * (SPOT_NCOMPS + 4)] = {0};
    cs->getDeviceNLine(input, output, 3);
    // Just verify it doesn't crash
}

// Test with DeviceGray base
TEST_F(GfxIndexedColorSpaceTest_466, WithDeviceGrayBase_466) {
    auto base = GfxColorSpace::create(csDeviceGray);
    ASSERT_NE(base, nullptr);
    auto cs = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csIndexed);
    EXPECT_EQ(cs->getNComps(), 1);
    EXPECT_EQ(cs->getIndexHigh(), 255);
    EXPECT_NE(cs->getBase(), nullptr);
    EXPECT_EQ(cs->getBase()->getMode(), csDeviceGray);
}

// Test with DeviceCMYK base
TEST_F(GfxIndexedColorSpaceTest_466, WithDeviceCMYKBase_466) {
    auto base = GfxColorSpace::create(csDeviceCMYK);
    ASSERT_NE(base, nullptr);
    auto cs = std::make_unique<GfxIndexedColorSpace>(std::move(base), 127);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csIndexed);
    EXPECT_EQ(cs->getIndexHigh(), 127);
    EXPECT_NE(cs->getBase(), nullptr);
    EXPECT_EQ(cs->getBase()->getMode(), csDeviceCMYK);
}

// Test getDeviceN
TEST_F(GfxIndexedColorSpaceTest_466, GetDeviceNProducesResult_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    cs->getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash
}

// Test that copy preserves useGetRGBLine behavior
TEST_F(GfxIndexedColorSpaceTest_466, CopyPreservesUseGetRGBLine_466) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->useGetRGBLine());
}
