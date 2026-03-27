#include <gtest/gtest.h>

#include "TestProjects/poppler/cpp/poppler-rectangle.h"



using namespace poppler;



class RectangleTest_1018 : public ::testing::Test {

protected:

    rectangle<int> rect;

};



TEST_F(RectangleTest_1018, DefaultConstructorInitializesToZero_1018) {

    EXPECT_EQ(rect.x(), 0);

    EXPECT_EQ(rect.y(), 0);

    EXPECT_EQ(rect.width(), 0);

    EXPECT_EQ(rect.height(), 0);

}



TEST_F(RectangleTest_1018, ParameterizedConstructorSetsCorrectValues_1018) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.x(), 1);

    EXPECT_EQ(rect.y(), 2);

    EXPECT_EQ(rect.width(), 3);

    EXPECT_EQ(rect.height(), 4);

}



TEST_F(RectangleTest_1018, IsEmptyReturnsTrueForZeroSize_1018) {

    EXPECT_TRUE(rect.is_empty());

}



TEST_F(RectangleTest_1018, IsEmptyReturnsFalseForNonZeroSize_1018) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_FALSE(rect.is_empty());

}



TEST_F(RectangleTest_1018, SetTopUpdatesTopValue_1018) {

    rect.set_top(5);

    EXPECT_EQ(rect.top(), 5);

}



TEST_F(RectangleTest_1018, SetLeftUpdatesLeftValue_1018) {

    rect.set_left(5);

    EXPECT_EQ(rect.left(), 5);

}



TEST_F(RectangleTest_1018, SetRightUpdatesRightValue_1018) {

    rectangle<int> rect(1, 2, 3, 4);

    rect.set_right(10);

    EXPECT_EQ(rect.right(), 10);

}



TEST_F(RectangleTest_1018, SetBottomUpdatesBottomValue_1018) {

    rectangle<int> rect(1, 2, 3, 4);

    rect.set_bottom(10);

    EXPECT_EQ(rect.bottom(), 10);

}



TEST_F(RectangleTest_1018, BoundaryConditionsWithNegativeValues_1018) {

    rectangle<int> rect(-5, -5, 10, 10);

    EXPECT_EQ(rect.x(), -5);

    EXPECT_EQ(rect.y(), -5);

    EXPECT_EQ(rect.width(), 10);

    EXPECT_EQ(rect.height(), 10);

}



TEST_F(RectangleTest_1018, BoundaryConditionsWithZeroWidthHeight_1018) {

    rectangle<int> rect(1, 2, 0, 0);

    EXPECT_TRUE(rect.is_empty());

}
