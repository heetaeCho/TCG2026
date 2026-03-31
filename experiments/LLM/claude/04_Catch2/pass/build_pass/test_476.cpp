#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterTest_476 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// ===== writeAttribute(StringRef, StringRef) Tests =====

TEST_F(XmlWriterTest_476, WriteAttribute_NormalNameAndValue_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeAttribute("id", "value123");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("id=\"value123\""), std::string::npos);
}

TEST_F(XmlWriterTest_476, WriteAttribute_EmptyName_NoOutput_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeAttribute("", "value");
    writer.ensureTagClosed();
    std::string output = oss.str();
    // Should not contain the attribute value since name is empty
    EXPECT_EQ(output.find("value"), std::string::npos);
}

TEST_F(XmlWriterTest_476, WriteAttribute_EmptyValue_NoOutput_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeAttribute("name", "");
    writer.ensureTagClosed();
    std::string output = oss.str();
    // Should not contain the attribute name since value is empty
    EXPECT_EQ(output.find("name="), std::string::npos);
}

TEST_F(XmlWriterTest_476, WriteAttribute_BothEmpty_NoOutput_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeAttribute("", "");
    writer.ensureTagClosed();
    std::string output = oss.str();
    // The output should just be the element, no extra attributes
    EXPECT_NE(output.find("<root"), std::string::npos);
}

TEST_F(XmlWriterTest_476, WriteAttribute_ReturnsSelf_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    XmlWriter& result = writer.writeAttribute("key", "val");
    EXPECT_EQ(&result, &writer);
}

TEST_F(XmlWriterTest_476, WriteAttribute_SpecialCharsInValueAreEncoded_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeAttribute("data", "a&b<c>d\"e");
    writer.ensureTagClosed();
    std::string output = oss.str();
    // Ampersand should be encoded
    EXPECT_NE(output.find("&amp;"), std::string::npos);
    // Less than should be encoded
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    // Greater than should be encoded
    EXPECT_NE(output.find("&gt;"), std::string::npos);
    // Quote should be encoded for attributes
    EXPECT_NE(output.find("&quot;"), std::string::npos);
}

TEST_F(XmlWriterTest_476, WriteAttribute_MultipleAttributes_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeAttribute("key1", "val1");
    writer.writeAttribute("key2", "val2");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("key1=\"val1\""), std::string::npos);
    EXPECT_NE(output.find("key2=\"val2\""), std::string::npos);
}

// ===== writeAttribute(StringRef, bool) Tests =====

TEST_F(XmlWriterTest_476, WriteAttribute_BoolTrue_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeAttribute("flag", true);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"true\""), std::string::npos);
}

TEST_F(XmlWriterTest_476, WriteAttribute_BoolFalse_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeAttribute("flag", false);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("flag=\"false\""), std::string::npos);
}

// ===== writeAttribute(StringRef, const char*) Tests =====

TEST_F(XmlWriterTest_476, WriteAttribute_CharPtr_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    const char* val = "hello";
    writer.writeAttribute("greeting", val);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("greeting=\"hello\""), std::string::npos);
}

// ===== startElement / endElement Tests =====

TEST_F(XmlWriterTest_476, StartAndEndElement_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("<root"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

TEST_F(XmlWriterTest_476, NestedElements_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.startElement("child", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("<root"), std::string::npos);
    EXPECT_NE(output.find("<child"), std::string::npos);
    EXPECT_NE(output.find("</child>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// ===== writeText Tests =====

TEST_F(XmlWriterTest_476, WriteText_Normal_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeText("Hello World", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

TEST_F(XmlWriterTest_476, WriteText_SpecialCharsEncoded_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeText("a<b>c&d", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

// ===== writeComment Tests =====

TEST_F(XmlWriterTest_476, WriteComment_Normal_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeComment("this is a comment", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
}

// ===== writeStylesheetRef Tests =====

TEST_F(XmlWriterTest_476, WriteStylesheetRef_476) {
    XmlWriter writer(oss);
    writer.writeStylesheetRef("style.xsl");
    std::string output = oss.str();
    EXPECT_NE(output.find("style.xsl"), std::string::npos);
    EXPECT_NE(output.find("xml-stylesheet"), std::string::npos);
}

// ===== scopedElement Tests =====

TEST_F(XmlWriterTest_476, ScopedElement_AutoCloses_476) {
    XmlWriter writer(oss);
    {
        auto scoped = writer.scopedElement("item", XmlFormatting::None);
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("<item"), std::string::npos);
    EXPECT_NE(output.find("</item>"), std::string::npos);
}

// ===== ensureTagClosed Tests =====

TEST_F(XmlWriterTest_476, EnsureTagClosed_ClosesOpenTag_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find(">"), std::string::npos);
}

// ===== Chaining Tests =====

TEST_F(XmlWriterTest_476, ChainingMultipleAttributes_476) {
    XmlWriter writer(oss);
    writer.startElement("elem", XmlFormatting::None)
          .writeAttribute("a", "1")
          .writeAttribute("b", "2")
          .writeAttribute("c", "3");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("a=\"1\""), std::string::npos);
    EXPECT_NE(output.find("b=\"2\""), std::string::npos);
    EXPECT_NE(output.find("c=\"3\""), std::string::npos);
}

// ===== Template writeAttribute Tests =====

TEST_F(XmlWriterTest_476, WriteAttribute_IntegerType_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeAttribute("count", 42);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("count=\"42\""), std::string::npos);
}

TEST_F(XmlWriterTest_476, WriteAttribute_FloatingPointType_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeAttribute("value", 3.14);
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("value=\""), std::string::npos);
}

// ===== Formatting Tests =====

TEST_F(XmlWriterTest_476, StartElement_WithNewlineFormatting_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::Newline);
    writer.endElement(XmlFormatting::Newline);
    std::string output = oss.str();
    EXPECT_NE(output.find("\n"), std::string::npos);
}

// ===== Destructor auto-close Tests =====

TEST_F(XmlWriterTest_476, Destructor_ClosesOpenElements_476) {
    {
        XmlWriter writer(oss);
        writer.startElement("root", XmlFormatting::None);
        writer.startElement("child", XmlFormatting::None);
        // Writer goes out of scope - should close open tags
    }
    std::string output = oss.str();
    EXPECT_NE(output.find("</child>"), std::string::npos);
    EXPECT_NE(output.find("</root>"), std::string::npos);
}

// ===== Edge cases =====

TEST_F(XmlWriterTest_476, WriteAttribute_SingleCharNameAndValue_476) {
    XmlWriter writer(oss);
    writer.startElement("e", XmlFormatting::None);
    writer.writeAttribute("x", "y");
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("x=\"y\""), std::string::npos);
}

TEST_F(XmlWriterTest_476, WriteAttribute_LongStringValue_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    std::string longVal(1000, 'a');
    writer.writeAttribute("data", StringRef(longVal));
    writer.ensureTagClosed();
    std::string output = oss.str();
    EXPECT_NE(output.find("data=\""), std::string::npos);
    EXPECT_NE(output.find(longVal), std::string::npos);
}

TEST_F(XmlWriterTest_476, WriteText_EmptyText_476) {
    XmlWriter writer(oss);
    writer.startElement("root", XmlFormatting::None);
    writer.writeText("", XmlFormatting::None);
    writer.endElement(XmlFormatting::None);
    std::string output = oss.str();
    // Just make sure we have the element
    EXPECT_NE(output.find("<root"), std::string::npos);
}

TEST_F(XmlWriterTest_476, Declaration_WrittenOnConstruction_476) {
    XmlWriter writer(oss);
    std::string output = oss.str();
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}
