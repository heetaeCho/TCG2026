#include <gtest/gtest.h>
#include <poppler-rectangle.h>  // Path to your header file

// Test fixture for poppler::rectangle
class RectangleTest_1008 : public ::testing::Test {
protected:
    // Helper function to create a rectangle
    template <typename T>
    poppler::rectangle<T> create_rectangle(T x, T y, T width, T height) {
        return poppler::rectangle<T>(x, y, width, height);
    }
};

// Test for is_empty when the rectangle has zero width and height
TEST_F(RectangleTest_1008, IsEmptyWhenZeroSize_1008) {
    // Create an empty rectangle (x1 == x2 && y1 == y2)
    poppler::rectangle<int> rect(0, 0, 0, 0);

    // Verify the rectangle is considered empty
    EXPECT_TRUE(rect.is_empty());
}

// Test for is_empty when the rectangle has non-zero width and height
TEST_F(RectangleTest_1008, IsNotEmptyWhenNonZeroSize_1008) {
    // Create a non-empty rectangle
    poppler::rectangle<int> rect(0, 0, 10, 10);

    // Verify the rectangle is not empty
    EXPECT_FALSE(rect.is_empty());
}

// Test the rectangle constructor for proper initialization (non-empty rectangle)
TEST_F(RectangleTest_1008, ConstructorInitializesCorrectly_1008) {
    // Create a rectangle with specific values
    poppler::rectangle<int> rect(5, 10, 15, 20);

    // Verify the rectangle's properties
    EXPECT_EQ(rect.x(), 5);
    EXPECT_EQ(rect.y(), 10);
    EXPECT_EQ(rect.width(), 15);
    EXPECT_EQ(rect.height(), 20);
}

// Test setting left value
TEST_F(RectangleTest_1008, SetLeftValue_1008) {
    poppler::rectangle<int> rect(0, 0, 10, 10);
    rect.set_left(5);
    EXPECT_EQ(rect.left(), 5);
}

// Test setting top value
TEST_F(RectangleTest_1008, SetTopValue_1008) {
    poppler::rectangle<int> rect(0, 0, 10, 10);
    rect.set_top(5);
    EXPECT_EQ(rect.top(), 5);
}

// Test setting right value
TEST_F(RectangleTest_1008, SetRightValue_1008) {
    poppler::rectangle<int> rect(0, 0, 10, 10);
    rect.set_right(15);
    EXPECT_EQ(rect.right(), 15);
}

// Test setting bottom value
TEST_F(RectangleTest_1008, SetBottomValue_1008) {
    poppler::rectangle<int> rect(0, 0, 10, 10);
    rect.set_bottom(15);
    EXPECT_EQ(rect.bottom(), 15);
}

// Test exceptional case: Ensure rectangle's width and height are not negative (boundary condition)
TEST_F(RectangleTest_1008, NegativeWidthHeightThrowsException_1008) {
    // Assuming that negative width/height is not allowed and should throw
    EXPECT_THROW(poppler::rectangle<int>(0, 0, -10, 10), std::invalid_argument);
    EXPECT_THROW(poppler::rectangle<int>(0, 0, 10, -10), std::invalid_argument);
}