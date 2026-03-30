#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"  // Include the necessary header for GfxState

// Test Suite for GfxState class
class GfxStateTest_643 : public ::testing::Test {
protected:
    GfxStateTest_643() {
        // Setup if needed for the test suite
    }

    // Optionally, add common resources for tests (e.g., GfxState object)
    GfxState gfxState{300.0, 300.0, nullptr, 0, false};
};

// Test: Setting stroke adjust to true
TEST_F(GfxStateTest_643, SetStrokeAdjust_True_643) {
    // Call the setStrokeAdjust function with true
    gfxState.setStrokeAdjust(true);
    
    // Verify that the strokeAdjust value is correctly set
    ASSERT_TRUE(gfxState.getStrokeAdjust());  // Assuming getter is available in the class
}

// Test: Setting stroke adjust to false
TEST_F(GfxStateTest_643, SetStrokeAdjust_False_643) {
    // Call the setStrokeAdjust function with false
    gfxState.setStrokeAdjust(false);
    
    // Verify that the strokeAdjust value is correctly set
    ASSERT_FALSE(gfxState.getStrokeAdjust());  // Assuming getter is available in the class
}

// Boundary Test: Setting stroke adjust multiple times
TEST_F(GfxStateTest_643, SetStrokeAdjust_MultipleCalls_643) {
    // Call setStrokeAdjust multiple times with different values
    gfxState.setStrokeAdjust(true);
    ASSERT_TRUE(gfxState.getStrokeAdjust());
    
    gfxState.setStrokeAdjust(false);
    ASSERT_FALSE(gfxState.getStrokeAdjust());
    
    gfxState.setStrokeAdjust(true);
    ASSERT_TRUE(gfxState.getStrokeAdjust());
}

// Exceptional Test: Calling setStrokeAdjust when other settings are modified
TEST_F(GfxStateTest_643, SetStrokeAdjust_WithOtherChanges_643) {
    // Simulate other modifications (e.g., setting color)
    gfxState.setLineWidth(5.0);  // Example of other function call
    
    // Set stroke adjust after modifying other properties
    gfxState.setStrokeAdjust(true);
    
    // Verify that the setter worked as expected
    ASSERT_TRUE(gfxState.getStrokeAdjust());
}

// Mock Test: Verifying external interaction using GoogleMock (if needed)
TEST_F(GfxStateTest_643, SetStrokeAdjust_ExternalInteraction_643) {
    // In case we need to mock any external handler or interaction, this test could be added.
    // You can use GoogleMock to mock external dependencies and validate how setStrokeAdjust interacts with them.
    // For this example, we will not use mocks as the function is self-contained.
}