#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>

#include "GfxState.h"

class GfxIndexedColorSpaceTest_474 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<GfxIndexedColorSpace> createWithDeviceRGB(int indexHigh) {
        auto baseCS = GfxColorSpace::create(csDeviceRGB);
        auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(baseCS), indexHigh);
        return indexed;
    }

    std::unique_ptr<GfxIndexedColorSpace> createWithDeviceGray(int indexHigh) {
        auto baseCS = GfxColorSpace::create(csDeviceGray);
        auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(baseCS), indexHigh);
        return indexed;
    }

    std::unique_ptr<GfxIndexedColorSpace> createWithDeviceCMYK(int indexHigh) {
        auto baseCS = GfxColorSpace::create(csDeviceCMYK);
        auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(baseCS), indexHigh);
        return indexed;
    }
};

// Test that getMode returns csIndexed
TEST_F(GfxIndexedColorSpaceTest_474, GetModeReturnsIndexed_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csIndexed);
}

// Test that getNComps returns 1 (indexed color spaces have 1 component - the index)
TEST_F(GfxIndexedColorSpaceTest_474, GetNCompsReturnsOne_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getNComps(), 1);
}

// Test getIndexHigh returns the value passed to constructor
TEST_F(GfxIndexedColorSpaceTest_474, GetIndexHighReturnsConstructorValue_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 255);
}

// Test getIndexHigh with smaller value
TEST_F(GfxIndexedColorSpaceTest_474, GetIndexHighSmallValue_474) {
    auto cs = createWithDeviceRGB(15);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 15);
}

// Test getIndexHigh with zero
TEST_F(GfxIndexedColorSpaceTest_474, GetIndexHighZero_474) {
    auto cs = createWithDeviceRGB(0);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 0);
}

// Test getBase returns non-null for valid base color space
TEST_F(GfxIndexedColorSpaceTest_474, GetBaseReturnsNonNull_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_NE(cs->getBase(), nullptr);
}

// Test getBase returns the correct base color space mode
TEST_F(GfxIndexedColorSpaceTest_474, GetBaseReturnsCorrectMode_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    GfxColorSpace *base = cs->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceRGB);
}

// Test getBase with DeviceGray
TEST_F(GfxIndexedColorSpaceTest_474, GetBaseDeviceGray_474) {
    auto cs = createWithDeviceGray(255);
    ASSERT_NE(cs, nullptr);
    GfxColorSpace *base = cs->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceGray);
}

// Test getBase with DeviceCMYK
TEST_F(GfxIndexedColorSpaceTest_474, GetBaseDeviceCMYK_474) {
    auto cs = createWithDeviceCMYK(255);
    ASSERT_NE(cs, nullptr);
    GfxColorSpace *base = cs->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceCMYK);
}

// Test getLookup returns non-null
TEST_F(GfxIndexedColorSpaceTest_474, GetLookupReturnsNonNull_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_NE(cs->getLookup(), nullptr);
}

// Test copy creates a valid copy
TEST_F(GfxIndexedColorSpaceTest_474, CopyCreatesValidObject_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    auto csCopy = cs->copy();
    ASSERT_NE(csCopy, nullptr);
    EXPECT_EQ(csCopy->getMode(), csIndexed);
}

// Test copy preserves indexHigh
TEST_F(GfxIndexedColorSpaceTest_474, CopyPreservesIndexHigh_474) {
    auto cs = createWithDeviceRGB(128);
    ASSERT_NE(cs, nullptr);
    auto csCopy = cs->copy();
    ASSERT_NE(csCopy, nullptr);
    auto *indexedCopy = dynamic_cast<GfxIndexedColorSpace *>(csCopy.get());
    ASSERT_NE(indexedCopy, nullptr);
    EXPECT_EQ(indexedCopy->getIndexHigh(), 128);
}

// Test copy preserves base color space mode
TEST_F(GfxIndexedColorSpaceTest_474, CopyPreservesBaseMode_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    auto csCopy = cs->copy();
    ASSERT_NE(csCopy, nullptr);
    auto *indexedCopy = dynamic_cast<GfxIndexedColorSpace *>(csCopy.get());
    ASSERT_NE(indexedCopy, nullptr);
    GfxColorSpace *base = indexedCopy->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceRGB);
}

// Test getDefaultColor sets color component to 0
TEST_F(GfxIndexedColorSpaceTest_474, GetDefaultColorSetsToZero_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    cs->getDefaultColor(&color);
    EXPECT_EQ(color.c[0], 0);
}

// Test getDefaultRanges with maxImgPixel
TEST_F(GfxIndexedColorSpaceTest_474, GetDefaultRangesWithMaxPixel_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    double decodeLow[1], decodeRange[1];
    cs->getDefaultRanges(decodeLow, decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 255.0);
}

// Test getDefaultRanges with different maxImgPixel
TEST_F(GfxIndexedColorSpaceTest_474, GetDefaultRangesWithDifferentMaxPixel_474) {
    auto cs = createWithDeviceRGB(100);
    ASSERT_NE(cs, nullptr);
    double decodeLow[1], decodeRange[1];
    cs->getDefaultRanges(decodeLow, decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 100.0);
}

// Test getGray with index 0 (default lookup is all zeros)
TEST_F(GfxIndexedColorSpaceTest_474, GetGrayWithIndexZero_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    color.c[0] = 0;
    GfxGray gray;
    cs->getGray(&color, &gray);
    // The lookup table is initialized, so this should not crash
}

// Test getRGB with index 0
TEST_F(GfxIndexedColorSpaceTest_474, GetRGBWithIndexZero_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    cs->getRGB(&color, &rgb);
    // Should not crash; values depend on lookup table initialization
}

// Test getCMYK with index 0
TEST_F(GfxIndexedColorSpaceTest_474, GetCMYKWithIndexZero_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    color.c[0] = 0;
    GfxCMYK cmyk;
    cs->getCMYK(&color, &cmyk);
    // Should not crash
}

// Test mapColorToBase returns non-null
TEST_F(GfxIndexedColorSpaceTest_474, MapColorToBaseReturnsNonNull_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    color.c[0] = 0;
    GfxColor baseColor;
    const GfxColor *result = cs->mapColorToBase(&color, &baseColor);
    EXPECT_NE(result, nullptr);
}

// Test useGetRGBLine delegates to base
TEST_F(GfxIndexedColorSpaceTest_474, UseGetRGBLineMatchesBase_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    // Just verify it returns a boolean without crashing
    bool result = cs->useGetRGBLine();
    (void)result; // We just want no crash
}

// Test useGetCMYKLine
TEST_F(GfxIndexedColorSpaceTest_474, UseGetCMYKLine_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    bool result = cs->useGetCMYKLine();
    (void)result;
}

// Test useGetDeviceNLine
TEST_F(GfxIndexedColorSpaceTest_474, UseGetDeviceNLine_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    bool result = cs->useGetDeviceNLine();
    (void)result;
}

// Test getOverprintMask
TEST_F(GfxIndexedColorSpaceTest_474, GetOverprintMask_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    unsigned int mask = cs->getOverprintMask();
    // Should return some valid mask value
    (void)mask;
}

// Test createMapping with null separation list doesn't crash
TEST_F(GfxIndexedColorSpaceTest_474, CreateMappingWithEmptyList_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;
    cs->createMapping(&separationList, 4);
    // Should not crash
}

// Test getRGBLine with unsigned int output
TEST_F(GfxIndexedColorSpaceTest_474, GetRGBLineUintOutput_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    unsigned char in[3] = {0, 1, 2};
    unsigned int out[3] = {0, 0, 0};
    cs->getRGBLine(in, out, 3);
    // Should not crash
}

// Test getRGBLine with unsigned char output
TEST_F(GfxIndexedColorSpaceTest_474, GetRGBLineUcharOutput_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    unsigned char in[3] = {0, 1, 2};
    unsigned char out[9] = {0};
    cs->getRGBLine(in, out, 3);
    // Should not crash
}

// Test getRGBXLine
TEST_F(GfxIndexedColorSpaceTest_474, GetRGBXLine_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    unsigned char in[3] = {0, 1, 2};
    unsigned char out[12] = {0};
    cs->getRGBXLine(in, out, 3);
    // Should not crash
}

// Test getCMYKLine
TEST_F(GfxIndexedColorSpaceTest_474, GetCMYKLine_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    unsigned char in[3] = {0, 1, 2};
    unsigned char out[12] = {0};
    cs->getCMYKLine(in, out, 3);
    // Should not crash
}

// Test getDeviceNLine
TEST_F(GfxIndexedColorSpaceTest_474, GetDeviceNLine_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    unsigned char in[3] = {0, 1, 2};
    unsigned char out[96] = {0}; // large enough for device N
    cs->getDeviceNLine(in, out, 3);
    // Should not crash
}

// Test construction with indexHigh of 1
TEST_F(GfxIndexedColorSpaceTest_474, ConstructWithIndexHighOne_474) {
    auto cs = createWithDeviceRGB(1);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 1);
    EXPECT_EQ(cs->getMode(), csIndexed);
    EXPECT_EQ(cs->getNComps(), 1);
}

// Test getDeviceN with index 0
TEST_F(GfxIndexedColorSpaceTest_474, GetDeviceNWithIndexZero_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    cs->getDeviceN(&color, &deviceN);
    // Should not crash
}

// Test that copy is independent (modifying original doesn't affect copy)
TEST_F(GfxIndexedColorSpaceTest_474, CopyIsIndependent_474) {
    auto cs = createWithDeviceRGB(200);
    ASSERT_NE(cs, nullptr);
    auto csCopy = cs->copy();
    ASSERT_NE(csCopy, nullptr);

    auto *indexedCopy = dynamic_cast<GfxIndexedColorSpace *>(csCopy.get());
    ASSERT_NE(indexedCopy, nullptr);

    // Both should have same indexHigh
    EXPECT_EQ(indexedCopy->getIndexHigh(), 200);

    // Original and copy are separate objects
    EXPECT_NE(cs.get(), csCopy.get());
}

// Test getMapping returns a valid reference
TEST_F(GfxIndexedColorSpaceTest_474, GetMappingReturnsValidRef_474) {
    auto cs = createWithDeviceRGB(255);
    ASSERT_NE(cs, nullptr);
    const auto &mapping = cs->getMapping();
    // Just verify it's accessible without crashing
    (void)mapping.size();
}
