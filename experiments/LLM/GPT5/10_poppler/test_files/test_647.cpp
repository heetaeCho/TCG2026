#include <gtest/gtest.h>
#include "GfxState.h"

// Mock external dependencies if needed (None identified in this example)

class GfxStateTest_647 : public ::testing::Test {
protected:
    GfxStateTest_647() {
        // Setup code if necessary
    }

    ~GfxStateTest_647() override {
        // Cleanup code if necessary
    }
};

// Test case for the setCharSpace method
TEST_F(GfxStateTest_647, SetCharSpace_NormalOperation_647) {
    GfxState gfxState(300.0, 300.0, nullptr, 0, false);  // Assuming a constructor to initialize the state

    double expected = 12.5;
    gfxState.setCharSpace(expected);  // Setting the charSpace to 12.5

    // Verify that the setCharSpace worked
    EXPECT_EQ(gfxState.getCharSpace(), expected);
}

// Test case for boundary condition where charSpace is set to a very large value
TEST_F(GfxStateTest_647, SetCharSpace_LargeValue_647) {
    GfxState gfxState(300.0, 300.0, nullptr, 0, false);

    double largeValue = 1e6;
    gfxState.setCharSpace(largeValue);

    // Verify that the large value is set correctly
    EXPECT_EQ(gfxState.getCharSpace(), largeValue);
}

// Test case for boundary condition where charSpace is set to 0
TEST_F(GfxStateTest_647, SetCharSpace_ZeroValue_647) {
    GfxState gfxState(300.0, 300.0, nullptr, 0, false);

    double zeroValue = 0.0;
    gfxState.setCharSpace(zeroValue);

    // Verify that the charSpace is set to zero
    EXPECT_EQ(gfxState.getCharSpace(), zeroValue);
}

// Test case for exceptional case where charSpace is set to a negative value
TEST_F(GfxStateTest_647, SetCharSpace_NegativeValue_647) {
    GfxState gfxState(300.0, 300.0, nullptr, 0, false);

    double negativeValue = -5.0;
    gfxState.setCharSpace(negativeValue);

    // Verify that the negative value is set (assuming no restrictions on negative values in the provided interface)
    EXPECT_EQ(gfxState.getCharSpace(), negativeValue);
}

// Test case for verification of external interaction (if applicable, e.g., mocking external collaborators)
TEST_F(GfxStateTest_647, ExternalInteractionTest_647) {
    // Assuming a mockable handler or dependency if applicable
    // Example: EXPECT_CALL(mockHandler, someFunction()).Times(1);

    // Test setup with external interaction verification
}