#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using Catch::XmlEncode;

class XmlEncodeTest_466 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// === Normal operation tests ===

TEST_F(XmlEncodeTest_466, EmptyString_466) {
    XmlEncode encoder("", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "");
}

TEST_F(XmlEncodeTest_466, PlainAsciiText_466) {
    XmlEncode encoder("Hello World", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "Hello World");
}

TEST_F(XmlEncodeTest_466, LessThanEscaped_466) {
    XmlEncode encoder("<", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&lt;");
}

TEST_F(XmlEncodeTest_466, AmpersandEscaped_466) {
    XmlEncode encoder("&", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&amp;");
}

TEST_F(XmlEncodeTest_466, GreaterThanAfterDoubleClosingBracket_466) {
    XmlEncode encoder("]]>", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "]]&gt;");
}

TEST_F(XmlEncodeTest_466, GreaterThanWithoutDoubleClosingBracket_466) {
    XmlEncode encoder("a>", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a>");
}

TEST_F(XmlEncodeTest_466, GreaterThanAlone_466) {
    XmlEncode encoder(">", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), ">");
}

TEST_F(XmlEncodeTest_466, QuoteEscapedForAttributes_466) {
    XmlEncode encoder("\"", XmlEncode::ForAttributes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&quot;");
}

TEST_F(XmlEncodeTest_466, QuoteNotEscapedForTextNodes_466) {
    XmlEncode encoder("\"", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "\"");
}

TEST_F(XmlEncodeTest_466, MultipleLessThan_466) {
    XmlEncode encoder("<<", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&lt;&lt;");
}

TEST_F(XmlEncodeTest_466, MixedSpecialChars_466) {
    XmlEncode encoder("<&>", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&lt;&amp;>");
}

TEST_F(XmlEncodeTest_466, MixedSpecialCharsForAttributes_466) {
    XmlEncode encoder("<\"&", XmlEncode::ForAttributes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&lt;&quot;&amp;");
}

// === Boundary condition tests ===

TEST_F(XmlEncodeTest_466, TabCharacterPassedThrough_466) {
    // Tab is 0x09, should be passed through
    std::string input(1, '\x09');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "\x09");
}

TEST_F(XmlEncodeTest_466, NewlinePassedThrough_466) {
    // Newline is 0x0A
    std::string input(1, '\x0A');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "\x0A");
}

TEST_F(XmlEncodeTest_466, CarriageReturnPassedThrough_466) {
    // CR is 0x0D
    std::string input(1, '\x0D');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "\x0D");
}

TEST_F(XmlEncodeTest_466, ControlCharBelowTab_466) {
    // 0x01 should be hex-escaped
    std::string input(1, '\x01');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    // Should be hex-escaped, not the raw character
    EXPECT_NE(oss.str(), "\x01");
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(XmlEncodeTest_466, NullCharHexEscaped_466) {
    // 0x00 should be hex-escaped
    std::string input(1, '\x00');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    // Should produce hex escape
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(XmlEncodeTest_466, ControlChar0x0E_466) {
    // 0x0E is between 0x0D and 0x20, should be hex-escaped
    std::string input(1, '\x0E');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_NE(oss.str(), "\x0E");
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(XmlEncodeTest_466, ControlChar0x1F_466) {
    // 0x1F is < 0x20, should be hex-escaped
    std::string input(1, '\x1F');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_NE(oss.str(), "\x1F");
}

TEST_F(XmlEncodeTest_466, DELCharHexEscaped_466) {
    // 0x7F should be hex-escaped
    std::string input(1, '\x7F');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_NE(oss.str(), "\x7F");
}

TEST_F(XmlEncodeTest_466, SpaceCharPassedThrough_466) {
    XmlEncode encoder(" ", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), " ");
}

TEST_F(XmlEncodeTest_466, TildeCharPassedThrough_466) {
    // 0x7E = '~', should pass through as normal ASCII
    XmlEncode encoder("~", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "~");
}

// === UTF-8 tests ===

TEST_F(XmlEncodeTest_466, ValidTwoByteUTF8_466) {
    // U+00E9 (é) = 0xC3 0xA9
    std::string input = "\xC3\xA9";
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "\xC3\xA9");
}

TEST_F(XmlEncodeTest_466, ValidThreeByteUTF8_466) {
    // U+20AC (€) = 0xE2 0x82 0xAC
    std::string input = "\xE2\x82\xAC";
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "\xE2\x82\xAC");
}

TEST_F(XmlEncodeTest_466, ValidFourByteUTF8_466) {
    // U+1F600 (😀) = 0xF0 0x9F 0x98 0x80
    std::string input = "\xF0\x9F\x98\x80";
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "\xF0\x9F\x98\x80");
}

TEST_F(XmlEncodeTest_466, InvalidLoneHighByte_466) {
    // 0x80 is a continuation byte, not a valid start; c < 0xC0 so hex-escaped
    std::string input(1, '\x80');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_NE(oss.str(), "\x80");
}

TEST_F(XmlEncodeTest_466, InvalidByteF8_466) {
    // 0xF8 >= 0xF8 so should be hex-escaped
    std::string input(1, '\xF8');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_NE(oss.str(), "\xF8");
}

TEST_F(XmlEncodeTest_466, TruncatedTwoByteSequence_466) {
    // Start of 2-byte sequence but string ends
    std::string input(1, '\xC3');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    // Should hex-escape the lone byte
    EXPECT_NE(oss.str(), "\xC3");
}

TEST_F(XmlEncodeTest_466, TruncatedThreeByteSequence_466) {
    // Start of 3-byte but only 2 bytes
    std::string input = "\xE2\x82";
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_NE(oss.str(), "\xE2\x82");
}

TEST_F(XmlEncodeTest_466, OverlongTwoByteSequence_466) {
    // Overlong encoding of a character < 0x80: 0xC0 0x80 encodes U+0000
    std::string input = "\xC0\x80";
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    // This should be rejected (overlong), so hex-escaped
    EXPECT_NE(oss.str(), "\xC0\x80");
}

TEST_F(XmlEncodeTest_466, InvalidContinuationByte_466) {
    // 0xC3 followed by non-continuation byte
    std::string input = "\xC3\x20";
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    // The first byte should be hex-escaped, then space passes through
    std::string result = oss.str();
    EXPECT_NE(result.substr(0, 1), "\xC3");
}

// === Stream operator test ===

TEST_F(XmlEncodeTest_466, StreamOperator_466) {
    XmlEncode encoder("<test>", XmlEncode::ForTextNodes);
    oss << encoder;
    EXPECT_EQ(oss.str(), "&lt;test>");
}

// === Complex string tests ===

TEST_F(XmlEncodeTest_466, ComplexMixedContent_466) {
    XmlEncode encoder("a<b&c\"d", XmlEncode::ForAttributes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a&lt;b&amp;c&quot;d");
}

TEST_F(XmlEncodeTest_466, OnlySpecialChars_466) {
    XmlEncode encoder("<&<&", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&lt;&amp;&lt;&amp;");
}

TEST_F(XmlEncodeTest_466, DoubleClosingBracketWithoutGreater_466) {
    XmlEncode encoder("]]", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "]]");
}

TEST_F(XmlEncodeTest_466, SingleClosingBracketThenGreater_466) {
    XmlEncode encoder("]>", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    // Only one ']' before '>', doesn't match pattern
    EXPECT_EQ(oss.str(), "]>");
}

TEST_F(XmlEncodeTest_466, TextFollowedByDoubleBracketGreater_466) {
    XmlEncode encoder("abc]]>def", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "abc]]&gt;def");
}

TEST_F(XmlEncodeTest_466, DefaultForWhatIsForTextNodes_466) {
    XmlEncode encoder("\"test\"");
    encoder.encodeTo(oss);
    // Default is ForTextNodes, so quotes should not be escaped
    EXPECT_EQ(oss.str(), "\"test\"");
}

TEST_F(XmlEncodeTest_466, PrintableAsciiRange_466) {
    // Test a range of normal printable ASCII characters
    XmlEncode encoder("ABCxyz0123456789!@#$%^*()_+-=[]{}|;':,./?`~", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "ABCxyz0123456789!@#$%^*()_+-=[]{}|;':,./?`~");
}

TEST_F(XmlEncodeTest_466, Char0x08HexEscaped_466) {
    // 0x08 (backspace) is < 0x09, should be hex-escaped
    std::string input(1, '\x08');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_NE(oss.str(), "\x08");
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(XmlEncodeTest_466, Char0x0BFormFeed_466) {
    // 0x0B is between 0x09 and 0x0D, should pass through
    std::string input(1, '\x0B');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "\x0B");
}

TEST_F(XmlEncodeTest_466, Char0x0CPassedThrough_466) {
    // 0x0C is between 0x09 and 0x0D, should pass through
    std::string input(1, '\x0C');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "\x0C");
}

TEST_F(XmlEncodeTest_466, ValidTwoByteAtBoundary_466) {
    // U+007F is 1 byte (0x7F, hex-escaped), U+0080 = 0xC2 0x80 is smallest valid 2-byte
    std::string input = "\xC2\x80";
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "\xC2\x80");
}

TEST_F(XmlEncodeTest_466, ByteFF_466) {
    // 0xFF >= 0xF8 so should be hex-escaped
    std::string input(1, '\xFF');
    XmlEncode encoder(input, XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_NE(oss.str(), "\xFF");
}

TEST_F(XmlEncodeTest_466, MultipleGreaterAfterBrackets_466) {
    XmlEncode encoder("]]>]]>", XmlEncode::ForTextNodes);
    encoder.encodeTo(oss);
    EXPECT_EQ(oss.str(), "]]&gt;]]&gt;");
}
