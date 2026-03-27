#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMP_Const.h" // Including error constants
#include "WXMPUtils.h"  // The header where WXMPUtils_ConvertToBool_1 is declared
#include "XMPUtils.hpp" // For the XMPUtils class, needed for mocking

// Mocking XMPUtils for our test
class MockXMPUtils : public XMPUtils {
public:
    MOCK_METHOD(bool, ConvertToBool, (XMP_StringPtr strValue), (override));  // Mocking ConvertToBool method
};

TEST_F(WXMPUtilsTest, ConvertToBool_ValidString_True_1940) {
    // Setup
    MockXMPUtils mockXMPUtils;
    const char* validStr = "true";  // Non-empty string for a valid case
    WXMP_Result result;

    // Expectation
    EXPECT_CALL(mockXMPUtils, ConvertToBool(validStr))
        .WillOnce(testing::Return(true));  // Expect the mock to return true for this string

    // Execute function
    WXMPUtils_ConvertToBool_1(validStr, &result);
    
    // Assert the expected result is populated correctly
    EXPECT_EQ(result.int32Result, 1);  // Since true should be converted to 1 (int32)
}

TEST_F(WXMPUtilsTest, ConvertToBool_ValidString_False_1941) {
    // Setup
    MockXMPUtils mockXMPUtils;
    const char* validStr = "false";  // Non-empty string but for false
    WXMP_Result result;

    // Expectation
    EXPECT_CALL(mockXMPUtils, ConvertToBool(validStr))
        .WillOnce(testing::Return(false));  // Expect the mock to return false for this string

    // Execute function
    WXMPUtils_ConvertToBool_1(validStr, &result);

    // Assert the expected result is populated correctly
    EXPECT_EQ(result.int32Result, 0);  // false should be converted to 0 (int32)
}

TEST_F(WXMPUtilsTest, ConvertToBool_EmptyString_ThrowsError_1942) {
    // Setup
    MockXMPUtils mockXMPUtils;
    const char* invalidStr = "";  // Empty string (edge case)
    WXMP_Result result;

    // Expectation: An empty string should throw an error
    EXPECT_THROW(WXMPUtils_ConvertToBool_1(invalidStr, &result), XMP_Error);
}

TEST_F(WXMPUtilsTest, ConvertToBool_NullPointer_ThrowsError_1943) {
    // Setup
    MockXMPUtils mockXMPUtils;
    const char* nullStr = nullptr;  // Null string pointer
    WXMP_Result result;

    // Expectation: Null pointer should throw an error
    EXPECT_THROW(WXMPUtils_ConvertToBool_1(nullStr, &result), XMP_Error);
}