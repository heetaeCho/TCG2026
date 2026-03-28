#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceRGBAColorSpaceTest_429 : public ::testing::Test {
protected:
    GfxDeviceRGBAColorSpace colorSpace;
};

TEST_F(GfxDeviceRGBAColorSpaceTest_429, GetNCompsReturnsFour_429) {
    EXPECT_EQ(colorSpace.getNComps(), 4);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, GetModeReturnsDeviceRGBA_429) {
    // GfxDeviceRGBAColorSpace should return a mode distinct from or consistent with RGBA
    GfxColorSpaceMode mode = colorSpace.getMode();
    // The mode should be csDeviceRGBA based on the class name
    // We just verify it returns a valid mode value (observable behavior)
    EXPECT_EQ(mode, csDeviceRGBA);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, CopyReturnsNonNull_429) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, CopyPreservesNComps_429) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getNComps(), 4);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, CopyPreservesMode_429) {
    auto copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), colorSpace.getMode());
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, GetNCompsConsistentAcrossCalls_429) {
    EXPECT_EQ(colorSpace.getNComps(), 4);
    EXPECT_EQ(colorSpace.getNComps(), 4);
    EXPECT_EQ(colorSpace.getNComps(), 4);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, GetARGBPremultipliedLineZeroLength_429) {
    // Zero length should be a no-op and not crash
    unsigned char in[4] = {0, 0, 0, 0};
    unsigned int out[1] = {0xDEADBEEF};
    GfxDeviceRGBAColorSpace::getARGBPremultipliedLine(in, out, 0);
    // out should remain unchanged since length is 0
    EXPECT_EQ(out[0], 0xDEADBEEF);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, GetARGBPremultipliedLineSinglePixel_429) {
    // Test with a single fully opaque white pixel
    unsigned char in[4] = {255, 255, 255, 255};
    unsigned int out[1] = {0};
    GfxDeviceRGBAColorSpace::getARGBPremultipliedLine(in, out, 1);
    // For fully opaque white, premultiplied ARGB should be 0xFFFFFFFF
    EXPECT_EQ(out[0], 0xFFFFFFFF);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, GetARGBPremultipliedLineTransparentPixel_429) {
    // Fully transparent pixel - premultiplied should zero out RGB
    unsigned char in[4] = {255, 128, 64, 0};
    unsigned int out[1] = {0xDEADBEEF};
    GfxDeviceRGBAColorSpace::getARGBPremultipliedLine(in, out, 1);
    // With alpha=0, premultiplied ARGB should be 0x00000000
    EXPECT_EQ(out[0], 0x00000000u);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, GetARGBPremultipliedLineMultiplePixels_429) {
    // Two pixels: opaque black and opaque white
    unsigned char in[8] = {0, 0, 0, 255, 255, 255, 255, 255};
    unsigned int out[2] = {0, 0};
    GfxDeviceRGBAColorSpace::getARGBPremultipliedLine(in, out, 2);
    // Opaque black
    EXPECT_EQ(out[0], 0xFF000000u);
    // Opaque white
    EXPECT_EQ(out[1], 0xFFFFFFFFu);
}

TEST_F(GfxDeviceRGBAColorSpaceTest_429, DefaultConstructionValid_429) {
    GfxDeviceRGBAColorSpace cs;
    EXPECT_EQ(cs.getNComps(), 4);
}
