#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/poppler/splash/SplashTypes.h"

    void splashOutBlendColorDodge(SplashColorPtr src, SplashColorPtr dest, SplashColorPtr blend, SplashColorMode cm);

}



TEST(splashOutBlendColorDodgeTest_1582, NormalOperation_RGB8_1582) {

    SplashColorPtr src = new unsigned char[3]{127, 64, 32};

    SplashColorPtr dest = new unsigned char[3]{64, 127, 192};

    SplashColorPtr blend = new unsigned char[3]{0, 0, 0};



    splashOutBlendColorDodge(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 191);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);



    delete[] src;

    delete[] dest;

    delete[] blend;

}



TEST(splashOutBlendColorDodgeTest_1582, NormalOperation_CMYK8_1582) {

    SplashColorPtr src = new unsigned char[4]{127, 64, 32, 0};

    SplashColorPtr dest = new unsigned char[4]{64, 127, 192, 0};

    SplashColorPtr blend = new unsigned char[4]{0, 0, 0, 0};



    splashOutBlendColorDodge(src, dest, blend, splashModeCMYK8);



    EXPECT_EQ(blend[0], 63);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);

    EXPECT_EQ(blend[3], 0);



    delete[] src;

    delete[] dest;

    delete[] blend;

}



TEST(splashOutBlendColorDodgeTest_1582, BoundaryCondition_SrcMax_RGB8_1582) {

    SplashColorPtr src = new unsigned char[3]{255, 255, 255};

    SplashColorPtr dest = new unsigned char[3]{64, 127, 192};

    SplashColorPtr blend = new unsigned char[3]{0, 0, 0};



    splashOutBlendColorDodge(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);



    delete[] src;

    delete[] dest;

    delete[] blend;

}



TEST(splashOutBlendColorDodgeTest_1582, BoundaryCondition_DestMax_RGB8_1582) {

    SplashColorPtr src = new unsigned char[3]{0, 0, 0};

    SplashColorPtr dest = new unsigned char[3]{255, 255, 255};

    SplashColorPtr blend = new unsigned char[3]{0, 0, 0};



    splashOutBlendColorDodge(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 255);

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);



    delete[] src;

    delete[] dest;

    delete[] blend;

}



TEST(splashOutBlendColorDodgeTest_1582, BoundaryCondition_AllZero_RGB8_1582) {

    SplashColorPtr src = new unsigned char[3]{0, 0, 0};

    SplashColorPtr dest = new unsigned char[3]{0, 0, 0};

    SplashColorPtr blend = new unsigned char[3]{0, 0, 0};



    splashOutBlendColorDodge(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 0);

    EXPECT_EQ(blend[1], 0);

    EXPECT_EQ(blend[2], 0);



    delete[] src;

    delete[] dest;

    delete[] blend;

}



TEST(splashOutBlendColorDodgeTest_1582, ExceptionalCase_DivisionByZero_RGB8_1582) {

    SplashColorPtr src = new unsigned char[3]{255, 0, 0};

    SplashColorPtr dest = new unsigned char[3]{64, 127, 192};

    SplashColorPtr blend = new unsigned char[3]{0, 0, 0};



    splashOutBlendColorDodge(src, dest, blend, splashModeRGB8);



    EXPECT_EQ(blend[0], 255);

    // No division by zero should occur for other channels

    EXPECT_EQ(blend[1], 255);

    EXPECT_EQ(blend[2], 255);



    delete[] src;

    delete[] dest;

    delete[] blend;

}
