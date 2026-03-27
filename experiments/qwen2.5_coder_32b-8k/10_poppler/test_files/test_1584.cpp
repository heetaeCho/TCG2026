#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function to be tested is declared in a header file

extern void splashOutBlendHardLight(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);



TEST(splashOutBlendHardLightTest_1584, NormalOperationRGB8_1584) {

    unsigned char src[] = {255, 0, 0}; // Red

    unsigned char dest[] = {0, 255, 0}; // Green

    unsigned char blend[3];



    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

}



TEST(splashOutBlendHardLightTest_1584, NormalOperationCMYK8_1584) {

    unsigned char src[] = {255, 0, 0, 0}; // Cmyk Red

    unsigned char dest[] = {0, 255, 0, 0}; // Cmyk Green

    unsigned char blend[4];



    splashOutBlendHardLight(src, dest, blend, splashModeCMYK8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

    EXPECT_EQ(blend[3], 0);

}



TEST(splashOutBlendHardLightTest_1584, BoundaryConditionMaxValues_1584) {

    unsigned char src[] = {255, 255, 255}; // White

    unsigned char dest[] = {255, 255, 255}; // White

    unsigned char blend[3];



    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

}



TEST(splashOutBlendHardLightTest_1584, BoundaryConditionMinValues_1584) {

    unsigned char src[] = {0, 0, 0}; // Black

    unsigned char dest[] = {0, 0, 0}; // Black

    unsigned char blend[3];



    splashOutBlendHardLight(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);

}



TEST(splashOutBlendHardLightTest_1584, ExceptionalCaseInvalidColorMode_1584) {

    unsigned char src[] = {128, 128, 128};

    unsigned char dest[] = {128, 128, 128};

    unsigned char blend[3];



    // Assuming splashOutBlendHardLight handles invalid color mode gracefully

    EXPECT_NO_THROW(splashOutBlendHardLight(src, dest, blend, static_cast<SplashColorMode>(99)));

}
