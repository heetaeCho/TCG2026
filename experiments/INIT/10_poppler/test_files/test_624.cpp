#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Mocking external dependencies
class MockGfxPath : public GfxPath {
public:
    MOCK_CONST_METHOD0(isPath, bool());
};

class GfxStateTest_624 : public ::testing::Test {
protected:
    GfxStateTest_624() = default;
    ~GfxStateTest_624() override = default;
};

// Normal operation: Verifying isPath when path is valid
TEST_F(GfxStateTest_624, IsPath_ReturnsTrue_WhenPathIsValid_624) {
    MockGfxPath mockPath;
    EXPECT_CALL(mockPath, isPath()).WillOnce(::testing::Return(true));

    GfxState gfxState;
    gfxState.setPath(&mockPath);

    ASSERT_TRUE(gfxState.isPath());
}

// Normal operation: Verifying isPath when path is invalid
TEST_F(GfxStateTest_624, IsPath_ReturnsFalse_WhenPathIsInvalid_624) {
    MockGfxPath mockPath;
    EXPECT_CALL(mockPath, isPath()).WillOnce(::testing::Return(false));

    GfxState gfxState;
    gfxState.setPath(&mockPath);

    ASSERT_FALSE(gfxState.isPath());
}

// Boundary case: Verifying behavior when path is NULL
TEST_F(GfxStateTest_624, IsPath_ReturnsFalse_WhenPathIsNull_624) {
    GfxState gfxState;
    gfxState.setPath(nullptr);

    ASSERT_FALSE(gfxState.isPath());
}

// Exceptional case: Verifying if a failed path check behaves as expected
TEST_F(GfxStateTest_624, IsPath_ReturnsFalse_WhenPathCheckFails_624) {
    GfxState gfxState;
    // Simulating an error or path failure scenario
    gfxState.setPath(nullptr); // Simulating the error case
    ASSERT_FALSE(gfxState.isPath());
}

// Verification of external interaction: Verifying that isPath interacts correctly with external dependencies
TEST_F(GfxStateTest_624, IsPath_CallsExternalMethod_WhenInvoked_624) {
    MockGfxPath mockPath;
    EXPECT_CALL(mockPath, isPath()).Times(1).WillOnce(::testing::Return(true));

    GfxState gfxState;
    gfxState.setPath(&mockPath);

    // This will trigger the call to mockPath.isPath
    gfxState.isPath();
}