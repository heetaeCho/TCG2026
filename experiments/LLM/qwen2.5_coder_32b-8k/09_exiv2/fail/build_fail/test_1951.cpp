#include <gtest/gtest.h>

#include "WXMPUtils.hpp"



// Fixture for WXMPUtils tests

class WXMPUtilsTest_1951 : public ::testing::Test {

protected:

    XMP_StringPtr encodedStr;

    XMP_StringLen encodedLen;

    XMP_StringPtr rawStr = nullptr;

    XMP_StringLen rawLen = 0;

    WXMP_Result wResult;



    void SetUp() override {

        // Initialize any necessary variables before each test

        encodedStr = "SGVsbG8gV29ybGQh"; // Base64 for "Hello World!"

        encodedLen = strlen(encodedStr);

    }



    void TearDown() override {

        // Clean up after each test

        if (rawStr != nullptr) {

            delete[] rawStr;

            rawStr = nullptr;

        }

        rawLen = 0;

    }

};



TEST_F(WXMPUtilsTest_1951, DecodeFromBase64_SuccessfulDecoding_1951) {

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);



    EXPECT_STREQ(rawStr, "Hello World!");

    EXPECT_EQ(rawLen, strlen("Hello World!"));

}



TEST_F(WXMPUtilsTest_1951, DecodeFromBase64_NullEncodedStr_1951) {

    encodedStr = nullptr;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);



    EXPECT_EQ(rawStr, voidStringPtr);

    EXPECT_EQ(rawLen, 0);

}



TEST_F(WXMPUtilsTest_1951, DecodeFromBase64_ZeroEncodedLen_1951) {

    encodedLen = 0;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);



    EXPECT_EQ(rawStr, voidStringPtr);

    EXPECT_EQ(rawLen, 0);

}



TEST_F(WXMPUtilsTest_1951, DecodeFromBase64_NullRawStrPointer_1951) {

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, nullptr, &rawLen, &wResult);



    EXPECT_EQ(rawStr, voidStringPtr);

    EXPECT_EQ(rawLen, 0);

}



TEST_F(WXMPUtilsTest_1951, DecodeFromBase64_NullRawLenPointer_1951) {

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, nullptr, &wResult);



    EXPECT_STREQ(rawStr, "Hello World!");

}



TEST_F(WXMPUtilsTest_1951, DecodeFromBase64_InvalidBase64String_1951) {

    encodedStr = "InvalidBase64";

    encodedLen = strlen(encodedStr);

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);



    EXPECT_EQ(rawStr, voidStringPtr);

    EXPECT_EQ(rawLen, 0);

}
