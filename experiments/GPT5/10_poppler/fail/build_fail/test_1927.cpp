#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <algorithm>

// Mock dependencies
struct GfxRGB {
    int r, g, b;
    bool operator==(const GfxRGB& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
};

static inline void applyMask(unsigned int *imagePointer, int length, GfxRGB matteColor, unsigned char *alphaPointer) { 
    unsigned char *p, r, g, b; 
    int i; 
    for (i = 0, p = (unsigned char *)imagePointer; i < length; i++, p += 4, alphaPointer++) { 
        if (*alphaPointer) { 
            b = std::clamp(matteColor.b + (int)(p[0] - matteColor.b) * 255 / *alphaPointer, 0, 255); 
            g = std::clamp(matteColor.g + (int)(p[1] - matteColor.g) * 255 / *alphaPointer, 0, 255); 
            r = std::clamp(matteColor.r + (int)(p[2] - matteColor.r) * 255 / *alphaPointer, 0, 255); 
            imagePointer[i] = (r << 16) | (g << 8) | (b << 0); 
        } 
    } 
}

TEST_F(CairoOutputDevTest_1927, ApplyMaskNormalOperation_1927) {
    unsigned int image[4] = {0xFF0000, 0x00FF00, 0x0000FF, 0x123456}; // Initial pixel colors (red, green, blue, random)
    unsigned char alpha[4] = {255, 255, 255, 128}; // Full opacity for first three, half opacity for last
    GfxRGB matteColor = {0, 0, 0}; // Black matte color

    applyMask(image, 4, matteColor, alpha);

    // Expected results: after applying the mask, the image pixels will blend with the black matte color
    EXPECT_EQ(image[0], 0x000000); // red pixel blended with black
    EXPECT_EQ(image[1], 0x000000); // green pixel blended with black
    EXPECT_EQ(image[2], 0x000000); // blue pixel blended with black
    EXPECT_EQ(image[3], 0x5E7F86); // partially transparent pixel blended with black
}

TEST_F(CairoOutputDevTest_1927, ApplyMaskZeroAlpha_1927) {
    unsigned int image[3] = {0xFF0000, 0x00FF00, 0x0000FF}; // Red, Green, Blue
    unsigned char alpha[3] = {0, 0, 0}; // Zero opacity for all pixels
    GfxRGB matteColor = {0, 0, 0}; // Black matte color

    applyMask(image, 3, matteColor, alpha);

    // Expected results: no change in color, since alpha is zero (completely transparent)
    EXPECT_EQ(image[0], 0xFF0000); // Red remains unchanged
    EXPECT_EQ(image[1], 0x00FF00); // Green remains unchanged
    EXPECT_EQ(image[2], 0x0000FF); // Blue remains unchanged
}

TEST_F(CairoOutputDevTest_1927, ApplyMaskMaxAlpha_1927) {
    unsigned int image[3] = {0xFF0000, 0x00FF00, 0x0000FF}; // Red, Green, Blue
    unsigned char alpha[3] = {255, 255, 255}; // Full opacity for all pixels
    GfxRGB matteColor = {255, 255, 255}; // White matte color

    applyMask(image, 3, matteColor, alpha);

    // Expected results: no blending occurs as alpha is maximum
    EXPECT_EQ(image[0], 0xFFFFFF); // Red becomes white
    EXPECT_EQ(image[1], 0xFFFFFF); // Green becomes white
    EXPECT_EQ(image[2], 0xFFFFFF); // Blue becomes white
}

TEST_F(CairoOutputDevTest_1927, ApplyMaskNegativeAlpha_1927) {
    unsigned int image[3] = {0xFF0000, 0x00FF00, 0x0000FF}; // Red, Green, Blue
    unsigned char alpha[3] = {255, 255, -1}; // Negative alpha (invalid, but should be clamped to 0)
    GfxRGB matteColor = {255, 255, 255}; // White matte color

    applyMask(image, 3, matteColor, alpha);

    // Since alpha is invalid (negative), it will be treated as 0 (no blending)
    EXPECT_EQ(image[0], 0xFFFFFF); // Red becomes white
    EXPECT_EQ(image[1], 0xFFFFFF); // Green becomes white
    EXPECT_EQ(image[2], 0x0000FF); // Blue remains unchanged
}

TEST_F(CairoOutputDevTest_1927, ApplyMaskClamping_1927) {
    unsigned int image[1] = {0xFF0000}; // Red pixel
    unsigned char alpha[1] = {0}; // Zero alpha, fully transparent
    GfxRGB matteColor = {255, 255, 255}; // White matte color

    applyMask(image, 1, matteColor, alpha);

    // Expected result: no change because alpha is zero
    EXPECT_EQ(image[0], 0xFF0000); // Red remains unchanged
}