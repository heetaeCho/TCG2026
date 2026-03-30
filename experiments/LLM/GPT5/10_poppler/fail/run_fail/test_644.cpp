#include <gtest/gtest.h>
#include "GfxState.h"

// Test fixture for GfxState
class GfxStateTest_644 : public ::testing::Test {
protected:
    GfxStateTest_644() : gfxState(300.0, 300.0, nullptr, 0, false) {}

    // GfxState instance for testing
    GfxState gfxState;
};

// Normal operation test: Verify that calling setAlphaIsShape(true) updates the alphaIsShape property
TEST_F(GfxStateTest_644, SetAlphaIsShapeTrue_644) {
    // Call setAlphaIsShape with true
    gfxState.setAlphaIsShape(true);

    // Verify that alphaIsShape is correctly set to true
    EXPECT_TRUE(gfxState.getAlphaIsShape());
}

// Normal operation test: Verify that calling setAlphaIsShape(false) updates the alphaIsShape property
TEST_F(GfxStateTest_644, SetAlphaIsShapeFalse_644) {
    // Call setAlphaIsShape with false
    gfxState.setAlphaIsShape(false);

    // Verify that alphaIsShape is correctly set to false
    EXPECT_FALSE(gfxState.getAlphaIsShape());
}

// Exceptional test case: Verify no unexpected behavior when calling setAlphaIsShape multiple times
TEST_F(GfxStateTest_644, SetAlphaIsShapeMultipleCalls_644) {
    // Call setAlphaIsShape with true, then false
    gfxState.setAlphaIsShape(true);
    EXPECT_TRUE(gfxState.getAlphaIsShape());

    gfxState.setAlphaIsShape(false);
    EXPECT_FALSE(gfxState.getAlphaIsShape());

    // Call again with true
    gfxState.setAlphaIsShape(true);
    EXPECT_TRUE(gfxState.getAlphaIsShape());
}

// Boundary condition test: Test behavior when setting alphaIsShape to true then false continuously
TEST_F(GfxStateTest_644, SetAlphaIsShapeTrueFalseBoundary_644) {
    // Set to true, check
    gfxState.setAlphaIsShape(true);
    EXPECT_TRUE(gfxState.getAlphaIsShape());

    // Set to false, check
    gfxState.setAlphaIsShape(false);
    EXPECT_FALSE(gfxState.getAlphaIsShape());

    // Boundary test: setting back to true
    gfxState.setAlphaIsShape(true);
    EXPECT_TRUE(gfxState.getAlphaIsShape());
}

// Mock test case: Verify external interaction (example if GfxState interacted with a callback or logger)
TEST_F(GfxStateTest_644, MockAlphaIsShapeInteraction_644) {
    // Assuming an external mockable handler (e.g., logging, callback, etc.)
    // This test would mock external interactions, but for simplicity here, we'll skip this part since setAlphaIsShape doesn't interact with external systems in the provided code.
}