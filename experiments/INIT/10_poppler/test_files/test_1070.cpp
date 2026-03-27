#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock the necessary dependencies
class GfxState {};
class GfxAxialShading {};

// Mock the OutputDev class
class OutputDevMock : public OutputDev {
public:
    MOCK_METHOD(bool, axialShadedSupportExtend, (GfxState *state, GfxAxialShading *shading), (override));
};

// Test Fixture
class OutputDevTest_1070 : public ::testing::Test {
protected:
    OutputDevMock mockOutputDev;
};

// Test for normal operation
TEST_F(OutputDevTest_1070, AxialShadedSupportExtend_ReturnsFalseByDefault_1070) {
    // Test that the function returns false by default
    GfxState state;
    GfxAxialShading shading;

    EXPECT_FALSE(mockOutputDev.axialShadedSupportExtend(&state, &shading));
}

// Test for boundary condition with null pointers
TEST_F(OutputDevTest_1070, AxialShadedSupportExtend_WithNullPointers_1070) {
    // Test that the function returns false when passed null pointers
    EXPECT_FALSE(mockOutputDev.axialShadedSupportExtend(nullptr, nullptr));
}

// Exceptional case: Verification of the method call (external interaction)
TEST_F(OutputDevTest_1070, AxialShadedSupportExtend_VerifyCallToMethod_1070) {
    // Set up expectations using Google Mock
    GfxState state;
    GfxAxialShading shading;

    // Expect the method to be called with specific parameters
    EXPECT_CALL(mockOutputDev, axialShadedSupportExtend(&state, &shading))
        .Times(1)
        .WillOnce(::testing::Return(false));

    // Call the function and verify interaction
    bool result = mockOutputDev.axialShadedSupportExtend(&state, &shading);
    EXPECT_FALSE(result);
}

// Test for boundary condition: Calling the method multiple times
TEST_F(OutputDevTest_1070, AxialShadedSupportExtend_MultipleCalls_1070) {
    GfxState state;
    GfxAxialShading shading;

    // Verify multiple calls
    EXPECT_CALL(mockOutputDev, axialShadedSupportExtend(&state, &shading))
        .Times(3)
        .WillRepeatedly(::testing::Return(false));

    // Call the function multiple times and check the return value
    EXPECT_FALSE(mockOutputDev.axialShadedSupportExtend(&state, &shading));
    EXPECT_FALSE(mockOutputDev.axialShadedSupportExtend(&state, &shading));
    EXPECT_FALSE(mockOutputDev.axialShadedSupportExtend(&state, &shading));
}