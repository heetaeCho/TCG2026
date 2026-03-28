#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

class GfxIndexedColorSpaceTest_471 : public ::testing::Test {
protected:
    std::unique_ptr<GfxIndexedColorSpace> createIndexedColorSpace(int indexHigh) {
        // Create a base DeviceRGB color space
        auto base = GfxColorSpace::create(csDeviceRGB);
        if (!base) {
            return nullptr;
        }
        return std::make_unique<GfxIndexedColorSpace>(std::move(base), indexHigh);
    }
};

// Test normal case: typical indexHigh value
TEST_F(GfxIndexedColorSpaceTest_471, GetIndexHigh_NormalValue_471) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 255);
}

// Test boundary: indexHigh of 0
TEST_F(GfxIndexedColorSpaceTest_471, GetIndexHigh_Zero_471) {
    auto cs = createIndexedColorSpace(0);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 0);
}

// Test boundary: indexHigh of 1
TEST_F(GfxIndexedColorSpaceTest_471, GetIndexHigh_One_471) {
    auto cs = createIndexedColorSpace(1);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 1);
}

// Test with a mid-range value
TEST_F(GfxIndexedColorSpaceTest_471, GetIndexHigh_MidRange_471) {
    auto cs = createIndexedColorSpace(127);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 127);
}

// Test with a small value
TEST_F(GfxIndexedColorSpaceTest_471, GetIndexHigh_SmallValue_471) {
    auto cs = createIndexedColorSpace(15);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 15);
}

// Test that getMode returns csIndexed
TEST_F(GfxIndexedColorSpaceTest_471, GetMode_ReturnsIndexed_471) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getMode(), csIndexed);
}

// Test getNComps returns 1 for indexed color space
TEST_F(GfxIndexedColorSpaceTest_471, GetNComps_ReturnsOne_471) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getNComps(), 1);
}

// Test getBase returns non-null
TEST_F(GfxIndexedColorSpaceTest_471, GetBase_ReturnsNonNull_471) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    EXPECT_NE(cs->getBase(), nullptr);
}

// Test copy preserves indexHigh
TEST_F(GfxIndexedColorSpaceTest_471, Copy_PreservesIndexHigh_471) {
    auto cs = createIndexedColorSpace(200);
    ASSERT_NE(cs, nullptr);
    auto copied = cs->copy();
    ASSERT_NE(copied, nullptr);
    auto* copiedIndexed = dynamic_cast<GfxIndexedColorSpace*>(copied.get());
    ASSERT_NE(copiedIndexed, nullptr);
    EXPECT_EQ(copiedIndexed->getIndexHigh(), 200);
}

// Test getDefaultColor
TEST_F(GfxIndexedColorSpaceTest_471, GetDefaultColor_471) {
    auto cs = createIndexedColorSpace(255);
    ASSERT_NE(cs, nullptr);
    GfxColor color;
    cs->getDefaultColor(&color);
    // Default color for indexed should set first component to 0
    EXPECT_EQ(color.c[0], 0);
}

// Test with large indexHigh value
TEST_F(GfxIndexedColorSpaceTest_471, GetIndexHigh_LargeValue_471) {
    auto cs = createIndexedColorSpace(4095);
    ASSERT_NE(cs, nullptr);
    EXPECT_EQ(cs->getIndexHigh(), 4095);
}
