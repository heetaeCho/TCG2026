#include <gtest/gtest.h>

#include "SplashPattern.h"



class SplashSolidColorTest_1051 : public ::testing::Test {

protected:

    void SetUp() override {

        color = new SplashColor();

        splashSolidColor = new SplashSolidColor(color);

    }



    void TearDown() override {

        delete splashSolidColor;

        delete[] color;

    }



    SplashColor* color;

    SplashSolidColor* splashSolidColor;

};



TEST_F(SplashSolidColorTest_1051, IsStatic_ReturnsTrue_1051) {

    EXPECT_TRUE(splashSolidColor->isStatic());

}



// Assuming getColor is a function that returns true on success and modifies the passed-in color

TEST_F(SplashSolidColorTest_1051, GetColor_Success_1051) {

    SplashColor c;

    EXPECT_TRUE(splashSolidColor->getColor(0, 0, &c));

}



// Assuming copy creates a new instance of SplashSolidColor

TEST_F(SplashSolidColorTest_1051, Copy_ReturnsNewInstance_1051) {

    SplashPattern* copiedPattern = splashSolidColor->copy();

    EXPECT_NE(copiedPattern, nullptr);

    EXPECT_TRUE(dynamic_cast<SplashSolidColor*>(copiedPattern));

    delete copiedPattern;

}



// Assuming testPosition always returns true for static patterns

TEST_F(SplashSolidColorTest_1051, TestPosition_ReturnsTrue_1051) {

    EXPECT_TRUE(splashSolidColor->testPosition(0, 0));

}



// Boundary condition: large coordinates

TEST_F(SplashSolidColorTest_1051, GetColor_LargeCoordinates_Success_1051) {

    SplashColor c;

    EXPECT_TRUE(splashSolidColor->getColor(INT_MAX, INT_MAX, &c));

}



// Exceptional case: nullptr color pointer

TEST_F(SplashSolidColorTest_1051, GetColor_NullptrColor_ReturnsFalse_1051) {

    EXPECT_FALSE(splashSolidColor->getColor(0, 0, nullptr));

}
