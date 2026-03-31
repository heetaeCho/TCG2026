#include <gtest/gtest.h>
#include <QString>
#include <string>

// Forward declare the function we're testing
namespace Poppler {
QString UnicodeParsedString(const std::string &s1);
}

class UnicodeParsedStringTest_1283 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test empty string returns empty QString
TEST_F(UnicodeParsedStringTest_1283, EmptyStringReturnsEmptyQString_1283)
{
    std::string empty;
    QString result = Poppler::UnicodeParsedString(empty);
    EXPECT_TRUE(result.isEmpty());
    EXPECT_EQ(result, QString());
}

// Test string with Unicode BOM (Big Endian: 0xFE 0xFF)
TEST_F(UnicodeParsedStringTest_1283, UnicodeBOMBigEndian_1283)
{
    // UTF-16 BE BOM followed by 'A' (0x00 0x41)
    std::string input;
    input.push_back(static_cast<char>(0xFE));
    input.push_back(static_cast<char>(0xFF));
    input.push_back(static_cast<char>(0x00));
    input.push_back(static_cast<char>(0x41));
    
    QString result = Poppler::UnicodeParsedString(input);
    // The result should contain something parseable from UTF-16
    EXPECT_FALSE(result.isEmpty());
}

// Test string with Unicode BOM (Little Endian: 0xFF 0xFE)
TEST_F(UnicodeParsedStringTest_1283, UnicodeBOMLittleEndian_1283)
{
    // UTF-16 LE BOM followed by 'A' (0x41 0x00)
    std::string input;
    input.push_back(static_cast<char>(0xFF));
    input.push_back(static_cast<char>(0xFE));
    input.push_back(static_cast<char>(0x41));
    input.push_back(static_cast<char>(0x00));
    
    QString result = Poppler::UnicodeParsedString(input);
    EXPECT_FALSE(result.isEmpty());
}

// Test plain ASCII string (no BOM) - should go through PDFDocEncoding path
TEST_F(UnicodeParsedStringTest_1283, PlainAsciiString_1283)
{
    std::string input = "Hello";
    QString result = Poppler::UnicodeParsedString(input);
    EXPECT_FALSE(result.isEmpty());
    EXPECT_EQ(result, QString("Hello"));
}

// Test single character ASCII
TEST_F(UnicodeParsedStringTest_1283, SingleCharacterAscii_1283)
{
    std::string input = "A";
    QString result = Poppler::UnicodeParsedString(input);
    EXPECT_FALSE(result.isEmpty());
    EXPECT_EQ(result, QString("A"));
}

// Test string with only BOM (Big Endian) and no actual content
TEST_F(UnicodeParsedStringTest_1283, OnlyBOMBigEndianNoContent_1283)
{
    std::string input;
    input.push_back(static_cast<char>(0xFE));
    input.push_back(static_cast<char>(0xFF));
    
    QString result = Poppler::UnicodeParsedString(input);
    // Only BOM, no actual characters - the BOM itself is interpreted as one UTF-16 char
    // Result may or may not be empty depending on how BOM is handled
    // We just verify it doesn't crash
    SUCCEED();
}

// Test string with only BOM (Little Endian) and no actual content
TEST_F(UnicodeParsedStringTest_1283, OnlyBOMLittleEndianNoContent_1283)
{
    std::string input;
    input.push_back(static_cast<char>(0xFF));
    input.push_back(static_cast<char>(0xFE));
    
    QString result = Poppler::UnicodeParsedString(input);
    // Just verify no crash
    SUCCEED();
}

// Test PDFDocEncoding path with various characters
TEST_F(UnicodeParsedStringTest_1283, PDFDocEncodingPath_1283)
{
    // Characters that are valid in PDFDocEncoding but don't have a BOM
    std::string input = "Test 123";
    QString result = Poppler::UnicodeParsedString(input);
    EXPECT_EQ(result, QString("Test 123"));
}

// Test that a string starting with 0xFE but not followed by 0xFF
// goes through PDFDocEncoding path
TEST_F(UnicodeParsedStringTest_1283, FalsePositiveBOM_FEOnly_1283)
{
    std::string input;
    input.push_back(static_cast<char>(0xFE));
    input.push_back(static_cast<char>(0x41)); // Not 0xFF, so not a BOM
    
    QString result = Poppler::UnicodeParsedString(input);
    // Should go through PDFDocEncoding, not crash
    EXPECT_FALSE(result.isEmpty());
}

// Test that a string starting with 0xFF but not followed by 0xFE
// goes through PDFDocEncoding path
TEST_F(UnicodeParsedStringTest_1283, FalsePositiveBOM_FFOnly_1283)
{
    std::string input;
    input.push_back(static_cast<char>(0xFF));
    input.push_back(static_cast<char>(0x41)); // Not 0xFE, so not a LE BOM
    
    QString result = Poppler::UnicodeParsedString(input);
    // Should go through PDFDocEncoding, not crash
    EXPECT_FALSE(result.isEmpty());
}

// Test with odd-length string in BOM path (Big Endian)
TEST_F(UnicodeParsedStringTest_1283, OddLengthWithBOMBE_1283)
{
    std::string input;
    input.push_back(static_cast<char>(0xFE));
    input.push_back(static_cast<char>(0xFF));
    input.push_back(static_cast<char>(0x00));
    input.push_back(static_cast<char>(0x41));
    input.push_back(static_cast<char>(0x00)); // Odd byte
    
    QString result = Poppler::UnicodeParsedString(input);
    // size / 2 = 2 (integer division), so only BOM + 'A' should be parsed
    // Just verify no crash
    SUCCEED();
}

// Test with multiple UTF-16 BE characters
TEST_F(UnicodeParsedStringTest_1283, MultipleUTF16BECharacters_1283)
{
    std::string input;
    // BOM
    input.push_back(static_cast<char>(0xFE));
    input.push_back(static_cast<char>(0xFF));
    // 'H' = 0x0048
    input.push_back(static_cast<char>(0x00));
    input.push_back(static_cast<char>(0x48));
    // 'i' = 0x0069
    input.push_back(static_cast<char>(0x00));
    input.push_back(static_cast<char>(0x69));
    
    QString result = Poppler::UnicodeParsedString(input);
    EXPECT_FALSE(result.isEmpty());
}

// Test with longer plain ASCII string
TEST_F(UnicodeParsedStringTest_1283, LongerAsciiString_1283)
{
    std::string input = "The quick brown fox jumps over the lazy dog";
    QString result = Poppler::UnicodeParsedString(input);
    EXPECT_EQ(result, QString("The quick brown fox jumps over the lazy dog"));
}

// Test with numeric-only string
TEST_F(UnicodeParsedStringTest_1283, NumericString_1283)
{
    std::string input = "1234567890";
    QString result = Poppler::UnicodeParsedString(input);
    EXPECT_EQ(result, QString("1234567890"));
}

// Test single byte string (length 1) - goes through PDFDocEncoding
TEST_F(UnicodeParsedStringTest_1283, SingleByteString_1283)
{
    std::string input(1, 'X');
    QString result = Poppler::UnicodeParsedString(input);
    EXPECT_FALSE(result.isEmpty());
}

// Test with spaces only
TEST_F(UnicodeParsedStringTest_1283, SpacesOnlyString_1283)
{
    std::string input = "   ";
    QString result = Poppler::UnicodeParsedString(input);
    EXPECT_EQ(result, QString("   "));
}

// Test with null bytes in non-BOM string
TEST_F(UnicodeParsedStringTest_1283, NullBytesInString_1283)
{
    std::string input;
    input.push_back('A');
    input.push_back('\0');
    input.push_back('B');
    
    QString result = Poppler::UnicodeParsedString(input);
    // The string has embedded nulls - PDFDocEncoding path
    // Just verify no crash
    SUCCEED();
}

// Test with high byte values that aren't BOMs (PDFDocEncoding special chars)
TEST_F(UnicodeParsedStringTest_1283, HighByteValuesPDFDocEncoding_1283)
{
    std::string input;
    input.push_back(static_cast<char>(0x80));
    input.push_back(static_cast<char>(0x90));
    input.push_back(static_cast<char>(0xA0));
    
    QString result = Poppler::UnicodeParsedString(input);
    // PDFDocEncoding maps these to specific Unicode characters
    EXPECT_FALSE(result.isEmpty());
}
