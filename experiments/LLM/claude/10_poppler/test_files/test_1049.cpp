#include <gtest/gtest.h>
#include "splash/SplashPattern.h"
#include "splash/SplashTypes.h"

class SplashSolidColorTest_1049 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(SplashSolidColorTest_1049, ConstructWithBlackColor_1049) {
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    SplashSolidColor solidColor(color);

    SplashColor result;
    bool ret = solidColor.getColor(0, 0, result);
    EXPECT_TRUE(ret);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 0);
}

TEST_F(SplashSolidColorTest_1049, ConstructWithWhiteColor_1049) {
    SplashColor color;
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;
    SplashSolidColor solidColor(color);

    SplashColor result;
    bool ret = solidColor.getColor(0, 0, result);
    EXPECT_TRUE(ret);
    EXPECT_EQ(result[0], 255);
    EXPECT_EQ(result[1], 255);
    EXPECT_EQ(result[2], 255);
}

TEST_F(SplashSolidColorTest_1049, ConstructWithArbitraryColor_1049) {
    SplashColor color;
    color[0] = 100;
    color[1] = 150;
    color[2] = 200;
    SplashSolidColor solidColor(color);

    SplashColor result;
    bool ret = solidColor.getColor(0, 0, result);
    EXPECT_TRUE(ret);
    EXPECT_EQ(result[0], 100);
    EXPECT_EQ(result[1], 150);
    EXPECT_EQ(result[2], 200);
}

TEST_F(SplashSolidColorTest_1049, GetColorAtDifferentPositions_1049) {
    SplashColor color;
    color[0] = 50;
    color[1] = 100;
    color[2] = 150;
    SplashSolidColor solidColor(color);

    SplashColor result1, result2, result3;
    solidColor.getColor(0, 0, result1);
    solidColor.getColor(100, 200, result2);
    solidColor.getColor(-10, -20, result3);

    // Solid color should return the same color regardless of position
    EXPECT_EQ(result1[0], result2[0]);
    EXPECT_EQ(result1[1], result2[1]);
    EXPECT_EQ(result1[2], result2[2]);
    EXPECT_EQ(result1[0], result3[0]);
    EXPECT_EQ(result1[1], result3[1]);
    EXPECT_EQ(result1[2], result3[2]);
}

TEST_F(SplashSolidColorTest_1049, CopyReturnsSameColor_1049) {
    SplashColor color;
    color[0] = 42;
    color[1] = 84;
    color[2] = 126;
    SplashSolidColor solidColor(color);

    SplashPattern *copied = solidColor.copy();
    ASSERT_NE(copied, nullptr);

    SplashColor origResult, copyResult;
    solidColor.getColor(0, 0, origResult);
    copied->getColor(0, 0, copyResult);

    EXPECT_EQ(origResult[0], copyResult[0]);
    EXPECT_EQ(origResult[1], copyResult[1]);
    EXPECT_EQ(origResult[2], copyResult[2]);

    delete copied;
}

TEST_F(SplashSolidColorTest_1049, CopyReturnsDistinctObject_1049) {
    SplashColor color;
    color[0] = 10;
    color[1] = 20;
    color[2] = 30;
    SplashSolidColor solidColor(color);

    SplashPattern *copied = solidColor.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(static_cast<SplashPattern*>(&solidColor), copied);

    delete copied;
}

TEST_F(SplashSolidColorTest_1049, IsStaticReturnsTrue_1049) {
    SplashColor color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    SplashSolidColor solidColor(color);

    // A solid color pattern should be static (same everywhere)
    EXPECT_TRUE(solidColor.isStatic());
}

TEST_F(SplashSolidColorTest_1049, TestPositionAlwaysTrue_1049) {
    SplashColor color;
    color[0] = 128;
    color[1] = 128;
    color[2] = 128;
    SplashSolidColor solidColor(color);

    // A solid color should pass test at any position
    EXPECT_TRUE(solidColor.testPosition(0, 0));
    EXPECT_TRUE(solidColor.testPosition(1000, 1000));
    EXPECT_TRUE(solidColor.testPosition(-1, -1));
}

TEST_F(SplashSolidColorTest_1049, GetColorWithLargeCoordinates_1049) {
    SplashColor color;
    color[0] = 200;
    color[1] = 100;
    color[2] = 50;
    SplashSolidColor solidColor(color);

    SplashColor result;
    bool ret = solidColor.getColor(INT_MAX, INT_MAX, result);
    EXPECT_TRUE(ret);
    EXPECT_EQ(result[0], 200);
    EXPECT_EQ(result[1], 100);
    EXPECT_EQ(result[2], 50);
}

TEST_F(SplashSolidColorTest_1049, GetColorWithNegativeCoordinates_1049) {
    SplashColor color;
    color[0] = 1;
    color[1] = 2;
    color[2] = 3;
    SplashSolidColor solidColor(color);

    SplashColor result;
    bool ret = solidColor.getColor(INT_MIN, INT_MIN, result);
    EXPECT_TRUE(ret);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

TEST_F(SplashSolidColorTest_1049, MultipleCopiesAreIndependent_1049) {
    SplashColor color;
    color[0] = 77;
    color[1] = 88;
    color[2] = 99;
    SplashSolidColor solidColor(color);

    SplashPattern *copy1 = solidColor.copy();
    SplashPattern *copy2 = solidColor.copy();

    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2);

    SplashColor result1, result2;
    copy1->getColor(0, 0, result1);
    copy2->getColor(0, 0, result2);

    EXPECT_EQ(result1[0], result2[0]);
    EXPECT_EQ(result1[1], result2[1]);
    EXPECT_EQ(result1[2], result2[2]);

    delete copy1;
    delete copy2;
}

TEST_F(SplashSolidColorTest_1049, BoundaryColorValues_1049) {
    // Test with max byte values
    SplashColor color;
    color[0] = 255;
    color[1] = 0;
    color[2] = 255;
    SplashSolidColor solidColor(color);

    SplashColor result;
    solidColor.getColor(5, 10, result);
    EXPECT_EQ(result[0], 255);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 255);
}
