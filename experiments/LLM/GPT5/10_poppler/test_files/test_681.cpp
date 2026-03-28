#include <gtest/gtest.h>
#include "PDFRectangle.h"

// Test Fixture for PDFRectangle
class PDFRectangleTest_681 : public ::testing::Test {
protected:
    PDFRectangle rect1;
    PDFRectangle rect2;
    
    PDFRectangleTest_681() : rect1(1.0, 2.0, 3.0, 4.0), rect2(1.0, 2.0, 3.0, 4.0) {}
};

// Test for the default constructor (should create an empty rectangle)
TEST_F(PDFRectangleTest_681, DefaultConstructor_681) {
    PDFRectangle rect;
    EXPECT_FALSE(rect.isValid()) << "Default-constructed rectangle should not be valid";
}

// Test for the constructor with parameters
TEST_F(PDFRectangleTest_681, ParameterizedConstructor_681) {
    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(rect.isValid()) << "Rectangle should be valid with non-zero values";
}

// Test for the isValid method with a valid rectangle
TEST_F(PDFRectangleTest_681, IsValid_ValidRectangle_681) {
    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(rect.isValid()) << "Rectangle should be valid with non-zero values";
}

// Test for the isValid method with an empty rectangle
TEST_F(PDFRectangleTest_681, IsValid_EmptyRectangle_681) {
    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);
    EXPECT_FALSE(rect.isValid()) << "Rectangle should not be valid with all zero values";
}

// Test for the isEmpty method (empty rectangle)
TEST_F(PDFRectangleTest_681, IsEmpty_EmptyRectangle_681) {
    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);
    EXPECT_TRUE(rect.isEmpty()) << "Rectangle with all zero values should be empty";
}

// Test for the isEmpty method (non-empty rectangle)
TEST_F(PDFRectangleTest_681, IsEmpty_NonEmptyRectangle_681) {
    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    EXPECT_FALSE(rect.isEmpty()) << "Rectangle with non-zero values should not be empty";
}

// Test for the contains method (point inside rectangle)
TEST_F(PDFRectangleTest_681, Contains_PointInside_681) {
    PDFRectangle rect(0.0, 0.0, 5.0, 5.0);
    EXPECT_TRUE(rect.contains(2.0, 2.0)) << "Point (2, 2) should be inside the rectangle";
}

// Test for the contains method (point outside rectangle)
TEST_F(PDFRectangleTest_681, Contains_PointOutside_681) {
    PDFRectangle rect(0.0, 0.0, 5.0, 5.0);
    EXPECT_FALSE(rect.contains(6.0, 6.0)) << "Point (6, 6) should be outside the rectangle";
}

// Test for the equality operator (rectangles are equal)
TEST_F(PDFRectangleTest_681, EqualityOperator_EqualRectangles_681) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(1.0, 2.0, 3.0, 4.0);
    EXPECT_TRUE(rect1 == rect2) << "Rectangles with the same coordinates should be equal";
}

// Test for the equality operator (rectangles are not equal)
TEST_F(PDFRectangleTest_681, EqualityOperator_NotEqualRectangles_681) {
    PDFRectangle rect1(1.0, 2.0, 3.0, 4.0);
    PDFRectangle rect2(0.0, 0.0, 5.0, 5.0);
    EXPECT_FALSE(rect1 == rect2) << "Rectangles with different coordinates should not be equal";
}

// Test for the clipTo method (clipping to another rectangle)
TEST_F(PDFRectangleTest_681, ClipTo_Clipping_681) {
    PDFRectangle rect(1.0, 1.0, 5.0, 5.0);
    PDFRectangle clipRect(2.0, 2.0, 4.0, 4.0);
    rect.clipTo(clipRect);
    EXPECT_TRUE(rect.isValid()) << "Clipped rectangle should remain valid";
    EXPECT_TRUE(rect.contains(3.0, 3.0)) << "Clipped rectangle should contain point (3, 3)";
}