#include <gtest/gtest.h>

#include "poppler-rectangle.h"



using namespace poppler;



template <typename T>

class RectangleTest : public ::testing::Test {

protected:

    rectangle<T> rect;

};



typedef ::testing::Types<int, float, double> Implementations;



TYPED_TEST_SUITE(RectangleTest, Implementations);



TYPED_TEST(RectangleTest, DefaultConstructorInitializesZero_1009) {

    EXPECT_EQ(this->rect.x(), 0);

    EXPECT_EQ(this->rect.y(), 0);

    EXPECT_EQ(this->rect.width(), 0);

    EXPECT_EQ(this->rect.height(), 0);

}



TYPED_TEST(RectangleTest, ParameterizedConstructorInitializesCorrectly_1009) {

    rectangle<TypeParam> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.x(), 1);

    EXPECT_EQ(rect.y(), 2);

    EXPECT_EQ(rect.width(), 3);

    EXPECT_EQ(rect.height(), 4);

}



TYPED_TEST(RectangleTest, SetLeftUpdatesCorrectly_1009) {

    this->rect.set_left(5);

    EXPECT_EQ(this->rect.left(), 5);

}



TYPED_TEST(RectangleTest, SetTopUpdatesCorrectly_1009) {

    this->rect.set_top(6);

    EXPECT_EQ(this->rect.top(), 6);

}



TYPED_TEST(RectangleTest, SetRightUpdatesCorrectly_1009) {

    this->rect.set_right(7);

    EXPECT_EQ(this->rect.right(), 7);

}



TYPED_TEST(RectangleTest, SetBottomUpdatesCorrectly_1009) {

    this->rect.set_bottom(8);

    EXPECT_EQ(this->rect.bottom(), 8);

}



TYPED_TEST(RectangleTest, WidthCalculationIsCorrect_1009) {

    rectangle<TypeParam> rect(0, 0, 5, 5);

    EXPECT_EQ(rect.width(), 5);

}



TYPED_TEST(RectangleTest, HeightCalculationIsCorrect_1009) {

    rectangle<TypeParam> rect(0, 0, 5, 5);

    EXPECT_EQ(rect.height(), 5);

}



TYPED_TEST(RectangleTest, IsEmptyReturnsTrueForZeroWidthOrHeight_1009) {

    rectangle<TypeParam> zeroWidthRect(0, 0, 0, 5);

    rectangle<TypeParam> zeroHeightRect(0, 0, 5, 0);

    EXPECT_TRUE(zeroWidthRect.is_empty());

    EXPECT_TRUE(zeroHeightRect.is_empty());

}



TYPED_TEST(RectangleTest, IsEmptyReturnsFalseForNonZeroWidthAndHeight_1009) {

    rectangle<TypeParam> rect(0, 0, 5, 5);

    EXPECT_FALSE(rect.is_empty());

}
