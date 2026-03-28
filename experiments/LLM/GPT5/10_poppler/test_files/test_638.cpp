#include <gtest/gtest.h>
#include "GfxState.h"

class GfxStateTest_638 : public ::testing::Test {
protected:
    GfxState state{72.0, 72.0, nullptr, 0, false};  // A test GfxState object, initialized with arbitrary values

    // Helper function to check the line width set
    void assertLineWidth(double expected) {
        EXPECT_DOUBLE_EQ(state.getLineWidth(), expected);
    }
};

// Test case for normal operation (valid line width)
TEST_F(GfxStateTest_638, SetValidLineWidth_638) {
    // Test setting a positive line width
    double newWidth = 5.0;
    state.setLineWidth(newWidth);
    assertLineWidth(newWidth);  // Verify the line width is set correctly
}

// Test case for boundary condition (zero line width)
TEST_F(GfxStateTest_638, SetZeroLineWidth_638) {
    double newWidth = 0.0;
    state.setLineWidth(newWidth);
    assertLineWidth(newWidth);  // Verify the line width can be set to zero
}

// Test case for boundary condition (negative line width)
TEST_F(GfxStateTest_638, SetNegativeLineWidth_638) {
    double newWidth = -1.0;
    state.setLineWidth(newWidth);
    assertLineWidth(newWidth);  // Verify the line width can be set to a negative value
}

// Test case for exceptional/error case (invalid line width)
TEST_F(GfxStateTest_638, SetInvalidLineWidth_638) {
    double newWidth = -9999.0;  // Arbitrary invalid value
    state.setLineWidth(newWidth);
    assertLineWidth(newWidth);  // Verify that negative values are still set, but they could be handled differently
}