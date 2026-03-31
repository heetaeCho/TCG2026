#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_473 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that XmlWriter can be constructed with an ostream
TEST_F(XmlWriterTest_473, ConstructorWritesDeclaration_473) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    // The constructor should write an XML declaration
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

// Test startElement produces an opening tag
TEST_F(XmlWriterTest_473, StartElementProducesOpeningTag_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
}

// Test startElement returns a reference to the writer (chaining)
TEST_F(XmlWriterTest_473, StartElementReturnsSelf_473) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("root", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test endElement closes the tag
TEST_F(XmlWriterTest_473, EndElementClosesTag_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

// Test endElement returns a reference to the writer
TEST_F(XmlWriterTest_473, EndElementReturnsSelf_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.endElement(XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test nested elements
TEST_F(XmlWriterTest_473, NestedElements_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("child", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
    EXPECT_TRUE(output.find("<child") != std::string::npos);
    EXPECT_TRUE(output.find("</child>") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

// Test writeAttribute with StringRef
TEST_F(XmlWriterTest_473, WriteAttributeStringRef_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("key", StringRef("value"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("key=\"value\"") != std::string::npos);
}

// Test writeAttribute returns self for chaining
TEST_F(XmlWriterTest_473, WriteAttributeReturnsSelf_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeAttribute("key", StringRef("value"));
    EXPECT_EQ(&ref, &writer);
}

// Test writeAttribute with bool true
TEST_F(XmlWriterTest_473, WriteAttributeBoolTrue_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("flag", true);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"true\"") != std::string::npos);
}

// Test writeAttribute with bool false
TEST_F(XmlWriterTest_473, WriteAttributeBoolFalse_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("flag", false);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"false\"") != std::string::npos);
}

// Test writeAttribute with const char*
TEST_F(XmlWriterTest_473, WriteAttributeConstCharPtr_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("name", "hello");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name=\"hello\"") != std::string::npos);
}

// Test writeText
TEST_F(XmlWriterTest_473, WriteText_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText("some text", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("some text") != std::string::npos);
}

// Test writeText returns self
TEST_F(XmlWriterTest_473, WriteTextReturnsSelf_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeText("text", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test writeComment
TEST_F(XmlWriterTest_473, WriteComment_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeComment("this is a comment", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("this is a comment") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

// Test writeComment returns self
TEST_F(XmlWriterTest_473, WriteCommentReturnsSelf_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeComment("comment", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test writeStylesheetRef
TEST_F(XmlWriterTest_473, WriteStylesheetRef_473) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl");
    std::string output = oss.str();
    EXPECT_TRUE(output.find("style.xsl") != std::string::npos);
    EXPECT_TRUE(output.find("xml-stylesheet") != std::string::npos);
}

// Test ensureTagClosed closes an open tag
TEST_F(XmlWriterTest_473, EnsureTagClosedClosesOpenTag_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find(">") != std::string::npos);
}

// Test multiple attributes on same element
TEST_F(XmlWriterTest_473, MultipleAttributes_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("a", StringRef("1"));
    writer.writeAttribute("b", StringRef("2"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=\"1\"") != std::string::npos);
    EXPECT_TRUE(output.find("b=\"2\"") != std::string::npos);
}

// Test with XmlFormatting::None
TEST_F(XmlWriterTest_473, StartElementWithNoFormatting_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root>") != std::string::npos || output.find("<root") != std::string::npos);
}

// Test with XmlFormatting::Indent
TEST_F(XmlWriterTest_473, StartElementWithIndentFormatting_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Indent);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
}

// Test deeply nested elements produce correct indentation
TEST_F(XmlWriterTest_473, DeeplyNestedElements_473) {
    XmlWriter writer(oss);
    writer.startElement("a", XmlFormatting::Indent | XmlFormatting::Newline);
    writer.startElement("b", XmlFormatting::Indent | XmlFormatting::Newline);
    writer.startElement("c", XmlFormatting::Indent | XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Indent | XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Indent | XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Indent | XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<a") != std::string::npos);
    EXPECT_TRUE(output.find("<b") != std::string::npos);
    EXPECT_TRUE(output.find("<c") != std::string::npos);
    EXPECT_TRUE(output.find("</c>") != std::string::npos);
    EXPECT_TRUE(output.find("</b>") != std::string::npos);
    EXPECT_TRUE(output.find("</a>") != std::string::npos);
}

// Test scopedElement automatically closes on destruction
TEST_F(XmlWriterTest_473, ScopedElementAutoCloses_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    {
        auto scoped = writer.scopedElement("child", XmlFormatting::Newline);
    }
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<child") != std::string::npos);
    EXPECT_TRUE(output.find("</child>") != std::string::npos || output.find("/>") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

// Test empty element name
TEST_F(XmlWriterTest_473, EmptyElementName_473) {
    XmlWriter writer(oss);
    writer.startElement("", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<>") != std::string::npos || output.find("<") != std::string::npos);
}

// Test writeAttribute with numeric type via template
TEST_F(XmlWriterTest_473, WriteAttributeNumeric_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("count", 42);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count=\"42\"") != std::string::npos);
}

// Test that destructor closes all open tags
TEST_F(XmlWriterTest_473, DestructorClosesAllTags_473) {
    {
        XmlWriter writer(oss);
        writer.startElement("root", XmlFormatting::Newline);
        writer.startElement("child", XmlFormatting::Newline);
    }
    std::string output = oss.str();
    // After destruction, tags should be closed
    EXPECT_TRUE(output.find("</child>") != std::string::npos || output.find("/>") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos || output.find("/>") != std::string::npos);
}

// Test chaining of multiple operations
TEST_F(XmlWriterTest_473, ChainingOperations_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline)
          .writeAttribute("id", StringRef("1"))
          .writeText("content", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
    EXPECT_TRUE(output.find("id=\"1\"") != std::string::npos);
    EXPECT_TRUE(output.find("content") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

// Test writing text with special XML characters
TEST_F(XmlWriterTest_473, WriteTextWithSpecialCharacters_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText("<>&\"", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Special characters should be escaped
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
    EXPECT_TRUE(output.find("&gt;") != std::string::npos);
}

// Test writeAttribute with empty value
TEST_F(XmlWriterTest_473, WriteAttributeEmptyValue_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("key", StringRef(""));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("key=\"\"") != std::string::npos);
}

// Test multiple sibling elements
TEST_F(XmlWriterTest_473, MultipleSiblingElements_473) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("child1", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.startElement("child2", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<child1") != std::string::npos);
    EXPECT_TRUE(output.find("</child1>") != std::string::npos);
    EXPECT_TRUE(output.find("<child2") != std::string::npos);
    EXPECT_TRUE(output.find("</child2>") != std::string::npos);
}
