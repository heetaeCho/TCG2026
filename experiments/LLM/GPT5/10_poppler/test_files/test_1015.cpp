#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-rectangle.h"  // Adjust the path to match your project structure

// Mock dependencies if necessary (for external collaborators)
class MockRectangleHandler {
public:
    MOCK_METHOD(void, onRectangleCreated, (const poppler::rectangle<int>&), ());
};

namespace poppler {

// Test cases for the rectangle class
TEST_F(RectangleTest_1015, DefaultConstructor_1015) {
    rectangle<int> rect;
    EXPECT_EQ(rect.x(), 0);
    EXPECT_EQ(rect.y(), 0);
    EXPECT_EQ(rect.width(), 0);
    EXPECT_EQ(rect.height(), 0);
}

TEST_F(RectangleTest_1015, ParameterizedConstructor_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    EXPECT_EQ(rect.x(), 10);
    EXPECT_EQ(rect.y(), 20);
    EXPECT_EQ(rect.width(), 30);
    EXPECT_EQ(rect.height(), 40);
}

TEST_F(RectangleTest_1015, RightMethod_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    EXPECT_EQ(rect.right(), 40);
}

TEST_F(RectangleTest_1015, IsEmpty_True_1015) {
    rectangle<int> rect;
    EXPECT_TRUE(rect.is_empty());
}

TEST_F(RectangleTest_1015, IsEmpty_False_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    EXPECT_FALSE(rect.is_empty());
}

TEST_F(RectangleTest_1015, SetRightMethod_1015) {
    rectangle<int> rect(10, 20, 30, 40);
    rect.set_right(50);
    EXPECT_EQ(rect.right(), 50);
}

TEST_F(RectangleTest_1015, BoundaryConditions_1015) {
    rectangle<int> rect(0, 0, 0, 0);
    EXPECT_EQ(rect.x(), 0);
    EXPECT_EQ(rect.y(), 0);
    EXPECT_EQ(rect.width(), 0);
    EXPECT_EQ(rect.height(), 0);
    
    rect.set_right(100);
    EXPECT_EQ(rect.right(), 100);
}

TEST_F(RectangleTest_1015, ExceptionalCase_NegativeWidth_1015) {
    // If a rectangle has a negative width, it should handle it gracefully (assuming a default implementation)
    rectangle<int> rect(10, 20, -30, 40);
    EXPECT_EQ(rect.width(), 0);  // Assume it normalizes to zero width
}

TEST_F(RectangleTest_1015, MockExternalInteraction_1015) {
    MockRectangleHandler mockHandler;
    rectangle<int> rect(10, 20, 30, 40);
    
    EXPECT_CALL(mockHandler, onRectangleCreated(testing::_)).Times(1);
    
    // Simulate the external interaction with the rectangle
    mockHandler.onRectangleCreated(rect);
}

} // namespace poppler