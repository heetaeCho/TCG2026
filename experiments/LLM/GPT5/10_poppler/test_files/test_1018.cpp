#include "gtest/gtest.h"
#include "./TestProjects/poppler/cpp/poppler-rectangle.h"

namespace poppler {
    // Test fixture for rectangle
    class RectangleTest_1018 : public ::testing::Test {
    protected:
        rectangle<int> rect;

        // You can initialize rect in the constructor or in SetUp
        void SetUp() override {
            // Initialize with a sample rectangle
            rect = rectangle<int>(0, 0, 10, 20);
        }
    };

    // Test normal operation of set_top
    TEST_F(RectangleTest_1018, SetTop_UpdatesY1_1018) {
        rect.set_top(15);
        EXPECT_EQ(rect.top(), 15);
    }

    // Test boundary conditions of set_top (handling edge cases like 0 or negative values)
    TEST_F(RectangleTest_1018, SetTop_NegativeValue_1018) {
        rect.set_top(-10);
        EXPECT_EQ(rect.top(), -10);
    }

    TEST_F(RectangleTest_1018, SetTop_ZeroValue_1018) {
        rect.set_top(0);
        EXPECT_EQ(rect.top(), 0);
    }

    // Exceptional case: Check for interaction with other attributes after setting the top
    TEST_F(RectangleTest_1018, SetTop_InteractionWithOtherAttributes_1018) {
        rect.set_top(10);
        EXPECT_EQ(rect.y(), 10);  // Ensure that top is reflected in the y position
        EXPECT_EQ(rect.height(), 20); // Ensure height is unchanged
    }

    // Test for the rectangle's constructor, normal operation
    TEST_F(RectangleTest_1018, RectangleConstructor_ValidValues_1018) {
        rectangle<int> r(0, 0, 15, 25);
        EXPECT_EQ(r.x(), 0);
        EXPECT_EQ(r.y(), 0);
        EXPECT_EQ(r.width(), 15);
        EXPECT_EQ(r.height(), 25);
    }

    // Boundary case: Test when width and height are 0
    TEST_F(RectangleTest_1018, RectangleConstructor_ZeroWidthHeight_1018) {
        rectangle<int> r(0, 0, 0, 0);
        EXPECT_EQ(r.width(), 0);
        EXPECT_EQ(r.height(), 0);
        EXPECT_TRUE(r.is_empty());
    }

    // Boundary case: Test when width and height are negative
    TEST_F(RectangleTest_1018, RectangleConstructor_NegativeWidthHeight_1018) {
        rectangle<int> r(0, 0, -5, -10);
        EXPECT_EQ(r.width(), -5);
        EXPECT_EQ(r.height(), -10);
        EXPECT_TRUE(r.is_empty());
    }

    // Exceptional case: Interaction between x1, y1, x2, y2 after set_top is called
    TEST_F(RectangleTest_1018, SetTop_UpdatesOtherCoordinates_1018) {
        rect.set_top(15);
        EXPECT_EQ(rect.left(), 0); // Ensure left remains unaffected
        EXPECT_EQ(rect.right(), 10); // Ensure right remains unaffected
        EXPECT_EQ(rect.bottom(), 5); // Expect bottom to be updated based on set_top
    }

    // Test for is_empty() with non-empty rectangle
    TEST_F(RectangleTest_1018, IsEmpty_False_1018) {
        EXPECT_FALSE(rect.is_empty());
    }

    // Test for is_empty() with empty rectangle
    TEST_F(RectangleTest_1018, IsEmpty_True_1018) {
        rectangle<int> empty_rect(0, 0, 0, 0);
        EXPECT_TRUE(empty_rect.is_empty());
    }
}