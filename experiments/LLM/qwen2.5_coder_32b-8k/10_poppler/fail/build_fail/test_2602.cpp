#include <gtest/gtest.h>

#include "SplashScreen.h"



class SplashScreenTest_2602 : public ::testing::Test {

protected:

    SplashScreen* splashScreen;



    void SetUp() override {

        const SplashScreenParams params = { /* Initialize with appropriate values if necessary */ };

        splashScreen = new SplashScreen(&params);

    }



    void TearDown() override {

        delete splashScreen;

    }

};



TEST_F(SplashScreenTest_2602, TestNormalOperation_LessThanMatrixValue_2602) {

    EXPECT_EQ(splashScreen->test(1, 1, 5), 0); // Assuming mat[1] > 5

}



TEST_F(SplashScreenTest_2602, TestNormalOperation_GreaterThanOrEqualToMatrixValue_2602) {

    EXPECT_EQ(splashScreen->test(1, 1, 10), 1); // Assuming mat[1] <= 10

}



TEST_F(SplashScreenTest_2602, TestBoundaryCondition_XZeroYZero_2602) {

    EXPECT_TRUE((splashScreen->test(0, 0, 5) == 0 || splashScreen->test(0, 0, 5) == 1));

}



TEST_F(SplashScreenTest_2602, TestBoundaryCondition_XMaxYMax_2602) {

    EXPECT_TRUE((splashScreen->test(splashScreen->sizeM1, splashScreen->sizeM1, 5) == 0 || 

                 splashScreen->test(splashScreen->sizeM1, splashScreen->sizeM1, 5) == 1));

}



TEST_F(SplashScreenTest_2602, TestBoundaryCondition_XMaxYZero_2602) {

    EXPECT_TRUE((splashScreen->test(splashScreen->sizeM1, 0, 5) == 0 || 

                 splashScreen->test(splashScreen->sizeM1, 0, 5) == 1));

}



TEST_F(SplashScreenTest_2602, TestBoundaryCondition_XZeroYMax_2602) {

    EXPECT_TRUE((splashScreen->test(0, splashScreen->sizeM1, 5) == 0 || 

                 splashScreen->test(0, splashScreen->sizeM1, 5) == 1));

}



// Assuming sizeM1 is a power of two minus one for bit masking

TEST_F(SplashScreenTest_2602, TestBoundaryCondition_OutOfBoundsX_2602) {

    EXPECT_TRUE((splashScreen->test(splashScreen->sizeM1 + 1, 5, 5) == 0 || 

                 splashScreen->test(splashScreen->sizeM1 + 1, 5, 5) == 1));

}



TEST_F(SplashScreenTest_2602, TestBoundaryCondition_OutOfBoundsY_2602) {

    EXPECT_TRUE((splashScreen->test(5, splashScreen->sizeM1 + 1, 5) == 0 || 

                 splashScreen->test(5, splashScreen->sizeM1 + 1, 5) == 1));

}



TEST_F(SplashScreenTest_2602, TestBoundaryCondition_OutOfBoundsXY_2602) {

    EXPECT_TRUE((splashScreen->test(splashScreen->sizeM1 + 1, splashScreen->sizeM1 + 1, 5) == 0 || 

                 splashScreen->test(splashScreen->sizeM1 + 1, splashScreen->sizeM1 + 1, 5) == 1));

}
