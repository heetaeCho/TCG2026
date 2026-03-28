#include <gtest/gtest.h>

#include "poppler-rectangle.h"



using namespace poppler;



template<typename T>

class RectangleTest : public ::testing::Test {

protected:

    rectangle<T> rect;

    rectangle<T> emptyRect;

};



typedef ::testing::Types<int, float, double> Implementations;

TYPED_TEST_SUITE(RectangleTest, Implementations);



TYPED_TEST(RectangleTest, DefaultConstructorInitializesEmpty_1011) {

    EXPECT_TRUE(this->emptyRect.is_empty());

}



TYPED_TEST(RectangleTest, ParameterizedConstructorSetsDimensions_1011) {

    TypeParam x = 5;

    TypeParam y = 10;

    TypeParam width = 20;

    TypeParam height = 30;



    rectangle<TypeParam> rect(x, y, width, height);



    EXPECT_EQ(rect.x(), x);

    EXPECT_EQ(rect.y(), y);

    EXPECT_EQ(rect.width(), width);

    EXPECT_EQ(rect.height(), height);

    EXPECT_FALSE(rect.is_empty());

}



TYPED_TEST(RectangleTest, WidthCalculatesCorrectly_1011) {

    TypeParam x = 5;

    TypeParam width = 20;



    rectangle<TypeParam> rect(x, 0, width, 0);



    EXPECT_EQ(rect.width(), width);

}



TYPED_TEST(RectangleTest, HeightCalculatesCorrectly_1011) {

    TypeParam y = 10;

    TypeParam height = 30;



    rectangle<TypeParam> rect(0, y, 0, height);



    EXPECT_EQ(rect.height(), height);

}



TYPED_TEST(RectangleTest, SetLeftUpdatesX1_1011) {

    this->rect.set_left(5);

    EXPECT_EQ(this->rect.left(), 5);

}



TYPED_TEST(RectangleTest, SetTopUpdatesY2_1011) {

    this->rect.set_top(10);

    EXPECT_EQ(this->rect.top(), 10);

}



TYPED_TEST(RectangleTest, SetRightUpdatesX2_1011) {

    TypeParam x = 5;

    TypeParam width = 20;

    rectangle<TypeParam> rect(x, 0, width, 0);



    TypeParam newRight = 30;

    rect.set_right(newRight);

    EXPECT_EQ(rect.right(), newRight);

}



TYPED_TEST(RectangleTest, SetBottomUpdatesY1_1011) {

    TypeParam y = 10;

    TypeParam height = 30;

    rectangle<TypeParam> rect(0, y, 0, height);



    TypeParam newBottom = 40;

    rect.set_bottom(newBottom);

    EXPECT_EQ(rect.bottom(), newBottom);

}



TYPED_TEST(RectangleTest, SettingNegativeWidthMakesRectangleEmpty_1011) {

    this->rect.set_right(-5);

    EXPECT_TRUE(this->rect.is_empty());

}



TYPED_TEST(RectangleTest, SettingNegativeHeightMakesRectangleEmpty_1011) {

    this->rect.set_bottom(-5);

    EXPECT_TRUE(this->rect.is_empty());

}
