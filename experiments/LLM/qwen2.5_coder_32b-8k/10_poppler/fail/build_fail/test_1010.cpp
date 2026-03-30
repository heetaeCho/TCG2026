#include <gtest/gtest.h>

#include "poppler/cpp/poppler-rectangle.h"



using namespace poppler;



class RectangleTest_1010 : public ::testing::Test {

protected:

    rectangle<int> defaultRect;

    rectangle<int> customRect;



    RectangleTest_1010() 

        : defaultRect(), 

          customRect(1, 2, 3, 4) {}

};



TEST_F(RectangleTest_1010, DefaultConstructorInitializesToZero_1010) {

    EXPECT_EQ(defaultRect.x(), 0);

    EXPECT_EQ(defaultRect.y(), 0);

    EXPECT_EQ(defaultRect.width(), 0);

    EXPECT_EQ(defaultRect.height(), 0);

}



TEST_F(RectangleTest_1010, CustomConstructorInitializesCorrectly_1010) {

    EXPECT_EQ(customRect.x(), 1);

    EXPECT_EQ(customRect.y(), 2);

    EXPECT_EQ(customRect.width(), 3);

    EXPECT_EQ(customRect.height(), 4);

}



TEST_F(RectangleTest_1010, IsEmptyReturnsTrueForDefaultRectangle_1010) {

    EXPECT_TRUE(defaultRect.is_empty());

}



TEST_F(RectangleTest_1010, IsEmptyReturnsFalseForNonEmptyRectangle_1010) {

    EXPECT_FALSE(customRect.is_empty());

}



TEST_F(RectangleTest_1010, SetLeftUpdatesXCoordinate_1010) {

    customRect.set_left(5);

    EXPECT_EQ(customRect.x(), 5);

}



TEST_F(RectangleTest_1010, SetTopUpdatesYCoordinate_1010) {

    customRect.set_top(6);

    EXPECT_EQ(customRect.y(), 6);

}



TEST_F(RectangleTest_1010, SetRightUpdatesWidth_1010) {

    customRect.set_right(7);

    EXPECT_EQ(customRect.width(), 6); // right - x

}



TEST_F(RectangleTest_1010, SetBottomUpdatesHeight_1010) {

    customRect.set_bottom(8);

    EXPECT_EQ(customRect.height(), 6); // bottom - y

}



TEST_F(RectangleTest_1010, WidthReturnsCorrectValueAfterModification_1010) {

    customRect.set_right(10);

    EXPECT_EQ(customRect.width(), 9); // right (10) - x (1)

}



TEST_F(RectangleTest_1010, HeightReturnsCorrectValueAfterModification_1010) {

    customRect.set_bottom(10);

    EXPECT_EQ(customRect.height(), 8); // bottom (10) - y (2)

}
