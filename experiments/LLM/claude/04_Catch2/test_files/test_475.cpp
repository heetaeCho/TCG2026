#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_475 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test: endElement closes a self-closing tag when tag is still open (no content written)
TEST_F(XmlWriterTest_475, EndElementSelfClosingTag_475) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Should contain self-closing tag
    EXPECT_NE(output.find("/>"), std::string::npos);
}

// Test: endElement writes closing tag when content has been written
TEST_F(XmlWriterTest_475, EndElementWithClosingTag_475) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeText("hello", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// Test: startElement and endElement produce valid XML structure
TEST_F(XmlWriterTest_475, StartAndEndElementProduceValidXml_475) {
    XmlWriter writer(oss);
    writer.startElement("outer", XmlFormatting::None);
    writer.startElement("inner", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("<outer"), std::string::npos);
    EXPECT_NE(output.find("/>"), std::string::npos); // inner self-closes
    EXPECT_NE(output.find("</outer>"), std::string::npos);
}

// Test: endElement returns reference to the XmlWriter (chaining)
TEST_F(XmlWriterTest_475, EndElementReturnsSelf_475) {
    XmlWriter writer(oss);
    writer.startElement("a", XmlFormatting::None);
    XmlWriter& ref = writer.endElement(XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// Test: Nested elements produce correct closing tags in correct order
TEST_F(XmlWriterTest_475, NestedElementsCloseInOrder_475) {
    XmlWriter writer(oss);
    writer.startElement("a", XmlFormatting::None);
    writer.writeText("text", XmlFormatting::None);
    writer.startElement("b", XmlFormatting::None);
    writer.writeText("inner", XmlFormatting::None);
    writer.endElement(XmlFormatting::None); // closes b
    writer.endElement(XmlFormatting::None); // closes a
    std::string output = oss.str();
    EXPECT_NE(output.find("</b>"), std::string::npos);
    EXPECT_NE(output.find("</a>"), std::string::npos);
    // </b> should appear before </a>
    EXPECT_LT(output.find("</b>"), output.find("</a>"));
}

// Test: endElement with Newline formatting
TEST_F(XmlWriterTest_475, EndElementWithNewlineFormatting_475) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText("content", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("</root>"), std::string::npos);
    // Should end with a newline after closing tag
    // The exact position depends on formatting, but the closing tag should be present
}

// Test: endElement with Indent formatting
TEST_F(XmlWriterTest_475, EndElementWithIndentFormatting_475) {
    XmlWriter writer(oss);
    writer.startElement("outer", XmlFormatting::Indent);
    writer.startElement("inner", XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Indent);
    std::string output = oss.str();
    EXPECT_NE(output.find("<outer"), std::string::npos);
}

// Test: startElement returns reference for chaining
TEST_F(XmlWriterTest_475, StartElementReturnsSelf_475) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("root", XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::None);
}

// Test: writeAttribute adds attribute to current element
TEST_F(XmlWriterTest_475, WriteAttributeAddsAttribute_475) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("key"_catch_sr, "value"_catch_sr);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("key=\"value\""), std::string::npos);
}

// Test: writeAttribute with bool true
TEST_F(XmlWriterTest_475, WriteAttributeBoolTrue_475) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("flag"_catch_sr, true);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos);
}

// Test: writeAttribute with bool false
TEST_F(XmlWriterTest_475, WriteAttributeBoolFalse_475) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("flag"_catch_sr, false);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"false\""), std::string::npos);
}

// Test: writeText includes text content
TEST_F(XmlWriterTest_475, WriteTextIncludesContent_475) {
    XmlWriter writer(oss);
    writer.startElement("p", XmlFormatting::None);
    writer.writeText("Hello World", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello World"), std::string::npos);
    EXPECT_NE(output.find("</p>"), std::string::npos);
}

// Test: writeComment produces XML comment
TEST_F(XmlWriterTest_475, WriteCommentProducesComment_475) {
    XmlWriter writer(oss);
    writer.writeComment("this is a comment", XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
}

// Test: writeStylesheetRef writes processing instruction
TEST_F(XmlWriterTest_475, WriteStylesheetRefProducesPI_475) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl");
    std::string output = oss.str();
    EXPECT_NE(output.find("style.xsl"), std::string::npos);
    EXPECT_NE(output.find("<?xml-stylesheet"), std::string::npos);
}

// Test: ensureTagClosed closes an open tag
TEST_F(XmlWriterTest_475, EnsureTagClosedClosesOpenTag_475) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.ensureTagClosed();
    std::string output = oss.str();
    // After ensuring tag is closed, the tag should have a closing >
    EXPECT_NE(output.find("<elem>"), std::string::npos);
}

// Test: Multiple attributes on same element
TEST_F(XmlWriterTest_475, MultipleAttributesOnElement_475) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("a"_catch_sr, "1"_catch_sr);
    writer.writeAttribute("b"_catch_sr, "2"_catch_sr);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
}

// Test: Empty text does not break XML structure
TEST_F(XmlWriterTest_475, EmptyTextDoesNotBreakXml_475) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeText("", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Element should still be well-formed
    EXPECT_NE(output.find("elem"), std::string::npos);
}

// Test: ScopedElement automatically closes on destruction
TEST_F(XmlWriterTest_475, ScopedElementAutoCloses_475) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("auto", XmlFormatting::None);
    }
    std::string output = oss.str();
    // The element should be closed (either self-closing or with end tag)
    bool selfClosed = output.find("/>") != std::string::npos;
    bool endTagClosed = output.find("</auto>") != std::string::npos;
    EXPECT_TRUE(selfClosed || endTagClosed);
}

// Test: Deeply nested elements
TEST_F(XmlWriterTest_475, DeeplyNestedElements_475) {
    XmlWriter writer(oss);
    writer.startElement("a", XmlFormatting::None);
    writer.startElement("b", XmlFormatting::None);
    writer.startElement("c", XmlFormatting::None);
    writer.startElement("d", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("<a"), std::string::npos);
    EXPECT_NE(output.find("</a>"), std::string::npos);
}

// Test: writeAttribute with const char*
TEST_F(XmlWriterTest_475, WriteAttributeConstCharPtr_475) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("name"_catch_sr, "test_value");
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("name=\"test_value\""), std::string::npos);
}

// Test: Self-closing tag does not produce end tag
TEST_F(XmlWriterTest_475, SelfClosingTagNoEndTag_475) {
    XmlWriter writer(oss);
    writer.startElement("empty", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Should be self-closing, no </empty>
    EXPECT_NE(output.find("/>"), std::string::npos);
    EXPECT_EQ(output.find("</empty>"), std::string::npos);
}

// Test: endElement after writeText produces closing tag not self-closing
TEST_F(XmlWriterTest_475, EndElementAfterWriteTextProducesClosingTag_475) {
    XmlWriter writer(oss);
    writer.startElement("data", XmlFormatting::None);
    writer.writeText("value", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("</data>"), std::string::npos);
    // Self-closing should NOT be present for this element
    // (though the inner structure might have sub-elements that self-close)
}

// Test: XmlFormatting::None produces no extra whitespace
TEST_F(XmlWriterTest_475, NoFormattingNoExtraWhitespace_475) {
    XmlWriter writer(oss);
    writer.startElement("a", XmlFormatting::None);
    writer.writeText("x", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // With None formatting, there should be no newline between text and end tag
    EXPECT_NE(output.find("x</a>"), std::string::npos);
}

// Test: writeAttribute with integer (template version)
TEST_F(XmlWriterTest_475, WriteAttributeWithInteger_475) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute("count"_catch_sr, 42);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("count=\"42\""), std::string::npos);
}
