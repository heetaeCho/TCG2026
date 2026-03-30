#include <gtest/gtest.h>

#include "poppler-rectangle.h"



using namespace poppler;



class RectangleTest_1020 : public ::testing::Test {

protected:

    RectangleTest_1020() {}

    ~RectangleTest_1020() override {}



    rectangle<int> rect;

};



TEST_F(RectangleTest_1020, DefaultConstructorInitializesZero_1020) {

    EXPECT_EQ(rect.x(), 0);

    EXPECT_EQ(rect.y(), 0);

    EXPECT_EQ(rect.width(), 0);

    EXPECT_EQ(rect.height(), 0);

}



TEST_F(RectangleTest_1020, ParameterizedConstructorSetsValuesCorrectly_1020) {

    rectangle<int> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.x(), 1);

    EXPECT_EQ(rect.y(), 2);

    EXPECT_EQ(rect.width(), 3);

    EXPECT_EQ(rect.height(), 4);

}



TEST_F(RectangleTest_1020, SetLeftUpdatesX1Correctly_1020) {

    rect.set_left(5);

    EXPECT_EQ(rect.x(), 5);

}



TEST_F(RectangleTest_1020, SetTopUpdatesY1Correctly_1020) {

    rect.set_top(6);

    EXPECT_EQ(rect.y(), 6);

}



TEST_F(RectangleTest_1020, SetRightUpdatesX2Correctly_1020) {

    rect.set_right(7);

    EXPECT_EQ(rect.right(), 7);

}



TEST_F(RectangleTest_1020, SetBottomUpdatesY2Correctly_1020) {

    rect.set_bottom(8);

    EXPECT_EQ(rect.bottom(), 8);

}



TEST_F(RectangleTest_1020, IsEmptyReturnsTrueForZeroSize_1020) {

    rectangle<int> emptyRect;

    EXPECT_TRUE(emptyRect.is_empty());

}



TEST_F(RectangleTest_1020, IsEmptyReturnsFalseForNonZeroSize_1020) {

    rectangle<int> nonEmptyRect(0, 0, 1, 1);

    EXPECT_FALSE(nonEmptyRect.is_empty());

}



TEST_F(RectangleTest_1020, BoundaryConditionSetLeftToNegativeValue_1020) {

    rect.set_left(-1);

    EXPECT_EQ(rect.x(), -1);

}



TEST_F(RectangleTest_1020, BoundaryConditionSetTopToNegativeValue_1020) {

    rect.set_top(-1);

    EXPECT_EQ(rect.y(), -1);

}



TEST_F(RectangleTest_1020, BoundaryConditionSetRightToNegativeValue_1020) {

    rect.set_right(-1);

    EXPECT_EQ(rect.right(), -1);

}



TEST_F(RectangleTest_1020, BoundaryConditionSetBottomToNegativeValue_1020) {

    rect.set_bottom(-1);

    EXPECT_EQ(rect.bottom(), -1);

}
