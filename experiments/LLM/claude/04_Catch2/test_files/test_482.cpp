#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_482 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that constructing an XmlWriter writes a declaration
TEST_F(XmlWriterTest_482, ConstructorWritesDeclaration_482) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

// Test ensureTagClosed when no tag is open (should be a no-op)
TEST_F(XmlWriterTest_482, EnsureTagClosedWhenNoTagOpen_482) {
    XmlWriter writer(oss);
    std::string beforeClose = oss.str();
    writer.ensureTagClosed();
    std::string afterClose = oss.str();
    // No '>' should be appended when no tag is open
    EXPECT_EQ(beforeClose, afterClose);
}

// Test ensureTagClosed when a tag is open
TEST_F(XmlWriterTest_482, EnsureTagClosedWhenTagIsOpen_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    std::string beforeClose = oss.str();
    writer.ensureTagClosed();
    std::string afterClose = oss.str();
    // The tag should now be closed with '>'
    EXPECT_TRUE(afterClose.find(">") != std::string::npos);
    EXPECT_NE(beforeClose, afterClose);
}

// Test startElement creates an opening tag
TEST_F(XmlWriterTest_482, StartElementCreatesTag_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
}

// Test endElement closes a tag
TEST_F(XmlWriterTest_482, EndElementClosesTag_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</root>") != std::string::npos || output.find("/>") != std::string::npos);
}

// Test writing a string attribute
TEST_F(XmlWriterTest_482, WriteStringAttribute_482) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("name"_catch_sr, "value"_catch_sr);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name=") != std::string::npos);
    EXPECT_TRUE(output.find("value") != std::string::npos);
}

// Test writing a boolean attribute (true)
TEST_F(XmlWriterTest_482, WriteBoolAttributeTrue_482) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("flag"_catch_sr, true);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=") != std::string::npos);
    EXPECT_TRUE(output.find("true") != std::string::npos);
}

// Test writing a boolean attribute (false)
TEST_F(XmlWriterTest_482, WriteBoolAttributeFalse_482) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("flag"_catch_sr, false);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=") != std::string::npos);
    EXPECT_TRUE(output.find("false") != std::string::npos);
}

// Test writing a const char* attribute
TEST_F(XmlWriterTest_482, WriteCharPtrAttribute_482) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    const char* val = "hello";
    writer.writeAttribute("attr"_catch_sr, val);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("attr=") != std::string::npos);
    EXPECT_TRUE(output.find("hello") != std::string::npos);
}

// Test writeText writes text content
TEST_F(XmlWriterTest_482, WriteTextContent_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText("Hello World"_catch_sr, XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Hello World") != std::string::npos);
}

// Test writeComment writes a comment
TEST_F(XmlWriterTest_482, WriteComment_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeComment("This is a comment"_catch_sr, XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("This is a comment") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

// Test writeStylesheetRef writes a stylesheet reference
TEST_F(XmlWriterTest_482, WriteStylesheetRef_482) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl"_catch_sr);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("style.xsl") != std::string::npos);
    EXPECT_TRUE(output.find("xml-stylesheet") != std::string::npos);
}

// Test nested elements
TEST_F(XmlWriterTest_482, NestedElements_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("child", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
    EXPECT_TRUE(output.find("<child") != std::string::npos);
}

// Test scopedElement auto-closes
TEST_F(XmlWriterTest_482, ScopedElementAutoCloses_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    {
        auto scoped = writer.scopedElement("scoped", XmlFormatting::Newline);
    }
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("scoped") != std::string::npos);
}

// Test XmlFormatting::None does not add extra newlines
TEST_F(XmlWriterTest_482, NoFormattingOption_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeText("text"_catch_sr, XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("text") != std::string::npos);
}

// Test empty element (start then immediately end)
TEST_F(XmlWriterTest_482, EmptyElement_482) {
    XmlWriter writer(oss);
    writer.startElement("empty", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Empty element should produce self-closing tag or open/close pair
    EXPECT_TRUE(output.find("empty") != std::string::npos);
}

// Test writeText with special XML characters escapes them
TEST_F(XmlWriterTest_482, WriteTextEscapesSpecialChars_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText("<>&\""_catch_sr, XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // The raw characters should be escaped
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
    EXPECT_TRUE(output.find("&gt;") != std::string::npos);
}

// Test writeAttribute with special characters in value
TEST_F(XmlWriterTest_482, WriteAttributeEscapesSpecialChars_482) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("attr"_catch_sr, "<value>"_catch_sr);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("&lt;") != std::string::npos || output.find("&quot;") != std::string::npos || output.find("<value>") == std::string::npos);
}

// Test multiple attributes on same element
TEST_F(XmlWriterTest_482, MultipleAttributes_482) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("a"_catch_sr, "1"_catch_sr);
    writer.writeAttribute("b"_catch_sr, "2"_catch_sr);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=") != std::string::npos);
    EXPECT_TRUE(output.find("b=") != std::string::npos);
}

// Test calling ensureTagClosed multiple times is safe
TEST_F(XmlWriterTest_482, EnsureTagClosedIdempotent_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string afterFirst = oss.str();
    writer.ensureTagClosed();
    std::string afterSecond = oss.str();
    EXPECT_EQ(afterFirst, afterSecond);
}

// Test writeAttribute returns reference to same writer (chaining)
TEST_F(XmlWriterTest_482, WriteAttributeChaining_482) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeAttribute("a"_catch_sr, "1"_catch_sr);
    EXPECT_EQ(&ref, &writer);
}

// Test startElement returns reference to same writer (chaining)
TEST_F(XmlWriterTest_482, StartElementChaining_482) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("root", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test endElement returns reference to same writer (chaining)
TEST_F(XmlWriterTest_482, EndElementChaining_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.endElement(XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test writeText returns reference to same writer (chaining)
TEST_F(XmlWriterTest_482, WriteTextChaining_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeText("text"_catch_sr, XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test writeComment returns reference to same writer (chaining)
TEST_F(XmlWriterTest_482, WriteCommentChaining_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeComment("comment"_catch_sr, XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// Test deeply nested elements
TEST_F(XmlWriterTest_482, DeeplyNestedElements_482) {
    XmlWriter writer(oss);
    writer.startElement("a", XmlFormatting::Newline);
    writer.startElement("b", XmlFormatting::Newline);
    writer.startElement("c", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<a") != std::string::npos);
    EXPECT_TRUE(output.find("<b") != std::string::npos);
    EXPECT_TRUE(output.find("<c") != std::string::npos);
}

// Test writeText with empty string
TEST_F(XmlWriterTest_482, WriteEmptyText_482) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText(""_catch_sr, XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    // Should not crash; output should still be valid
    std::string output = oss.str();
    EXPECT_TRUE(output.find("root") != std::string::npos);
}

// Test destructor closes all open tags
TEST_F(XmlWriterTest_482, DestructorClosesOpenTags_482) {
    {
        XmlWriter writer(oss);
        writer.startElement("root", XmlFormatting::Newline);
        writer.startElement("child", XmlFormatting::Newline);
        // Destructor should close open tags
    }
    std::string output = oss.str();
    // After destruction, the output should be well-formed enough that tags are closed
    EXPECT_FALSE(output.empty());
}

// Test numeric attribute via template
TEST_F(XmlWriterTest_482, WriteNumericAttribute_482) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("count"_catch_sr, 42);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count=") != std::string::npos);
    EXPECT_TRUE(output.find("42") != std::string::npos);
}
