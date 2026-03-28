#include <gtest/gtest.h>
#include "GfxState.h"

class GfxStateTest : public ::testing::Test {
protected:
    GfxStateTest() {}

    // Helper function to create a GfxState object with a specific rotation
    GfxState createGfxStateWithRotation(int rotate) {
        return GfxState(72.0, 72.0, nullptr, rotate, false);  // Mocking constructor params
    }
};

TEST_F(GfxStateTest, GetRotate_NormalOperation_574) {
    // Test for normal operation with different rotation values

    // Test with rotation = 0
    GfxState state0 = createGfxStateWithRotation(0);
    EXPECT_EQ(state0.getRotate(), 0) << "Expected rotation to be 0";

    // Test with rotation = 90
    GfxState state90 = createGfxStateWithRotation(90);
    EXPECT_EQ(state90.getRotate(), 90) << "Expected rotation to be 90";

    // Test with rotation = 180
    GfxState state180 = createGfxStateWithRotation(180);
    EXPECT_EQ(state180.getRotate(), 180) << "Expected rotation to be 180";

    // Test with rotation = 270
    GfxState state270 = createGfxStateWithRotation(270);
    EXPECT_EQ(state270.getRotate(), 270) << "Expected rotation to be 270";
}

TEST_F(GfxStateTest, GetRotate_BoundaryCondition_574) {
    // Test boundary conditions for rotation values

    // Test with extreme rotation value (e.g., 360, which is equivalent to 0)
    GfxState state360 = createGfxStateWithRotation(360);
    EXPECT_EQ(state360.getRotate(), 360) << "Expected rotation to be 360";

    // Test with negative rotation value (-90)
    GfxState stateNeg90 = createGfxStateWithRotation(-90);
    EXPECT_EQ(stateNeg90.getRotate(), -90) << "Expected rotation to be -90";
}

TEST_F(GfxStateTest, GetRotate_ExceptionalCase_574) {
    // Test for exceptional or error cases where rotation should not exceed 360
    GfxState stateInvalid = createGfxStateWithRotation(1000); // Invalid rotation
    EXPECT_EQ(stateInvalid.getRotate(), 1000) << "Expected rotation to handle out-of-bound values correctly";
}