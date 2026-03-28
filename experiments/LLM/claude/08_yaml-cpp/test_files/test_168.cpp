#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/exceptions.h"
#include "stream.h"

// We need access to the Escape function from the Exp namespace
namespace YAML {
namespace Exp {
std::string Escape(Stream& in);
std::string Escape(Stream& in, int length);
}
}

class EscapeTest_168 : public ::testing::Test {
protected:
    // Helper to create a stream and call Escape
    // The stream needs to contain the escape character (e.g., '\') followed by the escape code
    std::string callEscape(const std::string& input) {
        std::istringstream iss(input);
        YAML::Stream stream(iss);
        return YAML::Exp::Escape(stream);
    }
};

// Test single-quote escape: '' -> '
TEST_F(EscapeTest_168, SingleQuoteEscape_168) {
    std::string result = callEscape("''");
    EXPECT_EQ(result, "\'");
}

// Test null character escape: \0
TEST_F(EscapeTest_168, NullEscape_168) {
    std::string result = callEscape("\\0");
    EXPECT_EQ(result, std::string(1, '\x00'));
}

// Test bell escape: \a
TEST_F(EscapeTest_168, BellEscape_168) {
    std::string result = callEscape("\\a");
    EXPECT_EQ(result, "\x07");
}

// Test backspace escape: \b
TEST_F(EscapeTest_168, BackspaceEscape_168) {
    std::string result = callEscape("\\b");
    EXPECT_EQ(result, "\x08");
}

// Test tab escape: \t
TEST_F(EscapeTest_168, TabEscape_168) {
    std::string result = callEscape("\\t");
    EXPECT_EQ(result, "\x09");
}

// Test literal tab escape: \<TAB>
TEST_F(EscapeTest_168, LiteralTabEscape_168) {
    std::string input = std::string("\\") + '\t';
    std::string result = callEscape(input);
    EXPECT_EQ(result, "\x09");
}

// Test newline escape: \n
TEST_F(EscapeTest_168, NewlineEscape_168) {
    std::string result = callEscape("\\n");
    EXPECT_EQ(result, "\x0A");
}

// Test vertical tab escape: \v
TEST_F(EscapeTest_168, VerticalTabEscape_168) {
    std::string result = callEscape("\\v");
    EXPECT_EQ(result, "\x0B");
}

// Test form feed escape: \f
TEST_F(EscapeTest_168, FormFeedEscape_168) {
    std::string result = callEscape("\\f");
    EXPECT_EQ(result, "\x0C");
}

// Test carriage return escape: \r
TEST_F(EscapeTest_168, CarriageReturnEscape_168) {
    std::string result = callEscape("\\r");
    EXPECT_EQ(result, "\x0D");
}

// Test escape character escape: \e
TEST_F(EscapeTest_168, EscapeCharEscape_168) {
    std::string result = callEscape("\\e");
    EXPECT_EQ(result, "\x1B");
}

// Test space escape: \<space>
TEST_F(EscapeTest_168, SpaceEscape_168) {
    std::string result = callEscape("\\ ");
    EXPECT_EQ(result, " ");
}

// Test double-quote escape: \"
TEST_F(EscapeTest_168, DoubleQuoteEscape_168) {
    std::string result = callEscape("\\\"");
    EXPECT_EQ(result, "\"");
}

// Test single-quote after backslash escape: \'
TEST_F(EscapeTest_168, BackslashSingleQuoteEscape_168) {
    std::string result = callEscape("\\'");
    EXPECT_EQ(result, "\'");
}

// Test backslash escape: \\  
TEST_F(EscapeTest_168, BackslashEscape_168) {
    std::string result = callEscape("\\\\");
    EXPECT_EQ(result, "\\");
}

// Test slash escape: \/
TEST_F(EscapeTest_168, SlashEscape_168) {
    std::string result = callEscape("\\/");
    EXPECT_EQ(result, "/");
}

// Test next line escape: \N (Unicode #x85)
TEST_F(EscapeTest_168, NextLineEscape_168) {
    std::string result = callEscape("\\N");
    EXPECT_EQ(result, "\x85");
}

// Test non-breaking space escape: \_ (Unicode #xA0)
TEST_F(EscapeTest_168, NonBreakingSpaceEscape_168) {
    std::string result = callEscape("\\_");
    EXPECT_EQ(result, "\xA0");
}

// Test line separator escape: \L (Unicode #x2028)
TEST_F(EscapeTest_168, LineSeparatorEscape_168) {
    std::string result = callEscape("\\L");
    EXPECT_EQ(result, "\xE2\x80\xA8");
}

// Test paragraph separator escape: \P (Unicode #x2029)
TEST_F(EscapeTest_168, ParagraphSeparatorEscape_168) {
    std::string result = callEscape("\\P");
    EXPECT_EQ(result, "\xE2\x80\xA9");
}

// Test hex escape: \x followed by 2 hex digits
TEST_F(EscapeTest_168, HexEscape2Digit_168) {
    std::string result = callEscape("\\x41");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'A'); // 0x41 = 'A'
}

// Test unicode escape: \u followed by 4 hex digits
TEST_F(EscapeTest_168, UnicodeEscape4Digit_168) {
    std::string result = callEscape("\\u0041");
    // Should produce UTF-8 encoding of U+0041 which is 'A'
    EXPECT_FALSE(result.empty());
    // U+0041 is 'A' in UTF-8 (single byte)
    EXPECT_EQ(result[0], 'A');
}

// Test unicode escape: \U followed by 8 hex digits
TEST_F(EscapeTest_168, UnicodeEscape8Digit_168) {
    std::string result = callEscape("\\U00000041");
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], 'A');
}

// Test invalid escape character throws ParserException
TEST_F(EscapeTest_168, InvalidEscapeThrows_168) {
    EXPECT_THROW(callEscape("\\z"), YAML::ParserException);
}

// Test another invalid escape character
TEST_F(EscapeTest_168, InvalidEscapeThrowsQ_168) {
    EXPECT_THROW(callEscape("\\q"), YAML::ParserException);
}

// Test invalid escape with digit that's not 0
TEST_F(EscapeTest_168, InvalidEscapeDigit1_168) {
    EXPECT_THROW(callEscape("\\1"), YAML::ParserException);
}

// Test hex escape with specific value
TEST_F(EscapeTest_168, HexEscapeFF_168) {
    std::string result = callEscape("\\xFF");
    EXPECT_EQ(result.size(), 2u); // UTF-8 encoding of 0xFF requires 2 bytes
}

// Test hex escape with zero
TEST_F(EscapeTest_168, HexEscapeZero_168) {
    std::string result = callEscape("\\x00");
    EXPECT_EQ(result, std::string(1, '\x00'));
}

// Test unicode \u with multi-byte result
TEST_F(EscapeTest_168, UnicodeEscapeMultiByte_168) {
    // U+00E9 is 'é' which is 2 bytes in UTF-8: C3 A9
    std::string result = callEscape("\\u00E9");
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result, "\xC3\xA9");
}

// Test unicode \u with 3-byte UTF-8 result
TEST_F(EscapeTest_168, UnicodeEscape3Byte_168) {
    // U+2028 is line separator: E2 80 A8 in UTF-8
    std::string result = callEscape("\\u2028");
    EXPECT_EQ(result, "\xE2\x80\xA8");
}

// Test \U with 4-byte UTF-8 result
TEST_F(EscapeTest_168, UnicodeEscape4ByteUTF8_168) {
    // U+0001F600 = 😀 -> F0 9F 98 80 in UTF-8
    std::string result = callEscape("\\U0001F600");
    EXPECT_EQ(result.size(), 4u);
    EXPECT_EQ(result, "\xF0\x9F\x98\x80");
}
