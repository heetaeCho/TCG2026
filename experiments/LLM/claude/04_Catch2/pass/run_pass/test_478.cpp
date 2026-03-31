#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_478 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that constructing XmlWriter writes an XML declaration
TEST_F(XmlWriterTest_478, ConstructorWritesDeclaration_478) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

// Test startElement writes an opening tag
TEST_F(XmlWriterTest_478, StartElementWritesOpeningTag_478) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("<root"), std::string::npos);
}

// Test endElement closes the tag
TEST_F(XmlWriterTest_478, EndElementClosesTag_478) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// Test writeAttribute with StringRef name and StringRef value
TEST_F(XmlWriterTest_478, WriteAttributeStringRef_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("key"), StringRef("value"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("key=\"value\""), std::string::npos);
}

// Test writeAttribute with char const* value
TEST_F(XmlWriterTest_478, WriteAttributeCharPtr_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("name"), "hello");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("name=\"hello\""), std::string::npos);
}

// Test writeAttribute with bool true
TEST_F(XmlWriterTest_478, WriteAttributeBoolTrue_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("flag"), true);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos);
}

// Test writeAttribute with bool false
TEST_F(XmlWriterTest_478, WriteAttributeBoolFalse_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("flag"), false);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"false\""), std::string::npos);
}

// Test writeText writes text content
TEST_F(XmlWriterTest_478, WriteTextContent_478) {
    XmlWriter writer(oss);
    writer.startElement("msg", XmlFormatting::Newline);
    writer.writeText(StringRef("Hello World"), XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

// Test writeComment writes an XML comment
TEST_F(XmlWriterTest_478, WriteComment_478) {
    XmlWriter writer(oss);
    writer.writeComment(StringRef("This is a comment"), XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("This is a comment"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
}

// Test writeStylesheetRef writes a stylesheet processing instruction
TEST_F(XmlWriterTest_478, WriteStylesheetRef_478) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef(StringRef("style.xsl"));
    std::string output = oss.str();
    EXPECT_NE(output.find("style.xsl"), std::string::npos);
    EXPECT_NE(output.find("xml-stylesheet"), std::string::npos);
}

// Test nested elements produce proper structure
TEST_F(XmlWriterTest_478, NestedElements_478) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("child", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<root"), std::string::npos);
    EXPECT_NE(output.find("<child"), std::string::npos);
    EXPECT_NE(output.find("</child>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// Test ensureTagClosed closes an open tag
TEST_F(XmlWriterTest_478, EnsureTagClosed_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find(">"), std::string::npos);
}

// Test writeAttribute returns reference for chaining
TEST_F(XmlWriterTest_478, WriteAttributeChaining_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeAttribute(StringRef("a"), StringRef("1"));
    ref.writeAttribute(StringRef("b"), StringRef("2"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
}

// Test startElement returns reference for chaining
TEST_F(XmlWriterTest_478, StartElementChaining_478) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("root", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test endElement returns reference for chaining
TEST_F(XmlWriterTest_478, EndElementChaining_478) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.endElement(XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test writeText returns reference for chaining
TEST_F(XmlWriterTest_478, WriteTextChaining_478) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeText(StringRef("text"), XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test writeComment returns reference for chaining
TEST_F(XmlWriterTest_478, WriteCommentChaining_478) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.writeComment(StringRef("comment"), XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test writeAttribute with empty attribute value
TEST_F(XmlWriterTest_478, WriteAttributeEmptyValue_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("key"), StringRef(""));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("key=\"\""), std::string::npos);
}

// Test writeText with empty text
TEST_F(XmlWriterTest_478, WriteTextEmpty_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.writeText(StringRef(""), XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Should still have opening and closing tags
    EXPECT_NE(output.find("<item"), std::string::npos);
}

// Test multiple attributes on same element
TEST_F(XmlWriterTest_478, MultipleAttributes_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("a"), StringRef("1"));
    writer.writeAttribute(StringRef("b"), StringRef("2"));
    writer.writeAttribute(StringRef("c"), StringRef("3"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
    EXPECT_NE(output.find("c=\"3\""), std::string::npos);
}

// Test special characters in text are escaped
TEST_F(XmlWriterTest_478, WriteTextSpecialCharacters_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.writeText(StringRef("<>&\""), XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // The raw < > & " should be escaped
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

// Test special characters in attribute values are escaped
TEST_F(XmlWriterTest_478, WriteAttributeSpecialCharacters_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("val"), StringRef("<>&\""));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

// Test scopedElement auto-closes on scope exit
TEST_F(XmlWriterTest_478, ScopedElementAutoCloses_478) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("scoped", XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("<scoped"), std::string::npos);
    EXPECT_NE(output.find("</scoped>"), std::string::npos);
}

// Test writeAttribute with template (numeric type)
TEST_F(XmlWriterTest_478, WriteAttributeNumeric_478) {
    XmlWriter writer(oss);
    writer.startElement("item", XmlFormatting::Newline);
    writer.writeAttribute(StringRef("count"), 42);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("count=\"42\""), std::string::npos);
}

// Test destructor closes all open tags
TEST_F(XmlWriterTest_478, DestructorClosesAllTags_478) {
    {
        XmlWriter writer(oss);
        writer.startElement("root", XmlFormatting::Newline);
        writer.startElement("child", XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("</child>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// Test XmlFormatting::None produces no extra formatting
TEST_F(XmlWriterTest_478, FormattingNone_478) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("<root"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// Test writing multiple sibling elements
TEST_F(XmlWriterTest_478, MultipleSiblingElements_478) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("a", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.startElement("b", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<a"), std::string::npos);
    EXPECT_NE(output.find("</a>"), std::string::npos);
    EXPECT_NE(output.find("<b"), std::string::npos);
    EXPECT_NE(output.find("</b>"), std::string::npos);
}
