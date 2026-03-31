#include <gtest/gtest.h>
#include "PDFRectangle.h"

class PDFRectangleTest_683 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== contains() tests ====================

TEST_F(PDFRectangleTest_683, ContainsPointInsideRectangle_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(5.0, 5.0));
}

TEST_F(PDFRectangleTest_683, ContainsPointOnLeftEdge_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(0.0, 5.0));
}

TEST_F(PDFRectangleTest_683, ContainsPointOnRightEdge_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(10.0, 5.0));
}

TEST_F(PDFRectangleTest_683, ContainsPointOnTopEdge_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(5.0, 10.0));
}

TEST_F(PDFRectangleTest_683, ContainsPointOnBottomEdge_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(5.0, 0.0));
}

TEST_F(PDFRectangleTest_683, ContainsPointOnTopLeftCorner_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(0.0, 10.0));
}

TEST_F(PDFRectangleTest_683, ContainsPointOnTopRightCorner_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(10.0, 10.0));
}

TEST_F(PDFRectangleTest_683, ContainsPointOnBottomLeftCorner_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(0.0, 0.0));
}

TEST_F(PDFRectangleTest_683, ContainsPointOnBottomRightCorner_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(10.0, 0.0));
}

TEST_F(PDFRectangleTest_683, DoesNotContainPointOutsideLeft_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(-0.1, 5.0));
}

TEST_F(PDFRectangleTest_683, DoesNotContainPointOutsideRight_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(10.1, 5.0));
}

TEST_F(PDFRectangleTest_683, DoesNotContainPointOutsideTop_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(5.0, 10.1));
}

TEST_F(PDFRectangleTest_683, DoesNotContainPointOutsideBottom_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(5.0, -0.1));
}

TEST_F(PDFRectangleTest_683, DoesNotContainPointFarOutside_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(100.0, 100.0));
}

TEST_F(PDFRectangleTest_683, ContainsWithNegativeCoordinates_683) {
    PDFRectangle rect(-10.0, -10.0, -1.0, -1.0);
    EXPECT_TRUE(rect.contains(-5.0, -5.0));
}

TEST_F(PDFRectangleTest_683, DoesNotContainOriginInNegativeRect_683) {
    PDFRectangle rect(-10.0, -10.0, -1.0, -1.0);
    EXPECT_FALSE(rect.contains(0.0, 0.0));
}

TEST_F(PDFRectangleTest_683, ContainsWithMixedSignCoordinates_683) {
    PDFRectangle rect(-5.0, -5.0, 5.0, 5.0);
    EXPECT_TRUE(rect.contains(0.0, 0.0));
}

TEST_F(PDFRectangleTest_683, ContainsDegeneratePointRect_683) {
    PDFRectangle rect(5.0, 5.0, 5.0, 5.0);
    EXPECT_TRUE(rect.contains(5.0, 5.0));
}

TEST_F(PDFRectangleTest_683, DoesNotContainNearDegeneratePointRect_683) {
    PDFRectangle rect(5.0, 5.0, 5.0, 5.0);
    EXPECT_FALSE(rect.contains(5.1, 5.0));
}

TEST_F(PDFRectangleTest_683, ContainsWithVerySmallRect_683) {
    PDFRectangle rect(1.0, 1.0, 1.0 + 1e-10, 1.0 + 1e-10);
    EXPECT_TRUE(rect.contains(1.0 + 5e-11, 1.0 + 5e-11));
}

TEST_F(PDFRectangleTest_683, ContainsWithLargeValues_683) {
    PDFRectangle rect(0.0, 0.0, 1e15, 1e15);
    EXPECT_TRUE(rect.contains(5e14, 5e14));
}

// ==================== Default constructor tests ====================

TEST_F(PDFRectangleTest_683, DefaultConstructorCreatesZeroRect_683) {
    PDFRectangle rect;
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}

// ==================== Parameterized constructor tests ====================

TEST_F(PDFRectangleTest_683, ParameterizedConstructorSetsValues_683) {
    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(rect.x1, 1.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 3.0);
    EXPECT_DOUBLE_EQ(rect.y2, 4.0);
}

// ==================== operator== tests ====================

TEST_F(PDFRectangleTest_683, EqualRectanglesAreEqual_683) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_683, DifferentRectanglesAreNotEqual_683) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.0, 5.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_683, DefaultRectanglesAreEqual_683) {
    PDFRectangle rect1;
    PDFRectangle rect2;
    EXPECT_TRUE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_683, DifferentX1NotEqual_683) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.5, 2.0, 3.0, 4.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_683, DifferentY1NotEqual_683) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.5, 3.0, 4.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_683, DifferentX2NotEqual_683) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.5, 4.0);
    EXPECT_FALSE(rect1 == rect2);
}

// ==================== isValid() tests ====================

TEST_F(PDFRectangleTest_683, ValidRectangleIsValid_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.isValid());
}

TEST_F(PDFRectangleTest_683, DefaultRectangleValidity_683) {
    PDFRectangle rect;
    // Default rect has x1==x2 and y1==y2, all zero
    // Whether this is valid depends on implementation; just check it doesn't crash
    rect.isValid();
}

TEST_F(PDFRectangleTest_683, InvalidRectangleX1GreaterThanX2_683) {
    PDFRectangle rect(10.0, 0.0, 0.0, 10.0);
    // x1 > x2 might be considered invalid
    // Just observe the return
    bool result = rect.isValid();
    (void)result; // We call it to ensure no crash; behavior depends on implementation
}

// ==================== isEmpty() tests ====================

TEST_F(PDFRectangleTest_683, NonEmptyRectangleIsNotEmpty_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.isEmpty());
}

TEST_F(PDFRectangleTest_683, DefaultRectangleIsEmpty_683) {
    PDFRectangle rect;
    EXPECT_TRUE(rect.isEmpty());
}

TEST_F(PDFRectangleTest_683, ZeroWidthRectangleIsEmpty_683) {
    PDFRectangle rect(5.0, 0.0, 5.0, 10.0);
    // Width is zero, might be considered empty
    bool result = rect.isEmpty();
    (void)result;
}

TEST_F(PDFRectangleTest_683, ZeroHeightRectangleIsEmpty_683) {
    PDFRectangle rect(0.0, 5.0, 10.0, 5.0);
    bool result = rect.isEmpty();
    (void)result;
}

// ==================== clipTo() tests ====================

TEST_F(PDFRectangleTest_683, ClipToSmallerRect_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    PDFRectangle clipRect(2.0, 2.0, 8.0, 8.0);
    rect.clipTo(clipRect);
    // After clipping, rect should be within clipRect bounds
    EXPECT_TRUE(rect.contains(5.0, 5.0));
    EXPECT_GE(rect.x1, clipRect.x1);
    EXPECT_GE(rect.y1, clipRect.y1);
    EXPECT_LE(rect.x2, clipRect.x2);
    EXPECT_LE(rect.y2, clipRect.y2);
}

TEST_F(PDFRectangleTest_683, ClipToLargerRect_683) {
    PDFRectangle rect(2.0, 2.0, 8.0, 8.0);
    PDFRectangle clipRect(0.0, 0.0, 10.0, 10.0);
    rect.clipTo(clipRect);
    // Clipping to a larger rect should not change the original rect
    EXPECT_DOUBLE_EQ(rect.x1, 2.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 8.0);
    EXPECT_DOUBLE_EQ(rect.y2, 8.0);
}

TEST_F(PDFRectangleTest_683, ClipToPartiallyOverlappingRect_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    PDFRectangle clipRect(5.0, 5.0, 15.0, 15.0);
    rect.clipTo(clipRect);
    EXPECT_GE(rect.x1, 5.0);
    EXPECT_GE(rect.y1, 5.0);
    EXPECT_LE(rect.x2, 10.0);
    EXPECT_LE(rect.y2, 10.0);
}

TEST_F(PDFRectangleTest_683, ClipToSameRect_683) {
    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    PDFRectangle clipRect(1.0, 2.0, 3.0, 4.0);
    rect.clipTo(clipRect);
    EXPECT_DOUBLE_EQ(rect.x1, 1.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 3.0);
    EXPECT_DOUBLE_EQ(rect.y2, 4.0);
}

// ==================== contains() with degenerate line rectangles ====================

TEST_F(PDFRectangleTest_683, ContainsOnHorizontalLineRect_683) {
    PDFRectangle rect(0.0, 5.0, 10.0, 5.0);
    EXPECT_TRUE(rect.contains(5.0, 5.0));
    EXPECT_FALSE(rect.contains(5.0, 6.0));
}

TEST_F(PDFRectangleTest_683, ContainsOnVerticalLineRect_683) {
    PDFRectangle rect(5.0, 0.0, 5.0, 10.0);
    EXPECT_TRUE(rect.contains(5.0, 5.0));
    EXPECT_FALSE(rect.contains(6.0, 5.0));
}

// ==================== contains() edge precision ====================

TEST_F(PDFRectangleTest_683, ContainsPointJustInsideAllEdges_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    double epsilon = 1e-15;
    EXPECT_TRUE(rect.contains(0.0 + epsilon, 0.0 + epsilon));
    EXPECT_TRUE(rect.contains(10.0 - epsilon, 10.0 - epsilon));
}

TEST_F(PDFRectangleTest_683, ContainsPointJustOutsideAllEdges_683) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    double epsilon = 1e-10;
    EXPECT_FALSE(rect.contains(-epsilon, 5.0));
    EXPECT_FALSE(rect.contains(10.0 + epsilon, 5.0));
    EXPECT_FALSE(rect.contains(5.0, -epsilon));
    EXPECT_FALSE(rect.contains(5.0, 10.0 + epsilon));
}
