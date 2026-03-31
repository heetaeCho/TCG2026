#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <vector>
#include "UTF.h"
#include "PDFDocEncoding.h"

// Helper to create a string with Unicode BOM (Big Endian: 0xFE 0xFF)
static std::string makeUnicodeBE(const std::vector<uint16_t>& codepoints) {
    std::string result;
    result.push_back(static_cast<char>(0xFE));
    result.push_back(static_cast<char>(0xFF));
    for (auto cp : codepoints) {
        result.push_back(static_cast<char>((cp >> 8) & 0xFF));
        result.push_back(static_cast<char>(cp & 0xFF));
    }
    return result;
}

// Helper to create a string with Unicode LE BOM (0xFF 0xFE)
static std::string makeUnicodeLE(const std::vector<uint16_t>& codepoints) {
    std::string result;
    result.push_back(static_cast<char>(0xFF));
    result.push_back(static_cast<char>(0xFE));
    for (auto cp : codepoints) {
        result.push_back(static_cast<char>(cp & 0xFF));
        result.push_back(static_cast<char>((cp >> 8) & 0xFF));
    }
    return result;
}

class TextStringToUCS4Test_1521 : public ::testing::Test {
protected:
};

// Test empty string returns empty vector
TEST_F(TextStringToUCS4Test_1521, EmptyString_1521) {
    std::string_view empty("");
    auto result = TextStringToUCS4(empty);
    EXPECT_TRUE(result.empty());
}

// Test PDFDocEncoding path with a simple ASCII string
TEST_F(TextStringToUCS4Test_1521, PDFDocEncodingSimpleASCII_1521) {
    std::string input = "Hello";
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 5u);
    for (size_t i = 0; i < input.size(); i++) {
        EXPECT_EQ(result[i], pdfDocEncoding[static_cast<unsigned char>(input[i])]);
    }
}

// Test PDFDocEncoding with a single character
TEST_F(TextStringToUCS4Test_1521, PDFDocEncodingSingleChar_1521) {
    std::string input = "A";
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], pdfDocEncoding[0x41]);
}

// Test Unicode Big Endian BOM with simple characters
TEST_F(TextStringToUCS4Test_1521, UnicodeBESimple_1521) {
    // 'A' = U+0041, 'B' = U+0042
    std::string input = makeUnicodeBE({0x0041, 0x0042});
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 0x0041u);
    EXPECT_EQ(result[1], 0x0042u);
}

// Test Unicode Little Endian BOM with simple characters
TEST_F(TextStringToUCS4Test_1521, UnicodeLESimple_1521) {
    // 'A' = U+0041, 'B' = U+0042
    std::string input = makeUnicodeLE({0x0041, 0x0042});
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 0x0041u);
    EXPECT_EQ(result[1], 0x0042u);
}

// Test Unicode BE BOM only (no actual characters after BOM) -> should return empty
TEST_F(TextStringToUCS4Test_1521, UnicodeBEBOMOnly_1521) {
    std::string input;
    input.push_back(static_cast<char>(0xFE));
    input.push_back(static_cast<char>(0xFF));
    auto result = TextStringToUCS4(std::string_view(input));
    EXPECT_TRUE(result.empty());
}

// Test Unicode LE BOM only (no actual characters after BOM) -> should return empty
TEST_F(TextStringToUCS4Test_1521, UnicodeLEBOMOnly_1521) {
    std::string input;
    input.push_back(static_cast<char>(0xFF));
    input.push_back(static_cast<char>(0xFE));
    auto result = TextStringToUCS4(std::string_view(input));
    EXPECT_TRUE(result.empty());
}

// Test Unicode BE with odd byte count (BOM + 3 bytes -> len/2 - 1 = 1)
TEST_F(TextStringToUCS4Test_1521, UnicodeBEOddByteCount_1521) {
    std::string input;
    input.push_back(static_cast<char>(0xFE));
    input.push_back(static_cast<char>(0xFF));
    input.push_back(static_cast<char>(0x00));
    input.push_back(static_cast<char>(0x41));
    input.push_back(static_cast<char>(0x00)); // trailing odd byte
    auto result = TextStringToUCS4(std::string_view(input));
    // len = 5, len/2 - 1 = 1, so one character should be decoded
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x0041u);
}

// Test Unicode BE with a single character
TEST_F(TextStringToUCS4Test_1521, UnicodeBESingleChar_1521) {
    std::string input = makeUnicodeBE({0x0048}); // 'H'
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x0048u);
}

// Test Unicode LE with a single character
TEST_F(TextStringToUCS4Test_1521, UnicodeLESingleChar_1521) {
    std::string input = makeUnicodeLE({0x0048}); // 'H'
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0x0048u);
}

// Test Unicode BE with non-ASCII BMP characters
TEST_F(TextStringToUCS4Test_1521, UnicodeBENonASCII_1521) {
    // U+00E9 (é), U+4E2D (中), U+00FC (ü)
    std::string input = makeUnicodeBE({0x00E9, 0x4E2D, 0x00FC});
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 0x00E9u);
    EXPECT_EQ(result[1], 0x4E2Du);
    EXPECT_EQ(result[2], 0x00FCu);
}

// Test Unicode LE with non-ASCII BMP characters
TEST_F(TextStringToUCS4Test_1521, UnicodeLENonASCII_1521) {
    std::string input = makeUnicodeLE({0x00E9, 0x4E2D, 0x00FC});
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 0x00E9u);
    EXPECT_EQ(result[1], 0x4E2Du);
    EXPECT_EQ(result[2], 0x00FCu);
}

// Test Unicode BE with surrogate pair (U+1F600 = D83D DE00)
TEST_F(TextStringToUCS4Test_1521, UnicodeBESurrogatePair_1521) {
    // U+1F600 encoded as UTF-16 surrogate pair: 0xD83D, 0xDE00
    std::string input = makeUnicodeBE({0xD83D, 0xDE00});
    auto result = TextStringToUCS4(std::string_view(input));
    // UTF16toUCS4 should combine the surrogate pair into one codepoint
    ASSERT_GE(result.size(), 1u);
    EXPECT_EQ(result[0], 0x1F600u);
}

// Test Unicode LE with surrogate pair
TEST_F(TextStringToUCS4Test_1521, UnicodeLESurrogatePair_1521) {
    std::string input = makeUnicodeLE({0xD83D, 0xDE00});
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_GE(result.size(), 1u);
    EXPECT_EQ(result[0], 0x1F600u);
}

// Test PDFDocEncoding with high byte values
TEST_F(TextStringToUCS4Test_1521, PDFDocEncodingHighByte_1521) {
    std::string input;
    input.push_back(static_cast<char>(0x80));
    input.push_back(static_cast<char>(0xFF));
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], pdfDocEncoding[0x80]);
    EXPECT_EQ(result[1], pdfDocEncoding[0xFF]);
}

// Test PDFDocEncoding with null byte in middle
TEST_F(TextStringToUCS4Test_1521, PDFDocEncodingNullByte_1521) {
    std::string input;
    input.push_back('A');
    input.push_back('\0');
    input.push_back('B');
    auto result = TextStringToUCS4(std::string_view(input.data(), 3));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], pdfDocEncoding[0x41]);
    EXPECT_EQ(result[1], pdfDocEncoding[0x00]);
    EXPECT_EQ(result[2], pdfDocEncoding[0x42]);
}

// Test that a string starting with 0xFE but not 0xFF as second byte is PDFDocEncoding
TEST_F(TextStringToUCS4Test_1521, NotUnicodeBOMFalseStart_1521) {
    std::string input;
    input.push_back(static_cast<char>(0xFE));
    input.push_back(static_cast<char>(0x00)); // not 0xFF, so not a BOM
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], pdfDocEncoding[0xFE]);
    EXPECT_EQ(result[1], pdfDocEncoding[0x00]);
}

// Test that a string starting with 0xFF but not 0xFE as second byte is PDFDocEncoding
TEST_F(TextStringToUCS4Test_1521, NotUnicodeLEBOMFalseStart_1521) {
    std::string input;
    input.push_back(static_cast<char>(0xFF));
    input.push_back(static_cast<char>(0x00)); // not 0xFE, so not a LE BOM
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], pdfDocEncoding[0xFF]);
    EXPECT_EQ(result[1], pdfDocEncoding[0x00]);
}

// Test single byte string
TEST_F(TextStringToUCS4Test_1521, SingleByteString_1521) {
    std::string input;
    input.push_back(static_cast<char>(0xFE));
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], pdfDocEncoding[0xFE]);
}

// Test Unicode BE with BOM + 1 extra byte (3 bytes total, len/2-1 = 0) -> empty
TEST_F(TextStringToUCS4Test_1521, UnicodeBEBOMPlusOneByte_1521) {
    std::string input;
    input.push_back(static_cast<char>(0xFE));
    input.push_back(static_cast<char>(0xFF));
    input.push_back(static_cast<char>(0x00));
    // len = 3, len/2 = 1, len/2 - 1 = 0 -> empty
    auto result = TextStringToUCS4(std::string_view(input));
    EXPECT_TRUE(result.empty());
}

// Test Unicode BE with multiple characters including high values
TEST_F(TextStringToUCS4Test_1521, UnicodeBEMultipleChars_1521) {
    std::string input = makeUnicodeBE({0x0041, 0x0042, 0x0043, 0x0044, 0x0045});
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 0x0041u);
    EXPECT_EQ(result[1], 0x0042u);
    EXPECT_EQ(result[2], 0x0043u);
    EXPECT_EQ(result[3], 0x0044u);
    EXPECT_EQ(result[4], 0x0045u);
}

// Test PDFDocEncoding for all printable ASCII
TEST_F(TextStringToUCS4Test_1521, PDFDocEncodingPrintableASCII_1521) {
    std::string input;
    for (int i = 0x20; i < 0x7F; i++) {
        input.push_back(static_cast<char>(i));
    }
    auto result = TextStringToUCS4(std::string_view(input));
    ASSERT_EQ(result.size(), input.size());
    for (size_t i = 0; i < input.size(); i++) {
        EXPECT_EQ(result[i], pdfDocEncoding[static_cast<unsigned char>(input[i])]);
    }
}
