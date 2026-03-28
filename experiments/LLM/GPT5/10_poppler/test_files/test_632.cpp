#include <gtest/gtest.h>
#include "GfxState.h"

class GfxStateTest_632 : public ::testing::Test {
protected:
    // Test fixture setup, if needed
    void SetUp() override {
        // Setup if needed for each test
    }

    // Test fixture cleanup, if needed
    void TearDown() override {
        // Cleanup if needed for each test
    }
};

TEST_F(GfxStateTest_632, SetBlendMode_ValidMode_ChangesBlendMode_632) {
    // Arrange
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);  // Example GfxState initialization
    GfxBlendMode mode = GfxBlendMode::Normal; // Assuming Normal is a valid enum for blend mode

    // Act
    gfxState.setBlendMode(mode);

    // Assert
    EXPECT_EQ(gfxState.getBlendMode(), mode);
}

TEST_F(GfxStateTest_632, SetBlendMode_DifferentMode_ChangesBlendMode_632) {
    // Arrange
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);  // Example GfxState initialization
    GfxBlendMode mode1 = GfxBlendMode::Normal;
    GfxBlendMode mode2 = GfxBlendMode::Multiply; // Assuming Multiply is another valid enum for blend mode

    // Act
    gfxState.setBlendMode(mode1); // Set first mode
    gfxState.setBlendMode(mode2); // Set different mode

    // Assert
    EXPECT_EQ(gfxState.getBlendMode(), mode2);
}

TEST_F(GfxStateTest_632, SetBlendMode_HandlesInvalidMode_632) {
    // Arrange
    GfxState gfxState(72.0, 72.0, nullptr, 0, false);  // Example GfxState initialization
    GfxBlendMode invalidMode = static_cast<GfxBlendMode>(999); // Invalid blend mode

    // Act
    gfxState.setBlendMode(invalidMode);

    // Assert
    // Assuming the function will set to a default mode or handle invalid input
    EXPECT_EQ(gfxState.getBlendMode(), GfxBlendMode::Normal);  // Default to normal mode
}