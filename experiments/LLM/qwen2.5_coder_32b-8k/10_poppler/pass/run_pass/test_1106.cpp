#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"



class SplashOutputDevTest_1106 : public ::testing::Test {

protected:

    SplashOutputDev* splashOutputDev;



    void SetUp() override {

        // Assuming some default parameters for the constructor

        splashOutputDev = new SplashOutputDev(splashModeRGB8, 4, nullptr, false, splashThinLineDefault, false);

    }



    void TearDown() override {

        delete splashOutputDev;

    }

};



TEST_F(SplashOutputDevTest_1106, UseShadedFills_NormalCaseTrue_1106) {

    EXPECT_TRUE(splashOutputDev->useShadedFills(3));

}



TEST_F(SplashOutputDevTest_1106, UseShadedFills_NormalCaseFalse_1106) {

    EXPECT_FALSE(splashOutputDev->useShadedFills(6));

}



TEST_F(SplashOutputDevTest_1106, UseShadedFills_BoundaryConditionLower_1106) {

    EXPECT_FALSE(splashOutputDev->useShadedFills(0));

}



TEST_F(SplashOutputDevTest_1106, UseShadedFills_BoundaryConditionUpper_1106) {

    EXPECT_TRUE(splashOutputDev->useShadedFills(5));

    EXPECT_FALSE(splashOutputDev->useShadedFills(6));

}
