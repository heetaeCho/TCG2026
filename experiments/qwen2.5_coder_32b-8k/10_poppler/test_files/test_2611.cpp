#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming SplashCoord and splashFloor are defined somewhere in the codebase

typedef double SplashCoord;

int splashFloor(SplashCoord x);



// Mocking any potential dependencies if necessary (none needed here)



// Test fixture for imgCoordMungeLower function

class ImgCoordMungeLowerTest_2611 : public ::testing::Test {

protected:

    // Setup and teardown can be done here if needed

};



TEST_F(ImgCoordMungeLowerTest_2611, PositiveValue_2611) {

    EXPECT_EQ(imgCoordMungeLower(3.7), 3);

}



TEST_F(ImgCoordMungeLowerTest_2611, NegativeValue_2611) {

    EXPECT_EQ(imgCoordMungeLower(-3.7), -4);

}



TEST_F(ImgCoordMungeLowerTest_2611, ZeroValue_2611) {

    EXPECT_EQ(imgCoordMungeLower(0.0), 0);

}



TEST_F(ImgCoordMungeLowerTest_2611, BoundaryConditionPositive_2611) {

    EXPECT_EQ(imgCoordMungeLower(3.0), 3);

}



TEST_F(ImgCoordMungeLowerTest_2611, BoundaryConditionNegative_2611) {

    EXPECT_EQ(imgCoordMungeLower(-3.0), -3);

}

```


