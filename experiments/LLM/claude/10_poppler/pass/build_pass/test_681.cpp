#include <gtest/gtest.h>
#include "PDFRectangle.h"

// Test fixture for PDFRectangle tests
class PDFRectangleTest_681 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== isValid() tests ====================

TEST_F(PDFRectangleTest_681, DefaultConstructedRectangleIsNotValid_681) {
    PDFRectangle rect;
    EXPECT_FALSE(rect.isValid());
}

TEST_F(PDFRectangleTest_681, AllZerosIsNotValid_681) {
    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);
    EXPECT_FALSE(rect.isValid());
}

TEST_F(PDFRectangleTest_681, NonZeroX1IsValid_681) {
    PDFRectangle rect(1.0, 0.0, 0.0, 0.0);
    EXPECT_TRUE(rect.isValid());
}

TEST_F(PDFRectangleTest_681, NonZeroY1IsValid_681) {
    PDFRectangle rect(0.0, 1.0, 0.0, 0.0);
    EXPECT_TRUE(rect.isValid());
}

TEST_F(PDFRectangleTest_681, NonZeroX2IsValid_681) {
    PDFRectangle rect(0.0, 0.0, 1.0, 0.0);
    EXPECT_TRUE(rect.isValid());
}

TEST_F(PDFRectangleTest_681, NonZeroY2IsValid_681) {
    PDFRectangle rect(0.0, 0.0, 0.0, 1.0);
    EXPECT_TRUE(rect.isValid());
}

TEST_F(PDFRectangleTest_681, AllNonZeroIsValid_681) {
    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(rect.isValid());
}

TEST_F(PDFRectangleTest_681, NegativeValuesAreValid_681) {
    PDFRectangle rect(-1.0, -2.0, -3.0, -4.0);
    EXPECT_TRUE(rect.isValid());
}

TEST_F(PDFRectangleTest_681, VerySmallNonZeroValueIsValid_681) {
    PDFRectangle rect(0.0, 0.0, 0.0, 1e-300);
    EXPECT_TRUE(rect.isValid());
}

// ==================== isEmpty() tests ====================

TEST_F(PDFRectangleTest_681, DefaultConstructedRectangleIsEmpty_681) {
    PDFRectangle rect;
    EXPECT_TRUE(rect.isEmpty());
}

TEST_F(PDFRectangleTest_681, ZeroWidthRectangleIsEmpty_681) {
    PDFRectangle rect(5.0, 0.0, 5.0, 10.0);
    EXPECT_TRUE(rect.isEmpty());
}

TEST_F(PDFRectangleTest_681, ZeroHeightRectangleIsEmpty_681) {
    PDFRectangle rect(0.0, 5.0, 10.0, 5.0);
    EXPECT_TRUE(rect.isEmpty());
}

TEST_F(PDFRectangleTest_681, NormalRectangleIsNotEmpty_681) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.isEmpty());
}

TEST_F(PDFRectangleTest_681, InvertedRectangleIsNotEmpty_681) {
    // x1 > x2 and y1 > y2 - still has area
    PDFRectangle rect(10.0, 10.0, 0.0, 0.0);
    EXPECT_FALSE(rect.isEmpty());
}

// ==================== contains() tests ====================

TEST_F(PDFRectangleTest_681, ContainsPointInside_681) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(5.0, 5.0));
}

TEST_F(PDFRectangleTest_681, ContainsPointOnBoundary_681) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(0.0, 0.0));
    EXPECT_TRUE(rect.contains(10.0, 10.0));
    EXPECT_TRUE(rect.contains(0.0, 10.0));
    EXPECT_TRUE(rect.contains(10.0, 0.0));
}

TEST_F(PDFRectangleTest_681, DoesNotContainPointOutside_681) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(rect.contains(-1.0, 5.0));
    EXPECT_FALSE(rect.contains(11.0, 5.0));
    EXPECT_FALSE(rect.contains(5.0, -1.0));
    EXPECT_FALSE(rect.contains(5.0, 11.0));
}

TEST_F(PDFRectangleTest_681, ContainsWithNegativeCoordinates_681) {
    PDFRectangle rect(-10.0, -10.0, 10.0, 10.0);
    EXPECT_TRUE(rect.contains(0.0, 0.0));
    EXPECT_TRUE(rect.contains(-10.0, -10.0));
    EXPECT_FALSE(rect.contains(-11.0, 0.0));
}

// ==================== operator==() tests ====================

TEST_F(PDFRectangleTest_681, EqualRectangles_681) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_681, DefaultRectanglesAreEqual_681) {
    PDFRectangle rect1;
    PDFRectangle rect2;
    EXPECT_TRUE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_681, DifferentX1NotEqual_681) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.5, 2.0, 3.0, 4.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_681, DifferentY1NotEqual_681) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.5, 3.0, 4.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_681, DifferentX2NotEqual_681) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.5, 4.0);
    EXPECT_FALSE(rect1 == rect2);
}

TEST_F(PDFRectangleTest_681, DifferentY2NotEqual_681) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.0, 4.5);
    EXPECT_FALSE(rect1 == rect2);
}

// ==================== Constructor tests ====================

TEST_F(PDFRectangleTest_681, DefaultConstructorSetsAllZeros_681) {
    PDFRectangle rect;
    EXPECT_DOUBLE_EQ(rect.x1, 0.0);
    EXPECT_DOUBLE_EQ(rect.y1, 0.0);
    EXPECT_DOUBLE_EQ(rect.x2, 0.0);
    EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}

TEST_F(PDFRectangleTest_681, ParameterizedConstructorSetsValues_681) {
    PDFRectangle rect(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(rect.x1, 1.5);
    EXPECT_DOUBLE_EQ(rect.y1, 2.5);
    EXPECT_DOUBLE_EQ(rect.x2, 3.5);
    EXPECT_DOUBLE_EQ(rect.y2, 4.5);
}

// ==================== clipTo() tests ====================

TEST_F(PDFRectangleTest_681, ClipToSmallerRectangle_681) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    PDFRectangle clipRect(2.0, 2.0, 8.0, 8.0);
    rect.clipTo(clipRect);
    EXPECT_DOUBLE_EQ(rect.x1, 2.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 8.0);
    EXPECT_DOUBLE_EQ(rect.y2, 8.0);
}

TEST_F(PDFRectangleTest_681, ClipToLargerRectangleNoChange_681) {
    PDFRectangle rect(2.0, 2.0, 8.0, 8.0);
    PDFRectangle clipRect(0.0, 0.0, 10.0, 10.0);
    rect.clipTo(clipRect);
    EXPECT_DOUBLE_EQ(rect.x1, 2.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 8.0);
    EXPECT_DOUBLE_EQ(rect.y2, 8.0);
}

TEST_F(PDFRectangleTest_681, ClipToPartialOverlap_681) {
    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    PDFRectangle clipRect(5.0, 5.0, 15.0, 15.0);
    rect.clipTo(clipRect);
    EXPECT_DOUBLE_EQ(rect.x1, 5.0);
    EXPECT_DOUBLE_EQ(rect.y1, 5.0);
    EXPECT_DOUBLE_EQ(rect.x2, 10.0);
    EXPECT_DOUBLE_EQ(rect.y2, 10.0);
}

TEST_F(PDFRectangleTest_681, ClipToSameRectangle_681) {
    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    PDFRectangle clipRect(1.0, 2.0, 3.0, 4.0);
    rect.clipTo(clipRect);
    EXPECT_DOUBLE_EQ(rect.x1, 1.0);
    EXPECT_DOUBLE_EQ(rect.y1, 2.0);
    EXPECT_DOUBLE_EQ(rect.x2, 3.0);
    EXPECT_DOUBLE_EQ(rect.y2, 4.0);
}

// ==================== Boundary / edge case tests ====================

TEST_F(PDFRectangleTest_681, IsValidWithOnlyOneNonZeroField_681) {
    PDFRectangle r1(0.0001, 0.0, 0.0, 0.0);
    EXPECT_TRUE(r1.isValid());
}

TEST_F(PDFRectangleTest_681, ContainsOnEdgeOfRectangle_681) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    EXPECT_TRUE(rect.contains(50.0, 0.0));
    EXPECT_TRUE(rect.contains(50.0, 100.0));
    EXPECT_TRUE(rect.contains(0.0, 50.0));
    EXPECT_TRUE(rect.contains(100.0, 50.0));
}

TEST_F(PDFRectangleTest_681, PointRectangleContainsOnlyThatPoint_681) {
    PDFRectangle rect(5.0, 5.0, 5.0, 5.0);
    EXPECT_TRUE(rect.contains(5.0, 5.0));
    EXPECT_FALSE(rect.contains(5.1, 5.0));
    EXPECT_FALSE(rect.contains(5.0, 5.1));
}

TEST_F(PDFRectangleTest_681, LargeCoordinateRectangle_681) {
    PDFRectangle rect(1e10, 1e10, 1e15, 1e15);
    EXPECT_TRUE(rect.isValid());
    EXPECT_FALSE(rect.isEmpty());
    EXPECT_TRUE(rect.contains(1e12, 1e12));
}
