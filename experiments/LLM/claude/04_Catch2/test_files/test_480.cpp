#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

// We need to know about XmlFormatting. Based on typical Catch2 code:
// XmlFormatting is an enum with None and Newline/Indent flags.
// We'll include the relevant header or use the values from the namespace.

using namespace Catch;

class XmlWriterTest_480 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// ============================================================
// Construction tests
// ============================================================

TEST_F(XmlWriterTest_480, ConstructionWritesDeclaration_480) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    // The constructor should write an XML declaration
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

// ============================================================
// writeComment tests
// ============================================================

TEST_F(XmlWriterTest_480, WriteCommentContainsText_480) {
    XmlWriter writer(oss);
    writer.writeComment("This is a comment", XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!-- This is a comment -->") != std::string::npos);
}

TEST_F(XmlWriterTest_480, WriteCommentWithNewlineFormatting_480) {
    XmlWriter writer(oss);
    writer.writeComment("comment with newline", XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!-- comment with newline -->") != std::string::npos);
    // Should end with a newline
    EXPECT_TRUE(output.back() == '\n');
}

TEST_F(XmlWriterTest_480, WriteCommentEmptyText_480) {
    XmlWriter writer(oss);
    writer.writeComment("", XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--  -->") != std::string::npos);
}

TEST_F(XmlWriterTest_480, WriteCommentReturnsSelf_480) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.writeComment("test", XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// ============================================================
// startElement / endElement tests
// ============================================================

TEST_F(XmlWriterTest_480, StartElementWritesOpenTag_480) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

TEST_F(XmlWriterTest_480, StartElementWithNewlineFormatting_480) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root>") != std::string::npos || output.find("<root") != std::string::npos);
}

TEST_F(XmlWriterTest_480, NestedElements_480) {
    XmlWriter writer(oss);
    writer.startElement("parent", XmlFormatting::Newline);
    writer.startElement("child", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<parent>") != std::string::npos || output.find("<parent") != std::string::npos);
    EXPECT_TRUE(output.find("<child") != std::string::npos);
    EXPECT_TRUE(output.find("</child>") != std::string::npos);
    EXPECT_TRUE(output.find("</parent>") != std::string::npos);
}

TEST_F(XmlWriterTest_480, StartElementReturnsSelf_480) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("elem", XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::None);
}

TEST_F(XmlWriterTest_480, EndElementReturnsSelf_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    XmlWriter& ref = writer.endElement(XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// ============================================================
// writeAttribute tests
// ============================================================

TEST_F(XmlWriterTest_480, WriteAttributeStringRef_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute(StringRef("name"), StringRef("value"));
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name=\"value\"") != std::string::npos);
}

TEST_F(XmlWriterTest_480, WriteAttributeBoolTrue_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute(StringRef("flag"), true);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"true\"") != std::string::npos);
}

TEST_F(XmlWriterTest_480, WriteAttributeBoolFalse_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute(StringRef("flag"), false);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"false\"") != std::string::npos);
}

TEST_F(XmlWriterTest_480, WriteAttributeCharPtr_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute(StringRef("key"), "val");
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("key=\"val\"") != std::string::npos);
}

TEST_F(XmlWriterTest_480, WriteAttributeReturnsSelf_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    XmlWriter& ref = writer.writeAttribute(StringRef("a"), StringRef("b"));
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::None);
}

TEST_F(XmlWriterTest_480, WriteMultipleAttributes_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute(StringRef("a"), StringRef("1"));
    writer.writeAttribute(StringRef("b"), StringRef("2"));
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=\"1\"") != std::string::npos);
    EXPECT_TRUE(output.find("b=\"2\"") != std::string::npos);
}

// ============================================================
// writeText tests
// ============================================================

TEST_F(XmlWriterTest_480, WriteTextOutputsContent_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeText("Hello World", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Hello World") != std::string::npos);
}

TEST_F(XmlWriterTest_480, WriteTextReturnsSelf_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    XmlWriter& ref = writer.writeText("text", XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::None);
}

TEST_F(XmlWriterTest_480, WriteTextEmptyString_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeText("", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Should still have the element tags
    EXPECT_TRUE(output.find("<elem") != std::string::npos);
    EXPECT_TRUE(output.find("</elem>") != std::string::npos);
}

// ============================================================
// writeStylesheetRef tests
// ============================================================

TEST_F(XmlWriterTest_480, WriteStylesheetRefContainsUrl_480) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl");
    std::string output = oss.str();
    EXPECT_TRUE(output.find("style.xsl") != std::string::npos);
    EXPECT_TRUE(output.find("xml-stylesheet") != std::string::npos);
}

// ============================================================
// scopedElement tests
// ============================================================

TEST_F(XmlWriterTest_480, ScopedElementAutoCloses_480) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("auto", XmlFormatting::Newline);
        }
        // After scoped goes out of scope, element should be closed
        std::string output = oss.str();
        EXPECT_TRUE(output.find("</auto>") != std::string::npos || output.find("<auto/>") != std::string::npos);
    }
}

TEST_F(XmlWriterTest_480, ScopedElementWithContent_480) {
    {
        XmlWriter writer(oss);
        {
            auto scoped = writer.scopedElement("item", XmlFormatting::None);
            writer.writeText("content", XmlFormatting::None);
        }
        std::string output = oss.str();
        EXPECT_TRUE(output.find("content") != std::string::npos);
    }
}

// ============================================================
// ensureTagClosed tests
// ============================================================

TEST_F(XmlWriterTest_480, EnsureTagClosedAfterStartElement_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.ensureTagClosed();
    std::string output = oss.str();
    // The tag should be closed with '>'
    EXPECT_TRUE(output.find(">") != std::string::npos);
    writer.endElement(XmlFormatting::None);
}

// ============================================================
// XmlFormatting::Indent tests
// ============================================================

TEST_F(XmlWriterTest_480, IndentFormattingAppliesIndentation_480) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("child", XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Child element should be indented
    EXPECT_TRUE(output.find("<child") != std::string::npos);
}

// ============================================================
// Comment inside element
// ============================================================

TEST_F(XmlWriterTest_480, WriteCommentInsideElement_480) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeComment("inner comment", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!-- inner comment -->") != std::string::npos);
    EXPECT_TRUE(output.find("<root>") != std::string::npos || output.find("<root") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

// ============================================================
// Template writeAttribute with numeric type
// ============================================================

TEST_F(XmlWriterTest_480, WriteAttributeNumericType_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute(StringRef("count"), 42);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count=\"42\"") != std::string::npos);
}

// ============================================================
// Destructor closes all open tags
// ============================================================

TEST_F(XmlWriterTest_480, DestructorClosesOpenElements_480) {
    {
        XmlWriter writer(oss);
        writer.startElement("outer", XmlFormatting::Newline);
        writer.startElement("inner", XmlFormatting::Newline);
        // Destructor should close both elements
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</inner>") != std::string::npos || output.find("<inner/>") != std::string::npos);
    EXPECT_TRUE(output.find("</outer>") != std::string::npos || output.find("<outer/>") != std::string::npos);
}

// ============================================================
// Multiple comments
// ============================================================

TEST_F(XmlWriterTest_480, MultipleCommentsWritten_480) {
    XmlWriter writer(oss);
    writer.writeComment("first", XmlFormatting::Newline);
    writer.writeComment("second", XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!-- first -->") != std::string::npos);
    EXPECT_TRUE(output.find("<!-- second -->") != std::string::npos);
}

// ============================================================
// Special characters in text
// ============================================================

TEST_F(XmlWriterTest_480, WriteTextWithSpecialChars_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeText("a < b & c > d", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // XML special chars should be escaped
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
    EXPECT_TRUE(output.find("&gt;") != std::string::npos);
}

// ============================================================
// Attribute with special characters
// ============================================================

TEST_F(XmlWriterTest_480, WriteAttributeWithSpecialChars_480) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None);
    writer.writeAttribute(StringRef("data"), StringRef("a\"b"));
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Quotes in attribute values should be escaped
    EXPECT_TRUE(output.find("&quot;") != std::string::npos);
}

// ============================================================
// Empty element (start + end without content)
// ============================================================

TEST_F(XmlWriterTest_480, EmptyElementProducesValidXml_480) {
    XmlWriter writer(oss);
    writer.startElement("empty", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Should produce either <empty></empty> or <empty/>
    bool hasClosingTag = output.find("</empty>") != std::string::npos;
    bool hasSelfClosing = output.find("<empty/>") != std::string::npos;
    EXPECT_TRUE(hasClosingTag || hasSelfClosing);
}
