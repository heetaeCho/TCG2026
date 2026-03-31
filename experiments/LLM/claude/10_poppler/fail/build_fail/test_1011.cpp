#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor creates an empty rectangle with zero dimensions
TEST(RectangleTest_1011, DefaultConstructor_1011) {
    rectangle<int> r;
    EXPECT_EQ(r.x(), 0);
    EXPECT_EQ(r.y(), 0);
    EXPECT_EQ(r.width(), 0);
    EXPECT_EQ(r.height(), 0);
}

// Test parameterized constructor with positive values
TEST(RectangleTest_1011, ParameterizedConstructorPositive_1011) {
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(r.x(), 10);
    EXPECT_EQ(r.y(), 20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
}

// Test parameterized constructor with zero dimensions
TEST(RectangleTest_1011, ParameterizedConstructorZeroDimensions_1011) {
    rectangle<int> r(5, 10, 0, 0);
    EXPECT_EQ(r.x(), 5);
    EXPECT_EQ(r.y(), 10);
    EXPECT_EQ(r.width(), 0);
    EXPECT_EQ(r.height(), 0);
}

// Test width calculation
TEST(RectangleTest_1011, WidthCalculation_1011) {
    rectangle<int> r(3, 4, 15, 25);
    EXPECT_EQ(r.width(), 15);
}

// Test height calculation
TEST(RectangleTest_1011, HeightCalculation_1011) {
    rectangle<int> r(3, 4, 15, 25);
    EXPECT_EQ(r.height(), 25);
}

// Test left() returns x1
TEST(RectangleTest_1011, LeftReturnsX1_1011) {
    rectangle<int> r(7, 8, 10, 20);
    EXPECT_EQ(r.left(), 7);
}

// Test top() returns y1
TEST(RectangleTest_1011, TopReturnsY1_1011) {
    rectangle<int> r(7, 8, 10, 20);
    EXPECT_EQ(r.top(), 8);
}

// Test right() returns x2 (x1 + width)
TEST(RectangleTest_1011, RightReturnsX2_1011) {
    rectangle<int> r(7, 8, 10, 20);
    EXPECT_EQ(r.right(), 17);
}

// Test bottom() returns y2 (y1 + height)
TEST(RectangleTest_1011, BottomReturnsY2_1011) {
    rectangle<int> r(7, 8, 10, 20);
    EXPECT_EQ(r.bottom(), 28);
}

// Test is_empty on default constructed rectangle
TEST(RectangleTest_1011, IsEmptyDefaultConstructor_1011) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty on non-empty rectangle
TEST(RectangleTest_1011, IsEmptyNonEmptyRectangle_1011) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
}

// Test is_empty on zero-width rectangle
TEST(RectangleTest_1011, IsEmptyZeroWidth_1011) {
    rectangle<int> r(5, 5, 0, 10);
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty on zero-height rectangle
TEST(RectangleTest_1011, IsEmptyZeroHeight_1011) {
    rectangle<int> r(5, 5, 10, 0);
    EXPECT_TRUE(r.is_empty());
}

// Test set_left modifies the left boundary
TEST(RectangleTest_1011, SetLeft_1011) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_left(5);
    EXPECT_EQ(r.left(), 5);
    // right should remain the same
    EXPECT_EQ(r.right(), 40);
    // width should change accordingly
    EXPECT_EQ(r.width(), 35);
}

// Test set_top modifies the top boundary
TEST(RectangleTest_1011, SetTop_1011) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_top(5);
    EXPECT_EQ(r.top(), 5);
    EXPECT_EQ(r.bottom(), 60);
    EXPECT_EQ(r.height(), 55);
}

// Test set_right modifies the right boundary
TEST(RectangleTest_1011, SetRight_1011) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_right(100);
    EXPECT_EQ(r.right(), 100);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.width(), 90);
}

// Test set_bottom modifies the bottom boundary
TEST(RectangleTest_1011, SetBottom_1011) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_bottom(100);
    EXPECT_EQ(r.bottom(), 100);
    EXPECT_EQ(r.top(), 20);
    EXPECT_EQ(r.height(), 80);
}

// Test with double type
TEST(RectangleTest_1011, DoubleType_1011) {
    rectangle<double> r(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(r.x(), 1.5);
    EXPECT_DOUBLE_EQ(r.y(), 2.5);
    EXPECT_DOUBLE_EQ(r.width(), 3.5);
    EXPECT_DOUBLE_EQ(r.height(), 4.5);
    EXPECT_DOUBLE_EQ(r.left(), 1.5);
    EXPECT_DOUBLE_EQ(r.top(), 2.5);
    EXPECT_DOUBLE_EQ(r.right(), 5.0);
    EXPECT_DOUBLE_EQ(r.bottom(), 7.0);
}

// Test with negative coordinates
TEST(RectangleTest_1011, NegativeCoordinates_1011) {
    rectangle<int> r(-10, -20, 30, 40);
    EXPECT_EQ(r.x(), -10);
    EXPECT_EQ(r.y(), -20);
    EXPECT_EQ(r.left(), -10);
    EXPECT_EQ(r.top(), -20);
    EXPECT_EQ(r.right(), 20);
    EXPECT_EQ(r.bottom(), 20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
}

// Test x() and y() return the origin
TEST(RectangleTest_1011, XYReturnOrigin_1011) {
    rectangle<int> r(42, 84, 10, 20);
    EXPECT_EQ(r.x(), 42);
    EXPECT_EQ(r.y(), 84);
}

// Test that set_left and set_right can create inverted rectangle (negative width)
TEST(RectangleTest_1011, InvertedRectangleWidth_1011) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_left(20);
    // Now left > right, width should be negative
    EXPECT_EQ(r.left(), 20);
    EXPECT_EQ(r.right(), 10);
    EXPECT_EQ(r.width(), -10);
}

// Test large values
TEST(RectangleTest_1011, LargeValues_1011) {
    rectangle<long long> r(0, 0, 1000000000LL, 2000000000LL);
    EXPECT_EQ(r.width(), 1000000000LL);
    EXPECT_EQ(r.height(), 2000000000LL);
    EXPECT_EQ(r.right(), 1000000000LL);
    EXPECT_EQ(r.bottom(), 2000000000LL);
}

// Test copy semantics
TEST(RectangleTest_1011, CopyConstructor_1011) {
    rectangle<int> r1(10, 20, 30, 40);
    rectangle<int> r2(r1);
    EXPECT_EQ(r2.x(), 10);
    EXPECT_EQ(r2.y(), 20);
    EXPECT_EQ(r2.width(), 30);
    EXPECT_EQ(r2.height(), 40);
}

// Test assignment operator
TEST(RectangleTest_1011, AssignmentOperator_1011) {
    rectangle<int> r1(10, 20, 30, 40);
    rectangle<int> r2;
    r2 = r1;
    EXPECT_EQ(r2.x(), 10);
    EXPECT_EQ(r2.y(), 20);
    EXPECT_EQ(r2.width(), 30);
    EXPECT_EQ(r2.height(), 40);
}

// Test float type precision
TEST(RectangleTest_1011, FloatTypePrecision_1011) {
    rectangle<float> r(0.1f, 0.2f, 0.3f, 0.4f);
    EXPECT_FLOAT_EQ(r.x(), 0.1f);
    EXPECT_FLOAT_EQ(r.y(), 0.2f);
    EXPECT_FLOAT_EQ(r.width(), 0.3f);
    EXPECT_FLOAT_EQ(r.height(), 0.4f);
}

// Test multiple setters in sequence
TEST(RectangleTest_1011, MultipleSettersSequence_1011) {
    rectangle<int> r;
    r.set_left(10);
    r.set_top(20);
    r.set_right(50);
    r.set_bottom(80);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.top(), 20);
    EXPECT_EQ(r.right(), 50);
    EXPECT_EQ(r.bottom(), 80);
    EXPECT_EQ(r.width(), 40);
    EXPECT_EQ(r.height(), 60);
}

// Test is_empty after setting all boundaries
TEST(RectangleTest_1011, IsEmptyAfterSetBoundaries_1011) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
    r.set_right(10);
    r.set_bottom(10);
    EXPECT_FALSE(r.is_empty());
}
