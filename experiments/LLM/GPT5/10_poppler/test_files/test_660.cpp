#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "GfxColorSpace.h"

class GfxStateTest : public ::testing::Test {
protected:
    std::unique_ptr<GfxState> gfxState;

    void SetUp() override {
        gfxState = std::make_unique<GfxState>(300.0, 300.0, nullptr, 0, false);
    }
};

TEST_F(GfxStateTest, CopyDefaultCMYKColorSpace_ReturnsCopiedColorSpace_660) {
    // Arrange
    std::unique_ptr<GfxColorSpace> expectedColorSpace = std::make_unique<GfxDeviceCMYKColorSpace>();

    // Act
    std::unique_ptr<GfxColorSpace> copiedColorSpace = gfxState->copyDefaultCMYKColorSpace();

    // Assert
    ASSERT_NE(copiedColorSpace, nullptr);  // Ensure the copied color space is not null
    EXPECT_NE(copiedColorSpace.get(), expectedColorSpace.get());  // Ensure a new instance is returned
    // Assuming that GfxDeviceCMYKColorSpace has a method to compare or verify its equality
    // Use an appropriate method or check based on the actual class behavior
}

TEST_F(GfxStateTest, CopyDefaultCMYKColorSpace_ReturnsDefaultColorSpaceWhenNull_661) {
    // Arrange: Ensure defaultCMYKColorSpace is null
    gfxState->defaultCMYKColorSpace.reset();

    // Act
    std::unique_ptr<GfxColorSpace> copiedColorSpace = gfxState->copyDefaultCMYKColorSpace();

    // Assert
    ASSERT_NE(copiedColorSpace, nullptr);
    EXPECT_TRUE(dynamic_cast<GfxDeviceCMYKColorSpace*>(copiedColorSpace.get()) != nullptr);
}

TEST_F(GfxStateTest, CopyDefaultCMYKColorSpace_WhenColorSpaceIsAlreadySet_662) {
    // Arrange: Set a specific color space for defaultCMYKColorSpace
    std::unique_ptr<GfxColorSpace> existingColorSpace = std::make_unique<GfxDeviceCMYKColorSpace>();
    gfxState->defaultCMYKColorSpace = std::move(existingColorSpace);

    // Act
    std::unique_ptr<GfxColorSpace> copiedColorSpace = gfxState->copyDefaultCMYKColorSpace();

    // Assert
    ASSERT_NE(copiedColorSpace, nullptr);
    EXPECT_NE(copiedColorSpace.get(), gfxState->defaultCMYKColorSpace.get());  // Should return a different instance
}