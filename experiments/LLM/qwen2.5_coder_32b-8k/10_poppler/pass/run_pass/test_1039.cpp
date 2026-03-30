#include <gtest/gtest.h>

#include "./TestProjects/poppler/splash/SplashTypes.h"



class SplashCMYK8CTest : public ::testing::Test {

protected:

    SplashColorPtr cmyk8;

    

    void SetUp() override {

        cmyk8 = new unsigned char[4];  // Assuming CMYK has 4 components

    }



    void TearDown() override {

        delete[] cmyk8;

    }

};



TEST_F(SplashCMYK8CTest, GetCValue_Zero_1039) {

    cmyk8[0] = 0;

    EXPECT_EQ(splashCMYK8C(cmyk8), 0);

}



TEST_F(SplashCMYK8CTest, GetCValue_Maximum_1039) {

    cmyk8[0] = 255;

    EXPECT_EQ(splashCMYK8C(cmyk8), 255);

}



TEST_F(SplashCMYK8CTest, GetCValue_RandomValue_1039) {

    cmyk8[0] = 128;

    EXPECT_EQ(splashCMYK8C(cmyk8), 128);

}



TEST_F(SplashCMYK8CTest, UnchangedOtherValues_1039) {

    cmyk8[0] = 50;

    cmyk8[1] = 100;

    cmyk8[2] = 150;

    cmyk8[3] = 200;



    EXPECT_EQ(splashCMYK8C(cmyk8), 50);

}
