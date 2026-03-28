#include <gtest/gtest.h>
#include <poppler-rectangle.h>

namespace poppler {
namespace test {

// Test class for rectangle
class RectangleTest_1012 : public ::testing::Test {
protected:
    // Set up any necessary shared resources for the tests
    void SetUp() override {
        // No shared state needed for these simple tests
    }
};

// Test case for normal operation of height function
TEST_F(RectangleTest_1012, HeightNormalOperation_1012) {
    // Test case for rectangle height computation
    poppler::rectangle<int> rect(0, 0, 5, 10);
    EXPECT_EQ(rect.height(), 10);
}

// Test case for rectangle height when y1 equals y2 (zero height)
TEST_F(RectangleTest_1012, HeightZeroHeight_1012) {
    poppler::rectangle<int> rect(0, 0, 5, 0);
    EXPECT_EQ(rect.height(), 0);
}

// Test case for boundary conditions where height is negative
TEST_F(RectangleTest_1012, HeightNegativeHeight_1012) {
    poppler::rectangle<int> rect(0, 10, 5, -10);
    EXPECT_EQ(rect.height(), -10);
}

// Test case for verifying external interactions with mock handler
TEST_F(RectangleTest_1012, MockHandlerInteraction_1012) {
    // Example test for verifying external handler interactions (mock not implemented in this case)
    // Using Google Mock, if necessary, to check the behavior of rectangle
    // Could add mock behavior here if there were external dependencies (not applicable here)
    SUCCEED(); // Placeholder to indicate interaction testing
}

}  // namespace test
}  // namespace poppler