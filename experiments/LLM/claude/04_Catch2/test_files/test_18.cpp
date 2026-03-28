#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_18 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// ============================================================
// Constructor and Destructor Tests
// ============================================================

TEST_F(XmlWriterTest_18, ConstructorWritesDeclaration_18) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<?xml") != std::string::npos);
}

TEST_F(XmlWriterTest_18, DestructorClosesOpenTags_18) {
    {
        XmlWriter writer(oss);
        writer.startElement("root", XmlFormatting::Newline);
        writer.startElement("child", XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</child>") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

// ============================================================
// startElement Tests
// ============================================================

TEST_F(XmlWriterTest_18, StartElementWritesOpeningTag_18) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root>") != std::string::npos || output.find("<root") != std::string::npos);
}

TEST_F(XmlWriterTest_18, StartElementNested_18) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("child", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
    EXPECT_TRUE(output.find("<child") != std::string::npos);
}

TEST_F(XmlWriterTest_18, StartElementWithIndent_18) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Indent);
    writer.startElement("child", XmlFormatting::Indent);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("child") != std::string::npos);
}

TEST_F(XmlWriterTest_18, StartElementNoFormatting_18) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<root") != std::string::npos);
}

// ============================================================
// endElement Tests
// ============================================================

TEST_F(XmlWriterTest_18, EndElementWritesClosingTag_18) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

TEST_F(XmlWriterTest_18, EndElementReturnsSelf_18) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    XmlWriter& ref = writer.endElement(XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

TEST_F(XmlWriterTest_18, EndElementNestedCorrectOrder_18) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.startElement("child", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // child should close before root
    auto childClose = output.find("</child>");
    auto rootClose = output.find("</root>");
    EXPECT_TRUE(childClose != std::string::npos);
    EXPECT_TRUE(rootClose != std::string::npos);
    EXPECT_LT(childClose, rootClose);
}

// ============================================================
// writeAttribute Tests (StringRef overload)
// ============================================================

TEST_F(XmlWriterTest_18, WriteAttributeStringRef_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("name", StringRef("value"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("name=\"value\"") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteAttributeReturnsSelf_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeAttribute("attr", StringRef("val"));
    EXPECT_EQ(&ref, &writer);
}

// ============================================================
// writeAttribute Tests (bool overload)
// ============================================================

TEST_F(XmlWriterTest_18, WriteAttributeBoolTrue_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("flag", true);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"true\"") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteAttributeBoolFalse_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("flag", false);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("flag=\"false\"") != std::string::npos);
}

// ============================================================
// writeAttribute Tests (const char* overload)
// ============================================================

TEST_F(XmlWriterTest_18, WriteAttributeCharPtr_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("key", "myvalue");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("key=\"myvalue\"") != std::string::npos);
}

// ============================================================
// writeAttribute Tests (template overload - numeric types)
// ============================================================

TEST_F(XmlWriterTest_18, WriteAttributeIntValue_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("count", 42);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("count=\"42\"") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteAttributeDoubleValue_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("ratio", 3.14);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("ratio=\"") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteAttributeNegativeInt_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("value", -100);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("value=\"-100\"") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteAttributeZero_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("val", 0);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("val=\"0\"") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteAttributeUnsignedLong_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("big", 999999UL);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("big=\"999999\"") != std::string::npos);
}

// ============================================================
// writeText Tests
// ============================================================

TEST_F(XmlWriterTest_18, WriteTextInElement_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeText("hello world", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("hello world") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteTextEmpty_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeText("", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<element") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteTextWithSpecialChars_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeText("<>&\"", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Special characters should be escaped
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
    EXPECT_TRUE(output.find("&gt;") != std::string::npos);
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteTextReturnsSelf_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeText("text", XmlFormatting::None);
    EXPECT_EQ(&ref, &writer);
}

// ============================================================
// writeComment Tests
// ============================================================

TEST_F(XmlWriterTest_18, WriteComment_18) {
    XmlWriter writer(oss);
    writer.writeComment("this is a comment", XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<!--") != std::string::npos);
    EXPECT_TRUE(output.find("this is a comment") != std::string::npos);
    EXPECT_TRUE(output.find("-->") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteCommentReturnsSelf_18) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.writeComment("comment", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// ============================================================
// writeStylesheetRef Tests
// ============================================================

TEST_F(XmlWriterTest_18, WriteStylesheetRef_18) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl");
    std::string output = oss.str();
    EXPECT_TRUE(output.find("style.xsl") != std::string::npos);
    EXPECT_TRUE(output.find("xml-stylesheet") != std::string::npos);
}

// ============================================================
// scopedElement Tests
// ============================================================

TEST_F(XmlWriterTest_18, ScopedElementClosesOnDestruction_18) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("scoped", XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("<scoped") != std::string::npos);
    EXPECT_TRUE(output.find("</scoped>") != std::string::npos || output.find("/>") != std::string::npos);
}

TEST_F(XmlWriterTest_18, ScopedElementNested_18) {
    XmlWriter writer(oss);
    {
        auto outer = writer.scopedElement("outer", XmlFormatting::Newline);
        {
            auto inner = writer.scopedElement("inner", XmlFormatting::Newline);
        }
    }
    std::string output = oss.str();
    EXPECT_TRUE(output.find("outer") != std::string::npos);
    EXPECT_TRUE(output.find("inner") != std::string::npos);
}

// ============================================================
// ensureTagClosed Tests
// ============================================================

TEST_F(XmlWriterTest_18, EnsureTagClosedClosesOpenTag_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("attr", "value");
    writer.ensureTagClosed();
    std::string output = oss.str();
    // After ensureTagClosed, the '>' should be present
    EXPECT_TRUE(output.find(">") != std::string::npos);
}

TEST_F(XmlWriterTest_18, EnsureTagClosedIdempotent_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string before = oss.str();
    writer.ensureTagClosed();
    std::string after = oss.str();
    EXPECT_EQ(before, after);
}

// ============================================================
// Multiple Attributes Tests
// ============================================================

TEST_F(XmlWriterTest_18, MultipleAttributesOnSameElement_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("a", "1");
    writer.writeAttribute("b", "2");
    writer.writeAttribute("c", "3");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("a=\"1\"") != std::string::npos);
    EXPECT_TRUE(output.find("b=\"2\"") != std::string::npos);
    EXPECT_TRUE(output.find("c=\"3\"") != std::string::npos);
}

// ============================================================
// Chaining Tests
// ============================================================

TEST_F(XmlWriterTest_18, ChainingWriteAttributes_18) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::Newline)
          .writeAttribute("x", 10)
          .writeAttribute("y", 20);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("x=\"10\"") != std::string::npos);
    EXPECT_TRUE(output.find("y=\"20\"") != std::string::npos);
}

// ============================================================
// Empty Element Tests
// ============================================================

TEST_F(XmlWriterTest_18, EmptyElementStartAndEnd_18) {
    XmlWriter writer(oss);
    writer.startElement("empty", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_TRUE(output.find("empty") != std::string::npos);
}

// ============================================================
// Formatting Tests
// ============================================================

TEST_F(XmlWriterTest_18, NewlineFormatting_18) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Should contain newline characters
    EXPECT_TRUE(output.find('\n') != std::string::npos);
}

TEST_F(XmlWriterTest_18, AttributeEscaping_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("data", StringRef("a\"b"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    // Quotes in attribute values should be escaped
    EXPECT_TRUE(output.find("&quot;") != std::string::npos);
}

// ============================================================
// Complex Document Test
// ============================================================

TEST_F(XmlWriterTest_18, ComplexDocument_18) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.writeAttribute("version", "1.0");
    
    writer.startElement("item", XmlFormatting::Newline | XmlFormatting::Indent);
    writer.writeAttribute("id", 1);
    writer.writeText("First item", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    
    writer.startElement("item", XmlFormatting::Newline | XmlFormatting::Indent);
    writer.writeAttribute("id", 2);
    writer.writeText("Second item", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    
    writer.endElement(XmlFormatting::Newline);
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("version=\"1.0\"") != std::string::npos);
    EXPECT_TRUE(output.find("First item") != std::string::npos);
    EXPECT_TRUE(output.find("Second item") != std::string::npos);
    EXPECT_TRUE(output.find("</root>") != std::string::npos);
}

// ============================================================
// Write attribute with empty string
// ============================================================

TEST_F(XmlWriterTest_18, WriteAttributeEmptyStringValue_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("empty", StringRef(""));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("empty=\"\"") != std::string::npos);
}

// ============================================================
// Write attribute with special XML characters in value
// ============================================================

TEST_F(XmlWriterTest_18, WriteAttributeWithAmpersand_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("data", StringRef("a&b"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("&amp;") != std::string::npos);
}

TEST_F(XmlWriterTest_18, WriteAttributeWithLessThan_18) {
    XmlWriter writer(oss);
    writer.startElement("element", XmlFormatting::Newline);
    writer.writeAttribute("data", StringRef("a<b"));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_TRUE(output.find("&lt;") != std::string::npos);
}
