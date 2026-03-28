#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor creates an empty/zero rectangle
TEST(RectangleTest_1013, DefaultConstructor_1013) {
    rectangle<int> r;
    EXPECT_EQ(r.left(), 0);
    EXPECT_EQ(r.top(), 0);
    EXPECT_EQ(r.right(), 0);
    EXPECT_EQ(r.bottom(), 0);
}

TEST(RectangleTest_1013, DefaultConstructorDouble_1013) {
    rectangle<double> r;
    EXPECT_DOUBLE_EQ(r.left(), 0.0);
    EXPECT_DOUBLE_EQ(r.top(), 0.0);
    EXPECT_DOUBLE_EQ(r.right(), 0.0);
    EXPECT_DOUBLE_EQ(r.bottom(), 0.0);
}

// Test parameterized constructor
TEST(RectangleTest_1013, ParameterizedConstructor_1013) {
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.top(), 20);
    EXPECT_EQ(r.right(), 40);   // x + w = 10 + 30
    EXPECT_EQ(r.bottom(), 60);  // y + h = 20 + 40
}

TEST(RectangleTest_1013, ParameterizedConstructorDouble_1013) {
    rectangle<double> r(1.5, 2.5, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(r.left(), 1.5);
    EXPECT_DOUBLE_EQ(r.top(), 2.5);
    EXPECT_DOUBLE_EQ(r.right(), 4.5);   // 1.5 + 3.0
    EXPECT_DOUBLE_EQ(r.bottom(), 6.5);  // 2.5 + 4.0
}

// Test x() and y() accessors
TEST(RectangleTest_1013, XYAccessors_1013) {
    rectangle<int> r(5, 10, 15, 20);
    EXPECT_EQ(r.x(), 5);
    EXPECT_EQ(r.y(), 10);
}

// Test width() and height()
TEST(RectangleTest_1013, WidthHeight_1013) {
    rectangle<int> r(5, 10, 15, 20);
    EXPECT_EQ(r.width(), 15);
    EXPECT_EQ(r.height(), 20);
}

TEST(RectangleTest_1013, WidthHeightDouble_1013) {
    rectangle<double> r(1.0, 2.0, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(r.width(), 3.5);
    EXPECT_DOUBLE_EQ(r.height(), 4.5);
}

// Test is_empty for default constructed rectangle
TEST(RectangleTest_1013, IsEmptyDefault_1013) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty for non-empty rectangle
TEST(RectangleTest_1013, IsEmptyNonEmpty_1013) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
}

// Test is_empty for zero-width rectangle
TEST(RectangleTest_1013, IsEmptyZeroWidth_1013) {
    rectangle<int> r(5, 5, 0, 10);
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty for zero-height rectangle
TEST(RectangleTest_1013, IsEmptyZeroHeight_1013) {
    rectangle<int> r(5, 5, 10, 0);
    EXPECT_TRUE(r.is_empty());
}

// Test left() accessor
TEST(RectangleTest_1013, LeftAccessor_1013) {
    rectangle<int> r(3, 7, 10, 20);
    EXPECT_EQ(r.left(), 3);
}

// Test top() accessor
TEST(RectangleTest_1013, TopAccessor_1013) {
    rectangle<int> r(3, 7, 10, 20);
    EXPECT_EQ(r.top(), 7);
}

// Test right() accessor
TEST(RectangleTest_1013, RightAccessor_1013) {
    rectangle<int> r(3, 7, 10, 20);
    EXPECT_EQ(r.right(), 13);  // 3 + 10
}

// Test bottom() accessor
TEST(RectangleTest_1013, BottomAccessor_1013) {
    rectangle<int> r(3, 7, 10, 20);
    EXPECT_EQ(r.bottom(), 27);  // 7 + 20
}

// Test set_left
TEST(RectangleTest_1013, SetLeft_1013) {
    rectangle<int> r(3, 7, 10, 20);
    r.set_left(100);
    EXPECT_EQ(r.left(), 100);
}

// Test set_top
TEST(RectangleTest_1013, SetTop_1013) {
    rectangle<int> r(3, 7, 10, 20);
    r.set_top(200);
    EXPECT_EQ(r.top(), 200);
}

// Test set_right
TEST(RectangleTest_1013, SetRight_1013) {
    rectangle<int> r(3, 7, 10, 20);
    r.set_right(50);
    EXPECT_EQ(r.right(), 50);
}

// Test set_bottom
TEST(RectangleTest_1013, SetBottom_1013) {
    rectangle<int> r(3, 7, 10, 20);
    r.set_bottom(99);
    EXPECT_EQ(r.bottom(), 99);
}

// Test negative coordinates
TEST(RectangleTest_1013, NegativeCoordinates_1013) {
    rectangle<int> r(-10, -20, 30, 40);
    EXPECT_EQ(r.left(), -10);
    EXPECT_EQ(r.top(), -20);
    EXPECT_EQ(r.right(), 20);   // -10 + 30
    EXPECT_EQ(r.bottom(), 20);  // -20 + 40
    EXPECT_EQ(r.x(), -10);
    EXPECT_EQ(r.y(), -20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
}

// Test setting values and checking width/height consistency
TEST(RectangleTest_1013, SetLeftAffectsWidth_1013) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_EQ(r.width(), 10);
    r.set_left(5);
    // After setting left to 5, right is still 10, so width should be 5
    EXPECT_EQ(r.left(), 5);
    EXPECT_EQ(r.right(), 10);
    EXPECT_EQ(r.width(), 5);
}

TEST(RectangleTest_1013, SetRightAffectsWidth_1013) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_right(20);
    EXPECT_EQ(r.right(), 20);
    EXPECT_EQ(r.width(), 20);
}

TEST(RectangleTest_1013, SetTopAffectsHeight_1013) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_top(3);
    EXPECT_EQ(r.top(), 3);
    EXPECT_EQ(r.bottom(), 10);
    EXPECT_EQ(r.height(), 7);
}

TEST(RectangleTest_1013, SetBottomAffectsHeight_1013) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_bottom(25);
    EXPECT_EQ(r.bottom(), 25);
    EXPECT_EQ(r.height(), 25);
}

// Test with float type
TEST(RectangleTest_1013, FloatType_1013) {
    rectangle<float> r(1.5f, 2.5f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(r.left(), 1.5f);
    EXPECT_FLOAT_EQ(r.top(), 2.5f);
    EXPECT_FLOAT_EQ(r.right(), 4.5f);
    EXPECT_FLOAT_EQ(r.bottom(), 6.5f);
    EXPECT_FLOAT_EQ(r.width(), 3.0f);
    EXPECT_FLOAT_EQ(r.height(), 4.0f);
}

// Test large values
TEST(RectangleTest_1013, LargeValues_1013) {
    rectangle<int> r(1000000, 2000000, 3000000, 4000000);
    EXPECT_EQ(r.left(), 1000000);
    EXPECT_EQ(r.top(), 2000000);
    EXPECT_EQ(r.right(), 4000000);
    EXPECT_EQ(r.bottom(), 6000000);
}

// Test rectangle where left > right after set (degenerate)
TEST(RectangleTest_1013, DegenerateAfterSet_1013) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_left(20);
    // left is now 20, right is 10 — degenerate rectangle
    EXPECT_EQ(r.left(), 20);
    EXPECT_EQ(r.right(), 10);
    // width would be negative
    EXPECT_TRUE(r.is_empty());
}

// Copy behavior test
TEST(RectangleTest_1013, CopyConstruct_1013) {
    rectangle<int> r1(5, 10, 15, 20);
    rectangle<int> r2(r1);
    EXPECT_EQ(r2.left(), 5);
    EXPECT_EQ(r2.top(), 10);
    EXPECT_EQ(r2.right(), 20);
    EXPECT_EQ(r2.bottom(), 30);
}

// Assignment operator test
TEST(RectangleTest_1013, AssignmentOperator_1013) {
    rectangle<int> r1(5, 10, 15, 20);
    rectangle<int> r2;
    r2 = r1;
    EXPECT_EQ(r2.left(), 5);
    EXPECT_EQ(r2.top(), 10);
    EXPECT_EQ(r2.right(), 20);
    EXPECT_EQ(r2.bottom(), 30);
}
