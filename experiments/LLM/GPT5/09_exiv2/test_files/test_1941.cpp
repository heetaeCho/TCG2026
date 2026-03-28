#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "XMPUtils.hpp"
#include "WXMPUtils.hpp"

// Mock class to simulate the WXMP_Result
class MockWXMPResult : public WXMP_Result {
public:
    MOCK_METHOD(void, SetResult, (XMP_Int32 result), ());
};

// Test fixture for WXMPUtils_ConvertToInt_1
class WXMPUtilsConvertToIntTest_1941 : public testing::Test {
protected:
    void SetUp() override {
        // Initialize the mock WXMP_Result object
        mockResult = std::make_unique<MockWXMPResult>();
    }

    std::unique_ptr<MockWXMPResult> mockResult;
};

// Normal operation test case
TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertToIntNormal_1941) {
    // Define the test input and expected result
    XMP_StringPtr strValue = "123";
    XMP_Int32 expectedResult = 123;

    // Set up mock expectation
    EXPECT_CALL(*mockResult, SetResult(expectedResult)).Times(1);

    // Call the function under test
    WXMPUtils_ConvertToInt_1(strValue, mockResult.get());
}

// Boundary condition: empty string input should throw an error
TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertToIntEmptyString_1942) {
    // Define the test input
    XMP_StringPtr strValue = "";

    // Expect that the function throws an error
    EXPECT_THROW({
        WXMPUtils_ConvertToInt_1(strValue, mockResult.get());
    }, XMP_Error);  // XMP_Error is thrown for empty string
}

// Boundary condition: null string input should throw an error
TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertToIntNullString_1943) {
    // Define the test input
    XMP_StringPtr strValue = nullptr;

    // Expect that the function throws an error
    EXPECT_THROW({
        WXMPUtils_ConvertToInt_1(strValue, mockResult.get());
    }, XMP_Error);  // XMP_Error is thrown for null pointer
}

// Error case: invalid conversion input, the function might throw an exception or handle differently
TEST_F(WXMPUtilsConvertToIntTest_1941, ConvertToIntInvalidString_1944) {
    // Define the test input
    XMP_StringPtr strValue = "abc";  // Non-numeric string

    // Expect that the function throws an error
    EXPECT_THROW({
        WXMPUtils_ConvertToInt_1(strValue, mockResult.get());
    }, XMP_Error);  // Expecting XMP_Error or another error for invalid string
}

// Verifying that the result is set correctly
TEST_F(WXMPUtilsConvertToIntTest_1941, VerifyResultSet_1945) {
    // Define the test input and expected result
    XMP_StringPtr strValue = "456";
    XMP_Int32 expectedResult = 456;

    // Set up mock expectation
    EXPECT_CALL(*mockResult, SetResult(expectedResult)).Times(1);

    // Call the function under test
    WXMPUtils_ConvertToInt_1(strValue, mockResult.get());
}