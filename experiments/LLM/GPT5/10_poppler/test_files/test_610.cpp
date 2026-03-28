#include <gtest/gtest.h>
#include "GfxState.h"  // Include the header file for GfxState

// Test class for GfxState
class GfxStateTest_610 : public ::testing::Test {
protected:
    // Helper function to create a GfxState instance for testing
    GfxState* createGfxState(double horizScaling) {
        // Create and return a GfxState object with a specific horizontal scaling
        // assuming a constructor that can set horizScaling directly.
        return new GfxState(horizScaling);
    }
};

// Test the getHorizScaling() method for normal operation
TEST_F(GfxStateTest_610, GetHorizScaling_Normal_610) {
    // Arrange
    double expectedHorizScaling = 1.5;
    GfxState* state = createGfxState(expectedHorizScaling);

    // Act
    double actualHorizScaling = state->getHorizScaling();

    // Assert
    EXPECT_DOUBLE_EQ(actualHorizScaling, expectedHorizScaling);

    // Clean up
    delete state;
}

// Test the getHorizScaling() method for boundary condition (zero scaling)
TEST_F(GfxStateTest_610, GetHorizScaling_ZeroScaling_610) {
    // Arrange
    double expectedHorizScaling = 0.0;
    GfxState* state = createGfxState(expectedHorizScaling);

    // Act
    double actualHorizScaling = state->getHorizScaling();

    // Assert
    EXPECT_DOUBLE_EQ(actualHorizScaling, expectedHorizScaling);

    // Clean up
    delete state;
}

// Test the getHorizScaling() method for boundary condition (negative scaling)
TEST_F(GfxStateTest_610, GetHorizScaling_NegativeScaling_610) {
    // Arrange
    double expectedHorizScaling = -2.0;
    GfxState* state = createGfxState(expectedHorizScaling);

    // Act
    double actualHorizScaling = state->getHorizScaling();

    // Assert
    EXPECT_DOUBLE_EQ(actualHorizScaling, expectedHorizScaling);

    // Clean up
    delete state;
}

// Test for invalid state (if applicable) or uninitialized values
TEST_F(GfxStateTest_610, GetHorizScaling_Uninitialized_610) {
    // Arrange
    GfxState* state = new GfxState(0.0);  // A default or empty state if possible

    // Act and Assert: If uninitialized values are invalid, check for error handling
    // (in this example we assume no errors and expect the method to work)
    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.0);

    // Clean up
    delete state;
}