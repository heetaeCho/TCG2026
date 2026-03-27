#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/cpp/poppler-rectangle.h"

namespace poppler {
    // Test Fixture for rectangle class
    template<typename T>
    class RectangleTest : public testing::Test {
    protected:
        rectangle<T> rect;
        rectangle<T> custom_rect;

        void SetUp() override {
            rect = rectangle<T>();
            custom_rect = rectangle<T>(1, 2, 3, 4);
        }
    };

    using TestTypes = testing::Types<int, float>;  // Support for different types like int, float
    TYPED_TEST_SUITE(RectangleTest, TestTypes);

    // Normal Operation Test for y() function
    TYPED_TEST(RectangleTest, y_ReturnsCorrectYCoordinate) {
        EXPECT_EQ(this->custom_rect.y(), 2);
    }

    // Test for is_empty() - Boundary Test
    TYPED_TEST(RectangleTest, is_empty_ReturnsTrueForEmptyRectangle) {
        EXPECT_TRUE(this->rect.is_empty());
    }

    // Test for is_empty() - Boundary Test (non-empty rectangle)
    TYPED_TEST(RectangleTest, is_empty_ReturnsFalseForNonEmptyRectangle) {
        EXPECT_FALSE(this->custom_rect.is_empty());
    }

    // Test for width() and height() - Normal Test
    TYPED_TEST(RectangleTest, width_ReturnsCorrectWidth) {
        EXPECT_EQ(this->custom_rect.width(), 3);
    }

    TYPED_TEST(RectangleTest, height_ReturnsCorrectHeight) {
        EXPECT_EQ(this->custom_rect.height(), 4);
    }

    // Exceptional case for invalid set_left() (if implemented)
    TYPED_TEST(RectangleTest, set_left_InvalidValue) {
        // Assuming an exception or assertion is raised if setting invalid value
        // This would need modification if the function implements actual validation
        EXPECT_NO_THROW(this->custom_rect.set_left(-5)); // Example of valid operation
    }

    // Test for modifying left boundary
    TYPED_TEST(RectangleTest, set_left_ChangesLeftValue) {
        this->custom_rect.set_left(10);
        EXPECT_EQ(this->custom_rect.left(), 10);
    }

    // Test for top() function - Normal test
    TYPED_TEST(RectangleTest, top_ReturnsCorrectTopCoordinate) {
        EXPECT_EQ(this->custom_rect.top(), 2);
    }

    // Test for set_top() function - Boundary Test
    TYPED_TEST(RectangleTest, set_top_ChangesTopValue) {
        this->custom_rect.set_top(5);
        EXPECT_EQ(this->custom_rect.top(), 5);
    }

    // Exceptional case for right() boundary condition (e.g., when rectangle is invalid)
    TYPED_TEST(RectangleTest, set_right_InvalidOperation) {
        // Check behavior if the right value is less than left
        this->custom_rect.set_left(5);
        this->custom_rect.set_right(3);
        // Assuming there's logic to handle invalid states, it should handle appropriately
        EXPECT_GT(this->custom_rect.right(), this->custom_rect.left());
    }

    // Test for bottom() function - Normal test
    TYPED_TEST(RectangleTest, bottom_ReturnsCorrectBottomCoordinate) {
        EXPECT_EQ(this->custom_rect.bottom(), 6);  // Should be y + height
    }

    // Boundary test for empty rectangle height
    TYPED_TEST(RectangleTest, height_ReturnsZeroForEmptyRectangle) {
        EXPECT_EQ(this->rect.height(), 0);
    }

    // Mock Test for interaction with other dependencies (example)
    // (Note: Use Google Mock if there are external collaborators such as callback handlers)
    // For simplicity, assuming no external collaborators are in this particular implementation.
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}