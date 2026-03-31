#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor creates an empty/zero-initialized rectangle
TEST(RectangleTest_1017, DefaultConstructor_1017) {
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
TEST(RectangleTest_1017, ParameterizedConstructorPositiveValues_1017) {
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(r.x(), 10);
    EXPECT_EQ(r.y(), 20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.top(), 20);
    EXPECT_EQ(r.right(), 40);   // x + width = 10 + 30
    EXPECT_EQ(r.bottom(), 60);  // y + height = 20 + 40
}

// Test parameterized constructor with zero dimensions
TEST(RectangleTest_1017, ParameterizedConstructorZeroDimensions_1017) {
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

// Test is_empty on default-constructed rectangle
TEST(RectangleTest_1017, IsEmptyDefaultConstructed_1017) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty on a rectangle with positive dimensions
TEST(RectangleTest_1017, IsEmptyNonEmptyRectangle_1017) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
}

// Test is_empty on a rectangle with zero width
TEST(RectangleTest_1017, IsEmptyZeroWidth_1017) {
    rectangle<int> r(0, 0, 0, 10);
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty on a rectangle with zero height
TEST(RectangleTest_1017, IsEmptyZeroHeight_1017) {
    rectangle<int> r(0, 0, 10, 0);
    EXPECT_TRUE(r.is_empty());
}

// Test set_left modifies left and affects x and width
TEST(RectangleTest_1017, SetLeft_1017) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_left(5);
    EXPECT_EQ(r.left(), 5);
    // right should remain unchanged (40)
    EXPECT_EQ(r.right(), 40);
    // width should now be right - left = 40 - 5 = 35
    EXPECT_EQ(r.width(), 35);
}

// Test set_top modifies top and affects y and height
TEST(RectangleTest_1017, SetTop_1017) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_top(5);
    EXPECT_EQ(r.top(), 5);
    EXPECT_EQ(r.bottom(), 60);
    EXPECT_EQ(r.height(), 55);
}

// Test set_right modifies right and affects width
TEST(RectangleTest_1017, SetRight_1017) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_right(100);
    EXPECT_EQ(r.right(), 100);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.width(), 90);
}

// Test set_bottom modifies bottom and affects height
TEST(RectangleTest_1017, SetBottom_1017) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_bottom(100);
    EXPECT_EQ(r.bottom(), 100);
    EXPECT_EQ(r.top(), 20);
    EXPECT_EQ(r.height(), 80);
}

// Test with double type
TEST(RectangleTest_1017, DoubleType_1017) {
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
TEST(RectangleTest_1017, NegativeCoordinates_1017) {
    rectangle<int> r(-10, -20, 30, 40);
    EXPECT_EQ(r.x(), -10);
    EXPECT_EQ(r.y(), -20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
    EXPECT_EQ(r.left(), -10);
    EXPECT_EQ(r.top(), -20);
    EXPECT_EQ(r.right(), 20);
    EXPECT_EQ(r.bottom(), 20);
}

// Test set_left to a negative value
TEST(RectangleTest_1017, SetLeftNegative_1017) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_left(-5);
    EXPECT_EQ(r.left(), -5);
    EXPECT_EQ(r.right(), 40);
    EXPECT_EQ(r.width(), 45);
}

// Test set_right to be less than left (inverted rectangle)
TEST(RectangleTest_1017, SetRightLessThanLeft_1017) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_right(5);
    EXPECT_EQ(r.right(), 5);
    EXPECT_EQ(r.left(), 10);
    // Width would be negative: 5 - 10 = -5
    EXPECT_EQ(r.width(), -5);
}

// Test default constructed double rectangle
TEST(RectangleTest_1017, DefaultConstructorDouble_1017) {
    rectangle<double> r;
    EXPECT_DOUBLE_EQ(r.x(), 0.0);
    EXPECT_DOUBLE_EQ(r.y(), 0.0);
    EXPECT_DOUBLE_EQ(r.width(), 0.0);
    EXPECT_DOUBLE_EQ(r.height(), 0.0);
}

// Test setting all four sides
TEST(RectangleTest_1017, SetAllSides_1017) {
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
    EXPECT_EQ(r.x(), 1);
    EXPECT_EQ(r.y(), 2);
}

// Test is_empty after setting non-zero dimensions via setters
TEST(RectangleTest_1017, IsEmptyAfterSetters_1017) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
    r.set_right(10);
    r.set_bottom(10);
    EXPECT_FALSE(r.is_empty());
}

// Test with large values
TEST(RectangleTest_1017, LargeValues_1017) {
    rectangle<int> r(0, 0, 1000000, 1000000);
    EXPECT_EQ(r.width(), 1000000);
    EXPECT_EQ(r.height(), 1000000);
    EXPECT_EQ(r.right(), 1000000);
    EXPECT_EQ(r.bottom(), 1000000);
    EXPECT_FALSE(r.is_empty());
}

// Test that x() returns left() equivalent
TEST(RectangleTest_1017, XEqualsLeft_1017) {
    rectangle<int> r(15, 25, 35, 45);
    EXPECT_EQ(r.x(), r.left());
}

// Test that y() returns top() equivalent
TEST(RectangleTest_1017, YEqualsTop_1017) {
    rectangle<int> r(15, 25, 35, 45);
    EXPECT_EQ(r.y(), r.top());
}

// Test set_left updates x() as well
TEST(RectangleTest_1017, SetLeftUpdatesX_1017) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_left(99);
    EXPECT_EQ(r.x(), 99);
}

// Test set_top updates y() as well
TEST(RectangleTest_1017, SetTopUpdatesY_1017) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_top(99);
    EXPECT_EQ(r.y(), 99);
}

// Test with float type
TEST(RectangleTest_1017, FloatType_1017) {
    rectangle<float> r(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(r.x(), 1.0f);
    EXPECT_FLOAT_EQ(r.y(), 2.0f);
    EXPECT_FLOAT_EQ(r.width(), 3.0f);
    EXPECT_FLOAT_EQ(r.height(), 4.0f);
    EXPECT_FLOAT_EQ(r.right(), 4.0f);
    EXPECT_FLOAT_EQ(r.bottom(), 6.0f);
}
