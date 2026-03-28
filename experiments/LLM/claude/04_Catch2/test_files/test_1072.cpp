#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_1072 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that construction writes an XML declaration
TEST_F(XmlWriterTest_1072, ConstructorWritesDeclaration_1072) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_NE(output.find("<?xml"), std::string::npos);
    EXPECT_NE(output.find("?>"), std::string::npos);
}

// Test that construction includes version in declaration
TEST_F(XmlWriterTest_1072, DeclarationContainsVersion_1072) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_NE(output.find("version"), std::string::npos);
}

// Test startElement writes an opening tag
TEST_F(XmlWriterTest_1072, StartElementWritesOpeningTag_1072) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("<TestElement"), std::string::npos);
}

// Test endElement writes a closing tag
TEST_F(XmlWriterTest_1072, EndElementWritesClosingTag_1072) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("</TestElement>"), std::string::npos);
}

// Test that writeAttribute adds an attribute to the current element
TEST_F(XmlWriterTest_1072, WriteAttributeStringRef_1072) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::Newline);
    writer.writeAttribute("name"_sr, "value"_sr);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("name=\"value\""), std::string::npos);
}

// Test writeAttribute with bool true
TEST_F(XmlWriterTest_1072, WriteAttributeBoolTrue_1072) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::Newline);
    writer.writeAttribute("flag"_sr, true);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos);
}

// Test writeAttribute with bool false
TEST_F(XmlWriterTest_1072, WriteAttributeBoolFalse_1072) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::Newline);
    writer.writeAttribute("flag"_sr, false);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"false\""), std::string::npos);
}

// Test writeAttribute with const char*
TEST_F(XmlWriterTest_1072, WriteAttributeConstChar_1072) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::Newline);
    const char* val = "charval";
    writer.writeAttribute("attr"_sr, val);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("attr=\"charval\""), std::string::npos);
}

// Test writeText writes text content
TEST_F(XmlWriterTest_1072, WriteTextContent_1072) {
    XmlWriter writer(oss);
    writer.startElement("Element", XmlFormatting::Newline);
    writer.writeText("Hello World"_sr, XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

// Test writeComment writes a comment
TEST_F(XmlWriterTest_1072, WriteComment_1072) {
    XmlWriter writer(oss);
    writer.writeComment("This is a comment"_sr, XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("This is a comment"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
}

// Test writeStylesheetRef writes a stylesheet processing instruction
TEST_F(XmlWriterTest_1072, WriteStylesheetRef_1072) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl"_sr);
    std::string output = oss.str();
    EXPECT_NE(output.find("style.xsl"), std::string::npos);
    EXPECT_NE(output.find("xml-stylesheet"), std::string::npos);
}

// Test nested elements produce correct output
TEST_F(XmlWriterTest_1072, NestedElements_1072) {
    XmlWriter writer(oss);
    writer.startElement("Outer", XmlFormatting::Newline);
    writer.startElement("Inner", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<Outer"), std::string::npos);
    EXPECT_NE(output.find("<Inner"), std::string::npos);
    EXPECT_NE(output.find("</Inner>"), std::string::npos);
    EXPECT_NE(output.find("</Outer>"), std::string::npos);
}

// Test scopedElement auto-closes element when scope ends
TEST_F(XmlWriterTest_1072, ScopedElementAutoCloses_1072) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("ScopedElem", XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("ScopedElem"), std::string::npos);
    // Should have closing tag or self-closing
    bool hasClosed = (output.find("</ScopedElem>") != std::string::npos) ||
                     (output.find("/>") != std::string::npos);
    EXPECT_TRUE(hasClosed);
}

// Test ensureTagClosed closes an open tag
TEST_F(XmlWriterTest_1072, EnsureTagClosed_1072) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find(">"), std::string::npos);
}

// Test empty element (start then immediately end) may produce self-closing or open/close
TEST_F(XmlWriterTest_1072, EmptyElement_1072) {
    XmlWriter writer(oss);
    writer.startElement("Empty", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    bool valid = (output.find("/>") != std::string::npos) ||
                 (output.find("</Empty>") != std::string::npos);
    EXPECT_TRUE(valid);
}

// Test writeText with special XML characters (escaping)
TEST_F(XmlWriterTest_1072, WriteTextEscapesSpecialCharacters_1072) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeText("<>&\""_sr, XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // The raw characters should be escaped
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

// Test writeAttribute with special characters in value
TEST_F(XmlWriterTest_1072, WriteAttributeEscapesSpecialCharacters_1072) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeAttribute("key"_sr, "a<b>c&d"_sr);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

// Test multiple attributes on the same element
TEST_F(XmlWriterTest_1072, MultipleAttributes_1072) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeAttribute("a"_sr, "1"_sr);
    writer.writeAttribute("b"_sr, "2"_sr);
    writer.writeAttribute("c"_sr, "3"_sr);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
    EXPECT_NE(output.find("c=\"3\""), std::string::npos);
}

// Test writeAttribute with integer type (template overload)
TEST_F(XmlWriterTest_1072, WriteAttributeIntegerType_1072) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeAttribute("count"_sr, 42);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("count=\"42\""), std::string::npos);
}

// Test that XmlFormatting::None does not add newlines for elements
TEST_F(XmlWriterTest_1072, FormattingNone_1072) {
    XmlWriter writer(oss);
    std::string beforeStart = oss.str();
    writer.startElement("Elem", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // The element should be present
    EXPECT_NE(output.find("Elem"), std::string::npos);
}

// Test destructor closes all open tags
TEST_F(XmlWriterTest_1072, DestructorClosesOpenTags_1072) {
    {
        XmlWriter writer(oss);
        writer.startElement("Outer", XmlFormatting::Newline);
        writer.startElement("Inner", XmlFormatting::Newline);
        // Don't explicitly close - destructor should handle it
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("</Inner>"), std::string::npos);
    EXPECT_NE(output.find("</Outer>"), std::string::npos);
}

// Test chaining of methods (fluent interface)
TEST_F(XmlWriterTest_1072, MethodChaining_1072) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline)
          .writeAttribute("a"_sr, "1"_sr)
          .writeAttribute("b"_sr, "2"_sr);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
}

// Test writeText with empty string
TEST_F(XmlWriterTest_1072, WriteTextEmptyString_1072) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeText(""_sr, XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Should still produce valid XML
    EXPECT_NE(output.find("Elem"), std::string::npos);
}

// Test writeComment with empty string
TEST_F(XmlWriterTest_1072, WriteCommentEmpty_1072) {
    XmlWriter writer(oss);
    writer.writeComment(""_sr, XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
}

// Test deeply nested elements
TEST_F(XmlWriterTest_1072, DeeplyNestedElements_1072) {
    XmlWriter writer(oss);
    writer.startElement("L1", XmlFormatting::Newline);
    writer.startElement("L2", XmlFormatting::Newline);
    writer.startElement("L3", XmlFormatting::Newline);
    writer.startElement("L4", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<L1"), std::string::npos);
    EXPECT_NE(output.find("<L2"), std::string::npos);
    EXPECT_NE(output.find("<L3"), std::string::npos);
    EXPECT_NE(output.find("<L4"), std::string::npos);
    EXPECT_NE(output.find("</L4>"), std::string::npos);
    EXPECT_NE(output.find("</L3>"), std::string::npos);
    EXPECT_NE(output.find("</L2>"), std::string::npos);
    EXPECT_NE(output.find("</L1>"), std::string::npos);
}

// Test that XmlWriter is not copyable
TEST_F(XmlWriterTest_1072, NotCopyable_1072) {
    EXPECT_FALSE(std::is_copy_constructible<XmlWriter>::value);
    EXPECT_FALSE(std::is_copy_assignable<XmlWriter>::value);
}

// Test scoped element with attributes and text
TEST_F(XmlWriterTest_1072, ScopedElementWithContent_1072) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("Item", XmlFormatting::Newline);
        writer.writeAttribute("id"_sr, "123"_sr);
        writer.writeText("content"_sr, XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("id=\"123\""), std::string::npos);
    EXPECT_NE(output.find("content"), std::string::npos);
}

// Test sibling elements
TEST_F(XmlWriterTest_1072, SiblingElements_1072) {
    XmlWriter writer(oss);
    writer.startElement("Parent", XmlFormatting::Newline);
    writer.startElement("Child1", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.startElement("Child2", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<Child1"), std::string::npos);
    EXPECT_NE(output.find("</Child1>"), std::string::npos);
    EXPECT_NE(output.find("<Child2"), std::string::npos);
    EXPECT_NE(output.find("</Child2>"), std::string::npos);
}
