#include <gtest/gtest.h>
#include "splash/SplashPattern.h"
#include "splash/SplashTypes.h"

class SplashSolidColorTest_1052 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that isCMYK returns false
TEST_F(SplashSolidColorTest_1052, IsCMYKReturnsFalse_1052) {
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    color[3] = 0;
    SplashSolidColor solidColor(color);
    EXPECT_FALSE(solidColor.isCMYK());
}

// Test construction with black color and getColor
TEST_F(SplashSolidColorTest_1052, GetColorReturnsSetColor_1052) {
    SplashColor color;
    color[0] = 128;
    color[1] = 64;
    color[2] = 32;
    color[3] = 0;
    SplashSolidColor solidColor(color);

    SplashColor result;
    solidColor.getColor(0, 0, result);
    EXPECT_EQ(result[0], 128);
    EXPECT_EQ(result[1], 64);
    EXPECT_EQ(result[2], 32);
}

// Test getColor at different positions returns same color (solid pattern)
TEST_F(SplashSolidColorTest_1052, GetColorSameAtDifferentPositions_1052) {
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 127;
    color[3] = 0;
    SplashSolidColor solidColor(color);

    SplashColor result1, result2, result3;
    solidColor.getColor(0, 0, result1);
    solidColor.getColor(100, 200, result2);
    solidColor.getColor(-50, -30, result3);

    EXPECT_EQ(result1[0], result2[0]);
    EXPECT_EQ(result1[1], result2[1]);
    EXPECT_EQ(result1[2], result2[2]);

    EXPECT_EQ(result1[0], result3[0]);
    EXPECT_EQ(result1[1], result3[1]);
    EXPECT_EQ(result1[2], result3[2]);
}

// Test isStatic returns true for solid color
TEST_F(SplashSolidColorTest_1052, IsStaticReturnsTrue_1052) {
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    color[3] = 0;
    SplashSolidColor solidColor(color);
    EXPECT_TRUE(solidColor.isStatic());
}

// Test testPosition returns true for any position
TEST_F(SplashSolidColorTest_1052, TestPositionReturnsTrue_1052) {
    SplashColor color;
    color[0] = 100;
    color[1] = 100;
    color[2] = 100;
    color[3] = 0;
    SplashSolidColor solidColor(color);
    EXPECT_TRUE(solidColor.testPosition(0, 0));
    EXPECT_TRUE(solidColor.testPosition(500, 500));
    EXPECT_TRUE(solidColor.testPosition(-100, -100));
}

// Test copy creates a valid copy
TEST_F(SplashSolidColorTest_1052, CopyCreatesSameColor_1052) {
    SplashColor color;
    color[0] = 200;
    color[1] = 150;
    color[2] = 100;
    color[3] = 0;
    SplashSolidColor solidColor(color);

    SplashPattern *copied = solidColor.copy();
    ASSERT_NE(copied, nullptr);

    SplashColor origResult, copyResult;
    solidColor.getColor(10, 20, origResult);
    copied->getColor(10, 20, copyResult);

    EXPECT_EQ(origResult[0], copyResult[0]);
    EXPECT_EQ(origResult[1], copyResult[1]);
    EXPECT_EQ(origResult[2], copyResult[2]);

    delete copied;
}

// Test copy returns independent object
TEST_F(SplashSolidColorTest_1052, CopyIsIndependentObject_1052) {
    SplashColor color;
    color[0] = 50;
    color[1] = 100;
    color[2] = 150;
    color[3] = 0;
    SplashSolidColor solidColor(color);

    SplashPattern *copied = solidColor.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(static_cast<SplashPattern*>(&solidColor), copied);

    delete copied;
}

// Test with white color
TEST_F(SplashSolidColorTest_1052, WhiteColor_1052) {
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

// Test with black color
TEST_F(SplashSolidColorTest_1052, BlackColor_1052) {
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

// Test getColor at boundary coordinates
TEST_F(SplashSolidColorTest_1052, GetColorAtBoundaryCoordinates_1052) {
    SplashColor color;
    color[0] = 42;
    color[1] = 84;
    color[2] = 168;
    color[3] = 0;
    SplashSolidColor solidColor(color);

    SplashColor result;
    solidColor.getColor(INT_MAX, INT_MAX, result);
    EXPECT_EQ(result[0], 42);
    EXPECT_EQ(result[1], 84);
    EXPECT_EQ(result[2], 168);

    solidColor.getColor(INT_MIN, INT_MIN, result);
    EXPECT_EQ(result[0], 42);
    EXPECT_EQ(result[1], 84);
    EXPECT_EQ(result[2], 168);
}

// Test isCMYK on copied object
TEST_F(SplashSolidColorTest_1052, CopiedObjectIsCMYKReturnsFalse_1052) {
    SplashColor color;
    color[0] = 10;
    color[1] = 20;
    color[2] = 30;
    color[3] = 0;
    SplashSolidColor solidColor(color);

    SplashPattern *copied = solidColor.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_FALSE(copied->isCMYK());

    delete copied;
}
