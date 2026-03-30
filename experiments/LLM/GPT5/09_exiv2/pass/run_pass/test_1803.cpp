#include <gtest/gtest.h>
#include <cstring>

// Assuming the code to test is in the Exiv2 namespace
namespace Exiv2 {
    extern const char base64_encode[64];
    int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize);
}

// Test class to test the base64encode function
class Base64EncodeTest_1803 : public ::testing::Test {};

// Normal Operation: Test with a basic valid input.
TEST_F(Base64EncodeTest_1803, EncodeBasicInput_1803) {
    const char input[] = "Hello";
    char result[16];  // Just enough space to hold the base64 result.
    int rc = Exiv2::base64encode(input, std::strlen(input), result, sizeof(result));
    ASSERT_EQ(rc, 1);  // Ensure the function succeeded.
    ASSERT_STREQ(result, "SGVsbG8=");  // The expected base64 encoding of "Hello".
}

// Boundary Condition: Test with an empty input string.
TEST_F(Base64EncodeTest_1803, EncodeEmptyInput_1804) {
    const char input[] = "";
    char result[16];  // Just enough space to hold the base64 result.
    int rc = Exiv2::base64encode(input, 0, result, sizeof(result));
    ASSERT_EQ(rc, 1);  // Ensure the function succeeded.
    ASSERT_STREQ(result, "");  // An empty input should return an empty result.
}

// Boundary Condition: Test with input data that is a single byte.
TEST_F(Base64EncodeTest_1803, EncodeSingleByte_1805) {
    const char input[] = "A";
    char result[16];
    int rc = Exiv2::base64encode(input, std::strlen(input), result, sizeof(result));
    ASSERT_EQ(rc, 1);  // Ensure the function succeeded.
    ASSERT_STREQ(result, "QQ==");  // The expected base64 encoding of "A".
}

// Boundary Condition: Test with input data that is exactly three bytes.
TEST_F(Base64EncodeTest_1803, EncodeThreeBytes_1806) {
    const char input[] = "ABC";
    char result[16];
    int rc = Exiv2::base64encode(input, std::strlen(input), result, sizeof(result));
    ASSERT_EQ(rc, 1);  // Ensure the function succeeded.
    ASSERT_STREQ(result, "QUJD");  // The expected base64 encoding of "ABC".
}

// Exceptional Case: Test when the result buffer is too small to hold the base64 output.
TEST_F(Base64EncodeTest_1803, EncodeInsufficientBuffer_1807) {
    const char input[] = "Hello";
    char result[5];  // Too small buffer.
    int rc = Exiv2::base64encode(input, std::strlen(input), result, sizeof(result));
    ASSERT_EQ(rc, 0);  // The function should fail due to insufficient buffer.
}

// Exceptional Case: Test with null input data.
TEST_F(Base64EncodeTest_1803, EncodeNullInput_1808) {
    char result[16];
    int rc = Exiv2::base64encode(nullptr, 0, result, sizeof(result));
    ASSERT_EQ(rc, 0);  // The function should fail as the input buffer is null.
}

// Exceptional Case: Test with null result buffer.
TEST_F(Base64EncodeTest_1803, EncodeNullResultBuffer_1809) {
    const char input[] = "Hello";
    int rc = Exiv2::base64encode(input, std::strlen(input), nullptr, 0);
    ASSERT_EQ(rc, 0);  // The function should fail as the result buffer is null.
}

// Boundary Condition: Test with maximum length of input that fits within result size.
TEST_F(Base64EncodeTest_1803, EncodeMaxLengthInput_1810) {
    const char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char result[64];  // A buffer large enough to hold the base64 encoding.
    int rc = Exiv2::base64encode(input, std::strlen(input), result, sizeof(result));
    ASSERT_EQ(rc, 1);  // Ensure the function succeeded.
    ASSERT_STRNE(result, "");  // The result should not be empty.
}

// Boundary Condition: Test with input data that is two bytes, ensuring padding works correctly.
TEST_F(Base64EncodeTest_1803, EncodeTwoBytes_1811) {
    const char input[] = "AB";
    char result[16];
    int rc = Exiv2::base64encode(input, std::strlen(input), result, sizeof(result));
    ASSERT_EQ(rc, 1);  // Ensure the function succeeded.
    ASSERT_STREQ(result, "QUI=");  // The expected base64 encoding of "AB".
}