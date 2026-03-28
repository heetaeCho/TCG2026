#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

// Test normal text encoding
TEST(XmlEncodeTest_467, EmptyString_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef(""), XmlEncode::ForTextNodes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "");
}

TEST(XmlEncodeTest_467, PlainTextNoSpecialChars_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("hello world"), XmlEncode::ForTextNodes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "hello world");
}

TEST(XmlEncodeTest_467, AmpersandIsEncoded_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("a&b"), XmlEncode::ForTextNodes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a&amp;b");
}

TEST(XmlEncodeTest_467, LessThanIsEncoded_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("a<b"), XmlEncode::ForTextNodes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a&lt;b");
}

TEST(XmlEncodeTest_467, GreaterThanIsEncoded_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("a>b"), XmlEncode::ForTextNodes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a&gt;b");
}

TEST(XmlEncodeTest_467, QuoteEncodedInAttributes_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("a\"b"), XmlEncode::ForAttributes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a&quot;b");
}

TEST(XmlEncodeTest_467, QuoteNotEncodedInTextNodes_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("a\"b"), XmlEncode::ForTextNodes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "a\"b");
}

TEST(XmlEncodeTest_467, MultipleSpecialChars_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("<a>&b</a>"), XmlEncode::ForTextNodes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&lt;a&gt;&amp;b&lt;/a&gt;");
}

TEST(XmlEncodeTest_467, StreamOperator_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("a&b"), XmlEncode::ForTextNodes);
    oss << encode;
    EXPECT_EQ(oss.str(), "a&amp;b");
}

TEST(XmlEncodeTest_467, StreamOperatorReturnsStream_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("test"), XmlEncode::ForTextNodes);
    std::ostream& result = (oss << encode);
    EXPECT_EQ(&result, &oss);
}

TEST(XmlEncodeTest_467, DefaultForWhatIsTextNodes_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("a\"b"));
    encode.encodeTo(oss);
    // Default is ForTextNodes, so quotes should not be encoded
    EXPECT_EQ(oss.str(), "a\"b");
}

TEST(XmlEncodeTest_467, AttributeEncodesAllSpecialChars_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("<\"&>"), XmlEncode::ForAttributes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&lt;&quot;&amp;&gt;");
}

TEST(XmlEncodeTest_467, OnlySpecialChars_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("&&&"), XmlEncode::ForTextNodes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&amp;&amp;&amp;");
}

TEST(XmlEncodeTest_467, SingleCharAmpersand_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("&"), XmlEncode::ForTextNodes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&amp;");
}

TEST(XmlEncodeTest_467, SingleCharLessThan_467) {
    std::ostringstream oss;
    XmlEncode encode(StringRef("<"), XmlEncode::ForTextNodes);
    encode.encodeTo(oss);
    EXPECT_EQ(oss.str(), "&lt;");
}

TEST(XmlEncodeTest_467, ChainedStreamOperator_467) {
    std::ostringstream oss;
    XmlEncode encode1(StringRef("a&b"), XmlEncode::ForTextNodes);
    XmlEncode encode2(StringRef("c<d"), XmlEncode::ForTextNodes);
    oss << encode1 << encode2;
    EXPECT_EQ(oss.str(), "a&amp;bc&lt;d");
}
