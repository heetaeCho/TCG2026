#include <gtest/gtest.h>
#include "./TestProjects/poppler/cpp/poppler-rectangle.h"

namespace {

using poppler::rectangle;

// ============================================================
// Default Constructor Tests
// ============================================================

TEST(RectangleTest_1008, DefaultConstructorCreatesEmptyRectangle_1008)
{
    rectangle<int> r;
    EXPECT_TRUE(r.is_empty());
}

TEST(RectangleTest_1008, DefaultConstructorZeroCoordinatesInt_1008)
{
    rectangle<int> r;
    EXPECT_EQ(0, r.x());
    EXPECT_EQ(0, r.y());
    EXPECT_EQ(0, r.width());
    EXPECT_EQ(0, r.height());
}

TEST(RectangleTest_1008, DefaultConstructorZeroCoordinatesDouble_1008)
{
    rectangle<double> r;
    EXPECT_DOUBLE_EQ(0.0, r.x());
    EXPECT_DOUBLE_EQ(0.0, r.y());
    EXPECT_DOUBLE_EQ(0.0, r.width());
    EXPECT_DOUBLE_EQ(0.0, r.height());
}

// ============================================================
// Parameterized Constructor Tests
// ============================================================

TEST(RectangleTest_1008, ParameterizedConstructorSetsValues_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(10, r.x());
    EXPECT_EQ(20, r.y());
    EXPECT_EQ(30, r.width());
    EXPECT_EQ(40, r.height());
}

TEST(RectangleTest_1008, ParameterizedConstructorDouble_1008)
{
    rectangle<double> r(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(1.5, r.x());
    EXPECT_DOUBLE_EQ(2.5, r.y());
    EXPECT_DOUBLE_EQ(3.5, r.width());
    EXPECT_DOUBLE_EQ(4.5, r.height());
}

TEST(RectangleTest_1008, ParameterizedConstructorWithZeroDimensions_1008)
{
    rectangle<int> r(5, 10, 0, 0);
    EXPECT_TRUE(r.is_empty());
}

TEST(RectangleTest_1008, ParameterizedConstructorNonEmpty_1008)
{
    rectangle<int> r(5, 10, 15, 20);
    EXPECT_FALSE(r.is_empty());
}

// ============================================================
// is_empty Tests
// ============================================================

TEST(RectangleTest_1008, IsEmptyWhenWidthZero_1008)
{
    rectangle<int> r(5, 10, 0, 20);
    // x1 == x2 but y1 != y2, so is_empty should be false based on the provided code
    // is_empty checks (x1==x2) && (y1==y2)
    EXPECT_FALSE(r.is_empty());
}

TEST(RectangleTest_1008, IsEmptyWhenHeightZero_1008)
{
    rectangle<int> r(5, 10, 20, 0);
    // x1 != x2 but y1 == y2
    EXPECT_FALSE(r.is_empty());
}

TEST(RectangleTest_1008, IsEmptyWhenBothDimensionsZero_1008)
{
    rectangle<int> r(5, 10, 0, 0);
    EXPECT_TRUE(r.is_empty());
}

TEST(RectangleTest_1008, IsNotEmptyForPositiveDimensions_1008)
{
    rectangle<int> r(0, 0, 10, 10);
    EXPECT_FALSE(r.is_empty());
}

// ============================================================
// Accessor Tests (left, top, right, bottom)
// ============================================================

TEST(RectangleTest_1008, LeftReturnsX1_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(10, r.left());
}

TEST(RectangleTest_1008, TopReturnsY1_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(20, r.top());
}

TEST(RectangleTest_1008, RightReturnsX2_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(40, r.right());  // x1 + w = 10 + 30 = 40
}

TEST(RectangleTest_1008, BottomReturnsY2_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_EQ(60, r.bottom());  // y1 + h = 20 + 40 = 60
}

// ============================================================
// x(), y(), width(), height() Tests
// ============================================================

TEST(RectangleTest_1008, XReturnsLeftCoordinate_1008)
{
    rectangle<int> r(15, 25, 35, 45);
    EXPECT_EQ(15, r.x());
}

TEST(RectangleTest_1008, YReturnsTopCoordinate_1008)
{
    rectangle<int> r(15, 25, 35, 45);
    EXPECT_EQ(25, r.y());
}

TEST(RectangleTest_1008, WidthReturnsCorrectValue_1008)
{
    rectangle<int> r(15, 25, 35, 45);
    EXPECT_EQ(35, r.width());
}

TEST(RectangleTest_1008, HeightReturnsCorrectValue_1008)
{
    rectangle<int> r(15, 25, 35, 45);
    EXPECT_EQ(45, r.height());
}

// ============================================================
// Setter Tests
// ============================================================

TEST(RectangleTest_1008, SetLeftChangesLeftCoordinate_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    r.set_left(5);
    EXPECT_EQ(5, r.left());
}

TEST(RectangleTest_1008, SetTopChangesTopCoordinate_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    r.set_top(5);
    EXPECT_EQ(5, r.top());
}

TEST(RectangleTest_1008, SetRightChangesRightCoordinate_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    r.set_right(100);
    EXPECT_EQ(100, r.right());
}

TEST(RectangleTest_1008, SetBottomChangesBottomCoordinate_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    r.set_bottom(100);
    EXPECT_EQ(100, r.bottom());
}

TEST(RectangleTest_1008, SetLeftAffectsWidth_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    // right is 40, set left to 10 -> width should be 30
    // set left to 20 -> width should be 20
    r.set_left(20);
    EXPECT_EQ(20, r.width());
}

TEST(RectangleTest_1008, SetRightAffectsWidth_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    // left is 10, right was 40
    r.set_right(50);
    EXPECT_EQ(40, r.width());
}

TEST(RectangleTest_1008, SetTopAffectsHeight_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    // bottom is 60, set top to 30 -> height should be 30
    r.set_top(30);
    EXPECT_EQ(30, r.height());
}

TEST(RectangleTest_1008, SetBottomAffectsHeight_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    // top is 20, bottom was 60
    r.set_bottom(70);
    EXPECT_EQ(50, r.height());
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST(RectangleTest_1008, NegativeCoordinates_1008)
{
    rectangle<int> r(-10, -20, 30, 40);
    EXPECT_EQ(-10, r.x());
    EXPECT_EQ(-20, r.y());
    EXPECT_EQ(30, r.width());
    EXPECT_EQ(40, r.height());
    EXPECT_EQ(-10, r.left());
    EXPECT_EQ(-20, r.top());
    EXPECT_EQ(20, r.right());   // -10 + 30
    EXPECT_EQ(20, r.bottom());  // -20 + 40
}

TEST(RectangleTest_1008, LargeValues_1008)
{
    rectangle<int> r(100000, 200000, 300000, 400000);
    EXPECT_EQ(100000, r.x());
    EXPECT_EQ(200000, r.y());
    EXPECT_EQ(300000, r.width());
    EXPECT_EQ(400000, r.height());
}

TEST(RectangleTest_1008, FloatType_1008)
{
    rectangle<float> r(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(1.0f, r.x());
    EXPECT_FLOAT_EQ(2.0f, r.y());
    EXPECT_FLOAT_EQ(3.0f, r.width());
    EXPECT_FLOAT_EQ(4.0f, r.height());
    EXPECT_FLOAT_EQ(4.0f, r.right());
    EXPECT_FLOAT_EQ(6.0f, r.bottom());
}

TEST(RectangleTest_1008, SetMakesRectangleEmpty_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    EXPECT_FALSE(r.is_empty());
    r.set_right(10);   // left == right
    r.set_bottom(20);  // top == bottom
    EXPECT_TRUE(r.is_empty());
}

TEST(RectangleTest_1008, SetLeftEqualToRightPartialEmpty_1008)
{
    rectangle<int> r(10, 20, 30, 40);
    r.set_left(40);  // left == right
    // x1 == x2 but y1 != y2, so not empty per the is_empty logic
    EXPECT_FALSE(r.is_empty());
}

TEST(RectangleTest_1008, NegativeWidthViaConstructor_1008)
{
    // Negative width scenario
    rectangle<int> r(10, 20, -5, -10);
    EXPECT_EQ(10, r.left());
    EXPECT_EQ(20, r.top());
    EXPECT_EQ(5, r.right());    // 10 + (-5)
    EXPECT_EQ(10, r.bottom());  // 20 + (-10)
}

TEST(RectangleTest_1008, ZeroOriginWithDimensions_1008)
{
    rectangle<int> r(0, 0, 100, 200);
    EXPECT_EQ(0, r.x());
    EXPECT_EQ(0, r.y());
    EXPECT_EQ(100, r.width());
    EXPECT_EQ(200, r.height());
    EXPECT_FALSE(r.is_empty());
}

}  // namespace
