#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming SplashCoord and splashFloor are defined somewhere in the codebase

typedef double SplashCoord;

int splashFloor(SplashCoord x);



class ImgCoordMungeUpperTest : public ::testing::Test {

protected:

    // No additional setup required for this simple function

};



TEST_F(ImgCoordMungeUpperTest, NormalOperation_2612) {

    EXPECT_EQ(imgCoordMungeUpper(3.7), 4);

    EXPECT_EQ(imgCoordMungeUpper(5.0), 6);

}



TEST_F(ImgCoordMungeUpperTest, BoundaryConditions_2612) {

    EXPECT_EQ(imgCoordMungeUpper(0.0), 1);

    EXPECT_EQ(imgCoordMungeUpper(-1.9), -1);

}



TEST_F(ImgCoordMungeUpperTest, NegativeValues_2612) {

    EXPECT_EQ(imgCoordMungeUpper(-3.7), -3);

    EXPECT_EQ(imgCoordMungeUpper(-5.0), -4);

}
