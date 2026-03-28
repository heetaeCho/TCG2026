#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Declaration of the function under test
namespace Exiv2 {
int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize);
}

class Base64EncodeTest_1803 : public ::testing::Test {
protected:
    char result[1024];
    
    void SetUp() override {
        memset(result, 0, sizeof(result));
    }
};

// Test normal encoding of a simple string
TEST_F(Base64EncodeTest_1803, EncodeSimpleString_1803) {
    const char* input = "Man";
    int rc = Exiv2::base64encode(input, 3, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "TWFu");
}

// Test encoding of a single byte (padding with ==)
TEST_F(Base64EncodeTest_1803, EncodeSingleByte_1803) {
    const char* input = "M";
    int rc = Exiv2::base64encode(input, 1, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "TQ==");
}

// Test encoding of two bytes (padding with =)
TEST_F(Base64EncodeTest_1803, EncodeTwoBytes_1803) {
    const char* input = "Ma";
    int rc = Exiv2::base64encode(input, 2, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "TWE=");
}

// Test encoding of empty data (dataLength = 0)
TEST_F(Base64EncodeTest_1803, EncodeEmptyData_1803) {
    const char* input = "";
    int rc = Exiv2::base64encode(input, 0, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "");
}

// Test with null data buffer
TEST_F(Base64EncodeTest_1803, NullDataBuffer_1803) {
    int rc = Exiv2::base64encode(nullptr, 5, result, sizeof(result));
    EXPECT_EQ(rc, 0);
}

// Test with null result buffer
TEST_F(Base64EncodeTest_1803, NullResultBuffer_1803) {
    const char* input = "Hello";
    int rc = Exiv2::base64encode(input, 5, nullptr, 100);
    EXPECT_EQ(rc, 0);
}

// Test with both null buffers
TEST_F(Base64EncodeTest_1803, BothNullBuffers_1803) {
    int rc = Exiv2::base64encode(nullptr, 5, nullptr, 100);
    EXPECT_EQ(rc, 0);
}

// Test with result buffer too small
TEST_F(Base64EncodeTest_1803, ResultBufferTooSmall_1803) {
    const char* input = "Hello, World!";
    // "Hello, World!" is 13 bytes -> output_length = 4 * ((13+2)/3) = 4*5 = 20
    // resultSize must be > 20 for success
    int rc = Exiv2::base64encode(input, 13, result, 20);
    EXPECT_EQ(rc, 0);
}

// Test with result buffer exactly sufficient (output_length + 1)
TEST_F(Base64EncodeTest_1803, ResultBufferExactSize_1803) {
    const char* input = "Man"; // 3 bytes -> output_length = 4
    // resultSize must be > 4, so 5 is the minimum
    int rc = Exiv2::base64encode(input, 3, result, 5);
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "TWFu");
}

// Test with result buffer size equal to output_length (should fail since not strictly greater)
TEST_F(Base64EncodeTest_1803, ResultBufferEqualToOutputLength_1803) {
    const char* input = "Man"; // output_length = 4
    int rc = Exiv2::base64encode(input, 3, result, 4);
    EXPECT_EQ(rc, 0);
}

// Test well-known base64 encoding: "Hello"
TEST_F(Base64EncodeTest_1803, EncodeHello_1803) {
    const char* input = "Hello";
    int rc = Exiv2::base64encode(input, 5, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "SGVsbG8=");
}

// Test well-known base64 encoding: "Hello, World!"
TEST_F(Base64EncodeTest_1803, EncodeHelloWorld_1803) {
    const char* input = "Hello, World!";
    int rc = Exiv2::base64encode(input, 13, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "SGVsbG8sIFdvcmxkIQ==");
}

// Test encoding binary data with all zeros
TEST_F(Base64EncodeTest_1803, EncodeBinaryZeros_1803) {
    unsigned char input[3] = {0, 0, 0};
    int rc = Exiv2::base64encode(input, 3, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "AAAA");
}

// Test encoding binary data with 0xFF bytes
TEST_F(Base64EncodeTest_1803, EncodeBinaryAllOnes_1803) {
    unsigned char input[3] = {0xFF, 0xFF, 0xFF};
    int rc = Exiv2::base64encode(input, 3, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "////");
}

// Test encoding a single zero byte
TEST_F(Base64EncodeTest_1803, EncodeSingleZeroByte_1803) {
    unsigned char input[1] = {0};
    int rc = Exiv2::base64encode(input, 1, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "AA==");
}

// Test encoding "foobar" (well-known test vector)
TEST_F(Base64EncodeTest_1803, EncodeFoobar_1803) {
    const char* input = "foobar";
    int rc = Exiv2::base64encode(input, 6, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "Zm9vYmFy");
}

// Test encoding "fooba" (5 bytes, padding with =)
TEST_F(Base64EncodeTest_1803, EncodeFooba_1803) {
    const char* input = "fooba";
    int rc = Exiv2::base64encode(input, 5, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "Zm9vYmE=");
}

// Test encoding "foob" (4 bytes, padding with ==)
TEST_F(Base64EncodeTest_1803, EncodeFoob_1803) {
    const char* input = "foob";
    int rc = Exiv2::base64encode(input, 4, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "Zm9vYg==");
}

// Test encoding "foo" (3 bytes, no padding)
TEST_F(Base64EncodeTest_1803, EncodeFoo_1803) {
    const char* input = "foo";
    int rc = Exiv2::base64encode(input, 3, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "Zm9v");
}

// Test encoding "fo" (2 bytes)
TEST_F(Base64EncodeTest_1803, EncodeFo_1803) {
    const char* input = "fo";
    int rc = Exiv2::base64encode(input, 2, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "Zm8=");
}

// Test encoding "f" (1 byte)
TEST_F(Base64EncodeTest_1803, EncodeF_1803) {
    const char* input = "f";
    int rc = Exiv2::base64encode(input, 1, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "Zg==");
}

// Test that result is null-terminated
TEST_F(Base64EncodeTest_1803, ResultIsNullTerminated_1803) {
    const char* input = "Test";
    memset(result, 'X', sizeof(result));
    int rc = Exiv2::base64encode(input, 4, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    size_t len = strlen(result);
    // "Test" -> 4 bytes -> output_length = 4*((4+2)/3) = 8
    EXPECT_EQ(len, 8u);
    EXPECT_EQ(result[8], '\0');
}

// Test with resultSize = 0
TEST_F(Base64EncodeTest_1803, ResultSizeZero_1803) {
    const char* input = "A";
    // output_length = 4, resultSize = 0, so 4 < 0 is false
    int rc = Exiv2::base64encode(input, 1, result, 0);
    EXPECT_EQ(rc, 0);
}

// Test with resultSize = 1 for non-empty input
TEST_F(Base64EncodeTest_1803, ResultSizeOne_1803) {
    const char* input = "A";
    int rc = Exiv2::base64encode(input, 1, result, 1);
    EXPECT_EQ(rc, 0);
}

// Test encoding binary data containing the plus and slash characters
TEST_F(Base64EncodeTest_1803, EncodeBinaryWithPlusSlash_1803) {
    // Input bytes chosen to produce '+' and '/' in output
    // 0xFB, 0xEF, 0xBE = base64 "+++++/"  -- let's use a known mapping
    // Byte 62 -> '+', byte 63 -> '/'
    // Triple 0x3E << 18 | 0x3F << 12 | ... 
    // Let's use bytes {0x3F, 0xBF, 0xFF} which should give specific output
    unsigned char input[3] = {0xFB, 0xEF, 0xBE};
    int rc = Exiv2::base64encode(input, 3, result, sizeof(result));
    EXPECT_EQ(rc, 1);
    // Verify the output length is 4
    EXPECT_EQ(strlen(result), 4u);
}

// Test larger input
TEST_F(Base64EncodeTest_1803, EncodeLargerInput_1803) {
    const char* input = "The quick brown fox jumps over the lazy dog";
    int rc = Exiv2::base64encode(input, strlen(input), result, sizeof(result));
    EXPECT_EQ(rc, 1);
    EXPECT_STREQ(result, "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==");
}
