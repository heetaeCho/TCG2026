#include <gtest/gtest.h>
#include <string>

// Forward declaration of the function under test
std::string pdfDocEncodingToUTF16(const std::string &orig);

// We need access to the pdfDocEncoding table used internally.
// Since we're treating the implementation as a black box, we test observable behavior.

class PdfDocEncodingToUTF16Test_1511 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that an empty string produces only the BOM (byte order mark)
TEST_F(PdfDocEncodingToUTF16Test_1511, EmptyStringProducesBOM_1511) {
    std::string result = pdfDocEncodingToUTF16("");
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
}

// Test that a single ASCII character produces BOM + 2 bytes
TEST_F(PdfDocEncodingToUTF16Test_1511, SingleAsciiCharacter_1511) {
    std::string result = pdfDocEncodingToUTF16("A");
    ASSERT_EQ(result.size(), 4u);
    // BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // 'A' is U+0041, so high byte = 0x00, low byte = 0x41
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x41);
}

// Test that multiple ASCII characters are correctly encoded
TEST_F(PdfDocEncodingToUTF16Test_1511, MultipleAsciiCharacters_1511) {
    std::string input = "Hello";
    std::string result = pdfDocEncodingToUTF16(input);
    // Expected size: 2 (BOM) + 2 * 5 = 12
    ASSERT_EQ(result.size(), 12u);
    // BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // 'H' = U+0048
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x48);
    // 'e' = U+0065
    EXPECT_EQ(static_cast<unsigned char>(result[4]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[5]), 0x65);
    // 'l' = U+006C
    EXPECT_EQ(static_cast<unsigned char>(result[6]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[7]), 0x6C);
    // 'l' = U+006C
    EXPECT_EQ(static_cast<unsigned char>(result[8]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[9]), 0x6C);
    // 'o' = U+006F
    EXPECT_EQ(static_cast<unsigned char>(result[10]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[11]), 0x6F);
}

// Test output size is always 2 + 2 * input.size()
TEST_F(PdfDocEncodingToUTF16Test_1511, OutputSizeIsCorrect_1511) {
    for (size_t len = 0; len <= 10; ++len) {
        std::string input(len, 'x');
        std::string result = pdfDocEncodingToUTF16(input);
        EXPECT_EQ(result.size(), 2 + 2 * len) << "Failed for input length " << len;
    }
}

// Test null byte (0x00) in input
TEST_F(PdfDocEncodingToUTF16Test_1511, NullByteInInput_1511) {
    std::string input(1, '\0');
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 4u);
    // BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // PDFDocEncoding for 0x00 should map to U+0000
    // (though exact mapping depends on the table, for code point 0 it's typically 0)
}

// Test space character (0x20)
TEST_F(PdfDocEncodingToUTF16Test_1511, SpaceCharacter_1511) {
    std::string result = pdfDocEncodingToUTF16(" ");
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // Space U+0020
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x20);
}

// Test digit characters
TEST_F(PdfDocEncodingToUTF16Test_1511, DigitCharacters_1511) {
    std::string result = pdfDocEncodingToUTF16("0");
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x30); // '0' = U+0030
}

// Test BOM is always present at the start
TEST_F(PdfDocEncodingToUTF16Test_1511, BOMAlwaysPresent_1511) {
    std::string inputs[] = {"", "a", "test", "12345"};
    for (const auto &input : inputs) {
        std::string result = pdfDocEncodingToUTF16(input);
        ASSERT_GE(result.size(), 2u);
        EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE) << "BOM high byte failed for input: " << input;
        EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF) << "BOM low byte failed for input: " << input;
    }
}

// Test high-bit characters (0x80-0xFF range) - these may map to non-ASCII Unicode
// PDFDocEncoding has specific mappings for 0x80-0xFF range
TEST_F(PdfDocEncodingToUTF16Test_1511, HighBitCharacter_0xA9_Copyright_1511) {
    // In PDFDocEncoding, 0xA9 maps to U+00A9 (©)
    std::string input(1, '\xA9');
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0xA9);
}

// Test character 0x7F (DEL) - in standard ASCII this is a control character
TEST_F(PdfDocEncodingToUTF16Test_1511, DelCharacter_1511) {
    std::string input(1, '\x7F');
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 4u);
    // We just verify the output is 4 bytes (BOM + one UTF-16 code unit)
}

// Test PDFDocEncoding specific mapping: 0x80 maps to U+2022 (BULLET)
TEST_F(PdfDocEncodingToUTF16Test_1511, Byte0x80MapsToBullet_1511) {
    std::string input(1, '\x80');
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 4u);
    // PDFDocEncoding 0x80 = U+2022 (BULLET)
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x20);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x22);
}

// Test PDFDocEncoding specific mapping: 0x93 maps to U+201C (LEFT DOUBLE QUOTATION MARK)
TEST_F(PdfDocEncodingToUTF16Test_1511, Byte0x93MapsToLeftDoubleQuote_1511) {
    std::string input(1, '\x93');
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 4u);
    // PDFDocEncoding 0x93 = U+201C
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x20);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x1C);
}

// Test PDFDocEncoding specific mapping: 0x94 maps to U+201D (RIGHT DOUBLE QUOTATION MARK)
TEST_F(PdfDocEncodingToUTF16Test_1511, Byte0x94MapsToRightDoubleQuote_1511) {
    std::string input(1, '\x94');
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 4u);
    // PDFDocEncoding 0x94 = U+201D
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x20);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x1D);
}

// Test a longer string to verify all positions are encoded
TEST_F(PdfDocEncodingToUTF16Test_1511, LongerStringAllPositionsEncoded_1511) {
    std::string input = "ABCDEFGHIJ";
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 22u); // 2 + 2*10

    for (int i = 0; i < 10; i++) {
        unsigned char expected_low = static_cast<unsigned char>(input[i]);
        EXPECT_EQ(static_cast<unsigned char>(result[2 + 2 * i]), 0x00)
            << "High byte mismatch at position " << i;
        EXPECT_EQ(static_cast<unsigned char>(result[2 + 2 * i + 1]), expected_low)
            << "Low byte mismatch at position " << i;
    }
}

// Test that the function handles all printable ASCII characters correctly
TEST_F(PdfDocEncodingToUTF16Test_1511, AllPrintableAscii_1511) {
    for (unsigned char c = 0x20; c < 0x7F; c++) {
        std::string input(1, static_cast<char>(c));
        std::string result = pdfDocEncodingToUTF16(input);
        ASSERT_EQ(result.size(), 4u) << "Size mismatch for char " << (int)c;
        // For standard ASCII range (0x20-0x7E), PDFDocEncoding maps directly to Unicode
        EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00) << "High byte for char " << (int)c;
        EXPECT_EQ(static_cast<unsigned char>(result[3]), c) << "Low byte for char " << (int)c;
    }
}

// Test PDFDocEncoding: 0xAD maps to U+00AD (SOFT HYPHEN)
TEST_F(PdfDocEncodingToUTF16Test_1511, Byte0xAD_SoftHyphen_1511) {
    std::string input(1, '\xAD');
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 4u);
    // In PDFDocEncoding, 0xAD should map to U+00AD
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0xAD);
}

// Test string with mixed ASCII and high-byte characters
TEST_F(PdfDocEncodingToUTF16Test_1511, MixedAsciiAndHighByte_1511) {
    std::string input;
    input.push_back('A');        // 0x41 -> U+0041
    input.push_back('\x80');     // 0x80 -> U+2022
    input.push_back('Z');        // 0x5A -> U+005A
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 8u); // 2 + 2*3

    // 'A'
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x41);
    // 0x80 -> BULLET U+2022
    EXPECT_EQ(static_cast<unsigned char>(result[4]), 0x20);
    EXPECT_EQ(static_cast<unsigned char>(result[5]), 0x22);
    // 'Z'
    EXPECT_EQ(static_cast<unsigned char>(result[6]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[7]), 0x5A);
}

// Test single character boundary: 0xFF
TEST_F(PdfDocEncodingToUTF16Test_1511, Byte0xFF_1511) {
    std::string input(1, '\xFF');
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 4u);
    // PDFDocEncoding 0xFF = U+00FF (LATIN SMALL LETTER Y WITH DIAERESIS)
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0xFF);
}

// Test single character: 0x01
TEST_F(PdfDocEncodingToUTF16Test_1511, Byte0x01_1511) {
    std::string input(1, '\x01');
    std::string result = pdfDocEncodingToUTF16(input);
    ASSERT_EQ(result.size(), 4u);
    // Just verify size and structure - exact mapping depends on table
}
