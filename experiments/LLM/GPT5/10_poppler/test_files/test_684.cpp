#include <gtest/gtest.h>
#include "./TestProjects/poppler/poppler/PDFRectangle.h"

class PDFRectangleTest_684 : public ::testing::Test {
protected:
    PDFRectangle rect1;
    PDFRectangle rect2;

    // Default constructor test
    PDFRectangleTest_684() : rect1(), rect2(1.0, 1.0, 2.0, 2.0) {}
};

// Test for the default constructor and initial values (rect1 should be (0, 0, 0, 0))
TEST_F(PDFRectangleTest_684, DefaultConstructor_684) {
    EXPECT_EQ(rect1.x1, 0.);
    EXPECT_EQ(rect1.y1, 0.);
    EXPECT_EQ(rect1.x2, 0.);
    EXPECT_EQ(rect1.y2, 0.);
}

// Test for parameterized constructor
TEST_F(PDFRectangleTest_684, ParameterizedConstructor_684) {
    EXPECT_EQ(rect2.x1, 1.0);
    EXPECT_EQ(rect2.y1, 1.0);
    EXPECT_EQ(rect2.x2, 2.0);
    EXPECT_EQ(rect2.y2, 2.0);
}

// Test for the equality operator (operator==)
TEST_F(PDFRectangleTest_684, EqualityOperator_684) {
    PDFRectangle rect3(1.0, 1.0, 2.0, 2.0);
    PDFRectangle rect4(1.0, 1.0, 2.0, 2.0);
    PDFRectangle rect5(0.0, 0.0, 1.0, 1.0);

    EXPECT_TRUE(rect3 == rect4); // Same values
    EXPECT_FALSE(rect3 == rect5); // Different values
}

// Test for the isValid() method
TEST_F(PDFRectangleTest_684, IsValid_684) {
    PDFRectangle validRect(0.0, 0.0, 1.0, 1.0);
    PDFRectangle invalidRect(0.0, 0.0, 0.0, 0.0); // Empty rectangle

    EXPECT_TRUE(validRect.isValid());
    EXPECT_FALSE(invalidRect.isValid());
}

// Test for the isEmpty() method
TEST_F(PDFRectangleTest_684, IsEmpty_684) {
    PDFRectangle emptyRect(0.0, 0.0, 0.0, 0.0);
    PDFRectangle nonEmptyRect(0.0, 0.0, 1.0, 1.0);

    EXPECT_TRUE(emptyRect.isEmpty());
    EXPECT_FALSE(nonEmptyRect.isEmpty());
}

// Test for the contains() method
TEST_F(PDFRectangleTest_684, Contains_684) {
    PDFRectangle rect(0.0, 0.0, 2.0, 2.0);

    // Test for points inside and outside the rectangle
    EXPECT_TRUE(rect.contains(1.0, 1.0)); // Inside
    EXPECT_FALSE(rect.contains(3.0, 3.0)); // Outside
}

// Test for the clipTo() method
TEST_F(PDFRectangleTest_684, ClipTo_684) {
    PDFRectangle rect(0.0, 0.0, 4.0, 4.0);
    PDFRectangle clipRect(2.0, 2.0, 5.0, 5.0);

    rect.clipTo(clipRect);
    EXPECT_EQ(rect.x1, 2.0);
    EXPECT_EQ(rect.y1, 2.0);
    EXPECT_EQ(rect.x2, 4.0);
    EXPECT_EQ(rect.y2, 4.0);
}