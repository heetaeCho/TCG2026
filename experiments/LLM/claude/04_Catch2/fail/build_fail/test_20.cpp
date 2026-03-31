#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstring>

// Include necessary headers
#include "catch2/internal/catch_xmlwriter.hpp"
#include "NullOStream.h"

// Test fixture for XmlEncode tests
class XmlEncodeTest_20 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Empty string encoding
TEST_F(XmlEncodeTest_20, EmptyStringEncodesSuccessfully_20) {
    std::string input = "";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "");
}

// Test: Plain ASCII text without special characters
TEST_F(XmlEncodeTest_20, PlainTextEncodesUnchanged_20) {
    std::string input = "Hello World";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "Hello World");
}

// Test: Ampersand is escaped
TEST_F(XmlEncodeTest_20, AmpersandIsEscaped_20) {
    std::string input = "a&b";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a&amp;b");
}

// Test: Less-than sign is escaped
TEST_F(XmlEncodeTest_20, LessThanIsEscaped_20) {
    std::string input = "a<b";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a&lt;b");
}

// Test: Greater-than sign is escaped
TEST_F(XmlEncodeTest_20, GreaterThanIsEscaped_20) {
    std::string input = "a>b";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a&gt;b");
}

// Test: Double quote is escaped for attributes
TEST_F(XmlEncodeTest_20, DoubleQuoteEscapedForAttributes_20) {
    std::string input = "a\"b";
    Catch::XmlEncode encode(input, Catch::XmlEncode::ForAttributes);
    std::ostringstream oss;
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a&quot;b");
}

// Test: Double quote in text nodes (may or may not be escaped)
TEST_F(XmlEncodeTest_20, DoubleQuoteInTextNode_20) {
    std::string input = "a\"b";
    Catch::XmlEncode encode(input, Catch::XmlEncode::ForTextNodes);
    std::ostringstream oss;
    encode.encodeTo(oss);
    // Double quotes in text nodes may or may not be escaped,
    // but the result should contain some representation of the quote
    EXPECT_FALSE(oss.str().empty());
}

// Test: Multiple special characters
TEST_F(XmlEncodeTest_20, MultipleSpecialCharacters_20) {
    std::string input = "<tag attr=\"val\">&</tag>";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    std::string result = oss.str();
    // Should not contain raw < or > or & (they should be escaped)
    // Check that original special chars are replaced
    EXPECT_NE(result, input);
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
}

// Test: Encoding to NullOStream (no crash)
TEST_F(XmlEncodeTest_20, EncodeToNullOStreamNoCrash_20) {
    std::string input = "test<>&\"data";
    NullOStream nul;
    Catch::XmlEncode encode(input);
    EXPECT_NO_THROW(encode.encodeTo(nul));
}

// Test: String with only special characters
TEST_F(XmlEncodeTest_20, OnlySpecialCharacters_20) {
    std::string input = "<>&\"";
    Catch::XmlEncode encode(input, Catch::XmlEncode::ForAttributes);
    std::ostringstream oss;
    encode.encodeTo(oss);
    std::string result = oss.str();
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&quot;"), std::string::npos);
}

// Test: Very long string
TEST_F(XmlEncodeTest_20, VeryLongString_20) {
    std::string input(10000, 'a');
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    EXPECT_NO_THROW(encode.encodeTo(oss));
    EXPECT_EQ(oss.str(), input);
}

// Test: String with newlines and tabs
TEST_F(XmlEncodeTest_20, NewlinesAndTabs_20) {
    std::string input = "line1\nline2\ttab";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    // Newlines and tabs should be handled (either preserved or encoded)
    EXPECT_FALSE(oss.str().empty());
}

// Test: String with null bytes embedded
TEST_F(XmlEncodeTest_20, EmbeddedNullBytes_20) {
    std::string input("abc\0def", 7);
    Catch::XmlEncode encode(input);
    NullOStream nul;
    EXPECT_NO_THROW(encode.encodeTo(nul));
}

// Test: String with high-byte / non-ASCII characters
TEST_F(XmlEncodeTest_20, NonAsciiCharacters_20) {
    std::string input = "\xC3\xA9\xC3\xA0\xC3\xBC"; // UTF-8 encoded éàü
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    EXPECT_NO_THROW(encode.encodeTo(oss));
    EXPECT_FALSE(oss.str().empty());
}

// Test: operator<< works correctly
TEST_F(XmlEncodeTest_20, StreamOperator_20) {
    std::string input = "a<b";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    oss << encode;
    EXPECT_EQ(oss.str(), "a&lt;b");
}

// Test: ForTextNodes is the default
TEST_F(XmlEncodeTest_20, DefaultIsForTextNodes_20) {
    std::string input = "a<b>c&d";
    Catch::XmlEncode encode1(input);
    Catch::XmlEncode encode2(input, Catch::XmlEncode::ForTextNodes);
    std::ostringstream oss1, oss2;
    encode1.encodeTo(oss1);
    encode2.encodeTo(oss2);
    EXPECT_EQ(oss1.str(), oss2.str());
}

// Test: Binary data (all byte values)
TEST_F(XmlEncodeTest_20, BinaryData_20) {
    std::string input;
    for (int i = 0; i < 256; ++i) {
        input.push_back(static_cast<char>(i));
    }
    Catch::XmlEncode encode(input);
    NullOStream nul;
    EXPECT_NO_THROW(encode.encodeTo(nul));
}

// Test: Single character special cases
TEST_F(XmlEncodeTest_20, SingleAmpersand_20) {
    std::string input = "&";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&amp;");
}

TEST_F(XmlEncodeTest_20, SingleLessThan_20) {
    std::string input = "<";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&lt;");
}

TEST_F(XmlEncodeTest_20, SingleGreaterThan_20) {
    std::string input = ">";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&gt;");
}

// Test: Repeated special characters
TEST_F(XmlEncodeTest_20, RepeatedAmpersands_20) {
    std::string input = "&&&";
    Catch::XmlEncode encode(input);
    std::ostringstream oss;
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&amp;&amp;&amp;");
}

// Test: Mixed content
TEST_F(XmlEncodeTest_20, MixedContent_20) {
    std::string input = "Hello <World> & \"Friends\"";
    Catch::XmlEncode encode(input, Catch::XmlEncode::ForAttributes);
    std::ostringstream oss;
    encode.encodeTo(oss);
    std::string result = oss.str();
    EXPECT_NE(result.find("Hello "), std::string::npos);
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&quot;"), std::string::npos);
}

// Test matching the fuzz function behavior
TEST_F(XmlEncodeTest_20, FuzzFunctionEquivalent_20) {
    const uint8_t data[] = {'<', '>', '&', '"', 'a', 'b', 'c'};
    size_t size = sizeof(data);
    std::string buf(data, data + size);
    NullOStream nul;
    Catch::XmlEncode encode(buf);
    EXPECT_NO_THROW(encode.encodeTo(nul));
}

// Test: Encoding consistency - calling encodeTo multiple times
TEST_F(XmlEncodeTest_20, EncodingConsistency_20) {
    std::string input = "test<data>&more";
    Catch::XmlEncode encode(input);
    std::ostringstream oss1, oss2;
    encode.encodeTo(oss1);
    encode.encodeTo(oss2);
    EXPECT_EQ(oss1.str(), oss2.str());
}
