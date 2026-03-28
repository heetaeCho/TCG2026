#include <gtest/gtest.h>
#include "splash/SplashPattern.h"
#include "splash/SplashTypes.h"

class SplashSolidColorTest_1051 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that isStatic returns true for SplashSolidColor
TEST_F(SplashSolidColorTest_1051, IsStaticReturnsTrue_1051) {
    SplashColor color;
    // Initialize color to some value
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    color[3] = 0;

    SplashSolidColor solidColor(color);
    EXPECT_TRUE(solidColor.isStatic());
}

// Test construction with black color and getColor
TEST_F(SplashSolidColorTest_1051, GetColorReturnsSetColor_Black_1051) {
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    color[3] = 0;

    SplashSolidColor solidColor(color);

    SplashColor result;
    solidColor.getColor(0, 0, result);

    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 0);
}

// Test construction with white color and getColor
TEST_F(SplashSolidColorTest_1051, GetColorReturnsSetColor_White_1051) {
    SplashColor color;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    color[3] = 0;

    SplashSolidColor solidColor(color);

    SplashColor result;
    solidColor.getColor(0, 0, result);

    EXPECT_EQ(result[0], 255);
    EXPECT_EQ(result[1], 255);
    EXPECT_EQ(result[2], 255);
}

// Test that getColor returns the same color regardless of position
TEST_F(SplashSolidColorTest_1051, GetColorSameForDifferentPositions_1051) {
    SplashColor color;
    color[0] = 128;
    color[1] = 64;
    color[2] = 32;
    color[3] = 0;

    SplashSolidColor solidColor(color);

    SplashColor result1, result2, result3;
    solidColor.getColor(0, 0, result1);
    solidColor.getColor(100, 200, result2);
    solidColor.getColor(-50, -100, result3);

    EXPECT_EQ(result1[0], result2[0]);
    EXPECT_EQ(result1[1], result2[1]);
    EXPECT_EQ(result1[2], result2[2]);

    EXPECT_EQ(result1[0], result3[0]);
    EXPECT_EQ(result1[1], result3[1]);
    EXPECT_EQ(result1[2], result3[2]);
}

// Test testPosition - for a solid color, it should work for any position
TEST_F(SplashSolidColorTest_1051, TestPositionReturnsTrue_1051) {
    SplashColor color;
    color[0] = 100;
    color[1] = 100;
    color[2] = 100;
    color[3] = 0;

    SplashSolidColor solidColor(color);

    EXPECT_TRUE(solidColor.testPosition(0, 0));
    EXPECT_TRUE(solidColor.testPosition(500, 500));
    EXPECT_TRUE(solidColor.testPosition(-1, -1));
}

// Test copy creates a valid copy
TEST_F(SplashSolidColorTest_1051, CopyCreatesValidCopy_1051) {
    SplashColor color;
    color[0] = 42;
    color[1] = 84;
    color[2] = 126;
    color[3] = 0;

    SplashSolidColor solidColor(color);

    SplashPattern *copied = solidColor.copy();
    ASSERT_NE(copied, nullptr);

    EXPECT_TRUE(copied->isStatic());

    SplashColor origResult, copyResult;
    solidColor.getColor(10, 20, origResult);
    copied->getColor(10, 20, copyResult);

    EXPECT_EQ(origResult[0], copyResult[0]);
    EXPECT_EQ(origResult[1], copyResult[1]);
    EXPECT_EQ(origResult[2], copyResult[2]);

    delete copied;
}

// Test with boundary color values
TEST_F(SplashSolidColorTest_1051, BoundaryColorValues_1051) {
    SplashColor color;
    color[0] = 0;
    color[1] = 255;
    color[2] = 0;
    color[3] = 255;

    SplashSolidColor solidColor(color);

    SplashColor result;
    solidColor.getColor(0, 0, result);

    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 255);
    EXPECT_EQ(result[2], 0);
}

// Test with large coordinate values
TEST_F(SplashSolidColorTest_1051, LargeCoordinateValues_1051) {
    SplashColor color;
    color[0] = 200;
    color[1] = 150;
    color[2] = 100;
    color[3] = 50;

    SplashSolidColor solidColor(color);

    SplashColor result;
    solidColor.getColor(INT_MAX, INT_MAX, result);

    EXPECT_EQ(result[0], 200);
    EXPECT_EQ(result[1], 150);
    EXPECT_EQ(result[2], 100);
}

// Test with negative coordinate values
TEST_F(SplashSolidColorTest_1051, NegativeCoordinateValues_1051) {
    SplashColor color;
    color[0] = 50;
    color[1] = 100;
    color[2] = 150;
    color[3] = 200;

    SplashSolidColor solidColor(color);

    SplashColor result;
    solidColor.getColor(INT_MIN, INT_MIN, result);

    EXPECT_EQ(result[0], 50);
    EXPECT_EQ(result[1], 100);
    EXPECT_EQ(result[2], 150);
}

// Test isStatic is consistent across multiple calls
TEST_F(SplashSolidColorTest_1051, IsStaticConsistent_1051) {
    SplashColor color;
    color[0] = 10;
    color[1] = 20;
    color[2] = 30;
    color[3] = 40;

    SplashSolidColor solidColor(color);

    EXPECT_TRUE(solidColor.isStatic());
    EXPECT_TRUE(solidColor.isStatic());
    EXPECT_TRUE(solidColor.isStatic());
}

// Test that copy is independent from original
TEST_F(SplashSolidColorTest_1051, CopyIsIndependent_1051) {
    SplashColor color;
    color[0] = 77;
    color[1] = 88;
    color[2] = 99;
    color[3] = 0;

    SplashSolidColor solidColor(color);
    SplashPattern *copied = solidColor.copy();
    ASSERT_NE(copied, nullptr);

    // The copy should be a separate object
    EXPECT_NE(static_cast<SplashPattern *>(&solidColor), copied);

    SplashColor result;
    copied->getColor(5, 5, result);
    EXPECT_EQ(result[0], 77);
    EXPECT_EQ(result[1], 88);
    EXPECT_EQ(result[2], 99);

    delete copied;
}
