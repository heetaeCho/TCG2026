#include <gtest/gtest.h>
#include "PDFRectangle.h"

class PDFRectangleTest : public ::testing::Test {
protected:
    // Helper method to create a rectangle
    PDFRectangle createRectangle(double x1, double y1, double x2, double y2) {
        return PDFRectangle(x1, y1, x2, y2);
    }
};

// Test for normal operation of the `contains` method
TEST_F(PDFRectangleTest, ContainsPointWithinRectangle_683) {
    // Arrange
    PDFRectangle rect = createRectangle(0.0, 0.0, 5.0, 5.0);
    
    // Act & Assert
    EXPECT_TRUE(rect.contains(2.0, 2.0)); // Point inside the rectangle
    EXPECT_FALSE(rect.contains(6.0, 6.0)); // Point outside the rectangle
}

// Test for boundary condition where the point is on the edge of the rectangle
TEST_F(PDFRectangleTest, ContainsPointOnEdge_684) {
    // Arrange
    PDFRectangle rect = createRectangle(0.0, 0.0, 5.0, 5.0);

    // Act & Assert
    EXPECT_TRUE(rect.contains(0.0, 0.0));  // Point on bottom-left corner
    EXPECT_TRUE(rect.contains(5.0, 5.0));  // Point on top-right corner
    EXPECT_TRUE(rect.contains(2.5, 0.0));  // Point on bottom edge
    EXPECT_TRUE(rect.contains(0.0, 2.5));  // Point on left edge
    EXPECT_TRUE(rect.contains(5.0, 2.5));  // Point on right edge
    EXPECT_TRUE(rect.contains(2.5, 5.0));  // Point on top edge
}

// Test for boundary condition where the point is just outside the rectangle
TEST_F(PDFRectangleTest, ContainsPointJustOutside_685) {
    // Arrange
    PDFRectangle rect = createRectangle(0.0, 0.0, 5.0, 5.0);
    
    // Act & Assert
    EXPECT_FALSE(rect.contains(-0.1, 0.0)); // Just outside the left edge
    EXPECT_FALSE(rect.contains(5.1, 5.0));  // Just outside the right edge
    EXPECT_FALSE(rect.contains(0.0, -0.1)); // Just outside the bottom edge
    EXPECT_FALSE(rect.contains(0.0, 5.1));  // Just outside the top edge
}

// Test for `isValid` method when the rectangle has valid coordinates
TEST_F(PDFRectangleTest, IsValidRectangle_686) {
    // Arrange
    PDFRectangle rect1 = createRectangle(0.0, 0.0, 5.0, 5.0);
    PDFRectangle rect2 = createRectangle(-2.0, -3.0, 2.0, 3.0);
    
    // Act & Assert
    EXPECT_TRUE(rect1.isValid());
    EXPECT_TRUE(rect2.isValid());
}

// Test for `isEmpty` method when the rectangle has zero area (empty rectangle)
TEST_F(PDFRectangleTest, IsEmptyRectangle_687) {
    // Arrange
    PDFRectangle emptyRect = createRectangle(0.0, 0.0, 0.0, 0.0);
    
    // Act & Assert
    EXPECT_TRUE(emptyRect.isEmpty());
}

// Test for `operator==` method, checking equality of two rectangles
TEST_F(PDFRectangleTest, EqualRectangles_688) {
    // Arrange
    PDFRectangle rect1 = createRectangle(0.0, 0.0, 5.0, 5.0);
    PDFRectangle rect2 = createRectangle(0.0, 0.0, 5.0, 5.0);
    PDFRectangle rect3 = createRectangle(1.0, 1.0, 4.0, 4.0);
    
    // Act & Assert
    EXPECT_TRUE(rect1 == rect2);  // Same coordinates
    EXPECT_FALSE(rect1 == rect3); // Different coordinates
}

// Test for invalid rectangle (where x1 > x2 or y1 > y2)
TEST_F(PDFRectangleTest, InvalidRectangle_689) {
    // Arrange
    PDFRectangle invalidRect1 = createRectangle(5.0, 5.0, 2.0, 2.0);  // x1 > x2
    PDFRectangle invalidRect2 = createRectangle(0.0, 5.0, 5.0, 2.0);  // y1 > y2
    
    // Act & Assert
    EXPECT_FALSE(invalidRect1.isValid());
    EXPECT_FALSE(invalidRect2.isValid());
}

// Test for `clipTo` method when clipping happens (not implemented, test the interface if available)
TEST_F(PDFRectangleTest, ClipRectangle_690) {
    // Arrange
    PDFRectangle rect1 = createRectangle(0.0, 0.0, 5.0, 5.0);
    PDFRectangle rect2 = createRectangle(2.0, 2.0, 6.0, 6.0);
    
    // Act: Perform clipping (mocked or handled based on the interface)
    rect1.clipTo(rect2);  // Assuming the clipTo method modifies rect1 to the intersection of rect1 and rect2
    
    // Assert: After clipping, rect1 should be within the bounds of rect2
    EXPECT_TRUE(rect1.contains(2.0, 2.0));  // Point inside the clipped rectangle
    EXPECT_FALSE(rect1.contains(6.0, 6.0)); // Point outside the clipped rectangle
}