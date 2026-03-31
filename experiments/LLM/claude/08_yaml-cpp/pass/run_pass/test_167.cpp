#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/exceptions.h"
#include "stream.h"

// We need access to the Escape function
namespace YAML {
namespace Exp {
std::string Escape(Stream& in, int codeLength);
}
}

class EscapeTest_167 : public ::testing::Test {
protected:
    // Helper to create a Stream from a string and call Escape
    std::string CallEscape(const std::string& hexStr, int codeLength) {
        std::istringstream iss(hexStr);
        YAML::Stream stream(iss);
        return YAML::Exp::Escape(stream, codeLength);
    }
};

// Test ASCII character (value <= 0x7F): U+0041 = 'A'
TEST_F(EscapeTest_167, SingleByteAsciiCharacter_167) {
    // "41" in hex = 65 decimal = 'A'
    std::string result = CallEscape("41", 2);
    EXPECT_EQ(result, "A");
}

// Test ASCII null character U+0000
TEST_F(EscapeTest_167, NullCharacter_167) {
    std::string result = CallEscape("00", 2);
    std::string expected(1, '\0');
    EXPECT_EQ(result, expected);
}

// Test boundary: U+007F (max single byte)
TEST_F(EscapeTest_167, MaxSingleByteCharacter_167) {
    std::string result = CallEscape("7F", 2);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0x7F);
}

// Test 2-byte UTF-8: U+0080 (boundary, value = 128)
TEST_F(EscapeTest_167, TwoByteUtf8Boundary_167) {
    // 0x0080 -> 0xC2 0x80
    std::string result = CallEscape("0080", 4);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xC2);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0x80);
}

// Test 2-byte UTF-8: U+07FF (max 2-byte)
TEST_F(EscapeTest_167, MaxTwoByteUtf8_167) {
    // 0x07FF -> 0xDF 0xBF
    std::string result = CallEscape("07FF", 4);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xDF);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xBF);
}

// Test 3-byte UTF-8: U+0800 (boundary)
TEST_F(EscapeTest_167, ThreeByteUtf8Boundary_167) {
    // 0x0800 -> 0xE0 0xA0 0x80
    std::string result = CallEscape("0800", 4);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xE0);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xA0);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x80);
}

// Test 3-byte UTF-8: U+FFFF (max 3-byte)
TEST_F(EscapeTest_167, MaxThreeByteUtf8_167) {
    // 0xFFFF -> 0xEF 0xBF 0xBF
    std::string result = CallEscape("FFFF", 4);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xEF);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xBF);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0xBF);
}

// Test 4-byte UTF-8: U+10000 (boundary)
TEST_F(EscapeTest_167, FourByteUtf8Boundary_167) {
    // 0x10000 -> 0xF0 0x90 0x80 0x80
    std::string result = CallEscape("010000", 6);
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xF0);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0x90);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x80);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x80);
}

// Test 4-byte UTF-8: U+10FFFF (max valid Unicode)
TEST_F(EscapeTest_167, MaxValidUnicode_167) {
    // 0x10FFFF -> 0xF4 0x8F 0xBF 0xBF
    std::string result = CallEscape("10FFFF", 6);
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xF4);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0x8F);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0xBF);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0xBF);
}

// Test surrogate range: U+D800 (start of surrogate range) should throw
TEST_F(EscapeTest_167, SurrogateStartThrows_167) {
    EXPECT_THROW(CallEscape("D800", 4), YAML::ParserException);
}

// Test surrogate range: U+DFFF (end of surrogate range) should throw
TEST_F(EscapeTest_167, SurrogateEndThrows_167) {
    EXPECT_THROW(CallEscape("DFFF", 4), YAML::ParserException);
}

// Test surrogate range: U+D900 (middle of surrogate range) should throw
TEST_F(EscapeTest_167, SurrogateMiddleThrows_167) {
    EXPECT_THROW(CallEscape("D900", 4), YAML::ParserException);
}

// Test value just before surrogate range: U+D7FF should be valid (3-byte UTF-8)
TEST_F(EscapeTest_167, JustBeforeSurrogateRange_167) {
    // 0xD7FF -> 0xED 0x9F 0xBF
    std::string result = CallEscape("D7FF", 4);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xED);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0x9F);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0xBF);
}

// Test value just after surrogate range: U+E000 should be valid (3-byte UTF-8)
TEST_F(EscapeTest_167, JustAfterSurrogateRange_167) {
    // 0xE000 -> 0xEE 0x80 0x80
    std::string result = CallEscape("E000", 4);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xEE);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0x80);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x80);
}

// Test a common character: U+00E9 (é) - 2-byte UTF-8
TEST_F(EscapeTest_167, TwoByteAccentedChar_167) {
    // 0x00E9 -> 0xC3 0xA9
    std::string result = CallEscape("00E9", 4);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xC3);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xA9);
}

// Test codeLength = 2 with hex "61" -> 'a' (0x61 = 97)
TEST_F(EscapeTest_167, CodeLength2LowercaseA_167) {
    std::string result = CallEscape("61", 2);
    EXPECT_EQ(result, "a");
}

// Test a 4-byte encoded emoji-like character: U+1F600 (if we supply 8 hex digits as codeLength=8)
// Actually, 0x1F600 needs 5 hex digits. With codeLength=8, we'd need "001F6000" but that's a different value.
// Let's use codeLength=8 for U+0001F600
TEST_F(EscapeTest_167, FourByteEmojiCharacter_167) {
    // 0x1F600 with 8 hex digits = "0001F600"
    std::string result = CallEscape("0001F600", 8);
    EXPECT_EQ(result.size(), 4u);
    // 0x1F600: F0 9F 98 80
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xF0);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0x9F);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0x98);
    EXPECT_EQ(static_cast<unsigned char>(result[3]), 0x80);
}

// Test value > 0x10FFFF should throw (e.g., 0x110000)
TEST_F(EscapeTest_167, ValueAboveMaxUnicodeThrows_167) {
    EXPECT_THROW(CallEscape("00110000", 8), YAML::ParserException);
}

// Test codeLength = 0 should produce empty hex string and value 0
// Parsing "" as hex might throw or produce 0 depending on implementation
// This is a boundary test for codeLength
TEST_F(EscapeTest_167, CodeLengthZero_167) {
    // With codeLength=0, no characters read from stream, hex string is ""
    // ParseHex("") behavior is implementation-dependent, might throw
    try {
        std::string result = CallEscape("", 0);
        // If it succeeds, value should be 0, resulting in a null character
        std::string expected(1, '\0');
        EXPECT_EQ(result, expected);
    } catch (const YAML::ParserException&) {
        // Also acceptable if ParseHex throws on empty input
        SUCCEED();
    }
}

// Test a 2-byte boundary: U+0100 (Latin Extended-A)
TEST_F(EscapeTest_167, TwoByteLatinExtended_167) {
    // 0x0100 -> 0xC4 0x80
    std::string result = CallEscape("0100", 4);
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xC4);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0x80);
}

// Test a known CJK character: U+4E2D (中)
TEST_F(EscapeTest_167, ThreeByteCJKCharacter_167) {
    // 0x4E2D -> 0xE4 0xB8 0xAD
    std::string result = CallEscape("4E2D", 4);
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(static_cast<unsigned char>(result[0]), 0xE4);
    EXPECT_EQ(static_cast<unsigned char>(result[1]), 0xB8);
    EXPECT_EQ(static_cast<unsigned char>(result[2]), 0xAD);
}
