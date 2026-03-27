#include <gtest/gtest.h>
#include "./TestProjects/poppler/cpp/poppler-rectangle.h"

// Test the constructor and left() function
TEST_F(RectangleTest_1013, DefaultConstructor_Left_1013) {
    poppler::rectangle<int> rect;
    EXPECT_EQ(rect.left(), 0);  // Default value for x1 is 0
}

TEST_F(RectangleTest_1013, ParameterizedConstructor_Left_1013) {
    poppler::rectangle<int> rect(5, 10, 15, 20);
    EXPECT_EQ(rect.left(), 5);  // x1 should be 5 as per the constructor
}

// Test boundary conditions for left()
TEST_F(RectangleTest_1013, SetLeftValue_Left_1013) {
    poppler::rectangle<int> rect(0, 0, 10, 10);
    rect.set_left(10);
    EXPECT_EQ(rect.left(), 10);  // Verifying that the left() function reflects set_left()
}

TEST_F(RectangleTest_1013, SetLeftNegativeValue_Left_1013) {
    poppler::rectangle<int> rect(0, 0, 10, 10);
    rect.set_left(-10);
    EXPECT_EQ(rect.left(), -10);  // Verifying that left() can handle negative values
}

// Test exceptional/error cases for left()
TEST_F(RectangleTest_1013, SetLeftValueBeyondBoundary_Left_1013) {
    poppler::rectangle<int> rect(0, 0, 10, 10);
    rect.set_left(10000);  // Setting an extremely large value
    EXPECT_EQ(rect.left(), 10000);  // Verifying that set_left() works with large values
}

// Test boundary conditions for rectangle being empty
TEST_F(RectangleTest_1013, RectangleEmptyCondition_1013) {
    poppler::rectangle<int> rect(0, 0, 0, 0);
    EXPECT_TRUE(rect.is_empty());  // A rectangle with zero width and height should be empty
}

TEST_F(RectangleTest_1013, RectangleNonEmptyCondition_1013) {
    poppler::rectangle<int> rect(0, 0, 10, 20);
    EXPECT_FALSE(rect.is_empty());  // A non-zero sized rectangle should not be empty
}

// Test interaction with external collaborators (mock scenario, if needed)
TEST_F(RectangleTest_1013, MockExternalHandler_Left_1013) {
    // This test assumes an external handler (e.g., a callback) is involved in setting/reading left
    // Use Google Mock to simulate this external interaction if needed
}