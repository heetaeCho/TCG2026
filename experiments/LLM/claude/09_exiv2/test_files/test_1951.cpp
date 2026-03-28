#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPCore_Impl.hpp"
#include "XMPUtils.hpp"

// Declaration of the function under test
extern "C" void WXMPUtils_DecodeFromBase64_1(
    XMP_StringPtr encodedStr,
    XMP_StringLen encodedLen,
    XMP_StringPtr * rawStr,
    XMP_StringLen * rawLen,
    WXMP_Result * wResult);

// We also need EncodeToBase64 for creating test data
extern "C" void WXMPUtils_EncodeToBase64_1(
    XMP_StringPtr rawStr,
    XMP_StringLen rawLen,
    XMP_StringPtr * encodedStr,
    XMP_StringLen * encodedLen,
    WXMP_Result * wResult);

class WXMPUtilsDecodeFromBase64Test_1951 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMPUtils is initialized
        XMPUtils::Initialize();
    }

    void TearDown() override {
        // Cleanup if needed
    }
};

// Test: Decode a simple base64-encoded string
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeSimpleBase64String_1951) {
    // "SGVsbG8=" is base64 for "Hello"
    const char* encodedStr = "SGVsbG8=";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error";
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(rawLen, 5u);
    EXPECT_EQ(std::string(rawStr, rawLen), "Hello");
}

// Test: Decode an empty base64 string
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeEmptyString_1951) {
    const char* encodedStr = "";
    XMP_StringLen encodedLen = 0;
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error for empty input";
    EXPECT_EQ(rawLen, 0u);
}

// Test: Decode with null rawStr pointer (should use voidStringPtr internally)
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeWithNullRawStrPointer_1951) {
    const char* encodedStr = "SGVsbG8=";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    // Pass null for rawStr - the function should handle it gracefully
    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, nullptr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error when rawStr is null";
    EXPECT_EQ(rawLen, 5u);
}

// Test: Decode with null rawLen pointer (should use voidStringLen internally)
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeWithNullRawLenPointer_1951) {
    const char* encodedStr = "SGVsbG8=";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringPtr rawStr = nullptr;
    WXMP_Result wResult;

    // Pass null for rawLen - the function should handle it gracefully
    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error when rawLen is null";
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(std::string(rawStr, 5), "Hello");
}

// Test: Decode with both null rawStr and rawLen pointers
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeWithBothNullOutputPointers_1951) {
    const char* encodedStr = "SGVsbG8=";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "Expected no error when both output pointers are null";
}

// Test: Decode base64 string with padding
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeBase64WithPadding_1951) {
    // "TWE=" is base64 for "Ma" (2 bytes, needs one padding char)
    const char* encodedStr = "TWE=";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(rawLen, 2u);
    EXPECT_EQ(std::string(rawStr, rawLen), "Ma");
}

// Test: Decode base64 string with double padding
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeBase64WithDoublePadding_1951) {
    // "TQ==" is base64 for "M" (1 byte, needs two padding chars)
    const char* encodedStr = "TQ==";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(rawLen, 1u);
    EXPECT_EQ(rawStr[0], 'M');
}

// Test: Decode base64 for longer string
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeLongerBase64String_1951) {
    // "SGVsbG8gV29ybGQh" is base64 for "Hello World!"
    const char* encodedStr = "SGVsbG8gV29ybGQh";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(rawLen, 12u);
    EXPECT_EQ(std::string(rawStr, rawLen), "Hello World!");
}

// Test: Decode base64 with no padding (multiple of 3 bytes input)
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeBase64NoPadding_1951) {
    // "QUJD" is base64 for "ABC" (exactly 3 bytes, no padding needed)
    const char* encodedStr = "QUJD";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(rawLen, 3u);
    EXPECT_EQ(std::string(rawStr, rawLen), "ABC");
}

// Test: Roundtrip - Encode then Decode should produce original
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, RoundtripEncodeDecode_1951) {
    const char* originalStr = "Test roundtrip data with special chars: !@#$%";
    XMP_StringLen originalLen = static_cast<XMP_StringLen>(std::strlen(originalStr));

    // Encode
    XMP_StringPtr encodedStr = nullptr;
    XMP_StringLen encodedLen = 0;
    WXMP_Result encResult;
    WXMPUtils_EncodeToBase64_1(originalStr, originalLen, &encodedStr, &encodedLen, &encResult);
    ASSERT_EQ(encResult.errMessage, nullptr) << "Encoding should succeed";

    // Decode
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result decResult;
    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &decResult);

    EXPECT_EQ(decResult.errMessage, nullptr) << "Decoding should succeed";
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(rawLen, originalLen);
    EXPECT_EQ(std::string(rawStr, rawLen), std::string(originalStr, originalLen));
}

// Test: Decode base64 encoding of binary data (all zero bytes)
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeBinaryZeroBytes_1951) {
    // "AAAA" is base64 for three zero bytes
    const char* encodedStr = "AAAA";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(rawLen, 3u);
    EXPECT_EQ(rawStr[0], '\0');
    EXPECT_EQ(rawStr[1], '\0');
    EXPECT_EQ(rawStr[2], '\0');
}

// Test: WXMP_Result is properly initialized with no error on success
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, ResultInitializedCorrectly_1951) {
    const char* encodedStr = "dGVzdA=="; // "test"
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(rawLen, 4u);
    EXPECT_EQ(std::string(rawStr, rawLen), "test");
}

// Test: Decode a single base64 quantum (4 chars -> 3 bytes)
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeSingleQuantum_1951) {
    // "/+8=" decodes to bytes 0xFF 0xEF
    const char* encodedStr = "/+8=";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(rawLen, 2u);
    EXPECT_EQ(static_cast<unsigned char>(rawStr[0]), 0xFF);
    EXPECT_EQ(static_cast<unsigned char>(rawStr[1]), 0xEF);
}

// Test: Decode base64 with all valid characters present
TEST_F(WXMPUtilsDecodeFromBase64Test_1951, DecodeAllBase64Characters_1951) {
    // Encode a string that uses many different byte values
    // "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" 
    // is a valid base64 string representing 48 bytes
    const char* encodedStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    XMP_StringLen encodedLen = static_cast<XMP_StringLen>(std::strlen(encodedStr));
    XMP_StringPtr rawStr = nullptr;
    XMP_StringLen rawLen = 0;
    WXMP_Result wResult;

    WXMPUtils_DecodeFromBase64_1(encodedStr, encodedLen, &rawStr, &rawLen, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    ASSERT_NE(rawStr, nullptr);
    EXPECT_EQ(rawLen, 48u);
}
