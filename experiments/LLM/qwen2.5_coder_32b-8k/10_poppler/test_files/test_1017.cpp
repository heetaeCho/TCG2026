#include <gtest/gtest.h>

#include "poppler-rectangle.h"



using namespace poppler;



TEST_F(RectangleTest_1017, DefaultConstructorInitializesZero_1017) {

    rectangle<int> rect;

    EXPECT_EQ(rect.x(), 0);

    EXPECT_EQ(rect.y(), 0);

    EXPECT_EQ(rect.width(), 0);

    EXPECT_EQ(rect.height(), 0);

}



TEST_F(RectangleTest_1017, ParameterizedConstructorInitializesCorrectly_1017) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.x(), 1);

    EXPECT_EQ(rect.y(), 2);

    EXPECT_EQ(rect.width(), 3);

    EXPECT_EQ(rect.height(), 4);

}



TEST_F(RectangleTest_1017, SetLeftUpdatesCorrectly_1017) {

    rectangle<int> rect(1, 2, 3, 4);

    rect.set_left(5);

    EXPECT_EQ(rect.left(), 5);

    EXPECT_EQ(rect.x(), 5);

}



TEST_F(RectangleTest_1017, SetTopUpdatesCorrectly_1017) {

    rectangle<int> rect(1, 2, 3, 4);

    rect.set_top(6);

    EXPECT_EQ(rect.top(), 6);

    EXPECT_EQ(rect.y(), 6);

}



TEST_F(RectangleTest_1017, SetRightUpdatesCorrectly_1017) {

    rectangle<int> rect(1, 2, 3, 4);

    rect.set_right(7);

    EXPECT_EQ(rect.right(), 7);

    EXPECT_EQ(rect.width(), 6); // width = right - x

}



TEST_F(RectangleTest_1017, SetBottomUpdatesCorrectly_1017) {

    rectangle<int> rect(1, 2, 3, 4);

    rect.set_bottom(8);

    EXPECT_EQ(rect.bottom(), 8);

    EXPECT_EQ(rect.height(), 6); // height = bottom - y

}



TEST_F(RectangleTest_1017, IsEmptyReturnsTrueForZeroArea_1017) {

    rectangle<int> rect;

    EXPECT_TRUE(rect.is_empty());

}



TEST_F(RectangleTest_1017, IsEmptyReturnsFalseForNonZeroArea_1017) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_FALSE(rect.is_empty());

}



TEST_F(RectangleTest_1017, BoundaryConditionsWithNegativeWidthHeight_1017) {

    rectangle<int> rect(1, 2, -3, -4);

    EXPECT_EQ(rect.width(), -3);

    EXPECT_EQ(rect.height(), -4);

    EXPECT_TRUE(rect.is_empty()); // Assuming negative width/height is considered empty

}



TEST_F(RectangleTest_1017, BoundaryConditionsWithZeroWidthHeight_1017) {

    rectangle<int> rect(1, 2, 0, 0);

    EXPECT_EQ(rect.width(), 0);

    EXPECT_EQ(rect.height(), 0);

    EXPECT_TRUE(rect.is_empty());

}



TEST_F(RectangleTest_1017, BoundaryConditionsWithMaxValues_1017) {

    rectangle<int> rect(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), 0, 0);

    EXPECT_EQ(rect.x(), std::numeric_limits<int>::max());

    EXPECT_EQ(rect.y(), std::numeric_limits<int>::max());

    EXPECT_TRUE(rect.is_empty()); // Assuming zero width/height is considered empty

}
