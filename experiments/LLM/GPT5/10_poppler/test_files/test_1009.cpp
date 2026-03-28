#include <gtest/gtest.h>
#include "poppler-rectangle.h"

namespace poppler {
    // Mocking the rectangle class for external collaborator verification
    template <typename T>
    class RectangleTest : public ::testing::Test {
    public:
        rectangle<T> rect;

        // Helper function for testing
        void initRectangle(T x, T y, T w, T h) {
            rect = rectangle<T>(x, y, w, h);
        }
    };

    typedef ::testing::Types<int, float> MyTypes;
    TYPED_TEST_SUITE(RectangleTest, MyTypes);

    // TEST_ID 1009: Test for normal operation of the rectangle constructor
    TYPED_TEST(RectangleTest, ConstructorTest_1009) {
        // Arrange
        TypeParam x = 10, y = 20, width = 30, height = 40;
        
        // Act
        this->initRectangle(x, y, width, height);

        // Assert
        EXPECT_EQ(this->rect.x(), x);
        EXPECT_EQ(this->rect.y(), y);
        EXPECT_EQ(this->rect.width(), width);
        EXPECT_EQ(this->rect.height(), height);
    }

    // TEST_ID 1010: Test for checking an empty rectangle (assuming is_empty method exists)
    TYPED_TEST(RectangleTest, IsEmptyTest_1010) {
        // Arrange
        this->initRectangle(0, 0, 0, 0);
        
        // Act
        bool is_empty = this->rect.is_empty();

        // Assert
        EXPECT_TRUE(is_empty);
    }

    // TEST_ID 1011: Test for normal operation of setting left position
    TYPED_TEST(RectangleTest, SetLeftTest_1011) {
        // Arrange
        TypeParam x = 10, y = 20, width = 30, height = 40;
        this->initRectangle(x, y, width, height);
        TypeParam new_left = 5;

        // Act
        this->rect.set_left(new_left);

        // Assert
        EXPECT_EQ(this->rect.left(), new_left);
    }

    // TEST_ID 1012: Test for setting top position
    TYPED_TEST(RectangleTest, SetTopTest_1012) {
        // Arrange
        TypeParam x = 10, y = 20, width = 30, height = 40;
        this->initRectangle(x, y, width, height);
        TypeParam new_top = 15;

        // Act
        this->rect.set_top(new_top);

        // Assert
        EXPECT_EQ(this->rect.top(), new_top);
    }

    // TEST_ID 1013: Test for normal operation of checking the right position
    TYPED_TEST(RectangleTest, SetRightTest_1013) {
        // Arrange
        TypeParam x = 10, y = 20, width = 30, height = 40;
        this->initRectangle(x, y, width, height);
        TypeParam new_right = 45;

        // Act
        this->rect.set_right(new_right);

        // Assert
        EXPECT_EQ(this->rect.right(), new_right);
    }

    // TEST_ID 1014: Test for normal operation of setting bottom position
    TYPED_TEST(RectangleTest, SetBottomTest_1014) {
        // Arrange
        TypeParam x = 10, y = 20, width = 30, height = 40;
        this->initRectangle(x, y, width, height);
        TypeParam new_bottom = 60;

        // Act
        this->rect.set_bottom(new_bottom);

        // Assert
        EXPECT_EQ(this->rect.bottom(), new_bottom);
    }

    // TEST_ID 1015: Test boundary conditions for large values
    TYPED_TEST(RectangleTest, BoundaryTest_LargeValues_1015) {
        // Arrange
        TypeParam x = std::numeric_limits<TypeParam>::max(), y = 0, width = 1, height = 1;
        
        // Act
        this->initRectangle(x, y, width, height);

        // Assert
        EXPECT_EQ(this->rect.x(), x);
        EXPECT_EQ(this->rect.y(), y);
        EXPECT_EQ(this->rect.width(), width);
        EXPECT_EQ(this->rect.height(), height);
    }

    // TEST_ID 1016: Test boundary conditions for small values
    TYPED_TEST(RectangleTest, BoundaryTest_SmallValues_1016) {
        // Arrange
        TypeParam x = std::numeric_limits<TypeParam>::min(), y = 0, width = 1, height = 1;
        
        // Act
        this->initRectangle(x, y, width, height);

        // Assert
        EXPECT_EQ(this->rect.x(), x);
        EXPECT_EQ(this->rect.y(), y);
        EXPECT_EQ(this->rect.width(), width);
        EXPECT_EQ(this->rect.height(), height);
    }
}