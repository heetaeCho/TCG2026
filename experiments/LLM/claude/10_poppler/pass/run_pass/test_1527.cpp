#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include "UTF.h"

class Utf8ToUtf16WithBomTest_1527 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that empty input returns empty string
TEST_F(Utf8ToUtf16WithBomTest_1527, EmptyInputReturnsEmpty_1527) {
    std::string result = utf8ToUtf16WithBom("");
    EXPECT_TRUE(result.empty());
}

// Test that empty string_view returns empty string
TEST_F(Utf8ToUtf16WithBomTest_1527, EmptyStringViewReturnsEmpty_1527) {
    std::string_view empty_sv;
    std::string result = utf8ToUtf16WithBom(empty_sv);
    EXPECT_TRUE(result.empty());
}

// Test that result starts with BOM (0xFE 0xFF for big-endian UTF-16)
TEST_F(Utf8ToUtf16WithBomTest_1527, ResultStartsWithBOM_1527) {
    std::string result = utf8ToUtf16WithBom("A");
    ASSERT_GE(result.size(), 2u);
    // BOM should be 0xFE 0xFF
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
}

// Test single ASCII character 'A' (U+0041)
TEST_F(Utf8ToUtf16WithBomTest_1527, SingleAsciiCharacter_1527) {
    std::string result = utf8ToUtf16WithBom("A");
    // BOM (2 bytes) + one UTF-16 code unit (2 bytes) = 4 bytes
    ASSERT_EQ(result.size(), 4u);
    // BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // 'A' = U+0041 in big-endian: 0x00 0x41
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x41);
}

// Test multiple ASCII characters
TEST_F(Utf8ToUtf16WithBomTest_1527, MultipleAsciiCharacters_1527) {
    std::string result = utf8ToUtf16WithBom("AB");
    // BOM (2 bytes) + 2 UTF-16 code units (4 bytes) = 6 bytes
    ASSERT_EQ(result.size(), 6u);
    // BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // 'A' = 0x00 0x41
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x41);
    // 'B' = 0x00 0x42
    EXPECT_EQ(static_cast<unsigned char>(result[4]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[5]), 0x42);
}

// Test a two-byte UTF-8 character: é (U+00E9)
TEST_F(Utf8ToUtf16WithBomTest_1527, TwoByteUtf8Character_1527) {
    // é in UTF-8 is 0xC3 0xA9
    std::string result = utf8ToUtf16WithBom("\xC3\xA9");
    // BOM (2 bytes) + one UTF-16 code unit (2 bytes) = 4 bytes
    ASSERT_EQ(result.size(), 4u);
    // BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // U+00E9 in big-endian: 0x00 0xE9
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0xE9);
}

// Test a three-byte UTF-8 character: 中 (U+4E2D)
TEST_F(Utf8ToUtf16WithBomTest_1527, ThreeByteUtf8Character_1527) {
    // 中 in UTF-8 is 0xE4 0xB8 0xAD
    std::string result = utf8ToUtf16WithBom("\xE4\xB8\xAD");
    // BOM (2 bytes) + one UTF-16 code unit (2 bytes) = 4 bytes
    ASSERT_EQ(result.size(), 4u);
    // BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // U+4E2D in big-endian: 0x4E 0x2D
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x4E);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x2D);
}

// Test a four-byte UTF-8 character (surrogate pair): 𝄞 (U+1D11E)
TEST_F(Utf8ToUtf16WithBomTest_1527, FourByteUtf8CharacterSurrogatePair_1527) {
    // 𝄞 (U+1D11E) in UTF-8: 0xF0 0x9D 0x84 0x9E
    std::string result = utf8ToUtf16WithBom("\xF0\x9D\x84\x9E");
    // BOM (2 bytes) + surrogate pair (4 bytes) = 6 bytes
    ASSERT_EQ(result.size(), 6u);
    // BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // U+1D11E -> surrogate pair: high = 0xD834, low = 0xDD1E
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0xD8);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x34);
    EXPECT_EQ(static_cast<unsigned char>(result[4]), 0xDD);
    EXPECT_EQ(static_cast<unsigned char>(result[5]), 0x1E);
}

// Test mixed ASCII and multibyte characters
TEST_F(Utf8ToUtf16WithBomTest_1527, MixedAsciiAndMultibyte_1527) {
    // "Aé" -> A(U+0041) + é(U+00E9)
    std::string result = utf8ToUtf16WithBom("A\xC3\xA9");
    // BOM (2) + 2 code units (4) = 6 bytes
    ASSERT_EQ(result.size(), 6u);
    // BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // 'A'
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x41);
    // é
    EXPECT_EQ(static_cast<unsigned char>(result[4]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[5]), 0xE9);
}

// Test that result size is always at least BOM size for non-empty input
TEST_F(Utf8ToUtf16WithBomTest_1527, NonEmptyInputHasAtLeastBomSize_1527) {
    std::string result = utf8ToUtf16WithBom("x");
    EXPECT_GE(result.size(), 2u);
}

// Test longer string
TEST_F(Utf8ToUtf16WithBomTest_1527, LongerAsciiString_1527) {
    std::string input = "Hello, World!";
    std::string result = utf8ToUtf16WithBom(input);
    // BOM (2) + 13 code units (26) = 28 bytes
    ASSERT_EQ(result.size(), 28u);
    // Verify BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // Verify 'H' = U+0048
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x48);
}

// Test single space character
TEST_F(Utf8ToUtf16WithBomTest_1527, SingleSpaceCharacter_1527) {
    std::string result = utf8ToUtf16WithBom(" ");
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // Space = U+0020
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x20);
}

// Test null character embedded in string_view
TEST_F(Utf8ToUtf16WithBomTest_1527, NullCharacterInStringView_1527) {
    std::string_view input("A\0B", 3);
    std::string result = utf8ToUtf16WithBom(input);
    // BOM (2) + 3 code units (6) = 8 bytes
    ASSERT_EQ(result.size(), 8u);
    // BOM
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // 'A'
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x41);
    // null
    EXPECT_EQ(static_cast<unsigned char>(result[4]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[5]), 0x00);
    // 'B'
    EXPECT_EQ(static_cast<unsigned char>(result[6]), 0x00);
    EXPECT_EQ(static_cast<unsigned char>(result[7]), 0x42);
}

// Test BMP boundary character U+FFFF (if valid)
TEST_F(Utf8ToUtf16WithBomTest_1527, BmpBoundaryCharacter_1527) {
    // U+FFFD (replacement character) in UTF-8: 0xEF 0xBF 0xBD
    std::string result = utf8ToUtf16WithBom("\xEF\xBF\xBD");
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xFE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xFF);
    // U+FFFD: 0xFF 0xFD
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0xFF);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0xFD);
}

// Test that the output is in big-endian format (the BOM indicates BE)
TEST_F(Utf8ToUtf16WithBomTest_1527, OutputIsBigEndianFormat_1527) {
    // Test with a character where byte order matters: Ω (U+03A9)
    // UTF-8: 0xCE 0xA9
    std::string result = utf8ToUtf16WithBom("\xCE\xA9");
    ASSERT_EQ(result.size(), 4u);
    // U+03A9 in big-endian: 0x03 0xA9
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x03);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0xA9);
}
