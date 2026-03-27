#include <gtest/gtest.h>

#include "poppler/cpp/poppler-rectangle.h"



using namespace poppler;



TEST_F(RectangleTest_1019, DefaultConstructorInitializesZero_1019) {

    rectangle<int> rect;

    EXPECT_EQ(rect.x(), 0);

    EXPECT_EQ(rect.y(), 0);

    EXPECT_EQ(rect.width(), 0);

    EXPECT_EQ(rect.height(), 0);

}



TEST_F(RectangleTest_1019, ParameterizedConstructorInitializesCorrectly_1019) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.x(), 1);

    EXPECT_EQ(rect.y(), 2);

    EXPECT_EQ(rect.width(), 3);

    EXPECT_EQ(rect.height(), 4);

}



TEST_F(RectangleTest_1019, SetRightUpdatesWidthCorrectly_1019) {

    rectangle<int> rect(0, 0, 5, 5);

    rect.set_right(10);

    EXPECT_EQ(rect.width(), 10);

    EXPECT_EQ(rect.x2(), 10);

}



TEST_F(RectangleTest_1019, SetLeftUpdatesWidthAndXCorrectly_1019) {

    rectangle<int> rect(0, 0, 5, 5);

    rect.set_left(-5);

    EXPECT_EQ(rect.width(), 10);

    EXPECT_EQ(rect.x(), -5);

}



TEST_F(RectangleTest_1019, SetTopUpdatesHeightAndYCorrectly_1019) {

    rectangle<int> rect(0, 0, 5, 5);

    rect.set_top(-5);

    EXPECT_EQ(rect.height(), 10);

    EXPECT_EQ(rect.y(), -5);

}



TEST_F(RectangleTest_1019, SetBottomUpdatesHeightCorrectly_1019) {

    rectangle<int> rect(0, 0, 5, 5);

    rect.set_bottom(10);

    EXPECT_EQ(rect.height(), 10);

    EXPECT_EQ(rect.y2(), 10);

}



TEST_F(RectangleTest_1019, IsEmptyReturnsTrueForZeroWidthOrHeight_1019) {

    rectangle<int> rect1(0, 0, 0, 5);

    rectangle<int> rect2(0, 0, 5, 0);

    EXPECT_TRUE(rect1.is_empty());

    EXPECT_TRUE(rect2.is_empty());

}



TEST_F(RectangleTest_1019, IsEmptyReturnsFalseForNonZeroWidthAndHeight_1019) {

    rectangle<int> rect(0, 0, 5, 5);

    EXPECT_FALSE(rect.is_empty());

}
