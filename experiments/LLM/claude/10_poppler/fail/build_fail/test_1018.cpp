#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor creates an empty/zero rectangle
TEST(RectangleTest_1018, DefaultConstructor_1018) {
    rectangle<int> r;
    EXPECT_EQ(r.x(), 0);
    EXPECT_EQ(r.y(), 0);
    EXPECT_EQ(r.width(), 0);
    EXPECT_EQ(r.height(), 0);
}

// Test parameterized constructor with positive values
TEST(RectangleTest_1018, ParameterizedConstructor_1018) {
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(r.x(), 10);
    EXPECT_EQ(r.y(), 20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
}

// Test left(), top(), right(), bottom() accessors
TEST(RectangleTest_1018, AccessorsLeftTopRightBottom_1018) {
    rectangle<int> r(5, 10, 15, 20);
    EXPECT_EQ(r.left(), 5);
    EXPECT_EQ(r.top(), 10);
    EXPECT_EQ(r.right(), 5 + 15);
    EXPECT_EQ(r.bottom(), 10 + 20);
}

// Test is_empty on default constructed rectangle
TEST(RectangleTest_1018, IsEmptyDefault_1018) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty on non-empty rectangle
TEST(RectangleTest_1018, IsEmptyNonEmpty_1018) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
}

// Test set_top modifies the top value
TEST(RectangleTest_1018, SetTop_1018) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_top(5);
    EXPECT_EQ(r.top(), 5);
}

// Test set_left modifies the left value
TEST(RectangleTest_1018, SetLeft_1018) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_left(3);
    EXPECT_EQ(r.left(), 3);
}

// Test set_right modifies the right value
TEST(RectangleTest_1018, SetRight_1018) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_right(25);
    EXPECT_EQ(r.right(), 25);
}

// Test set_bottom modifies the bottom value
TEST(RectangleTest_1018, SetBottom_1018) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_bottom(30);
    EXPECT_EQ(r.bottom(), 30);
}

// Test width and height reflect changes after set_right/set_bottom
TEST(RectangleTest_1018, WidthHeightAfterSetters_1018) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_right(20);
    r.set_bottom(30);
    EXPECT_EQ(r.width(), 20);
    EXPECT_EQ(r.height(), 30);
}

// Test width and height reflect changes after set_left/set_top
TEST(RectangleTest_1018, WidthHeightAfterSetLeftTop_1018) {
    rectangle<int> r(0, 0, 20, 20);
    r.set_left(5);
    r.set_top(10);
    EXPECT_EQ(r.width(), 15);  // right(20) - left(5) = 15
    EXPECT_EQ(r.height(), 10); // bottom(20) - top(10) = 10
}

// Test with double type
TEST(RectangleTest_1018, DoubleType_1018) {
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
TEST(RectangleTest_1018, NegativeCoordinates_1018) {
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

// Test zero-width rectangle is empty
TEST(RectangleTest_1018, ZeroWidthIsEmpty_1018) {
    rectangle<int> r(5, 5, 0, 10);
    EXPECT_TRUE(r.is_empty());
}

// Test zero-height rectangle is empty
TEST(RectangleTest_1018, ZeroHeightIsEmpty_1018) {
    rectangle<int> r(5, 5, 10, 0);
    EXPECT_TRUE(r.is_empty());
}

// Test setting all corners individually
TEST(RectangleTest_1018, SetAllCorners_1018) {
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

// Test x() and y() correspond to left() and top()
TEST(RectangleTest_1018, XYCorrespondToLeftTop_1018) {
    rectangle<int> r(7, 13, 100, 200);
    EXPECT_EQ(r.x(), r.left());
    EXPECT_EQ(r.y(), r.top());
}

// Test copy semantics (default copy constructor)
TEST(RectangleTest_1018, CopyConstructor_1018) {
    rectangle<int> r1(3, 4, 5, 6);
    rectangle<int> r2(r1);
    EXPECT_EQ(r2.x(), 3);
    EXPECT_EQ(r2.y(), 4);
    EXPECT_EQ(r2.width(), 5);
    EXPECT_EQ(r2.height(), 6);
}

// Test assignment operator
TEST(RectangleTest_1018, AssignmentOperator_1018) {
    rectangle<int> r1(1, 2, 3, 4);
    rectangle<int> r2;
    r2 = r1;
    EXPECT_EQ(r2.left(), 1);
    EXPECT_EQ(r2.top(), 2);
    EXPECT_EQ(r2.right(), 4);
    EXPECT_EQ(r2.bottom(), 6);
}

// Test large values
TEST(RectangleTest_1018, LargeValues_1018) {
    rectangle<long long> r(1000000LL, 2000000LL, 3000000LL, 4000000LL);
    EXPECT_EQ(r.x(), 1000000LL);
    EXPECT_EQ(r.y(), 2000000LL);
    EXPECT_EQ(r.width(), 3000000LL);
    EXPECT_EQ(r.height(), 4000000LL);
}

// Test set_top changes y() as well
TEST(RectangleTest_1018, SetTopChangesY_1018) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_top(7);
    EXPECT_EQ(r.y(), 7);
    EXPECT_EQ(r.top(), 7);
}

// Test set_left changes x() as well
TEST(RectangleTest_1018, SetLeftChangesX_1018) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_left(7);
    EXPECT_EQ(r.x(), 7);
    EXPECT_EQ(r.left(), 7);
}

// Test float type
TEST(RectangleTest_1018, FloatType_1018) {
    rectangle<float> r(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(r.x(), 1.0f);
    EXPECT_FLOAT_EQ(r.y(), 2.0f);
    EXPECT_FLOAT_EQ(r.width(), 3.0f);
    EXPECT_FLOAT_EQ(r.height(), 4.0f);
}
