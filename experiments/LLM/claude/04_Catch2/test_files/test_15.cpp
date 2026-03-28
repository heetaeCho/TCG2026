#include "catch2/internal/catch_xmlwriter.hpp"
#include <sstream>
#include <gtest/gtest.h>

using namespace Catch;

// Tests for XmlFormatting operator|
class XmlFormattingTest_15 : public ::testing::Test {};

TEST_F(XmlFormattingTest_15, NoneOrNoneIsNone_15) {
    constexpr auto result = XmlFormatting::None | XmlFormatting::None;
    EXPECT_EQ(static_cast<std::uint8_t>(result), 0);
}

TEST_F(XmlFormattingTest_15, NoneOrIndentIsIndent_15) {
    constexpr auto result = XmlFormatting::None | XmlFormatting::Indent;
    EXPECT_EQ(static_cast<std::uint8_t>(result), static_cast<std::uint8_t>(XmlFormatting::Indent));
}

TEST_F(XmlFormattingTest_15, NoneOrNewlineIsNewline_15) {
    constexpr auto result = XmlFormatting::None | XmlFormatting::Newline;
    EXPECT_EQ(static_cast<std::uint8_t>(result), static_cast<std::uint8_t>(XmlFormatting::Newline));
}

TEST_F(XmlFormattingTest_15, IndentOrNewlineCombinesBoth_15) {
    constexpr auto result = XmlFormatting::Indent | XmlFormatting::Newline;
    auto expected = static_cast<std::uint8_t>(XmlFormatting::Indent) | static_cast<std::uint8_t>(XmlFormatting::Newline);
    EXPECT_EQ(static_cast<std::uint8_t>(result), expected);
}

TEST_F(XmlFormattingTest_15, OperatorOrIsCommutative_15) {
    constexpr auto lhs = XmlFormatting::Indent | XmlFormatting::Newline;
    constexpr auto rhs = XmlFormatting::Newline | XmlFormatting::Indent;
    EXPECT_EQ(static_cast<std::uint8_t>(lhs), static_cast<std::uint8_t>(rhs));
}

TEST_F(XmlFormattingTest_15, OperatorOrWithSameValueIsIdempotent_15) {
    constexpr auto result = XmlFormatting::Indent | XmlFormatting::Indent;
    EXPECT_EQ(static_cast<std::uint8_t>(result), static_cast<std::uint8_t>(XmlFormatting::Indent));
}

TEST_F(XmlFormattingTest_15, OperatorOrIsConstexpr_15) {
    // Verify that operator| is usable in constexpr context
    constexpr auto result = XmlFormatting::Indent | XmlFormatting::Newline;
    static_assert(static_cast<std::uint8_t>(result) != 0, "Combined formatting should not be zero");
    SUCCEED();
}

TEST_F(XmlFormattingTest_15, NewlineOrNewlineIsNewline_15) {
    constexpr auto result = XmlFormatting::Newline | XmlFormatting::Newline;
    EXPECT_EQ(static_cast<std::uint8_t>(result), static_cast<std::uint8_t>(XmlFormatting::Newline));
}

// Tests for XmlWriter (if available in the header)
class XmlWriterTest_15 : public ::testing::Test {
protected:
    std::ostringstream stream;
};

TEST_F(XmlWriterTest_15, DefaultConstructionProducesValidWriter_15) {
    XmlEncode encoder("test", XmlEncode::ForTextNodes);
    std::ostringstream oss;
    oss << encoder;
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(XmlWriterTest_15, XmlEncodeEscapesAmpersand_15) {
    XmlEncode encoder("a&b", XmlEncode::ForTextNodes);
    std::ostringstream oss;
    oss << encoder;
    EXPECT_NE(oss.str().find("&amp;"), std::string::npos);
}

TEST_F(XmlWriterTest_15, XmlEncodeEscapesLessThan_15) {
    XmlEncode encoder("a<b", XmlEncode::ForTextNodes);
    std::ostringstream oss;
    oss << encoder;
    EXPECT_NE(oss.str().find("&lt;"), std::string::npos);
}

TEST_F(XmlWriterTest_15, XmlEncodeEscapesGreaterThan_15) {
    XmlEncode encoder("a>b", XmlEncode::ForTextNodes);
    std::ostringstream oss;
    oss << encoder;
    EXPECT_NE(oss.str().find("&gt;"), std::string::npos);
}

TEST_F(XmlWriterTest_15, XmlEncodeForAttributesEscapesQuotes_15) {
    XmlEncode encoder("a\"b", XmlEncode::ForAttributes);
    std::ostringstream oss;
    oss << encoder;
    EXPECT_NE(oss.str().find("&quot;"), std::string::npos);
}

TEST_F(XmlWriterTest_15, XmlEncodeEmptyString_15) {
    XmlEncode encoder("", XmlEncode::ForTextNodes);
    std::ostringstream oss;
    oss << encoder;
    EXPECT_TRUE(oss.str().empty());
}
