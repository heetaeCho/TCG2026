#include <gtest/gtest.h>
#include "PDFRectangle.h"

class PDFRectangleTest_2756 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(PDFRectangleTest_2756, DefaultConstructor_2756) {
    PDFRectangle rect;
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}

TEST_F(PDFRectangleTest_2756, ParameterizedConstructor_2756) {
    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(rect.x1, 1.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 3.0);
    EXPECT_DOUBLE_EQ(rect.y2, 4.0);
}

TEST_F(PDFRectangleTest_2756, ConstructorWithNegativeValues_2756) {
    PDFRectangle rect(-5.0, -10.0, -1.0, -2.0);
    EXPECT_DOUBLE_EQ(rect.x1, -5.0);
    EXPECT_DOUBLE_EQ(rect.y1, -10.0);
    EXPECT_DOUBLE_EQ(rect.x2, -1.0);
    EXPECT_DOUBLE_EQ(rect.y2, -2.0);
}

TEST_F(PDFRectangleTest_2756, ConstructorWithZeroValues_2756) {
    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}

TEST_F(PDFRectangleTest_2756, ConstructorWithLargeValues_2756) {
    PDFRectangle rect(1e15, 1e15, 1e16, 1e16);
    EXPECT_DOUBLE_EQ(rect.x1, 1e15);
    EXPECT_DOUBLE_EQ(rect.y1, 1e15);
    EXPECT_DOUBLE_EQ(rect.x2, 1e16);
    EXPECT_DOUBLE_EQ(rect.y2, 1e16);
}

TEST_F(PDFRectangleTest_2756, ConstructorWithFractionalValues_2756) {
    PDFRectangle rect(0.001, 0.002, 0.003, 0.004);
    EXPECT_DOUBLE_EQ(rect.x1, 0.001);
    EXPECT_DOUBLE_EQ(rect.y1, 0.002);
    EXPECT_DOUBLE_EQ(rect.x2, 0.003);
    EXPECT_DOUBLE_EQ(rect.y2, 0.004);
}

// ============================================================
// Equality Operator Tests
// ============================================================

TEST_F(PDFRectangleTest_2756, EqualityOperatorSameValues_2756) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_2756, EqualityOperatorDifferentValues_2756) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(5.0, 6.0, 7.0, 8.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_2756, EqualityOperatorDifferentX1_2756) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.5, 2.0, 3.0, 4.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_2756, EqualityOperatorDifferentY1_2756) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.5, 3.0, 4.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_2756, EqualityOperatorDifferentX2_2756) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.5, 4.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_2756, EqualityOperatorDifferentY2_2756) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.0, 4.5);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_2756, EqualityOperatorDefaultRectangles_2756) {
    PDFRectangle rect1;
    PDFRectangle rect2;
    EXPECT_TRUE(rect1 == rect2);
}

// ============================================================
// isEmpty Tests
// ============================================================

TEST_F(PDFRectangleTest_2756, IsEmptyDefaultConstructor_2756) {
    PDFRectangle rect;
    EXPECT_TRUE(rect.isEmpty());
}

TEST_F(PDFRectangleTest_2756, IsEmptyNonEmptyRect_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.isEmpty());
}

TEST_F(PDFRectangleTest_2756, IsEmptyZeroWidthRect_2756) {
    PDFRectangle rect(5.0, 0.0, 5.0, 10.0);
    // Width is zero - likely considered empty
    EXPECT_TRUE(rect.isEmpty());
}

TEST_F(PDFRectangleTest_2756, IsEmptyZeroHeightRect_2756) {
    PDFRectangle rect(0.0, 5.0, 10.0, 5.0);
    // Height is zero - likely considered empty
    EXPECT_TRUE(rect.isEmpty());
}

TEST_F(PDFRectangleTest_2756, IsEmptyAllZero_2756) {
    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);
    EXPECT_TRUE(rect.isEmpty());
}

// ============================================================
// isValid Tests
// ============================================================

TEST_F(PDFRectangleTest_2756, IsValidNormalRect_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.isValid());
}

TEST_F(PDFRectangleTest_2756, IsValidDefaultRect_2756) {
    PDFRectangle rect;
    // Default rect with all zeros
    // Behavior depends on implementation, but test it
    bool valid = rect.isValid();
    (void)valid; // just ensure it doesn't crash; could be true or false
}

TEST_F(PDFRectangleTest_2756, IsValidInvertedRect_2756) {
    // x1 > x2 and y1 > y2
    PDFRectangle rect(10.0, 10.0, 0.0, 0.0);
    // This might be considered invalid depending on implementation
    bool valid = rect.isValid();
    (void)valid;
}

// ============================================================
// contains Tests
// ============================================================

TEST_F(PDFRectangleTest_2756, ContainsPointInside_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(5.0, 5.0));
}

TEST_F(PDFRectangleTest_2756, ContainsPointOutside_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(15.0, 15.0));
}

TEST_F(PDFRectangleTest_2756, ContainsPointOnLeftEdge_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(0.0, 5.0));
}

TEST_F(PDFRectangleTest_2756, ContainsPointOnRightEdge_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(10.0, 5.0));
}

TEST_F(PDFRectangleTest_2756, ContainsPointOnTopEdge_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(5.0, 10.0));
}

TEST_F(PDFRectangleTest_2756, ContainsPointOnBottomEdge_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(5.0, 0.0));
}

TEST_F(PDFRectangleTest_2756, ContainsCornerPoint_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(0.0, 0.0));
    EXPECT_TRUE(rect.contains(10.0, 10.0));
    EXPECT_TRUE(rect.contains(0.0, 10.0));
    EXPECT_TRUE(rect.contains(10.0, 0.0));
}

TEST_F(PDFRectangleTest_2756, ContainsPointOutsideLeft_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(-1.0, 5.0));
}

TEST_F(PDFRectangleTest_2756, ContainsPointOutsideRight_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(11.0, 5.0));
}

TEST_F(PDFRectangleTest_2756, ContainsPointOutsideTop_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(5.0, 11.0));
}

TEST_F(PDFRectangleTest_2756, ContainsPointOutsideBottom_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(5.0, -1.0));
}

TEST_F(PDFRectangleTest_2756, ContainsWithNegativeRect_2756) {
    PDFRectangle rect(-10.0, -10.0, -1.0, -1.0);
    EXPECT_TRUE(rect.contains(-5.0, -5.0));
    EXPECT_FALSE(rect.contains(0.0, 0.0));
}

// ============================================================
// clipTo Tests
// ============================================================

TEST_F(PDFRectangleTest_2756, ClipToOverlappingRect_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    PDFRectangle clipRect(5.0, 5.0, 15.0, 15.0);
    rect.clipTo(clipRect);
    EXPECT_DOUBLE_EQ(rect.x1, 5.0);
    EXPECT_DOUBLE_EQ(rect.y1, 5.0);
    EXPECT_DOUBLE_EQ(rect.x2, 10.0);
    EXPECT_DOUBLE_EQ(rect.y2, 10.0);
}

TEST_F(PDFRectangleTest_2756, ClipToContainedRect_2756) {
    PDFRectangle rect(2.0, 2.0, 8.0, 8.0);
    PDFRectangle clipRect(0.0, 0.0, 10.0, 10.0);
    rect.clipTo(clipRect);
    // rect is fully inside clipRect, should remain unchanged
    EXPECT_DOUBLE_EQ(rect.x1, 2.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 8.0);
    EXPECT_DOUBLE_EQ(rect.y2, 8.0);
}

TEST_F(PDFRectangleTest_2756, ClipToContainingRect_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    PDFRectangle clipRect(2.0, 2.0, 8.0, 8.0);
    rect.clipTo(clipRect);
    // rect should be clipped to clipRect
    EXPECT_DOUBLE_EQ(rect.x1, 2.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 8.0);
    EXPECT_DOUBLE_EQ(rect.y2, 8.0);
}

TEST_F(PDFRectangleTest_2756, ClipToSameRect_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    PDFRectangle clipRect(0.0, 0.0, 10.0, 10.0);
    rect.clipTo(clipRect);
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 10.0);
    EXPECT_DOUBLE_EQ(rect.y2, 10.0);
}

TEST_F(PDFRectangleTest_2756, ClipToPartialOverlapLeft_2756) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    PDFRectangle clipRect(-5.0, 0.0, 5.0, 10.0);
    rect.clipTo(clipRect);
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 5.0);
    EXPECT_DOUBLE_EQ(rect.y2, 10.0);
}

// ============================================================
// Constexpr Tests
// ============================================================

TEST_F(PDFRectangleTest_2756, ConstexprConstruction_2756) {
    constexpr PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(rect.x1, 1.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 3.0);
    EXPECT_DOUBLE_EQ(rect.y2, 4.0);
}

TEST_F(PDFRectangleTest_2756, ConstexprDefaultConstruction_2756) {
    constexpr PDFRectangle rect;
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}

TEST_F(PDFRectangleTest_2756, ConstexprIsEmpty_2756) {
    constexpr PDFRectangle rect;
    constexpr bool empty = rect.isEmpty();
    EXPECT_TRUE(empty);
}

TEST_F(PDFRectangleTest_2756, ConstexprContains_2756) {
    constexpr PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    constexpr bool inside = rect.contains(5.0, 5.0);
    EXPECT_TRUE(inside);
}

TEST_F(PDFRectangleTest_2756, ConstexprEquality_2756) {
    constexpr PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    constexpr PDFRectangle rect2(1.0, 2.0, 3.0, 4.0);
    constexpr bool eq = (rect1 == rect2);
    EXPECT_TRUE(eq);
}

// ============================================================
// Member field direct access tests
// ============================================================

TEST_F(PDFRectangleTest_2756, DirectFieldModification_2756) {
    PDFRectangle rect;
    rect.x1 = 1.0;
    rect.y1 = 2.0;
    rect.x2 = 3.0;
    rect.y2 = 4.0;
    EXPECT_DOUBLE_EQ(rect.x1, 1.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 3.0);
    EXPECT_DOUBLE_EQ(rect.y2, 4.0);
}

TEST_F(PDFRectangleTest_2756, ContainsAfterFieldModification_2756) {
    PDFRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;
    EXPECT_TRUE(rect.contains(50.0, 50.0));
    EXPECT_FALSE(rect.contains(101.0, 50.0));
}
