#include <gtest/gtest.h>

#include "poppler-rectangle.h"



using namespace poppler;



template<typename T>

class RectangleTest : public ::testing::Test {

protected:

    RectangleTest() : rect(0, 0, 10, 20) {}



    rectangle<T> rect;

};



typedef ::testing::Types<int, float, double> Implementations;

TYPED_TEST_SUITE(RectangleTest, Implementations);



// Normal operation

TYPED_TEST(RectangleTest, HeightReturnsCorrectValue_1012) {

    EXPECT_EQ(this->rect.height(), 20);

}



TYPED_TEST(RectangleTest, WidthReturnsCorrectValue_1012) {

    EXPECT_EQ(this->rect.width(), 10);

}



// Boundary conditions

TYPED_TEST(RectangleTest, ZeroDimensionsRectangleHeightIsZero_1012) {

    rectangle<TypeParam> zeroRect(0, 0, 0, 0);

    EXPECT_EQ(zeroRect.height(), 0);

}



TYPED_TEST(RectangleTest, ZeroDimensionsRectangleWidthIsZero_1012) {

    rectangle<TypeParam> zeroRect(0, 0, 0, 0);

    EXPECT_EQ(zeroRect.width(), 0);

}



// Exceptional or error cases

TYPED_TEST(RectangleTest, NegativeWidthDoesNotThrow_1012) {

    rectangle<TypeParam> negWidthRect(0, 0, -10, 20);

    EXPECT_NO_THROW(negWidthRect.width());

}



TYPED_TEST(RectangleTest, NegativeHeightDoesNotThrow_1012) {

    rectangle<TypeParam> negHeightRect(0, 0, 10, -20);

    EXPECT_NO_THROW(negHeightRect.height());

}



// Verification of external interactions

// No mocks needed as there are no external collaborators



// Additional tests for other methods

TYPED_TEST(RectangleTest, IsEmptyReturnsTrueForZeroDimensions_1012) {

    rectangle<TypeParam> zeroRect(0, 0, 0, 0);

    EXPECT_TRUE(zeroRect.is_empty());

}



TYPETEST(RectangleTest, IsEmptyReturnsFalseForNonZeroDimensions_1012) {

    EXPECT_FALSE(this->rect.is_empty());

}



TYPED_TEST(RectangleTest, SettersUpdateValuesCorrectly_1012) {

    this->rect.set_left(5);

    this->rect.set_top(6);

    this->rect.set_right(15);

    this->rect.set_bottom(26);



    EXPECT_EQ(this->rect.x(), 5);

    EXPECT_EQ(this->rect.y(), 6);

    EXPECT_EQ(this->rect.width(), 10);

    EXPECT_EQ(this->rect.height(), 20);

}
