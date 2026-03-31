#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceRGBAColorSpaceTest_428 : public ::testing::Test {
protected:
    void SetUp() override {
        colorSpace = std::make_unique<GfxDeviceRGBAColorSpace>();
    }

    void TearDown() override {
        colorSpace.reset();
    }

    std::unique_ptr<GfxDeviceRGBAColorSpace> colorSpace;
};

// Test that getMode returns csDeviceRGBA
TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetModeReturnsDeviceRGBA_428) {
    EXPECT_EQ(colorSpace->getMode(), csDeviceRGBA);
}

// Test that getMode returns the correct enum value (11)
TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetModeReturnsCorrectEnumValue_428) {
    EXPECT_EQ(static_cast<int>(colorSpace->getMode()), 11);
}

// Test that getMode does not return other color space modes
TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetModeIsNotOtherModes_428) {
    EXPECT_NE(colorSpace->getMode(), csDeviceGray);
    EXPECT_NE(colorSpace->getMode(), csCalGray);
    EXPECT_NE(colorSpace->getMode(), csDeviceRGB);
    EXPECT_NE(colorSpace->getMode(), csCalRGB);
    EXPECT_NE(colorSpace->getMode(), csDeviceCMYK);
    EXPECT_NE(colorSpace->getMode(), csLab);
    EXPECT_NE(colorSpace->getMode(), csICCBased);
    EXPECT_NE(colorSpace->getMode(), csIndexed);
    EXPECT_NE(colorSpace->getMode(), csSeparation);
    EXPECT_NE(colorSpace->getMode(), csDeviceN);
    EXPECT_NE(colorSpace->getMode(), csPattern);
}

// Test that getNComps returns expected value for RGBA (should be 4)
TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetNCompsReturnsFour_428) {
    EXPECT_EQ(colorSpace->getNComps(), 4);
}

// Test that copy returns a valid non-null color space
TEST_F(GfxDeviceRGBAColorSpaceTest_428, CopyReturnsNonNull_428) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
}

// Test that copy returns a color space with the same mode
TEST_F(GfxDeviceRGBAColorSpaceTest_428, CopyPreservesMode_428) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceRGBA);
}

// Test that copy returns a color space with the same number of components
TEST_F(GfxDeviceRGBAColorSpaceTest_428, CopyPreservesNComps_428) {
    auto copied = colorSpace->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), colorSpace->getNComps());
}

// Test that multiple calls to getMode are consistent
TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetModeIsConsistent_428) {
    EXPECT_EQ(colorSpace->getMode(), colorSpace->getMode());
    EXPECT_EQ(colorSpace->getMode(), csDeviceRGBA);
    EXPECT_EQ(colorSpace->getMode(), csDeviceRGBA);
}

// Test default construction works without issues
TEST_F(GfxDeviceRGBAColorSpaceTest_428, DefaultConstruction_428) {
    GfxDeviceRGBAColorSpace cs;
    EXPECT_EQ(cs.getMode(), csDeviceRGBA);
    EXPECT_EQ(cs.getNComps(), 4);
}

// Test getARGBPremultipliedLine with zero length (boundary condition)
TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetARGBPremultipliedLineZeroLength_428) {
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned int out[1] = {0};
    // Zero length should be a no-op
    GfxDeviceRGBAColorSpace::getARGBPremultipliedLine(in, out, 0);
    EXPECT_EQ(out[0], 0u);
}

// Test getARGBPremultipliedLine with a single fully opaque white pixel
TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetARGBPremultipliedLineSingleOpaqueWhite_428) {
    unsigned char in[4] = {255, 255, 255, 255};  // RGBA: white, fully opaque
    unsigned int out[1] = {0};
    GfxDeviceRGBAColorSpace::getARGBPremultipliedLine(in, out, 1);
    // For fully opaque white, the premultiplied ARGB should be 0xFFFFFFFF
    EXPECT_EQ(out[0], 0xFFFFFFFFu);
}

// Test getARGBPremultipliedLine with a single fully transparent pixel
TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetARGBPremultipliedLineSingleTransparent_428) {
    unsigned char in[4] = {255, 255, 255, 0};  // RGBA: white, fully transparent
    unsigned int out[1] = {0xDEADBEEF};
    GfxDeviceRGBAColorSpace::getARGBPremultipliedLine(in, out, 1);
    // For fully transparent, premultiplied values should be 0
    EXPECT_EQ(out[0], 0x00000000u);
}

// Test getARGBPremultipliedLine with fully opaque black
TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetARGBPremultipliedLineSingleOpaqueBlack_428) {
    unsigned char in[4] = {0, 0, 0, 255};  // RGBA: black, fully opaque
    unsigned int out[1] = {0};
    GfxDeviceRGBAColorSpace::getARGBPremultipliedLine(in, out, 1);
    // For fully opaque black, ARGB should be 0xFF000000
    EXPECT_EQ(out[0], 0xFF000000u);
}

// Test getARGBPremultipliedLine with multiple pixels
TEST_F(GfxDeviceRGBAColorSpaceTest_428, GetARGBPremultipliedLineMultiplePixels_428) {
    unsigned char in[8] = {
        255, 0, 0, 255,    // Red, fully opaque
        0, 255, 0, 255     // Green, fully opaque
    };
    unsigned int out[2] = {0, 0};
    GfxDeviceRGBAColorSpace::getARGBPremultipliedLine(in, out, 2);
    EXPECT_EQ(out[0], 0xFFFF0000u);  // ARGB red
    EXPECT_EQ(out[1], 0xFF00FF00u);  // ARGB green
}
