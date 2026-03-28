#include <gtest/gtest.h>
#include <poppler-rectangle.h>  // Include the header file for the poppler::rectangle class

namespace poppler {
    // Mock test class for rectangle template specialization
    typedef rectangle<int> IntRectangle;
}

// Test fixture for rectangle class
class RectangleTest_1016 : public ::testing::Test {
protected:
    // Test fixture to create common objects for tests
    poppler::IntRectangle rect1{0, 0, 10, 20}; // Rectangle with width 10, height 20
    poppler::IntRectangle rect2{5, 5, 15, 25}; // Rectangle with width 15, height 25
};

// Test for normal operation of `bottom()`
TEST_F(RectangleTest_1016, BottomTest_1016) {
    // Expecting bottom() to return the correct value based on the given rectangle (y2)
    EXPECT_EQ(rect1.bottom(), 20); // y2 = 0 + 20
    EXPECT_EQ(rect2.bottom(), 30); // y2 = 5 + 25
}

// Test for boundary condition when the rectangle has 0 height
TEST_F(RectangleTest_1016, BottomTestZeroHeight_1016) {
    poppler::IntRectangle rect3{0, 0, 10, 0}; // Rectangle with zero height
    EXPECT_EQ(rect3.bottom(), 0); // y2 = 0 + 0
}

// Test for boundary condition when the rectangle has 0 width and height
TEST_F(RectangleTest_1016, BottomTestZeroWidthHeight_1016) {
    poppler::IntRectangle rect4{0, 0, 0, 0}; // Rectangle with zero width and height
    EXPECT_EQ(rect4.bottom(), 0); // y2 = 0 + 0
}

// Test for exceptional case when rectangle is empty (by checking the is_empty() function if it's part of the class)
TEST_F(RectangleTest_1016, EmptyRectangleTest_1016) {
    poppler::IntRectangle rect5{0, 0, 0, 0}; // Empty rectangle with no width/height
    EXPECT_TRUE(rect5.is_empty()); // Check if the rectangle is empty
    EXPECT_EQ(rect5.bottom(), 0); // y2 should be 0 in the empty case
}