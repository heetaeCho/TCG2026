#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor
TEST(RectangleTest_1020, DefaultConstructorCreatesEmptyRectangle_1020) {
    rectangle<int> rect;
    EXPECT_EQ(rect.x(), 0);
    EXPECT_EQ(rect.y(), 0);
    EXPECT_EQ(rect.width(), 0);
    EXPECT_EQ(rect.height(), 0);
}

TEST(RectangleTest_1020, DefaultConstructorIsEmpty_1020) {
    rectangle<int> rect;
    EXPECT_TRUE(rect.is_empty());
}

// Test parameterized constructor
TEST(RectangleTest_1020, ParameterizedConstructorSetsValues_1020) {
    rectangle<int> rect(10, 20, 30, 40);
    EXPECT_EQ(rect.x(), 10);
    EXPECT_EQ(rect.y(), 20);
    EXPECT_EQ(rect.width(), 30);
    EXPECT_EQ(rect.height(), 40);
}

TEST(RectangleTest_1020, ParameterizedConstructorNotEmpty_1020) {
    rectangle<int> rect(10, 20, 30, 40);
    EXPECT_FALSE(rect.is_empty());
}

// Test left/top/right/bottom accessors
TEST(RectangleTest_1020, LeftReturnsX_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.left(), 5);
}

TEST(RectangleTest_1020, TopReturnsY_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.top(), 10);
}

TEST(RectangleTest_1020, RightReturnsXPlusWidth_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.right(), 20);  // 5 + 15
}

TEST(RectangleTest_1020, BottomReturnsYPlusHeight_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.bottom(), 30);  // 10 + 20
}

// Test setters
TEST(RectangleTest_1020, SetLeftChangesLeft_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    rect.set_left(100);
    EXPECT_EQ(rect.left(), 100);
}

TEST(RectangleTest_1020, SetTopChangesTop_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    rect.set_top(100);
    EXPECT_EQ(rect.top(), 100);
}

TEST(RectangleTest_1020, SetRightChangesRight_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    rect.set_right(100);
    EXPECT_EQ(rect.right(), 100);
}

TEST(RectangleTest_1020, SetBottomChangesBottom_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    rect.set_bottom(100);
    EXPECT_EQ(rect.bottom(), 100);
}

// Test width and height after setter changes
TEST(RectangleTest_1020, SetRightAffectsWidth_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    rect.set_right(50);
    EXPECT_EQ(rect.width(), 45);  // 50 - 5
}

TEST(RectangleTest_1020, SetBottomAffectsHeight_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    rect.set_bottom(50);
    EXPECT_EQ(rect.height(), 40);  // 50 - 10
}

TEST(RectangleTest_1020, SetLeftAffectsWidth_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    // right is 20 (5+15), setting left to 10 => width = 20 - 10 = 10
    rect.set_left(10);
    EXPECT_EQ(rect.width(), 10);
}

TEST(RectangleTest_1020, SetTopAffectsHeight_1020) {
    rectangle<int> rect(5, 10, 15, 20);
    // bottom is 30 (10+20), setting top to 15 => height = 30 - 15 = 15
    rect.set_top(15);
    EXPECT_EQ(rect.height(), 15);
}

// Test with double type
TEST(RectangleTest_1020, DoubleTypeConstructor_1020) {
    rectangle<double> rect(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(rect.x(), 1.5);
    EXPECT_DOUBLE_EQ(rect.y(), 2.5);
    EXPECT_DOUBLE_EQ(rect.width(), 3.5);
    EXPECT_DOUBLE_EQ(rect.height(), 4.5);
}

TEST(RectangleTest_1020, DoubleTypeLeftTopRightBottom_1020) {
    rectangle<double> rect(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(rect.left(), 1.5);
    EXPECT_DOUBLE_EQ(rect.top(), 2.5);
    EXPECT_DOUBLE_EQ(rect.right(), 5.0);   // 1.5 + 3.5
    EXPECT_DOUBLE_EQ(rect.bottom(), 7.0);  // 2.5 + 4.5
}

// Test is_empty with zero width
TEST(RectangleTest_1020, ZeroWidthIsEmpty_1020) {
    rectangle<int> rect(5, 10, 0, 20);
    EXPECT_TRUE(rect.is_empty());
}

// Test is_empty with zero height
TEST(RectangleTest_1020, ZeroHeightIsEmpty_1020) {
    rectangle<int> rect(5, 10, 20, 0);
    EXPECT_TRUE(rect.is_empty());
}

// Test is_empty with both zero
TEST(RectangleTest_1020, ZeroWidthAndHeightIsEmpty_1020) {
    rectangle<int> rect(5, 10, 0, 0);
    EXPECT_TRUE(rect.is_empty());
}

// Test negative dimensions
TEST(RectangleTest_1020, NegativeWidthRectangle_1020) {
    rectangle<int> rect(10, 10, -5, 5);
    // right = 10 + (-5) = 5, which is less than left (10)
    EXPECT_EQ(rect.right(), 5);
    EXPECT_EQ(rect.width(), -5);
}

TEST(RectangleTest_1020, NegativeCoordinates_1020) {
    rectangle<int> rect(-10, -20, 30, 40);
    EXPECT_EQ(rect.x(), -10);
    EXPECT_EQ(rect.y(), -20);
    EXPECT_EQ(rect.left(), -10);
    EXPECT_EQ(rect.top(), -20);
    EXPECT_EQ(rect.right(), 20);   // -10 + 30
    EXPECT_EQ(rect.bottom(), 20);  // -20 + 40
}

// Test set_bottom specifically (the provided partial code)
TEST(RectangleTest_1020, SetBottomOnDefaultRectangle_1020) {
    rectangle<int> rect;
    rect.set_bottom(50);
    EXPECT_EQ(rect.bottom(), 50);
}

TEST(RectangleTest_1020, SetBottomToNegative_1020) {
    rectangle<int> rect(0, 0, 10, 10);
    rect.set_bottom(-5);
    EXPECT_EQ(rect.bottom(), -5);
}

TEST(RectangleTest_1020, SetBottomToZero_1020) {
    rectangle<int> rect(0, 5, 10, 10);
    rect.set_bottom(0);
    EXPECT_EQ(rect.bottom(), 0);
    EXPECT_EQ(rect.height(), -5);  // 0 - 5
}

// Test copy semantics
TEST(RectangleTest_1020, CopyConstructor_1020) {
    rectangle<int> rect1(1, 2, 3, 4);
    rectangle<int> rect2(rect1);
    EXPECT_EQ(rect2.x(), 1);
    EXPECT_EQ(rect2.y(), 2);
    EXPECT_EQ(rect2.width(), 3);
    EXPECT_EQ(rect2.height(), 4);
}

TEST(RectangleTest_1020, CopyAssignment_1020) {
    rectangle<int> rect1(1, 2, 3, 4);
    rectangle<int> rect2;
    rect2 = rect1;
    EXPECT_EQ(rect2.x(), 1);
    EXPECT_EQ(rect2.y(), 2);
    EXPECT_EQ(rect2.width(), 3);
    EXPECT_EQ(rect2.height(), 4);
}

// Test multiple setters in sequence
TEST(RectangleTest_1020, MultipleSettersCombined_1020) {
    rectangle<int> rect;
    rect.set_left(10);
    rect.set_top(20);
    rect.set_right(50);
    rect.set_bottom(80);
    EXPECT_EQ(rect.left(), 10);
    EXPECT_EQ(rect.top(), 20);
    EXPECT_EQ(rect.right(), 50);
    EXPECT_EQ(rect.bottom(), 80);
    EXPECT_EQ(rect.width(), 40);   // 50 - 10
    EXPECT_EQ(rect.height(), 60);  // 80 - 20
    EXPECT_FALSE(rect.is_empty());
}

// Test with float type
TEST(RectangleTest_1020, FloatTypeRectangle_1020) {
    rectangle<float> rect(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(rect.x(), 1.0f);
    EXPECT_FLOAT_EQ(rect.y(), 2.0f);
    EXPECT_FLOAT_EQ(rect.width(), 3.0f);
    EXPECT_FLOAT_EQ(rect.height(), 4.0f);
    EXPECT_FLOAT_EQ(rect.left(), 1.0f);
    EXPECT_FLOAT_EQ(rect.top(), 2.0f);
    EXPECT_FLOAT_EQ(rect.right(), 4.0f);
    EXPECT_FLOAT_EQ(rect.bottom(), 6.0f);
}

// Test large values
TEST(RectangleTest_1020, LargeValues_1020) {
    rectangle<int> rect(1000000, 2000000, 3000000, 4000000);
    EXPECT_EQ(rect.x(), 1000000);
    EXPECT_EQ(rect.y(), 2000000);
    EXPECT_EQ(rect.width(), 3000000);
    EXPECT_EQ(rect.height(), 4000000);
    EXPECT_EQ(rect.right(), 4000000);
    EXPECT_EQ(rect.bottom(), 6000000);
}
