#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor creates a rectangle with all zero values
TEST(RectangleTest_1014, DefaultConstructor_1014) {
    rectangle<int> r;
    EXPECT_EQ(r.x(), 0);
    EXPECT_EQ(r.y(), 0);
    EXPECT_EQ(r.width(), 0);
    EXPECT_EQ(r.height(), 0);
    EXPECT_EQ(r.left(), 0);
    EXPECT_EQ(r.top(), 0);
    EXPECT_EQ(r.right(), 0);
    EXPECT_EQ(r.bottom(), 0);
}

// Test parameterized constructor with positive values
TEST(RectangleTest_1014, ParameterizedConstructorPositive_1014) {
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(r.x(), 10);
    EXPECT_EQ(r.y(), 20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.top(), 20);
    EXPECT_EQ(r.right(), 40);  // x + w = 10 + 30
    EXPECT_EQ(r.bottom(), 60); // y + h = 20 + 40
}

// Test parameterized constructor with zero dimensions
TEST(RectangleTest_1014, ParameterizedConstructorZeroDimensions_1014) {
    rectangle<int> r(5, 10, 0, 0);
    EXPECT_EQ(r.x(), 5);
    EXPECT_EQ(r.y(), 10);
    EXPECT_EQ(r.width(), 0);
    EXPECT_EQ(r.height(), 0);
    EXPECT_EQ(r.left(), 5);
    EXPECT_EQ(r.top(), 10);
    EXPECT_EQ(r.right(), 5);
    EXPECT_EQ(r.bottom(), 10);
}

// Test is_empty on default constructed rectangle
TEST(RectangleTest_1014, IsEmptyDefaultConstructed_1014) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty on non-empty rectangle
TEST(RectangleTest_1014, IsEmptyNonEmpty_1014) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
}

// Test is_empty on zero-width rectangle
TEST(RectangleTest_1014, IsEmptyZeroWidth_1014) {
    rectangle<int> r(5, 5, 0, 10);
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty on zero-height rectangle
TEST(RectangleTest_1014, IsEmptyZeroHeight_1014) {
    rectangle<int> r(5, 5, 10, 0);
    EXPECT_TRUE(r.is_empty());
}

// Test top() returns y1
TEST(RectangleTest_1014, TopReturnsY1_1014) {
    rectangle<int> r(3, 7, 10, 20);
    EXPECT_EQ(r.top(), 7);
}

// Test left() returns x1
TEST(RectangleTest_1014, LeftReturnsX1_1014) {
    rectangle<int> r(3, 7, 10, 20);
    EXPECT_EQ(r.left(), 3);
}

// Test right() returns x2 (x1 + width)
TEST(RectangleTest_1014, RightReturnsX2_1014) {
    rectangle<int> r(3, 7, 10, 20);
    EXPECT_EQ(r.right(), 13);
}

// Test bottom() returns y2 (y1 + height)
TEST(RectangleTest_1014, BottomReturnsY2_1014) {
    rectangle<int> r(3, 7, 10, 20);
    EXPECT_EQ(r.bottom(), 27);
}

// Test set_left modifies left/x value
TEST(RectangleTest_1014, SetLeft_1014) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_left(5);
    EXPECT_EQ(r.left(), 5);
}

// Test set_top modifies top/y value
TEST(RectangleTest_1014, SetTop_1014) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_top(15);
    EXPECT_EQ(r.top(), 15);
}

// Test set_right modifies right value
TEST(RectangleTest_1014, SetRight_1014) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_right(25);
    EXPECT_EQ(r.right(), 25);
}

// Test set_bottom modifies bottom value
TEST(RectangleTest_1014, SetBottom_1014) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_bottom(30);
    EXPECT_EQ(r.bottom(), 30);
}

// Test with double type
TEST(RectangleTest_1014, DoubleType_1014) {
    rectangle<double> r(1.5, 2.5, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(r.x(), 1.5);
    EXPECT_DOUBLE_EQ(r.y(), 2.5);
    EXPECT_DOUBLE_EQ(r.width(), 3.0);
    EXPECT_DOUBLE_EQ(r.height(), 4.0);
    EXPECT_DOUBLE_EQ(r.left(), 1.5);
    EXPECT_DOUBLE_EQ(r.top(), 2.5);
    EXPECT_DOUBLE_EQ(r.right(), 4.5);
    EXPECT_DOUBLE_EQ(r.bottom(), 6.5);
}

// Test with negative coordinates
TEST(RectangleTest_1014, NegativeCoordinates_1014) {
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

// Test set_left affects width
TEST(RectangleTest_1014, SetLeftAffectsWidth_1014) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_left(3);
    // right should still be 10, width should be 10 - 3 = 7
    EXPECT_EQ(r.right(), 10);
    EXPECT_EQ(r.width(), 7);
}

// Test set_top affects height
TEST(RectangleTest_1014, SetTopAffectsHeight_1014) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_top(4);
    // bottom should still be 10, height should be 10 - 4 = 6
    EXPECT_EQ(r.bottom(), 10);
    EXPECT_EQ(r.height(), 6);
}

// Test set_right affects width
TEST(RectangleTest_1014, SetRightAffectsWidth_1014) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_right(20);
    EXPECT_EQ(r.left(), 0);
    EXPECT_EQ(r.width(), 20);
}

// Test set_bottom affects height
TEST(RectangleTest_1014, SetBottomAffectsHeight_1014) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_bottom(25);
    EXPECT_EQ(r.top(), 0);
    EXPECT_EQ(r.height(), 25);
}

// Test with float type
TEST(RectangleTest_1014, FloatType_1014) {
    rectangle<float> r(0.0f, 0.0f, 5.5f, 3.3f);
    EXPECT_FLOAT_EQ(r.width(), 5.5f);
    EXPECT_FLOAT_EQ(r.height(), 3.3f);
    EXPECT_FLOAT_EQ(r.right(), 5.5f);
    EXPECT_FLOAT_EQ(r.bottom(), 3.3f);
}

// Test default constructed double rectangle
TEST(RectangleTest_1014, DefaultConstructorDouble_1014) {
    rectangle<double> r;
    EXPECT_DOUBLE_EQ(r.x(), 0.0);
    EXPECT_DOUBLE_EQ(r.y(), 0.0);
    EXPECT_DOUBLE_EQ(r.width(), 0.0);
    EXPECT_DOUBLE_EQ(r.height(), 0.0);
    EXPECT_TRUE(r.is_empty());
}

// Test setting all corners individually
TEST(RectangleTest_1014, SetAllCorners_1014) {
    rectangle<int> r;
    r.set_left(1);
    r.set_top(2);
    r.set_right(11);
    r.set_bottom(22);
    EXPECT_EQ(r.left(), 1);
    EXPECT_EQ(r.top(), 2);
    EXPECT_EQ(r.right(), 11);
    EXPECT_EQ(r.bottom(), 22);
    EXPECT_EQ(r.width(), 10);
    EXPECT_EQ(r.height(), 20);
    EXPECT_FALSE(r.is_empty());
}

// Test large values
TEST(RectangleTest_1014, LargeValues_1014) {
    rectangle<int> r(100000, 200000, 300000, 400000);
    EXPECT_EQ(r.left(), 100000);
    EXPECT_EQ(r.top(), 200000);
    EXPECT_EQ(r.right(), 400000);
    EXPECT_EQ(r.bottom(), 600000);
}

// Test that a rectangle with equal left/right is empty
TEST(RectangleTest_1014, EqualLeftRightIsEmpty_1014) {
    rectangle<int> r(5, 0, 0, 10);
    EXPECT_TRUE(r.is_empty());
}

// Test x() and y() accessors
TEST(RectangleTest_1014, XYAccessors_1014) {
    rectangle<int> r(42, 99, 10, 20);
    EXPECT_EQ(r.x(), 42);
    EXPECT_EQ(r.y(), 99);
}
