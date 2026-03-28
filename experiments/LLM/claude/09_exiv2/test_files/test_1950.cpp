#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#define XMP_INCLUDE_XMPFILES 0

#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPUtils_EncodeToBase64_1(
    XMP_StringPtr rawStr,
    XMP_StringLen rawLen,
    XMP_StringPtr * encodedStr,
    XMP_StringLen * encodedLen,
    WXMP_Result * wResult);

// We also need XMPUtils for initialization
#include "XMPUtils.hpp"
#include "XMPCore_Impl.hpp"

class WXMPUtilsEncodeToBase64Test_1950 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP SDK
        XMPUtils::Initialize();
    }

    static void TearDownTestSuite() {
        XMPUtils::Terminate();
    }

    void SetUp() override {
        memset(&result, 0, sizeof(result));
        result.errMessage = nullptr;
        encodedStr = nullptr;
        encodedLen = 0;
    }

    WXMP_Result result;
    XMP_StringPtr encodedStr;
    XMP_StringLen encodedLen;
};

// Test encoding an empty string
TEST_F(WXMPUtilsEncodeToBase64Test_1950, EmptyStringEncodesSuccessfully_1950) {
    const char* rawStr = "";
    XMP_StringLen rawLen = 0;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(encodedLen, 0u);
}

// Test encoding a simple known string "A"
TEST_F(WXMPUtilsEncodeToBase64Test_1950, SingleCharEncode_1950) {
    const char* rawStr = "A";
    XMP_StringLen rawLen = 1;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(encodedStr, nullptr);
    // "A" in Base64 is "QQ=="
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "QQ==");
}

// Test encoding "Hello" - a well-known Base64 test vector
TEST_F(WXMPUtilsEncodeToBase64Test_1950, HelloStringEncode_1950) {
    const char* rawStr = "Hello";
    XMP_StringLen rawLen = 5;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(encodedStr, nullptr);
    // "Hello" in Base64 is "SGVsbG8="
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "SGVsbG8=");
}

// Test encoding "Man" - no padding needed
TEST_F(WXMPUtilsEncodeToBase64Test_1950, ThreeCharNoPadding_1950) {
    const char* rawStr = "Man";
    XMP_StringLen rawLen = 3;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(encodedStr, nullptr);
    // "Man" in Base64 is "TWFu"
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "TWFu");
}

// Test encoding two characters - single padding
TEST_F(WXMPUtilsEncodeToBase64Test_1950, TwoCharSinglePadding_1950) {
    const char* rawStr = "Ma";
    XMP_StringLen rawLen = 2;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(encodedStr, nullptr);
    // "Ma" in Base64 is "TWE="
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "TWE=");
}

// Test encoding one character - double padding
TEST_F(WXMPUtilsEncodeToBase64Test_1950, OneCharDoublePadding_1950) {
    const char* rawStr = "M";
    XMP_StringLen rawLen = 1;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(encodedStr, nullptr);
    // "M" in Base64 is "TQ=="
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "TQ==");
}

// Test with null encodedStr pointer (should use voidStringPtr internally)
TEST_F(WXMPUtilsEncodeToBase64Test_1950, NullEncodedStrPointer_1950) {
    const char* rawStr = "test";
    XMP_StringLen rawLen = 4;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, nullptr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    // encodedLen should still be set
    EXPECT_GT(encodedLen, 0u);
}

// Test with null encodedLen pointer (should use voidStringLen internally)
TEST_F(WXMPUtilsEncodeToBase64Test_1950, NullEncodedLenPointer_1950) {
    const char* rawStr = "test";
    XMP_StringLen rawLen = 4;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, nullptr, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(encodedStr, nullptr);
}

// Test with both null output pointers
TEST_F(WXMPUtilsEncodeToBase64Test_1950, BothOutputPointersNull_1950) {
    const char* rawStr = "test";
    XMP_StringLen rawLen = 4;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, nullptr, nullptr, &result);

    EXPECT_EQ(result.errMessage, nullptr);
}

// Test encoding binary data with null bytes
TEST_F(WXMPUtilsEncodeToBase64Test_1950, BinaryDataWithNullBytes_1950) {
    const char rawStr[] = {'\x00', '\x01', '\x02', '\x03'};
    XMP_StringLen rawLen = 4;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(encodedStr, nullptr);
    EXPECT_GT(encodedLen, 0u);
    // {0x00, 0x01, 0x02, 0x03} in Base64 is "AAECAw=="
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "AAECAw==");
}

// Test encoding a longer string
TEST_F(WXMPUtilsEncodeToBase64Test_1950, LongerStringEncode_1950) {
    const char* rawStr = "Base64 encoding test string for validation";
    XMP_StringLen rawLen = static_cast<XMP_StringLen>(strlen(rawStr));

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(encodedStr, nullptr);
    EXPECT_GT(encodedLen, rawLen); // Base64 is always longer than raw
}

// Test that encoded length is approximately 4/3 of raw length (plus padding/newlines)
TEST_F(WXMPUtilsEncodeToBase64Test_1950, EncodedLengthIsReasonable_1950) {
    const char* rawStr = "Hello, World!";
    XMP_StringLen rawLen = static_cast<XMP_StringLen>(strlen(rawStr));

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    // Base64 output length should be ceil(rawLen/3)*4 (possibly with line breaks)
    // At minimum it should be >= ceil(13/3)*4 = 20
    EXPECT_GE(encodedLen, 20u);
}

// Test encoding all 256 byte values
TEST_F(WXMPUtilsEncodeToBase64Test_1950, AllByteValues_1950) {
    char rawStr[256];
    for (int i = 0; i < 256; i++) {
        rawStr[i] = static_cast<char>(i);
    }
    XMP_StringLen rawLen = 256;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(encodedStr, nullptr);
    EXPECT_GT(encodedLen, 0u);
}

// Test WXMP_Result is properly initialized and no error for valid input
TEST_F(WXMPUtilsEncodeToBase64Test_1950, ResultStructNoError_1950) {
    const char* rawStr = "abc";
    XMP_StringLen rawLen = 3;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    // "abc" in Base64 is "YWJj"
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "YWJj");
}

// Test encoding exactly 3 bytes (exact multiple, no padding)
TEST_F(WXMPUtilsEncodeToBase64Test_1950, ExactMultipleOfThree_1950) {
    const char* rawStr = "abc";
    XMP_StringLen rawLen = 3;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    std::string encoded(encodedStr, encodedLen);
    // Should not have padding characters
    EXPECT_EQ(encoded.find('='), std::string::npos);
}

// Test encoding 6 bytes (exact multiple of 3)
TEST_F(WXMPUtilsEncodeToBase64Test_1950, SixBytesNoPadding_1950) {
    const char* rawStr = "abcdef";
    XMP_StringLen rawLen = 6;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "YWJjZGVm");
}

// Test encoding known RFC 4648 test vectors
TEST_F(WXMPUtilsEncodeToBase64Test_1950, RFC4648TestVector_f_1950) {
    const char* rawStr = "f";
    XMP_StringLen rawLen = 1;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "Zg==");
}

TEST_F(WXMPUtilsEncodeToBase64Test_1950, RFC4648TestVector_fo_1950) {
    const char* rawStr = "fo";
    XMP_StringLen rawLen = 2;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "Zm8=");
}

TEST_F(WXMPUtilsEncodeToBase64Test_1950, RFC4648TestVector_foo_1950) {
    const char* rawStr = "foo";
    XMP_StringLen rawLen = 3;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "Zm9v");
}

TEST_F(WXMPUtilsEncodeToBase64Test_1950, RFC4648TestVector_foob_1950) {
    const char* rawStr = "foob";
    XMP_StringLen rawLen = 4;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "Zm9vYg==");
}

TEST_F(WXMPUtilsEncodeToBase64Test_1950, RFC4648TestVector_fooba_1950) {
    const char* rawStr = "fooba";
    XMP_StringLen rawLen = 5;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "Zm9vYmE=");
}

TEST_F(WXMPUtilsEncodeToBase64Test_1950, RFC4648TestVector_foobar_1950) {
    const char* rawStr = "foobar";
    XMP_StringLen rawLen = 6;

    WXMPUtils_EncodeToBase64_1(rawStr, rawLen, &encodedStr, &encodedLen, &result);

    EXPECT_EQ(result.errMessage, nullptr);
    std::string encoded(encodedStr, encodedLen);
    EXPECT_EQ(encoded, "Zm9vYmFy");
}
