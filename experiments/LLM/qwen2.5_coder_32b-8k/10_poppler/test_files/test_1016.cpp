#include <gtest/gtest.h>

#include "TestProjects/poppler/cpp/poppler-rectangle.h"



using namespace poppler;



class RectangleTest_1016 : public ::testing::Test {

protected:

    rectangle<int> rect;

};



TEST_F(RectangleTest_1016, DefaultConstructorInitializesZero_1016) {

    EXPECT_EQ(rect.x(), 0);

    EXPECT_EQ(rect.y(), 0);

    EXPECT_EQ(rect.width(), 0);

    EXPECT_EQ(rect.height(), 0);

}



TEST_F(RectangleTest_1016, ParameterizedConstructorInitializesCorrectly_1016) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.x(), 1);

    EXPECT_EQ(rect.y(), 2);

    EXPECT_EQ(rect.width(), 3);

    EXPECT_EQ(rect.height(), 4);

}



TEST_F(RectangleTest_1016, IsEmptyReturnsTrueForZeroSize_1016) {

    EXPECT_TRUE(rect.is_empty());

}



TEST_F(RectangleTest_1016, IsEmptyReturnsFalseForNonZeroSize_1016) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_FALSE(rect.is_empty());

}



TEST_F(RectangleTest_1016, SettersUpdateValuesCorrectly_1016) {

    rect.set_left(5);

    rect.set_top(6);

    rect.set_right(7);

    rect.set_bottom(8);



    EXPECT_EQ(rect.left(), 5);

    EXPECT_EQ(rect.top(), 6);

    EXPECT_EQ(rect.right(), 7);

    EXPECT_EQ(rect.bottom(), 8);

}



TEST_F(RectangleTest_1016, WidthAndHeightCalculateCorrectly_1016) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.width(), 3);

    EXPECT_EQ(rect.height(), 4);

}



TEST_F(RectangleTest_1016, BoundaryConditionsForSetters_1016) {

    rect.set_left(INT_MIN);

    rect.set_top(INT_MIN);

    rect.set_right(INT_MAX);

    rect.set_bottom(INT_MAX);



    EXPECT_EQ(rect.left(), INT_MIN);

    EXPECT_EQ(rect.top(), INT_MIN);

    EXPECT_EQ(rect.right(), INT_MAX);

    EXPECT_EQ(rect.bottom(), INT_MAX);

}



TEST_F(RectangleTest_1016, WidthAndHeightReturnZeroForNegativeWidthOrHeight_1016) {

    rectangle<int> rect(5, 6, -3, 4);

    EXPECT_EQ(rect.width(), 0);



    rectangle<int> rect2(5, 6, 3, -4);

    EXPECT_EQ(rect2.height(), 0);

}
