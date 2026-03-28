#include <gtest/gtest.h>

// Mock class for testing purposes
template<typename Result>
class MockResult {
public:
    MOCK_CONST_METHOD0(error, int());
};

// Test fixture for testing the isValidResult function
class GPGMECryptoSignBackendTest_1948 : public ::testing::Test {
protected:
    // Mocked Result objects
    MockResult<int> result;
};

// Test case for normal operation
TEST_F(GPGMECryptoSignBackendTest_1948, isValidResult_SuccessCase_1948) {
    // Setup: Mock the error method to return a successful error code (0)
    EXPECT_CALL(result, error()).WillOnce(::testing::Return(0));

    // Assert: Verify the function returns true for a successful result
    EXPECT_TRUE(isValidResult(result));
}

// Test case for boundary conditions (error returns a non-zero value)
TEST_F(GPGMECryptoSignBackendTest_1948, isValidResult_FailureCase_1948) {
    // Setup: Mock the error method to return a failure error code (non-zero)
    EXPECT_CALL(result, error()).WillOnce(::testing::Return(1));

    // Assert: Verify the function returns false for a failed result
    EXPECT_FALSE(isValidResult(result));
}

// Exceptional case (Error condition not directly observable in the provided interface, so will verify mock behavior)
TEST_F(GPGMECryptoSignBackendTest_1948, isValidResult_ExceptionalCase_1948) {
    // Setup: Simulate an exceptional behavior (non-zero error)
    EXPECT_CALL(result, error()).WillOnce(::testing::Return(-1)); // Simulating an exception-like condition

    // Assert: Verify the function returns false for an error result
    EXPECT_FALSE(isValidResult(result));
}