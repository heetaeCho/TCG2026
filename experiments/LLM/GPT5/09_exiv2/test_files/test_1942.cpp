#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "WXMPUtils.cpp"

class WXMPUtilsConvertToInt64Test_1942 : public ::testing::Test {
protected:
    WXMP_Result wResult;
};

// Normal Operation Test
TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertToInt64_NormalOperation_1942) {
    // Test case where strValue contains a valid integer string
    XMP_StringPtr strValue = "12345";
    
    WXMPUtils_ConvertToInt64_1(strValue, &wResult);
    
    // Verify that the result is correctly converted
    EXPECT_EQ(wResult.int64Result, 12345);
}

// Boundary Condition Test: Empty string input
TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertToInt64_EmptyString_1942) {
    // Test case where strValue is an empty string
    XMP_StringPtr strValue = "";
    
    // Expect an exception to be thrown for empty string
    EXPECT_THROW(WXMPUtils_ConvertToInt64_1(strValue, &wResult), std::runtime_error);
}

// Boundary Condition Test: Null pointer as input
TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertToInt64_NullPointer_1942) {
    // Test case where strValue is a null pointer
    XMP_StringPtr strValue = nullptr;
    
    // Expect an exception to be thrown for null pointer
    EXPECT_THROW(WXMPUtils_ConvertToInt64_1(strValue, &wResult), std::runtime_error);
}

// Error Case: Invalid string input (non-integer)
TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertToInt64_InvalidString_1942) {
    // Test case where strValue contains non-integer characters
    XMP_StringPtr strValue = "abcde";
    
    // Expect an exception to be thrown for invalid string format
    EXPECT_THROW(WXMPUtils_ConvertToInt64_1(strValue, &wResult), std::runtime_error);
}

// Mock external interaction: Verifying external function call
TEST_F(WXMPUtilsConvertToInt64Test_1942, ConvertToInt64_VerifyMockHandler_1942) {
    // Test case to verify if external handlers are called correctly (assuming the logic supports external mocks)
    XMP_StringPtr strValue = "98765";
    
    // Expect no exception and the result to be the converted int64
    WXMPUtils_ConvertToInt64_1(strValue, &wResult);
    
    // Verify that the result is correctly converted
    EXPECT_EQ(wResult.int64Result, 98765);
}