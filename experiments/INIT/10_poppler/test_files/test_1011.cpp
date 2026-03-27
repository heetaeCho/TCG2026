#include <gtest/gtest.h>
#include "./TestProjects/poppler/cpp/poppler-rectangle.h"

// Test fixture for the rectangle class
class RectangleTest_1011 : public ::testing::Test {
protected:
    // Helper function to create a rectangle
    poppler::rectangle<int> createRectangle(int x, int y, int w, int h) {
        return poppler::rectangle<int>(x, y, w, h);
    }
};

// TEST_ID: 1011
TEST_F(RectangleTest_1011, DefaultConstructor_1011) {
    poppler::rectangle<int> rect;
    EXPECT_EQ(rect.width(), 0);  // Width should be 0 by default
    EXPECT_EQ(rect.height(), 0); // Height should be 0 by default
}

// TEST_ID: 1012
TEST_F(RectangleTest_1011, ParameterizedConstructor_1012) {
    poppler::rectangle<int> rect = createRectangle(10, 20, 30, 40);
    EXPECT_EQ(rect.width(), 30);  // Width should be 30
    EXPECT_EQ(rect.height(), 40); // Height should be 40
}

// TEST_ID: 1013
TEST_F(RectangleTest_1011, IsEmpty_Default_1013) {
    poppler::rectangle<int> rect;
    EXPECT_TRUE(rect.is_empty());  // Should be empty by default
}

// TEST_ID: 1014
TEST_F(RectangleTest_1011, IsEmpty_NonEmpty_1014) {
    poppler::rectangle<int> rect = createRectangle(10, 20, 30, 40);
    EXPECT_FALSE(rect.is_empty());  // Should not be empty
}

// TEST_ID: 1015
TEST_F(RectangleTest_1011, SetLeft_1015) {
    poppler::rectangle<int> rect = createRectangle(10, 20, 30, 40);
    rect.set_left(5);
    EXPECT_EQ(rect.left(), 5);  // Left should be updated to 5
}

// TEST_ID: 1016
TEST_F(RectangleTest_1011, SetTop_1016) {
    poppler::rectangle<int> rect = createRectangle(10, 20, 30, 40);
    rect.set_top(15);
    EXPECT_EQ(rect.top(), 15);  // Top should be updated to 15
}

// TEST_ID: 1017
TEST_F(RectangleTest_1011, SetRight_1017) {
    poppler::rectangle<int> rect = createRectangle(10, 20, 30, 40);
    rect.set_right(50);
    EXPECT_EQ(rect.right(), 50);  // Right should be updated to 50
}

// TEST_ID: 1018
TEST_F(RectangleTest_1011, SetBottom_1018) {
    poppler::rectangle<int> rect = createRectangle(10, 20, 30, 40);
    rect.set_bottom(60);
    EXPECT_EQ(rect.bottom(), 60);  // Bottom should be updated to 60
}

// TEST_ID: 1019
TEST_F(RectangleTest_1011, Width_ZeroWidth_1019) {
    poppler::rectangle<int> rect = createRectangle(10, 20, 0, 40);
    EXPECT_EQ(rect.width(), 0);  // Width should be 0
}

// TEST_ID: 1020
TEST_F(RectangleTest_1011, Height_ZeroHeight_1020) {
    poppler::rectangle<int> rect = createRectangle(10, 20, 30, 0);
    EXPECT_EQ(rect.height(), 0);  // Height should be 0
}

// TEST_ID: 1021
TEST_F(RectangleTest_1011, NegativeWidth_1021) {
    poppler::rectangle<int> rect = createRectangle(10, 20, -30, 40);
    EXPECT_EQ(rect.width(), -30);  // Width should be negative
}

// TEST_ID: 1022
TEST_F(RectangleTest_1011, NegativeHeight_1022) {
    poppler::rectangle<int> rect = createRectangle(10, 20, 30, -40);
    EXPECT_EQ(rect.height(), -40);  // Height should be negative
}