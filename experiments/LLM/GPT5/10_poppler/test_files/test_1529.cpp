#include <gtest/gtest.h>
#include <gmock/gmock.h>

// The provided function from the codebase
int utf16CountUtf8Bytes(const uint16_t *utf16);

// TEST CASES FOR utf16CountUtf8Bytes

// Test normal operation with a basic string of valid UTF-16 characters
TEST_F(UTF16Test_1529, BasicUtf16Encoding_1529) {
    uint16_t input[] = {0x0061, 0x0062, 0x0063, 0};  // "abc"
    int result = utf16CountUtf8Bytes(input);
    EXPECT_EQ(result, 3);  // "abc" -> 3 bytes in UTF-8
}

// Test with multi-byte characters
TEST_F(UTF16Test_1530, MultiByteUtf16Encoding_1530) {
    uint16_t input[] = {0x00E9, 0};  // "é" (U+00E9, 2 bytes in UTF-8)
    int result = utf16CountUtf8Bytes(input);
    EXPECT_EQ(result, 2);  // "é" -> 2 bytes in UTF-8
}

// Test with a character that will be replaced by the replacement character
TEST_F(UTF16Test_1531, ReplacementCharacter_1531) {
    uint16_t input[] = {0xD800, 0};  // Invalid UTF-16, invalid surrogate pair
    int result = utf16CountUtf8Bytes(input);
    EXPECT_EQ(result, 3);  // Replacement character in UTF-8: 3 bytes
}

// Test with a character exceeding the valid UCS4 range
TEST_F(UTF16Test_1532, ExceedingUCS4Max_1532) {
    uint16_t input[] = {0x110000, 0};  // Code point exceeding UCS4_MAX
    int result = utf16CountUtf8Bytes(input);
    EXPECT_EQ(result, 3);  // Replacement character, 3 bytes in UTF-8
}

// Test with a string that contains a mix of valid and invalid UTF-16 characters
TEST_F(UTF16Test_1533, MixedValidAndInvalidUtf16_1533) {
    uint16_t input[] = {0x0061, 0xD800, 0x0062, 0};  // "a" + invalid + "b"
    int result = utf16CountUtf8Bytes(input);
    EXPECT_EQ(result, 6);  // "a" -> 1 byte, invalid -> replacement (3 bytes), "b" -> 1 byte
}

// Test edge case with an empty string
TEST_F(UTF16Test_1534, EmptyUtf16String_1534) {
    uint16_t input[] = {0};  // Empty string
    int result = utf16CountUtf8Bytes(input);
    EXPECT_EQ(result, 0);  // Empty string should result in 0 bytes
}

// Test boundary condition with the largest valid UTF-16 character (U+10FFFF)
TEST_F(UTF16Test_1535, LargestUtf16Character_1535) {
    uint16_t input[] = {0xD800, 0xDFFF, 0};  // Surrogate pair for U+10FFFF
    int result = utf16CountUtf8Bytes(input);
    EXPECT_EQ(result, 4);  // U+10FFFF -> 4 bytes in UTF-8
}

// Test with an invalid surrogate pair
TEST_F(UTF16Test_1536, InvalidSurrogatePair_1536) {
    uint16_t input[] = {0xD800, 0};  // Only one half of the surrogate pair
    int result = utf16CountUtf8Bytes(input);
    EXPECT_EQ(result, 3);  // Should be replaced by the replacement character (3 bytes in UTF-8)
}

// Test when all characters are valid ASCII
TEST_F(UTF16Test_1537, AllAsciiUtf16Characters_1537) {
    uint16_t input[] = {0x0041, 0x0042, 0x0043, 0};  // "ABC"
    int result = utf16CountUtf8Bytes(input);
    EXPECT_EQ(result, 3);  // "ABC" -> 3 bytes in UTF-8
}

// Test boundary condition with a character at the upper limit of UCS4_MAX
TEST_F(UTF16Test_1538, MaxUtf16Character_1538) {
    uint16_t input[] = {0x10FFFF, 0};  // U+10FFFF (valid Unicode character)
    int result = utf16CountUtf8Bytes(input);
    EXPECT_EQ(result, 4);  // U+10FFFF -> 4 bytes in UTF-8
}