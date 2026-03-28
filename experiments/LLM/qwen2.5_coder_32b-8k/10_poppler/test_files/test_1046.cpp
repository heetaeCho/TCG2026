#include <gtest/gtest.h>

#include "splash/SplashTypes.h"



class SplashTypesTest_1046 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed.

};



TEST_F(SplashTypesTest_1046, splashDeviceN8K_ReturnsFourthElement_1046) {

    unsigned char color[] = {255, 192, 128, 64};

    EXPECT_EQ(splashDeviceN8K(color), 64);

}



TEST_F(SplashTypesTest_1046, splashDeviceN8K_ZeroInitializedArray_ReturnsZero_1046) {

    unsigned char color[] = {0, 0, 0, 0};

    EXPECT_EQ(splashDeviceN8K(color), 0);

}



TEST_F(SplashTypesTest_1046, splashDeviceN8K_MaxValuesArray_ReturnsMaxValue_1046) {

    unsigned char color[] = {255, 255, 255, 255};

    EXPECT_EQ(splashDeviceN8K(color), 255);

}
