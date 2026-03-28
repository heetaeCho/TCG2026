#include <gtest/gtest.h>
#include "GfxState.h"

class GfxDeviceGrayColorSpaceTest_409 : public ::testing::Test {
protected:
    GfxDeviceGrayColorSpace colorSpace;
};

// Test that useGetGrayLine returns true
TEST_F(GfxDeviceGrayColorSpaceTest_409, UseGetGrayLineReturnsTrue_409) {
    EXPECT_TRUE(colorSpace.useGetGrayLine());
}

// Test that useGetRGBLine returns expected value (should be true for device gray)
TEST_F(GfxDeviceGrayColorSpaceTest_409, UseGetRGBLine_409) {
    bool result = colorSpace.useGetRGBLine();
    // Device gray typically supports RGB line operations
    EXPECT_TRUE(result);
}

// Test that useGetCMYKLine returns expected value
TEST_F(GfxDeviceGrayColorSpaceTest_409, UseGetCMYKLine_409) {
    bool result = colorSpace.useGetCMYKLine();
    EXPECT_TRUE(result);
}

// Test that useGetDeviceNLine returns expected value
TEST_F(GfxDeviceGrayColorSpaceTest_409, UseGetDeviceNLine_409) {
    bool result = colorSpace.useGetDeviceNLine();
    EXPECT_TRUE(result);
}

// Test that getMode returns csDeviceGray
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetModeReturnsDeviceGray_409) {
    EXPECT_EQ(colorSpace.getMode(), csDeviceGray);
}

// Test that getNComps returns 1 for gray color space
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetNCompsReturnsOne_409) {
    EXPECT_EQ(colorSpace.getNComps(), 1);
}

// Test copy creates a valid copy
TEST_F(GfxDeviceGrayColorSpaceTest_409, CopyCreatesValidCopy_409) {
    std::unique_ptr<GfxColorSpace> copied = colorSpace.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getMode(), csDeviceGray);
    EXPECT_EQ(copied->getNComps(), 1);
    EXPECT_TRUE(copied->useGetGrayLine());
}

// Test getGray conversion
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetGrayConversion_409) {
    GfxColor color;
    GfxGray gray;

    // Set component to 0 (black)
    color.c[0] = 0;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, 0);

    // Set component to max (white)
    color.c[0] = gfxColorComp1;
    colorSpace.getGray(&color, &gray);
    EXPECT_EQ(gray, gfxColorComp1);
}

// Test getRGB conversion - gray should map to equal R, G, B
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetRGBConversion_409) {
    GfxColor color;
    GfxRGB rgb;

    // Black
    color.c[0] = 0;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, 0);
    EXPECT_EQ(rgb.g, 0);
    EXPECT_EQ(rgb.b, 0);

    // White
    color.c[0] = gfxColorComp1;
    colorSpace.getRGB(&color, &rgb);
    EXPECT_EQ(rgb.r, gfxColorComp1);
    EXPECT_EQ(rgb.g, gfxColorComp1);
    EXPECT_EQ(rgb.b, gfxColorComp1);
}

// Test getCMYK conversion
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetCMYKConversion_409) {
    GfxColor color;
    GfxCMYK cmyk;

    // White (gray = 1.0) should be C=0, M=0, Y=0, K=0
    color.c[0] = gfxColorComp1;
    colorSpace.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, 0);

    // Black (gray = 0) should be K=1
    color.c[0] = 0;
    colorSpace.getCMYK(&color, &cmyk);
    EXPECT_EQ(cmyk.c, 0);
    EXPECT_EQ(cmyk.m, 0);
    EXPECT_EQ(cmyk.y, 0);
    EXPECT_EQ(cmyk.k, gfxColorComp1);
}

// Test getDefaultColor
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetDefaultColor_409) {
    GfxColor color;
    colorSpace.getDefaultColor(&color);
    // Default for gray color space is typically 0 (black)
    EXPECT_EQ(color.c[0], 0);
}

// Test getGrayLine with identity mapping
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetGrayLineIdentity_409) {
    const int length = 5;
    unsigned char in[length] = {0, 64, 128, 192, 255};
    unsigned char out[length] = {0};

    colorSpace.getGrayLine(in, out, length);

    // For device gray, output should match input
    for (int i = 0; i < length; i++) {
        EXPECT_EQ(out[i], in[i]);
    }
}

// Test getRGBLine (unsigned int version)
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetRGBLineUintVersion_409) {
    const int length = 3;
    unsigned char in[length] = {0, 128, 255};
    unsigned int out[length] = {0};

    colorSpace.getRGBLine(in, out, length);

    // Each output pixel should be a packed RGB value
    // For gray, R=G=B=gray value
    for (int i = 0; i < length; i++) {
        unsigned int pixel = out[i];
        // Verify the pixel is non-zero for non-zero input (basic check)
        if (in[i] > 0) {
            EXPECT_NE(pixel, 0u);
        }
    }
}

// Test getRGBLine (unsigned char version)
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetRGBLineUcharVersion_409) {
    const int length = 3;
    unsigned char in[length] = {0, 128, 255};
    unsigned char out[length * 3] = {0};

    colorSpace.getRGBLine(in, out, length);

    // For device gray, R=G=B for each pixel
    for (int i = 0; i < length; i++) {
        EXPECT_EQ(out[i * 3], out[i * 3 + 1]);     // R == G
        EXPECT_EQ(out[i * 3 + 1], out[i * 3 + 2]); // G == B
        EXPECT_EQ(out[i * 3], in[i]);                // R == input gray
    }
}

// Test getRGBXLine
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetRGBXLine_409) {
    const int length = 3;
    unsigned char in[length] = {0, 128, 255};
    unsigned char out[length * 4] = {0};

    colorSpace.getRGBXLine(in, out, length);

    // For device gray, R=G=B for each pixel, with an extra byte
    for (int i = 0; i < length; i++) {
        EXPECT_EQ(out[i * 4], out[i * 4 + 1]);     // R == G
        EXPECT_EQ(out[i * 4 + 1], out[i * 4 + 2]); // G == B
        EXPECT_EQ(out[i * 4], in[i]);                // R == input gray
    }
}

// Test getCMYKLine
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetCMYKLine_409) {
    const int length = 2;
    unsigned char in[length] = {0, 255};
    unsigned char out[length * 4] = {0};

    colorSpace.getCMYKLine(in, out, length);

    // Black (gray=0): K=255, C=M=Y=0
    EXPECT_EQ(out[0], 0);   // C
    EXPECT_EQ(out[1], 0);   // M
    EXPECT_EQ(out[2], 0);   // Y
    EXPECT_EQ(out[3], 255); // K

    // White (gray=255): K=0, C=M=Y=0
    EXPECT_EQ(out[4], 0);   // C
    EXPECT_EQ(out[5], 0);   // M
    EXPECT_EQ(out[6], 0);   // Y
    EXPECT_EQ(out[7], 0);   // K
}

// Test with zero length arrays
TEST_F(GfxDeviceGrayColorSpaceTest_409, ZeroLengthLine_409) {
    unsigned char in[1] = {128};
    unsigned char out[1] = {0};

    // Zero length should be a no-op
    colorSpace.getGrayLine(in, out, 0);
    EXPECT_EQ(out[0], 0); // Should remain unchanged
}

// Test getDeviceN
TEST_F(GfxDeviceGrayColorSpaceTest_409, GetDeviceN_409) {
    GfxColor color;
    GfxColor deviceN;

    color.c[0] = gfxColorComp1;
    colorSpace.getDeviceN(&color, &deviceN);
    // Just verify it doesn't crash; exact values depend on implementation
}

// Test single element line operations
TEST_F(GfxDeviceGrayColorSpaceTest_409, SingleElementGrayLine_409) {
    unsigned char in[1] = {128};
    unsigned char out[1] = {0};

    colorSpace.getGrayLine(in, out, 1);
    EXPECT_EQ(out[0], 128);
}
