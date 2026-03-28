#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/SplashOutputDev.h"



class SplashOutputDevTest_1113 : public ::testing::Test {

protected:

    SplashOutputDev* splashOutputDev;



    void SetUp() override {

        // Assuming a default constructor exists for the sake of test setup

        splashOutputDev = new SplashOutputDev(SplashColorModeRGB8, 4, nullptr, true, splashThinLineDefault, false);

    }



    void TearDown() override {

        delete splashOutputDev;

    }

};



TEST_F(SplashOutputDevTest_1113, SetSkipText_DefaultValues_1113) {

    // Verify default values

    EXPECT_EQ(splashOutputDev->useDrawChar(), true);



    // Call the function with both parameters as false

    splashOutputDev->setSkipText(false, false);

    EXPECT_EQ(splashOutputDev->useDrawChar(), true);



    // Call the function with first parameter as true and second as false

    splashOutputDev->setSkipText(true, false);

    EXPECT_EQ(splashOutputDev->useDrawChar(), false);



    // Call the function with both parameters as true

    splashOutputDev->setSkipText(true, true);

    EXPECT_EQ(splashOutputDev->useDrawChar(), false);



    // Call the function with first parameter as false and second as true

    splashOutputDev->setSkipText(false, true);

    EXPECT_EQ(splashOutputDev->useDrawChar(), false);

}



TEST_F(SplashOutputDevTest_1113, SetSkipText_BoundaryConditions_1113) {

    // Boundary condition: Both parameters are false

    splashOutputDev->setSkipText(false, false);

    EXPECT_EQ(splashOutputDev->useDrawChar(), true);



    // Boundary condition: First parameter is true, second is false

    splashOutputDev->setSkipText(true, false);

    EXPECT_EQ(splashOutputDev->useDrawChar(), false);



    // Boundary condition: Both parameters are true

    splashOutputDev->setSkipText(true, true);

    EXPECT_EQ(splashOutputDev->useDrawChar(), false);



    // Boundary condition: First parameter is false, second is true

    splashOutputDev->setSkipText(false, true);

    EXPECT_EQ(splashOutputDev->useDrawChar(), false);

}



TEST_F(SplashOutputDevTest_1113, SetSkipText_MultipleCalls_1113) {

    // Call the function multiple times with different parameters

    splashOutputDev->setSkipText(true, false);

    EXPECT_EQ(splashOutputDev->useDrawChar(), false);



    splashOutputDev->setSkipText(false, true);

    EXPECT_EQ(splashOutputDev->useDrawChar(), false);



    splashOutputDev->setSkipText(true, true);

    EXPECT_EQ(splashOutputDev->useDrawChar(), false);



    splashOutputDev->setSkipText(false, false);

    EXPECT_EQ(splashOutputDev->useDrawChar(), true);

}
