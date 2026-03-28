#include <gtest/gtest.h>

#include "SplashTypes.h"



class SplashTypesTest_1044 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialization code if needed

    }



    void TearDown() override {

        // Cleanup code if needed

    }

};



TEST_F(SplashTypesTest_1044, splashDeviceN8M_ReturnsSecondElement_1044) {

    SplashColorPtr deviceN8 = new unsigned char[3]{50, 75, 100};

    EXPECT_EQ(splashDeviceN8M(deviceN8), 75);

    delete[] deviceN8;

}



TEST_F(SplashTypesTest_1044, splashDeviceN8M_BoundaryCondition_Zero_1044) {

    SplashColorPtr deviceN8 = new unsigned char[3]{0, 0, 255};

    EXPECT_EQ(splashDeviceN8M(deviceN8), 0);

    delete[] deviceN8;

}



TEST_F(SplashTypesTest_1044, splashDeviceN8M_BoundaryCondition_Maximum_1044) {

    SplashColorPtr deviceN8 = new unsigned char[3]{255, 255, 0};

    EXPECT_EQ(splashDeviceN8M(deviceN8), 255);

    delete[] deviceN8;

}
