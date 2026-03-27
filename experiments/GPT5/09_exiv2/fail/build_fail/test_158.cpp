#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/value.hpp"

using namespace Exiv2;

// Mock class to simulate interactions
class MockValueType : public ValueType<double> {
public:
    MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));
};

// Unit test for the toUint32 method of ValueType<double>
TEST_F(ValueTypeTest_158, toUint32_NormalOperation_158) {
    // Create a ValueType object for double with a mock value
    ValueType<double> value(3.14, TypeId::kUnknown);

    // Test the toUint32 function with a sample size
    uint32_t result = value.toUint32(10);  // Arbitrary size for testing

    // Expectation based on the conversion logic in the implementation
    uint32_t expectedResult = static_cast<uint32_t>(3.14);  // Expected result from the toUint32 conversion
    EXPECT_EQ(result, expectedResult);
}

TEST_F(ValueTypeTest_158, toUint32_ZeroSize_158) {
    // Test the toUint32 function with size 0 (boundary condition)
    ValueType<double> value(1.0, TypeId::kUnknown);
    uint32_t result = value.toUint32(0);  // Size is zero

    uint32_t expectedResult = static_cast<uint32_t>(1.0);  // Conversion of 1.0 to uint32_t
    EXPECT_EQ(result, expectedResult);
}

TEST_F(ValueTypeTest_158, toUint32_NegativeSize_158) {
    // Test the toUint32 function with a negative size
    ValueType<double> value(-1.0, TypeId::kUnknown);
    uint32_t result = value.toUint32(-10);  // Invalid size (negative size)

    // Since negative size doesn't make sense, we assume an exception should be thrown or result in an error
    // Depending on your implementation, you could expect an exception or specific behavior
    EXPECT_EQ(result, 0);  // Here we're assuming 0 for an invalid negative size
}

TEST_F(ValueTypeTest_158, toUint32_LargeDouble_158) {
    // Test the toUint32 function with a very large double value
    ValueType<double> value(1e10, TypeId::kUnknown);  // Very large number
    uint32_t result = value.toUint32(50);  // Arbitrary size for testing

    // The result is a large number that should be cast to uint32_t
    uint32_t expectedResult = static_cast<uint32_t>(1e10);  // Expect a truncated result based on casting
    EXPECT_EQ(result, expectedResult);
}

// Mocking a different scenario for mocking external collaborations (if needed)
TEST_F(ValueTypeTest_158, MockToUint32_158) {
    // Create a mock ValueType object
    MockValueType mockValue;

    // Set up an expectation for toUint32 with size 100
    EXPECT_CALL(mockValue, toUint32(100))
        .WillOnce(testing::Return(42));  // Mock return value

    // Invoke the method
    uint32_t result = mockValue.toUint32(100);

    // Verify that the mocked method was called and returned the expected value
    EXPECT_EQ(result, 42);
}