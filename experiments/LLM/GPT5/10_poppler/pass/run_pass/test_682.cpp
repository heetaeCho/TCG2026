#include <gtest/gtest.h>
#include "PDFRectangle.h"

class PDFRectangleTest_682 : public ::testing::Test {
protected:
    // Setup any common test data or state here
};

// Test normal operation: check if isEmpty() works correctly for a rectangle with equal x1, x2 and y1, y2
TEST_F(PDFRectangleTest_682, isEmpty_ReturnsTrueWhenRectangleIsEmpty_682) {
    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);
    EXPECT_TRUE(rect.isEmpty());
}

// Test normal operation: check if isEmpty() works correctly for a rectangle with non-equal x1, x2 or y1, y2
TEST_F(PDFRectangleTest_682, isEmpty_ReturnsFalseWhenRectangleIsNotEmpty_682) {
    PDFRectangle rect(0.0, 0.0, 1.0, 1.0);
    EXPECT_FALSE(rect.isEmpty());
}

// Test boundary condition: Check if isEmpty() handles edge case where coordinates are the same
TEST_F(PDFRectangleTest_682, isEmpty_ReturnsTrueForZeroSizedRectangle_682) {
    PDFRectangle rect(1.0, 1.0, 1.0, 1.0);
    EXPECT_TRUE(rect.isEmpty());
}

// Test normal operation: check if isValid() works correctly for a valid rectangle
TEST_F(PDFRectangleTest_682, isValid_ReturnsTrueForValidRectangle_682) {
    PDFRectangle rect(0.0, 0.0, 1.0, 1.0);
    EXPECT_TRUE(rect.isValid());
}

// Test boundary condition: Check if isValid() works correctly for a rectangle with invalid (zero area) values
TEST_F(PDFRectangleTest_682, isValid_ReturnsTrueForZeroAreaRectangle_682) {
    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);
    EXPECT_FALSE(rect.isValid());
}

// Test normal operation: check if contains() works correctly for a point inside the rectangle
TEST_F(PDFRectangleTest_682, contains_ReturnsTrueWhenPointIsInsideRectangle_682) {
    PDFRectangle rect(0.0, 0.0, 2.0, 2.0);
    EXPECT_TRUE(rect.contains(1.0, 1.0));  // Point inside
}

// Test exceptional case: Check if contains() works correctly for a point outside the rectangle
TEST_F(PDFRectangleTest_682, contains_ReturnsFalseWhenPointIsOutsideRectangle_682) {
    PDFRectangle rect(0.0, 0.0, 2.0, 2.0);
    EXPECT_FALSE(rect.contains(3.0, 3.0));  // Point outside
}

// Test boundary condition: Check if contains() works correctly for a point on the boundary of the rectangle
TEST_F(PDFRectangleTest_682, contains_ReturnsTrueForPointOnBoundary_682) {
    PDFRectangle rect(0.0, 0.0, 2.0, 2.0);
    EXPECT_TRUE(rect.contains(0.0, 1.0));  // Point on the boundary
}

// Test normal operation: check if equality operator works for two identical rectangles
TEST_F(PDFRectangleTest_682, operatorEquality_ReturnsTrueForIdenticalRectangles_682) {
    PDFRectangle rect1(0.0, 0.0, 2.0, 2.0);
    PDFRectangle rect2(0.0, 0.0, 2.0, 2.0);
    EXPECT_TRUE(rect1 == rect2);
}

// Test exceptional case: check if equality operator works for two non-identical rectangles
TEST_F(PDFRectangleTest_682, operatorEquality_ReturnsFalseForDifferentRectangles_682) {
    PDFRectangle rect1(0.0, 0.0, 2.0, 2.0);
    PDFRectangle rect2(1.0, 1.0, 3.0, 3.0);
    EXPECT_FALSE(rect1 == rect2);
}

// Test boundary condition: Check if clipTo() modifies the rectangle to fit within another rectangle
TEST_F(PDFRectangleTest_682, clipTo_ModifiesRectangleToFitWithinOther_682) {
    PDFRectangle rect1(0.0, 0.0, 5.0, 5.0);
    PDFRectangle rect2(1.0, 1.0, 3.0, 3.0);
    rect1.clipTo(rect2);  // Clip rect1 to fit within rect2
    EXPECT_TRUE(rect1 == PDFRectangle(1.0, 1.0, 3.0, 3.0));  // Expecting clipped rectangle
}