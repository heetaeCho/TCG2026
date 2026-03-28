#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <vector>
#include <string_view>

// Include the headers for the function to be tested
#include "./TestProjects/poppler/poppler/UTF.h"
#include "./TestProjects/poppler/poppler/PDFDocEncoding.h"

// Test Fixture for TextStringToUCS4
class TextStringToUCS4Test_1521 : public ::testing::Test {
protected:
    // Setup code can go here if necessary
    void SetUp() override {}

    // Cleanup code can go here if necessary
    void TearDown() override {}
};

// Test case for normal operation (non-UTF-16 encoded text)
TEST_F(TextStringToUCS4Test_1521, NonUTF16TextConversion_1521) {
    std::string_view textStr = "Hello";

    std::vector<Unicode> result = TextStringToUCS4(textStr);

    // Check that the conversion matches the expected output
    ASSERT_EQ(result.size(), textStr.size());
    for (size_t i = 0; i < textStr.size(); ++i) {
        ASSERT_EQ(result[i], pdfDocEncoding[textStr[i] & 0xff]);
    }
}

// Test case for handling an empty input string
TEST_F(TextStringToUCS4Test_1521, EmptyString_1521) {
    std::string_view textStr = "";

    std::vector<Unicode> result = TextStringToUCS4(textStr);

    // Expect an empty result
    ASSERT_TRUE(result.empty());
}

// Test case for detecting and converting UTF-16 big-endian (Unicode) input
TEST_F(TextStringToUCS4Test_1521, UTF16BigEndianConversion_1521) {
    // Example UTF-16 encoded string (big-endian)
    std::string_view textStr = "\xFE\xFF\x00\x48\x00\x65\x00\x6C\x00\x6C\x00\x6F"; // "Hello"

    std::vector<Unicode> result = TextStringToUCS4(textStr);

    // Expected output: UTF-16 characters converted to UCS4
    std::vector<Unicode> expected = { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F }; // "Hello"
    ASSERT_EQ(result, expected);
}

// Test case for detecting and converting UTF-16 little-endian (UnicodeLE) input
TEST_F(TextStringToUCS4Test_1521, UTF16LittleEndianConversion_1521) {
    // Example UTF-16 encoded string (little-endian)
    std::string_view textStr = "\xFF\xFE\x48\x00\x65\x00\x6C\x00\x6C\x00\x6F\x00"; // "Hello"

    std::vector<Unicode> result = TextStringToUCS4(textStr);

    // Expected output: UTF-16 characters converted to UCS4
    std::vector<Unicode> expected = { 0x0048, 0x0065, 0x006C, 0x006C, 0x006F }; // "Hello"
    ASSERT_EQ(result, expected);
}

// Test case for handling input with no byte order mark (not UTF-16)
TEST_F(TextStringToUCS4Test_1521, NoBOMTextConversion_1521) {
    std::string_view textStr = "World";

    std::vector<Unicode> result = TextStringToUCS4(textStr);

    // Check that the conversion uses the pdfDocEncoding table
    ASSERT_EQ(result.size(), textStr.size());
    for (size_t i = 0; i < textStr.size(); ++i) {
        ASSERT_EQ(result[i], pdfDocEncoding[textStr[i] & 0xff]);
    }
}

// Test case for boundary condition: very large string input
TEST_F(TextStringToUCS4Test_1521, LargeInputTextConversion_1521) {
    std::string_view textStr(10000, 'A');  // 10,000 'A' characters

    std::vector<Unicode> result = TextStringToUCS4(textStr);

    // Ensure the result has the correct number of entries
    ASSERT_EQ(result.size(), textStr.size());

    // Verify the conversion for the 'A' character
    for (size_t i = 0; i < textStr.size(); ++i) {
        ASSERT_EQ(result[i], pdfDocEncoding['A']);
    }
}

// Test case for boundary condition: handling an invalid character or unexpected behavior
TEST_F(TextStringToUCS4Test_1521, InvalidCharacterHandling_1521) {
    std::string_view textStr = "\xFF\xFF";  // Invalid byte sequence

    std::vector<Unicode> result = TextStringToUCS4(textStr);

    // Expect the result to be empty or handled as an error (could depend on implementation)
    ASSERT_TRUE(result.empty());
}