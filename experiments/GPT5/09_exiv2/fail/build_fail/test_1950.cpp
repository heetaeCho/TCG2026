#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "WXMPUtils.h"
#include "XMP_Const.h"
#include "XMPUtils.hpp"
#include "client-glue/WXMP_Common.hpp"

using ::testing::_;
using ::testing::Mock;

class WXMPUtilsTest : public ::testing::Test {
protected:
    // Setup and teardown if needed
    void SetUp() override {
        // Initialize any necessary components or reset the state
    }

    void TearDown() override {
        // Clean up if necessary
    }
};

// Test case for normal operation of WXMPUtils_EncodeToBase64_1
TEST_F(WXMPUtilsTest, EncodeToBase64_NormalOperation_1950) {
    const char* rawStr = "Test String";
    XMP_StringLen rawLen = strlen(rawStr);
    XMP_StringPtr encodedStr = nullptr;
    XMP_StringLen encodedLen = 0;
    WXMP_Result wResult;

    // Call the function
    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &wResult);

    // Check if the encoding was successful
    ASSERT_NE(encodedStr, nullptr);
    ASSERT_GT(encodedLen, 0);

    // Verify that the encoded string is correctly base64 encoded
    // (just as an example, you can decode the base64 to verify)
    // For this example, we'll just check if the encoded length is greater than 0.
    ASSERT_GT(encodedLen, 0);
}

// Test case for boundary condition where rawStr is an empty string
TEST_F(WXMPUtilsTest, EncodeToBase64_EmptyString_1951) {
    const char* rawStr = "";
    XMP_StringLen rawLen = 0;
    XMP_StringPtr encodedStr = nullptr;
    XMP_StringLen encodedLen = 0;
    WXMP_Result wResult;

    // Call the function with empty string
    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &wResult);

    // Assert that the encoded string is still valid
    ASSERT_NE(encodedStr, nullptr);
    ASSERT_EQ(encodedLen, 0); // No encoding should happen for empty string
}

// Test case for exceptional case when rawStr is null
TEST_F(WXMPUtilsTest, EncodeToBase64_NullString_1952) {
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    XMP_StringPtr encodedStr = nullptr;
    XMP_StringLen encodedLen = 0;
    WXMP_Result wResult;

    // Call the function with a null string
    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &wResult);

    // Assert that the encoded string is still valid
    ASSERT_EQ(encodedStr, nullptr);
    ASSERT_EQ(encodedLen, 0); // Encoding shouldn't happen with null input
}

// Test case for boundary condition where the input string is very long
TEST_F(WXMPUtilsTest, EncodeToBase64_LongString_1953) {
    const char* rawStr = "This is a long string to test the base64 encoding functionality. ";
    XMP_StringLen rawLen = strlen(rawStr);
    XMP_StringPtr encodedStr = nullptr;
    XMP_StringLen encodedLen = 0;
    WXMP_Result wResult;

    // Call the function with a long string
    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &wResult);

    // Check that the encoding is done and the encoded length is greater than 0
    ASSERT_NE(encodedStr, nullptr);
    ASSERT_GT(encodedLen, 0);
}

// Test case to verify the handling of WXMP_Result with an error message
TEST_F(WXMPUtilsTest, EncodeToBase64_ErrorResult_1954) {
    const char* rawStr = "Test String";
    XMP_StringLen rawLen = strlen(rawStr);
    XMP_StringPtr encodedStr = nullptr;
    XMP_StringLen encodedLen = 0;
    WXMP_Result wResult;

    // Force an error in the result (for testing purposes)
    wResult.errMessage = "Some error occurred";
    
    // Call the function with an error condition
    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &wResult);

    // Check that the error message is set correctly
    ASSERT_STREQ(wResult.errMessage, "Some error occurred");
}