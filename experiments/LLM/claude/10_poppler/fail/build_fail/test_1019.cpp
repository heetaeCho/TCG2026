#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor creates an empty rectangle with all zeros
TEST(RectangleTest_1019, DefaultConstructor_1019) {
    rectangle<int> r;
    EXPECT_EQ(r.x(), 0);
    EXPECT_EQ(r.y(), 0);
    EXPECT_EQ(r.width(), 0);
    EXPECT_EQ(r.height(), 0);
}

// Test parameterized constructor
TEST(RectangleTest_1019, ParameterizedConstructor_1019) {
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(r.x(), 10);
    EXPECT_EQ(r.y(), 20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
}

// Test left/top/right/bottom after parameterized construction
TEST(RectangleTest_1019, LeftTopRightBottom_1019) {
    rectangle<int> r(5, 10, 20, 30);
    EXPECT_EQ(r.left(), 5);
    EXPECT_EQ(r.top(), 10);
    EXPECT_EQ(r.right(), 25);   // x + width = 5 + 20
    EXPECT_EQ(r.bottom(), 40);  // y + height = 10 + 30
}

// Test is_empty on default constructed rectangle
TEST(RectangleTest_1019, DefaultIsEmpty_1019) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty on non-empty rectangle
TEST(RectangleTest_1019, NonEmptyRectangle_1019) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
}

// Test set_right
TEST(RectangleTest_1019, SetRight_1019) {
    rectangle<int> r(0, 0, 10, 10);
    r.set_right(50);
    EXPECT_EQ(r.right(), 50);
    EXPECT_EQ(r.width(), 50);  // width = right - left = 50 - 0
}

// Test set_left
TEST(RectangleTest_1019, SetLeft_1019) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_left(5);
    EXPECT_EQ(r.left(), 5);
    EXPECT_EQ(r.x(), 5);
}

// Test set_top
TEST(RectangleTest_1019, SetTop_1019) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_top(15);
    EXPECT_EQ(r.top(), 15);
    EXPECT_EQ(r.y(), 15);
}

// Test set_bottom
TEST(RectangleTest_1019, SetBottom_1019) {
    rectangle<int> r(10, 20, 30, 40);
    r.set_bottom(100);
    EXPECT_EQ(r.bottom(), 100);
}

// Test with double type
TEST(RectangleTest_1019, DoubleType_1019) {
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

// Test zero width rectangle is empty
TEST(RectangleTest_1019, ZeroWidthIsEmpty_1019) {
    rectangle<int> r(5, 5, 0, 10);
    EXPECT_TRUE(r.is_empty());
}

// Test zero height rectangle is empty
TEST(RectangleTest_1019, ZeroHeightIsEmpty_1019) {
    rectangle<int> r(5, 5, 10, 0);
    EXPECT_TRUE(r.is_empty());
}

// Test negative dimensions
TEST(RectangleTest_1019, NegativeDimensions_1019) {
    rectangle<int> r(10, 10, -5, -5);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.top(), 10);
    EXPECT_EQ(r.right(), 5);   // 10 + (-5)
    EXPECT_EQ(r.bottom(), 5);  // 10 + (-5)
}

// Test width and height computed correctly after set operations
TEST(RectangleTest_1019, WidthHeightAfterSetters_1019) {
    rectangle<int> r(0, 0, 100, 200);
    r.set_left(10);
    r.set_right(90);
    EXPECT_EQ(r.width(), 80);  // 90 - 10

    r.set_top(20);
    r.set_bottom(180);
    EXPECT_EQ(r.height(), 160);  // 180 - 20
}

// Test setting right equal to left makes width zero
TEST(RectangleTest_1019, SetRightEqualToLeft_1019) {
    rectangle<int> r(10, 10, 50, 50);
    r.set_right(10);
    EXPECT_EQ(r.width(), 0);
    EXPECT_TRUE(r.is_empty());
}

// Test setting bottom equal to top makes height zero
TEST(RectangleTest_1019, SetBottomEqualToTop_1019) {
    rectangle<int> r(10, 10, 50, 50);
    r.set_bottom(10);
    EXPECT_EQ(r.height(), 0);
    EXPECT_TRUE(r.is_empty());
}

// Test large values
TEST(RectangleTest_1019, LargeValues_1019) {
    rectangle<int> r(0, 0, 1000000, 1000000);
    EXPECT_EQ(r.right(), 1000000);
    EXPECT_EQ(r.bottom(), 1000000);
    EXPECT_FALSE(r.is_empty());
}

// Test copy behavior (implicit copy constructor)
TEST(RectangleTest_1019, CopyConstructor_1019) {
    rectangle<int> r1(5, 10, 15, 20);
    rectangle<int> r2 = r1;
    EXPECT_EQ(r2.x(), 5);
    EXPECT_EQ(r2.y(), 10);
    EXPECT_EQ(r2.width(), 15);
    EXPECT_EQ(r2.height(), 20);
}

// Test assignment operator
TEST(RectangleTest_1019, AssignmentOperator_1019) {
    rectangle<int> r1(5, 10, 15, 20);
    rectangle<int> r2;
    r2 = r1;
    EXPECT_EQ(r2.x(), 5);
    EXPECT_EQ(r2.y(), 10);
    EXPECT_EQ(r2.width(), 15);
    EXPECT_EQ(r2.height(), 20);
}

// Test float type
TEST(RectangleTest_1019, FloatType_1019) {
    rectangle<float> r(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(r.x(), 1.0f);
    EXPECT_FLOAT_EQ(r.y(), 2.0f);
    EXPECT_FLOAT_EQ(r.width(), 3.0f);
    EXPECT_FLOAT_EQ(r.height(), 4.0f);
}

// Test that x() == left() and y() == top()
TEST(RectangleTest_1019, XEqualsLeftYEqualsTop_1019) {
    rectangle<int> r(42, 84, 100, 200);
    EXPECT_EQ(r.x(), r.left());
    EXPECT_EQ(r.y(), r.top());
}
