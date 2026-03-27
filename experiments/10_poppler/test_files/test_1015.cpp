#include <gtest/gtest.h>

#include "poppler/cpp/poppler-rectangle.h"



using namespace poppler;



// Test Fixture for rectangle class

class RectangleTest_1015 : public ::testing::Test {

protected:

    // Common setup code can go here if needed

};



TEST_F(RectangleTest_1015, DefaultConstructorInitializesZero_1015) {

    rectangle<int> rect;

    EXPECT_EQ(rect.x(), 0);

    EXPECT_EQ(rect.y(), 0);

    EXPECT_EQ(rect.width(), 0);

    EXPECT_EQ(rect.height(), 0);

}



TEST_F(RectangleTest_1015, ParameterizedConstructorInitializesCorrectly_1015) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.x(), 1);

    EXPECT_EQ(rect.y(), 2);

    EXPECT_EQ(rect.width(), 3);

    EXPECT_EQ(rect.height(), 4);

}



TEST_F(RectangleTest_1015, IsEmptyReturnsTrueForZeroDimensions_1015) {

    rectangle<int> rect;

    EXPECT_TRUE(rect.is_empty());

}



TEST_F(RectangleTest_1015, IsEmptyReturnsFalseForNonZeroDimensions_1015) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_FALSE(rect.is_empty());

}



TEST_F(RectangleTest_1015, SettersUpdateCoordinatesCorrectly_1015) {

    rectangle<int> rect;

    rect.set_left(1);

    rect.set_top(2);

    rect.set_right(4);

    rect.set_bottom(6);



    EXPECT_EQ(rect.x(), 1);

    EXPECT_EQ(rect.y(), 2);

    EXPECT_EQ(rect.width(), 3);

    EXPECT_EQ(rect.height(), 4);

}



TEST_F(RectangleTest_1015, GettersReturnCorrectValuesAfterSetters_1015) {

    rectangle<int> rect;

    rect.set_left(1);

    rect.set_top(2);

    rect.set_right(4);

    rect.set_bottom(6);



    EXPECT_EQ(rect.left(), 1);

    EXPECT_EQ(rect.top(), 2);

    EXPECT_EQ(rect.right(), 4);

    EXPECT_EQ(rect.bottom(), 6);

}



TEST_F(RectangleTest_1015, BoundaryConditionsWithNegativeWidthHeight_1015) {

    rectangle<int> rect(1, 2, -3, -4);

    EXPECT_EQ(rect.x(), 1);

    EXPECT_EQ(rect.y(), 2);

    EXPECT_EQ(rect.width(), -3);

    EXPECT_EQ(rect.height(), -4);

}



TEST_F(RectangleTest_1015, BoundaryConditionsWithZeroWidthHeight_1015) {

    rectangle<int> rect(1, 2, 0, 0);

    EXPECT_TRUE(rect.is_empty());

    EXPECT_EQ(rect.width(), 0);

    EXPECT_EQ(rect.height(), 0);

}
