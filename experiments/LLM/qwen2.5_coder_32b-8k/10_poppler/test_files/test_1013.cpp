#include <gtest/gtest.h>

#include "poppler/cpp/poppler-rectangle.h"



using namespace poppler;



template <typename T>

class RectangleTest_1013 : public ::testing::Test {

protected:

    rectangle<T> rect;

};



typedef ::testing::Types<int, float, double> Implementations;



TYPED_TEST_SUITE(RectangleTest_1013, Implementations);



TYPED_TEST(RectangleTest_1013, DefaultConstructorInitializesZero_1013) {

    EXPECT_EQ(this->rect.left(), 0);

    EXPECT_EQ(this->rect.top(), 0);

    EXPECT_EQ(this->rect.width(), 0);

    EXPECT_EQ(this->rect.height(), 0);

}



TYPED_TEST(RectangleTest_1013, ParameterizedConstructorInitializesCorrectly_1013) {

    rectangle<TypeParam> rect(1, 2, 3, 4);

    EXPECT_EQ(rect.left(), 1);

    EXPECT_EQ(rect.top(), 2);

    EXPECT_EQ(rect.width(), 3);

    EXPECT_EQ(rect.height(), 4);

}



TYPED_TEST(RectangleTest_1013, SetLeftUpdatesCorrectly_1013) {

    this->rect.set_left(5);

    EXPECT_EQ(this->rect.left(), 5);

}



TYPED_TEST(RectangleTest_1013, SetTopUpdatesCorrectly_1013) {

    this->rect.set_top(6);

    EXPECT_EQ(this->rect.top(), 6);

}



TYPED_TEST(RectangleTest_1013, SetRightUpdatesCorrectly_1013) {

    rectangle<TypeParam> rect(1, 2, 3, 4);

    rect.set_right(8);

    EXPECT_EQ(rect.right(), 8);

    EXPECT_EQ(rect.width(), 7); // right - left = 8 - 1

}



TYPED_TEST(RectangleTest_1013, SetBottomUpdatesCorrectly_1013) {

    rectangle<TypeParam> rect(1, 2, 3, 4);

    rect.set_bottom(9);

    EXPECT_EQ(rect.bottom(), 9);

    EXPECT_EQ(rect.height(), 7); // bottom - top = 9 - 2

}



TYPED_TEST(RectangleTest_1013, IsEmptyReturnsTrueForZeroWidth_1013) {

    rectangle<TypeParam> rect(1, 2, 0, 4);

    EXPECT_TRUE(rect.is_empty());

}



TYPED_TEST(RectangleTest_1013, IsEmptyReturnsTrueForZeroHeight_1013) {

    rectangle<TypeParam> rect(1, 2, 3, 0);

    EXPECT_TRUE(rect.is_empty());

}



TYPETEST(RectangleTest_1013, IsEmptyReturnsFalseForNonZeroDimensions_1013) {

    rectangle<TypeParam> rect(1, 2, 3, 4);

    EXPECT_FALSE(rect.is_empty());

}
