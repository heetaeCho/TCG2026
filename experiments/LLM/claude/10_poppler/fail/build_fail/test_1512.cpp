#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "GooString.h"
#include "UTF.h"

// Since convertToUtf16 is a static function in Form.cc, we need to include it
// or have it exposed for testing. We include the source to access the static function.
// In practice, this may require a test-specific build configuration.
namespace {
#include "Form.cc"
}

class ConvertToUtf16Test_1512 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal ASCII string conversion
TEST_F(ConvertToUtf16Test_1512, NormalAsciiString_1512) {
    GooString input("Hello");
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
    // Result should be non-empty for a non-empty input
    EXPECT_GT(result->toStr().size(), 0u);
}

// Test empty string conversion
TEST_F(ConvertToUtf16Test_1512, EmptyString_1512) {
    GooString input("");
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
    // Empty input should produce empty output (after BOM removal)
    EXPECT_EQ(result->toStr().size(), 0u);
}

// Test single character conversion
TEST_F(ConvertToUtf16Test_1512, SingleCharacter_1512) {
    GooString input("A");
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
    // Single ASCII char in UTF-16 should be 2 bytes (after BOM removal)
    EXPECT_EQ(result->toStr().size(), 2u);
}

// Test that the result does not contain BOM
TEST_F(ConvertToUtf16Test_1512, NoBOMInResult_1512) {
    GooString input("Test");
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
    const std::string &str = result->toStr();
    // If result has at least 2 bytes, verify it doesn't start with BOM (0xFE 0xFF or 0xFF 0xFE)
    if (str.size() >= 2) {
        bool hasBOM = (static_cast<unsigned char>(str[0]) == 0xFE && static_cast<unsigned char>(str[1]) == 0xFF) ||
                      (static_cast<unsigned char>(str[0]) == 0xFF && static_cast<unsigned char>(str[1]) == 0xFE);
        EXPECT_FALSE(hasBOM);
    }
}

// Test conversion of string with PDFDocEncoding special characters
TEST_F(ConvertToUtf16Test_1512, SpecialPDFDocEncodingChars_1512) {
    // Character 0x93 in PDFDocEncoding is LEFT DOUBLE QUOTATION MARK (U+201C)
    char specialChars[] = {static_cast<char>(0x93), '\0'};
    GooString input(specialChars, 1);
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
    // Should produce 2 bytes for the UTF-16 encoding of U+201C
    EXPECT_EQ(result->toStr().size(), 2u);
}

// Test multiple characters conversion produces correct size
TEST_F(ConvertToUtf16Test_1512, MultipleCharacters_1512) {
    GooString input("ABCD");
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
    // 4 ASCII chars in UTF-16 = 8 bytes (each char is 2 bytes)
    EXPECT_EQ(result->toStr().size(), 8u);
}

// Test return type is a valid unique_ptr
TEST_F(ConvertToUtf16Test_1512, ReturnsValidUniquePtr_1512) {
    GooString input("test");
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
}

// Test string with only high-byte PDFDocEncoding characters
TEST_F(ConvertToUtf16Test_1512, HighByteCharacters_1512) {
    char highBytes[] = {static_cast<char>(0x80), static_cast<char>(0x81), static_cast<char>(0x82)};
    GooString input(highBytes, 3);
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
    // 3 characters should produce 6 bytes in UTF-16
    EXPECT_EQ(result->toStr().size(), 6u);
}

// Test with space characters
TEST_F(ConvertToUtf16Test_1512, SpaceCharacters_1512) {
    GooString input("   ");
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
    // 3 spaces = 6 bytes in UTF-16
    EXPECT_EQ(result->toStr().size(), 6u);
}

// Test with null bytes embedded in the string
TEST_F(ConvertToUtf16Test_1512, NullBytesEmbedded_1512) {
    char data[] = {'A', '\0', 'B'};
    GooString input(data, 3);
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
    // 3 characters = 6 bytes in UTF-16
    EXPECT_EQ(result->toStr().size(), 6u);
}

// Test with Latin-1 compatible characters (0x20-0x7E)
TEST_F(ConvertToUtf16Test_1512, Latin1CompatibleRange_1512) {
    GooString input("0123456789");
    auto result = convertToUtf16(&input);
    ASSERT_NE(result, nullptr);
    // 10 digits = 20 bytes in UTF-16
    EXPECT_EQ(result->toStr().size(), 20u);
}
