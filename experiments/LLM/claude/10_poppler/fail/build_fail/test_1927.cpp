#include <gtest/gtest.h>
#include <cstring>
#include <algorithm>
#include <vector>

// We need GfxRGB and GfxColorComp from GfxState.h
#include "GfxState.h"

// Since applyMask is static inline in the .cc file, we include it to get access
// We need to handle potential conflicts - include the implementation file
#include "CairoOutputDev.cc"

class ApplyMaskTest_1927 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: When alpha is 0, pixel should remain unchanged
TEST_F(ApplyMaskTest_1927, AlphaZeroLeavesPixelUnchanged_1927) {
    unsigned int image[1] = {0xAABBCCDD};
    unsigned int original = image[0];
    unsigned char alpha[1] = {0};
    GfxRGB matte;
    matte.r = 128;
    matte.g = 128;
    matte.b = 128;

    applyMask(image, 1, matte, alpha);

    EXPECT_EQ(image[0], original);
}

// Test: When alpha is 255, pixel values are recalculated as (pixel - matte) * 255 / 255 + matte = pixel
TEST_F(ApplyMaskTest_1927, AlphaFullOpaque_1927) {
    // With alpha=255, result should be: matte + (p - matte) * 255 / 255 = p
    // Pixel bytes in memory: p[0]=B, p[1]=G, p[2]=R, p[3]=A(unused)
    unsigned char pixelBytes[4] = {100, 150, 200, 0}; // B=100, G=150, R=200
    unsigned int image[1];
    memcpy(image, pixelBytes, 4);

    unsigned char alpha[1] = {255};
    GfxRGB matte;
    matte.r = 0;
    matte.g = 0;
    matte.b = 0;

    applyMask(image, 1, matte, alpha);

    // Expected: r=200, g=150, b=100
    unsigned int expected = (200u << 16) | (150u << 8) | 100u;
    EXPECT_EQ(image[0], expected);
}

// Test: Zero matte color, half alpha
TEST_F(ApplyMaskTest_1927, ZeroMatteHalfAlpha_1927) {
    // With matte=0, alpha=128: result = 0 + (p - 0) * 255 / 128 = p * 255 / 128
    // B=64: 64*255/128 = 127 (integer division)
    // G=64: same = 127
    // R=64: same = 127
    unsigned char pixelBytes[4] = {64, 64, 64, 0};
    unsigned int image[1];
    memcpy(image, pixelBytes, 4);

    unsigned char alpha[1] = {128};
    GfxRGB matte;
    matte.r = 0;
    matte.g = 0;
    matte.b = 0;

    applyMask(image, 1, matte, alpha);

    int expected_channel = 64 * 255 / 128; // = 127
    unsigned int expected = (expected_channel << 16) | (expected_channel << 8) | expected_channel;
    EXPECT_EQ(image[0], expected);
}

// Test: Clamping to 255 when computation exceeds 255
TEST_F(ApplyMaskTest_1927, ClampToMax255_1927) {
    // matte.r=0, pixel_r=200, alpha=100
    // result = 0 + (200 - 0) * 255 / 100 = 510 -> clamped to 255
    unsigned char pixelBytes[4] = {200, 200, 200, 0};
    unsigned int image[1];
    memcpy(image, pixelBytes, 4);

    unsigned char alpha[1] = {100};
    GfxRGB matte;
    matte.r = 0;
    matte.g = 0;
    matte.b = 0;

    applyMask(image, 1, matte, alpha);

    unsigned int expected = (255u << 16) | (255u << 8) | 255u;
    EXPECT_EQ(image[0], expected);
}

// Test: Clamping to 0 when computation goes below 0
TEST_F(ApplyMaskTest_1927, ClampToMin0_1927) {
    // matte=200, pixel=0, alpha=1
    // result = 200 + (0 - 200) * 255 / 1 = 200 - 51000 = -50800 -> clamped to 0
    unsigned char pixelBytes[4] = {0, 0, 0, 0};
    unsigned int image[1];
    memcpy(image, pixelBytes, 4);

    unsigned char alpha[1] = {1};
    GfxRGB matte;
    matte.r = 200;
    matte.g = 200;
    matte.b = 200;

    applyMask(image, 1, matte, alpha);

    unsigned int expected = 0;
    EXPECT_EQ(image[0], expected);
}

// Test: Multiple pixels, some with alpha=0 and some with alpha>0
TEST_F(ApplyMaskTest_1927, MultiplePixelsMixedAlpha_1927) {
    unsigned int image[3];
    unsigned char px0[4] = {50, 60, 70, 0};
    unsigned char px1[4] = {80, 90, 100, 0};
    unsigned char px2[4] = {110, 120, 130, 0};
    memcpy(&image[0], px0, 4);
    memcpy(&image[1], px1, 4);
    memcpy(&image[2], px2, 4);

    unsigned int original1 = image[1];
    unsigned char alpha[3] = {255, 0, 255};
    GfxRGB matte;
    matte.r = 0;
    matte.g = 0;
    matte.b = 0;

    applyMask(image, 3, matte, alpha);

    // Pixel 0: alpha=255, result = pixel values directly
    unsigned int expected0 = (70u << 16) | (60u << 8) | 50u;
    EXPECT_EQ(image[0], expected0);

    // Pixel 1: alpha=0, unchanged
    EXPECT_EQ(image[1], original1);

    // Pixel 2: alpha=255, result = pixel values directly
    unsigned int expected2 = (130u << 16) | (120u << 8) | 110u;
    EXPECT_EQ(image[2], expected2);
}

// Test: Length zero - no changes
TEST_F(ApplyMaskTest_1927, ZeroLength_1927) {
    unsigned int image[1] = {0xDEADBEEF};
    unsigned char alpha[1] = {255};
    GfxRGB matte;
    matte.r = 0;
    matte.g = 0;
    matte.b = 0;

    applyMask(image, 0, matte, alpha);

    EXPECT_EQ(image[0], 0xDEADBEEFu);
}

// Test: Alpha=1 with pixel matching matte - should stay at matte value
TEST_F(ApplyMaskTest_1927, PixelEqualsMatte_1927) {
    // matte=100, pixel=100, alpha=1
    // result = 100 + (100 - 100) * 255 / 1 = 100
    unsigned char pixelBytes[4] = {100, 100, 100, 0};
    unsigned int image[1];
    memcpy(image, pixelBytes, 4);

    unsigned char alpha[1] = {1};
    GfxRGB matte;
    matte.r = 100;
    matte.g = 100;
    matte.b = 100;

    applyMask(image, 1, matte, alpha);

    unsigned int expected = (100u << 16) | (100u << 8) | 100u;
    EXPECT_EQ(image[0], expected);
}

// Test: Different matte color channels
TEST_F(ApplyMaskTest_1927, DifferentMatteChannels_1927) {
    // matte: r=10, g=20, b=30
    // pixel: B=30, G=20, R=10 (all match matte)
    // alpha=128
    // result should be matte values since pixel == matte
    unsigned char pixelBytes[4] = {30, 20, 10, 0}; // B=30, G=20, R=10
    unsigned int image[1];
    memcpy(image, pixelBytes, 4);

    unsigned char alpha[1] = {128};
    GfxRGB matte;
    matte.r = 10;
    matte.g = 20;
    matte.b = 30;

    applyMask(image, 1, matte, alpha);

    unsigned int expected = (10u << 16) | (20u << 8) | 30u;
    EXPECT_EQ(image[0], expected);
}

// Test: Alpha=1 with large difference causes clamping to 255
TEST_F(ApplyMaskTest_1927, AlphaOneHighPixelValue_1927) {
    // matte=0, pixel=255, alpha=1
    // result = 0 + (255 - 0) * 255 / 1 = 65025 -> clamped to 255
    unsigned char pixelBytes[4] = {255, 255, 255, 0};
    unsigned int image[1];
    memcpy(image, pixelBytes, 4);

    unsigned char alpha[1] = {1};
    GfxRGB matte;
    matte.r = 0;
    matte.g = 0;
    matte.b = 0;

    applyMask(image, 1, matte, alpha);

    unsigned int expected = (255u << 16) | (255u << 8) | 255u;
    EXPECT_EQ(image[0], expected);
}

// Test: White matte with black pixel and low alpha should clamp to 0
TEST_F(ApplyMaskTest_1927, WhiteMatteBlackPixelLowAlpha_1927) {
    // matte=255, pixel=0, alpha=1
    // result = 255 + (0 - 255) * 255 / 1 = 255 - 65025 -> clamped to 0
    unsigned char pixelBytes[4] = {0, 0, 0, 0};
    unsigned int image[1];
    memcpy(image, pixelBytes, 4);

    unsigned char alpha[1] = {1};
    GfxRGB matte;
    matte.r = 255;
    matte.g = 255;
    matte.b = 255;

    applyMask(image, 1, matte, alpha);

    unsigned int expected = 0;
    EXPECT_EQ(image[0], expected);
}

// Test: Large array of pixels
TEST_F(ApplyMaskTest_1927, LargeArray_1927) {
    const int N = 1000;
    std::vector<unsigned int> image(N);
    std::vector<unsigned char> alpha(N);

    for (int i = 0; i < N; i++) {
        unsigned char pixelBytes[4] = {100, 100, 100, 0};
        memcpy(&image[i], pixelBytes, 4);
        alpha[i] = 255;
    }

    GfxRGB matte;
    matte.r = 0;
    matte.g = 0;
    matte.b = 0;

    applyMask(image.data(), N, matte, alpha.data());

    unsigned int expected = (100u << 16) | (100u << 8) | 100u;
    for (int i = 0; i < N; i++) {
        EXPECT_EQ(image[i], expected) << "Failed at index " << i;
    }
}
