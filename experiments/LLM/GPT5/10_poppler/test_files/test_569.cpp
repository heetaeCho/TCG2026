#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"

class GfxStateTest_569 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code for each test
        gfxState = std::make_unique<GfxState>(300.0, 300.0, nullptr, 0, false);
    }

    std::unique_ptr<GfxState> gfxState;
};

TEST_F(GfxStateTest_569, getY1ReturnsCorrectValue_569) {
    // Test the normal operation of getY1()
    double y1 = gfxState->getY1();
    EXPECT_EQ(y1, 0.0); // Assuming default value for py1 is 0.0
}

TEST_F(GfxStateTest_569, getY1AfterTransform_569) {
    // Test getY1 after a transformation to check boundary conditions
    gfxState->setCTM(1.0, 0.0, 0.0, 1.0, 10.0, 20.0); // Translate by (10, 20)
    double y1 = gfxState->getY1();
    EXPECT_EQ(y1, 20.0); // py1 should now reflect the translation
}

TEST_F(GfxStateTest_569, getY1WhenInverted_569) {
    // Test getY1 in an inverted state (boundary case)
    gfxState->setCTM(1.0, 0.0, 0.0, -1.0, 0.0, 0.0); // Invert the vertical axis
    double y1 = gfxState->getY1();
    EXPECT_EQ(y1, 0.0); // After inversion, y1 may be 0 if no additional transformation is applied
}

TEST_F(GfxStateTest_569, getY1WithNonZeroValues_569) {
    // Test getY1 with a non-zero py1 value set by the user
    gfxState->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, 50.0); // Set CTM to have a vertical translation
    double y1 = gfxState->getY1();
    EXPECT_EQ(y1, 50.0); // Assuming the transformation applies correctly to py1
}

TEST_F(GfxStateTest_569, getY1BoundaryCase_569) {
    // Test the boundary case of py1 being the max possible value (double max)
    gfxState->setCTM(1.0, 0.0, 0.0, 1.0, 0.0, std::numeric_limits<double>::max());
    double y1 = gfxState->getY1();
    EXPECT_EQ(y1, std::numeric_limits<double>::max()); // Check boundary handling
}

TEST_F(GfxStateTest_569, getY1AfterReset_569) {
    // Test getY1 after resetting the transformation matrix
    gfxState->setCTM(0.0, 0.0, 0.0, 0.0, 0.0, 0.0); // Reset CTM to the identity
    double y1 = gfxState->getY1();
    EXPECT_EQ(y1, 0.0); // After reset, y1 should be the default value
}