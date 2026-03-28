#include <gtest/gtest.h>
#include "poppler-rectangle.h"

// Test for normal operation of `top()`
TEST_F(RectangleTest_1014, TopReturnsCorrectValue_1014) {
    // Test normal operation for the `top()` function of the rectangle class.
    poppler::rectangle<int> rect(0, 10, 5, 5); // x=0, y=10, width=5, height=5
    EXPECT_EQ(rect.top(), 10);
}

// Test for boundary condition: rectangle with zero height
TEST_F(RectangleTest_1014, TopReturnsCorrectValueForZeroHeight_1014) {
    // Test boundary condition when the rectangle has zero height.
    poppler::rectangle<int> rect(0, 10, 5, 0); // x=0, y=10, width=5, height=0
    EXPECT_EQ(rect.top(), 10);
}

// Test for boundary condition: rectangle with zero width
TEST_F(RectangleTest_1014, TopReturnsCorrectValueForZeroWidth_1014) {
    // Test boundary condition when the rectangle has zero width.
    poppler::rectangle<int> rect(0, 10, 0, 5); // x=0, y=10, width=0, height=5
    EXPECT_EQ(rect.top(), 10);
}

// Test for boundary condition: rectangle with negative y-coordinate
TEST_F(RectangleTest_1014, TopReturnsCorrectValueForNegativeY_1014) {
    // Test boundary condition when the rectangle's top left y-coordinate is negative.
    poppler::rectangle<int> rect(0, -10, 5, 5); // x=0, y=-10, width=5, height=5
    EXPECT_EQ(rect.top(), -10);
}

// Test for exceptional/error case: rectangle with default constructor
TEST_F(RectangleTest_1014, TopReturnsZeroForDefaultRectangle_1014) {
    // Test for an uninitialized rectangle created with the default constructor.
    poppler::rectangle<int> rect;
    EXPECT_EQ(rect.top(), 0);
}