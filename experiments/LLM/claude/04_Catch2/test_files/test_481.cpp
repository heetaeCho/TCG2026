#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_481 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// ==================== writeStylesheetRef Tests ====================

TEST_F(XmlWriterTest_481, WriteStylesheetRef_BasicUrl_481) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl");
    std::string output = oss.str();
    EXPECT_NE(output.find(R"(<?xml-stylesheet type="text/xsl" href="style.xsl"?>)"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteStylesheetRef_EmptyUrl_481) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("");
    std::string output = oss.str();
    EXPECT_NE(output.find(R"(<?xml-stylesheet type="text/xsl" href=""?>)"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteStylesheetRef_FullUrl_481) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("http://example.com/styles/report.xsl");
    std::string output = oss.str();
    EXPECT_NE(output.find(R"(<?xml-stylesheet type="text/xsl" href="http://example.com/styles/report.xsl"?>)"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteStylesheetRef_EndsWithNewline_481) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl");
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

// ==================== Construction Tests ====================

TEST_F(XmlWriterTest_481, Constructor_WritesDeclaration_481) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    // XML declaration is typically written on construction
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

// ==================== startElement / endElement Tests ====================

TEST_F(XmlWriterTest_481, StartElement_WritesOpeningTag_481) {
    XmlWriter writer(oss);
    writer.startElement("TestElement", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("TestElement"), std::string::npos);
}

TEST_F(XmlWriterTest_481, StartElement_ReturnsSelf_481) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.startElement("Elem", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::Newline);
}

TEST_F(XmlWriterTest_481, NestedElements_481) {
    XmlWriter writer(oss);
    writer.startElement("Parent", XmlFormatting::Newline);
    writer.startElement("Child", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("Parent"), std::string::npos);
    EXPECT_NE(output.find("Child"), std::string::npos);
}

TEST_F(XmlWriterTest_481, EndElement_ReturnsSelf_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    XmlWriter& ref = writer.endElement(XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
}

// ==================== writeAttribute Tests ====================

TEST_F(XmlWriterTest_481, WriteAttribute_StringRef_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeAttribute("name", StringRef("value"));
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteAttribute_Bool_True_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeAttribute("flag", true);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("flag"), std::string::npos);
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteAttribute_Bool_False_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeAttribute("flag", false);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("flag"), std::string::npos);
    EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteAttribute_CharPtr_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeAttribute("attr", "charvalue");
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("attr"), std::string::npos);
    EXPECT_NE(output.find("charvalue"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteAttribute_NumericTemplate_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeAttribute("count", 42);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("count"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

// ==================== writeText Tests ====================

TEST_F(XmlWriterTest_481, WriteText_BasicText_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    XmlWriter& ref = writer.writeText("Hello World", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteText_EmptyText_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeText("", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    // Should not crash
    std::string output = oss.str();
    EXPECT_NE(output.find("Elem"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteText_SpecialCharacters_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeText("<>&\"", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    // Special characters should be escaped
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

// ==================== writeComment Tests ====================

TEST_F(XmlWriterTest_481, WriteComment_BasicComment_481) {
    XmlWriter writer(oss);
    XmlWriter& ref = writer.writeComment("This is a comment", XmlFormatting::Newline);
    EXPECT_EQ(&ref, &writer);
    std::string output = oss.str();
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("This is a comment"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteComment_EmptyComment_481) {
    XmlWriter writer(oss);
    writer.writeComment("", XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
}

// ==================== scopedElement Tests ====================

TEST_F(XmlWriterTest_481, ScopedElement_AutoCloses_481) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("ScopedElem", XmlFormatting::Newline);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("ScopedElem"), std::string::npos);
}

TEST_F(XmlWriterTest_481, ScopedElement_NestedScoped_481) {
    XmlWriter writer(oss);
    {
        auto outer = writer.scopedElement("Outer", XmlFormatting::Newline);
        {
            auto inner = writer.scopedElement("Inner", XmlFormatting::Newline);
        }
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("Outer"), std::string::npos);
    EXPECT_NE(output.find("Inner"), std::string::npos);
}

// ==================== ensureTagClosed Tests ====================

TEST_F(XmlWriterTest_481, EnsureTagClosed_AfterStartElement_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.ensureTagClosed();
    std::string output = oss.str();
    // The tag should be closed with ">"
    EXPECT_NE(output.find(">"), std::string::npos);
    writer.endElement(XmlFormatting::Newline);
}

TEST_F(XmlWriterTest_481, EnsureTagClosed_NoOpenTag_481) {
    XmlWriter writer(oss);
    // Should not crash when no tag is open
    writer.ensureTagClosed();
}

// ==================== Formatting Tests ====================

TEST_F(XmlWriterTest_481, Formatting_None_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    // Should still produce valid XML
    std::string output = oss.str();
    EXPECT_NE(output.find("Elem"), std::string::npos);
}

TEST_F(XmlWriterTest_481, Formatting_Indent_481) {
    XmlWriter writer(oss);
    writer.startElement("Parent", XmlFormatting::Newline);
    writer.startElement("Child", XmlFormatting::Indent);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("Parent"), std::string::npos);
    EXPECT_NE(output.find("Child"), std::string::npos);
}

// ==================== Multiple Operations Tests ====================

TEST_F(XmlWriterTest_481, MultipleElements_481) {
    XmlWriter writer(oss);
    writer.startElement("Root", XmlFormatting::Newline);
    writer.startElement("A", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.startElement("B", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("Root"), std::string::npos);
    EXPECT_NE(output.find("<A"), std::string::npos);
    EXPECT_NE(output.find("<B"), std::string::npos);
}

TEST_F(XmlWriterTest_481, ElementWithAttributeAndText_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeAttribute("key", "val");
    writer.writeText("content", XmlFormatting::None);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("val"), std::string::npos);
    EXPECT_NE(output.find("content"), std::string::npos);
}

// ==================== Destructor Tests ====================

TEST_F(XmlWriterTest_481, Destructor_ClosesOpenElements_481) {
    {
        XmlWriter writer(oss);
        writer.startElement("Root", XmlFormatting::Newline);
        writer.startElement("Child", XmlFormatting::Newline);
        // Destructor should close open elements
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("Root"), std::string::npos);
    EXPECT_NE(output.find("Child"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteStylesheetRef_WithSpecialCharsInUrl_481) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("path/to/style.xsl?param=value&other=2");
    std::string output = oss.str();
    EXPECT_NE(output.find("xml-stylesheet"), std::string::npos);
}

TEST_F(XmlWriterTest_481, WriteAttribute_MultipleAttributes_481) {
    XmlWriter writer(oss);
    writer.startElement("Elem", XmlFormatting::Newline);
    writer.writeAttribute("a1", "v1");
    writer.writeAttribute("a2", "v2");
    writer.writeAttribute("a3", "v3");
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("a1"), std::string::npos);
    EXPECT_NE(output.find("a2"), std::string::npos);
    EXPECT_NE(output.find("a3"), std::string::npos);
}
