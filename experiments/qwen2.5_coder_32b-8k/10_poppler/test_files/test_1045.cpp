#include <gtest/gtest.h>



// Assuming SplashColorPtr is defined as an array of unsigned char with at least 3 elements.

typedef unsigned char* SplashColorPtr;



unsigned char splashDeviceN8Y(SplashColorPtr deviceN8) {

    return deviceN8[2];

}



class SplashTypesTest : public ::testing::Test {

protected:

    unsigned char colorData[3];

    SplashColorPtr deviceN8;



    void SetUp() override {

        deviceN8 = colorData;

    }

};



TEST_F(SplashTypesTest_1045, NormalOperation_1045) {

    deviceN8[0] = 255;

    deviceN8[1] = 128;

    deviceN8[2] = 64;

    EXPECT_EQ(splashDeviceN8Y(deviceN8), 64);

}



TEST_F(SplashTypesTest_1045, BoundaryCondition_Zero_1045) {

    deviceN8[0] = 0;

    deviceN8[1] = 0;

    deviceN8[2] = 0;

    EXPECT_EQ(splashDeviceN8Y(deviceN8), 0);

}



TEST_F(SplashTypesTest_1045, BoundaryCondition_MaxValue_1045) {

    deviceN8[0] = 255;

    deviceN8[1] = 255;

    deviceN8[2] = 255;

    EXPECT_EQ(splashDeviceN8Y(deviceN8), 255);

}



TEST_F(SplashTypesTest_1045, MixedValues_1045) {

    deviceN8[0] = 100;

    deviceN8[1] = 200;

    deviceN8[2] = 150;

    EXPECT_EQ(splashDeviceN8Y(deviceN8), 150);

}
