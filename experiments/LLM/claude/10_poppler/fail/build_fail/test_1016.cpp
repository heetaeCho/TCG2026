#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor
TEST(RectangleTest_1016, DefaultConstructor_1016) {
    rectangle<int> r;
    EXPECT_EQ(r.x(), 0);
    EXPECT_EQ(r.y(), 0);
    EXPECT_EQ(r.width(), 0);
    EXPECT_EQ(r.height(), 0);
}

TEST(RectangleTest_1016, DefaultConstructorDouble_1016) {
    rectangle<double> r;
    EXPECT_DOUBLE_EQ(r.x(), 0.0);
    EXPECT_DOUBLE_EQ(r.y(), 0.0);
    EXPECT_DOUBLE_EQ(r.width(), 0.0);
    EXPECT_DOUBLE_EQ(r.height(), 0.0);
}

// Test parameterized constructor
TEST(RectangleTest_1016, ParameterizedConstructorInt_1016) {
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(r.x(), 10);
    EXPECT_EQ(r.y(), 20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
}

TEST(RectangleTest_1016, ParameterizedConstructorDouble_1016) {
    rectangle<double> r(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(r.x(), 1.5);
    EXPECT_DOUBLE_EQ(r.y(), 2.5);
    EXPECT_DOUBLE_EQ(r.width(), 3.5);
    EXPECT_DOUBLE_EQ(r.height(), 4.5);
}

// Test left(), top(), right(), bottom()
TEST(RectangleTest_1016, LeftTopRightBottom_1016) {
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.top(), 20);
    EXPECT_EQ(r.right(), 40);   // x + width = 10 + 30
    EXPECT_EQ(r.bottom(), 60);  // y + height = 20 + 40
}

TEST(RectangleTest_1016, LeftTopRightBottomDouble_1016) {
    rectangle<double> r(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(r.left(), 1.0);
    EXPECT_DOUBLE_EQ(r.top(), 2.0);
    EXPECT_DOUBLE_EQ(r.right(), 4.0);
    EXPECT_DOUBLE_EQ(r.bottom(), 6.0);
}

// Test bottom() specifically (the provided partial code)
TEST(RectangleTest_1016, BottomReturnsY2_1016) {
    rectangle<int> r(5, 10, 15, 20);
    EXPECT_EQ(r.bottom(), 30); // y + height = 10 + 20
}

// Test is_empty
TEST(RectangleTest_1016, IsEmptyDefaultConstructor_1016) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
}

TEST(RectangleTest_1016, IsEmptyNonEmptyRectangle_1016) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
}

TEST(RectangleTest_1016, IsEmptyZeroWidth_1016) {
    rectangle<int> r(0, 0, 0, 10);
    EXPECT_TRUE(r.is_empty());
}

TEST(RectangleTest_1016, IsEmptyZeroHeight_1016) {
    rectangle<int> r(0, 0, 10, 0);
    EXPECT_TRUE(r.is_empty());
}

TEST(RectangleTest_1016, IsEmptyZeroBoth_1016) {
    rectangle<int> r(5, 5, 0, 0);
    EXPECT_TRUE(r.is_empty());
}

// Test set_left
TEST(RectangleTest_1016, SetLeft_1016) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_left(5);
    EXPECT_EQ(r.left(), 5);
}

// Test set_top
TEST(RectangleTest_1016, SetTop_1016) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_top(5);
    EXPECT_EQ(r.top(), 5);
}

// Test set_right
TEST(RectangleTest_1016, SetRight_1016) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_right(100);
    EXPECT_EQ(r.right(), 100);
}

// Test set_bottom
TEST(RectangleTest_1016, SetBottom_1016) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_bottom(100);
    EXPECT_EQ(r.bottom(), 100);
}

// Test that setting left affects width
TEST(RectangleTest_1016, SetLeftAffectsWidth_1016) {
    rectangle<int> r(10, 20, 30, 40);
    // right is 40 (10+30)
    r.set_left(5);
    EXPECT_EQ(r.left(), 5);
    EXPECT_EQ(r.right(), 40); // right should remain unchanged
    EXPECT_EQ(r.width(), 35); // right - new left = 40 - 5
}

// Test that setting right affects width
TEST(RectangleTest_1016, SetRightAffectsWidth_1016) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_right(50);
    EXPECT_EQ(r.right(), 50);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.width(), 40); // 50 - 10
}

// Test that setting top affects height
TEST(RectangleTest_1016, SetTopAffectsHeight_1016) {
    rectangle<int> r(10, 20, 30, 40);
    // bottom is 60 (20+40)
    r.set_top(10);
    EXPECT_EQ(r.top(), 10);
    EXPECT_EQ(r.bottom(), 60);
    EXPECT_EQ(r.height(), 50); // 60 - 10
}

// Test that setting bottom affects height
TEST(RectangleTest_1016, SetBottomAffectsHeight_1016) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_bottom(80);
    EXPECT_EQ(r.bottom(), 80);
    EXPECT_EQ(r.top(), 20);
    EXPECT_EQ(r.height(), 60); // 80 - 20
}

// Test with negative coordinates
TEST(RectangleTest_1016, NegativeCoordinates_1016) {
    rectangle<int> r(-10, -20, 30, 40);
    EXPECT_EQ(r.x(), -10);
    EXPECT_EQ(r.y(), -20);
    EXPECT_EQ(r.left(), -10);
    EXPECT_EQ(r.top(), -20);
    EXPECT_EQ(r.right(), 20);   // -10 + 30
    EXPECT_EQ(r.bottom(), 20);  // -20 + 40
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
}

// Test with float type
TEST(RectangleTest_1016, FloatType_1016) {
    rectangle<float> r(1.5f, 2.5f, 3.5f, 4.5f);
    EXPECT_FLOAT_EQ(r.x(), 1.5f);
    EXPECT_FLOAT_EQ(r.y(), 2.5f);
    EXPECT_FLOAT_EQ(r.width(), 3.5f);
    EXPECT_FLOAT_EQ(r.height(), 4.5f);
    EXPECT_FLOAT_EQ(r.left(), 1.5f);
    EXPECT_FLOAT_EQ(r.top(), 2.5f);
    EXPECT_FLOAT_EQ(r.right(), 5.0f);
    EXPECT_FLOAT_EQ(r.bottom(), 7.0f);
}

// Boundary: very large values
TEST(RectangleTest_1016, LargeValues_1016) {
    rectangle<int> r(1000000, 2000000, 3000000, 4000000);
    EXPECT_EQ(r.left(), 1000000);
    EXPECT_EQ(r.top(), 2000000);
    EXPECT_EQ(r.right(), 4000000);
    EXPECT_EQ(r.bottom(), 6000000);
    EXPECT_EQ(r.width(), 3000000);
    EXPECT_EQ(r.height(), 4000000);
    EXPECT_FALSE(r.is_empty());
}

// Test x() and y() return the same as left() and top()
TEST(RectangleTest_1016, XYConsistentWithLeftTop_1016) {
    rectangle<int> r(15, 25, 35, 45);
    EXPECT_EQ(r.x(), r.left());
    EXPECT_EQ(r.y(), r.top());
}

// Test modifying all four sides
TEST(RectangleTest_1016, ModifyAllSides_1016) {
    rectangle<int> r(0, 0, 100, 100);
    r.set_left(10);
    r.set_top(20);
    r.set_right(90);
    r.set_bottom(80);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.top(), 20);
    EXPECT_EQ(r.right(), 90);
    EXPECT_EQ(r.bottom(), 80);
    EXPECT_EQ(r.width(), 80);
    EXPECT_EQ(r.height(), 60);
}

// Test negative width/height scenario (left > right after set)
TEST(RectangleTest_1016, NegativeDimensions_1016) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_left(20); // left > right (which is 10)
    // width would be negative
    EXPECT_EQ(r.left(), 20);
    EXPECT_EQ(r.right(), 10);
}
