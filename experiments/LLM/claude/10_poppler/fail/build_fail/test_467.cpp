#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

// Helper to create a basic GfxIndexedColorSpace for testing
// We need a base color space - DeviceRGB is the simplest available
static std::unique_ptr<GfxIndexedColorSpace> createTestIndexedColorSpace(int indexHigh = 255) {
    // Create a DeviceRGB base color space
    auto base = GfxColorSpace::create(csDeviceRGB);
    if (!base) {
        return nullptr;
    }
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    
    // Fill lookup table with identity-like mapping
    unsigned char *lookup = indexed->getLookup();
    if (lookup) {
        int nCompsBase = 3; // RGB has 3 components
        for (int i = 0; i <= indexHigh; i++) {
            for (int j = 0; j < nCompsBase; j++) {
                lookup[i * nCompsBase + j] = (unsigned char)(i & 0xFF);
            }
        }
    }
    
    return indexed;
}

static std::unique_ptr<GfxIndexedColorSpace> createTestIndexedCMYKColorSpace(int indexHigh = 255) {
    auto base = GfxColorSpace::create(csDeviceCMYK);
    if (!base) {
        return nullptr;
    }
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    
    unsigned char *lookup = indexed->getLookup();
    if (lookup) {
        int nCompsBase = 4; // CMYK has 4 components
        for (int i = 0; i <= indexHigh; i++) {
            for (int j = 0; j < nCompsBase; j++) {
                lookup[i * nCompsBase + j] = (unsigned char)(i & 0xFF);
            }
        }
    }
    
    return indexed;
}

class GfxIndexedColorSpaceTest_467 : public ::testing::Test {
protected:
    void SetUp() override {
        indexedCS = createTestIndexedColorSpace(255);
    }
    
    std::unique_ptr<GfxIndexedColorSpace> indexedCS;
};

// Test that getMode returns csIndexed
TEST_F(GfxIndexedColorSpaceTest_467, GetModeReturnsIndexed_467) {
    ASSERT_NE(indexedCS, nullptr);
    EXPECT_EQ(indexedCS->getMode(), csIndexed);
}

// Test that getNComps returns 1 (indexed color spaces have 1 component)
TEST_F(GfxIndexedColorSpaceTest_467, GetNCompsReturnsOne_467) {
    ASSERT_NE(indexedCS, nullptr);
    EXPECT_EQ(indexedCS->getNComps(), 1);
}

// Test that getIndexHigh returns the correct value
TEST_F(GfxIndexedColorSpaceTest_467, GetIndexHighReturnsCorrectValue_467) {
    ASSERT_NE(indexedCS, nullptr);
    EXPECT_EQ(indexedCS->getIndexHigh(), 255);
}

// Test with a different indexHigh value
TEST_F(GfxIndexedColorSpaceTest_467, GetIndexHighWithSmallValue_467) {
    auto cs = createTestIndexedColorSpace(15);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 15);
}

// Test that getBase returns a non-null pointer
TEST_F(GfxIndexedColorSpaceTest_467, GetBaseReturnsNonNull_467) {
    ASSERT_NE(indexedCS, nullptr);
    GfxColorSpace *base = indexedCS->getBase();
    EXPECT_NE(base, nullptr);
}

// Test that the base color space is DeviceRGB
TEST_F(GfxIndexedColorSpaceTest_467, GetBaseReturnsRGB_467) {
    ASSERT_NE(indexedCS, nullptr);
    GfxColorSpace *base = indexedCS->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceRGB);
}

// Test that getLookup returns a non-null pointer
TEST_F(GfxIndexedColorSpaceTest_467, GetLookupReturnsNonNull_467) {
    ASSERT_NE(indexedCS, nullptr);
    unsigned char *lookup = indexedCS->getLookup();
    EXPECT_NE(lookup, nullptr);
}

// Test useGetCMYKLine returns true
TEST_F(GfxIndexedColorSpaceTest_467, UseGetCMYKLineReturnsTrue_467) {
    ASSERT_NE(indexedCS, nullptr);
    EXPECT_TRUE(indexedCS->useGetCMYKLine());
}

// Test useGetRGBLine returns true (since DeviceRGB base supports it)
TEST_F(GfxIndexedColorSpaceTest_467, UseGetRGBLineReturnsTrue_467) {
    ASSERT_NE(indexedCS, nullptr);
    EXPECT_TRUE(indexedCS->useGetRGBLine());
}

// Test useGetDeviceNLine returns true
TEST_F(GfxIndexedColorSpaceTest_467, UseGetDeviceNLineReturnsTrue_467) {
    ASSERT_NE(indexedCS, nullptr);
    EXPECT_TRUE(indexedCS->useGetDeviceNLine());
}

// Test copy creates a valid copy
TEST_F(GfxIndexedColorSpaceTest_467, CopyCreatesValidCopy_467) {
    ASSERT_NE(indexedCS, nullptr);
    auto copied = indexedCS->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csIndexed);
    
    GfxIndexedColorSpace *copiedIndexed = dynamic_cast<GfxIndexedColorSpace *>(copied.get());
    ASSERT_NE(copiedIndexed, nullptr);
    EXPECT_EQ(copiedIndexed->getIndexHigh(), indexedCS->getIndexHigh());
    EXPECT_EQ(copiedIndexed->getNComps(), indexedCS->getNComps());
}

// Test getGray with a valid color
TEST_F(GfxIndexedColorSpaceTest_467, GetGrayProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    GfxColor color;
    color.c[0] = 0; // index 0
    GfxGray gray;
    indexedCS->getGray(&color, &gray);
    // Just verify it doesn't crash; exact value depends on lookup table content
}

// Test getRGB with a valid color
TEST_F(GfxIndexedColorSpaceTest_467, GetRGBProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    GfxColor color;
    color.c[0] = 0; // index 0
    GfxRGB rgb;
    indexedCS->getRGB(&color, &rgb);
    // Verify it doesn't crash
}

// Test getCMYK with a valid color
TEST_F(GfxIndexedColorSpaceTest_467, GetCMYKProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    GfxColor color;
    color.c[0] = 0; // index 0
    GfxCMYK cmyk;
    indexedCS->getCMYK(&color, &cmyk);
    // Verify it doesn't crash
}

// Test getDeviceN with a valid color
TEST_F(GfxIndexedColorSpaceTest_467, GetDeviceNProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    GfxColor color;
    color.c[0] = 0;
    GfxColor deviceN;
    indexedCS->getDeviceN(&color, &deviceN);
    // Verify it doesn't crash
}

// Test getDefaultColor
TEST_F(GfxIndexedColorSpaceTest_467, GetDefaultColorProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    GfxColor color;
    indexedCS->getDefaultColor(&color);
    // Default color for indexed should be index 0
    EXPECT_EQ(color.c[0], 0);
}

// Test getDefaultRanges
TEST_F(GfxIndexedColorSpaceTest_467, GetDefaultRangesProducesCorrectValues_467) {
    ASSERT_NE(indexedCS, nullptr);
    double decodeLow[1], decodeRange[1];
    indexedCS->getDefaultRanges(decodeLow, decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 255.0);
}

// Test getDefaultRanges with different maxImgPixel
TEST_F(GfxIndexedColorSpaceTest_467, GetDefaultRangesWithDifferentMaxPixel_467) {
    ASSERT_NE(indexedCS, nullptr);
    double decodeLow[1], decodeRange[1];
    indexedCS->getDefaultRanges(decodeLow, decodeRange, 15);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 15.0);
}

// Test mapColorToBase
TEST_F(GfxIndexedColorSpaceTest_467, MapColorToBaseProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    GfxColor color;
    color.c[0] = 0;
    GfxColor baseColor;
    const GfxColor *result = indexedCS->mapColorToBase(&color, &baseColor);
    EXPECT_NE(result, nullptr);
}

// Test getRGBLine with unsigned int output
TEST_F(GfxIndexedColorSpaceTest_467, GetRGBLineUintProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    unsigned char input[3] = {0, 1, 2};
    unsigned int output[3] = {0, 0, 0};
    indexedCS->getRGBLine(input, output, 3);
    // Verify it doesn't crash
}

// Test getRGBLine with unsigned char output
TEST_F(GfxIndexedColorSpaceTest_467, GetRGBLineUcharProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    unsigned char input[3] = {0, 1, 2};
    unsigned char output[9] = {0}; // 3 pixels * 3 components
    indexedCS->getRGBLine(input, output, 3);
    // Verify it doesn't crash
}

// Test getRGBXLine
TEST_F(GfxIndexedColorSpaceTest_467, GetRGBXLineProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    unsigned char input[3] = {0, 1, 2};
    unsigned char output[12] = {0}; // 3 pixels * 4 bytes (RGBX)
    indexedCS->getRGBXLine(input, output, 3);
    // Verify it doesn't crash
}

// Test getCMYKLine
TEST_F(GfxIndexedColorSpaceTest_467, GetCMYKLineProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    unsigned char input[3] = {0, 1, 2};
    unsigned char output[12] = {0}; // 3 pixels * 4 components
    indexedCS->getCMYKLine(input, output, 3);
    // Verify it doesn't crash
}

// Test getDeviceNLine
TEST_F(GfxIndexedColorSpaceTest_467, GetDeviceNLineProducesResult_467) {
    ASSERT_NE(indexedCS, nullptr);
    unsigned char input[3] = {0, 1, 2};
    unsigned char output[48] = {0}; // generous buffer
    indexedCS->getDeviceNLine(input, output, 3);
    // Verify it doesn't crash
}

// Test with indexHigh of 0 (boundary condition - single color)
TEST_F(GfxIndexedColorSpaceTest_467, IndexHighZero_467) {
    auto cs = createTestIndexedColorSpace(0);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 0);
    EXPECT_EQ(cs->getNComps(), 1);
    
    GfxColor color;
    cs->getDefaultColor(&color);
    EXPECT_EQ(color.c[0], 0);
}

// Test with indexHigh of 1 (boundary condition - two colors)
TEST_F(GfxIndexedColorSpaceTest_467, IndexHighOne_467) {
    auto cs = createTestIndexedColorSpace(1);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 1);
}

// Test with CMYK base color space
TEST_F(GfxIndexedColorSpaceTest_467, CMYKBaseColorSpace_467) {
    auto cs = createTestIndexedCMYKColorSpace(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csIndexed);
    EXPECT_EQ(cs->getNComps(), 1);
    
    GfxColorSpace *base = cs->getBase();
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->getMode(), csDeviceCMYK);
}

// Test that useGetCMYKLine is true with CMYK base
TEST_F(GfxIndexedColorSpaceTest_467, UseGetCMYKLineWithCMYKBase_467) {
    auto cs = createTestIndexedCMYKColorSpace(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_TRUE(cs->useGetCMYKLine());
}

// Test getOverprintMask
TEST_F(GfxIndexedColorSpaceTest_467, GetOverprintMaskReturnsValue_467) {
    ASSERT_NE(indexedCS, nullptr);
    // Just verify it returns a value without crashing
    unsigned int mask = indexedCS->getOverprintMask();
    // The overprint mask should be non-negative (it's unsigned)
    (void)mask;
}

// Test copy preserves lookup table content
TEST_F(GfxIndexedColorSpaceTest_467, CopyPreservesLookup_467) {
    ASSERT_NE(indexedCS, nullptr);
    auto copied = indexedCS->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxIndexedColorSpace *copiedIndexed = dynamic_cast<GfxIndexedColorSpace *>(copied.get());
    ASSERT_NE(copiedIndexed, nullptr);
    
    unsigned char *origLookup = indexedCS->getLookup();
    unsigned char *copiedLookup = copiedIndexed->getLookup();
    ASSERT_NE(origLookup, nullptr);
    ASSERT_NE(copiedLookup, nullptr);
    
    // The lookup tables should have the same content but be different pointers
    int nCompsBase = indexedCS->getBase()->getNComps();
    int lookupSize = (indexedCS->getIndexHigh() + 1) * nCompsBase;
    for (int i = 0; i < lookupSize; i++) {
        EXPECT_EQ(origLookup[i], copiedLookup[i]) << "Mismatch at index " << i;
    }
}

// Test getRGBLine with length 0 (boundary)
TEST_F(GfxIndexedColorSpaceTest_467, GetRGBLineZeroLength_467) {
    ASSERT_NE(indexedCS, nullptr);
    unsigned char input[1] = {0};
    unsigned int output[1] = {0};
    indexedCS->getRGBLine(input, output, 0);
    // Should not crash with zero length
}

// Test getCMYKLine with length 0 (boundary)
TEST_F(GfxIndexedColorSpaceTest_467, GetCMYKLineZeroLength_467) {
    ASSERT_NE(indexedCS, nullptr);
    unsigned char input[1] = {0};
    unsigned char output[1] = {0};
    indexedCS->getCMYKLine(input, output, 0);
    // Should not crash with zero length
}

// Test single pixel getRGBLine
TEST_F(GfxIndexedColorSpaceTest_467, GetRGBLineSinglePixel_467) {
    ASSERT_NE(indexedCS, nullptr);
    unsigned char input[1] = {0};
    unsigned int output[1] = {0};
    indexedCS->getRGBLine(input, output, 1);
    // Verify it doesn't crash
}
