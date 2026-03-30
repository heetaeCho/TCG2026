#include <gtest/gtest.h>

#include "poppler-rectangle.h"



using namespace poppler;



class RectangleTest_1008 : public ::testing::Test {

protected:

    rectangle<int> defaultRect;

    rectangle<int> nonEmptyRect;



    RectangleTest_1008() : defaultRect(), nonEmptyRect(0, 0, 10, 10) {}

};



TEST_F(RectangleTest_1008, DefaultConstructorCreatesEmptyRectangle_1008) {

    EXPECT_TRUE(defaultRect.is_empty());

}



TEST_F(RectangleTest_1008, ParameterizedConstructorCreatesNonEmptyRectangle_1008) {

    EXPECT_FALSE(nonEmptyRect.is_empty());

}



TEST_F(RectangleTest_1008, IsEmptyReturnsTrueForZeroWidthRectangle_1008) {

    rectangle<int> zeroWidthRect(0, 0, 0, 10);

    EXPECT_TRUE(zeroWidthRect.is_empty());

}



TEST_F(RectangleTest_1008, IsEmptyReturnsTrueForZeroHeightRectangle_1008) {

    rectangle<int> zeroHeightRect(0, 0, 10, 0);

    EXPECT_TRUE(zeroHeightRect.is_empty());

}



TEST_F(RectangleTest_1008, WidthAndHeightReturnCorrectValues_1008) {

    EXPECT_EQ(nonEmptyRect.width(), 10);

    EXPECT_EQ(nonEmptyRect.height(), 10);

}



TEST_F(RectangleTest_1008, SettersUpdateRectangleCoordinates_1008) {

    nonEmptyRect.set_left(5);

    nonEmptyRect.set_top(5);

    nonEmptyRect.set_right(15);

    nonEmptyRect.set_bottom(15);



    EXPECT_EQ(nonEmptyRect.x(), 5);

    EXPECT_EQ(nonEmptyRect.y(), 5);

    EXPECT_EQ(nonEmptyRect.width(), 10);

    EXPECT_EQ(nonEmptyRect.height(), 10);

}



TEST_F(RectangleTest_1008, SettersCanMakeRectangleEmpty_1008) {

    nonEmptyRect.set_left(5);

    nonEmptyRect.set_top(5);

    nonEmptyRect.set_right(5);

    nonEmptyRect.set_bottom(5);



    EXPECT_TRUE(nonEmptyRect.is_empty());

}



TEST_F(RectangleTest_1008, BoundaryConditionsForSetters_1008) {

    nonEmptyRect.set_left(-10);

    nonEmptyRect.set_top(-10);

    nonEmptyRect.set_right(10);

    nonEmptyRect.set_bottom(10);



    EXPECT_EQ(nonEmptyRect.x(), -10);

    EXPECT_EQ(nonEmptyRect.y(), -10);

    EXPECT_EQ(nonEmptyRect.width(), 20);

    EXPECT_EQ(nonEmptyRect.height(), 20);

}
