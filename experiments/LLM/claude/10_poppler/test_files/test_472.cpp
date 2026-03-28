#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

// Test fixture for GfxIndexedColorSpace
class GfxIndexedColorSpaceTest_472 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing a GfxIndexedColorSpace with a DeviceRGB base works
// and getBase() returns a valid pointer
TEST_F(GfxIndexedColorSpaceTest_472, ConstructWithDeviceRGBBase_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    int indexHigh = 255;
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    ASSERT_NE(indexed, nullptr);
    EXPECT_NE(indexed->getBase(), nullptr);
}

// Test that getIndexHigh returns the value passed during construction
TEST_F(GfxIndexedColorSpaceTest_472, GetIndexHighReturnsCorrectValue_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    int indexHigh = 127;
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    EXPECT_EQ(indexed->getIndexHigh(), 127);
}

// Test that getMode returns csIndexed
TEST_F(GfxIndexedColorSpaceTest_472, GetModeReturnsIndexed_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    EXPECT_EQ(indexed->getMode(), csIndexed);
}

// Test that getNComps returns 1 for indexed color space
TEST_F(GfxIndexedColorSpaceTest_472, GetNCompsReturnsOne_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    EXPECT_EQ(indexed->getNComps(), 1);
}

// Test that getLookup returns a non-null pointer after construction
TEST_F(GfxIndexedColorSpaceTest_472, GetLookupReturnsNonNull_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    // The lookup table should be allocated
    EXPECT_NE(indexed->getLookup(), nullptr);
}

// Test that getBase returns a color space with the expected mode
TEST_F(GfxIndexedColorSpaceTest_472, GetBaseReturnsCorrectColorSpaceMode_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    GfxColorSpace *basePtr = indexed->getBase();
    ASSERT_NE(basePtr, nullptr);
    EXPECT_EQ(basePtr->getMode(), csDeviceRGB);
}

// Test with indexHigh = 0 (minimum boundary)
TEST_F(GfxIndexedColorSpaceTest_472, ConstructWithIndexHighZero_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 0);
    EXPECT_EQ(indexed->getIndexHigh(), 0);
    EXPECT_NE(indexed->getLookup(), nullptr);
}

// Test copy produces a valid copy
TEST_F(GfxIndexedColorSpaceTest_472, CopyProducesValidCopy_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    int indexHigh = 100;
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    
    auto copied = indexed->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csIndexed);
    EXPECT_EQ(copied->getNComps(), 1);
}

// Test getDefaultColor sets color component
TEST_F(GfxIndexedColorSpaceTest_472, GetDefaultColorSetsValue_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    
    GfxColor color;
    indexed->getDefaultColor(&color);
    // Default color for indexed should set the first component to 0
    EXPECT_EQ(color.c[0], 0);
}

// Test getDefaultRanges provides proper decode ranges
TEST_F(GfxIndexedColorSpaceTest_472, GetDefaultRangesProvideCorrectValues_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    int indexHigh = 255;
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    
    double decodeLow[1], decodeRange[1];
    indexed->getDefaultRanges(decodeLow, decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 255.0);
}

// Test getDefaultRanges with maxImgPixel different from indexHigh
TEST_F(GfxIndexedColorSpaceTest_472, GetDefaultRangesWithDifferentMaxImgPixel_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    int indexHigh = 100;
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    
    double decodeLow[1], decodeRange[1];
    indexed->getDefaultRanges(decodeLow, decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 100.0);
}

// Test with DeviceCMYK base
TEST_F(GfxIndexedColorSpaceTest_472, ConstructWithDeviceCMYKBase_472) {
    auto base = GfxColorSpace::create(csDeviceCMYK);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    ASSERT_NE(indexed, nullptr);
    GfxColorSpace *basePtr = indexed->getBase();
    ASSERT_NE(basePtr, nullptr);
    EXPECT_EQ(basePtr->getMode(), csDeviceCMYK);
}

// Test with DeviceGray base
TEST_F(GfxIndexedColorSpaceTest_472, ConstructWithDeviceGrayBase_472) {
    auto base = GfxColorSpace::create(csDeviceGray);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    ASSERT_NE(indexed, nullptr);
    GfxColorSpace *basePtr = indexed->getBase();
    ASSERT_NE(basePtr, nullptr);
    EXPECT_EQ(basePtr->getMode(), csDeviceGray);
}

// Test getGray with a color at index 0
TEST_F(GfxIndexedColorSpaceTest_472, GetGrayAtIndexZero_472) {
    auto base = GfxColorSpace::create(csDeviceGray);
    ASSERT_NE(base, nullptr);
    int indexHigh = 255;
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    
    // Initialize lookup to known values
    unsigned char *lookup = indexed->getLookup();
    ASSERT_NE(lookup, nullptr);
    // For DeviceGray base with 1 component, set lookup[0] = 128
    lookup[0] = 128;
    
    GfxColor color;
    color.c[0] = 0; // index 0
    GfxGray gray;
    indexed->getGray(&color, &gray);
    // We just verify it doesn't crash and returns some value
    // The actual value depends on implementation details of lookup mapping
}

// Test getRGB with a color at a specific index
TEST_F(GfxIndexedColorSpaceTest_472, GetRGBAtIndex_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    int indexHigh = 255;
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    
    unsigned char *lookup = indexed->getLookup();
    ASSERT_NE(lookup, nullptr);
    // Set index 0 to white (255, 255, 255)
    lookup[0] = 255;
    lookup[1] = 255;
    lookup[2] = 255;
    
    GfxColor color;
    color.c[0] = 0;
    GfxRGB rgb;
    indexed->getRGB(&color, &rgb);
    // Just verify it completes without error
}

// Test mapColorToBase
TEST_F(GfxIndexedColorSpaceTest_472, MapColorToBase_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    int indexHigh = 255;
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    
    unsigned char *lookup = indexed->getLookup();
    ASSERT_NE(lookup, nullptr);
    // Set known values at index 0
    lookup[0] = 255;
    lookup[1] = 0;
    lookup[2] = 128;
    
    GfxColor color;
    color.c[0] = 0;
    GfxColor baseColor;
    const GfxColor *result = indexed->mapColorToBase(&color, &baseColor);
    ASSERT_NE(result, nullptr);
}

// Test that copy preserves indexHigh
TEST_F(GfxIndexedColorSpaceTest_472, CopyPreservesIndexHigh_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    int indexHigh = 42;
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    
    auto copied = indexed->copy();
    ASSERT_NE(copied, nullptr);
    
    // Cast to GfxIndexedColorSpace to check indexHigh
    GfxIndexedColorSpace *copiedIndexed = dynamic_cast<GfxIndexedColorSpace *>(copied.get());
    ASSERT_NE(copiedIndexed, nullptr);
    EXPECT_EQ(copiedIndexed->getIndexHigh(), 42);
}

// Test that copy preserves lookup data
TEST_F(GfxIndexedColorSpaceTest_472, CopyPreservesLookupData_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    int indexHigh = 1;
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    
    unsigned char *lookup = indexed->getLookup();
    ASSERT_NE(lookup, nullptr);
    // Set known values for index 0 and 1 (3 components each for RGB)
    lookup[0] = 10; lookup[1] = 20; lookup[2] = 30;
    lookup[3] = 40; lookup[4] = 50; lookup[5] = 60;
    
    auto copied = indexed->copy();
    ASSERT_NE(copied, nullptr);
    
    GfxIndexedColorSpace *copiedIndexed = dynamic_cast<GfxIndexedColorSpace *>(copied.get());
    ASSERT_NE(copiedIndexed, nullptr);
    unsigned char *copiedLookup = copiedIndexed->getLookup();
    ASSERT_NE(copiedLookup, nullptr);
    
    // Lookup should be a separate copy, not the same pointer
    EXPECT_NE(copiedLookup, lookup);
    
    EXPECT_EQ(copiedLookup[0], 10);
    EXPECT_EQ(copiedLookup[1], 20);
    EXPECT_EQ(copiedLookup[2], 30);
    EXPECT_EQ(copiedLookup[3], 40);
    EXPECT_EQ(copiedLookup[4], 50);
    EXPECT_EQ(copiedLookup[5], 60);
}

// Test with maximum indexHigh of 255
TEST_F(GfxIndexedColorSpaceTest_472, IndexHighMaximum255_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    EXPECT_EQ(indexed->getIndexHigh(), 255);
    EXPECT_NE(indexed->getLookup(), nullptr);
}

// Test useGetRGBLine delegates properly
TEST_F(GfxIndexedColorSpaceTest_472, UseGetRGBLine_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    // Just verify it returns a boolean without crashing
    bool result = indexed->useGetRGBLine();
    (void)result; // We don't assert a specific value since it depends on base
}

// Test useGetCMYKLine delegates properly
TEST_F(GfxIndexedColorSpaceTest_472, UseGetCMYKLine_472) {
    auto base = GfxColorSpace::create(csDeviceCMYK);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    bool result = indexed->useGetCMYKLine();
    (void)result;
}

// Test useGetDeviceNLine
TEST_F(GfxIndexedColorSpaceTest_472, UseGetDeviceNLine_472) {
    auto base = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(base, nullptr);
    auto indexed = std::make_unique<GfxIndexedColorSpace>(std::move(base), 255);
    bool result = indexed->useGetDeviceNLine();
    (void)result;
}
