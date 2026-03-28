#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashTypes.h"



class SplashTypesTest_1047 : public ::testing::Test {

protected:

    // You can set up any common state here if necessary.

};



TEST_F(SplashTypesTest_1047, NormalOperation_1047) {

    unsigned char deviceN8[] = {0, 1, 2, 3, 4, 5, 6, 7};

    int nSpot = 2;

    EXPECT_EQ(splashDeviceN8S(deviceN8, nSpot), 6);

}



TEST_F(SplashTypesTest_1047, BoundaryCondition_Start_1047) {

    unsigned char deviceN8[] = {0, 1, 2, 3, 4, 5, 6, 7};

    int nSpot = 0;

    EXPECT_EQ(splashDeviceN8S(deviceN8, nSpot), 4);

}



TEST_F(SplashTypesTest_1047, BoundaryCondition_End_1047) {

    unsigned char deviceN8[] = {0, 1, 2, 3, 4, 5, 6, 7};

    int nSpot = 3;

    EXPECT_EQ(splashDeviceN8S(deviceN8, nSpot), 7);

}



TEST_F(SplashTypesTest_1047, InvalidBoundaryCondition_NegativeIndex_1047) {

    unsigned char deviceN8[] = {0, 1, 2, 3, 4, 5, 6, 7};

    int nSpot = -1;

    // Assuming the function does not check for negative indices and wraps around

    EXPECT_EQ(splashDeviceN8S(deviceN8, nSpot), 3); // This depends on how out-of-bounds access is handled

}



TEST_F(SplashTypesTest_1047, InvalidBoundaryCondition_OutOfBoundsIndex_1047) {

    unsigned char deviceN8[] = {0, 1, 2, 3, 4, 5, 6, 7};

    int nSpot = 4;

    // Assuming the function does not check for out-of-bounds indices and wraps around

    EXPECT_EQ(splashDeviceN8S(deviceN8, nSpot), 0); // This depends on how out-of-bounds access is handled

}
