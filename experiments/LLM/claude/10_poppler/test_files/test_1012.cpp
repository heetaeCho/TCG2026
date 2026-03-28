#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor creates an empty rectangle with all zeros
TEST(RectangleTest_1012, DefaultConstructor_1012) {
    rectangle<int> r;
    EXPECT_EQ(r.x(), 0);
    EXPECT_EQ(r.y(), 0);
    EXPECT_EQ(r.width(), 0);
    EXPECT_EQ(r.height(), 0);
}

// Test parameterized constructor with positive values
TEST(RectangleTest_1012, ParameterizedConstructorPositive_1012) {
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(r.x(), 10);
    EXPECT_EQ(r.y(), 20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
}

// Test parameterized constructor with zero dimensions
TEST(RectangleTest_1012, ParameterizedConstructorZeroDimensions_1012) {
    rectangle<int> r(5, 10, 0, 0);
    EXPECT_EQ(r.x(), 5);
    EXPECT_EQ(r.y(), 10);
    EXPECT_EQ(r.width(), 0);
    EXPECT_EQ(r.height(), 0);
}

// Test height returns correct value
TEST(RectangleTest_1012, HeightReturnsCorrectValue_1012) {
    rectangle<int> r(0, 0, 100, 50);
    EXPECT_EQ(r.height(), 50);
}

// Test width returns correct value
TEST(RectangleTest_1012, WidthReturnsCorrectValue_1012) {
    rectangle<int> r(0, 0, 100, 50);
    EXPECT_EQ(r.width(), 100);
}

// Test left returns x1
TEST(RectangleTest_1012, LeftReturnsX1_1012) {
    rectangle<int> r(15, 25, 30, 40);
    EXPECT_EQ(r.left(), 15);
}

// Test top returns y1
TEST(RectangleTest_1012, TopReturnsY1_1012) {
    rectangle<int> r(15, 25, 30, 40);
    EXPECT_EQ(r.top(), 25);
}

// Test right returns x2 (x1 + width)
TEST(RectangleTest_1012, RightReturnsX2_1012) {
    rectangle<int> r(15, 25, 30, 40);
    EXPECT_EQ(r.right(), 45);  // 15 + 30
}

// Test bottom returns y2 (y1 + height)
TEST(RectangleTest_1012, BottomReturnsY2_1012) {
    rectangle<int> r(15, 25, 30, 40);
    EXPECT_EQ(r.bottom(), 65);  // 25 + 40
}

// Test is_empty on default rectangle
TEST(RectangleTest_1012, DefaultRectangleIsEmpty_1012) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty on non-empty rectangle
TEST(RectangleTest_1012, NonEmptyRectangleIsNotEmpty_1012) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
}

// Test is_empty when width is zero
TEST(RectangleTest_1012, ZeroWidthRectangleIsEmpty_1012) {
    rectangle<int> r(0, 0, 0, 10);
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty when height is zero
TEST(RectangleTest_1012, ZeroHeightRectangleIsEmpty_1012) {
    rectangle<int> r(0, 0, 10, 0);
    EXPECT_TRUE(r.is_empty());
}

// Test set_left modifies left boundary
TEST(RectangleTest_1012, SetLeftModifiesLeft_1012) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_left(5);
    EXPECT_EQ(r.left(), 5);
}

// Test set_top modifies top boundary
TEST(RectangleTest_1012, SetTopModifiesTop_1012) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_top(15);
    EXPECT_EQ(r.top(), 15);
}

// Test set_right modifies right boundary
TEST(RectangleTest_1012, SetRightModifiesRight_1012) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_right(100);
    EXPECT_EQ(r.right(), 100);
}

// Test set_bottom modifies bottom boundary
TEST(RectangleTest_1012, SetBottomModifiesBottom_1012) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_bottom(200);
    EXPECT_EQ(r.bottom(), 200);
}

// Test that set_left affects width
TEST(RectangleTest_1012, SetLeftAffectsWidth_1012) {
    rectangle<int> r(10, 20, 30, 40);
    // right is 40, set left to 5, width should be 40 - 5 = 35
    r.set_left(5);
    EXPECT_EQ(r.width(), r.right() - r.left());
}

// Test that set_right affects width
TEST(RectangleTest_1012, SetRightAffectsWidth_1012) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_right(100);
    EXPECT_EQ(r.width(), 100 - 10);
}

// Test that set_top affects height
TEST(RectangleTest_1012, SetTopAffectsHeight_1012) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_top(5);
    EXPECT_EQ(r.height(), r.bottom() - r.top());
}

// Test that set_bottom affects height
TEST(RectangleTest_1012, SetBottomAffectsHeight_1012) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_bottom(100);
    EXPECT_EQ(r.height(), 100 - 20);
}

// Test with double type
TEST(RectangleTest_1012, DoubleTypeRectangle_1012) {
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
TEST(RectangleTest_1012, NegativeCoordinates_1012) {
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

// Test with large values
TEST(RectangleTest_1012, LargeValues_1012) {
    rectangle<int> r(0, 0, 1000000, 2000000);
    EXPECT_EQ(r.width(), 1000000);
    EXPECT_EQ(r.height(), 2000000);
    EXPECT_EQ(r.right(), 1000000);
    EXPECT_EQ(r.bottom(), 2000000);
}

// Test x() and y() return initial position
TEST(RectangleTest_1012, XAndYReturnPosition_1012) {
    rectangle<int> r(42, 99, 10, 20);
    EXPECT_EQ(r.x(), 42);
    EXPECT_EQ(r.y(), 99);
}

// Test copy semantics
TEST(RectangleTest_1012, CopyConstructor_1012) {
    rectangle<int> r1(10, 20, 30, 40);
    rectangle<int> r2(r1);
    EXPECT_EQ(r2.x(), 10);
    EXPECT_EQ(r2.y(), 20);
    EXPECT_EQ(r2.width(), 30);
    EXPECT_EQ(r2.height(), 40);
}

// Test assignment operator
TEST(RectangleTest_1012, AssignmentOperator_1012) {
    rectangle<int> r1(10, 20, 30, 40);
    rectangle<int> r2;
    r2 = r1;
    EXPECT_EQ(r2.x(), 10);
    EXPECT_EQ(r2.y(), 20);
    EXPECT_EQ(r2.width(), 30);
    EXPECT_EQ(r2.height(), 40);
}

// Test setting all boundaries individually
TEST(RectangleTest_1012, SetAllBoundaries_1012) {
    rectangle<int> r;
    r.set_left(5);
    r.set_top(10);
    r.set_right(55);
    r.set_bottom(60);
    EXPECT_EQ(r.left(), 5);
    EXPECT_EQ(r.top(), 10);
    EXPECT_EQ(r.right(), 55);
    EXPECT_EQ(r.bottom(), 60);
    EXPECT_EQ(r.width(), 50);
    EXPECT_EQ(r.height(), 50);
}

// Test with float type
TEST(RectangleTest_1012, FloatTypeRectangle_1012) {
    rectangle<float> r(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(r.height(), 4.0f);
    EXPECT_FLOAT_EQ(r.width(), 3.0f);
    EXPECT_FLOAT_EQ(r.left(), 1.0f);
    EXPECT_FLOAT_EQ(r.right(), 4.0f);
}

// Test making a rectangle empty by setting left == right
TEST(RectangleTest_1012, MakeEmptyBySettingLeftEqualRight_1012) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
    r.set_left(r.right());
    EXPECT_EQ(r.width(), 0);
}

// Test making a rectangle empty by setting top == bottom
TEST(RectangleTest_1012, MakeEmptyBySettingTopEqualBottom_1012) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
    r.set_top(r.bottom());
    EXPECT_EQ(r.height(), 0);
}
