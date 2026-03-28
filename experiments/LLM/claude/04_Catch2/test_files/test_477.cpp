#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_477 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that XmlWriter can be constructed with an ostream
TEST_F(XmlWriterTest_477, ConstructorWritesDeclaration_477) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    // The constructor should write an XML declaration
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

// Test writeAttribute with bool true
TEST_F(XmlWriterTest_477, WriteAttributeBoolTrue_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeAttribute("flag"_sr, true);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"true\"") != std::string::npos);
}

// Test writeAttribute with bool false
TEST_F(XmlWriterTest_477, WriteAttributeBoolFalse_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeAttribute("flag"_sr, false);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"false\"") != std::string::npos);
}

// Test writeAttribute with StringRef
TEST_F(XmlWriterTest_477, WriteAttributeStringRef_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeAttribute("name"_sr, "value"_sr);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name=\"value\"") != std::string::npos);
}

// Test writeAttribute with const char*
TEST_F(XmlWriterTest_477, WriteAttributeConstCharPtr_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeAttribute("name"_sr, "charvalue");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name=\"charvalue\"") != std::string::npos);
}

// Test startElement creates an element tag
TEST_F(XmlWriterTest_477, StartElementCreatesTag_477) {
    XmlWriter writer(oss);
    writer.startElement("myElement", XmlFormatting::None);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<myElement") != std::string::npos);
}

// Test endElement closes the element
TEST_F(XmlWriterTest_477, EndElementClosesTag_477) {
    XmlWriter writer(oss);
    writer.startElement("myElement", XmlFormatting::None);
    writer.ensureTagClosed();
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</myElement>") != std::string::npos);
}

// Test writeText writes text content
TEST_F(XmlWriterTest_477, WriteTextContent_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeText("hello world"_sr, XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("hello world") != std::string::npos);
}

// Test writeComment writes a comment
TEST_F(XmlWriterTest_477, WriteComment_477) {
    XmlWriter writer(oss);
    writer.writeComment("this is a comment"_sr, XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("this is a comment") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

// Test writeStylesheetRef
TEST_F(XmlWriterTest_477, WriteStylesheetRef_477) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl"_sr);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("style.xsl") != std::string::npos);
    EXPECT_TRUE(output.find("xml-stylesheet") != std::string::npos);
}

// Test chaining writeAttribute returns reference to XmlWriter
TEST_F(XmlWriterTest_477, WriteAttributeChaining_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    XmlWriter& ref = writer.writeAttribute("a"_sr, true);
    EXPECT_EQ(&ref, &writer);
}

// Test chaining writeAttribute with StringRef returns reference
TEST_F(XmlWriterTest_477, WriteAttributeStringRefChaining_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    XmlWriter& ref = writer.writeAttribute("a"_sr, "b"_sr);
    EXPECT_EQ(&ref, &writer);
}

// Test multiple attributes on the same element
TEST_F(XmlWriterTest_477, MultipleAttributes_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeAttribute("attr1"_sr, "val1"_sr);
    writer.writeAttribute("attr2"_sr, true);
    writer.writeAttribute("attr3"_sr, false);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("attr1=\"val1\"") != std::string::npos);
    EXPECT_TRUE(output.find("attr2=\"true\"") != std::string::npos);
    EXPECT_TRUE(output.find("attr3=\"false\"") != std::string::npos);
}

// Test nested elements
TEST_F(XmlWriterTest_477, NestedElements_477) {
    XmlWriter writer(oss);
    writer.startElement("outer", XmlFormatting::None);
    writer.startElement("inner", XmlFormatting::None);
    writer.ensureTagClosed();
    writer.endElement(XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<outer") != std::string::npos);
    EXPECT_TRUE(output.find("<inner") != std::string::npos);
    EXPECT_TRUE(output.find("</inner>") != std::string::npos);
    EXPECT_TRUE(output.find("</outer>") != std::string::npos);
}

// Test scopedElement automatically closes element
TEST_F(XmlWriterTest_477, ScopedElementAutoClose_477) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("scoped", XmlFormatting::None);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<scoped") != std::string::npos);
    // The scoped element should be closed after scope exit
    EXPECT_TRUE(output.find("</scoped>") != std::string::npos || output.find("/>") != std::string::npos);
}

// Test empty text write
TEST_F(XmlWriterTest_477, WriteEmptyText_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeText(""_sr, XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<element") != std::string::npos);
}

// Test writeAttribute with empty string value
TEST_F(XmlWriterTest_477, WriteAttributeEmptyValue_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeAttribute("name"_sr, ""_sr);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name=\"\"") != std::string::npos);
}

// Test writeAttribute with numeric type via template
TEST_F(XmlWriterTest_477, WriteAttributeIntegerType_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeAttribute("count"_sr, 42);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count=\"42\"") != std::string::npos);
}

// Test that destructor closes all open tags
TEST_F(XmlWriterTest_477, DestructorClosesOpenTags_477) {
    {
        XmlWriter writer(oss);
        writer.startElement("outer", XmlFormatting::None);
        writer.startElement("inner", XmlFormatting::None);
        // Don't explicitly close
    }
    std::string output = oss.str();
    // Destructor should close open elements
    EXPECT_TRUE(output.find("</inner>") != std::string::npos || output.find("/>") != std::string::npos);
}

// Test writing text with special characters that need escaping
TEST_F(XmlWriterTest_477, WriteTextWithSpecialChars_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeText("<>&\""_sr, XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Special characters should be escaped
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
    EXPECT_TRUE(output.find("&gt;") != std::string::npos);
}

// Test writing attribute value with special characters
TEST_F(XmlWriterTest_477, WriteAttributeWithSpecialChars_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.writeAttribute("name"_sr, "a<b>c&d"_sr);
    writer.ensureTagClosed();
    std::string output = oss.str();
    // Attribute values should have special chars escaped
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
}

// Test XmlFormatting::Newline
TEST_F(XmlWriterTest_477, FormattingNewline_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.ensureTagClosed();
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Should contain newlines due to formatting
    EXPECT_TRUE(output.find("\n") != std::string::npos);
}

// Test ensureTagClosed when no tag is open (should be safe)
TEST_F(XmlWriterTest_477, EnsureTagClosedNoOpenTag_477) {
    XmlWriter writer(oss);
    // No startElement called, calling ensureTagClosed should not crash
    writer.ensureTagClosed();
    // Just verify it doesn't crash
    SUCCEED();
}

// Test startElement chaining (returns reference)
TEST_F(XmlWriterTest_477, StartElementReturnsReference_477) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("element", XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// Test endElement chaining (returns reference)
TEST_F(XmlWriterTest_477, EndElementReturnsReference_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    writer.ensureTagClosed();
    XmlWriter& ref = writer.endElement(XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// Test writeText chaining (returns reference)
TEST_F(XmlWriterTest_477, WriteTextReturnsReference_477) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::None);
    XmlWriter& ref = writer.writeText("text"_sr, XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// Test writeComment chaining (returns reference)
TEST_F(XmlWriterTest_477, WriteCommentReturnsReference_477) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.writeComment("comment"_sr, XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}
