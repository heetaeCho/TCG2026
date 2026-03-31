#include <gtest/gtest.h>
#include "poppler-rectangle.h"

using namespace poppler;

// Test default constructor
TEST(RectangleTest_1009, DefaultConstructor_1009) {
    rectangle<int> r;
    EXPECT_EQ(r.x(), 0);
    EXPECT_EQ(r.y(), 0);
    EXPECT_EQ(r.width(), 0);
    EXPECT_EQ(r.height(), 0);
}

TEST(RectangleTest_1009, DefaultConstructorDouble_1009) {
    rectangle<double> r;
    EXPECT_DOUBLE_EQ(r.x(), 0.0);
    EXPECT_DOUBLE_EQ(r.y(), 0.0);
    EXPECT_DOUBLE_EQ(r.width(), 0.0);
    EXPECT_DOUBLE_EQ(r.height(), 0.0);
}

// Test parameterized constructor
TEST(RectangleTest_1009, ParameterizedConstructorInt_1009) {
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(r.x(), 10);
    EXPECT_EQ(r.y(), 20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
}

TEST(RectangleTest_1009, ParameterizedConstructorDouble_1009) {
    rectangle<double> r(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(r.x(), 1.5);
    EXPECT_DOUBLE_EQ(r.y(), 2.5);
    EXPECT_DOUBLE_EQ(r.width(), 3.5);
    EXPECT_DOUBLE_EQ(r.height(), 4.5);
}

// Test x() method
TEST(RectangleTest_1009, XReturnsLeftCoordinate_1009) {
    rectangle<int> r(5, 10, 20, 30);
    EXPECT_EQ(r.x(), 5);
}

// Test y() method
TEST(RectangleTest_1009, YReturnsTopCoordinate_1009) {
    rectangle<int> r(5, 10, 20, 30);
    EXPECT_EQ(r.y(), 10);
}

// Test width() method
TEST(RectangleTest_1009, WidthReturnsCorrectValue_1009) {
    rectangle<int> r(5, 10, 20, 30);
    EXPECT_EQ(r.width(), 20);
}

// Test height() method
TEST(RectangleTest_1009, HeightReturnsCorrectValue_1009) {
    rectangle<int> r(5, 10, 20, 30);
    EXPECT_EQ(r.height(), 30);
}

// Test left() method
TEST(RectangleTest_1009, LeftReturnsX1_1009) {
    rectangle<int> r(5, 10, 20, 30);
    EXPECT_EQ(r.left(), 5);
}

// Test top() method
TEST(RectangleTest_1009, TopReturnsY1_1009) {
    rectangle<int> r(5, 10, 20, 30);
    EXPECT_EQ(r.top(), 10);
}

// Test right() method
TEST(RectangleTest_1009, RightReturnsX2_1009) {
    rectangle<int> r(5, 10, 20, 30);
    EXPECT_EQ(r.right(), 25); // x1 + width = 5 + 20 = 25
}

// Test bottom() method
TEST(RectangleTest_1009, BottomReturnsY2_1009) {
    rectangle<int> r(5, 10, 20, 30);
    EXPECT_EQ(r.bottom(), 40); // y1 + height = 10 + 30 = 40
}

// Test is_empty() with default constructor
TEST(RectangleTest_1009, DefaultRectangleIsEmpty_1009) {
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty() with non-zero dimensions
TEST(RectangleTest_1009, NonZeroRectangleIsNotEmpty_1009) {
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
}

// Test is_empty() with zero width
TEST(RectangleTest_1009, ZeroWidthRectangleIsEmpty_1009) {
    rectangle<int> r(5, 5, 0, 10);
    EXPECT_TRUE(r.is_empty());
}

// Test is_empty() with zero height
TEST(RectangleTest_1009, ZeroHeightRectangleIsEmpty_1009) {
    rectangle<int> r(5, 5, 10, 0);
    EXPECT_TRUE(r.is_empty());
}

// Test set_left()
TEST(RectangleTest_1009, SetLeftChangesLeft_1009) {
    rectangle<int> r(5, 10, 20, 30);
    r.set_left(15);
    EXPECT_EQ(r.left(), 15);
}

// Test set_top()
TEST(RectangleTest_1009, SetTopChangesTop_1009) {
    rectangle<int> r(5, 10, 20, 30);
    r.set_top(25);
    EXPECT_EQ(r.top(), 25);
}

// Test set_right()
TEST(RectangleTest_1009, SetRightChangesRight_1009) {
    rectangle<int> r(5, 10, 20, 30);
    r.set_right(50);
    EXPECT_EQ(r.right(), 50);
}

// Test set_bottom()
TEST(RectangleTest_1009, SetBottomChangesBottom_1009) {
    rectangle<int> r(5, 10, 20, 30);
    r.set_bottom(60);
    EXPECT_EQ(r.bottom(), 60);
}

// Test that set_left affects x() and width()
TEST(RectangleTest_1009, SetLeftAffectsXAndWidth_1009) {
    rectangle<int> r(5, 10, 20, 30);
    r.set_left(0);
    EXPECT_EQ(r.x(), 0);
    EXPECT_EQ(r.left(), 0);
    // right should remain unchanged
    EXPECT_EQ(r.right(), 25);
    // width should change: right - left = 25 - 0 = 25
    EXPECT_EQ(r.width(), 25);
}

// Test that set_right affects width()
TEST(RectangleTest_1009, SetRightAffectsWidth_1009) {
    rectangle<int> r(5, 10, 20, 30);
    r.set_right(100);
    EXPECT_EQ(r.right(), 100);
    EXPECT_EQ(r.left(), 5);
    // width = right - left = 100 - 5 = 95
    EXPECT_EQ(r.width(), 95);
}

// Test that set_top affects y() and height()
TEST(RectangleTest_1009, SetTopAffectsYAndHeight_1009) {
    rectangle<int> r(5, 10, 20, 30);
    r.set_top(0);
    EXPECT_EQ(r.y(), 0);
    EXPECT_EQ(r.top(), 0);
    // bottom should remain unchanged
    EXPECT_EQ(r.bottom(), 40);
    // height = bottom - top = 40 - 0 = 40
    EXPECT_EQ(r.height(), 40);
}

// Test that set_bottom affects height()
TEST(RectangleTest_1009, SetBottomAffectsHeight_1009) {
    rectangle<int> r(5, 10, 20, 30);
    r.set_bottom(100);
    EXPECT_EQ(r.bottom(), 100);
    EXPECT_EQ(r.top(), 10);
    // height = bottom - top = 100 - 10 = 90
    EXPECT_EQ(r.height(), 90);
}

// Test negative coordinates
TEST(RectangleTest_1009, NegativeCoordinates_1009) {
    rectangle<int> r(-10, -20, 30, 40);
    EXPECT_EQ(r.x(), -10);
    EXPECT_EQ(r.y(), -20);
    EXPECT_EQ(r.width(), 30);
    EXPECT_EQ(r.height(), 40);
    EXPECT_EQ(r.left(), -10);
    EXPECT_EQ(r.top(), -20);
    EXPECT_EQ(r.right(), 20);  // -10 + 30 = 20
    EXPECT_EQ(r.bottom(), 20); // -20 + 40 = 20
}

// Test with float type
TEST(RectangleTest_1009, FloatType_1009) {
    rectangle<float> r(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(r.x(), 1.0f);
    EXPECT_FLOAT_EQ(r.y(), 2.0f);
    EXPECT_FLOAT_EQ(r.width(), 3.0f);
    EXPECT_FLOAT_EQ(r.height(), 4.0f);
    EXPECT_FLOAT_EQ(r.left(), 1.0f);
    EXPECT_FLOAT_EQ(r.top(), 2.0f);
    EXPECT_FLOAT_EQ(r.right(), 4.0f);
    EXPECT_FLOAT_EQ(r.bottom(), 6.0f);
}

// Test negative width/height (degenerate rectangle)
TEST(RectangleTest_1009, NegativeDimensions_1009) {
    rectangle<int> r(10, 20, -5, -10);
    EXPECT_EQ(r.x(), 10);
    EXPECT_EQ(r.y(), 20);
    EXPECT_EQ(r.width(), -5);
    EXPECT_EQ(r.height(), -10);
    EXPECT_EQ(r.right(), 5);   // 10 + (-5) = 5
    EXPECT_EQ(r.bottom(), 10); // 20 + (-10) = 10
}

// Test is_empty with negative dimensions
TEST(RectangleTest_1009, NegativeDimensionsIsEmpty_1009) {
    rectangle<int> r(10, 20, -5, -10);
    EXPECT_TRUE(r.is_empty());
}

// Test large values
TEST(RectangleTest_1009, LargeValues_1009) {
    rectangle<int> r(1000000, 2000000, 3000000, 4000000);
    EXPECT_EQ(r.x(), 1000000);
    EXPECT_EQ(r.y(), 2000000);
    EXPECT_EQ(r.width(), 3000000);
    EXPECT_EQ(r.height(), 4000000);
}

// Test unit rectangle
TEST(RectangleTest_1009, UnitRectangle_1009) {
    rectangle<int> r(0, 0, 1, 1);
    EXPECT_FALSE(r.is_empty());
    EXPECT_EQ(r.x(), 0);
    EXPECT_EQ(r.y(), 0);
    EXPECT_EQ(r.width(), 1);
    EXPECT_EQ(r.height(), 1);
    EXPECT_EQ(r.left(), 0);
    EXPECT_EQ(r.top(), 0);
    EXPECT_EQ(r.right(), 1);
    EXPECT_EQ(r.bottom(), 1);
}

// Test set all corners
TEST(RectangleTest_1009, SetAllCorners_1009) {
    rectangle<int> r;
    r.set_left(10);
    r.set_top(20);
    r.set_right(30);
    r.set_bottom(40);
    EXPECT_EQ(r.left(), 10);
    EXPECT_EQ(r.top(), 20);
    EXPECT_EQ(r.right(), 30);
    EXPECT_EQ(r.bottom(), 40);
    EXPECT_EQ(r.width(), 20);
    EXPECT_EQ(r.height(), 20);
}

// Test copy behavior
TEST(RectangleTest_1009, CopyConstructor_1009) {
    rectangle<int> r1(5, 10, 20, 30);
    rectangle<int> r2(r1);
    EXPECT_EQ(r2.x(), 5);
    EXPECT_EQ(r2.y(), 10);
    EXPECT_EQ(r2.width(), 20);
    EXPECT_EQ(r2.height(), 30);
}

// Test assignment
TEST(RectangleTest_1009, AssignmentOperator_1009) {
    rectangle<int> r1(5, 10, 20, 30);
    rectangle<int> r2;
    r2 = r1;
    EXPECT_EQ(r2.x(), 5);
    EXPECT_EQ(r2.y(), 10);
    EXPECT_EQ(r2.width(), 20);
    EXPECT_EQ(r2.height(), 30);
}
