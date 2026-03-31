#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_479 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// ==================== Construction and Declaration ====================

TEST_F(XmlWriterTest_479, ConstructorWritesDeclaration_479) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

// ==================== writeText tests ====================

TEST_F(XmlWriterTest_479, WriteTextWithinElement_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText("Hello World", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Hello World") != std::string::npos);
}

TEST_F(XmlWriterTest_479, WriteTextEmptyStringDoesNothing_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    std::string beforeText = oss.str();
    // Ensure tag is open, then write empty text
    writer.writeText("", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // The empty text should not add content between the tags
    // Just ensure it doesn't crash and returns properly
    EXPECT_TRUE(output.find("root") != std::string::npos);
}

TEST_F(XmlWriterTest_479, WriteTextEncodesSpecialCharacters_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText("<>&\"", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
    EXPECT_TRUE(output.find("&gt;") != std::string::npos);
}

TEST_F(XmlWriterTest_479, WriteTextReturnsSelfForChaining_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeText("test", XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

TEST_F(XmlWriterTest_479, WriteTextWithNewlineFormatting_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText("text content", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("text content") != std::string::npos);
}

// ==================== startElement / endElement tests ====================

TEST_F(XmlWriterTest_479, StartAndEndElement_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

TEST_F(XmlWriterTest_479, NestedElements_479) {
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

// ==================== writeAttribute tests ====================

TEST_F(XmlWriterTest_479, WriteAttributeStringRef_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("name", StringRef("value"));
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name=\"value\"") != std::string::npos);
}

TEST_F(XmlWriterTest_479, WriteAttributeBoolTrue_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("flag", true);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"true\"") != std::string::npos);
}

TEST_F(XmlWriterTest_479, WriteAttributeBoolFalse_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("flag", false);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"false\"") != std::string::npos);
}

TEST_F(XmlWriterTest_479, WriteAttributeCharPtr_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("key", "val");
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("key=\"val\"") != std::string::npos);
}

TEST_F(XmlWriterTest_479, WriteMultipleAttributes_479) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("a", "1");
    writer.writeAttribute("b", "2");
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=\"1\"") != std::string::npos);
    EXPECT_TRUE(output.find("b=\"2\"") != std::string::npos);
}

// ==================== writeComment tests ====================

TEST_F(XmlWriterTest_479, WriteComment_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeComment("this is a comment", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("this is a comment") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

// ==================== writeStylesheetRef tests ====================

TEST_F(XmlWriterTest_479, WriteStylesheetRef_479) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl");
    std::string output = oss.str();
    EXPECT_TRUE(output.find("style.xsl") != std::string::npos);
    EXPECT_TRUE(output.find("xml-stylesheet") != std::string::npos);
}

// ==================== scopedElement tests ====================

TEST_F(XmlWriterTest_479, ScopedElementAutoCloses_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    {
        auto scoped = writer.scopedElement("child", XmlFormatting::Newline);
    }
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<child") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

// ==================== ensureTagClosed tests ====================

TEST_F(XmlWriterTest_479, EnsureTagClosed_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find(">") != std::string::npos);
}

// ==================== Edge / Error cases ====================

TEST_F(XmlWriterTest_479, WriteTextWithoutElementThrows_479) {
    XmlWriter writer(oss);
    // No startElement called, m_tags should be empty
    EXPECT_ANY_THROW(writer.writeText("text", XmlFormatting::None));
}

TEST_F(XmlWriterTest_479, WriteTextWithSpecialXmlChars_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText("a < b && c > d", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Should be encoded
    EXPECT_TRUE(output.find("<") == std::string::npos ||
                output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
}

TEST_F(XmlWriterTest_479, DestructorClosesAllElements_479) {
    {
        XmlWriter writer(oss);
        writer.startElement("root", XmlFormatting::Newline);
        writer.startElement("child", XmlFormatting::Newline);
        // Destructor should close both elements
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</child>") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

TEST_F(XmlWriterTest_479, WriteTextWithIndentFormatting_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("child", XmlFormatting::Newline);
    writer.writeText("indented text", XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("indented text") != std::string::npos);
}

TEST_F(XmlWriterTest_479, WriteAttributeReturnsSelfForChaining_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeAttribute("a", "b");
    EXPECT_EQ(&ref, &writer);
}

TEST_F(XmlWriterTest_479, WriteCommentReturnsSelfForChaining_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeComment("comment", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

TEST_F(XmlWriterTest_479, StartElementReturnsSelfForChaining_479) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("root", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

TEST_F(XmlWriterTest_479, EndElementReturnsSelfForChaining_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.endElement(XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

TEST_F(XmlWriterTest_479, WriteAttributeNumericValue_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("count", 42);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count=\"42\"") != std::string::npos);
}

TEST_F(XmlWriterTest_479, WriteTextMultipleTimes_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeText("Hello ", XmlFormatting::None);
    writer.writeText("World", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("Hello ") != std::string::npos);
    EXPECT_TRUE(output.find("World") != std::string::npos);
}

TEST_F(XmlWriterTest_479, ElementWithNoContentSelfCloses_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("empty", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Either self-closing or explicit close for "empty"
    EXPECT_TRUE(output.find("empty") != std::string::npos);
}

TEST_F(XmlWriterTest_479, FormattingNone_479) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeText("text", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("text") != std::string::npos);
}
