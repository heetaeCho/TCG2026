#include <gtest/gtest.h>

#include "./TestProjects/poppler/splash/SplashTypes.h"



// Define a fixture if necessary, though in this case it's not needed as we're testing a simple function.

class SplashCMYK8MTest_1040 : public ::testing::Test {

protected:

    // No additional setup or teardown required for this test

};



TEST_F(SplashCMYK8MTest_1040, NormalOperation_1040) {

    SplashColorPtr cmyk8 = new unsigned char[4]{255, 127, 63, 31}; // Example values for CMYK

    EXPECT_EQ(splashCMYK8M(cmyk8), 127);

    delete[] cmyk8;

}



TEST_F(SplashCMYK8MTest_1040, BoundaryConditions_ZeroValues_1040) {

    SplashColorPtr cmyk8 = new unsigned char[4]{0, 0, 0, 0};

    EXPECT_EQ(splashCMYK8M(cmyk8), 0);

    delete[] cmyk8;

}



TEST_F(SplashCMYK8MTest_1040, BoundaryConditions_MaxValues_1040) {

    SplashColorPtr cmyk8 = new unsigned char[4]{255, 255, 255, 255};

    EXPECT_EQ(splashCMYK8M(cmyk8), 255);

    delete[] cmyk8;

}



TEST_F(SplashCMYK8MTest_1040, BoundaryConditions_MixedValues_1040) {

    SplashColorPtr cmyk8 = new unsigned char[4]{10, 20, 30, 40};

    EXPECT_EQ(splashCMYK8M(cmyk8), 20);

    delete[] cmyk8;

}
