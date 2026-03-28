#include <gtest/gtest.h>

#include <climits>



// Mocking GfxRGB for testing purposes if needed

struct GfxRGB {

    int r;

    int g;

    int b;



    bool operator==(const GfxRGB& other) const {

        return r == other.r && g == other.g && b == other.b;

    }

};



// Function signature from the provided code

void applyMask(unsigned int *imagePointer, int length, GfxRGB matteColor, unsigned char *alphaPointer);



TEST(applyMaskTest_1927, NormalOperation_1927) {

    unsigned int image[4] = {0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFFFF00};

    GfxRGB matteColor = {128, 128, 128};

    unsigned char alpha[] = {128, 64, 32, 0};



    applyMask(image, 4, matteColor, alpha);



    EXPECT_EQ(image[0], 0x808080FF);

    EXPECT_EQ(image[1], 0x55AA55FF);

    EXPECT_EQ(image[2], 0x2AAA2AFF);

    EXPECT_EQ(image[3], 0xFFFFFF00);

}



TEST(applyMaskTest_1927, BoundaryCondition_ZeroLength_1927) {

    unsigned int image[] = {0xFF0000FF};

    GfxRGB matteColor = {128, 128, 128};

    unsigned char alpha[] = {128};



    applyMask(image, 0, matteColor, alpha);



    EXPECT_EQ(image[0], 0xFF0000FF);

}



TEST(applyMaskTest_1927, BoundaryCondition_MaxLength_1927) {

    const int length = INT_MAX / 4; // Assuming unsigned int is 4 bytes

    std::vector<unsigned int> image(length, 0xFFFFFFFF);

    GfxRGB matteColor = {128, 128, 128};

    std::vector<unsigned char> alpha(length, 128);



    applyMask(image.data(), length, matteColor, alpha.data());



    for (int i = 0; i < length; ++i) {

        EXPECT_EQ(image[i], 0x808080FF);

    }

}



TEST(applyMaskTest_1927, BoundaryCondition_ZeroAlpha_1927) {

    unsigned int image[4] = {0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFFFF00};

    GfxRGB matteColor = {128, 128, 128};

    unsigned char alpha[] = {0, 0, 0, 0};



    applyMask(image, 4, matteColor, alpha);



    EXPECT_EQ(image[0], 0xFF0000FF);

    EXPECT_EQ(image[1], 0x00FF00FF);

    EXPECT_EQ(image[2], 0x0000FFFF);

    EXPECT_EQ(image[3], 0xFFFFFF00);

}



TEST(applyMaskTest_1927, BoundaryCondition_MaxAlpha_1927) {

    unsigned int image[4] = {0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFFFF00};

    GfxRGB matteColor = {128, 128, 128};

    unsigned char alpha[] = {255, 255, 255, 255};



    applyMask(image, 4, matteColor, alpha);



    EXPECT_EQ(image[0], 0x808080FF);

    EXPECT_EQ(image[1], 0x808080FF);

    EXPECT_EQ(image[2], 0x808080FF);

    EXPECT_EQ(image[3], 0x808080FF);

}



TEST(applyMaskTest_1927, ExceptionalCase_NegativeLength_1927) {

    unsigned int image[4] = {0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFFFF00};

    GfxRGB matteColor = {128, 128, 128};

    unsigned char alpha[] = {128, 64, 32, 0};



    // This test assumes that negative length will not cause a crash and will handle gracefully.

    applyMask(image, -4, matteColor, alpha);



    // No specific expectation as behavior is undefined for negative lengths

}



TEST(applyMaskTest_1927, ExceptionalCase_NullImagePointer_1927) {

    GfxRGB matteColor = {128, 128, 128};

    unsigned char alpha[] = {128};



    // This test assumes that null image pointer will not cause a crash and will handle gracefully.

    applyMask(nullptr, 1, matteColor, alpha);



    // No specific expectation as behavior is undefined for null pointers

}



TEST(applyMaskTest_1927, ExceptionalCase_NullAlphaPointer_1927) {

    unsigned int image[4] = {0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFFFF00};

    GfxRGB matteColor = {128, 128, 128};



    // This test assumes that null alpha pointer will not cause a crash and will handle gracefully.

    applyMask(image, 4, matteColor, nullptr);



    // No specific expectation as behavior is undefined for null pointers

}



TEST(applyMaskTest_1927, ExceptionalCase_OutOfRangeValues_1927) {

    unsigned int image[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};

    GfxRGB matteColor = {256, -1, 300}; // Out of range values for colors

    unsigned char alpha[] = {128, 128, 128, 128};



    applyMask(image, 4, matteColor, alpha);



    EXPECT_EQ(image[0], 0x808080FF);

    EXPECT_EQ(image[1], 0x808080FF);

    EXPECT_EQ(image[2], 0x808080FF);

    EXPECT_EQ(image[3], 0x808080FF);

}
