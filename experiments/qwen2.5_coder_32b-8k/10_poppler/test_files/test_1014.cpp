#include <gtest/gtest.h>

#include "poppler/cpp/poppler-rectangle.h"



using namespace poppler;



template <typename T>

class RectangleTest : public ::testing::Test {

protected:

    rectangle<T> rect;

};



typedef ::testing::Types<int, float, double> RectangleTestTypes;

TYPED_TEST_SUITE(RectangleTest, RectangleTestTypes);



TYPED_TEST(RectangleTest, DefaultConstructorInitializesZero_1014) {

    EXPECT_EQ(this->rect.x(), static_cast<TypeParam>(0));

    EXPECT_EQ(this->rect.y(), static_cast<TypeParam>(0));

    EXPECT_EQ(this->rect.width(), static_cast<TypeParam>(0));

    EXPECT_EQ(this->rect.height(), static_cast<TypeParam>(0));

}



TYPED_TEST(RectangleTest, ParameterizedConstructorInitializesCorrectly_1014) {

    rectangle<TypeParam> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.x(), static_cast<TypeParam>(1));

    EXPECT_EQ(rect.y(), static_cast<TypeParam>(2));

    EXPECT_EQ(rect.width(), static_cast<TypeParam>(3));

    EXPECT_EQ(rect.height(), static_cast<TypeParam>(4));

}



TYPED_TEST(RectangleTest, SettersUpdateValues_1014) {

    this->rect.set_left(5);

    this->rect.set_top(6);

    this->rect.set_right(7);

    this->rect.set_bottom(8);



    EXPECT_EQ(this->rect.left(), static_cast<TypeParam>(5));

    EXPECT_EQ(this->rect.top(), static_cast<TypeParam>(6));

    EXPECT_EQ(this->rect.right(), static_cast<TypeParam>(7));

    EXPECT_EQ(this->rect.bottom(), static_cast<TypeParam>(8));

}



TYPED_TEST(RectangleTest, WidthAndHeightAreCorrect_1014) {

    rectangle<TypeParam> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.width(), static_cast<TypeParam>(3));

    EXPECT_EQ(rect.height(), static_cast<TypeParam>(4));

}



TYPED_TEST(RectangleTest, IsEmptyReturnsTrueForZeroSize_1014) {

    rectangle<TypeParam> rect(1, 2, 0, 0);

    EXPECT_TRUE(rect.is_empty());

}



TYPED_TEST(RectangleTest, IsEmptyReturnsFalseForNonZeroSize_1014) {

    rectangle<TypeParam> rect(1, 2, 3, 4);

    EXPECT_FALSE(rect.is_empty());

}



TYPED_TEST(RectangleTest, BoundaryConditionsZeroWidthOrHeight_1014) {

    rectangle<TypeParam> rect1(1, 2, 0, 5);

    rectangle<TypeParam> rect2(1, 2, 5, 0);



    EXPECT_TRUE(rect1.is_empty());

    EXPECT_TRUE(rect2.is_empty());

}



TYPED_TEST(RectangleTest, BoundaryConditionsNegativeWidthOrHeight_1014) {

    rectangle<TypeParam> rect1(1, 2, -3, 5);

    rectangle<TypeParam> rect2(1, 2, 5, -4);



    EXPECT_TRUE(rect1.is_empty());

    EXPECT_TRUE(rect2.is_empty());

}
