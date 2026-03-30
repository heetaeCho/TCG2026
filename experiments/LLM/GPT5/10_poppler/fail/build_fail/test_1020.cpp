#include "gtest/gtest.h"
#include "poppler-rectangle.h"

namespace poppler {

class RectangleTest_1020 : public ::testing::Test {
protected:
    rectangle<int> rect;

    // SetUp() and TearDown() can be used for any setup or cleanup
    void SetUp() override {
        rect = rectangle<int>(0, 0, 10, 5);  // Initialize a rectangle with x=0, y=0, width=10, height=5
    }

    void TearDown() override {
        // No resources to clean up in this case.
    }
};

// Test the normal behavior of the rectangle's set_bottom() method
TEST_F(RectangleTest_1020, SetBottom_SetsY2_1020) {
    rect.set_bottom(10);
    EXPECT_EQ(rect.bottom(), 10);  // Verify that the bottom (y2) is correctly updated to 10
}

// Test boundary condition: setting the bottom to the same value as the top (y1)
TEST_F(RectangleTest_1020, SetBottom_SetsY2ToTop_1021) {
    rect.set_top(5);
    rect.set_bottom(5);
    EXPECT_EQ(rect.bottom(), 5);  // bottom should be equal to top
    EXPECT_EQ(rect.top(), 5);     // top should remain 5
}

// Test case for an empty rectangle where width and height are 0
TEST_F(RectangleTest_1020, IsEmpty_ZeroWidthAndHeight_1022) {
    rectangle<int> empty_rect(0, 0, 0, 0);
    EXPECT_TRUE(empty_rect.is_empty());  // An empty rectangle should return true
}

// Test error case when trying to set a negative bottom value (assuming no specific behavior for negative values is defined)
TEST_F(RectangleTest_1020, SetBottom_NegativeValue_1023) {
    rect.set_bottom(-5);
    EXPECT_EQ(rect.bottom(), -5);  // Verify that the negative value is set correctly
}

// Test boundary condition: setting very large values for bottom
TEST_F(RectangleTest_1020, SetBottom_LargeValue_1024) {
    rect.set_bottom(1000000);
    EXPECT_EQ(rect.bottom(), 1000000);  // Verify that the large value is set correctly
}

// Test external interaction: Verify set_bottom impacts the rectangle's overall height
TEST_F(RectangleTest_1020, SetBottom_AffectsHeight_1025) {
    rect.set_bottom(8);
    EXPECT_EQ(rect.height(), 8);  // Verify that height adjusts accordingly
}

}  // namespace poppler