#include <gtest/gtest.h>
#include "poppler-rectangle.h"

// Test default constructor
TEST(RectangleTest_1010, DefaultConstructor_1010) {
    poppler::rectangle<int> rect;
    EXPECT_EQ(rect.x(), 0);
    EXPECT_EQ(rect.y(), 0);
    EXPECT_EQ(rect.width(), 0);
    EXPECT_EQ(rect.height(), 0);
}

TEST(RectangleTest_1010, DefaultConstructorDouble_1010) {
    poppler::rectangle<double> rect;
    EXPECT_DOUBLE_EQ(rect.x(), 0.0);
    EXPECT_DOUBLE_EQ(rect.y(), 0.0);
    EXPECT_DOUBLE_EQ(rect.width(), 0.0);
    EXPECT_DOUBLE_EQ(rect.height(), 0.0);
}

// Test parameterized constructor
TEST(RectangleTest_1010, ParameterizedConstructor_1010) {
    poppler::rectangle<int> rect(10, 20, 30, 40);
    EXPECT_EQ(rect.x(), 10);
    EXPECT_EQ(rect.y(), 20);
    EXPECT_EQ(rect.width(), 30);
    EXPECT_EQ(rect.height(), 40);
}

TEST(RectangleTest_1010, ParameterizedConstructorDouble_1010) {
    poppler::rectangle<double> rect(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(rect.x(), 1.5);
    EXPECT_DOUBLE_EQ(rect.y(), 2.5);
    EXPECT_DOUBLE_EQ(rect.width(), 3.5);
    EXPECT_DOUBLE_EQ(rect.height(), 4.5);
}

// Test x() and y() accessors
TEST(RectangleTest_1010, XAccessor_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.x(), 5);
}

TEST(RectangleTest_1010, YAccessor_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.y(), 10);
}

// Test width() and height()
TEST(RectangleTest_1010, WidthAccessor_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.width(), 15);
}

TEST(RectangleTest_1010, HeightAccessor_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.height(), 20);
}

// Test left(), top(), right(), bottom()
TEST(RectangleTest_1010, LeftAccessor_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.left(), 5);
}

TEST(RectangleTest_1010, TopAccessor_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.top(), 10);
}

TEST(RectangleTest_1010, RightAccessor_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.right(), 20); // x1 + width = 5 + 15 = 20
}

TEST(RectangleTest_1010, BottomAccessor_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.bottom(), 30); // y1 + height = 10 + 20 = 30
}

// Test is_empty()
TEST(RectangleTest_1010, IsEmptyDefaultConstructor_1010) {
    poppler::rectangle<int> rect;
    EXPECT_TRUE(rect.is_empty());
}

TEST(RectangleTest_1010, IsEmptyNonEmpty_1010) {
    poppler::rectangle<int> rect(0, 0, 10, 10);
    EXPECT_FALSE(rect.is_empty());
}

TEST(RectangleTest_1010, IsEmptyZeroWidth_1010) {
    poppler::rectangle<int> rect(5, 5, 0, 10);
    EXPECT_TRUE(rect.is_empty());
}

TEST(RectangleTest_1010, IsEmptyZeroHeight_1010) {
    poppler::rectangle<int> rect(5, 5, 10, 0);
    EXPECT_TRUE(rect.is_empty());
}

TEST(RectangleTest_1010, IsEmptyZeroBoth_1010) {
    poppler::rectangle<int> rect(5, 5, 0, 0);
    EXPECT_TRUE(rect.is_empty());
}

// Test set_left, set_top, set_right, set_bottom
TEST(RectangleTest_1010, SetLeft_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    rect.set_left(100);
    EXPECT_EQ(rect.left(), 100);
}

TEST(RectangleTest_1010, SetTop_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    rect.set_top(200);
    EXPECT_EQ(rect.top(), 200);
}

TEST(RectangleTest_1010, SetRight_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    rect.set_right(300);
    EXPECT_EQ(rect.right(), 300);
}

TEST(RectangleTest_1010, SetBottom_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    rect.set_bottom(400);
    EXPECT_EQ(rect.bottom(), 400);
}

// Test that setters affect width/height correctly
TEST(RectangleTest_1010, SetLeftAffectsWidth_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    // right is 20, left was 5, width was 15
    rect.set_left(10);
    // right should still be 20, so width = 20 - 10 = 10
    EXPECT_EQ(rect.left(), 10);
    EXPECT_EQ(rect.right(), 20);
    EXPECT_EQ(rect.width(), 10);
}

TEST(RectangleTest_1010, SetRightAffectsWidth_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    rect.set_right(50);
    EXPECT_EQ(rect.left(), 5);
    EXPECT_EQ(rect.right(), 50);
    EXPECT_EQ(rect.width(), 45);
}

TEST(RectangleTest_1010, SetTopAffectsHeight_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    rect.set_top(5);
    EXPECT_EQ(rect.top(), 5);
    EXPECT_EQ(rect.bottom(), 30);
    EXPECT_EQ(rect.height(), 25);
}

TEST(RectangleTest_1010, SetBottomAffectsHeight_1010) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    rect.set_bottom(100);
    EXPECT_EQ(rect.top(), 10);
    EXPECT_EQ(rect.bottom(), 100);
    EXPECT_EQ(rect.height(), 90);
}

// Boundary: negative dimensions
TEST(RectangleTest_1010, NegativeWidthHeight_1010) {
    poppler::rectangle<int> rect(10, 10, -5, -5);
    EXPECT_EQ(rect.x(), 10);
    EXPECT_EQ(rect.y(), 10);
    EXPECT_EQ(rect.width(), -5);
    EXPECT_EQ(rect.height(), -5);
}

// Boundary: negative coordinates
TEST(RectangleTest_1010, NegativeCoordinates_1010) {
    poppler::rectangle<int> rect(-10, -20, 30, 40);
    EXPECT_EQ(rect.x(), -10);
    EXPECT_EQ(rect.y(), -20);
    EXPECT_EQ(rect.width(), 30);
    EXPECT_EQ(rect.height(), 40);
    EXPECT_EQ(rect.left(), -10);
    EXPECT_EQ(rect.top(), -20);
    EXPECT_EQ(rect.right(), 20);
    EXPECT_EQ(rect.bottom(), 20);
}

// Test with float type
TEST(RectangleTest_1010, FloatType_1010) {
    poppler::rectangle<float> rect(1.0f, 2.0f, 3.0f, 4.0f);
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
TEST(RectangleTest_1010, LargeValues_1010) {
    poppler::rectangle<int> rect(1000000, 2000000, 3000000, 4000000);
    EXPECT_EQ(rect.x(), 1000000);
    EXPECT_EQ(rect.y(), 2000000);
    EXPECT_EQ(rect.width(), 3000000);
    EXPECT_EQ(rect.height(), 4000000);
}

// Test copy behavior
TEST(RectangleTest_1010, CopyConstructor_1010) {
    poppler::rectangle<int> rect1(5, 10, 15, 20);
    poppler::rectangle<int> rect2(rect1);
    EXPECT_EQ(rect2.x(), 5);
    EXPECT_EQ(rect2.y(), 10);
    EXPECT_EQ(rect2.width(), 15);
    EXPECT_EQ(rect2.height(), 20);
}

TEST(RectangleTest_1010, AssignmentOperator_1010) {
    poppler::rectangle<int> rect1(5, 10, 15, 20);
    poppler::rectangle<int> rect2;
    rect2 = rect1;
    EXPECT_EQ(rect2.x(), 5);
    EXPECT_EQ(rect2.y(), 10);
    EXPECT_EQ(rect2.width(), 15);
    EXPECT_EQ(rect2.height(), 20);
}

// Verify that modifying a copy does not affect the original
TEST(RectangleTest_1010, CopyIndependence_1010) {
    poppler::rectangle<int> rect1(5, 10, 15, 20);
    poppler::rectangle<int> rect2(rect1);
    rect2.set_left(100);
    EXPECT_EQ(rect1.left(), 5);
    EXPECT_EQ(rect2.left(), 100);
}

// Test is_empty after setters make it empty
TEST(RectangleTest_1010, IsEmptyAfterSetLeftEqualsRight_1010) {
    poppler::rectangle<int> rect(0, 0, 10, 10);
    EXPECT_FALSE(rect.is_empty());
    rect.set_left(10); // left == right
    EXPECT_TRUE(rect.is_empty());
}

TEST(RectangleTest_1010, IsEmptyAfterSetTopEqualsBottom_1010) {
    poppler::rectangle<int> rect(0, 0, 10, 10);
    EXPECT_FALSE(rect.is_empty());
    rect.set_top(10); // top == bottom
    EXPECT_TRUE(rect.is_empty());
}
