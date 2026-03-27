#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string_view>

extern const uint32_t UTF8_ACCEPT;
extern const uint32_t UTF8_REJECT;
extern const uint32_t REPLACEMENT_CHAR;

std::vector<Unicode> utf8ToUCS4(std::string_view utf8);

// Test Case 1: Normal operation with valid UTF-8 string.
TEST_F(UTFTest_1524, ValidUTF8String_1524) {
    std::string_view utf8 = "hello";
    std::vector<Unicode> result = utf8ToUCS4(utf8);
    std::vector<Unicode> expected = {104, 101, 108, 108, 111}; // ASCII values for 'h', 'e', 'l', 'l', 'o'
    EXPECT_EQ(result, expected);
}

// Test Case 2: Handling of invalid UTF-8 characters.
TEST_F(UTFTest_1525, InvalidUTF8Character_1525) {
    std::string_view utf8 = "abc\xFF";  // Invalid byte 0xFF in the middle of the string
    std::vector<Unicode> result = utf8ToUCS4(utf8);
    std::vector<Unicode> expected = {97, 98, 99, REPLACEMENT_CHAR};  // 'a', 'b', 'c' followed by REPLACEMENT_CHAR
    EXPECT_EQ(result, expected);
}

// Test Case 3: Empty string should return an empty vector.
TEST_F(UTFTest_1526, EmptyString_1526) {
    std::string_view utf8 = "";
    std::vector<Unicode> result = utf8ToUCS4(utf8);
    std::vector<Unicode> expected = {};
    EXPECT_EQ(result, expected);
}

// Test Case 4: String with multi-byte characters.
TEST_F(UTFTest_1527, MultiByteCharacters_1527) {
    std::string_view utf8 = "\xE2\x9C\x94"; // Unicode check mark (U+2714)
    std::vector<Unicode> result = utf8ToUCS4(utf8);
    std::vector<Unicode> expected = {0x2714};  // Unicode code point for check mark
    EXPECT_EQ(result, expected);
}

// Test Case 5: Handling of incomplete UTF-8 sequence at the end.
TEST_F(UTFTest_1528, IncompleteUTF8Sequence_1528) {
    std::string_view utf8 = "abc\xC2";  // Incomplete multi-byte sequence
    std::vector<Unicode> result = utf8ToUCS4(utf8);
    std::vector<Unicode> expected = {97, 98, 99, REPLACEMENT_CHAR};  // 'a', 'b', 'c' followed by REPLACEMENT_CHAR
    EXPECT_EQ(result, expected);
}

// Test Case 6: Boundary case with a single valid UTF-8 character.
TEST_F(UTFTest_1529, SingleCharacterUTF8_1529) {
    std::string_view utf8 = "a";  // Single ASCII character
    std::vector<Unicode> result = utf8ToUCS4(utf8);
    std::vector<Unicode> expected = {97};  // ASCII value for 'a'
    EXPECT_EQ(result, expected);
}

// Test Case 7: Boundary case with a single invalid UTF-8 byte.
TEST_F(UTFTest_1530, SingleInvalidByte_1530) {
    std::string_view utf8 = "\xFF";  // Single invalid byte
    std::vector<Unicode> result = utf8ToUCS4(utf8);
    std::vector<Unicode> expected = {REPLACEMENT_CHAR};  // Replace invalid byte with REPLACEMENT_CHAR
    EXPECT_EQ(result, expected);
}

// Test Case 8: Check if function handles multi-byte sequence with invalid end.
TEST_F(UTFTest_1531, MultiByteInvalidEnd_1531) {
    std::string_view utf8 = "\xE2\x9C";  // Incomplete multi-byte sequence
    std::vector<Unicode> result = utf8ToUCS4(utf8);
    std::vector<Unicode> expected = {REPLACEMENT_CHAR};  // Replace with REPLACEMENT_CHAR
    EXPECT_EQ(result, expected);
}