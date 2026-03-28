#include <gtest/gtest.h>
#include <stdexcept>
#include "./TestProjects/poppler/cpp/poppler-rectangle.h"

namespace poppler {

class RectangleTest_1017 : public ::testing::Test {
protected:
    rectangle<int> rect;

    // Constructor sets up a rectangle for testing
    RectangleTest_1017() : rect(10, 20, 30, 40) {}
};

TEST_F(RectangleTest_1017, SetLeft_ValidValue) {
    rect.set_left(15);
    // Test the expected behavior after setting left
    EXPECT_EQ(rect.left(), 15);
}

TEST_F(RectangleTest_1017, SetLeft_ZeroValue) {
    rect.set_left(0);
    // Test edge case where left is set to zero
    EXPECT_EQ(rect.left(), 0);
}

TEST_F(RectangleTest_1017, SetLeft_NegativeValue) {
    rect.set_left(-10);
    // Test edge case where left is set to a negative value
    EXPECT_EQ(rect.left(), -10);
}

TEST_F(RectangleTest_1017, RectangleDefaultConstructor) {
    rectangle<int> default_rect;
    // Test default constructor to ensure all values are initialized to zero
    EXPECT_EQ(default_rect.left(), 0);
    EXPECT_EQ(default_rect.top(), 0);
    EXPECT_EQ(default_rect.right(), 0);
    EXPECT_EQ(default_rect.bottom(), 0);
}

TEST_F(RectangleTest_1017, RectangleConstructor_ValidValues) {
    rectangle<int> custom_rect(5, 10, 20, 30);
    // Test constructor with specific values
    EXPECT_EQ(custom_rect.left(), 5);
    EXPECT_EQ(custom_rect.top(), 10);
    EXPECT_EQ(custom_rect.right(), 25);
    EXPECT_EQ(custom_rect.bottom(), 40);
}

TEST_F(RectangleTest_1017, IsEmpty_True) {
    rectangle<int> empty_rect(0, 0, 0, 0);
    // Test is_empty() with a rectangle that has zero area
    EXPECT_TRUE(empty_rect.is_empty());
}

TEST_F(RectangleTest_1017, IsEmpty_False) {
    rectangle<int> non_empty_rect(0, 0, 10, 20);
    // Test is_empty() with a non-empty rectangle
    EXPECT_FALSE(non_empty_rect.is_empty());
}

TEST_F(RectangleTest_1017, SetLeft_OutOfRange) {
    try {
        rect.set_left(-1000);
        // Test that setting a very large negative number should still be valid
        EXPECT_EQ(rect.left(), -1000);
    } catch (const std::exception& e) {
        FAIL() << "Expected valid set_left, but got exception: " << e.what();
    }
}

TEST_F(RectangleTest_1017, SetLeft_InvalidType) {
    // This test checks that invalid types are not allowed
    try {
        rectangle<std::string> str_rect;
        str_rect.set_left("invalid"); // Invalid type assignment
        FAIL() << "Expected exception for invalid type.";
    } catch (const std::invalid_argument& e) {
        EXPECT_EQ(std::string(e.what()), "Invalid type assignment");
    }
}

}  // namespace poppler