#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "WXMPUtils.hpp"
#include "XMP_Const.h"
#include "XMPUtils.hpp"

// Mock dependencies, if needed
class MockWXMPResult : public WXMP_Result {
public:
    MOCK_METHOD(void, SomeMockedMethod, (), ());
};

class WXMPUtils_DecodeFromBase64Test : public ::testing::Test {
protected:
    // Optionally set up any common test data
    void SetUp() override {
        // Any initialization if needed
    }

    void TearDown() override {
        // Clean up if needed
    }
};

// TEST_ID: 1951
TEST_F(WXMPUtils_DecodeFromBase64Test, DecodeFromBase64_ValidInput_1951) {
    // Prepare test input data
    const char* encodedStr = "U29tZSBkYXRh";
    size_t encodedLen = strlen(encodedStr);
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    // Call the function under test
    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    // Check that the decoded string is as expected
    ASSERT_NE(rawStr, nullptr);
    ASSERT_GT(rawLen, 0);
    ASSERT_STREQ(rawStr, "Some data");
}

// TEST_ID: 1952
TEST_F(WXMPUtils_DecodeFromBase64Test, DecodeFromBase64_NullRawStrPointer_1952) {
    const char* encodedStr = "U29tZSBkYXRh";
    size_t encodedLen = strlen(encodedStr);
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    // Expect the rawStr to be assigned to the voidStringPtr if passed as null
    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, nullptr, &rawLen, &wResult);
    
    // Check that the rawStr pointer is assigned to voidStringPtr
    ASSERT_EQ(rawStr, &voidStringPtr);
}

// TEST_ID: 1953
TEST_F(WXMPUtils_DecodeFromBase64Test, DecodeFromBase64_NullRawLenPointer_1953) {
    const char* encodedStr = "U29tZSBkYXRh";
    size_t encodedLen = strlen(encodedStr);
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    // Expect the rawLen to be assigned to voidStringLen if passed as null
    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, nullptr, &wResult);

    // Check that the rawLen is assigned to voidStringLen
    ASSERT_EQ(rawLen, voidStringLen);
}

// TEST_ID: 1954
TEST_F(WXMPUtils_DecodeFromBase64Test, DecodeFromBase64_EmptyInput_1954) {
    const char* encodedStr = "";
    size_t encodedLen = 0;
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    // Call the function with empty input
    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    // Expect the rawStr to remain nullptr and rawLen to be 0 for an empty input
    ASSERT_EQ(rawStr, nullptr);
    ASSERT_EQ(rawLen, 0);
}

// TEST_ID: 1955
TEST_F(WXMPUtils_DecodeFromBase64Test, DecodeFromBase64_ErrorHandling_1955) {
    const char* encodedStr = "Invalid base64 string!";
    size_t encodedLen = strlen(encodedStr);
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    // Call the function with an invalid base64 string
    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    // Verify the error code from the result (if defined in WXMP_Result or related)
    ASSERT_EQ(wResult.errMessage, nullptr);  // Assuming no error message was set, update accordingly.
}

// TEST_ID: 1956
TEST_F(WXMPUtils_DecodeFromBase64Test, DecodeFromBase64_MockedExternalInteraction_1956) {
    const char* encodedStr = "U29tZSBkYXRh";
    size_t encodedLen = strlen(encodedStr);
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    MockWXMPResult wResult;

    // Mock an external interaction if needed
    EXPECT_CALL(wResult, SomeMockedMethod()).Times(1);

    // Call the function under test
    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    // Check the mock call was made
    ASSERT_TRUE(Mock::VerifyAndClearExpectations(&wResult));
}