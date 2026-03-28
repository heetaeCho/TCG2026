#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor
TEST(RectangleTest_1015, DefaultConstructor_1015) {
    rectangle<int> rect;
    EXPECT_EQ(rect.x(), 0);
    EXPECT_EQ(rect.y(), 0);
    EXPECT_EQ(rect.width(), 0);
    EXPECT_EQ(rect.height(), 0);
}

TEST(RectangleTest_1015, DefaultConstructorDouble_1015) {
    rectangle<double> rect;
    EXPECT_DOUBLE_EQ(rect.x(), 0.0);
    EXPECT_DOUBLE_EQ(rect.y(), 0.0);
    EXPECT_DOUBLE_EQ(rect.width(), 0.0);
    EXPECT_DOUBLE_EQ(rect.height(), 0.0);
}

// Test parameterized constructor
TEST(RectangleTest_1015, ParameterizedConstructorInt_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    EXPECT_EQ(rect.x(), 10);
    EXPECT_EQ(rect.y(), 20);
    EXPECT_EQ(rect.width(), 30);
    EXPECT_EQ(rect.height(), 40);
}

TEST(RectangleTest_1015, ParameterizedConstructorDouble_1015) {
    rectangle<double> rect(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(rect.x(), 1.5);
    EXPECT_DOUBLE_EQ(rect.y(), 2.5);
    EXPECT_DOUBLE_EQ(rect.width(), 3.5);
    EXPECT_DOUBLE_EQ(rect.height(), 4.5);
}

// Test left, top, right, bottom
TEST(RectangleTest_1015, LeftTopRightBottom_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    EXPECT_EQ(rect.left(), 10);
    EXPECT_EQ(rect.top(), 20);
    EXPECT_EQ(rect.right(), 40);   // x + width = 10 + 30
    EXPECT_EQ(rect.bottom(), 60);  // y + height = 20 + 40
}

TEST(RectangleTest_1015, RightMethod_1015) {
    rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.right(), 20);  // 5 + 15
}

TEST(RectangleTest_1015, RightMethodDouble_1015) {
    rectangle<double> rect(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(rect.right(), 4.0);  // 1.0 + 3.0
}

// Test is_empty
TEST(RectangleTest_1015, IsEmptyDefaultConstructor_1015) {
    rectangle<int> rect;
    EXPECT_TRUE(rect.is_empty());
}

TEST(RectangleTest_1015, IsEmptyNonEmpty_1015) {
    rectangle<int> rect(0, 0, 10, 10);
    EXPECT_FALSE(rect.is_empty());
}

TEST(RectangleTest_1015, IsEmptyZeroWidth_1015) {
    rectangle<int> rect(5, 5, 0, 10);
    EXPECT_TRUE(rect.is_empty());
}

TEST(RectangleTest_1015, IsEmptyZeroHeight_1015) {
    rectangle<int> rect(5, 5, 10, 0);
    EXPECT_TRUE(rect.is_empty());
}

// Test setters
TEST(RectangleTest_1015, SetLeft_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    rect.set_left(5);
    EXPECT_EQ(rect.left(), 5);
}

TEST(RectangleTest_1015, SetTop_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    rect.set_top(15);
    EXPECT_EQ(rect.top(), 15);
}

TEST(RectangleTest_1015, SetRight_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    rect.set_right(100);
    EXPECT_EQ(rect.right(), 100);
}

TEST(RectangleTest_1015, SetBottom_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    rect.set_bottom(200);
    EXPECT_EQ(rect.bottom(), 200);
}

// Test that setting left changes x and width accordingly
TEST(RectangleTest_1015, SetLeftAffectsX_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    rect.set_left(5);
    EXPECT_EQ(rect.x(), 5);
}

// Test that setting right changes width
TEST(RectangleTest_1015, SetRightAffectsWidth_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    // right was 40, now set to 50
    rect.set_right(50);
    EXPECT_EQ(rect.right(), 50);
    EXPECT_EQ(rect.width(), 40);  // 50 - 10
}

// Test that setting top affects y
TEST(RectangleTest_1015, SetTopAffectsY_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    rect.set_top(5);
    EXPECT_EQ(rect.y(), 5);
}

// Test that setting bottom affects height
TEST(RectangleTest_1015, SetBottomAffectsHeight_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    rect.set_bottom(100);
    EXPECT_EQ(rect.bottom(), 100);
    EXPECT_EQ(rect.height(), 80);  // 100 - 20
}

// Boundary: negative coordinates
TEST(RectangleTest_1015, NegativeCoordinates_1015) {
    rectangle<int> rect(-10, -20, 30, 40);
    EXPECT_EQ(rect.x(), -10);
    EXPECT_EQ(rect.y(), -20);
    EXPECT_EQ(rect.left(), -10);
    EXPECT_EQ(rect.top(), -20);
    EXPECT_EQ(rect.right(), 20);   // -10 + 30
    EXPECT_EQ(rect.bottom(), 20);  // -20 + 40
    EXPECT_EQ(rect.width(), 30);
    EXPECT_EQ(rect.height(), 40);
}

// Boundary: zero-sized rectangle at origin
TEST(RectangleTest_1015, ZeroSizedAtOrigin_1015) {
    rectangle<int> rect(0, 0, 0, 0);
    EXPECT_TRUE(rect.is_empty());
    EXPECT_EQ(rect.left(), 0);
    EXPECT_EQ(rect.top(), 0);
    EXPECT_EQ(rect.right(), 0);
    EXPECT_EQ(rect.bottom(), 0);
}

// Test with float type
TEST(RectangleTest_1015, FloatType_1015) {
    rectangle<float> rect(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(rect.x(), 1.0f);
    EXPECT_FLOAT_EQ(rect.y(), 2.0f);
    EXPECT_FLOAT_EQ(rect.width(), 3.0f);
    EXPECT_FLOAT_EQ(rect.height(), 4.0f);
    EXPECT_FLOAT_EQ(rect.right(), 4.0f);
    EXPECT_FLOAT_EQ(rect.bottom(), 6.0f);
}

// Large values
TEST(RectangleTest_1015, LargeValues_1015) {
    rectangle<int> rect(1000000, 2000000, 3000000, 4000000);
    EXPECT_EQ(rect.right(), 4000000);
    EXPECT_EQ(rect.bottom(), 6000000);
    EXPECT_FALSE(rect.is_empty());
}

// Set all corners and verify consistency
TEST(RectangleTest_1015, SetAllCorners_1015) {
    rectangle<int> rect;
    rect.set_left(10);
    rect.set_top(20);
    rect.set_right(50);
    rect.set_bottom(70);
    EXPECT_EQ(rect.left(), 10);
    EXPECT_EQ(rect.top(), 20);
    EXPECT_EQ(rect.right(), 50);
    EXPECT_EQ(rect.bottom(), 70);
    EXPECT_EQ(rect.width(), 40);
    EXPECT_EQ(rect.height(), 50);
    EXPECT_FALSE(rect.is_empty());
}

// Verify width/height with negative dimensions (if allowed by setting right < left)
TEST(RectangleTest_1015, NegativeDimensions_1015) {
    rectangle<int> rect;
    rect.set_left(50);
    rect.set_right(10);
    // width would be negative: 10 - 50 = -40
    EXPECT_EQ(rect.right(), 10);
    EXPECT_EQ(rect.left(), 50);
}

// Copy semantics
TEST(RectangleTest_1015, CopyConstructor_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    rectangle<int> copy(rect);
    EXPECT_EQ(copy.x(), rect.x());
    EXPECT_EQ(copy.y(), rect.y());
    EXPECT_EQ(copy.width(), rect.width());
    EXPECT_EQ(copy.height(), rect.height());
    EXPECT_EQ(copy.right(), rect.right());
    EXPECT_EQ(copy.bottom(), rect.bottom());
}

TEST(RectangleTest_1015, AssignmentOperator_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    rectangle<int> other;
    other = rect;
    EXPECT_EQ(other.x(), 10);
    EXPECT_EQ(other.y(), 20);
    EXPECT_EQ(other.width(), 30);
    EXPECT_EQ(other.height(), 40);
}
