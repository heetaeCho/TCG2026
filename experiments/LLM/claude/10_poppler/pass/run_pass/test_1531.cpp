#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <vector>

// Include the header that declares TextStringToUtf8
// We need to find the right header - based on the file path, it's likely in UTF.h
#include "UTF.h"

class TextStringToUtf8Test_1531 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with an empty string
TEST_F(TextStringToUtf8Test_1531, EmptyString_1531) {
    std::string input = "";
    std::string result = TextStringToUtf8(input);
    // Empty input should produce a result with just a null terminator
    // The result string should have size 1 (the null byte appended)
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], '\0');
}

// Test with a simple ASCII string (PDFDocEncoding path)
TEST_F(TextStringToUtf8Test_1531, SimpleAsciiString_1531) {
    std::string input = "Hello";
    std::string result = TextStringToUtf8(input);
    // For basic ASCII characters, PDFDocEncoding maps them to the same Unicode code points
    // Result should contain "Hello" followed by a null terminator
    EXPECT_GE(result.size(), 6u);
    EXPECT_EQ(result[0], 'H');
    EXPECT_EQ(result[1], 'e');
    EXPECT_EQ(result[2], 'l');
    EXPECT_EQ(result[3], 'l');
    EXPECT_EQ(result[4], 'o');
    EXPECT_EQ(result[5], '\0');
}

// Test with Unicode BOM (UTF-16BE) prefix - basic ASCII encoded as UTF-16BE
TEST_F(TextStringToUtf8Test_1531, UnicodeBomWithAscii_1531) {
    // Unicode BOM is 0xFE 0xFF
    std::string input;
    input += (char)0xFE;
    input += (char)0xFF;
    // "Hi" in UTF-16BE: H = 0x00 0x48, i = 0x00 0x69
    input += (char)0x00;
    input += (char)0x48;
    input += (char)0x00;
    input += (char)0x69;

    std::string result = TextStringToUtf8(input);
    // Should decode to "Hi" in UTF-8
    // Find the actual content before null terminator
    std::string content(result.c_str());
    EXPECT_EQ(content, "Hi");
}

// Test with Unicode BOM and empty content after BOM
TEST_F(TextStringToUtf8Test_1531, UnicodeBomEmptyContent_1531) {
    std::string input;
    input += (char)0xFE;
    input += (char)0xFF;

    std::string result = TextStringToUtf8(input);
    // len = 2/2 - 1 = 0, so no characters to process
    // Should be essentially empty (just null-terminated from utf16ToUtf8)
    std::string content(result.c_str());
    EXPECT_TRUE(content.empty());
}

// Test with single character in PDFDocEncoding
TEST_F(TextStringToUtf8Test_1531, SingleCharPdfDocEncoding_1531) {
    std::string input = "A";
    std::string result = TextStringToUtf8(input);
    EXPECT_GE(result.size(), 2u);
    EXPECT_EQ(result[0], 'A');
    EXPECT_EQ(result[1], '\0');
}

// Test Unicode BOM with a non-ASCII character (e.g., a character > 0x7F in UTF-16BE)
TEST_F(TextStringToUtf8Test_1531, UnicodeBomWithNonAscii_1531) {
    // Unicode BOM
    std::string input;
    input += (char)0xFE;
    input += (char)0xFF;
    // é (U+00E9) in UTF-16BE: 0x00 0xE9
    input += (char)0x00;
    input += (char)0xE9;

    std::string result = TextStringToUtf8(input);
    std::string content(result.c_str());
    // U+00E9 in UTF-8 is 0xC3 0xA9
    EXPECT_EQ(content, "\xC3\xA9");
}

// Test Unicode BOM with characters in the BMP above 0xFF
TEST_F(TextStringToUtf8Test_1531, UnicodeBomWithCjkCharacter_1531) {
    // Unicode BOM
    std::string input;
    input += (char)0xFE;
    input += (char)0xFF;
    // CJK character U+4E2D (中) in UTF-16BE: 0x4E 0x2D
    input += (char)0x4E;
    input += (char)0x2D;

    std::string result = TextStringToUtf8(input);
    std::string content(result.c_str());
    // U+4E2D in UTF-8 is 0xE4 0xB8 0xAD
    EXPECT_EQ(content, "\xE4\xB8\xAD");
}

// Test with only BOM bytes but odd length (BOM + 1 byte)
TEST_F(TextStringToUtf8Test_1531, UnicodeBomOddLength_1531) {
    std::string input;
    input += (char)0xFE;
    input += (char)0xFF;
    input += (char)0x00; // only one byte after BOM

    std::string result = TextStringToUtf8(input);
    // len = 3/2 - 1 = 0 (integer division), so no characters
    std::string content(result.c_str());
    EXPECT_TRUE(content.empty());
}

// Test PDFDocEncoding with bytes that might map to different Unicode characters
TEST_F(TextStringToUtf8Test_1531, PdfDocEncodingHighByte_1531) {
    // Use a byte that in PDFDocEncoding might map to a specific Unicode character
    // For example, byte 0x80 in PDFDocEncoding maps to U+2022 (bullet)
    // This tests the PDFDocEncoding lookup table
    std::string input;
    input += (char)0x80;
    std::string result = TextStringToUtf8(input);
    // We just verify we get some result of appropriate size (at least 2 bytes: one for char + null)
    EXPECT_GE(result.size(), 2u);
}

// Test with multiple characters through Unicode BOM path
TEST_F(TextStringToUtf8Test_1531, UnicodeBomMultipleCharacters_1531) {
    std::string input;
    input += (char)0xFE;
    input += (char)0xFF;
    // "ABC" in UTF-16BE
    input += (char)0x00; input += (char)0x41; // A
    input += (char)0x00; input += (char)0x42; // B
    input += (char)0x00; input += (char)0x43; // C

    std::string result = TextStringToUtf8(input);
    std::string content(result.c_str());
    EXPECT_EQ(content, "ABC");
}

// Test that a string starting with 0xFE but not followed by 0xFF goes through PDFDocEncoding
TEST_F(TextStringToUtf8Test_1531, FalseUnicodeBom_1531) {
    std::string input;
    input += (char)0xFE;
    input += (char)0x00; // Not 0xFF, so no BOM

    std::string result = TextStringToUtf8(input);
    // This should go through the PDFDocEncoding path
    // Result size should be len + 1 = 3
    EXPECT_EQ(result.size(), 3u);
}

// Test digits through PDFDocEncoding
TEST_F(TextStringToUtf8Test_1531, DigitsPdfDocEncoding_1531) {
    std::string input = "12345";
    std::string result = TextStringToUtf8(input);
    std::string content(result.c_str());
    EXPECT_EQ(content, "12345");
}

// Test Unicode BOM with surrogate pairs (characters outside BMP)
TEST_F(TextStringToUtf8Test_1531, UnicodeBomSurrogatePair_1531) {
    std::string input;
    input += (char)0xFE;
    input += (char)0xFF;
    // U+1F600 (😀) as surrogate pair: D83D DE00
    input += (char)0xD8; input += (char)0x3D;
    input += (char)0xDE; input += (char)0x00;

    std::string result = TextStringToUtf8(input);
    // Should produce a valid UTF-8 encoding of U+1F600
    // U+1F600 in UTF-8: F0 9F 98 80
    std::string content(result.c_str());
    EXPECT_FALSE(content.empty());
}

// Test PDFDocEncoding with all printable ASCII characters
TEST_F(TextStringToUtf8Test_1531, PrintableAsciiRange_1531) {
    std::string input;
    for (int i = 0x20; i < 0x7F; i++) {
        input += (char)i;
    }
    std::string result = TextStringToUtf8(input);
    // For printable ASCII, PDFDocEncoding should map to the same values
    for (int i = 0; i < (int)input.size(); i++) {
        EXPECT_EQ(result[i], input[i]) << "Mismatch at index " << i;
    }
}

// Test with string_view pointing to substring
TEST_F(TextStringToUtf8Test_1531, StringViewSubstring_1531) {
    std::string full = "XXHelloXX";
    std::string_view sv(full.data() + 2, 5); // "Hello"
    std::string result = TextStringToUtf8(sv);
    std::string content(result.c_str());
    EXPECT_EQ(content, "Hello");
}

// Test Unicode BOM with null characters in payload
TEST_F(TextStringToUtf8Test_1531, UnicodeBomWithNullInPayload_1531) {
    std::string input;
    input += (char)0xFE;
    input += (char)0xFF;
    // Null character U+0000 in UTF-16BE: 0x00 0x00
    input += (char)0x00;
    input += (char)0x00;

    std::string result = TextStringToUtf8(input);
    // The null character should be encoded; result should exist
    EXPECT_GE(result.size(), 1u);
}
