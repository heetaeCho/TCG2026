#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

class GfxIndexedColorSpaceTest_470 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getBase() returns a non-null pointer when constructed with a valid base color space
TEST_F(GfxIndexedColorSpaceTest_470, GetBaseReturnsNonNullWhenConstructedWithValidBase_470) {
    // Create a base color space (DeviceRGB)
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxColorSpace* rawBase = baseCS.get();
    GfxIndexedColorSpace indexedCS(std::move(baseCS), 255);

    GfxColorSpace* result = indexedCS.getBase();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, rawBase);
}

// Test that getBase() returns a color space with the correct mode
TEST_F(GfxIndexedColorSpaceTest_470, GetBaseReturnsCorrectColorSpaceMode_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 255);

    GfxColorSpace* result = indexedCS.getBase();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getMode(), csDeviceRGB);
}

// Test getMode returns csIndexed
TEST_F(GfxIndexedColorSpaceTest_470, GetModeReturnsIndexed_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 255);
    EXPECT_EQ(indexedCS.getMode(), csIndexed);
}

// Test getIndexHigh returns the value passed in constructor
TEST_F(GfxIndexedColorSpaceTest_470, GetIndexHighReturnsConstructorValue_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 127);
    EXPECT_EQ(indexedCS.getIndexHigh(), 127);
}

// Test getIndexHigh with zero
TEST_F(GfxIndexedColorSpaceTest_470, GetIndexHighWithZero_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 0);
    EXPECT_EQ(indexedCS.getIndexHigh(), 0);
}

// Test getIndexHigh with max value 255
TEST_F(GfxIndexedColorSpaceTest_470, GetIndexHighWithMaxValue_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 255);
    EXPECT_EQ(indexedCS.getIndexHigh(), 255);
}

// Test getNComps returns 1 for indexed color space
TEST_F(GfxIndexedColorSpaceTest_470, GetNCompsReturnsOne_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 255);
    EXPECT_EQ(indexedCS.getNComps(), 1);
}

// Test getLookup returns non-null
TEST_F(GfxIndexedColorSpaceTest_470, GetLookupReturnsNonNull_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 255);
    // Lookup should be allocated during construction
    unsigned char* lookup = indexedCS.getLookup();
    EXPECT_NE(lookup, nullptr);
}

// Test getBase with DeviceCMYK base
TEST_F(GfxIndexedColorSpaceTest_470, GetBaseWithDeviceCMYKBase_470) {
    auto baseCS = GfxColorSpace::create(csDeviceCMYK);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 100);

    GfxColorSpace* result = indexedCS.getBase();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getMode(), csDeviceCMYK);
}

// Test getBase with DeviceGray base
TEST_F(GfxIndexedColorSpaceTest_470, GetBaseWithDeviceGrayBase_470) {
    auto baseCS = GfxColorSpace::create(csDeviceGray);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 50);

    GfxColorSpace* result = indexedCS.getBase();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getMode(), csDeviceGray);
}

// Test getDefaultColor sets color component to 0
TEST_F(GfxIndexedColorSpaceTest_470, GetDefaultColorSetsToZero_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 255);

    GfxColor color;
    indexedCS.getDefaultColor(&color);
    EXPECT_EQ(color.c[0], 0);
}

// Test copy produces a valid color space
TEST_F(GfxIndexedColorSpaceTest_470, CopyProducesValidColorSpace_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 200);

    auto copied = indexedCS.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csIndexed);
}

// Test that copied color space has same indexHigh
TEST_F(GfxIndexedColorSpaceTest_470, CopyPreservesIndexHigh_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 42);

    auto copied = indexedCS.copy();
    ASSERT_NE(copied, nullptr);

    GfxIndexedColorSpace* copiedIndexed = dynamic_cast<GfxIndexedColorSpace*>(copied.get());
    ASSERT_NE(copiedIndexed, nullptr);
    EXPECT_EQ(copiedIndexed->getIndexHigh(), 42);
}

// Test that copied color space has a valid base
TEST_F(GfxIndexedColorSpaceTest_470, CopyPreservesBase_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 255);

    auto copied = indexedCS.copy();
    ASSERT_NE(copied, nullptr);

    GfxIndexedColorSpace* copiedIndexed = dynamic_cast<GfxIndexedColorSpace*>(copied.get());
    ASSERT_NE(copiedIndexed, nullptr);

    GfxColorSpace* copiedBase = copiedIndexed->getBase();
    ASSERT_NE(copiedBase, nullptr);
    EXPECT_EQ(copiedBase->getMode(), csDeviceRGB);
}

// Test getDefaultRanges
TEST_F(GfxIndexedColorSpaceTest_470, GetDefaultRanges_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 255);

    double decodeLow[1];
    double decodeRange[1];
    indexedCS.getDefaultRanges(decodeLow, decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 255.0);
}

// Test getDefaultRanges with different maxImgPixel
TEST_F(GfxIndexedColorSpaceTest_470, GetDefaultRangesWithDifferentMaxImgPixel_470) {
    auto baseCS = GfxColorSpace::create(csDeviceRGB);
    ASSERT_NE(baseCS, nullptr);

    GfxIndexedColorSpace indexedCS(std::move(baseCS), 100);

    double decodeLow[1];
    double decodeRange[1];
    indexedCS.getDefaultRanges(decodeLow, decodeRange, 255);
    EXPECT_DOUBLE_EQ(decodeLow[0], 0.0);
    EXPECT_DOUBLE_EQ(decodeRange[0], 100.0);
}
