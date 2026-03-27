#include <gtest/gtest.h>
#include <memory>

// Include the necessary files
#include "./TestProjects/poppler/poppler/Annot.h"

// Mocking external dependencies if necessary
class MockXRef {};

// Test fixture for AnnotBorderArray
class AnnotBorderArrayTest : public ::testing::Test {
protected:
    // Create a fresh AnnotBorderArray object for each test case
    AnnotBorderArray annotBorderArray;

    AnnotBorderArrayTest() {
        // Initialize or set up anything if needed
    }

    ~AnnotBorderArrayTest() override {
        // Clean up if needed
    }
};

// Test case for normal operation: Setting and getting vertical corner
TEST_F(AnnotBorderArrayTest, SetAndGetVerticalCorner_751) {
    // Test behavior of setVerticalCorner and getVerticalCorner methods
    double testVerticalCorner = 10.5;

    // Set the vertical corner
    annotBorderArray.setVerticalCorner(testVerticalCorner);

    // Get and verify the vertical corner
    EXPECT_DOUBLE_EQ(annotBorderArray.getVerticalCorner(), testVerticalCorner);
}

// Test case for normal operation: Setting and getting horizontal corner
TEST_F(AnnotBorderArrayTest, SetAndGetHorizontalCorner_751) {
    // Test behavior of setHorizontalCorner and getHorizontalCorner methods
    double testHorizontalCorner = 15.5;

    // Set the horizontal corner
    annotBorderArray.setHorizontalCorner(testHorizontalCorner);

    // Get and verify the horizontal corner
    EXPECT_DOUBLE_EQ(annotBorderArray.getHorizontalCorner(), testHorizontalCorner);
}

// Test case for boundary condition: Setting and getting very large values for corners
TEST_F(AnnotBorderArrayTest, SetAndGetLargeCornerValues_751) {
    // Test behavior when setting large values for corners
    double largeValue = 1e6;

    // Set the vertical corner to a very large value
    annotBorderArray.setVerticalCorner(largeValue);
    EXPECT_DOUBLE_EQ(annotBorderArray.getVerticalCorner(), largeValue);

    // Set the horizontal corner to a very large value
    annotBorderArray.setHorizontalCorner(largeValue);
    EXPECT_DOUBLE_EQ(annotBorderArray.getHorizontalCorner(), largeValue);
}

// Test case for boundary condition: Setting and getting very small values for corners
TEST_F(AnnotBorderArrayTest, SetAndGetSmallCornerValues_751) {
    // Test behavior when setting very small values for corners
    double smallValue = 1e-6;

    // Set the vertical corner to a very small value
    annotBorderArray.setVerticalCorner(smallValue);
    EXPECT_DOUBLE_EQ(annotBorderArray.getVerticalCorner(), smallValue);

    // Set the horizontal corner to a very small value
    annotBorderArray.setHorizontalCorner(smallValue);
    EXPECT_DOUBLE_EQ(annotBorderArray.getHorizontalCorner(), smallValue);
}

// Test case for exceptional case: Handling of uninitialized corner values (should not happen with this API but can be simulated)
TEST_F(AnnotBorderArrayTest, HandleUninitializedCornerValues_751) {
    // In real-world scenarios, we'd test edge cases like calling getters before setting values.
    // This may require additional handling in your code, but for now, it is simply verifying behavior.
    // AnnotBorderArray assumes that the corner values are initialized, so we'll expect them to return default values.
    EXPECT_DOUBLE_EQ(annotBorderArray.getHorizontalCorner(), 0.0);
    EXPECT_DOUBLE_EQ(annotBorderArray.getVerticalCorner(), 0.0);
}