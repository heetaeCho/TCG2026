#include <gtest/gtest.h>
#include <memory>
#include "GfxState.h"
#include "GfxColorSpace.h"

// Mock class for testing purposes (if needed for external dependencies)
class MockGfxColorSpace : public GfxColorSpace {
public:
    MOCK_METHOD(std::unique_ptr<GfxColorSpace>, copy, (), (const, override));
};

// Test fixture for GfxState
class GfxStateTest_658 : public testing::Test {
protected:
    GfxStateTest_658() : state(300, 300, nullptr, 0, false) {}

    GfxState state;
};

// TEST 1: Normal operation when the defaultGrayColorSpace is initialized
TEST_F(GfxStateTest_658, CopyDefaultGrayColorSpace_Normal_658) {
    // Setup: initialize a GfxState with a valid defaultGrayColorSpace
    std::unique_ptr<GfxColorSpace> grayColorSpace = std::make_unique<GfxColorSpace>();
    state.setDefaultGrayColorSpace(std::move(grayColorSpace));

    // Action: Call the copyDefaultGrayColorSpace method
    auto copiedColorSpace = state.copyDefaultGrayColorSpace();

    // Verify: The returned color space is not null
    ASSERT_NE(copiedColorSpace, nullptr);
}

// TEST 2: Behavior when defaultGrayColorSpace is not initialized (null)
TEST_F(GfxStateTest_658, CopyDefaultGrayColorSpace_DefaultNotSet_658) {
    // Setup: No defaultGrayColorSpace is set (it is null)

    // Action: Call the copyDefaultGrayColorSpace method
    auto copiedColorSpace = state.copyDefaultGrayColorSpace();

    // Verify: It should return a default GfxDeviceGrayColorSpace (non-null)
    ASSERT_NE(copiedColorSpace, nullptr);
    // You can add more specific checks if needed, like type-checking (dynamic_cast, etc.)
}

// TEST 3: Verifying the call to copy() in the case of a set defaultGrayColorSpace
TEST_F(GfxStateTest_658, CopyDefaultGrayColorSpace_CallToCopy_658) {
    // Setup: Create a mock GfxColorSpace
    auto mockColorSpace = std::make_unique<MockGfxColorSpace>();
    EXPECT_CALL(*mockColorSpace, copy()).WillOnce(testing::Return(std::make_unique<GfxColorSpace>()));

    // Set the mock color space
    state.setDefaultGrayColorSpace(std::move(mockColorSpace));

    // Action: Call the copyDefaultGrayColorSpace method
    auto copiedColorSpace = state.copyDefaultGrayColorSpace();

    // Verify: The copy method on the mock GfxColorSpace was called
    testing::Mock::VerifyAndClearExpectations(mockColorSpace.get());
    ASSERT_NE(copiedColorSpace, nullptr);
}

// TEST 4: Edge case when the function is called multiple times
TEST_F(GfxStateTest_658, CopyDefaultGrayColorSpace_MultipleCalls_658) {
    // Setup: Initialize with a default gray color space
    std::unique_ptr<GfxColorSpace> grayColorSpace = std::make_unique<GfxColorSpace>();
    state.setDefaultGrayColorSpace(std::move(grayColorSpace));

    // Action & Verify: Call the function twice and ensure consistent results
    auto firstCopy = state.copyDefaultGrayColorSpace();
    auto secondCopy = state.copyDefaultGrayColorSpace();
    
    ASSERT_NE(firstCopy, nullptr);
    ASSERT_NE(secondCopy, nullptr);
    ASSERT_NE(firstCopy.get(), secondCopy.get());  // Ensures they are different instances
}