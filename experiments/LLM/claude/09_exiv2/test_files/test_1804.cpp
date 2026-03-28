#include <gtest/gtest.h>
#include <cstring>

// Declaration of the function under test
namespace Exiv2 {
size_t base64decode(const char* in, char* out, size_t out_size);
}

class Base64DecodeTest_1804 : public ::testing::Test {
protected:
    char out[1024];
    
    void SetUp() override {
        memset(out, 0, sizeof(out));
    }
};

// Test null input returns 0
TEST_F(Base64DecodeTest_1804, NullInput_1804) {
    size_t result = Exiv2::base64decode(nullptr, out, sizeof(out));
    EXPECT_EQ(result, 0u);
}

// Test empty string input returns 0
TEST_F(Base64DecodeTest_1804, EmptyInput_1804) {
    size_t result = Exiv2::base64decode("", out, sizeof(out));
    EXPECT_EQ(result, 0u);
}

// Test input with length not multiple of 4 returns 0
TEST_F(Base64DecodeTest_1804, InputLengthNotMultipleOf4_1804) {
    size_t result = Exiv2::base64decode("abc", out, sizeof(out));
    EXPECT_EQ(result, 0u);
}

// Test input with length not multiple of 4 (5 chars) returns 0
TEST_F(Base64DecodeTest_1804, InputLength5_1804) {
    size_t result = Exiv2::base64decode("abcde", out, sizeof(out));
    EXPECT_EQ(result, 0u);
}

// Test simple base64 decode: "TWFu" -> "Man"
TEST_F(Base64DecodeTest_1804, DecodeMan_1804) {
    size_t result = Exiv2::base64decode("TWFu", out, sizeof(out));
    EXPECT_EQ(result, 3u);
    EXPECT_STREQ(out, "Man");
}

// Test base64 decode with one padding: "TWE=" -> "Ma"
TEST_F(Base64DecodeTest_1804, DecodeWithOnePadding_1804) {
    size_t result = Exiv2::base64decode("TWE=", out, sizeof(out));
    EXPECT_EQ(result, 2u);
    EXPECT_STREQ(out, "Ma");
}

// Test base64 decode with two paddings: "TQ==" -> "M"
TEST_F(Base64DecodeTest_1804, DecodeWithTwoPaddings_1804) {
    size_t result = Exiv2::base64decode("TQ==", out, sizeof(out));
    EXPECT_EQ(result, 1u);
    EXPECT_STREQ(out, "M");
}

// Test decoding "SGVsbG8gV29ybGQ=" -> "Hello World"
TEST_F(Base64DecodeTest_1804, DecodeHelloWorld_1804) {
    size_t result = Exiv2::base64decode("SGVsbG8gV29ybGQ=", out, sizeof(out));
    EXPECT_EQ(result, 11u);
    EXPECT_STREQ(out, "Hello World");
}

// Test decoding "QUJD" -> "ABC"
TEST_F(Base64DecodeTest_1804, DecodeABC_1804) {
    size_t result = Exiv2::base64decode("QUJD", out, sizeof(out));
    EXPECT_EQ(result, 3u);
    EXPECT_STREQ(out, "ABC");
}

// Test output buffer too small returns 0
TEST_F(Base64DecodeTest_1804, OutputBufferTooSmall_1804) {
    // "TWFu" decodes to "Man" (3 bytes), need at least 4 bytes (3 + 1 for null)
    // output_length + 1 < out_size needs to hold, so out_size must be > 4
    // With out_size=4, output_length+1 = 4 which is NOT < 4, so should return 0
    size_t result = Exiv2::base64decode("TWFu", out, 4);
    EXPECT_EQ(result, 0u);
}

// Test output buffer exactly sufficient
TEST_F(Base64DecodeTest_1804, OutputBufferExactlySufficient_1804) {
    // "TWFu" -> "Man" (3 bytes), output_length=3, need output_length+1 < out_size
    // so out_size must be > 4, i.e., at least 5
    size_t result = Exiv2::base64decode("TWFu", out, 5);
    EXPECT_EQ(result, 3u);
    EXPECT_STREQ(out, "Man");
}

// Test output buffer size 0 returns 0
TEST_F(Base64DecodeTest_1804, OutputBufferSizeZero_1804) {
    size_t result = Exiv2::base64decode("TWFu", out, 0);
    EXPECT_EQ(result, 0u);
}

// Test output buffer size 1 returns 0 (even for smallest valid decode)
TEST_F(Base64DecodeTest_1804, OutputBufferSizeOne_1804) {
    // "TQ==" -> "M" (1 byte), need output_length+1 < out_size => 2 < out_size => out_size >= 3
    size_t result = Exiv2::base64decode("TQ==", out, 1);
    EXPECT_EQ(result, 0u);
}

// Test single character decode with sufficient buffer
TEST_F(Base64DecodeTest_1804, SingleCharDecodeWithSufficientBuffer_1804) {
    // "TQ==" -> "M" (1 byte), need out_size > 2
    size_t result = Exiv2::base64decode("TQ==", out, 3);
    EXPECT_EQ(result, 1u);
    EXPECT_EQ(out[0], 'M');
    EXPECT_EQ(out[1], '\0');
}

// Test longer string decode
TEST_F(Base64DecodeTest_1804, DecodeLongerString_1804) {
    // "YWJjZGVmZw==" -> "abcdefg"
    size_t result = Exiv2::base64decode("YWJjZGVmZw==", out, sizeof(out));
    EXPECT_EQ(result, 7u);
    EXPECT_STREQ(out, "abcdefg");
}

// Test decode with plus and slash characters
TEST_F(Base64DecodeTest_1804, DecodeWithSpecialChars_1804) {
    // Base64 for binary data containing characters that use + and /
    // "//8=" decodes to 0xFF 0xFF (two bytes)
    size_t result = Exiv2::base64decode("//8=", out, sizeof(out));
    EXPECT_EQ(result, 2u);
    EXPECT_EQ(static_cast<unsigned char>(out[0]), 0xFF);
    EXPECT_EQ(static_cast<unsigned char>(out[1]), 0xFF);
}

// Test decode "AAAA" -> three null bytes
TEST_F(Base64DecodeTest_1804, DecodeAllZeros_1804) {
    size_t result = Exiv2::base64decode("AAAA", out, sizeof(out));
    EXPECT_EQ(result, 3u);
    EXPECT_EQ(out[0], '\0');
    EXPECT_EQ(out[1], '\0');
    EXPECT_EQ(out[2], '\0');
}

// Test null termination of output
TEST_F(Base64DecodeTest_1804, OutputIsNullTerminated_1804) {
    memset(out, 'X', sizeof(out));
    size_t result = Exiv2::base64decode("TWFu", out, sizeof(out));
    EXPECT_EQ(result, 3u);
    EXPECT_EQ(out[3], '\0');
}

// Test return value matches string length
TEST_F(Base64DecodeTest_1804, ReturnValueMatchesOutputLength_1804) {
    // "dGVzdA==" -> "test" (4 bytes)
    size_t result = Exiv2::base64decode("dGVzdA==", out, sizeof(out));
    EXPECT_EQ(result, 4u);
    EXPECT_EQ(strlen(out), result);
    EXPECT_STREQ(out, "test");
}

// Test multiple blocks
TEST_F(Base64DecodeTest_1804, MultipleBlocks_1804) {
    // "SGVsbG8=" -> "Hello"
    size_t result = Exiv2::base64decode("SGVsbG8=", out, sizeof(out));
    EXPECT_EQ(result, 5u);
    EXPECT_STREQ(out, "Hello");
}

// Test 8 chars input no padding: "YWJjZGVm" -> "abcdef"
TEST_F(Base64DecodeTest_1804, EightCharsNoPadding_1804) {
    size_t result = Exiv2::base64decode("YWJjZGVm", out, sizeof(out));
    EXPECT_EQ(result, 6u);
    EXPECT_STREQ(out, "abcdef");
}

// Test that output_length + 1 boundary is respected (boundary case: out_size == output_length + 1)
TEST_F(Base64DecodeTest_1804, BoundaryOutSizeEqualOutputLengthPlusOne_1804) {
    // "TWFu" -> "Man" (3 bytes), output_length=3
    // output_length + 1 = 4, need 4 < out_size, so out_size=4 should fail
    size_t result = Exiv2::base64decode("TWFu", out, 4);
    EXPECT_EQ(result, 0u);
}

// Test input of exactly 4 characters with two padding
TEST_F(Base64DecodeTest_1804, FourCharsWithTwoPadding_1804) {
    // "AA==" -> single null byte
    size_t result = Exiv2::base64decode("AA==", out, sizeof(out));
    EXPECT_EQ(result, 1u);
    EXPECT_EQ(out[0], '\0');
}
